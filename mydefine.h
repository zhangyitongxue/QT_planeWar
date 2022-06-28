#ifndef MYDEFINE_H
#define MYDEFINE_H

#include <QString>

///////////////  场景基础设置 ////////////////////

#define SCENE_WIDTH 480     // 场景宽度

#define SCENE_HEIGHT 850    // 场景高度

#define GAME_INTERVAL 16    // 帧率为62.5

#define GAME_OVER_IMAGE_PATH ":/res/image/image_Scene/gameOver.jpg"  // 游戏结束图像

#define HP_IMAGE_PATH ":/res/image/image_Scene/HP.png"              // HP提示 图像

#define HPPOINT_IMAGE_PATH ":/res/image/image_Scene/HPPoint.png"    // HP点 图像

////////////////  玩家  /////////////////////

#define PLAYER_HP 4

#define PLAYER_IMAGE_PATH ":/res/image/image_PlaneAndProj/plane/player.png"        // 玩家飞机图像

#define PLAYER_SPEED 20      // 玩家飞机移动速度

#define PLAYER_INVINCIBLE_TIME 1000         // 玩家无敌时间，单位为毫秒

#define PLAYER_INVINCIBLE_IMAGE_PATH ":/res/image/image_PlaneAndProj/plane/invinciable.png" // 无敌图像

#define PLAYER_FIRE_INTERVAL 8              // 玩家开火间隔，单位是帧数

//////////////   敌人   //////////////////////

#define ENEMY_NO_PROJ_IMAGE_PATH ":/res/image/image_PlaneAndProj/plane/enemy_no_proj_Small.png"

#define ENEMY_BULLET_IMAGE_PATH ":/res/image/image_PlaneAndProj/plane/enemy_bullet_Small.png"

#define ENEMY_MISSILE_IMAGE_PATH ":/res/image/image_PlaneAndProj/plane/enemy_missile_Small.png"

const QString enemImgP[3] = {           // 敌人图像资源路径预先处理
    ENEMY_NO_PROJ_IMAGE_PATH,
    ENEMY_BULLET_IMAGE_PATH,
    ENEMY_MISSILE_IMAGE_PATH
};

#define ENEMY_INIT_HP 2              // 敌人初始HP值

#define ENEMY_SPEED_SLOW 4          // 敌人移动速度

#define ENEMY_SPEED_MEDIUM 5

#define ENEMY_SPEED_FAST 6

#define ENEMY_FIRE_INTERVAL 50           // 敌人开火间隔，单位是帧数

////////////////  发射物  //////////////////

#define PROJ_PLAYER_SPEED 10        // 玩家发射物移动速度

#define PROJ_ENEMY_SPEED 6          // 敌人发射物移动速度

#define PROJ_PLAYER_BULLET_PATH ":/res/image/image_PlaneAndProj/projectile/bullet_player.png"     // 玩家子弹的资源图片路径

#define PROJ_ENEMY_BULLET_PATH ":/res/image/image_PlaneAndProj/projectile/bullet_enemy.png"      // 敌人子弹的资源图片路径

#define PROJ_PLAYER_MISSILE_PATH ":/res/image/image_PlaneAndProj/projectile/missle_player.png"                 // 玩家导弹的资源图片路径

#define PROJ_ENEMY_MISSILE_PATH ":/res/image/image_PlaneAndProj/projectile/missle_enemy.png"                  // 敌人导弹资源图片

#define PROJ_BULLET_DAMAGE 1        // 子弹伤害

#define PROJ_MISSILE_DAMAGE 2       // 导弹伤害

//////////////// 音效路径 /////////////////////

#define SOUND_PATH_PLAYER_FIRE_BULLET ":/res/audio/bullet_cast.wav"      // 玩家发射子弹的音效

#define SOUND_PATH_PLAYER_FIRE_MISSILE ":/res/audio/missle_cast.wav"       // 玩家发射导弹的音效

#define SOUND_PATH_PLANE_DEATH ":/res/audio/enemy_break.wav"          // 飞机死亡

#define SOUND_PATH_PLANE_HIT ":/res/audio/hit.wav"            // 飞机受击

#define SOUND_PATH_GAME_OVER ":/res/audio/game_over.wav"           // 游戏结束

#define SOUND_PATH_BGM ":/res/audio/bgm.wav"

///////////////// 敌人生成相关参数 //////////////////////

#define ENEMY_CREATE_INTERVAL 70              // 敌人生成间隔，单位是帧数

#endif // MYDEFINE_H
