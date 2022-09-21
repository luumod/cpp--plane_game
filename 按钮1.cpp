#include "°´Å¥.h"

void Button::Draw() 
{
	setfillcolor(color);
	fillrectangle(x, y, x + w, y + h);

	auto textw = textwidth(text.c_str());
	auto texth = textheight(text.c_str());
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
	settextstyle(30, 0, "Î¢ÈíÑÅºÚ");
	//×ÖÌå¶ÔÆë
	outtextxy(x+(w-textw) / 2, y +(h-texth) / 2, text.c_str());
}

bool Button::MouseInButton(ExMessage msg)
{
	if (msg.x >= x && msg.x < x + w && msg.y >= y && msg.y <= y + h)
	{
		color = LIGHTRED;
		return true;
	}
	color = oldcolor;
	return false;
}

bool Button::ClickButton(ExMessage msg)
{
	if (msg.message == WM_LBUTTONDOWN && MouseInButton(msg))
	{
		return true;
	}
	return false;
}
