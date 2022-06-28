#include "plane.h"

//Plane::Plane(QWidget *parent) : QLabel(parent)
//{

//}

Plane::Plane(
        QString p, int hp, bool playerFlag,
        Projectile::Proj_Type projType
     )
{
    // 加载飞机图像
    bool ret = idleImage.load(p);
    if(!ret){
        qDebug() << p << "飞机图像加载失败";
    }
    else {
        this->setFixedSize(idleImage.width(), idleImage.height());
        // this->setStyleSheet("QLabel{border:0px;}");
        this->setPixmap(idleImage);
    }

    bool r = invincibleImage.load(PLAYER_INVINCIBLE_IMAGE_PATH);
    if(!r){
        qDebug() << PLAYER_INVINCIBLE_IMAGE_PATH << "Load Failed";
    }

    // 加边框，方便玩家躲避碰撞，但是很丑 TaT
    this->setFrameShape(QFrame::Box);
    this->setFrameShadow(QFrame::Sunken);

    // 基础属性的设置
    isIdleImage = true;     // 是否是默认形象
    imgPath = p;            // 图像路径
    HP = hp;                // 生命值
    isPlayer = playerFlag;  // 是否是玩家
    invincibleTime = 0;     // 剩余无敌时间
    weaponGrade = 1;        // 武器等级
    pType = projType;       // 发射物类型
    fireTime = 0;           // 是否应该进行发射的判断标志

    planeFireBullet = new QSound(SOUND_PATH_PLAYER_FIRE_BULLET, this);
    planeFireMissile = new QSound(SOUND_PATH_PLAYER_FIRE_MISSILE, this);
    planeHit = new QSound(SOUND_PATH_PLANE_HIT, this);

}

Plane::~Plane()
{
    delete planeFireBullet;
    delete planeFireMissile;
    delete planeHit;
}

int Plane::TarX()
{
    return tar_X;
}

int Plane::TarY()
{
    return tar_Y;
}

void Plane::setTarPos(int x, int y)
{
    tar_X = x;
    tar_Y = y;
}

int Plane::getHP()
{
    return HP;
}

int Plane::setHP(int newHP)
{
    HP = newHP;
    return HP;
}

void Plane::updatePos()
{
    this->move(tar_X, tar_Y);
}

void Plane::updateImage()
{
    if(invincibleTime > 0 && isIdleImage){
        this->setPixmap(invincibleImage);
        isIdleImage = false;
    }
    else if(invincibleTime <= 0 && !isIdleImage){
        this->setPixmap(idleImage);
        isIdleImage = true;
    }
}

void Plane::Hurt(int Damage)
{
    HP -= Damage;

    // qDebug() << QString("IsPlayer:%1  Hurt! Remain HP:%2").arg(isPlayer).arg(HP);

    // 播放音效
    planeHit->play();

    if(isPlayer)
    {
        invincibleTime = PLAYER_INVINCIBLE_TIME;
    }
}

// 事实上这个函数就是专门给player用的，enemyplane的Fire函数还会进行重写
Projectile * Plane::Fire()
{
    if(fireTime < PLAYER_FIRE_INTERVAL){
        fireTime++;
        return NULL;
    }
    else {
        fireTime = 0;

        // 发射物类型和创建的阵营归属
        Projectile::Proj_Type t = this->pType;
        bool createdByPlayer = true;
        Projectile::DIR d = Projectile::DIR::UP;

        Projectile * p = new Projectile(t, d, createdByPlayer);

        int pX, pY;

        pX = this->x() + this->width()/2 - p->width()/2 ;
        pY = this->y() - p->height();

        // 调整发射物的起始位置
        p->move(pX, pY);

        // 播放音效
        if(this->pType == Projectile::Proj_Type::PROJ_BULLET){
            planeFireBullet->play();
        }
        else if(this->pType == Projectile::Proj_Type::PROJ_MISSILE){
            planeFireMissile->play();
        }
        return p;
    }
}
