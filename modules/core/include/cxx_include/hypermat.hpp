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
	extern void readHdr(const char* hdrPath, int& samples, int& lines, int& bands, int& dataType, int& format, float* wavelength);

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
			int          lines;
			int          samples;
			int          bands;
			int          dataType;
			int          format;
			//todo 修改所有format 改成 int format， HYPERCV_BIL HYPERCV_BIP HYPERCV_BSQ 

			char         interleave[3];
			void*        data;
			float*       wavelength;

			int          elemSize;
			long int     dataSize;

			HyMat();

			HyMat(int _samples, int _lines, int _bands, int _dataType, int _format);
			//HyMat(unsigned int _samples, unsigned int _lines, unsigned int _bands, unsigned int _dataType, int _format);

			HyMat(int _samples, int _lines, int _bands, int _dataType, int _format, void* _data);			

			HyMat(int _samples, int _lines, int _bands, int _dataType, int _format, void* _data, float* wavelength);

			void create();
			void create(int _samples, int _lines, int _bands, int _dataType, int _format = HYPERCV_BSQ);
			void create(int _samples, int _lines, int _bands, int _dataType, int _format, void* _data, float* wavelength= NULL);

			HyMat copy();
			void CopyData(void* _data, long int _dataSize = 0);
			void CopyWaveLength(float* _data, long int _bands = 0);

			int empty();

			void save(const char* filePath);
			void open(const char* imagePath, const char* hdrPath);
			void open(const char* path, int _samples, int _lines, int _bands, int _dataType, int _format);

			void convertTo(int _format);

			HyMat range(int startRow, int startCol, int startBand, int endRow, int endCol, int endBand);

			void release();

			~HyMat()
			{

			}
		private:

			void writeHdr(const char* filePath);

	};

	inline HyMat::HyMat()
	{
		create(0, 0, 0, HYPERCV_UCHAR, HYPERCV_BSQ);
	}

	inline HyMat::HyMat(int _samples, int _lines, int _bands, int _dataType, int _format)
	{
		create(_samples, _lines, _bands, _dataType, _format);
	}

	/*
	   inline HyMat::HyMat(unsigned int _samples, unsigned int _lines, unsigned int _bands, unsigned int _dataType, int _format)
	   {

	   create(_samples, _lines, _bands, _dataType, _format);
	   }
	   */
	inline HyMat::HyMat(int _samples, int _lines, int _bands, int _dataType, int _format, void* _data)			
	{
		create(_samples, _lines, _bands, _dataType, _format, _data, NULL);
	}

	inline HyMat::HyMat(int _samples, int _lines, int _bands, int _dataType, int _format, void* _data, float* _wavelength)
	{
		create(_samples, _lines, _bands, _dataType, _format, _data, _wavelength);
	}

	inline void HyMat::create(int _samples, int _lines, int _bands, int _dataType, int _format)
	{

		create(_samples, _lines, _bands, _dataType, _format, NULL, NULL);
	}

	inline void HyMat::create()
	{
		create(samples, lines, bands, dataType, format);
	}

	inline void HyMat::create(int _samples, int _lines, int _bands, int _dataType, int _format, void* _data, float* _wavelength)
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
		hypercv_assert(_format != HYPERCV_BIL || _format != HYPERCV_BIP || _format != HYPERCV_BSQ, "HyMat format must be bil bsq bip");

		if(data)
			release();

		samples   = _samples;
		lines     = _lines;
		bands     = _bands;
		dataType  = _dataType;

		format = _format;

		interleave[0] = 'b';

		switch(format)
		{
			case HYPERCV_BIL:
				interleave[1] = 'i';
				interleave[2] = 'l';
				break;
			case HYPERCV_BIP:
				interleave[1] = 'i';
				interleave[2] = 'p';
				break;
			default:
				interleave[1] = 's';
				interleave[2] = 'q';
				break;
		}

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

	inline HyMat HyMat::copy()
	{
		HyMat dst;

		if (empty() == 0)
		{
			dst.create(samples, lines, bands, dataType, format);
			dst.CopyData(data, dataSize);
			dst.CopyWaveLength(wavelength, bands);
		}

		return dst;
	}

	inline void HyMat::CopyData(void* _data, long int _dataSize)
	{
		if(_data == NULL)
			return;

		if(_dataSize == 0)
			_dataSize = dataSize;

		memcpy(data, _data, _dataSize);
	}

	inline void HyMat::CopyWaveLength(float* _data, long int _bands)
	{
		if(_data == NULL)
			return;

		if(_bands == 0)
			_bands = bands;

		memcpy(wavelength, _data, _bands * sizeof(float));
	}

	inline int HyMat::empty()
	{
		if(data == NULL || dataSize == 0)
			return 1;
		else 
			return 0;
	}

	inline void HyMat::save(const char* filePath)
	{
		if(filePath == NULL)
			return;

		if(samples == 0||lines == 0||bands == 0)
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

	inline void HyMat::open(const char* imagePath, const char* hdrPath)
	{
		if(imagePath == NULL || hdrPath == NULL)
		{
			printf("image path or hdr path can not be NULL\n");
			return;
		}

		if (empty() == 0)
			release();

		int _samples, _lines, _bands, _dataType;
		readHdr(hdrPath, _samples, _lines, _bands, _dataType, format, wavelength);

		samples = _samples;
		lines = _lines;
		bands = _bands;
		dataType = _dataType;

		create();

		FILE* _fp = NULL;
		_fp = fopen(imagePath, "r");

		if (_fp == NULL )
		{
			printf("can not open file\n");
			return ;
		}

		fread(data, elemSize, dataSize, _fp);
		fclose(_fp);
	}

	inline void HyMat::open(const char* path, int _samples, int _lines, int _bands, int _dataType, int _format)
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
		hypercv_assert(_format != HYPERCV_BIL || _format != HYPERCV_BIP || _format != HYPERCV_BSQ, "HyMat format must be bil bsq bip");

		if (empty() == 0)
			release();

		create(_samples, _lines, _bands, _dataType, _format);

		FILE* _fp = NULL;
		_fp = fopen(path ,"r");

		if (_fp == NULL )
		{
			printf("can not open file\n");
			return ;
		}

		fread(data, elemSize, dataSize, _fp);
		fclose(_fp);

	}

	inline void HyMat::convertTo(int _format)
	{
		hypercv_assert(_format != HYPERCV_BIL || _format != HYPERCV_BIP || _format != HYPERCV_BSQ, "HyMat format must be bil bsq bip");
		
		if(_format == format)
			return;

		char* srcData = (char*)data;
		char* dstData = (char*)malloc(dataSize);

		long int dstIndex, srcIndex; 

		for (int i=0;i<lines; i++)
		{
			for (int j=0;j<samples; j++)
			{
				for (int k=0; k<bands; k++)
				{
					if(format == HYPERCV_BIL && _format == HYPERCV_BIP)
					{
						srcIndex = (i*samples*bands + k*samples + j)*elemSize;
					    dstIndex = (i*samples*bands + j*bands + k)*elemSize;
					}
					else if(format == HYPERCV_BIL && _format == HYPERCV_BSQ)
					{
						srcIndex = (i*samples*bands + k*samples + j)*elemSize;
						dstIndex = (k*samples*lines + i*samples + j)*elemSize;
					}
					else if(format == HYPERCV_BSQ && _format == HYPERCV_BIL)
					{
						dstIndex = (i*samples*bands + k*samples + j)*elemSize;
						srcIndex = (k*samples*lines + i*samples + j)*elemSize;
					}
					else if(format == HYPERCV_BSQ && _format == HYPERCV_BIP)
					{
						dstIndex = (i*samples*bands + j*bands + k)*elemSize;
						srcIndex = (k*samples*lines + i*samples + j)*elemSize;
					}
					else if(format == HYPERCV_BIP && _format == HYPERCV_BSQ)
					{
						srcIndex = (i*samples*bands + j*bands + k)*elemSize;
						dstIndex = (k*samples*lines + i*samples + j)*elemSize;
					}
					else if(format == HYPERCV_BIP && _format == HYPERCV_BIL)
					{
						srcIndex = (i*samples*bands + j*bands + k)*elemSize;
						dstIndex = (i*samples*bands + k*samples + j)*elemSize;
					}

					for (int t=0; t<elemSize; t++)
						dstData[dstIndex + t] = srcData[srcIndex + t];
				}
			}
		}

		this->CopyData(dstData, dataSize);
		free(dstData);

		format = _format;

		if(_format == HYPERCV_BIL)
		{
			interleave[0] = 'b';
		    interleave[1] = 'i';
			interleave[2] = 'l';
		}
		else if(_format == HYPERCV_BIP)
		{
			interleave[0] = 'b';
		    interleave[1] = 'i';
			interleave[2] = 'p';
		}
		else if(_format == HYPERCV_BSQ)
		{
			interleave[0] = 'b';
		    interleave[1] = 's';
			interleave[2] = 'q';
		}
	}


	inline void HyMat::release()
	{
		if(data)
			free(data);
		if(wavelength)
			free(wavelength);

		data = NULL;
		wavelength = NULL;
		samples = lines = bands = dataType = 0;

	}

	inline HyMat hmread(const char* imagePath, const char* hdrPath)
	{
		HyMat mat;

		if(imagePath == NULL || hdrPath == NULL)
			printf("image path or hdr path can not be NULL\n");
		else
			mat.open(imagePath, hdrPath);

		return mat;
	}

	inline HyMat hmread(const char* path, int _samples, int _lines, int _bands, int _dataType, int _format)
	{
		HyMat mat;
		mat.open(path, _samples, _lines, _bands, _dataType, _format);	
		return mat;
	}


	inline HyMat HyMat::range(int startRow, int startCol, int startBand, int endRow, int endCol, int endBand)
	{
		hypercv_assert(startCol<endCol && startRow<endRow && startBand<endBand, "start col & start row & start band must < end col & end row & end band");

		int newSamples = endCol - startCol;
		int newLines = endRow - startRow;
		int newBands = endBand - startBand;

		HyMat dst{newSamples, newLines, newBands, dataType, format};

		char* srcData = (char*)data;
		char* dstData = (char*)dst.data;

		int srcIndex =0, dstIndex =0;

		switch(format)
		{
			case HYPERCV_BIL:
				{
					for (int i = startRow; i < endRow; i++)
					{
						for (int k = startBand; k < endBand; k++)
						{
							for (int j = startCol; j < endCol; j++)
							{
								srcIndex = (i * samples * bands + k * samples + j) * elemSize;
								dstIndex = ((i - startRow) * newSamples * newBands + (k - startBand) * newSamples + j - startCol) * elemSize;

								for (int t = 0; t < elemSize; t++)
									dstData[dstIndex + t] = srcData[srcIndex + t];					
							}
						}
					}

				}
				break;
			case HYPERCV_BIP:
				{
					for (int i = startRow; i < endRow; i++)
					{
						for (int j = startCol; j < endCol; j++)
						{
							for (int k = startBand; k < endBand; k++)
							{
								srcIndex = (i * samples * bands + j * bands + k) * elemSize;
								dstIndex = ((i - startRow) * newSamples * newBands + (j - startCol) * newBands + k - startBand) * elemSize;

								for (int t = 0; t < elemSize; t++)
									dstData[dstIndex + t] = srcData[srcIndex + t];					
							}
						}
					}
				}
				break;
			case HYPERCV_BSQ:
				{
					for (int k = startBand; k < endBand; k++)
					{
						for (int i = startRow; i < endRow; i++)
						{
							for (int j = startCol; j < endCol; j++)
							{
								srcIndex = (k * samples * lines + i * samples + j) * elemSize;
								dstIndex = ((k - startBand) * newSamples * newLines + (i - startRow) * newSamples + j - startCol) * elemSize;

								for (int t = 0; t < elemSize; t++)
									dstData[dstIndex + t] = srcData[srcIndex + t];					
							}
						}
					}

				}
				break;
		}

		dst.CopyWaveLength(wavelength + startBand, newBands);

		return dst;
	}

	extern HyMat bil2bsq(HyMat &mat);

	extern HyMat bil2bip(HyMat &mat);

	extern HyMat bip2bil(HyMat &mat);

	extern HyMat bip2bsq(HyMat &mat);

	extern HyMat bsq2bip(HyMat &mat);

	extern HyMat bsq2bil(HyMat &mat);

}

#endif 

#endif 
