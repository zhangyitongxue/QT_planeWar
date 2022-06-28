#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <QLabel>
#include <QString>
#include <QPixmap>
#include <QDebug>
#include "mydefine.h"

class Projectile : public QLabel
{
    Q_OBJECT
public:
    enum class Proj_Type{
        PROJ_BULLET,
        PROJ_MISSILE
    };
    enum class DIR{
        RIGHT = 0,
        RIGHT_AND_UP = 1,
        UP = 2,
        LEFT_AND_UP = 3,
        LEFT = 4,
        LEFT_AND_DOWN = 5,
        DOWN = 6,
        RIGHT_AND_DOWN = 7,
    };

    // explicit Projectile(QWidget *parent = nullptr);
    Projectile(Proj_Type t, DIR D, bool CreatedByPlayer);
    // ~Projectile();

    bool belongToPlayer();

    int getDamage();

    Proj_Type getType();

    void updatePos();

    bool isActive();

    void setActive(bool );
private:
    const double dx[8] = {1,  0.7,  0, -0.7, -1, -0.7,  0, 0.7};
    const double dy[8] = {0, -0.7, -1, -0.7,  0,  0.7,  1, 0.7};
    int dir;                    // 发射方向
    bool isCreatedByPlayer;
    Proj_Type type;
    QString imgPath;            // 图像路径
    int Damage;                 // 伤害
    int Speed;
    bool Active;                // false表示需要销毁

public:
signals:

public slots:
};

#endif // PROJECTILE_H
