#pragma once
#include "common.h"


class Hudun
{
public:
	enum ״̬ { ��ʼ,���� };
	Hudun()
	{
		frame	//֡��=	flag;		//�޵��ж�
			= time_start	//��õ�ǰ��ʱ��
			= time_end = 0;	//���ܽ���ʱ��
		loadimage(&Yimage[0], "./common/Y����.png");
		loadimage(&image[0], "./common/����.png");
		start = ����;
	}

	int& GetX() { return x; }
	int& GetY() { return y; }
	int& GetW() { return w; }
	int& GetH() { return h; }

	bool& Getflag() { return flag; }
	״̬& GetStart() { return start; }
	int& Gettime_start() { return time_start; }
	int& Gettime_end() { return time_end; }
	int& GetFrame() { return frame; }
	IMAGE* GetYimage() { return &Yimage[0]; }
	IMAGE* Getimage() { return &image[0];}

	void Draw(int x,int y)
	{

		if (start == ��ʼ)
		{
			GetX() = x;
			GetY() = y;
			//���Ʋ���
			putimage(x,y-20, &Yimage[frame/500], SRCPAINT);
			putimage(x,y-20, &image[frame/500], SRCAND);
			frame++;
			if (frame >= 500)
			{
				frame = 0;
			}
			//�޵�ʱ����ʧ
			if (start ==����)
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
	int frame;		//֡��
	bool flag;		//�޵��ж�
	״̬ start;	//�˱�����ʾʱ��ı��
	int time_start;	//��õ�ǰ��ʱ��
	int time_end;	//���ܽ���ʱ��
};