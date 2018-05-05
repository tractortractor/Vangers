#include "xglobal.h"

#ifndef _WIN32
#include <stdlib.h>
#endif

XStream& XStream::operator<= (char var)
{
	char* s = port_itoa(var,_ConvertBuffer,radix);
	write(s,strlen(s));
	return *this;
}

XStream& XStream::operator<= (unsigned char var)
{
	char* s = port_itoa(var,_ConvertBuffer,radix);
	write(s,strlen(s));
	return *this;
}

XStream& XStream::operator<= (short var)
{
	char* s = port_itoa(var,_ConvertBuffer,radix);
	write(s,strlen(s));
	return *this;
}

XStream& XStream::operator<= (unsigned short var)
{
	char* s = port_ltoa(var,_ConvertBuffer,radix);
	write(s,strlen(s));
	return *this;
}

XStream& XStream::operator<= (int var)
{
	char* s = port_itoa(var,_ConvertBuffer,radix);
	write(s,strlen(s));
	return *this;
}

XStream& XStream::operator<= (unsigned var)
{
	char* s = port_ultoa(var,_ConvertBuffer,radix);
	write(s,strlen(s));
	return *this;
}

XStream& XStream::operator<= (long var)
{
	char* s = port_ltoa(var,_ConvertBuffer,radix);
	write(s,strlen(s));
	return *this;
}

XStream& XStream::operator<= (unsigned long var)
{
	char* s = port_ultoa(var,_ConvertBuffer,radix);
	write(s,strlen(s));
	return *this;
}

XStream& XStream::operator<= (float var)
{
	int len = snprintf(_ConvertBuffer, _CONV_BUFFER_LEN, "%.*g", digits, var);
	write(_ConvertBuffer,len);
	return *this;
}

XStream& XStream::operator<= (double var)
{
	int len = snprintf(_ConvertBuffer, _CONV_BUFFER_LEN, "%.*g", digits, var);
	write(_ConvertBuffer,len);
	return *this;
}

XStream& XStream::operator<= (long double var)
{
	int len = snprintf(_ConvertBuffer, _CONV_BUFFER_LEN, "%.*Lg", digits, var);
	write(_ConvertBuffer,len);
	return *this;
}

// tractortractor's added begin
#if defined(_MSC_VER) && defined(_WIN64)
XStream& XStream::operator<= (std::size_t v)
{
	int len = std::snprintf(_ConvertBuffer, _CONV_BUFFER_LEN, XSTREAM_SIZE_T_C_PRINTF_FORMAT, v);
	write(_ConvertBuffer,len);
	return *this;
}
#endif
// tractortractor's added end
