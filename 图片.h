#pragma once
#include "common.h"

//����ͼƬ��Դ
class Picture
{
public:
	Picture();
	Picture(string img_name);
	//����ԭͼ
	IMAGE* GetImage()const;
	//����ͼƬ������
	int GetImgW()const;
	int GetImgH()const;
	string GetName()const;
private:
	IMAGE* image;		//����ͼƬ
	int w;
	int h;	
	string name;		//·��
};

