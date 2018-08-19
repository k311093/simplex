#ifndef _RUNTIME_QUEUE_H_
#define _RUNTIME_QUEUE_H_

typedef struct _queue_t queue_t;
typedef struct _queue_node_t queue_node_t;

struct _queue_t {
    long lock;

    long size;
    long revision;

    queue_node_t *head;
    queue_node_t *tail;
};

int   queue_init(queue_t *q);
int   queue_uninit(queue_t *q);
void  queue_push(queue_t *q, void *data);
void *queue_pop(queue_t *q);
long  queue_size(queue_t *q);

#endif /* _RUNTIME_QUEUE_H_ */
