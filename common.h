#pragma once
#include <iostream>
#include <ctime>
#include <graphics.h>
#include <Windows.h>
#include <memory>
#include <conio.h>
#include <cstdlib>
#include <string>
#include <vector>
#include <deque>
#include <list>
#include <forward_list>
#include <array>
#include <map>
#include <set>
#include <algorithm>
#include <functional>
#include <numeric>
#include <stack>
#include <queue>
#include <utility>
using namespace std;

#define WINDOWS_GAME_W 720
#define WINDOWS_GAME_H 800
//宏观数据
#define WINDOWS_W 560
#define WINDOWS_H 800

//飞机移动速度
#define Plane_speed 8

#define Enemy1_speed 5
#define Enemy2_speed 10
#define Enemy3_speed 3
#define Enemy4_speed 2


#define Enemy_bullet_speed 6

//数据
#define My_Plane_Blood 400

//我的攻击伤害

//普通子弹 
#define My_Bullet1_Shanghai 2		
//冰子弹
#define My_Bullet2_Shanghai 4
//火子弹
#define My_Bullet3_Shanghai 5
//烟花弹
#define My_Bullet4_Shanghai 6
//终极子弹
#define My_Bullet5_Shanghai 8
//普通子弹速度
#define Bullet_speed 10
//冰子弹速度
#define Ice_and_Fire_Bullet_speed 15
//烟花弹速度


//敌人的初始血量和子弹伤害
#define Enemy1_Blood 2
#define Enemy2_Blood 3
#define Enemy3_Blood 12
#define Enemy4_Blood 20
#define BOSS_BLOOD 400

#define Enemy1_Bullet_Shanghai 1
#define Enemy2_Bullet_Shanghai 2
#define Enemy3_Bullet_Shanghai 3
#define Boss激光伤害 1
#define My激光伤害 1

//同屏最大敌机数量
#define enemy_num 10

//我方最大子弹数量
#define Max_biu 15

#define Tools_Speed 5



//敌机分数
#define Little_plane 100
#define Mid_plane 150
#define Big_plane 300
#define Biggg_plane 500;



#define MAX_Boom 10
static int score = 0;
#define GAME_OVER true
#define GAME_NOT_OVER false

#define Enemy1_Pengzhuang_Shanghai 5
#define Enemy2_Pengzhuang_Shanghai 20
#define Enemy3_Pengzhuang_Shanghai 10
#define Enemy4_Pengzhuang_Shanghai 10

#define 爆炸帧率 6

#define 标志帧率 80

#define 持续性道具最大帧率 500

#define 激光持续时间 3
#define 道具持续时间（可修改） 3