# 简单进程保护

------

使应用程序和内核程序交互，使内核保护输入的进程
> * 效果
> * 过程

------
## 效果
![image](https://github.com/luguanxing/Kernel-Driver/blob/master/10-%E7%AE%80%E5%8D%95%E8%BF%9B%E7%A8%8B%E4%BF%9D%E6%8A%A4/pictures/test.gif?raw=true)<br>
应用层EXE读入进程id在内核驱动层SYS进行保护<br><br><br><br><br>

## 过程
![image](https://github.com/luguanxing/Kernel-Driver/blob/master/10-%E7%AE%80%E5%8D%95%E8%BF%9B%E7%A8%8B%E4%BF%9D%E6%8A%A4/pictures/0.jpg?raw=true)<br>
打开驱动，用任务管理器查看保护的进程id，这里选择记事本<br><br><br><br>

![image](https://github.com/luguanxing/Kernel-Driver/blob/master/10-%E7%AE%80%E5%8D%95%E8%BF%9B%E7%A8%8B%E4%BF%9D%E6%8A%A4/pictures/1.jpg?raw=true)<br>
运行后发现内核一直在过滤打开的驱动<br><br><br><br>

![image](https://github.com/luguanxing/Kernel-Driver/blob/master/10-%E7%AE%80%E5%8D%95%E8%BF%9B%E7%A8%8B%E4%BF%9D%E6%8A%A4/pictures/2.jpg?raw=true)<br>
尝试用CE打开记事本<br><br><br><br>

![image](https://github.com/luguanxing/Cheating-Plugin-Program/raw/master/07%E7%AE%80%E5%8D%95%E8%BF%9B%E7%A8%8B%E4%BF%9D%E6%8A%A4/pictures/1.jpg?raw=true)<br>
返回失败，无法用CE打开记事本扫描内存<br><br><br><br>
