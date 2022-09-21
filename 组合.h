#pragma once
#include "对象.h"

class Game
{
public:
	enum 阶段 { 阶段一, 阶段二, 阶段三, 阶段四, 阶段五, 阶段六, 阶段七, 阶段八, BOSS阶段 };
	Game();
	bool Play_Game();								//游戏主循环
	void Draw();									//绘制工作
	void Draw_Other();								//其他物品的绘制
	void 持续性动画的绘制();
	void 持续性动画的绘制结束();
	void Create_Bullet();							//创建子弹
	void Create_Enemy();							//创建敌人
	void Enemy_GrowUp();							//敌军的随时间升级
	
	void Bullet_To_Enemy();							//攻击敌人
	void Bullet_To_Me();							//敌人攻击我方
	void Create_Tools();							//道具的产生
	void Tools_Good();								//道具效果
	void BoomZha(Object& baozha);					//爆炸
	void ConrtolFPS(int start_time);				//帧率控制
	bool Game_Over();								//判断游戏结束
	void isWin();

	bool Bullet_Pengzhuang(Object& a, Object& b);	//子弹的碰撞检测
	bool Plane_Pengzhuang(Object& a, Object& b);	//敌机的碰撞检测
	bool Jiguang_Pengzhuang(Object& a, 动画& b, 动画::动画类型 type);	//激光的碰撞检测
private:

	clock_t start_time;
	int FPS;
	IMAGE bk;
	int My_bullet_shanghai;
	int hedan_num = 0;
	bool hedan_flag = false;				//是否使用核弹
	bool Boss_come = false;					//Boss来袭
	int 我的阶段 = 阶段一;
	vector<int> Enemys_Blood;				//敌人的血量
	vector<int> Enemys_Bullet_Shanghai;		//敌人的子弹伤害
	Object* My;
	Object* Boss;							//Boss
	动画 boom[MAX_Boom];	//敌机爆炸
	动画 my_boom;			//我的爆炸	
	动画 hudun;				//护盾
	动画 jiguang;			//激光
	动画 boss_jiguang;		//Boss激光

	vector<Button> button;					//按钮类
	vector<Picture> plane_images;			//飞机图片
	vector<Picture> my_bullet_images;		//我方子弹图片
	vector<Picture> enemy_bullet_images;	//敌机子弹图片
	vector<Picture> Tool_images;			//工具图片
	vector<Picture> Other_images;			//其他图片


	vector<Object> my_bullet;				//我的子弹
	vector<Object> Super_bullet;			//特殊子弹
	vector<Object> enemys;					//敌机
	vector<Object> enemy_bullet;			//敌机子弹
	vector<Object> Boss_bullet;				//Boss子弹
	vector<Object> tools;					//道具类
	array<动画,5> biaozhi;				//标志类
};