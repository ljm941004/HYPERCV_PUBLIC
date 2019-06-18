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
