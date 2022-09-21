#pragma once
#include "common.h"

//操作
class Operation
{
public:
	enum Dir { up, down, left, right, NO};
	enum Leixing { Plane, My_Bullet, Enemy1, Enemy2, Enemy3,Enemy4, Enemy1_Bullet, Enemy2_Bullet, Enemy3_Bullet,Enemy4_Bullet,Boss,Boss_bullet,核弹,加血,护盾,加速,子弹升级, 激光状态,无类型 };
	enum Tools {飞机,子弹,hedan};
	Operation() :x(0), y(0),leixing(Leixing::无类型), speed(0),blood(0),shanghai(0), dir(Dir::NO) {}
	Operation(const int& x, const int& y,const Leixing& leixing=Leixing::无类型, const int& speed = 0, const int& blood = 0, const int& shanghai = 0, const Dir& dir = Dir::NO);
	~Operation() {}
	void Move();
	void SetW(int w);
	void SetH(int h);
	void SetSpeed(int speed);
	void SetBlood(int blood);
	void SetShanghai(int shanghai);

	int& GetX();
	int& GetY();
	int& GetW();
	int& GetH();
	Leixing& GetLeixing();
	int& GetSpeed();
	int& GetBlood();
	int& GetShanghai();
	Dir& GetDir();
	bool& GetIsDied();
private:
	int x;
	int y;
	int w;
	int h;
	Leixing leixing;//类型
	int speed;		//速度
	int	blood;		//血量
	int shanghai;	//伤害
	Dir dir;
	bool isdied = false;
};