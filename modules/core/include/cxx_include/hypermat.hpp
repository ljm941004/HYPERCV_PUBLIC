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
			unsigned int dataType;
			char         interleave[3];      
			void*        data;
			float*       wavelength;

			int          elemSize;
			long int     dataSize;

			HyMat();

			HyMat(int _samples, int _lines, int _bands, int _dataType, const char* _interleave);
			HyMat(unsigned int _samples, unsigned int _lines, unsigned int _bands, unsigned int _dataType, const char* _interleave);

			HyMat(int _samples, int _lines, int _bands, int _dataType, const char* _interleave, void* _data);			

			HyMat(int _samples, int _lines, int _bands, int _dataType, const char* _interleave, void* _data, float* wavelength);

			void create(int _samples, int _lines, int _bands, int _dataType, const char* _interleave = "bsq");
			void create(int _samples, int _lines, int _bands, int _dataType, const char* _interleave, void* _data, float* wavelength= NULL);

            void CopyData(void* _data, long int _dataSize = 0);
	        void CopyWaveLength(float* _data, long int _bands = 0);
			
			void release();

			~HyMat()
			{

			}

	};

	inline HyMat::HyMat(){}

	inline HyMat::HyMat(int _samples, int _lines, int _bands, int _dataType, const char* _interleave)
	{
		create(_samples, _lines, _bands, _dataType, _interleave);
	}

	inline HyMat::HyMat(unsigned int _samples, unsigned int _lines, unsigned int _bands, unsigned int _dataType, const char* _interleave)
	{

		create(_samples, _lines, _bands, _dataType, _interleave);
	}

	inline HyMat::HyMat(int _samples, int _lines, int _bands, int _dataType, const char* _interleave, void* _data)			
	{
		create(_samples, _lines, _bands, _dataType, _interleave, _data, NULL);
	}

	inline HyMat::HyMat(int _samples, int _lines, int _bands, int _dataType, const char* _interleave, void* _data, float* _wavelength)
	{
		create(_samples, _lines, _bands, _dataType, _interleave, _data, _wavelength);
	}

	inline void HyMat::create(int _samples, int _lines, int _bands, int _dataType, const char* _interleave)
	{

		create(_samples, _lines, _bands, _dataType, _interleave, NULL, NULL);
	}

	inline void HyMat::create(int _samples, int _lines, int _bands, int _dataType, const char* _interleave, void* _data, float* _wavelength)
	{

		hypercv_assert(_samples > 0 && _lines > 0 && bands > 0, "HyMat size > 0");
		hypercv_assert(dataType == HYPERCV_UCHAR || 
				dataType == 2 ||
				dataType == 3 ||
				dataType == 4 ||
				dataType == 5 ||
				dataType == 12 ||
				dataType == 13 ||
				dataType == 14 ||
				dataType == 15 , " data type error");
		if(data)
			release();

		samples   = _samples;
		lines     = _lines;
		bands     = _bands;
		dataType  = _dataType;

		for(int i=0; i<3; i++)
			interleave[i] = _interleave[i];

		elemSize  = get_elemsize(dataType);
		dataSize  = samples * lines * bands * elemSize;

		if(_data)
			data = _data;
		else 
		{
			data = (void*)malloc(dataSize);
		    memset(data, 0, dataSize);
		}

		if(_wavelength)
			wavelength = _wavelength;
		else
		{
			wavelength = (float*)malloc(bands*sizeof(float));
			memset(wavelength, 0, bands*sizeof(float));
		}	

	}

	inline void HyMat::release()
	{
		if(data)
			free(data);
		if(wavelength)
			free(wavelength);

		data = NULL;
		samples = lines = bands = dataType = 0;

	}

	inline void HyMat::CopyData(void* _data, long int _dataSize)
	{
	    
		if(_dataSize == 0)
			_dataSize = dataSize;

		memcpy(data, _data, _dataSize);

	}

	inline void HyMat::CopyWaveLength(float* _data, long int _bands)
	{
		if(_bands == 0)
			_bands = bands;

		memcpy(wavelength, _data, _bands * sizeof(float));
	}
}


#endif 

#endif 
