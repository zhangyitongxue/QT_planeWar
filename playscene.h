#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include <QKeyEvent>
#include <QDebug>
#include <QMouseEvent>
#include <QMainWindow>
#include <mypushbutton.h>
#include <QSound>
#include <QTimer>
#include <QRect>
#include <QFont>
#include <QVector>
#include "plane.h"
#include "projectile.h"
#include "enemyplane.h"
#include "mydefine.h"
#include "titlescene.h"
#include "chooselevel.h"

class ChooseLevel;

class playScene : public QMainWindow
{
    Q_OBJECT
public:
    explicit playScene(QString name_, ChooseLevel * chooseScene,QWidget *parent = nullptr);
    ~playScene();
    QString name;

    // 背景绘制参数
    int picPosY = 0;
    int nextY = 0;

    // 画图和计时事件
    void paintEvent(QPaintEvent*);
    void timerEvent(QTimerEvent* event);

//    // 窗口初始化
//    void initialize();

    // 游戏开始，计时开始
    void Play();

    // 场景内各个飞行物的位置和状态更新
    void updatePos();

    // 敌机生成函数
    void enemyCreate();

    // player 状态buff的更新
    void updateBuff();

    // 场景内飞机的攻击
    void planeAttack();

    // 碰撞检测
    void crashDetectInScene();

    // 清除场景中的垃圾
    void trashClear();

    // 设置难度
    void setLevel(int level);

    // 重写键盘按键按下事件
    void keyPressEvent(QKeyEvent *ev);

    // 重写鼠标按键时间
    void mouseMoveEvent(QMouseEvent *ev);

private:
    // HP显示更新
    void showHP();

    // 展示的HP
    int HPValueShowed;

    // 判断游戏是否结束
    void isGameOver();

    ChooseLevel * cl;

    // 玩家
    Plane * player;

    // 计时器
    QTimer sceneTimer;

    // 场景中的发射物
    QVector< Projectile* > projInScene;

    // 场景中的敌人
    QVector< enemyPlane* > enemInScene;

    // 背景循环音乐
    QSound* bgm;

    QSound * planeDeath;

    QLabel * imag_HP;

    QLabel * imag_HPPoint[PLAYER_HP];

    int enemyCreateTime;

    int enemLevel;

    const int levelIncreasedHP = 2;

signals:

};

#endif // PLAYSCENE_H
