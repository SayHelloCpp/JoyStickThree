#ifndef JOYSTICK_H
#define JOYSTICK_H

#include <QLibrary>
#include <iostream>
//#include <QDebug>
#include <QString>
#include "windows.h"
#include "winuser.h"
//采用多媒体库轮询读取手柄的好处是可以方便地自定义手柄组合按键
#include "mmsystem.h"


#define  JSX             JOYSTICKID1 //手柄ID号 -- JoyStick


typedef int (*MyPrototype) (HWND, UINT, UINT, BOOL);
extern MyPrototype qJoySetCapture;//向系统申请捕获某个游戏设备并定时将该设备的状态值通过消息发送到某个窗口

typedef UINT (*MyPrototype1) (UINT);
extern MyPrototype1 qJoyReleaseCapture ;//释放对某个游戏设备的捕获

typedef UINT (*MyPrototype2) (UINT, LPJOYINFOEX);
extern MyPrototype2 qJoyGetPosEx;//获取游戏设备的坐标位置和按钮状态

typedef void (*MyPrototype0) (UINT, LPJOYINFO);
extern MyPrototype0 qJoyGetPos;//获取游戏设备的坐标位置和按钮状态

typedef void (*MyPrototype3) (UINT, LPUINT);
extern MyPrototype3 qJoyGetThreshold ;//查询指定的游戏杆设备的当前移动阈值

typedef UINT (*MyPrototype4) (UINT, LPJOYCAPS, UINT);
extern MyPrototype4 qJoyGetDevCaps;//设置指定的游戏杆设备的移动阈值

typedef UINT (*MyPrototype5) (void);
extern MyPrototype5 qJoyGetNumDevs;//	获取当前系统支持的游戏设备数量

//joystick外部接口
void initOp();
void openJoy();
struct joyinfoex_tag* joyRead_row();






#endif // JOYSTICK_H
