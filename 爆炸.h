#pragma once
#include "common.h"
#include "ͼƬ.h"

class Boom
{
public:
	Boom() :frame(0), x(0), y(0) {}
	Boom(const int& x, const int& y);
	int& GetFrame();
	int& GetX();
	int& GetY();
	void Draw();		//��ը����

private:
	int frame;		//��ը֡��
	int x;	
	int y;			//��ը����
	vector<Picture> boom_image = {
		{"./common/boom1.png"}, 	//��ը	
		{"./common/boom2.png"}, 	//		
		{"./common/boom3.png"}, 	//		
		{"./common/boom4.png"}, 	//		
		{"./common/boom5.png"}, 	//		
		{"./common/boom6.png"}, 	//		
	};;
	vector<Picture> boom_Yimage = {
		{"./common/Yboom1.png"},
		{"./common/Yboom2.png"},
		{"./common/Yboom3.png"},
		{"./common/Yboom4.png"},
		{"./common/Yboom5.png"},
		{"./common/Yboom6.png"},
	};;

};