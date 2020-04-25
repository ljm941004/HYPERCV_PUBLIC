/*************************************************************************
	> File Name: testmergeimage.cpp
	> Author: ljm
	> Mail: jimin@iscas.ac.cn 
	> Created Time: 2020年04月24日 星期五 16时25分39秒
 ************************************************************************/
#include "precomp.h"
#include <dirent.h>

using namespace std;


char** readFileList(char *basePath, int *i)
{
    DIR *dir;
    struct dirent *ptr;

	char** filename = (char**) malloc(sizeof(char*)*10000); 
    dir = opendir(basePath);
	_assert(dir != NULL,"Open dir error...");

	*i = 0;
    while ((ptr=readdir(dir)) != NULL)
    {
        if(strcmp(ptr->d_name,".")==0 || strcmp(ptr->d_name,"..")==0)
            continue;
        else 
		{
	        char* name = (char*) malloc(100);
			strcpy(name,basePath);
			strcat(name,"/");
			strcat(name,ptr->d_name);
			if(*i<10000)
			{
				filename[*i] = name;
				(*i)++;
			}
		}
		
	}
    closedir(dir);
    return filename;
}


static void test_hyper_mat_merge()
{

	char* file = "/home/ljm/test";
	int t =0;
	char** filename = readFileList(file,&t);

	hyper_mat mat = create_hyper_mat(2048, t , 256, 12,"bil");
	for (int i=0;i<t;i++)
	{
		printf("%s\n",filename[i]);
		hyper_mat tmp = hmread_with_size(filename[i],2048,1,256,12,"bil");
		hyper_mat_merge(mat,tmp,i*2048*256);
		delete_hyper_mat(tmp);
	}
	hmsave("test",mat);
}

TEST(PROCESS,MERGE)
{
	test_hyper_mat_merge();
}

