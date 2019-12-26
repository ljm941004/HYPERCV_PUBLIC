/*************************************************************************
	> File Name: core/src/vector.c
	> Author: ljm
	> Mail: jimin@iscas.ac.cn
 ************************************************************************/
#include "precomp.h"
 
#ifndef __gnu_linux__
#define __func__ "unknown"
#define inline __forceinline
#endif
 
# define CWARNING_ITER(cv, iter, file, func, line) \
	do {\
	if ((hypercv_vector_begin(cv) > iter) || (hypercv_vector_end(cv) <= iter)) {\
	fprintf(stderr, "var(" #iter ") warng out of range, "\
	"at file:%s func:%s line:%d!!\n", file, func, line);\
	return CVEFAILED;\
	}\
	} while (0)
 
struct _hypercv_vector
{
	void *cv_pdata;
	size_t cv_len, cv_tot_len, cv_size;
};
 
hypercv_vector hypercv_vector_create(const size_t size)
{
	hypercv_vector cv = (hypercv_vector)malloc(sizeof (struct _hypercv_vector));
 
	if (!cv) return NULL;
 
	cv->cv_pdata = malloc(MIN_LEN * size);
 
	if (!cv->cv_pdata)
	{
		free(cv);
		return NULL;
	}
 
	cv->cv_size = size;
	cv->cv_tot_len = MIN_LEN;
	cv->cv_len = 0;
 
	return cv;
}  
 
void hypercv_vector_destroy(const hypercv_vector cv)  
{  
	free(cv->cv_pdata);  
	free(cv);  
	return;  
}  
 
size_t hypercv_vector_length(const hypercv_vector cv)  
{  
	return cv->cv_len;  
}  
 
int hypercv_vector_pushback(const hypercv_vector cv, void *memb)  
{  
	if (cv->cv_len >= cv->cv_tot_len)   
	{  
		void *pd_sav = cv->cv_pdata;  
		cv->cv_tot_len <<= EXPANED_VAL;  
		cv->cv_pdata = realloc(cv->cv_pdata, cv->cv_tot_len * cv->cv_size);  
 
		if (!cv->cv_pdata)   
		{  
			cv->cv_pdata = pd_sav;  
			cv->cv_tot_len >>= EXPANED_VAL;  
			return CVEPUSHBACK;  
		}  
	}  
 
	memcpy((char *)cv->cv_pdata + cv->cv_len * cv->cv_size, memb, cv->cv_size);  
	cv->cv_len++;  
 
	return CVESUCCESS;  
}  
 
int hypercv_vector_popback(const hypercv_vector cv, void *memb)  
{  
	if (cv->cv_len <= 0) return CVEPOPBACK;  
 
	cv->cv_len--;  
	memcpy(memb, (char *)cv->cv_pdata + cv->cv_len * cv->cv_size, cv->cv_size);  
 
	if ((cv->cv_tot_len >= (MIN_LEN << REDUSED_VAL))   
		&& (cv->cv_len <= (cv->cv_tot_len >> REDUSED_VAL)))   
	{  
		void *pd_sav = cv->cv_pdata;  
		cv->cv_tot_len >>= EXPANED_VAL;  
		cv->cv_pdata = realloc(cv->cv_pdata, cv->cv_tot_len * cv->cv_size);  
 
		if (!cv->cv_pdata)   
		{  
			cv->cv_tot_len <<= EXPANED_VAL;  
			cv->cv_pdata = pd_sav;  
			return CVEPOPBACK;  
		}  
	}  
 
	return CVESUCCESS;  
}  
 
size_t hypercv_vector_iter_at(const hypercv_vector cv, hypercv_iterator iter)  
{  
	CWARNING_ITER(cv, iter, __FILE__, __func__, __LINE__);  
	return ((char *)iter - (char *)cv->cv_pdata) / cv->cv_size;  
}  
 
int hypercv_vector_iter_val(const hypercv_vector cv, hypercv_iterator iter, void *memb)  
{  
	CWARNING_ITER(cv, iter, __FILE__, __func__, __LINE__);  
	memcpy(memb, iter, cv->cv_size);  
	return 0;  
}  
 
hypercv_iterator hypercv_vector_begin(const hypercv_vector cv)  
{  
	return cv->cv_pdata;  
}  
 
hypercv_iterator hypercv_vector_end(const hypercv_vector cv)  
{  
	return (char *)cv->cv_pdata + (cv->cv_size * cv->cv_len);  
}  
 
static inline void cvmemove_foreward(const hypercv_vector cv, void *from, void *to)  
{  
	size_t size = cv->cv_size;  
	char *p;  
	for (p = (char *)to; p >= (char *)from; p -= size) memcpy(p + size, p, size);  
	return;  
}  
 
static inline void cvmemove_backward(const hypercv_vector cv, void *from, void *to)  
{  
	memcpy(from, (char *)from + cv->cv_size, (char *)to - (char *)from);  
	return;  
}  
 
