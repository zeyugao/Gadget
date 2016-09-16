##GetHtmlAndTrim
- 不写用法了，代码还没有完成，还在写自动写入SUMMARY.md和写入标题

- 纯粹就是一个从网页上摘取文章并保存为.md的文件，更快完成书籍的摘取，简化步骤

##xlsxSortout:

- 使用方法：
1.将xlsTocsv.bat与xls文件放在同一目录下，运行此文件，即可获得这一目录下所有xls文件转换而来的csv文件
2.在这个目录下，打开命令行，输入dir /b /a:-d > all.txt 获得所有文件名并保存为txt文件，方便然后使用，也可以自己加上FindFirstFile&FindNextFile的函数，避免此操作
3.将所有在第一步获得的csv放到xlsxSortout.exe同目录的temp文件夹中（没有就自行新建），放置all.txt,keyword.txt于exe的同目录

- keyword文件结构:
1.第一行一个整数n，为有多少个关键字
2.第2~n+1行，每行一个字符串，为每个关键字的名称
3.第n+2~3*n+2行，每行一个字符串，第奇数个字符串为起始关键字，偶数个字符串为结束关键字，从1开始计数

