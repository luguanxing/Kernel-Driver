#pragma once
#ifdef __cplusplus
	extern "C" {
#endif
	#include <ntddk.h>
#ifdef __cplusplus
	}
#endif
#define INITCODE code_seg("INIT")


#define BUFFER_SIZE 1024
VOID CharTest() {  
	KdPrint(("=========字串测试=========\n"));
	PCHAR s1="abc11";		//CHAR
	KdPrint(("%x,%s\n",s1,s1)); 
	WCHAR* s2=L"abc11";		//WCHAR
	KdPrint(("%x,%S\n",s2,s2));
	KdPrint(("==========================\n"));
	KdPrint(("\n"));
}

VOID StringInitTest() {
	KdPrint(("=========初始化字串测试=========\n"));
	ANSI_STRING AnsiString1={0};
	ANSI_STRING AnsiString2={0};
	UNICODE_STRING UnicodeString1={0};
	UNICODE_STRING UnicodeString2={0};
	
	//用缓冲区初始化
	AnsiString1.Buffer=(PCHAR)ExAllocatePool(PagedPool,BUFFER_SIZE);
	strcpy(AnsiString1.Buffer,"ANSI_STRING!!!!!!");
	AnsiString1.Length=strlen( AnsiString1.Buffer);
	AnsiString1.MaximumLength=BUFFER_SIZE;

	UnicodeString1.Buffer=(PWSTR)ExAllocatePool(PagedPool,BUFFER_SIZE);
	wcscpy(UnicodeString1.Buffer,L"UNICODE_STRING!!!!!!");
	UnicodeString1.Length=wcslen(UnicodeString1.Buffer)*2-1;
	UnicodeString1.MaximumLength = BUFFER_SIZE;

	//用RTL函数初始化
	RtlInitAnsiString(&AnsiString2, "ANSI_STRING!!!!!!");	 
	RtlInitUnicodeString(&UnicodeString2, L"UNICODE_STRING!!!!!!");

	//打印ASCII字符用 %Z
	KdPrint(("%x AnsiString1:   %Z\n",&AnsiString1,   &AnsiString1));
	KdPrint(("%x AnsiString2:   %Z\n",&AnsiString2,   &AnsiString2));
	
	//打印UNICODE字符用 %wZ 中文字符会被截断
	KdPrint(("%x UnicodeString1:%wZ\n",&UnicodeString1,&UnicodeString1));
	KdPrint(("%x UnicodeString2:%wZ\n",&UnicodeString2,&UnicodeString2));
	KdPrint(("===========================\n")); 

	//销毁UnicodeString2
	//注意!调用过RtlInitUnicodeString 初始化的字串!UnicodeString2，AnsiString1不用销毁,否则会蓝屏
	RtlFreeAnsiString(&AnsiString1);
	RtlFreeUnicodeString(&UnicodeString1);
	KdPrint(("\n"));
}

VOID StringCopyTest() { 
	KdPrint(("=========字串复制判断测试开始=========\n"));
	UNICODE_STRING UnicodeString1={0};
	RtlInitUnicodeString(&UnicodeString1,L"COPY_STRING_TEST");

	UNICODE_STRING UnicodeString2={0};
	UnicodeString2.Buffer = (PWSTR)ExAllocatePool(PagedPool,BUFFER_SIZE);
	UnicodeString2.MaximumLength = BUFFER_SIZE;
	//将初始化UnicodeString1拷贝到UnicodeString2
	RtlCopyUnicodeString(&UnicodeString2,&UnicodeString1);

	//分别显示UnicodeString1和UnicodeString2
	KdPrint(("字串1:%wZ\n",&UnicodeString1));
	KdPrint(("字串2:%wZ\n",&UnicodeString2));
	if ( RtlEqualUnicodeString(&UnicodeString1,&UnicodeString2,true)) { 
		KdPrint(("字串相等\n"));
	}
	
	//销毁UnicodeString2
	//注意!调用过RtlInitUnicodeString 初始化的字串UnicodeString1不用销毁, 
	//RtlFreeUnicodeString(&UnicodeString1); 加上此行会蓝屏
	RtlFreeUnicodeString(&UnicodeString2);
	KdPrint(("==================================\n"));
		KdPrint(("\n"));
}

