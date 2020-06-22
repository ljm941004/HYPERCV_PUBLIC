#ifndef HYPERCV_CORE_HYPERMAT_HPP
#define HYPERCV_CORE_HYPERMAT_HPP

#ifndef _cplusplus


namespace hypercv
{

	class HyMat
	{
		public:
			/* 
			 * HYPER_MAT 
			 * */
			unsigned int lines;
			unsigned int samples;
			unsigned int bands;
			unsigned int data_type;
			char         interleave[3];      
			void*        data;
			float*       wavelength;

			HyMat();

			HyMat(int _samples, int _lines, int _bands, int _data_type, const char* _interleave);
			HyMat(unsigned int _samples, unsigned int _lines, unsigned int _bands, unsigned int _data_type, const char* _interleave);

			HyMat(int _samples, int _lines, int _bands, int _data_type, const char* _interleave, void* _data);			

			void create(int _samples, int _lines, int _bands, int _data_type, const char* _interleave = "bsq");
			void create(int _samples, int _lines, int _bands, int _data_type, const char* _interleave, void* _data, float* wavelength= NULL);

			void release();


	};


	inline HyMat::HyMat(){}

	inline HyMat::HyMat(int _samples, int _lines, int _bands, int _data_type, const char* _interleave)
	{
		hypercv_assert(_samples > 0 && _lines > 0 && bands > 0, "HyMat size > 0");
		create(_samples, _lines, _bands, _data_type, _interleave);
	}

	inline void HyMat::create(int _samples, int _lines, int _bands, int _data_type, const char* _interleave)
	{
		samples   = _samples;
		lines     = _lines;
		bands     = _bands;
		data_type = _data_type;
	
		for(int i=0; i<3; i++)
			interleave[i] = _interleave[i];
		if(data)
			release();

		int elemsize  = get_elemsize(data_type);
		long int data_size = samples*lines*bands*elemsize;
		data = (void*)malloc(data_size);
		wavelength = (float*)(bands*sizeof(float));
	}

	inline void HyMat::create(int _samples, int _lines, int _bands, int _data_type, const char* _interleave, void* data, float* wavelength)
	{
		//todo
	}

	inline void HyMat::release()
	{
		if(data)
			free(data);
		if(wavelength)
			free(wavelength);

		data = NULL;
		samples = lines = bands = 0;
	}
}


#endif 

#endif 
