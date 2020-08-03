/*************************************************************************
	> File Name: core/src/hypermat.cpp
	> Author: ljm
	> Mail: jimin@iscas.ac.cn 
	> Created Time: 2020年06月20日 星期六 10时57分55秒
 ************************************************************************/
#ifdef _cplusplus


#include "precomp.hpp"

namespace hypercv
{

#if gdal_switch

	GDALDataType dataType2GDALDataType(const int data_type)
	{
		switch (data_type)
		{
			case 1:
				return GDT_Byte;
				break;
			case 2:
				return GDT_Int16;
				break;
			case 3:
				return GDT_Int32;
				break;
			case 4:
				return GDT_Float32;
				break;
			case 5:
				return GDT_Float64;
				break;
			case 12:
				return GDT_UInt16;
				break;
			case 13:
				return GDT_UInt32;
				break;
		}
		return GDT_Unknown;

	}
#endif

	void readHdr(const char* hdrPath, int& samples, int& lines, int& bands,  int& dataType, int& format, float* wavelength)
	{
		if(hdrPath == NULL)
			return;

		std::ifstream file;
		file.open(hdrPath,ios::in);

		if(!file.is_open())
			return;

		string lineBuff;


		while (getline(file,lineBuff))
		{  
			const char* line = lineBuff.c_str();
			char item[20];
			sscanf(line, "%[^=]", item);

			if (cmpstr(item, (char*)"samples") == 1)
				sscanf(line, "%*[^=]=%d",&samples);

			else if (cmpstr(item, (char*)"lines") == 1)
				sscanf(line, "%*[^=]=%d",&lines);

			else if (cmpstr(item, (char*)"bands") == 1)
				sscanf(line, "%*[^=]=%d", &bands);

			else if (cmpstr(item, (char*)"data") == 1)
				sscanf(line, "%*[^=]=%d", &dataType);

			else if (lineBuff.find("interleave")!=lineBuff.npos)
			{
				if(lineBuff.find("q")!=lineBuff.npos)
					format = HYPERCV_BSQ;
				else if(lineBuff.find("p")!=lineBuff.npos)
					format = HYPERCV_BIP;
				else 
					format = HYPERCV_BIL;
			}
			else if (lineBuff.find("wavelength = {")!=lineBuff.npos)
			{	
				string waveBuff, s;
				stringstream ss;
				do
				{
					int startIndex, endIndex;

					startIndex = lineBuff.find('{')==lineBuff.npos?0:lineBuff.find('{')+1;
					endIndex = lineBuff.find('}')==lineBuff.npos?lineBuff.size():lineBuff.find('}');
					waveBuff += lineBuff.substr(startIndex,endIndex);
				}
				while(lineBuff.find('}')==lineBuff.npos&&getline(file,lineBuff));
				ss<<waveBuff;
				for(int i=0;i<bands;i++)
				{
					ss>>s;
					wavelength[i] = atof(s.c_str());
				}

			}
		}

		file.close();
	}

	/**
	 * @brief      transform bil to bsq.
	 * @param[in]  bil_mat    bil image.
	 * @retval     bsq_mat    bsq image.
	 **/
	HyMat bil2bsq(HyMat &mat)
	{
		hypercv_assert(mat.empty() == 0,"mat can not be empty");
		hypercv_assert(mat.format == HYPERCV_BIL, "format must be bil");
		
		HyMat dst{mat.samples, mat.lines, mat.bands, mat.dataType, HYPERCV_BSQ};

		int samples = mat.samples;
		int lines = mat.lines;
		int bands = mat.bands;
		int elemSize = mat.elemSize;

		char* matData = (char*)mat.data;
		char* dstData = (char*)dst.data;

		long int bilIndex = 0, bsqIndex = 0;

		for (int k=0; k<bands; k++)
		{
			for (int i=0; i<lines; i++)
			{
				for (int j=0; j<samples; j++)
				{
					bilIndex = (i*samples*bands + k*samples + j)*elemSize;
					bsqIndex = (k*samples*lines + i*samples + j)*elemSize;

					for (int t=0; t<elemSize; t++)
						dstData[bsqIndex + t] = matData[bilIndex + t];
				}
			}
		}

		dst.CopyWaveLength(mat.wavelength, bands);
		return dst;
	}

