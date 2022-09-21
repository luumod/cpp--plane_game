#include "×éºÏ.h"

#if 1
int main()
{

	initgraph(WINDOWS_GAME_W, WINDOWS_GAME_H, SHOWCONSOLE);
	srand(time(0));

	Game play;
	auto flag = false;
	do
	{
		flag = play.Play_Game();
	} while (!flag);


	closegraph();
	return 0;
}

#else

int main()
{
	initgraph(WINDOWS_W, WINDOWS_H, SHOWCONSOLE);
	setbkcolor(WHITE);
	cleardevice();
	IMAGE boom;
	while (1)
	{
		loadimage(&boom, "./common/±¬Õ¨.gif");
		putimage(100, 400, &boom);
	}

	closegraph();
	return 0;
}


#endif