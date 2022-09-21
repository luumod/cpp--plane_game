#pragma once
#include "±¬Õ¨.h"

Boom::Boom(const int& x, const int& y)
{
	this->frame = 1;		//Òª·¢Éú±¬Õ¨
	this->x = x;
	this->y = y;
}

int& Boom::GetFrame()
{
	return frame;
}

int& Boom::GetX()
{
	return x;
}

int& Boom::GetY()
{
	return y;
}

//void Boom::Draw()
//{
//	
//}