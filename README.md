## 依赖：libuiohook  https://github.com/kwhat/libuiohook/tree/1.2

## 0x00000135 原因： *.exe文件找不到链接库

## windows 下找不到C编译器的问题： 更新Visio studio 中的SDK版本，大于cmake中的select版本
<p>
  <code>
    <font color=Red>Success</font>: Selecting Windows SDK version 10.0.20348.0 to target Windows 10.0.19044.</code>
</p>
<p>
  <code>
    <font color=Red>Errors </font>: Selecting Windows SDK version 10.0.19041.0 to target Windows 10.0.19044.</code>
</p>


## TODO: 实现款跨平台的全局热键功能

```$ git clone https://github.com/kwhat/libuiohook
$ cd uiohook
$ mkdir build && cd build
$ cmake -S .. -D BUILD_SHARED_LIBS=ON -D BUILD_DEMO=ON -DCMAKE_INSTALL_PREFIX=../dist
$ cd ../dist
$ cmake --build . --parallel 2 --target install