#pragma once
#include "操作.h"
#include "子弹.h"
#include "图片.h"
#include "Timer.h"
#include "按钮.h"
#include "标志.h"
#include "持续性动画绘制.h"

//对象本身
class Object
{
public:
	enum Limits { up, down, left, right, NO };
	Object() = default;
	Object(const Picture& image, const Picture& Yimage, const Operation& target);	//对象
	~Object() {}
	Picture GetImage()const;
	Picture GetYimage()const;
	//获取当前对象
	Operation& GetTarget();
	//对象的绘制
	void Draw();
	//对象的方向设置
	void SetDir(Operation::Dir dir);
	//对象的移动
	void Move();
	
private:
	Operation target;	//操作目标
	Picture image;		//原图
	Picture Yimage;		//掩码图
};