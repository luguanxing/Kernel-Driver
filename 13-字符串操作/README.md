# 字符串操作
------

一段测试字符串操作的程序
> * 效果

------
## 效果
![image](https://github.com/luguanxing/Kernel-Driver/blob/master/13-%E5%AD%97%E7%AC%A6%E4%B8%B2%E6%93%8D%E4%BD%9C/pictures/0.jpg?raw=true)<br>
测试字符串操作<br><br><br>


# ASNI字符串和UNICODE字符串
在C语言中，有ANSI和UNICODE 两个不同字串类型。
```
    char* s1="abc";          //CHAR * s1="abc"; 61
    KdPrint(("%x,%s\n",s1,s1));
    wchar_t * s2=L"abc";     //WCHAR * s2=L"abc";00 61
    KdPrint(("%x,%S\n",s2,s2));
```

# ANSI_STRING字符串和UNICODE_STRING字符串
在C语言中，传统的char和wchar_t类型的字符串在使用过程中，很容易出现缓冲区溢出错误，从而导致整个系统的崩溃。一般由于程序员没有对字串长度进行校验造成的。
所以在DDK中 提供了2个带字串长度的类型 ANSI_STRING和UNICODE_STRING
```
   ANSI_STRING s1 ;        //CHAR Length MaxLength PCHAR
   KdPrint(("%x,%Z\n",s1,s1));
   UNICODE_STRING s2   //WCHAR * =PWSTR
   KdPrint(("%x,%wZ\n",s2,s2));
```

# 字符串的初始化与销毁
在使用ANSI_STRING和UNICODE_STRING这2个类型的字串时都需要对其进行初始化 和销毁
```
RtlInitAnsiString  RtlInitString(&s1,"abc"); //%Z
RtlInitUnicodeString(&s2,L"abc");// %wZ
```

# 字符串复制，比较，（大小写，整数和字串）相互转换
```
RtlFreeAnsiString
RtlFreeUnicodeString
RtlCopyUnicodeString
RtlEqualUnicodeString
RtlUpcaseUnicodeString
RtlUnicodeStringToInteger
RtlIntegerToUnicodeString
```

# ANSI_STRING字符串和UNICODE_STRING字符串相互转换
```
RtlUnicodeStringToAnsiString
RtlAnsiStringToUnicodeString
```
