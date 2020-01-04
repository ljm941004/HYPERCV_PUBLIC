/*************************************************************************
	> File Name: core/include/core/vector.h
	> Author: ljm
	> Mail: jimin@iscas.ac.cn
 ************************************************************************/
 
# define MIN_LEN 256
# define CVEFAILED  -1
# define CVESUCCESS  0
# define CVEPUSHBACK 1
# define CVEPOPBACK  2
# define CVEINSERT   3
# define CVERM       4
# define EXPANED_VAL 1
# define REDUSED_VAL 2

typedef void *hypercv_iterator;
typedef struct _hypercv_vector *hypercv_vector;

hypercv_vector hypercv_vector_create(const size_t size                           );
void      hypercv_vector_destroy  (const hypercv_vector cv                            );
size_t    hypercv_vector_length   (const hypercv_vector cv                            );
int       hypercv_vector_pushback (const hypercv_vector cv, void *memb                );
int       hypercv_vector_popback  (const hypercv_vector cv, void *memb                );
size_t    hypercv_vector_iter_at  (const hypercv_vector cv, hypercv_iterator iter            );
int       hypercv_vector_iter_val (const hypercv_vector cv, hypercv_iterator iter, void *memb);
hypercv_iterator hypercv_vector_begin    (const hypercv_vector cv                            );
hypercv_iterator hypercv_vector_end      (const hypercv_vector cv                            );
hypercv_iterator hypercv_vector_next     (const hypercv_vector cv, hypercv_iterator iter            );
int       hypercv_vector_val_at   (const hypercv_vector cv, size_t index, void *memb  );
int       hypercv_vector_insert   (const hypercv_vector cv, hypercv_iterator iter, void *memb);
int       hypercv_vector_insert_at(const hypercv_vector cv, size_t index, void *memb  );
int       hypercv_vector_rm       (const hypercv_vector cv, hypercv_iterator iter            );
int       hypercv_vector_rm_at    (const hypercv_vector cv, size_t index              );

	/* for test  */
void      hypercv_vector_info          (const hypercv_vector cv                            );
void      hypercv_vector_print         (const hypercv_vector cv                            );


