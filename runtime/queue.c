#include <stdlib.h>
#include <simplex/macros.h>
#include <simplex/atomic.h>
#include <simplex/mutex.h>
#include <simplex/queue.h>

#define FREE_FLAG_1     0x01
#define FREE_FLAG_2     0x02

#define FREE_FLAG_ALL   ((FREE_FLAG_1) | (FREE_FLAG_2))

struct _queue_node_t {
    long free_flag;
    void *data;
    queue_node_t *next;
};

int queue_init(queue_t *q)
{
    queue_node_t *init_node;

    q->lock     = 0;
    q->size     = 0;
    q->revision = 0;

    init_node = (queue_node_t *)malloc(sizeof(*init_node));

    init_node->free_flag = 0;
    init_node->data      = NULL;
    init_node->next      = NULL;

    q->head = init_node;
    q->tail = init_node;

    return 0;
}

int queue_uninit(queue_t *q)
{
    free(q->head);

    return 0;
}

void queue_push(queue_t *q, void *data)
{
    queue_node_t *new_tail, *prev_tail;

    new_tail = (queue_node_t *)malloc(sizeof(*new_tail));

    new_tail->free_flag = 0;
    new_tail->data      = data;
    new_tail->next      = NULL;

    do {
        prev_tail = q->tail;
    } while (!atomic_cas_ptr(&q->tail, prev_tail, new_tail));

    prev_tail->next = new_tail;

    atomic_add(&q->size, 1);
}

void *queue_pop(queue_t *q)
{
    void *result;
    queue_node_t *prev_head, *new_head;
    long prev_revision;

    do {
        prev_head = q->head;

        new_head = prev_head->next;

        if (new_head == NULL) {
            return NULL;
        }

        prev_revision = q->revision;
    } while (!atomic_revision_cas_ptr(
        &q->lock, &q->revision, prev_revision,
        (void **)&q->head, prev_head, new_head));

    result = new_head->data;

    if (atomic_or(&prev_head->free_flag, FREE_FLAG_1) == FREE_FLAG_ALL) {
        free(prev_head);
    }

    if (atomic_or(&new_head->free_flag, FREE_FLAG_2) == FREE_FLAG_ALL) {
        free(new_head);
    }

    atomic_sub(&q->size, 1);

    return result;
}

long queue_size(queue_t *q)
{
    long result = q->size;

    return result;
}
