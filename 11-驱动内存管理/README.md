# 驱动内存管理
------

一段测试驱动内存管理常用API的程序
> * 效果

------
## 效果
![image](https://github.com/luguanxing/Kernel-Driver/blob/master/11-%E9%A9%B1%E5%8A%A8%E5%86%85%E5%AD%98%E7%AE%A1%E7%90%86/pictures/0.jpg?raw=true)<br>
测试两个变量<br><br><br>

### RtlCopyMemory,RtlCopyBytes和RtlMoveMemory
### RtlZeroMemory和RtlFillMemory
### RtlEqualMemory
### ExAllocatePool和 ExFreePool
### 重载new和delete操作符
 
```
VOID RtlCopyMemory(
 
__in  VOID UNALIGNED *Destination,

__in  const VOID UNALIGNED *Source,
 
__in  SIZE_T Length
);

```

```
VOID RtlCopyBytes(
 
 __in  PVOID Destination,
 
 __in  const VOID *Source,

 __in  SIZE_T Length
);
```

```
VOID RtlMoveMemory(
  
__in  VOID UNALIGNED *Destination,

__in  const VOID UNALIGNED *Source,
  
__in  SIZE_T Length
);
```

```
VOID RtlZeroMemory(

__in  VOID UNALIGNED *Destination,
  
__in  SIZE_T Length
);
```

```
VOID RtlFillMemory(

 __in  VOID UNALIGNED *Destination,
 
 __in  SIZE_T Length,
 
 __in  UCHAR Fill
);
```

```
LOGICAL RtlEqualMemory(

__in  const VOID *Source1,
  
__in  const VOID *Source2,
  
__in  SIZE_T Length
);
```

```
SIZE_T RtlCompareMemory(
  
__in  const VOID *Source1,
 
__in  const VOID *Source2,
  
__in  SIZE_T Length
);
```

```
PVOID ExAllocatePool(
 
 __in  POOL_TYPE PoolType,
  
__in  SIZE_T NumberOfBytes
);
```

```
VOID ExFreePool(
 __in  PVOID P
);
```

```
void* _cdecl operator new(size_t size, POOL_TYPE pooltype) {
	KdPrint(("调用new方法\n"));
	KdPrint(("分配内存块大小:%d\n",size));
	return ExAllocatePool(pooltype, size);
}
```

```
void _cdecl operator delete(void* pointer) {
	KdPrint(("调用delete方法\n"));
	ExFreePool(pointer);
}
```
