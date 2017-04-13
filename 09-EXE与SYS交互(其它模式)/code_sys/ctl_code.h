#ifndef CTL_CODE
	#pragma message("---------\nEXE. Include winioctl.h\n--------- ")
	#include <WinIoCtl.h>
#else
	#pragma message("---------\nSYS. No Include winioctl.h\n---------  ")
#endif

#define add_code CTL_CODE(FILE_DEVICE_UNKNOWN, 	0x800, 	METHOD_NEITHER, FILE_ANY_ACCESS)
#define sub_code CTL_CODE(FILE_DEVICE_UNKNOWN, 	0x801, 	METHOD_NEITHER, FILE_ANY_ACCESS)
#define str_code CTL_CODE(FILE_DEVICE_UNKNOWN, 	0x802, 	METHOD_NEITHER, FILE_ANY_ACCESS)