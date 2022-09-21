#pragma once
#include "common.h"
#include "ͼƬ.h"

class Biaozhi
{
public:
	Biaozhi();
	Biaozhi(const int& x, const int& y, const bool& flag, const int& frame);

	void Draw����(int x, int y);
	void Draw��ɱ(int x, int y);
	void Draw��Ѫ(int x, int y);
	void Draw����(int x, int y);
	void Draw����(int x, int y);

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
	bool appera_flag;	//���ֵı��
	int frame;			//֡��

	vector<Picture> image;
	vector<Picture> Yimage;
};
