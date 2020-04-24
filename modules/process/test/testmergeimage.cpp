/*************************************************************************
	> File Name: testmergeimage.cpp
	> Author: ljm
	> Mail: jimin@iscas.ac.cn 
	> Created Time: 2020年04月24日 星期五 16时25分39秒
 ************************************************************************/
#include "precomp.h"
#include <dirent.h>

using namespace std;


char** readFileList(char *basePath)
{
    DIR *dir;
    struct dirent *ptr;

	char** filename = char*[10000];
    assert((dir=opendir(basePath))== NULL,"Open dir error...");

    while ((ptr=readdir(dir)) != NULL)
    {
        if(strcmp(ptr->d_name,".")==0 || strcmp(ptr->d_name,"..")==0)    ///current dir OR parrent dir
            continue;
        else if(ptr->d_type == 8)    ///file
            printf("d_name:%s/%s\n",basePath,ptr->d_name);
        else if(ptr->d_type == 10)    ///link file
            printf("d_name:%s/%s\n",basePath,ptr->d_name);
    }
    closedir(dir);
    return 1;
}


static void test_hyper_mat_merge()
{





}
