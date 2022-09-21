//#include "子弹.h"
//
//Shuxing::Shuxing() : x(0), y(0), w(0), h(0), speed(0), dir(NO), isdied(true) {}
//
//Shuxing::Shuxing(const int& x, const int& y, const int& speed, Dir dir, bool isdied)
//	:x(x), y(y), speed(speed), dir(dir), isdied(isdied)
//{
//	this->w = 0;
//	this->h = 0;
//}
//
//Shuxing::Shuxing(const Shuxing& biu)
//	:x(biu.x), y(biu.y), speed(biu.speed), dir(biu.dir), isdied(biu.isdied)
//{
//	this->w = biu.w;
//	this->h = biu.h;
//}
//
//void Shuxing::Draw()
//{
//	if (!isdied)
//	{
//		
//	}
//}
//
//int Shuxing::LookX() const
//{
//	return this->x;
//}
//
//int Shuxing::LookY() const
//{
//	return this->y;
//}
//
//int Shuxing::LookW() const
//{
//	return this->w;
//}
//
//int Shuxing::LookH() const
//{
//	return this->h;
//}
//
//int Shuxing::LookSpeed() const
//{
//	return this->speed;
//}
//
//int Shuxing::LookDir() const
//{
//	return this->dir;
//}
//
//bool Shuxing::LookIsDied() const
//{
//	return this->isdied;
//}
//
//void Shuxing::SetX(int x)
//{
//	this->x = x;
//}
//void Shuxing::SetY(int y)
//{
//	this->y = y;
//}
//
//void Shuxing::SetW(int w)
//{
//	this->w = w;
//}
//
//void Shuxing::SetH(int h)
//{
//	this->h = h;
//}
//
//void Shuxing::SetSpeed(int speed)
//{
//	this->speed = speed;
//}
//
//void Shuxing::SetDir(Dir dir)
//{
//	this->dir = dir;
//}
//
//int& Shuxing::GetX()
//{
//	// TODO: 在此处插入 return 语句
//	return this->x;
//}
//
//int& Shuxing::GetY()
//{
//	// TODO: 在此处插入 return 语句
//	return this->y;
//}
//
//int& Shuxing::GetW()
//{
//	// TODO: 在此处插入 return 语句
//	return this->w;
//}
//
//int& Shuxing::GetH()
//{
//	// TODO: 在此处插入 return 语句
//	return this->h;
//}
//
//int& Shuxing::GetSpeed()
//{
//	// TODO: 在此处插入 return 语句
//	return this->speed;
//}
//
//bool& Shuxing::GetIsdied()
//{
//	// TODO: 在此处插入 return 语句
//	return this->isdied;
//}
//
//Shuxing::Dir& Shuxing::GetDir()
//{
//	// TODO: 在此处插入 return 语句
//	return this->dir;
//}