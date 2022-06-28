#include "chooselevel.h"

ChooseLevel::ChooseLevel(titleScene * title ,QWidget *parent) :
    QMainWindow(parent)
{
    ts = title;

    // 窗口配置
    // 可选功能：等比例缩放
    width = 480;
    height = 850;
    setFixedSize(width, height);
    setWindowTitle("选择难度");
    setWindowIcon(QPixmap(":/res/image/image_Scene/logo.png"));

    // 配置按钮
    // 可选功能：按钮图标设置
    MyPushButton* L1_button = new MyPushButton(this, ":/res/image/image_Scene/easy.png");
    MyPushButton* L2_button = new MyPushButton(this, ":/res/image/image_Scene/medium.png");
    MyPushButton* L3_button = new MyPushButton(this, ":/res/image/image_Scene/hard.png");
    MyPushButton* Back_button = new MyPushButton(this, ":/res/image/image_Scene/choose_level_back.png");

    //设置按钮图片尺寸和位置
    L1_button->setIconSize(QSize(L1_button->width()/1, L1_button->height()/1));
    L2_button->setIconSize(QSize(L2_button->width()/1, L2_button->height()/1));
    L3_button->setIconSize(QSize(L3_button->width()/1, L3_button->height()/1));
    L1_button->move(width/1.9 - L1_button->width()/2, 330);
    L2_button->move(width/1.9 - L2_button->width()/2, 450);
    L3_button->move(width/1.9 - L3_button->width()/2, 570);


    Back_button->setIconSize(QSize(Back_button->width()/1, Back_button->height()/1));
    Back_button->move(width - Back_button->width()/1 - 3, height - Back_button->height()/1 - 5);

    // 关联难度按钮信号
    connect(L1_button, &QPushButton::clicked, this, [=](){
        this->hide();
        ps = new playScene("Easy", this);
        //------------------------------------
        // 在这里设定Level_1的变量数值，以改变难度
        ps->setLevel(0);
        //------------------------------------
        ps->setGeometry(this->geometry());
        ps->show();
    });

    connect(L2_button, &QPushButton::clicked, this, [=](){
        this->hide();
        ps = new playScene("Medium", this);
        //------------------------------------
        // 在这里设定Level_1的变量数值，以改变难度
        ps->setLevel(1);
        //------------------------------------
        ps->setGeometry(this->geometry());
        ps->show();
    });

    connect(L3_button, &QPushButton::clicked, this, [=](){
        this->hide();
        ps = new playScene("Hard", this);
        //------------------------------------
        // 在这里设定Level_1的变量数值，以改变难度
        ps->setLevel(2);
        //------------------------------------
        ps->setGeometry(this->geometry());
        ps->show();
    });


    // 关联"BACK"按钮信号
    connect(Back_button, &QPushButton::clicked, this, [=](){
        this->hide();

        ts->setGeometry(this->geometry());
        ts->show();
    });

}


ChooseLevel::~ChooseLevel()
{
    if(ps != NULL)
    {
        delete ps;
    }
}

void ChooseLevel::paintEvent(QPaintEvent *)
{
    // 背景图片
    QPainter painter(this);
    QPixmap main_bg;
    main_bg.load(":/res/image/image_Scene/choose_level.jpg");
    painter.drawPixmap(0, 0, width, height, main_bg);
    // 插入标题
    main_bg.load(":/res/image/image_Scene/title.png");
    painter.drawPixmap(50, 50, 380, 200, main_bg);
}

void ChooseLevel::backToChoose()
{
    if(ps != NULL)
    {
        delete ps;
    }
}
