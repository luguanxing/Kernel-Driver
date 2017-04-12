# EXE与SYS交互(缓冲模式)
------

以缓冲模式使应用程序和内核程序交互
> * 效果

------
## 效果
![image](https://github.com/luguanxing/Kernel-Driver/blob/master/07-EXE%E4%B8%8ESYS%E4%BA%A4%E4%BA%92(%E7%BC%93%E5%86%B2%E6%A8%A1%E5%BC%8F)/pictures/0.jpg?raw=true)<br>
应用层EXE读入两个数据<br><br><br>

![image](https://github.com/luguanxing/Kernel-Driver/blob/master/07-EXE%E4%B8%8ESYS%E4%BA%A4%E4%BA%92(%E7%BC%93%E5%86%B2%E6%A8%A1%E5%BC%8F)/pictures/1.jpg?raw=true)<br>
驱动层SYS在内核计算结果并返回<br><br><br>
