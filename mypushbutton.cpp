#include "mypushbutton.h"

MyPushButton::MyPushButton(QWidget *parent , QString imgpath_, QString pressed_imgpath_) :
    QPushButton(parent),
    imgpath(imgpath_),
    pressed_imgpath(pressed_imgpath_)

{
    // 创建按钮图片
    QPixmap img;
    img.load(imgpath);

    // 待实现：点击反馈
    QPixmap pressed_img;
    pressed_img.load(pressed_imgpath);

    // 固定尺寸
    setFixedSize(img.width(), img.height());

    // 不规则边缘
    setStyleSheet("QPushButton{border:0px;}");

    // 设定图标
    setIcon(img);
}

MyPushButton::~MyPushButton()
{

}
