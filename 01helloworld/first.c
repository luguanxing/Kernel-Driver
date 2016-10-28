//后缀名为C则以_stdcall调用
#include <ntddk.h>
#define INITCODE code_seg("INIT") 
#pragma INITCODE

VOID DDK_Unload (IN PDRIVER_OBJECT pDriverObject)
{
	KdPrint(("驱动成功卸载!"));
}

NTSTATUS DriverEntry(PDRIVER_OBJECT pDriverObject,PUNICODE_STRING B)
{
	KdPrint(("驱动成功加载!"));
	pDriverObject->DriverUnload = DDK_Unload;
	return STATUS_SUCCESS;
}
