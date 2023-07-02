# myt-androidControl-demo

1.默认使用windows x64系统，libmytrpc.h文件中是调用方法，exe文件须和libmytrpc.dll在同一个目录下，安卓必须是使用桥接网络模式创建的

2.参数说明

    -command string
    操作指令, click--点击, move--滑动, screenshot--截图 (default "click")
    -batch
    批量发送命令，为true时会读取config.json文件，默认false
    -host string
    安卓host，例192.168.100.10，batch为true时可不传
    -x1 int
    x轴坐标x1 (default 269)
    -y1 int
    y轴坐标y1 (default 462)
    -x2 int
    滑动终点x轴坐标x2 (default 600)
    -y2 int
    滑动终点y轴坐标y2 (default 200)

3.模拟点击

    .\demo.exe -host=192.168.100.10 -command=click -x1=269 -y1=462

4.模拟滑动

    .\demo.exe -host=192.168.100.10 -command=move -x1=269 -y1=690 -x2=300 -y2=300

5.屏幕截图

    .\demo.exe -host=192.168.100.10 -command=screenshot

6.批量发送命令

    .\demo.exe -batch=true -command=click -x1=269 -y1=462