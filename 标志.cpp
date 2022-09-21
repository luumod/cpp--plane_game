#include "标志.h"

Biaozhi::Biaozhi()
{
	x = y = appera_flag = frame = 0;

	image = {
		{"./common/武器升级.png"},	//  0
		{"./common/必杀.png"},	//  1
		{"./common/回血.png"},	//  2
		{"./common/护盾.png"},	//  3


	};

	Yimage = {
		{"./common/Y武器升级.png"},	//0 
		{"./common/Y必杀.png"},		//1 
		{"./common/Y回血.png"},	//  2
		{"./common/Y护盾.png"},	//  3

	};
}

Biaozhi::Biaozhi(const int& x, const int& y, const bool& flag, const int& frame)
{
	this->x - x;
	this->y = y;
	this->appera_flag = flag;
	this->frame = frame;
}

//绘制标志图片
void Biaozhi::Draw武器(int x,int y)
{
	if (frame != 0)
	{
		putimage(x, y, Yimage[frame / 标志帧率].GetImage(), SRCPAINT);
		putimage(x, y, image[frame / 标志帧率].GetImage(), SRCAND);
		frame++;
		if (frame >= 1 * 标志帧率)
		{
			frame = 0;
		}
	}
}

void Biaozhi::Draw必杀(int x, int y)
{
	if (frame != 0)
	{
		putimage(x, y, Yimage[frame / 标志帧率 + 1].GetImage(), SRCPAINT);
		putimage(x, y, image[frame / 标志帧率 + 1].GetImage(), SRCAND);
		frame++;
		if (frame >= 1 * 标志帧率)
		{
			frame = 0;
		}
	}
}

void Biaozhi::Draw回血(int x, int y)
{
	if (frame != 0)
	{
		putimage(x, y, Yimage[frame / 标志帧率 + 2].GetImage(), SRCPAINT);
		putimage(x, y, image[frame / 标志帧率 + 2].GetImage(), SRCAND);
		frame++;
		if (frame >= 1 * 标志帧率)
		{
			frame = 0;
		}
	}
}

void Biaozhi::Draw加速(int x, int y)
{
	if (frame != 0)
	{
		putimage(x, y, Yimage[frame / 标志帧率 + 0].GetImage(), SRCPAINT);
		putimage(x, y, image[frame / 标志帧率 + 0].GetImage(), SRCAND);
		frame++;
		if (frame >= 1 * 标志帧率)
		{
			frame = 0;
		}
	}
}

void Biaozhi::Draw护盾(int x, int y)
{
	if (frame != 0)
	{
		putimage(x, y, Yimage[frame / 标志帧率 + 3].GetImage(), SRCPAINT);
		putimage(x, y, image[frame / 标志帧率 + 3].GetImage(), SRCAND);
		frame++;
		if (frame >= 1 * 标志帧率)
		{
			frame = 0;
		}
	}
}


void Biaozhi::SetW(int w)
{
	this->w = w;
}

void Biaozhi::SetH(int h)
{
	this->h = h;
}

void Biaozhi::SetFrame(int frame)
{
	this->frame = frame;
}

void Biaozhi::SetFlag(bool flag)
{
	this->appera_flag = flag;
}

int& Biaozhi::GetX()
{
	// TODO: 在此处插入 return 语句
	return x;
}

int& Biaozhi::GetY()
{
	// TODO: 在此处插入 return 语句
	return y;
}

int& Biaozhi::GetW()
{
	// TODO: 在此处插入 return 语句
	return w;
}

int& Biaozhi::GetH()
{
	// TODO: 在此处插入 return 语句
	return h;
}

bool& Biaozhi::GetFlag()
{
	// TODO: 在此处插入 return 语句
	return appera_flag;
}

int& Biaozhi::GetFrame()
{
	// TODO: 在此处插入 return 语句
	return frame;
}