	/**
	 * @brief      transform bil to bip.
	 * @param[in]  bil_mat    bil image.
	 * @retval     bip_mat    bip image. 
	 **/
	HyMat bil2bip(HyMat &mat)
	{
		hypercv_assert(mat.empty() == 0,"mat can not be empty");
		hypercv_assert(mat.format == HYPERCV_BIL, "format must be bil");
		
		HyMat dst{mat.samples, mat.lines, mat.bands, mat.dataType, HYPERCV_BIP};

		int samples = mat.samples;
		int lines = mat.lines;
		int bands = mat.bands;
		int elemSize = mat.elemSize;

		char* matData = (char*)mat.data;
		char* dstData = (char*)dst.data;

		long int bilIndex = 0, bipIndex = 0;

		for (int i=0;i<lines; i++)
		{
			for (int j=0;j<samples; j++)
			{
				for (int k=0; k<bands; k++)
				{
					bilIndex = (i*samples*bands + k*samples + j)*elemSize;
					bipIndex = (i*samples*bands + j*bands + k)*elemSize;

					for (int t=0; t<elemSize; t++)
						dstData[bipIndex + t] = matData[bilIndex + t];
				}
			}
		}

		dst.CopyWaveLength(mat.wavelength, bands);
		return dst;
	}
	/**
	 * @brief      transform bsq to bil.
	 * @param[in]  mat    bsq image.
	 * @retval     bip_mat    bil image. 
	 **/
	HyMat bsq2bil(HyMat &mat)
	{
		if(mat.format == HYPERCV_BIL)
			return mat.copy();

		hypercv_assert(mat.format == HYPERCV_BSQ, "input hyper mat's interleave must be bsq");

		int samples   = mat.samples;
		int lines     = mat.lines;
		int bands     = mat.bands;
		int elemSize  = mat.elemSize;

		HyMat dst{samples, lines, bands, mat.dataType, HYPERCV_BIL};

		char* matData = (char*)mat.data;
		char* dstData = (char*)dst.data;

		long int bsqIndex = 0, bilIndex = 0;

		for (int i=0;i<lines; i++)
		{
			for (int k=0; k<bands; k++)
			{
				for (int j=0;j<samples; j++)
				{
					bsqIndex = (k*samples*lines + i*samples + j)*elemSize;
					bilIndex = (i*samples*bands + k*samples + j)*elemSize;

					for (int t=0; t<elemSize; t++)
						dstData[bilIndex + t] = matData[bsqIndex + t];
				}
			}
		}

		dst.CopyWaveLength(mat.wavelength, bands);

		return dst;
	}

	/**
	 * @brief      transform bsq to bip.
	 * @param[in]  bil_mat    bsq image.
	 * @retval     bip_mat    bip image. 
	 **/
	HyMat bsq2bip(HyMat &mat)
	{
		if(mat.format == HYPERCV_BIP)
			return mat.copy();

		hypercv_assert(mat.format == HYPERCV_BSQ, "input hyper mat's interleave must be bsq");

		int samples   = mat.samples;
		int lines     = mat.lines;
		int bands     = mat.bands;
		int elemSize  = mat.elemSize;

		HyMat dst{samples, lines, bands, mat.dataType, HYPERCV_BIP};

		char* matData = (char*)mat.data;
		char* dstData = (char*)dst.data;

	    long int bsqIndex = 0, bipIndex = 0;

		for (int i=0;i<lines; i++)
		{
			for (int j=0;j<samples; j++)
			{
				for (int k=0; k<bands; k++)
				{
					bsqIndex = (k*samples*lines + i*samples + j)*elemSize;
				    bipIndex = (i*samples*bands + j*bands + k)*elemSize;

					for (int t=0; t<elemSize; t++)
						dstData[bipIndex + t] = matData[bsqIndex + t];
				}
			}
		}

		dst.CopyWaveLength(mat.wavelength, bands);
		return dst;
	}

	/**
	 * @brief      transform bip to bsp.
	 * @param[in]  bil_mat    bip image.
	 * @retval     bip_mat    bsq image. 
	 **/
	HyMat bip2bsq(HyMat &mat)
	{
		if(mat.format == HYPERCV_BSQ)
			return mat.copy();

        hypercv_assert(mat.format == HYPERCV_BIP, "input hyper mat's interleave must be bip");

		int samples   = mat.samples;
		int lines     = mat.lines;
		int bands     = mat.bands;
		int elemSize  = mat.elemSize;

		HyMat dst{samples, lines, bands, mat.dataType, HYPERCV_BSQ};

		char* matData = (char*)mat.data;
		char* dstData = (char*)dst.data;

	    long int bsqIndex = 0, bipIndex = 0;

		for (int i=0;i<lines; i++)
		{
			for (int j=0;j<samples; j++)
			{
				for (int k=0; k<bands; k++)
				{
			        bsqIndex = (k*samples*lines + i*samples + j)*elemSize;
					bipIndex = (i*samples*bands + j*bands + k)*elemSize;

					for (int t=0; t<elemSize; t++)
						dstData[bsqIndex + t] = matData[bipIndex + t];
				}
			}
		}

		dst.CopyWaveLength(mat.wavelength, bands);
		return dst;
	}

	/**
	 * @brief      transform bip to bil .
	 * @param[in]  bip_mat    bip image.
	 * @retval     bil_mat    bil image. 
	 **/
	HyMat bip2bil(HyMat &mat)
	{
		if(mat.format == HYPERCV_BIL)
			return mat.copy();

        hypercv_assert(mat.format == HYPERCV_BIP, "input hyper mat's interleave must be bip");

		int samples   = mat.samples;
		int lines     = mat.lines;
		int bands     = mat.bands;
		int elemSize  = mat.elemSize;

		HyMat dst{samples, lines, bands, mat.dataType, HYPERCV_BIL};

		char* matData = (char*)mat.data;
		char* dstData = (char*)dst.data;

	    long int bilIndex = 0, bipIndex = 0;

		for (int i=0;i<lines; i++)
		{
			for (int j=0;j<samples; j++)
			{
				for (int k=0; k<bands; k++)
				{
					bilIndex = (i*samples*bands + k*samples + j)*elemSize;
				    bipIndex = (i*samples*bands + j*bands + k)*elemSize;

					for (int t=0; t<elemSize; t++)
						dstData[bilIndex + t] = matData[bipIndex + t];
				}
			}
		}

		dst.CopyWaveLength(mat.wavelength, bands);
		return dst;
	}
}

#endif

