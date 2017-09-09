client2.0是整个系统的核心算法部分，包括视频的采集、解码、检测、跟踪、轨迹的可视化，以及向shell传递处理完成的图像，具体原理在所附的论文中有详细论述。

文件组成：

文件夹：
getpic				保留用于接收截取的图像
HCNetSDKCom			海康动态链接库文件
images				离线视频保存文件
models				保存训练好的VGG网络参数文件和deploy文件

头文件
titlefile.h			所有头文件放在此头文件
Higo_SSD_lib.h			SSD检测的头文件
PlayM4.h			海康解码播放库
LinuxPlayM4.h			海康解码播放库
SocketMatTransmissionClient.h	Socket通信客户端
matqueue.h			mat类的queue库
trackpoint.h			储存每条轨迹的点以及所有轨迹的类
comparision.h			对跟踪和检测结果进行匹配并进行是否通过检测线的判断


.cpp文件
main.cpp			最后版本的主程序

其他文件
config.txt			存储参数，在程序不使用main接口输入初始参数时使用
lib_Higo_SSD.so			ssd封装库
libcaffe.so.1.0.0-rc3		caffe封装库文件
