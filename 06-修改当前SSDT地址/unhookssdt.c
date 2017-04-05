#include <ntddk.h>
#include <windef.h>
typedef struct _ServiceDescriptorTable {
	PVOID ServiceTableBase;					//System Service Dispatch Table 的基地址  
	PVOID ServiceCounterTable;				//包含着 SSDT 中每个服务被调用次数的计数器。这个计数器一般由sysenter 更新。 
	unsigned int NumberOfServices;			//由 ServiceTableBase 描述的服务的数目。  
	PVOID ParamTableBase;					//包含每个系统服务参数字节数表的基地址-系统服务参数表 
} *PServiceDescriptorTable;  
extern PServiceDescriptorTable KeServiceDescriptorTable;

#pragma pack(1)	//按1字节对齐
typedef struct MYJMPCODE {
	BYTE E9;
	ULONG JMPADDR;
}JMPCODE, *PJMPCODE;
#pragma pack()	//恢复字节对齐

PJMPCODE pjmpcode;
JMPCODE oldjmpcode;
ULONG cur, old;
BOOL ishook;

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

VOID UnhookProcess() {
	_asm {									//去掉页面保护
		cli
		mov eax, cr0
		and eax, not 10000h
		mov cr0, eax
	}
	pjmpcode = (PJMPCODE)cur;				//指向当前目标地址
	oldjmpcode.E9 = pjmpcode->E9;			//保存当前目标地址前5字节
	oldjmpcode.JMPADDR = pjmpcode->JMPADDR;
	pjmpcode->E9 = 0xE9;					//修改当前目标地址
	pjmpcode->JMPADDR = old-cur-5;
	_asm {									//恢复页面保护
		mov eax, cr0
		or eax, 10000h
		mov cr0,eax
		sti
	}
}

VOID DriverUnload(PDRIVER_OBJECT pDriverObject) {
	if (ishook) {
		_asm {									//去掉页面保护
			cli
			mov eax, cr0
			and eax, not 10000h
			mov cr0, eax
		}
		pjmpcode = (PJMPCODE)cur;				//指向当前目标地址
		pjmpcode->E9 = oldjmpcode.E9;			//恢复目标地址前5字节	
		pjmpcode->JMPADDR = oldjmpcode.JMPADDR;
		_asm {									//恢复页面保护
			mov eax, cr0
			or eax, 10000h
			mov cr0,eax
			sti
		}
	}
	DbgPrint("驱动成功卸载!");
}

NTSTATUS DriverEntry(PDRIVER_OBJECT pDriverObject, PUNICODE_STRING reg_path) {
	DbgPrint("驱动成功加载!\n");
	cur = GetNtOpenProcessCurrentAddr();
	old = GetNtOpenProcessOldAddr();
	if (old != cur) {
		ishook=TRUE;
		DbgPrint("NtOpenProcess地址被Hook了");
		UnhookProcess();
	} else {
		ishook=FALSE;
		DbgPrint("NtOpenProcess地址正常");
	}
	pDriverObject->DriverUnload = DriverUnload;
	return STATUS_SUCCESS;
}