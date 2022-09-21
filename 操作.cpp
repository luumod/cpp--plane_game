#include "操作.h"

Operation::Operation(const int& x, const int& y,const Leixing& leixing, const int& speed, const int& blood, const int& shanghai, const Dir& dir)
{
    this->x = x;
    this->y = y;
    this->leixing = leixing;
    this->speed = speed;
    this->dir = dir;
    this->blood = blood;
    this->shanghai = shanghai;
}

//控制移动
void Operation::Move()
{
    if (dir == Dir::up)
    {
        if (y >= 0)
        {
            y -= speed;
        }
   }
    if (dir == Dir::down)
    {
        if (y <= WINDOWS_H - h/2)
        {
            y += speed;
        }
    }
    if (dir == Dir::left)
    {
        if (x >= 0)
        {
            x -= speed;
        }
    }
    if (dir == Dir::right)
    {
        if (x <= WINDOWS_W - w/2)
        {
            x += speed;
        }
    }
    dir = Dir::NO;
}

void Operation::SetW(int w)
{
    this->w = w;
}

void Operation::SetH(int h)
{
    this->h = h;
}

void Operation::SetSpeed(int speed)
{
    this->speed = speed;
}

void Operation::SetBlood(int blood)
{
    this->blood = blood;
}

void Operation::SetShanghai(int shanghai)
{
    this->shanghai = shanghai;
}
int& Operation::GetX()
{
    // TODO: 在此处插入 return 语句
    return x;
}

int& Operation::GetY()
{
    // TODO: 在此处插入 return 语句
    return y;

}

int& Operation::GetW()
{
    // TODO: 在此处插入 return 语句
    return w;
}

int& Operation::GetH()
{
    // TODO: 在此处插入 return 语句
    return h;
}

Operation::Leixing& Operation::GetLeixing()
{
    return leixing;
}


int& Operation::GetSpeed()
{
    // TODO: 在此处插入 return 语句
    return speed;

}

int& Operation::GetBlood()
{
    return blood;
}

int& Operation::GetShanghai()
{
    return shanghai;
}

Operation::Dir& Operation::GetDir()
{
    // TODO: 在此处插入 return 语句
    return dir;

}

bool& Operation::GetIsDied()
{
    // TODO: 在此处插入 return 语句
    return isdied;
}
