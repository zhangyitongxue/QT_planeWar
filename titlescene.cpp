#include "titlescene.h"
#include <QPushButton>
#include <QDebug>
#include <QMessageBox>
#include "mypushbutton.h"
#include "chooselevel.h"

titleScene::titleScene(QWidget *parent)
    : QWidget(parent)
{

    // 窗口配置
    // 可选功能：等比例缩放
    width = 480;
    height = 850;
    setFixedSize(width, height);
    setWindowTitle("雷霆战机");
    setWindowIcon(QPixmap(":/res/image/image_Scene/logo.png"));

    // 配置按钮
    // 可选功能：按钮图标设置（已实现）
    MyPushButton* Start_button = new MyPushButton(this, ":/res/image/image_Scene/start_button.png");
    MyPushButton* Info_button = new MyPushButton(this, ":/res/image/image_Scene/information_button.png");
    MyPushButton* Exit_button = new MyPushButton(this, ":/res/image/image_Scene/exit_button.png");

    //设置按钮图片尺寸和位置
    Start_button->setIconSize(QSize(Start_button->width()/1, Start_button->height()/1));
    Info_button->setIconSize(QSize(Info_button->width()/1, Info_button->height()/1));
    Exit_button->setIconSize(QSize(Exit_button->width()/1, Exit_button->height()/1));
    Start_button->move(width/1.9-Start_button->width()/2, 330);
    Info_button->move(width/1.9-Info_button->width()/2, 450);
    Exit_button->move(width/1.9-Exit_button->width()/2, 570);

    cl = NULL;

    // 关联"Start"按钮信号
    // 可选功能：不同难度（已实现）
    // connect(Start_button, &QPushButton::clicked, this, &myWidget::Start);
    connect(Start_button, &QPushButton::clicked, this, [=](){
        this->hide();
        if(cl == NULL)
        {
            cl = new ChooseLevel(this);
        }
        cl->setGeometry(this->geometry());
        cl->show();
    });

    // 显示信息
    connect(Info_button, &QPushButton::clicked, this, &titleScene::Info);


    // 退出游戏的接口，点击“Exit”按钮实现Exit()功能
    connect(Exit_button, &QPushButton::clicked, this, &titleScene::Exit);
}

titleScene::~titleScene()
{
    if(cl != NULL)
    {
        delete cl;
    }
}


// 开始游戏的接口，点击“Start”按钮实现函数功能
void titleScene::Start()
{


}

// 项目开发信息显示
void titleScene::Info()
{
    QMessageBox::information(this, "开发信息", "Qt version: 5.12.2\n"
                                           "Group Members：张艺 曾志炜 徐梦达\n"
                                           "2022 June");

}

// 退出游戏确认
void titleScene::Exit()
{
    if(QMessageBox::question(this, "Attention", "Do you really want to exit?",
                             QMessageBox::Yes|QMessageBox::Cancel, QMessageBox::Cancel) == QMessageBox::Yes)
    {
        QWidget::close();
    }
    else
    {

    }

}

void titleScene::backToTitle()
{
    if(cl != NULL)
    {
        delete cl;
    }
}

void titleScene::paintEvent(QPaintEvent *)
{
    // 背景图片
    QPainter painter(this);
    QPixmap main_bg;
    main_bg.load(":/res/image/image_Scene/bg_menu.jpg");
    painter.drawPixmap(0, 0, width, height, main_bg);

    // 插入标题
    main_bg.load(":/res/image/image_Scene/title.png");
    painter.drawPixmap(50, 50, 380, 200, main_bg);

    // 版本号（可删去）
    painter.setPen(Qt::red);
    painter.setFont(QFont("Arial", 14, 3));
    painter.drawText(width-150, height-45, width, height, 1, "Version 1.0");
}



