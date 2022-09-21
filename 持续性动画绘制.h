#pragma once
#include "common.h"
#include "图片.h"

/*
持续性动画的绘制
*/
class 动画
{
public:
	enum 动画类型 {我方激光,敌方激光,我方护盾,武器升级提示,必杀提示,回血提示,护盾提示,Boss出现警告};
	enum 状态 {开始, 结束 };
	动画();
	int& GetX();
	int& GetY();
	int GetW(动画类型 x)const;
	int GetH(动画类型 x)const;
	//获取当前绘制状态
	状态& GetStart();
	//绘制开始时间
	int& Gettime_start();
	//绘制结束时间
	int& Gettime_end();
	//获取绘制帧率
	int& GetFrame();
	//获取绘制的图片掩码
	IMAGE* GetYimage(动画类型 x);
	//获取绘制原图片
	IMAGE* Getimage(动画类型 x);

	//绘制跟随性道具
	void Draw(int x, int y, 动画类型 type);
	//绘制固定性道具：爆炸
	void DrawBoom();
	//结束绘制
	void EndDraw();
private:
	int x;
	int y;
	int w;
	int h;
	////非固定性图片
	vector<Picture> Yimage; 
	vector<Picture> image;
	//固定位置的爆炸：特殊的爆炸连环画
	vector<Picture> boom_image;		
	vector<Picture> boom_Yimage;

	int frame;		//帧率
	状态 start;	//此变量表示时间的标记
	int time_start;	//激光开始的时间
	int time_end;	//激光结束时间
};