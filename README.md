# myt-androidControl-demo

1.默认使用windows x64系统，libmytrpc.h文件中是调用方法

2.参数说明

    -command string
    操作指令, click--点击, move--滑动 (default "move")
    -host string
    安卓host，例192.168.100.10
    -x1 int
    x轴坐标x1 (default 200)
    -y1 int
    y轴坐标y1 (default 200)
    -x2 int
    滑动终点x轴坐标x2 (default 600)
    -y2 int
    滑动终点y轴坐标y2 (default 200)

3.模拟点击

    .\demo.exe -host=192.168.100.10 -command=click -x1=269 -y1=690

4.模拟滑动

    .\demo.exe -host=192.168.100.10 -command=move -x1=269 -y1=690 -x2=300 -y2=300