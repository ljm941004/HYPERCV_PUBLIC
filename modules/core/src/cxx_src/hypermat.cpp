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


    void readHdr(const char* hdrPath, int& samples, int& lines, int& bands, int& dataType, char* interleave, float* wavelength)
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

			else if (cmpstr(item, (char*)"interleave") == 1)
				sscanf(line, "%*[^=]=%s",interleave);

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
	}


}

#endif

