/*************************************************************************
	> File Name: testsplicingimage.cpp
	> Author: ljm
	> Mail: jimin@iscas.ac.cn 
	> Created Time: 2020年04月24日 星期五 16时25分39秒
 ************************************************************************/
#include "precomp.h"
#include <dirent.h>

using namespace std;

struct dirent **name_list;

int readFileList(const char *basePath)
{
	int n = scandir(basePath, &name_list, 0, versionsort);
	return n;

}

static void test_hyper_mat_splicing()
{

	const char* file = "/home/ljm/tests";
	int t = readFileList(file);
	hyper_mat mat = create_hyper_mat(2048, t-2, 256, 12,"bil");
	
	for(int i=2;i<t;i++)
	{
		if(i>1)
		{
			char* name = (char*) malloc(100);
			strcpy(name,file);
			strcat(name,"/");
			strcat(name,name_list[i]->d_name);
			printf("%s\n",name);
			hyper_mat tmp = hmread_with_size(name,2048,1,256,12,"bil");	
			hyper_mat_splicing(mat,tmp,(i-2)*2048*256);	
			delete_hyper_mat(tmp);
			free(name);
			name = NULL;
		}
		free(name_list[i]);
	}
	hmsave("test",mat);
}

TEST(PROCESS,MERGE)
{
	test_hyper_mat_splicing();
	free(name_list);
}

