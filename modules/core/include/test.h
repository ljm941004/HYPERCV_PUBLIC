

// ********************************* private function only in test ************************************* 
inline void compare_2_mat(hyper_mat src_mat, hyper_mat dst_mat)
{
	if (src_mat->samples != dst_mat -> samples || src_mat -> lines != dst_mat ->lines || src_mat -> bands != dst_mat -> bands || src_mat->data_type != dst_mat ->data_type)
	{
		printf("un equal");
		return;
	}

	int elem_size = get_elem_size(src_mat->data_type);
	int sum = src_mat->samples*src_mat->lines*src_mat->bands*elem_size;

	char*src_data = (char*)src_mat->data;
	char*dst_data = (char*)dst_mat->data;

	for (int i=0;i<sum;i++)
	{
		if (src_data[i]!=dst_data[i])
		{
			printf("un equal");
			return;
		}
	}
	printf("ok");
}


void test_bi12bsq();
void test_hypermat_get_range();
void test_delete_hyper_mat();