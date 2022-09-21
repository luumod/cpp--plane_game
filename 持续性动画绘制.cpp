
#include "持续性动画绘制.h"

动画::动画()
{
	x = y = 0;
	frame	//帧率=	flag;		//无敌判断
		= time_start	//获得当前的时间
		= time_end = 0;	//护盾结束时间

	Yimage = {
		{"./images1/Y激光.png"},		// 0 
		{"./images1/YBoss激光.png"},	// 1
		{"./common/Y盾牌.png"},			// 2

		{"./common/Y武器升级.png"},		//  3
		{"./common/Y必杀.png"},			//  4
		{"./common/Y回血.png"},			 //  5
		{"./common/Y护盾.png"},			 //  6
		{"./common/Y警告.png"},			 //  7

	};
	image = {
		{"./images1/激光.png"},			// 0 
		{"./images1/Boss激光.png"},		// 1
		{"./common/盾牌.png"},			// 2

		{"./common/武器升级.png"},		// 3
		{"./common/必杀.png"},			// 4 
		{"./common/回血.png"},			// 5 
		{"./common/护盾.png"},			// 6
		{"./common/警告.png"},			// 7

	};

	boom_image = {
{"./common/boom1.png"}, 	//爆炸	
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
	start = 结束;
}

int& 动画::GetX()
{
	return x;
}

int& 动画::GetY()
{
	return y;
}

int 动画::GetW(动画类型 x) const
{
	return image[x].GetImgW();
}

int 动画::GetH(动画类型 x) const
{
	return image[x].GetImgH();
}

动画::状态& 动画::GetStart()
{
	return start;
}

int& 动画::Gettime_start()
{
	return time_start;
}

int& 动画::Gettime_end()
{
	return time_end;
}

int& 动画::GetFrame()
{
	return frame;
}
IMAGE* 动画::GetYimage(动画类型 x)
{
	return Yimage[x].GetImage();
}

IMAGE* 动画::Getimage(动画类型 x)
{
	return image[x].GetImage();
}


void 动画::Draw(int x, int y, 动画类型 type)
{
	GetX() = x;
	GetY() = y;
	if (start == 开始)
	{
		putimage(x, y - 20, Yimage[(static_cast<std::vector<Picture, std::allocator<Picture>>::size_type>(frame / 持续性道具最大帧率)) + type].GetImage(), SRCPAINT);
		putimage(x, y - 20, image[(static_cast<std::vector<Picture, std::allocator<Picture>>::size_type>(frame / 持续性道具最大帧率)) + type].GetImage(), SRCAND);
		frame++;
		//结束绘制
		if (frame >= 持续性道具最大帧率)
		{
			frame = 0;
		}
		if (start == 结束)
		{
			frame = 0;
		}
	}

}

void 动画::DrawBoom()
{
	if (frame != 0)
	{
		putimage(x, y, boom_Yimage[frame / 爆炸帧率].GetImage(), SRCPAINT);
		putimage(x, y, boom_image[frame / 爆炸帧率].GetImage(), SRCAND);
		frame++;
		if (frame >= 6 * 爆炸帧率)
		{
			frame = 0;
		}
	}
}

void 动画::EndDraw()
{
	Gettime_end() = time(0);
	//只会执行一次，即时间正好等于3秒的时候，无敌时间结束
	if (Gettime_end() - Gettime_start() >= 道具持续时间（可修改） && GetStart() == 动画::开始)
	{
		//持续三秒，护罩消失
		GetStart() = 动画::结束;	//无敌状态消失
	}
}
