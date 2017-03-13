#include <ntddk.h>

VOID DriverUnload(PDRIVER_OBJECT pDriverObject) {
	DbgPrint("驱动成功卸载!");
}

extern long KeServiceDescriptorTable;	//读取SSDT表[[KeServiceDescriptorTable]+0x7a*4]中的NtOpenProcess地址

NTSTATUS DriverEntry(PDRIVER_OBJECT pDriverObject, PUNICODE_STRING reg_path) {
	ULONG SSDT_NtOpenProcess;
	DbgPrint("驱动成功加载!\n");
	pDriverObject->DriverUnload = DriverUnload;
	_asm {
		push ebx
		push eax
			mov ebx, KeServiceDescriptorTable
			mov ebx, [ebx]											//[KeServiceDescriptorTable]
			mov eax, 0x7a											
			shl eax, 2
			add ebx, eax												//[KeServiceDescriptorTable]+0x7a*4
			mov ebx, [ebx]											//NtOpenProcess地址
			mov SSDT_NtOpenProcess, ebx
		pop eax
		pop ebx
	}
	KdPrint(("NtOpenProcess的地址是%08x\n", SSDT_NtOpenProcess));
	return STATUS_SUCCESS;
}