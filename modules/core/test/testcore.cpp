#include <iostream>
#include <gtest/gtest.h>

extern "C"
{
#include "core/core.h"
#include "process/process.h"
#include "core/test.h"
}
void test_delete_hyper_mat()
{
	const char* image_path = "IMAGE_20180914142522_0030.raw";
	const char* hdr_path = "IMAGE_20180914142522_0030.hdr";

	hyper_mat bil_mat = hmread(image_path,hdr_path);
	hyper_mat bsq_mat = bil2bsq(bil_mat);
	hyper_mat s = bsq2bip(bsq_mat);

	uintptr_t address = (uintptr_t)s;
	uintptr_t addrw = (uintptr_t)(s->data);

}

TEST(haha, hss)
{
    printf("haha\n");
    //test_delete_hyper_mat();
}

