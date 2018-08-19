#ifndef _RUNTIME_PAGE_H_
#define _RUNTIME_PAGE_H_

int   page_alloc_size(void);
void *page_alloc(void);
int   page_free(void *pages);

#endif /* _RUNTIME_PAGE_H_ */