int hypercv_vector_insert(const hypercv_vector cv, hypercv_iterator iter, void *memb)  
{  
	CWARNING_ITER(cv, iter, __FILE__, __func__, __LINE__);  
 
	if (cv->cv_len >= cv->cv_tot_len)   
	{  
		void *pd_sav = cv->cv_pdata;  
		cv->cv_tot_len <<= EXPANED_VAL;  
		cv->cv_pdata = realloc(cv->cv_pdata, cv->cv_tot_len * cv->cv_size);  
 
		if (!cv->cv_pdata)   
		{  
			cv->cv_pdata = pd_sav;  
			cv->cv_tot_len >>= EXPANED_VAL;  
			return CVEINSERT;  
		}  
	}  
 
	cvmemove_foreward(cv, iter, (char *)cv->cv_pdata + cv->cv_len * cv->cv_size);  
	memcpy(iter, memb, cv->cv_size);  
	cv->cv_len++;  
 
	return CVESUCCESS;  
}  
 
int hypercv_vector_insert_at(const hypercv_vector cv, size_t index, void *memb)  
{  
	hypercv_iterator iter;  
 
	if (index >= cv->cv_tot_len)   
	{  
		cv->cv_len = index + 1;  
		while (cv->cv_len >= cv->cv_tot_len) cv->cv_tot_len <<= EXPANED_VAL;  
		cv->cv_pdata = realloc(cv->cv_pdata, cv->cv_tot_len * cv->cv_size);  
		iter = (char *)cv->cv_pdata + cv->cv_size * index;  
		memcpy(iter, memb, cv->cv_size);  
	}  
	else   
	{  
		iter = (char *)cv->cv_pdata + cv->cv_size * index;  
		hypercv_vector_insert(cv, iter, memb);  
	}  
 
	return 0;  
}  
 
hypercv_iterator hypercv_vector_next(const hypercv_vector cv, hypercv_iterator iter)  
{  
	return (char *)iter + cv->cv_size;  
}  
 
int hypercv_vector_val(const hypercv_vector cv, hypercv_iterator iter, void *memb)  
{  
	memcpy(memb, iter, cv->cv_size);  
	return 0;  
}  
 
int hypercv_vector_val_at(const hypercv_vector cv, size_t index, void *memb)  
{  
	memcpy(memb, (char *)cv->cv_pdata + index * cv->cv_size, cv->cv_size);  
	return 0;  
}  
 
int hypercv_vector_rm(const hypercv_vector cv, hypercv_iterator iter)  
{  
	hypercv_iterator from;  
	hypercv_iterator end;  
	CWARNING_ITER(cv, iter, __FILE__, __func__, __LINE__);  
	from = iter;  
	end = hypercv_vector_end(cv);  
	memcpy(from, (char *)from + cv->cv_size, (char *)end - (char *)from);  
	cv->cv_len--;  
 
	if ((cv->cv_tot_len >= (MIN_LEN << REDUSED_VAL))  
		&& (cv->cv_len <= (cv->cv_tot_len >> REDUSED_VAL)))   
	{  
		void *pd_sav = cv->cv_pdata;  
		cv->cv_tot_len >>= EXPANED_VAL;  
		cv->cv_pdata = realloc(cv->cv_pdata, cv->cv_tot_len * cv->cv_size);  
 
		if (!cv->cv_pdata)   
		{  
			cv->cv_tot_len <<= EXPANED_VAL;  
			cv->cv_pdata = pd_sav;  
			return CVERM;  
		}  
	}  
 
	return CVESUCCESS;  
}  
 
int hypercv_vector_rm_at(const hypercv_vector cv, size_t index)  
{  
	hypercv_iterator iter;  
	iter = (char *)cv->cv_pdata + cv->cv_size * index;  
	CWARNING_ITER(cv, iter, __FILE__, __func__, __LINE__);  
	return hypercv_vector_rm(cv, iter);  
}  
 
void cv_info(const hypercv_vector cv)  
{  
	printf("\n\ntot :%s : %d\n", __func__, (int)(cv->cv_tot_len));  
	printf("len :%s : %d\n",     __func__, (int)cv->cv_len);  
	printf("size:%s : %d\n\n",   __func__, (int)cv->cv_size);  
	return;  
}  
 
void cv_print(const hypercv_vector cv)  
{  
	int num;  
	hypercv_iterator iter;  
 
	if (hypercv_vector_length(cv) == 0)  
		fprintf(stderr, "file:%s func:%s line:%d error, null length hypercv_vector!!\n", __FILE__, __func__, __LINE__);  
 
	for (iter = hypercv_vector_begin(cv);   
		iter != hypercv_vector_end(cv);  
		iter = hypercv_vector_next(cv, iter))   
	{  
		hypercv_vector_iter_val(cv, iter, &num);  
		printf("var:%d at:%d\n", num,(int)hypercv_vector_iter_at(cv, iter));  
	}  
 
	return;  
}  

