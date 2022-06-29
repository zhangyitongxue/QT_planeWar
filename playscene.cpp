#include "playscene.h"

playScene::playScene(QString name_, ChooseLevel * chooseScene, QWidget *parent) :
    QMainWindow(parent),
    name(name_)
{
    cl = chooseScene;

    // 窗口配置
    // 可选功能：等比例缩放
    setFixedSize(SCENE_WIDTH, SCENE_HEIGHT);
    setWindowTitle(name);
    setWindowIcon(QPixmap(":/res/image/image_Scene/logo.png"));

    // 关卡音效
    bgm = new QSound(":/res/audio/bgm.wav", this);
    bgm->play();
    bgm->setLoops(-1);


    // 计时器：20ms
    // 改变帧率
    startTimer(GAME_INTERVAL);

    // 配置按钮
    // 可选功能：按钮图标设置（已实现）
    MyPushButton* Back_button = new MyPushButton(this, ":/res/image/image_Scene/level_back.png");
    Back_button->setIconSize(QSize(Back_button->width()/1, Back_button->height()/1));
    Back_button->move(this->width() - Back_button->width()/1 - 2, this->height() - Back_button->height()/1 - 4);

    // 关联"BACK"按钮信号
    connect(Back_button, &QPushButton::clicked, this, [=](){
        bgm->stop();
        this->hide();

        cl->setGeometry(this->geometry());
        cl->show();
        cl->backToChoose();
    });

    // 敌机坠毁音效
    planeDeath = new QSound(SOUND_PATH_PLANE_DEATH, this);

    // 敌人属性
    enemyCreateTime = 0;
    enemLevel = 0;

    // 生成 player
    player = new Plane(QString(PLAYER_IMAGE_PATH), PLAYER_HP, true);
    player->setParent(this);
    player->setTarPos(SCENE_WIDTH/2, SCENE_HEIGHT/2);

    // HP 显示
    QPixmap pix_Hp;
    pix_Hp.load(HP_IMAGE_PATH);

    imag_HP = new QLabel(this);
    imag_HP->setPixmap(pix_Hp);
    imag_HP->setFixedSize(pix_Hp.width(), pix_Hp.height());
    imag_HP->move(0, this->height()-imag_HP->height());
    imag_HP->show();

    QPixmap pix_HPPoint;
    pix_HPPoint.load(HPPOINT_IMAGE_PATH);
    int pw = pix_HPPoint.width();
    int ph = pix_HPPoint.height();
    for(int i = 0; i < PLAYER_HP; ++i){
        imag_HPPoint[i] = new QLabel(this);
        imag_HPPoint[i]->setPixmap(pix_HPPoint);
        imag_HPPoint[i]->setFixedSize(pw, ph);
        imag_HPPoint[i]->move(imag_HP->width() + i*pw, this->height() - ph);
        imag_HPPoint[i]->show();
    }
    HPValueShowed = PLAYER_HP;  // 刚开始为满血

    // 游戏运行的Timer设置
    sceneTimer.setInterval(GAME_INTERVAL);

    Play(); // 游戏开始运行
}


playScene::~playScene()
{
    if(player != NULL){
        delete player;
    }

    int l1 = enemInScene.size();
    for(int i = 0; i < l1; ++i){
        delete enemInScene[i];
    }

    int l2 = projInScene.size();
    for(int i = 0; i < l2; ++i){
        delete projInScene[i];
    }

    if(qs != NULL){
        delete qs;
    }

    if(planeDeath != NULL){
        delete planeDeath;
    }
}

void playScene::paintEvent(QPaintEvent *)
{
    int w = this->width();
    int h = this->height();

    // 背景图片
    QPainter painter(this);
    QPixmap main_bg;
    main_bg.load(":/res/image/image_Scene/level1_map.jpg");
    QRect q1(0, (picPosY >= 0) ? picPosY : 0, w, h);
    QRect q2(0, nextY, w, h);
    painter.drawPixmap(q2, main_bg, q1);
    QRect q3(0, 1498 - nextY, w, nextY);
    QRect q4(0, 0, w, nextY);
    painter.drawPixmap(q4, main_bg, q3);

}

