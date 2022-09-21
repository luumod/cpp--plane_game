#pragma once
#include "common.h"


class Hudun
{
public:
	enum 状态 { 开始,结束 };
	Hudun()
	{
		frame	//帧率=	flag;		//无敌判断
			= time_start	//获得当前的时间
			= time_end = 0;	//护盾结束时间
		loadimage(&Yimage[0], "./common/Y盾牌.png");
		loadimage(&image[0], "./common/盾牌.png");
		start = 结束;
	}

	int& GetX() { return x; }
	int& GetY() { return y; }
	int& GetW() { return w; }
	int& GetH() { return h; }

	bool& Getflag() { return flag; }
	状态& GetStart() { return start; }
	int& Gettime_start() { return time_start; }
	int& Gettime_end() { return time_end; }
	int& GetFrame() { return frame; }
	IMAGE* GetYimage() { return &Yimage[0]; }
	IMAGE* Getimage() { return &image[0];}

	void Draw(int x,int y)
	{

		if (start == 开始)
		{
			GetX() = x;
			GetY() = y;
			//盾牌产生
			putimage(x,y-20, &Yimage[frame/500], SRCPAINT);
			putimage(x,y-20, &image[frame/500], SRCAND);
			frame++;
			if (frame >= 500)
			{
				frame = 0;
			}
			//无敌时间消失
			if (start ==结束)
			{
				frame = 0;
			}
		}
	}

private:
	int x;
	int y;
	int w;
	int h;
	IMAGE Yimage[1];
	IMAGE image[1];
	int frame;		//帧率
	bool flag;		//无敌判断
	状态 start;	//此变量表示时间的标记
	int time_start;	//获得当前的时间
	int time_end;	//护盾结束时间
};