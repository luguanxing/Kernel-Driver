#include <ntddk.h>

typedef struct _ServiceDescriptorTable {
	PVOID ServiceTableBase;					//System Service Dispatch Table 的基地址  
	PVOID ServiceCounterTable;				//包含着 SSDT 中每个服务被调用次数的计数器。这个计数器一般由sysenter 更新。 
	unsigned int NumberOfServices;		//由 ServiceTableBase 描述的服务的数目。  
	PVOID ParamTableBase;						//包含每个系统服务参数字节数表的基地址-系统服务参数表 
} *PServiceDescriptorTable;  
extern PServiceDescriptorTable KeServiceDescriptorTable;

ULONG GetNtOpenProcessCurrentAddr() {
	ULONG PSSDT_Addr, *SSDT_Addr, SSDT_NtOpenProcess_Cur_Addr;
	PSSDT_Addr=(LONG)KeServiceDescriptorTable->ServiceTableBase;
	SSDT_Addr=(PLONG)(PSSDT_Addr+0x7A*4);
	SSDT_NtOpenProcess_Cur_Addr=*SSDT_Addr;	
	KdPrint(("当前NtOpenProcess地址为%08x\n", SSDT_NtOpenProcess_Cur_Addr));
	return SSDT_NtOpenProcess_Cur_Addr;
}

ULONG GetNtOpenProcessOldAddr() {
	ULONG  SSDT_NtOpenProcess_Old_Addr; 
	UNICODE_STRING SSDT_NtOpenProcess_Name;
	RtlInitUnicodeString(&SSDT_NtOpenProcess_Name, L"NtOpenProcess");
	SSDT_NtOpenProcess_Old_Addr = (ULONG)MmGetSystemRoutineAddress(&SSDT_NtOpenProcess_Name);
	KdPrint(("原函数NtOpenProcess的地址为%08x\n", SSDT_NtOpenProcess_Old_Addr));
	return SSDT_NtOpenProcess_Old_Addr;
}

VOID DriverUnload(PDRIVER_OBJECT pDriverObject) {
	DbgPrint("驱动成功卸载!");
}

NTSTATUS DriverEntry(PDRIVER_OBJECT pDriverObject, PUNICODE_STRING reg_path) {
	ULONG cur, old;
	DbgPrint("驱动成功加载!\n");
	cur = GetNtOpenProcessCurrentAddr();
	old = GetNtOpenProcessOldAddr();
	if (old != cur) {
		DbgPrint("NtOpenProcess地址被Hook了");
	} else {
		DbgPrint("NtOpenProcess地址正常");
	}
	pDriverObject->DriverUnload = DriverUnload;
	return STATUS_SUCCESS;
}