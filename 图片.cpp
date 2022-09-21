#include "ͼƬ.h"

Picture::Picture()
{
	image = new IMAGE;
	image = nullptr;
	w = h = 0;
}

Picture::Picture(string img_path):name(img_path)
{
	this->image = new IMAGE;					//ԭͼ����
	
	loadimage(image, img_path.c_str());	//ԭͼ
	w = image->getwidth();
	h = image->getheight();
}


IMAGE* Picture::GetImage() const
{
	return image;
}

int Picture::GetImgW() const
{
	return image->getwidth();
}

int Picture::GetImgH() const
{
	return image->getheight();
}

string Picture::GetName()const
{
	return name;
}

