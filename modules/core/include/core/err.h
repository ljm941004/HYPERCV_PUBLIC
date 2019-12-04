#ifndef MEMORY_H

#define MEMORY_H
#define MALLOC_FAIL_CHECK(__ptr_in)                                        \
do {                                                                       \
    if(!(__ptr_in))                                                        \
    {                                                                      \
        fprintf(stderr, "memory allocation faild in %s, ", __FUNCTION__);  \
        fprintf(stderr, "file: %s, line: %d. exit.\n", __FILE__, __LINE__);\
        exit(1);                                                           \
    }                                                                      \
} while(0)

#endif /* MEMORY_H */


#define _assert(exp, description) \
        { \
           if(exp) \
              ; \
           else \
          { \
              printf("ERROR: "); \
              printf(description);   \
              printf("\n");   \
              exit(1);  \
          } \
       } 
