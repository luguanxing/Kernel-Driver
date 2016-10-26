#include <ntddk.h>

VOID DriverUnload(PDRIVER_OBJECT driver) {
	DbgPrint("loading!\n");
}

NTSTATUS DriverEntry(PDRIVER_OBJECT driver, PUNICODE_STRING reg_path) {
	DbgPrint("hello world!\n");
	driver->DriverUnload = DriverUnload;
	return STATUS_SUCCESS;
}