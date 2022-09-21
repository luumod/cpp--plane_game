#pragma once
#include "common.h"
#include "图片.h"

class Biaozhi
{
public:
	Biaozhi();
	Biaozhi(const int& x, const int& y, const bool& flag, const int& frame);

	void Draw武器(int x, int y);
	void Draw必杀(int x, int y);
	void Draw回血(int x, int y);
	void Draw加速(int x, int y);
	void Draw护盾(int x, int y);

	void SetW(int w);
	void SetH(int h);
	void SetFrame(int frame);
	void SetFlag(bool flag);

	int& GetX();
	int& GetY();
	int& GetW();
	int& GetH();
	bool& GetFlag();
	int& GetFrame();
private:
	int x;
	int y;
	int w;
	int h;
	bool appera_flag;	//出现的标记
	int frame;			//帧率

	vector<Picture> image;
	vector<Picture> Yimage;
};
