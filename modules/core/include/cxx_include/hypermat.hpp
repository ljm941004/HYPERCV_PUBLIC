#ifndef HYPERCV_CORE_HYPERMAT_HPP
#define HYPERCV_CORE_HYPERMAT_HPP

#ifdef _cplusplus

#include "type.hpp"

#if gdal_switch 
#include "gdal_priv.h"
#include "cpl_conv.h"
#endif 

namespace hypercv
{

	extern void readHdr(const char* hdrPath, int& samples, int& lines, int& bands, int& dataType, char* interleave, float* wavelength);

#if gdal_switch
#ifndef DATA_TYPE_2_GDAL_DATA_TYPE
#define DATA_TYPE_2_GDAL_DATA_TYPE
	extern GDALDataType dataType2GDALDataType(const int data_type);
#endif
#endif

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

			void create();
			void create(int _samples, int _lines, int _bands, int _dataType, const char* _interleave = "bsq");
			void create(int _samples, int _lines, int _bands, int _dataType, const char* _interleave, void* _data, float* wavelength= NULL);

			void CopyData(void* _data, long int _dataSize = 0);
			void CopyWaveLength(float* _data, long int _bands = 0);

			void save(const char* filePath);
	        void hmread(const char* imagePath, const char* hdrPath);

			void release();

			~HyMat()
			{

			}
		private:

			void writeHdr(const char* filePath);

	};

	inline HyMat::HyMat()
	{
		create(0, 0, 0, HYPERCV_UCHAR, NULL);
	}

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

	inline void HyMat::create()
	{
		create(samples, lines, bands, dataType, interleave);
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

	inline void HyMat::save(const char* filePath)
	{
		if(filePath == NULL)
			return;

		if(samples == 0||lines == 0||bands == 0||interleave == NULL)
		{
			std::cout<<"mat size error";
			return;
		}

		//#if gdal_switch 
		GDALAllRegister();
		GDALDataset *dataSet;
		GDALDriver *hDriver = GetGDALDriverManager()->GetDriverByName("ENVI");	
		GDALDataType DT = dataType2GDALDataType(dataType);

		char** papszOptions = NULL;
		dataSet = hDriver->Create(filePath, samples, lines, bands, DT, papszOptions);

		//	dataSet->RasterIO(GF_Write, 0, 0, samples, lines, data, DT, )
		//todo	
		//#endif 

		FILE* _fp;
		_fp = fopen(filePath, "wb");
	    if(_fp == NULL)
		{
			return;
			printf("can not open files\n");
		}
		fwrite(data, elemSize, samples * lines * bands, _fp);
		this->writeHdr(filePath);
		fclose(_fp);

	}

	inline void HyMat::writeHdr(const char* filePath)
	{
		std::string path(filePath);
		path = path.substr(0, path.find('.')) + "hdr";

		FILE *fp;
		fp = fopen(path.c_str(), "w");

		fputs("ENVI\n", fp);
		fputs("samples = ", fp); fprintf(fp, "%d\n", samples);
		fputs("lines = ", fp); fprintf(fp, "%d\n", lines);
		fputs("bands = ", fp); fprintf(fp, "%d\n", bands);
		fputs("data type = ", fp); fprintf(fp, "%d\n", dataType);

		fputs("interleave = ", fp); fprintf(fp, "%c%c%c\n", interleave[0], interleave[1], interleave[2]);

		if(wavelength != NULL)
		{
			fputs("wavelength = { \n", fp); 
			for(int i=0; i<bands-1; i++)
				fprintf(fp,"%f,",wavelength[i]);
			fprintf(fp,"%f}",wavelength[bands-1]);
		}
		else 
		{
			fputs("wavelength = unknown \n",fp);
		}
		fclose(fp);
	}

	inline void HyMat::hmread(const char* imagePath, const char* hdrPath)
	{
		if(imagePath == NULL || hdrPath == NULL)
		{
			printf("image path or hdr path can not be NULL\n");
			return;
		}

		int _samples, _lines, _bands, _dataType;
		readHdr(hdrPath, _samples, _lines, _bands, _dataType, interleave, wavelength);

		samples = _samples;
		lines = _lines;
		bands = _bands;
		dataType = _dataType;

		FILE* _fp = NULL;
		_fp = fopen(imagePath, "r");

		if (_fp == NULL )
		{
			printf("can not open file\n");
			return ;
		}

		create();
		fread(data, elemSize, dataSize, _fp);
		fclose(_fp);
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

	inline HyMat hmread(const char* imagePath, const char* hdrPath)
	{
		HyMat mat;
		
		if(imagePath == NULL || hdrPath == NULL)
			printf("image path or hdr path can not be NULL\n");
		else
			mat.hmread(imagePath, hdrPath);
		
		return mat;
	}

}



#endif 

#endif 
