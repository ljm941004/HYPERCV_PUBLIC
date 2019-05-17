//* @param[in]  data_type   data_type of hyper spectral image, data type 1: Byte (8 bits) 2: Integer (16 bits) 3: Long integer (32 bits) 4: Floating-point (32 bits) 5: Double-precision floating-point (64 bits) 6: Complex (2x32 bits) 9: Double-precision complex (2x64 bits) 12: Unsigned integer (16 bits) 13: Unsigned long integer (32 bits) 14: Long 64-bit integer 15: Unsigned long 64-bit integer.

#define ALLOC_BYTE_ALIGNMENT 64

#define BYTE_ALIGNMENT(address, alignment) \
{ \
	(address) = (((address) + ((alignment) - 1)) & (-alignment)); \
}

inline int get_elem_size(const int data_type)
{
	switch (data_type)
	{
	case 1:
			  return sizeof(char);
		break;
	case 2:
			  return sizeof(short);
		break;
	case 3:
			  return sizeof(int);
		break;
	case 4:
			  return sizeof(float);
		break;
	case 5:
			  return sizeof(double);
		break;
	case 12:
			  return sizeof(unsigned short);
		break;
	case 13:
			  return sizeof(unsigned int);
		break;
	case 14:
			  return sizeof(long int);
		break;
	case 15:
			  return sizeof(unsigned long int);
		break;
	}
	return -1;
}