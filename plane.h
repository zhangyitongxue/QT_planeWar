#ifndef PLANE_H
#define PLANE_H

#include <QLabel>
#include <QString>
#include <QPixmap>
#include <QDebug>
#include <QWidget>
#include <QSound>
#include "mydefine.h"
#include "projectile.h"


class Plane : public QLabel
{
    Q_OBJECT
public:
    // explicit Plane(QWidget *parent = nullptr);
    Plane(  QString , int, bool playerFlag = false,
            Projectile::Proj_Type projType = Projectile::Proj_Type::PROJ_BULLET
            );

    virtual ~Plane();

    int getHP();
    int setHP(int newHP);

    int TarX();
    int TarY();
    void setTarPos(int x, int y);

    virtual void updatePos();

    virtual void Hurt(int Damage);

    virtual Projectile * Fire();

    virtual void updateImage();

    int invincibleTime;       // 无敌时间

protected:
    int tar_X;
    int tar_Y;
    QString imgPath;        // 飞机的图像路径
    int HP;                 // 飞机血量
    bool isPlayer;          // 是否是玩家控制的飞机

    QPixmap idleImage;      // 默认形象
    QPixmap invincibleImage; // 无敌形象
    bool isIdleImage;       // 处于默认形象

    Projectile::Proj_Type pType; // 发射物类型
    int weaponGrade;        // 武器等级
    int fireTime;           // 用这个来判断是否应该进行一次发射
    QSound * planeFireBullet;
    QSound * planeFireMissile;
    QSound * planeHit;

public:

signals:

public slots:
};

#endif // PLANE_H
