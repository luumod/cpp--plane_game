
#include "�����Զ�������.h"

����::����()
{
	x = y = 0;
	frame	//֡��=	flag;		//�޵��ж�
		= time_start	//��õ�ǰ��ʱ��
		= time_end = 0;	//���ܽ���ʱ��

	Yimage = {
		{"./images1/Y����.png"},		// 0 
		{"./images1/YBoss����.png"},	// 1
		{"./common/Y����.png"},			// 2

		{"./common/Y��������.png"},		//  3
		{"./common/Y��ɱ.png"},			//  4
		{"./common/Y��Ѫ.png"},			 //  5
		{"./common/Y����.png"},			 //  6
		{"./common/Y����.png"},			 //  7

	};
	image = {
		{"./images1/����.png"},			// 0 
		{"./images1/Boss����.png"},		// 1
		{"./common/����.png"},			// 2

		{"./common/��������.png"},		// 3
		{"./common/��ɱ.png"},			// 4 
		{"./common/��Ѫ.png"},			// 5 
		{"./common/����.png"},			// 6
		{"./common/����.png"},			// 7

	};

	boom_image = {
{"./common/boom1.png"}, 	//��ը	
{"./common/boom2.png"}, 	//		
{"./common/boom3.png"}, 	//		
{"./common/boom4.png"}, 	//		
{"./common/boom5.png"}, 	//		
{"./common/boom6.png"}, 	//		
	};
	boom_Yimage = {
	{"./common/Yboom1.png"},
	{"./common/Yboom2.png"},
	{"./common/Yboom3.png"},
	{"./common/Yboom4.png"},
	{"./common/Yboom5.png"},
	{"./common/Yboom6.png"},
	};


	w = 0;
	h = 0;
	start = ����;
}

int& ����::GetX()
{
	return x;
}

int& ����::GetY()
{
	return y;
}

int ����::GetW(�������� x) const
{
	return image[x].GetImgW();
}

int ����::GetH(�������� x) const
{
	return image[x].GetImgH();
}

����::״̬& ����::GetStart()
{
	return start;
}

int& ����::Gettime_start()
{
	return time_start;
}

int& ����::Gettime_end()
{
	return time_end;
}

int& ����::GetFrame()
{
	return frame;
}
IMAGE* ����::GetYimage(�������� x)
{
	return Yimage[x].GetImage();
}

IMAGE* ����::Getimage(�������� x)
{
	return image[x].GetImage();
}


void ����::Draw(int x, int y, �������� type)
{
	GetX() = x;
	GetY() = y;
	if (start == ��ʼ)
	{
		putimage(x, y - 20, Yimage[(static_cast<std::vector<Picture, std::allocator<Picture>>::size_type>(frame / �����Ե������֡��)) + type].GetImage(), SRCPAINT);
		putimage(x, y - 20, image[(static_cast<std::vector<Picture, std::allocator<Picture>>::size_type>(frame / �����Ե������֡��)) + type].GetImage(), SRCAND);
		frame++;
		//��������
		if (frame >= �����Ե������֡��)
		{
			frame = 0;
		}
		if (start == ����)
		{
			frame = 0;
		}
	}

}

void ����::DrawBoom()
{
	if (frame != 0)
	{
		putimage(x, y, boom_Yimage[frame / ��ը֡��].GetImage(), SRCPAINT);
		putimage(x, y, boom_image[frame / ��ը֡��].GetImage(), SRCAND);
		frame++;
		if (frame >= 6 * ��ը֡��)
		{
			frame = 0;
		}
	}
}

void ����::EndDraw()
{
	Gettime_end() = time(0);
	//ֻ��ִ��һ�Σ���ʱ�����õ���3���ʱ���޵�ʱ�����
	if (Gettime_end() - Gettime_start() >= ���߳���ʱ�䣨���޸ģ� && GetStart() == ����::��ʼ)
	{
		//�������룬������ʧ
		GetStart() = ����::����;	//�޵�״̬��ʧ
	}
}
