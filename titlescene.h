#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>
#include <QPainter>

class ChooseLevel;

class titleScene : public QWidget
{
    Q_OBJECT

public:
    // 背景加载参数
    int posX = 0;
    int width, height;
    titleScene(QWidget *parent = nullptr);
    ~titleScene();

    // 主界面按钮事件和绘图事件
    void Start();
    void Info();
    void Exit();
    void paintEvent(QPaintEvent*);
    void backToTitle();
private:
    ChooseLevel * cl;

};


#endif // MYWIDGET_H
