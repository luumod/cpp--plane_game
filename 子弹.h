//#pragma once
//#include "common.h"
//
//class Shuxing
//{
//public:
//	enum Dir { up, down, left, right, NO };
//	Shuxing();
//	Shuxing(const int& x, const int& y,const int& speed, Dir dir, bool isdied = true);
//	Shuxing(const Shuxing& biu);
//	~Shuxing() {}
//	//显式设置子弹的数据
//	void SetX(int x);
//	void SetY(int y);
//	void SetW(int w);
//	void SetH(int h);
//	void SetSpeed(int speed);
//	void SetDir(Dir dir);
//	//引用返回子弹的数据（可修改）
//	int& GetX();
//	int& GetY();
//	int& GetW();
//	int& GetH();
//	int& GetSpeed();
//	bool& GetIsdied();
//	Dir& GetDir();
//private:
//	int 
//	int y;
//	int w;
//	int h;
//	int speed;		//子弹速度
//	Dir dir;		//子弹方向
//	bool isdied = true;	//子弹是否消失
//};