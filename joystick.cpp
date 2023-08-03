#include "joystick.h"
#include <QMessageBox>
#include <QDebug>
#include <QThread>

using std::cout;

static joyinfoex_tag     now_act;




//加载多媒体库
QLibrary mylib("Winmm.dll");
MyPrototype qJoySetCapture = (MyPrototype)mylib.resolve("joySetCapture");
//游戏杆数获得函数
MyPrototype1 qJoyReleaseCapture = (MyPrototype1)mylib.resolve("joyReleaseCapture");
//返回游戏杆位置及按钮活动函数
MyPrototype2 qJoyGetPosEx = (MyPrototype2)mylib.resolve("joyGetPosEx");
//返回游戏杆位置及按钮活动函数
MyPrototype0 qJoyGetPos = (MyPrototype0)mylib.resolve("joyGetPos");
//读取操纵杆移动阈值
MyPrototype3 qJoyGetThreshold = (MyPrototype3)mylib.resolve("joyGetThreshold");
//获取操纵杆属性信息，以结构体JoyCaps接收
MyPrototype4 qJoyGetDevCaps = (MyPrototype4)mylib.resolve("joyGetDevCapsW");
//有多少个游戏杆可以用
MyPrototype5 qJoyGetNumDevs = (MyPrototype5)mylib.resolve("joyGetNumDevs");




void initOp()
{
    // Initialize DirectInput
    //MMRESULT result = qJoySetCapture(GetConsoleWindow(), JSX, 0, TRUE);
    //if (result != JOYERR_NOERROR) {
    //    //qDebug() << "Failed to capture joystick input";
    //    qCritical() << "打开设备失败，错误代码：" << result;

    //    return;
    //}

    // 获取连接到计算机上的游戏手柄数量(显示的是可连接数量)
    UINT numJoysticks = qJoyGetNumDevs();
    QString message = QString("Connected device count: %1").arg(numJoysticks);
    
    if (numJoysticks == 0) {
        qDebug() << QString::fromLocal8Bit("No gamepad attached");
    }
    else {
        
        qDebug() << message;

        }
    openJoy();
}

void openJoy()
{
    JOYCAPS joyCaps[3];
    // 处理获取游戏手柄设备属性信息
    for(int i = 0; i < 3; i++){    // 获取游戏手柄设备的属性信息
        ZeroMemory(&joyCaps, sizeof(JOYCAPS));

        MMRESULT result1 = qJoyGetDevCaps(i, &joyCaps[i], sizeof(JOYCAPS));
        // 获取游戏手柄设备属性信息成功
        // 获取设备名称
        ;
        QString deviceName = QString::fromWCharArray(reinterpret_cast<const wchar_t*>(&joyCaps[i].szPname));

        qDebug() << "Device name:" << deviceName;

        if (result1 != JOYERR_NOERROR)
        {
            //处理获取游戏手柄设备属性信息失败的情况
            //...
        }

        // 获取操纵杆当前使用的轴数
        int numAxes = joyCaps[i].wNumAxes;
        qDebug() << "Number of axes:" << numAxes;
    }
}


struct joyinfoex_tag* joyRead_row()
{
    //now_act.dwSize = sizeof(joyinfoex_tag);
    //now_act.dwFlags = (int)JOY_RETURNBUTTONS;
    //qJoyGetPosEx(JSX, &now_act);//根据需要，调用该方法查询某个游戏手柄的当前状态
    //return now_act;

    joyinfoex_tag* joyInfo = new joyinfoex_tag[3];

     // 获取三个游戏手柄设备的状态信息
    for (int i = 0; i < 3; i++)
    {
        // 初始化JOYINFOEX结构体
        ZeroMemory(&joyInfo[i], sizeof(joyinfoex_tag));
        joyInfo[i].dwSize = sizeof(joyinfoex_tag);
        //joyInfo[i].dwFlags = JOY_RETURNALL;
        joyInfo[i].dwFlags = (int)JOY_RETURNBUTTONS;


        // 获取游戏手柄设备的状态信息
        MMRESULT result = qJoyGetPosEx(i, &joyInfo[i]);
        if (result != JOYERR_NOERROR)
        {
            // 处理获取游戏手柄设备状态信息失败的情况
            // ...
        }
    }
    return joyInfo;
}