void playScene::timerEvent(QTimerEvent *event)
{
    // 改变影响背景滚动速度
    picPosY -= 2;

    // 越界时启动双画笔渲染达到单张图片首尾循环的效果
    if(picPosY < 0)
    {
        nextY = -picPosY;
    }

    if(picPosY < -this->height())
    {
        picPosY = 0;
        picPosY = 1498 - this->height();
    }

    repaint();
}

void playScene::Play()
{
    // 播放音乐


    // 游戏开始
    sceneTimer.start();

    // 监听定时器的信号
    connect(&sceneTimer, &QTimer::timeout, this,[=](){

        this->updatePos();

        this->enemyCreate();

        this->updateBuff();

        this->crashDetectInScene();

        this->planeAttack();

        this->trashClear();

        this->showHP();

        this->isGameOver();

    });
}


void playScene::updatePos()
{
    // 玩家更新位置
    player->updatePos();


    // 敌人更新位置
    int enemVLen = enemInScene.size();
    for(int i = 0; i < enemVLen; ++i)
    {
        int posX = enemInScene[i]->x();
        int posY = enemInScene[i]->y();
        int w = enemInScene[i]->width();
        int h = enemInScene[i]->height();
        if( posX >= 0 - w && posX <= this->width() && posY >= 0 - h && posY <= this->height() )
        {
            enemInScene[i]->updatePos();
        }
        else { // 超出范围的设为非active
            enemInScene[i]->setActive(false);
        }
    }

    // 发射物更新位置
    int projVLen = projInScene.size();
    for(int i = 0; i < projVLen; ++i)
    {
        int posX = projInScene[i]->x();
        int posY = projInScene[i]->y();
        int w = projInScene[i]->width();
        int h = projInScene[i]->height();
        if( posX >= 0 - w && posX <= this->width() && posY >= 0 - h && posY <= this->height() )
        {
            projInScene[i]->updatePos();
        }
        else { // 超出范围的设置为无效
            projInScene[i]->setActive(false);

        }
    }

}

void playScene::updateBuff()
{
    if(player->invincibleTime > 0)
    {
        player->invincibleTime -= GAME_INTERVAL;
        if(player->invincibleTime < 0){
            player->invincibleTime = 0;
        }
    }

    player->updateImage();
}

// 检测两个QLabel是否发生了碰撞
bool crashDetectForLabel(const QLabel * L1, const QLabel * L2)
{
    int x1 = L1->x();
    int y1 = L1->y();
    int w1 = L1->width();
    int h1 = L1->height();

    int x2 = L2->x();
    int y2 = L2->y();
    int w2 = L2->width();
    int h2 = L2->height();

    // 无奈只能采取矩形检测的方法，非常的垃圾
    if( (x1 >= x2 && x1 <= x2+w2) || (x1+w1 >= x2 && x1+w1 <= x2+w2) )
    {
        if( (y1 >= y2 && y1 <= y2+h2) || (y1+h1 >= y2 && y1+h1 <= y2+h2) )
        {
            return true;
        }
    }

    return false;
}

void playScene::crashDetectInScene()
{
    int projVLen = projInScene.size();
    int enemVLen = enemInScene.size();

    // 先检测敌人和palyer对应的飞机是否发生碰撞
    if(player->invincibleTime == 0) {
        for(int enemIndex = 0; enemIndex < enemVLen; ++enemIndex) {
            if(crashDetectForLabel(player, enemInScene[enemIndex])){
                enemInScene[enemIndex]->Hurt(1);
                player->Hurt(1);
                break;

            }
        }
    }


    for(int projIndex = 0; projIndex < projVLen; ++projIndex) //遍历发射物
    {
        if(projInScene[projIndex]->belongToPlayer()) {
            for(int enemIndex = 0; enemIndex < enemVLen; ++enemIndex) {
                if(crashDetectForLabel(projInScene[projIndex], enemInScene[enemIndex]))
                {
                    projInScene[projIndex]->setActive(false);
                    int Damage = projInScene[projIndex]->getDamage();
                    enemInScene[enemIndex]->Hurt(Damage);
                    break;
                }
            }
        }
        else {
            if(player->invincibleTime == 0){
                if(crashDetectForLabel(projInScene[projIndex], player))
                {
                    projInScene[projIndex]->setActive(false);
                    int Damage = projInScene[projIndex]->getDamage();
                    player->Hurt(Damage);

                }
            }
        }
    }
}

