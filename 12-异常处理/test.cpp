#pragma once
#ifdef __cplusplus
	extern "C" {
#endif
	#include <ntddk.h>
#ifdef __cplusplus
	}
#endif
#define INITCODE code_seg("INIT")

void Memaccess_Test() {
	int i=3, *pi=NULL;
	bool isOk = true;
	KdPrint(("================\n"));
	KdPrint(("测试*NULL=3;是否会发生异常\n"));
	__try {
		*pi=i;
	} __except(1) {
		KdPrint(("发生了异常\n"));
		isOk = false;
	}
	if (isOk) {
		KdPrint(("没发现异常\n"));
	}
	KdPrint(("================\n"));
}

void ProbeForRead_Test() {
	int *pi=NULL;
	bool isOk = true;
	KdPrint(("================\n"));
	KdPrint(("使用ProbeForRead(NULL,14,4);测试内存是否可读\n"));
	__try {
		ProbeForRead(pi,14,4);
	} __except(EXCEPTION_EXECUTE_HANDLER) {
		KdPrint(("发生了异常\n"));
		isOk = false;
	}
	if (isOk) {
		KdPrint(("没发现异常\n"));
	}
	KdPrint(("================\n"));
}

void ProbeForWrite_Test() {
	int *pi=NULL;
	bool isOk = true;
	KdPrint(("================\n"));
	KdPrint(("使用ProbeForWrite(NULL,14,4);测试内存是否可写\n"));
	__try {
		ProbeForWrite(pi,4,1);
	} __except(EXCEPTION_EXECUTE_HANDLER) {
		KdPrint(("发生了异常\n"));
		isOk = false;
	}
	if (isOk) {
		KdPrint(("没发现异常\n"));
	}
	KdPrint(("================\n"));
}

void finally_test() {
	int *pi=NULL;
	bool isOk = true;
	KdPrint(("================\n"));
	KdPrint(("测试*NULL=3;是否会发生异常\n"));
	__try {	
		__try {		//__finally和__except好像不能放在一起，不是C标准函数
			*pi = 3;
		} __finally {
			KdPrint(("__finally结束处理部分\n"));
		}
	} __except(EXCEPTION_EXECUTE_HANDLER) {
		KdPrint(("发生了异常\n"));
		isOk = false;
	}
	if (isOk) {
		KdPrint(("没发现异常\n"));
	}
	KdPrint(("================\n"));
}

void ASSERT_test() {  
	int *p=NULL;
	int i=1;
	ASSERT(p==NULL); //p==NULL条件正常继续，否则中断
}

void TestException() {
	Memaccess_Test();
	ProbeForRead_Test();
	ProbeForWrite_Test();
	finally_test();
	ASSERT_test();
}


#pragma INITCODE
VOID DriverUnload(PDRIVER_OBJECT pDriverObject) {
	DbgPrint("驱动成功卸载!");
}

extern "C" NTSTATUS DriverEntry(PDRIVER_OBJECT pDriverObject, PUNICODE_STRING reg_path) {
	DbgPrint("驱动成功加载!\n");
	TestException();
	pDriverObject->DriverUnload = DriverUnload;
	return STATUS_SUCCESS;
}