##Get Plane Equation
-已知三点求平面方程
-函数参数依次为三点的x,y,z

##xlsxSortout:

###使用方法：
- 1.将xlsTocsv.bat与xls文件放在同一目录下，运行此文件，即可获得这一目录下所有xls文件转换而来的csv文件
- 2.在这个目录下，打开命令行，输入dir /b /a:-d > all.txt 获得所有文件名并保存为txt文件，方便然后使用，也可以自己加上FindFirstFile&FindNextFile的函数，避免此操作
- 3.将所有在第一步获得的csv放到xlsxSortout.exe同目录的temp文件夹中（没有就自行新建），放置all.txt,keyword.txt于exe的同目录

####附：keyword文件结构:
- 1.第一行一个整数n，为有多少个关键字
- 2.第2~n+1行，每行一个字符串，为每个关键字的名称
- 3.第n+2~3*n+2行，每行一个字符串，第奇数个字符串为起始关键字，偶数个字符串为结束关键字，从1开始计数
- <s>*如果实在看不懂，就直接看源码吧*</s>

##Useful Function

###GetHtmlAndTrim
- 不写用法了，代码还没有完成，还在写自动写入SUMMARY.md和写入标题
- 纯粹就是一个从网页上摘取文章并保存为.md的文件，更快完成书籍的摘取，简化步骤

###Build Requirements for Windows Vista Common Controls
- 为Windows窗体（Win32&MFC）添加新的窗体样式

###ifstreamChineseReading
- 读取GB2312和UTF-8的方式，这里提到了ifstream和ofstream的方法，同样可以对cin以及cout直接应用

###SetWindowSize
- 为Win32 API创建的窗体重新设置大小，使其加上了边框的大小，令客户区就是自己想要的大小