// 清除剩余的垃圾
void playScene::trashClear()
{
    for(auto i = projInScene.begin(); i != projInScene.end(); )
    {
        if( ! (*i)->isActive() ){
            Projectile * p = *i;
            delete p;
            p = 0;
            projInScene.erase(i);
        }
        else {
            ++i;
        }
    }

    for(auto i = enemInScene.begin(); i != enemInScene.end(); )
    {
        if( !(*i)->isActive() )
        {
            enemyPlane * p = *i;
            delete p;
            p = 0;
            enemInScene.erase(i);
            continue;
        }
        else if( (*i)->getHP() <= 0 ){
            enemyPlane * p = *i;
            delete p;
            p = 0;
            enemInScene.erase(i);

            //  播放音效：敌人死亡
            planeDeath->play();
        }
        else {
            ++i;
        }
    }
}

// 飞机生成发射物
void playScene::planeAttack()
{
    Projectile * p = player->Fire();
    if(p != NULL){
        p->setParent(this);
        p->show();
        projInScene.push_back(p);
    }

    int tail = enemInScene.length();
    for(int i = 0; i < tail; ++i){
        Projectile * p = enemInScene[i]->Fire();
        if(p != NULL){
            p->setParent(this);
            p->show();
            projInScene.push_back(p);
        }
    }

}


void playScene::enemyCreate()
{
    if(enemyCreateTime < ENEMY_CREATE_INTERVAL){
        enemyCreateTime++;
        return;
    }
    else {
        enemyCreateTime = 0;

        // 大概思路：生成敌人的位置分为三类：左边生成、右边生成、上边生成
        int dir = rand() % 3; // 三个方向
        int enemyTypeInt = rand() % 3;     // 暂时我只想弄三种敌人
        enemyPlane::Enemy_Type t;
        enemyPlane::SpeedGrade s;

        switch(enemyTypeInt){
        case 0:
            t = enemyPlane::Enemy_Type::ENEMY_NO_PROJ;
            s = enemyPlane::SpeedGrade::FAST;
            break;
        case 1:
            t = enemyPlane::Enemy_Type::ENEMY_BULLET;
            s = enemyPlane::SpeedGrade::MEDIUM;
            break;
        case 2:
            t = enemyPlane::Enemy_Type::ENEMY_MISSLE;
            s = enemyPlane::SpeedGrade::SLOW;
            break;
        }

        if(dir == 0){ // 上边生成，往下移动
            enemyPlane::DIR d = enemyPlane::DIR::DOWN;

            enemyPlane * enem1 = new enemyPlane(
                        t,
                        ENEMY_INIT_HP + enemLevel * levelIncreasedHP,
                        d,
                        s
                        );
            enem1->setParent(this);
            enem1->show();
            enemInScene.push_back(enem1);

            int bornX, bornY;

            int availableWidth = this->width() - enem1->width();
            bornX = rand() % availableWidth;
            bornY = 2 - enem1->height();

            enem1->move(bornX, bornY);
        }
        else if(dir == 1){ // 左边生成，右下移动
            enemyPlane::DIR d = enemyPlane::DIR::RIGHT_AND_DOWN;

            enemyPlane * enem1 = new enemyPlane(
                        t,
                        ENEMY_INIT_HP + enemLevel * levelIncreasedHP,
                        d,
                        s
                        );
            enem1->setParent(this);
            enem1->show();
            enemInScene.push_back(enem1);

            int bornX, bornY;

            int availableHeight = this->height()/2;
            bornX = 1 - enem1->width();
            bornY = rand() % availableHeight + 1 - enem1->height();

            enem1->move(bornX, bornY);

        }
        else if(dir == 2){ // 右边生成， 左下移动
            enemyPlane::DIR d = enemyPlane::DIR::LEFT_AND_DOWN;

            enemyPlane * enem1 = new enemyPlane(
                        t,
                        ENEMY_INIT_HP + enemLevel * levelIncreasedHP,
                        d,
                        s
                        );
            enem1->setParent(this);
            enem1->show();
            enemInScene.push_back(enem1);

            int bornX, bornY;

            int availableHeight = this->height()/2;
            bornX = this->width() - 1;
            bornY = rand() % availableHeight + 1 - enem1->height();

            enem1->move(bornX, bornY);
        }
    }
}

