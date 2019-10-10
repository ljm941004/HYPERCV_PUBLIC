/*************************************************************************
	> File Name: savesm.h
	> Author: ljm
	> Mail: jimin@iscas.ac.cn
 ************************************************************************/
typedef struct FileHeader
{
	unsigned short	bfType;
	unsigned int	bfSize;
	unsigned short	bfReserved1;
	unsigned short	bfReserved2;
	unsigned int	bfOffBits;
}__attribute__((packed))FileHeader;
 
/*bmp info header*/
typedef struct InfoHeader
{
	unsigned int	biSize;
	int				biWidth;
	int				biHeight;
	unsigned short	biPlanes;
	unsigned short	biBitCount;
	unsigned int	biCompression;
	unsigned int	biSizeImage;
	int				biXPelsPerMeter;
	int 			biYPelsPerMeter;
	unsigned int	biClrUsed;
	unsigned int	biClrImportant;
}__attribute__((packed))InfoHeader;
 
//we won't use it while BitCount=24
typedef struct tagRGBQUAD
{
	unsigned char	rgbBlue;
	unsigned char	rgbGreen;
	unsigned char	rgbRed;
	unsigned char	rgbReserved;
}RGBQUAD;
	
typedef struct
{
	unsigned char b;
	unsigned char g;
	unsigned char r;
}RGB_data;


simple_mat bmp2sm(char *bmpName, RGBQUAD *pColorTable);
int sm2bmp(char *bmpName, simple_mat src_mat, RGBQUAD *pColorTable);
