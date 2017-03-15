# 读取SSDT函数当前地址
------

读取SSDT函数NtOpenProcess当前地址
> * 效果
> * 测试
> * 总结

------
## 效果
![image](https://github.com/luguanxing/Kernel-Driver/blob/master/04-%E8%AF%BB%E5%8F%96SSDT%E5%87%BD%E6%95%B0%E5%BD%93%E5%89%8D%E5%9C%B0%E5%9D%80/pictures/2.jpg?raw=true)
<br>用方式1（汇编）读出函数地址
<br><br><br>

![image](https://github.com/luguanxing/Kernel-Driver/blob/master/04-%E8%AF%BB%E5%8F%96SSDT%E5%87%BD%E6%95%B0%E5%BD%93%E5%89%8D%E5%9C%B0%E5%9D%80/pictures/3.jpg?raw=true)
<br>用方式2（指针）读出函数地址
<br><br><br><br><br>

## 测试
![image](https://github.com/luguanxing/Kernel-Driver/blob/master/04-%E8%AF%BB%E5%8F%96SSDT%E5%87%BD%E6%95%B0%E5%BD%93%E5%89%8D%E5%9C%B0%E5%9D%80/pictures/0.jpg?raw=true)
![image](https://github.com/luguanxing/Kernel-Driver/blob/master/04-%E8%AF%BB%E5%8F%96SSDT%E5%87%BD%E6%95%B0%E5%BD%93%E5%89%8D%E5%9C%B0%E5%9D%80/pictures/1.jpg?raw=true)
<br>使用Windbg跟踪
<br><br><br><br><br>

## 总结
两种方式效果一样(方式1较简单，方式2较正规)
<br><br><br>
