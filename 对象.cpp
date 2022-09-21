#include "¶ÔÏó.h"


Object::Object(const Picture& image, const Picture& Yimage, const Operation& target)
{
	this->image = image;
	this->Yimage = Yimage;
	this->target = target;
	this->target.SetW(image.GetImgW());
	this->target.SetH(image.GetImgH());
}


Picture Object::GetImage()const
{
	return image;
}

Picture Object::GetYimage()const
{
	return Yimage;
}

Operation& Object::GetTarget()
{
	return target;
}

void Object::Draw()
{
	putimage(target.GetX(), target.GetY(), Yimage.GetImage(), SRCPAINT);		//ÑÚÂëÍ¼
	putimage(target.GetX(), target.GetY(), image.GetImage(), SRCAND);			//Ô­Í¼
}	

void Object::SetDir(Operation::Dir dir)
{
	target.GetDir() = dir;
}

void Object::Move()
{
	if (GetAsyncKeyState(VK_UP) || GetAsyncKeyState(0x57))
	{
		target.GetDir() = Operation::up;
		if (target.GetDir() == up)
		{
			if (target.GetY() >= 0)
			{
				target.GetY() -= target.GetSpeed();
			}
		}
	}
	if (GetAsyncKeyState(VK_DOWN)|| GetAsyncKeyState(0x53))
	{
		target.GetDir() = Operation::down;
		if (target.GetDir() == down)
		{
			if (target.GetY() <= WINDOWS_H-target.GetH()/2)
			{
				target.GetY() += target.GetSpeed();
			}
		}
	}
	if (GetAsyncKeyState(VK_LEFT)|| GetAsyncKeyState(0x41))
	{
		target.GetDir() = Operation::left;
		if (target.GetDir() == left)
		{
			if (target.GetX() >= 0)
			{
				target.GetX() -= target.GetSpeed();
			}
		}
	}
	if (GetAsyncKeyState(VK_RIGHT)|| GetAsyncKeyState(0x44))
	{
		target.GetDir() = Operation::right;
		if (target.GetDir() == right)
		{
			if (target.GetX() <= WINDOWS_W - target.GetW())
			{
				target.GetX() += target.GetSpeed();
			}
		}
	}
}
