#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QPushButton>

class MyPushButton : public QPushButton
{
    Q_OBJECT
public:
    explicit MyPushButton(QWidget *parent , QString imgpath_, QString pressed_imgpath_= "");
    ~MyPushButton();

    // 按钮图片路径和被按后图片路径
    // 可选功能：按钮特效、声效
    // 鼠标移动到按钮上有图像和声音反馈，点击按钮有声音反馈（待实现）
    QString imgpath, pressed_imgpath;
signals:

};

#endif // MYPUSHBUTTON_H
