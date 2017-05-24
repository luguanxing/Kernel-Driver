# 异常处理
------

一段测试异常处理的程序
> * 效果

------
## 效果
![image](https://github.com/luguanxing/Kernel-Driver/blob/master/12-%E5%BC%82%E5%B8%B8%E5%A4%84%E7%90%86/pictures/0.jpg?raw=true)<br>
测试异常处理<br><br><br>

```
VOID ProbeForRead(
  __in  PVOID Address,
  __in  SIZE_T Length,
  __in  ULONG Alignment
);
```


```
VOID ProbeForWrite(
  __in  PVOID Address,
  __in  SIZE_T Length,
  __in  ULONG Alignment
);
```

```
NTSTATUS
typedef LONG NTSTATUS;

NT_SUCCESS
#define NT_SUCCESS(Status) ((NTSTATUS)(Status) >= 0)

#define STATUS_SUCCESS                          ((NTSTATUS)0x00000000L) // ntsubauth
//
//  Values are 32 bit values layed out as follows:
//
//   3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
//   1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
//  +---+-+-+-----------------------+-------------------------------+
//  |Sev|C|R|     Facility          |               Code            |
//  +---+-+-+-----------------------+-------------------------------+
//
//  where
//
//      Sev - is the severity code
//
//          00 - Success
//          01 - Informational
//          10 - Warning
//          11 - Error
//
//      C - is the Customer code flag
//
//      R - is a reserved bit
//
//      Facility - is the facility code
//
//      Code - is the facility's status code
//
//
// Define the facility codes

R（Reserved)保留位
C (Customer) 客户位
Sev(Severity) 重要位 共2个二进制位 00表示成功 01表示信息 10表示警告 11表示错误
```
