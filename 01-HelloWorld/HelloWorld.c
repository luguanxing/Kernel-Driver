#include <ntddk.h>

VOID DriverUnload(PDRIVER_OBJECT pDriverObject) {
	DbgPrint("驱动成功卸载!");
}

NTSTATUS DriverEntry(PDRIVER_OBJECT pDriverObject, PUNICODE_STRING reg_path) {
	DbgPrint("驱动成功加载!\n");
	driver->DriverUnload = DriverUnload;
	return STATUS_SUCCESS;
}
