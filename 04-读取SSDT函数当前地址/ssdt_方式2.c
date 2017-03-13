#include <ntddk.h>

VOID DriverUnload(PDRIVER_OBJECT pDriverObject) {
	DbgPrint("驱动成功卸载!");
}

typedef struct _ServiceDescriptorTable {
	PVOID ServiceTableBase;					//System Service Dispatch Table 的基地址  
	PVOID ServiceCounterTable;				//包含着 SSDT 中每个服务被调用次数的计数器。这个计数器一般由sysenter 更新。 
	unsigned int NumberOfServices;		//由 ServiceTableBase 描述的服务的数目。  
	PVOID ParamTableBase;						//包含每个系统服务参数字节数表的基地址-系统服务参数表 
} *PServiceDescriptorTable;  
extern PServiceDescriptorTable KeServiceDescriptorTable;

NTSTATUS DriverEntry(PDRIVER_OBJECT pDriverObject, PUNICODE_STRING reg_path) {
	LONG PSSDT_Addr, *SSDT_Addr, SSDT_NtOpenProcess_Addr; 
	DbgPrint("驱动成功加载!\n");
	pDriverObject->DriverUnload = DriverUnload;

	PSSDT_Addr=(LONG)KeServiceDescriptorTable->ServiceTableBase;
	KdPrint(("当前ServiceTableBase地址为%08x\n", PSSDT_Addr));
	SSDT_Addr=(PLONG)(PSSDT_Addr+0x7A*4);
	KdPrint(("当前PSSDT_Addr+0x7A*4=%08x\n", SSDT_Addr)); 
	SSDT_NtOpenProcess_Addr=*SSDT_Addr;	
	KdPrint(("当前SSDT_NtOpenProcess_Addr地址为%08x\n", SSDT_NtOpenProcess_Addr));
	return STATUS_SUCCESS;
}