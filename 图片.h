#pragma once
#include "common.h"

//加载图片资源
class Picture
{
public:
	Picture();
	Picture(string img_name);
	//返回原图
	IMAGE* GetImage()const;
	//返回图片的数据
	int GetImgW()const;
	int GetImgH()const;
	string GetName()const;
private:
	IMAGE* image;		//加载图片
	int w;
	int h;	
	string name;		//路径
};

