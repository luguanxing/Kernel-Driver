# 设备对象DeviceObject
------

添加第一个设备对象MyDeviceObject
> * 效果
> * 测试
> * 总结

------
## 效果
![image](https://github.com/luguanxing/Kernel-Driver/blob/master/02-%E8%AE%BE%E5%A4%87%E5%AF%B9%E8%B1%A1DeviceObject/pictures/1.jpg?raw=true)<br>
加载驱动<br><br>

![image](https://github.com/luguanxing/Kernel-Driver/blob/master/02-%E8%AE%BE%E5%A4%87%E5%AF%B9%E8%B1%A1DeviceObject/pictures/2.jpg?raw=true)<br>
成功创建了设备对象<br><br>

![image](https://github.com/luguanxing/Kernel-Driver/blob/master/02-%E8%AE%BE%E5%A4%87%E5%AF%B9%E8%B1%A1DeviceObject/pictures/3.jpg?raw=true)<br>
查看设备对象有关信息<br><br>
<br><br><br>


## 测试
![image](https://github.com/luguanxing/Kernel-Driver/blob/master/02-%E8%AE%BE%E5%A4%87%E5%AF%B9%E8%B1%A1DeviceObject/pictures/4.jpg?raw=true)<br>
利用自带中断下断点调试<br><br>

![image](https://github.com/luguanxing/Kernel-Driver/blob/master/02-%E8%AE%BE%E5%A4%87%E5%AF%B9%E8%B1%A1DeviceObject/pictures/5.jpg?raw=true)<br>
利用windbg下断点调试<br><br>

<br><br><br>
## 总结
刚开始没注意把pDeviceObject写成了pDriverObject，直接蓝屏...符号链接也容易反复,最好起个复杂的链接名而且先删除后使用
<br><br><br>
