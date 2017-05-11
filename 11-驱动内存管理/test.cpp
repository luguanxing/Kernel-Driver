#pragma once
#ifdef __cplusplus
	extern "C" {
#endif
	#include <ntddk.h>
#ifdef __cplusplus
	}
#endif
#define INITCODE code_seg("INIT")



void* _cdecl operator new(size_t size, POOL_TYPE pooltype) {
	KdPrint(("调用new方法\n"));
	KdPrint(("分配内存块大小:%d\n",size));
	return ExAllocatePool(pooltype, size);
}

void _cdecl operator delete(void* pointer) {
	KdPrint(("调用delete方法\n"));
	ExFreePool(pointer);
}

void check(VOID UNALIGNED *p1, VOID UNALIGNED *p2, unsigned char UNALIGNED *p, int ALLOCATE_SIZE) {
	DbgPrint("p1=");
	p = (unsigned char*)p1;
	for (int i = 0; i < ALLOCATE_SIZE; i++)
		DbgPrint("%02x ", p[i]);
	DbgPrint("\n");
	DbgPrint("p2=");
	p = (unsigned char*)p2;
	for (int i = 0; i < ALLOCATE_SIZE; i++)
		DbgPrint("%02x ", p[i]);
	DbgPrint("\n");
}

void TestMemFunciton() {
	VOID UNALIGNED *p1;
	VOID UNALIGNED *p2;
	unsigned char UNALIGNED *p;
	SIZE_T ALLOCATE_SIZE=8;
	ULONG uRet;

	#if DBG
		_asm int 3
	#endif

	//测试重载后的new和delete功能
	char *buffer=new (PagedPool)  char[ALLOCATE_SIZE];
	delete buffer;

	//为p1,p2指针分配大小为ALLOCATE_SIZE字节的内核 内存
	p1 = ExAllocatePool(PagedPool, ALLOCATE_SIZE);
	KdPrint(("p1分配内存地址%x\n", (void*)p1));
	p2 = ExAllocatePool(PagedPool, ALLOCATE_SIZE);
	KdPrint(("p2分配内存地址%x\n", (void*)p2));
	check(p1, p2, p, ALLOCATE_SIZE);

	//填充p1指针
	RtlFillMemory(p1, ALLOCATE_SIZE, 'X');
	KdPrint(("p1填充指针后\n"));
	check(p1, p2, p, ALLOCATE_SIZE);

	//复制p1指针到p2指针内容，必须确保内存没有重叠，否则使用RtlMoveMemory
	RtlCopyMemory(p2, p1, ALLOCATE_SIZE);
	KdPrint(("复制p1指针到p2指针内容后\n"));
	check(p1, p2, p, ALLOCATE_SIZE);

	//比较内存块是否相同
	uRet = RtlCompareMemory(p1, p2, ALLOCATE_SIZE);
	if (uRet == ALLOCATE_SIZE)
		KdPrint(("p1和p2内存块相同\n"));
	else
		KdPrint(("p1和p2内存块不相同\n"));

	//清空p1指针地址内容
	RtlZeroBytes(p1, ALLOCATE_SIZE);
	KdPrint(("清空p1指针地址内容后\n"));
	check(p1, p2, p, ALLOCATE_SIZE);
	uRet = RtlCompareMemory(p1, p2, ALLOCATE_SIZE);
	if (uRet == ALLOCATE_SIZE)
		KdPrint(("p1和p2内存块相同\n"));
	else
		KdPrint(("p1和p2内存块不相同\n"));

	ExFreePool(p1);
	ExFreePool(p2);
}



#pragma INITCODE
VOID DriverUnload(PDRIVER_OBJECT pDriverObject) {
	DbgPrint("驱动成功卸载!");
}

extern "C" NTSTATUS DriverEntry(PDRIVER_OBJECT pDriverObject, PUNICODE_STRING reg_path) {
	DbgPrint("驱动成功加载!\n");
	TestMemFunciton();
	pDriverObject->DriverUnload = DriverUnload;
	return STATUS_SUCCESS;
}