VOID StringToUpperTest() {  
	KdPrint(("===============字串转大写测试===============\n"));
	UNICODE_STRING UnicodeString1;
	RtlInitUnicodeString(&UnicodeString1,L"UnicodeString1—Aabc");
	//变化前
	KdPrint(("UnicodeString1 初值:%wZ\n",&UnicodeString1));
	//变大写
	RtlUpcaseUnicodeString(&UnicodeString1,&UnicodeString1,FALSE);
	//变化后
	KdPrint(("UnicodeString1 转换大写后:%wZ\n",&UnicodeString1));
	KdPrint(("=============================================\n"));
		KdPrint(("\n"));
}

VOID StringToIntegerTest() {   
	KdPrint(("===============字串转整数测试===============\n"));
	//字符串转换成数字
	UNICODE_STRING UnicodeString1;
	RtlInitUnicodeString(&UnicodeString1,L"101");
	ULONG lNumber;
	KdPrint(("待转换字串%wZ \n",&UnicodeString1));
	NTSTATUS nStatus = RtlUnicodeStringToInteger(&UnicodeString1,2,&lNumber);
	if ( NT_SUCCESS(nStatus)) {
		KdPrint(("字串转换2进制整数成功 结果=%d !\n",lNumber));
	} else {
		KdPrint(("转换整数 失败\n"));
	}

	//数字转换成字符串
	UNICODE_STRING UnicodeString2={0};
	UnicodeString2.Buffer = (PWSTR)ExAllocatePool(PagedPool,BUFFER_SIZE);
	UnicodeString2.MaximumLength = BUFFER_SIZE;
	nStatus = RtlIntegerToUnicodeString(200,2,&UnicodeString2);
	if ( NT_SUCCESS(nStatus)) {
		KdPrint(("2进制数字转换字串成功! 结果:%wZ\n",&UnicodeString2));
	} else {
		KdPrint(("转换字串 失败!\n"));
	}

	//销毁UnicodeString2
	//注意!调用过RtlInitUnicodeString 初始化的字串!UnicodeString1不用销毁, 
	//RtlFreeUnicodeString(&UnicodeString1); 加上此行会蓝屏
	RtlFreeUnicodeString(&UnicodeString2);
	KdPrint(("=============================================\n"));
		KdPrint(("\n"));
}

//ANSI_STRING字符串与UNICODE_STRING字符串相互转换测试
VOID StringConverTest() {  
	KdPrint(("===============ANSI_STRING字符串与UNICODE_STRING字符串相互转换测试===============\n"));
	//将UNICODE_STRING字符串转换成ANSI_STRING字符串
	UNICODE_STRING UnicodeString1;
	RtlInitUnicodeString(&UnicodeString1,L"UnicodeString");
	ANSI_STRING AnsiString1;
	NTSTATUS nStatus = RtlUnicodeStringToAnsiString(&AnsiString1,&UnicodeString1,true);
	if ( NT_SUCCESS(nStatus)) {
		KdPrint(("RtlUnicodeStringToAnsiString 转换成功 结果=%Z\n",&AnsiString1));
	} else {
		KdPrint(("RtlAnsiStringToUnicodeString 转换失败 !\n"));
	}
	RtlFreeAnsiString(&AnsiString1);

	//将ANSI_STRING字符串转换成UNICODE_STRING字符串
	ANSI_STRING AnsiString2;
	RtlInitString(&AnsiString2,"AnsiString");
	UNICODE_STRING UnicodeString2;
	nStatus = RtlAnsiStringToUnicodeString(&UnicodeString2,&AnsiString2,true);
	if ( NT_SUCCESS(nStatus)) {
		KdPrint(("RtlAnsiStringToUnicodeString转换成功 结果=%wZ\n",&UnicodeString2));
	} else {
		KdPrint(("RtlAnsiStringToUnicodeString字串转换失败!\n"));
	}
	RtlFreeUnicodeString(&UnicodeString2);
	KdPrint(("=====================================================================================\n")); 
		KdPrint(("\n"));
}

void TestString() {
	CharTest();
	StringInitTest();
	StringCopyTest();
	StringToUpperTest();
	StringToIntegerTest();
	StringConverTest();
}


#pragma INITCODE
VOID DriverUnload(PDRIVER_OBJECT pDriverObject) {
	DbgPrint("驱动成功卸载!");
}

extern "C" NTSTATUS DriverEntry(PDRIVER_OBJECT pDriverObject, PUNICODE_STRING reg_path) {
	DbgPrint("驱动成功加载!\n");
	TestString();
	pDriverObject->DriverUnload = DriverUnload;
	return STATUS_SUCCESS;
}