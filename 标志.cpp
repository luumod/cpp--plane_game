#include "��־.h"

Biaozhi::Biaozhi()
{
	x = y = appera_flag = frame = 0;

	image = {
		{"./common/��������.png"},	//  0
		{"./common/��ɱ.png"},	//  1
		{"./common/��Ѫ.png"},	//  2
		{"./common/����.png"},	//  3


	};

	Yimage = {
		{"./common/Y��������.png"},	//0 
		{"./common/Y��ɱ.png"},		//1 
		{"./common/Y��Ѫ.png"},	//  2
		{"./common/Y����.png"},	//  3

	};
}

Biaozhi::Biaozhi(const int& x, const int& y, const bool& flag, const int& frame)
{
	this->x - x;
	this->y = y;
	this->appera_flag = flag;
	this->frame = frame;
}

//���Ʊ�־ͼƬ
void Biaozhi::Draw����(int x,int y)
{
	if (frame != 0)
	{
		putimage(x, y, Yimage[frame / ��־֡��].GetImage(), SRCPAINT);
		putimage(x, y, image[frame / ��־֡��].GetImage(), SRCAND);
		frame++;
		if (frame >= 1 * ��־֡��)
		{
			frame = 0;
		}
	}
}

void Biaozhi::Draw��ɱ(int x, int y)
{
	if (frame != 0)
	{
		putimage(x, y, Yimage[frame / ��־֡�� + 1].GetImage(), SRCPAINT);
		putimage(x, y, image[frame / ��־֡�� + 1].GetImage(), SRCAND);
		frame++;
		if (frame >= 1 * ��־֡��)
		{
			frame = 0;
		}
	}
}

void Biaozhi::Draw��Ѫ(int x, int y)
{
	if (frame != 0)
	{
		putimage(x, y, Yimage[frame / ��־֡�� + 2].GetImage(), SRCPAINT);
		putimage(x, y, image[frame / ��־֡�� + 2].GetImage(), SRCAND);
		frame++;
		if (frame >= 1 * ��־֡��)
		{
			frame = 0;
		}
	}
}

void Biaozhi::Draw����(int x, int y)
{
	if (frame != 0)
	{
		putimage(x, y, Yimage[frame / ��־֡�� + 0].GetImage(), SRCPAINT);
		putimage(x, y, image[frame / ��־֡�� + 0].GetImage(), SRCAND);
		frame++;
		if (frame >= 1 * ��־֡��)
		{
			frame = 0;
		}
	}
}

void Biaozhi::Draw����(int x, int y)
{
	if (frame != 0)
	{
		putimage(x, y, Yimage[frame / ��־֡�� + 3].GetImage(), SRCPAINT);
		putimage(x, y, image[frame / ��־֡�� + 3].GetImage(), SRCAND);
		frame++;
		if (frame >= 1 * ��־֡��)
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
	// TODO: �ڴ˴����� return ���
	return x;
}

int& Biaozhi::GetY()
{
	// TODO: �ڴ˴����� return ���
	return y;
}

int& Biaozhi::GetW()
{
	// TODO: �ڴ˴����� return ���
	return w;
}

int& Biaozhi::GetH()
{
	// TODO: �ڴ˴����� return ���
	return h;
}

bool& Biaozhi::GetFlag()
{
	// TODO: �ڴ˴����� return ���
	return appera_flag;
}

int& Biaozhi::GetFrame()
{
	// TODO: �ڴ˴����� return ���
	return frame;
}