void playScene::setLevel(int level)
{
    enemLevel = level;
}

void playScene::showHP()
{
    int playerHP = player->getHP();
    if(player == NULL || playerHP == HPValueShowed){
        return;
    }
    else if(player != NULL && playerHP != HPValueShowed){
        HPValueShowed = playerHP;
        for(int i = 0; i < PLAYER_HP; ++i){
            if(i+1 <= playerHP){
                imag_HPPoint[i]->show();
            }
            else {
                imag_HPPoint[i]->hide();
            }
        }
    }
}

void playScene::isGameOver()
{
    if(player != NULL && player->getHP() <= 0)
    {
        qs->stop();
        sceneTimer.stop();

        QSound * s = new QSound(SOUND_PATH_GAME_OVER);
        s->setParent(this);
        s->play();

        QLabel * gameOverImage = new QLabel(this);
        QPixmap p;
        p.load(GAME_OVER_IMAGE_PATH);
        gameOverImage->setPixmap(p);
        gameOverImage->setFixedSize(p.width(), p.height());

        int bornX = this->width()/2 - gameOverImage->width()/2;
        int bornY = this->height()/2 - gameOverImage->height()/2;
        gameOverImage->move(bornX, bornY);
        gameOverImage->show();

        return;
    }
    else {
        return;
    }
}

void playScene::keyPressEvent(QKeyEvent *ev)
{
    if(player != NULL)
    {
        if(ev->key() == Qt::Key_W ){ // 上
            int xx = player->x();
            int yy = player->y() - PLAYER_SPEED;
            if(yy >= 0 && yy <= this->height()){
                player->setTarPos(xx, yy);
            }
        }
        else if(ev->key() == Qt::Key_S ){ // 下
            int xx = player->x();
            int yy = player->y() + PLAYER_SPEED;
            if(yy >= 0 && yy + player->height() <= this->height()){
                player->setTarPos(xx, yy);
            }
        }
        else if(ev->key() == Qt::Key_A){ // 左
            int xx = player->x() - PLAYER_SPEED;
            int yy = player->y();
            if(xx >= 0 && xx + player->width() <= this->width()){
                player->setTarPos(xx, yy);
            }
        }
        else if(ev->key() == Qt::Key_D ){ // 右
            int xx = player->x() + PLAYER_SPEED;
            int yy = player->y();
            if(xx >= 0 && xx + player->width() <= this->width()){
                player->setTarPos(xx, yy);
            }
        }
    }
}

void playScene::mouseMoveEvent(QMouseEvent *ev)
{
    if(player != NULL)
    {
        int ori_x = player->x();
        int ori_y = player->y();

        int xx = ev->x() - player->width()/2;
        int yy = ev->y() - player->height()/2;

        int tar_x;
        int tar_y;

        if(xx >= 0 && xx + player->width() <= this->width())
        {
            tar_x = xx;
        }
        else {
            tar_x = ori_x;
        }
        if(yy >= 0 && yy + player->height() <= this->height())
        {
            tar_y = yy;
        }
        else {
            tar_y = ori_y;
        }

        player->setTarPos(tar_x, tar_y);
    }
}
