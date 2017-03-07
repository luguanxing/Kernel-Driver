#include <ntddk.h>
#define INITCODE code_seg("INIT") 
#define PAGECODE code_seg("PAGE")	//表示内存不足时，可以被置换到硬盘
#pragma INITCODE										//指的代码运行后 就从内存释放掉

NTSTATUS CreateMyDevice(IN PDRIVER_OBJECT pDriverObject) {
	NTSTATUS status;
	UNICODE_STRING devName;				//设备名称
	UNICODE_STRING sysLinkName;			//系统符号链接名
	PDEVICE_OBJECT pDevObject;				//用于返回创建设备

	RtlInitUnicodeString(&devName, L"\\Device\\MyDevObj");
	status = IoCreateDevice(pDriverObject, 0, &devName, FILE_DEVICE_UNKNOWN, 0, TRUE, &pDevObject);
	if (!NT_SUCCESS(status)) {						//判断创建设备是否成功
		if (status == STATUS_INSUFFICIENT_RESOURCES)
			KdPrint(("资源不足\n"));
		if (status == STATUS_OBJECT_NAME_EXISTS)
			KdPrint(("指定对象名存在\n"));
		if (status == STATUS_OBJECT_NAME_COLLISION)
			KdPrint(("对象名有冲突\n"));
		return status;
	}
	KdPrint(("设备创建成功\n"));

	pDevObject->Flags |= DO_BUFFERED_IO;	//缓冲区方式读写
	RtlInitUnicodeString(&sysLinkName, L"\\??\\MySysLinkName_20170307");
	IoDeleteSymbolicLink(&sysLinkName);		//防止已有相同符号链接重复
	status = IoCreateSymbolicLink(&sysLinkName, &devName);		//判断生成符号链接是否成功

	if (!NT_SUCCESS(status)) {
		KdPrint(("生成符号链接失败\n"));
		IoDeleteDevice(pDevObject);
		return status;
	}
	KdPrint(("生成符号链接成功\n"));
	return STATUS_SUCCESS;
}


VOID DriverUnload(PDRIVER_OBJECT pDriverObject) {
	PDEVICE_OBJECT pDevObject;
	UNICODE_STRING sysLinkName;

	pDevObject = pDriverObject->DeviceObject;
	IoDeleteDevice(pDevObject);	//取得设备并删除
	KdPrint(("成功删除设备\n"));

	RtlInitUnicodeString(&sysLinkName, L"\\??\\MySysLinkName_20170307");
	IoDeleteSymbolicLink(&sysLinkName);	//取得符号链接并删除
	KdPrint(("成功删除符号链接\n"));

	KdPrint(("驱动成功卸载\n"));
}


NTSTATUS DriverEntry(PDRIVER_OBJECT pDriverObject, PUNICODE_STRING reg_path) {
	KdPrint(("驱动成功加载\n"));
	CreateMyDevice(pDriverObject);
	pDriverObject->DriverUnload=DriverUnload;
	return STATUS_SUCCESS;
}