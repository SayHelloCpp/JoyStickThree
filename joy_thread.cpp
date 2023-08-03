#include "joy_thread.h"
#include <QDebug>

Joy_Thread::Joy_Thread(QObject *parent) :
    QThread(parent)
{
}

//发送joy_row的状态结构体信号
void Joy_Thread::send_state_row(joyinfoex_tag state_row)
{
    emit JoySignal_row(state_row);
}

//发送joy_joystick的状态结构体信号
void Joy_Thread::send_state_joystick(joyinfoex_tag state_row)
{
    emit JoySignal_joystick(state_row);
}

//发送joy_pedal的状态结构体信号
void Joy_Thread::send_state_pedal(joyinfoex_tag state_row)
{
    emit JoySignal_pedal(state_row);
}

void Joy_Thread::run()
{
    //joyinfoex_tag state_row;
    joyinfoex_tag state_row;
    joyinfoex_tag state_joystick;
    joyinfoex_tag state_pedal;

    joyinfoex_tag* joyInfo;

    

    initOp();
    
    qDebug() << "hello";

    while(1) {
        msleep(JOY_READ_PEROID);
        joyInfo = joyRead_row();
        state_row = joyInfo[0];
        state_joystick = joyInfo[1];
        state_pedal = joyInfo[2];

        send_state_row(state_row);
        send_state_joystick(state_joystick);
        send_state_pedal(state_pedal);

        // 释放数组的内存空间
        delete[] joyInfo;
    }
}

