#pragma once
#include "common.h"

//����
class Operation
{
public:
	enum Dir { up, down, left, right, NO};
	enum Leixing { Plane, My_Bullet, Enemy1, Enemy2, Enemy3,Enemy4, Enemy1_Bullet, Enemy2_Bullet, Enemy3_Bullet,Enemy4_Bullet,Boss,Boss_bullet,�˵�,��Ѫ,����,����,�ӵ�����, ����״̬,������ };
	enum Tools {�ɻ�,�ӵ�,hedan};
	Operation() :x(0), y(0),leixing(Leixing::������), speed(0),blood(0),shanghai(0), dir(Dir::NO) {}
	Operation(const int& x, const int& y,const Leixing& leixing=Leixing::������, const int& speed = 0, const int& blood = 0, const int& shanghai = 0, const Dir& dir = Dir::NO);
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
	Leixing leixing;//����
	int speed;		//�ٶ�
	int	blood;		//Ѫ��
	int shanghai;	//�˺�
	Dir dir;
	bool isdied = false;
};