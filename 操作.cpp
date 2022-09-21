#include "����.h"

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

//�����ƶ�
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
    // TODO: �ڴ˴����� return ���
    return x;
}

int& Operation::GetY()
{
    // TODO: �ڴ˴����� return ���
    return y;

}

int& Operation::GetW()
{
    // TODO: �ڴ˴����� return ���
    return w;
}

int& Operation::GetH()
{
    // TODO: �ڴ˴����� return ���
    return h;
}

Operation::Leixing& Operation::GetLeixing()
{
    return leixing;
}


int& Operation::GetSpeed()
{
    // TODO: �ڴ˴����� return ���
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
    // TODO: �ڴ˴����� return ���
    return dir;

}

bool& Operation::GetIsDied()
{
    // TODO: �ڴ˴����� return ���
    return isdied;
}
