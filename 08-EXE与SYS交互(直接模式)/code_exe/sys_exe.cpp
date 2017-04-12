#include <iostream>
#include <Windows.h>
#include <WinIoCtl.h>
#include "ctl_code.h"
using namespace std; 

int add(HANDLE hDevice ,int a, int b) {
	int port[2];
	int buffret;
	ULONG dwWrite;
	port[0] = a;
	port[1] = b;
	::DeviceIoControl(hDevice, add_code , &port, 8, &buffret, 4, &dwWrite, NULL);
	return buffret;
}

int sub(HANDLE hDevice ,int a, int b) {
	int port[2];
	int buffret;
	ULONG dwWrite;
	port[0] = a;
	port[1] = b;
	::DeviceIoControl(hDevice, sub_code , &port, 8, &buffret, 4, &dwWrite, NULL);
	return buffret;
}

int main() {
	HANDLE hDevice = ::CreateFile("\\\\.\\MySysLinkName_20170411", 
															GENERIC_READ | GENERIC_WRITE,
															0,
															NULL,
															OPEN_EXISTING,
															FILE_ATTRIBUTE_NORMAL,
															NULL );
	printf("开始\n");

	if (hDevice == INVALID_HANDLE_VALUE) {
		printf("获取驱动句柄失败: %s with Win32 error code: %d\n","MyDriver", GetLastError() );
		getchar();
		return -1;
	}
	 
	printf("输入:a, b:\n");
	int a, b;
	scanf("%d%d", &a, &b);
	int r1 = add(hDevice, a, b);
	printf("%d+%d=%d\n",a, b, r1);

	int r2 = sub(hDevice, a, b);
	printf("%d-%d=%d\n",a, b, r2);
	getchar();
	getchar();
	return 0;
}