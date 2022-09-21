#include "组合.h"

//图片资源的加载
Game::Game()
{
	loadimage(&bk, "./images1/bg5.jpg");
	start_time = 0;
	FPS = 0;
	plane_images = {
		{"./images1/plane1.png"},{"./images1/Yplane1.png" },//我方飞机		0 1
		{"./images1/enemy1.png"},{"./images1/Yenemy1.png"},	//敌机一号		2 3
		{"./images1/enemy2.png"},{"./images1/Yenemy2.png"},	//敌机二号		4 5
		{"./images1/enemy3.png"},{"./images1/Yenemy3.png"},	//敌机三号		6 7
		{"./images1/enemy4.png"},{"./images1/Yenemy4.png"},	//敌机四号		8 9
		{"./images1/Boss.png"},{"./images1/YBoss.png"},		//Boss		    10 11

	};
	my_bullet_images = {
		{"./images1/biu1.png"},{"./images1/Ybiu1.png"},		//我方飞机子弹	0 1
		{"./images1/biu2.png"},{"./images1/Ybiu2.png"},		//我方飞机子弹	2 3
		{"./images1/biu3.png"},{"./images1/Ybiu3.png"},		//我方飞机子弹	4 5
		{"./images1/biu4.png"},{"./images1/Ybiu4.png"},		//我方飞机子弹	6 7
		{"./images1/biu5.png"},{"./images1/Ybiu5.png"},		//我方飞机子弹	8 9
		{"./images1/biu5.png"},{"./images1/Ybiu5.png"},		//我方飞机子弹	8 9
		{"./images1/激光.png"},{"./images1/Y激光.png"},		//我方飞机子弹	10 11


	};

	enemy_bullet_images = {
		{"./images1/enemy_bullet1.png"},{"./images1/Yenemy_bullet1.png"},// 0 1
		{"./images1/enemy_bullet2.png"},{"./images1/Yenemy_bullet2.png"},// 2 3
		{"./images1/enemy_bullet3.png"},{"./images1/Yenemy_bullet3.png"},// 4 5
		{"./images1/Boss_bullet1.png"},{"./images1/YBoss_bullet1.png"},	// 6 7
		{"./images1/Boss激光.png"},{"./images1/YBoss激光.png"},	// 6 7

	};

	Tool_images = {
		{"./common/核弹攻击.png"},{"./common/Y核弹攻击.png"},	// 0 1
		{"./common/保护.png"},{"./common/Y保护.png"},			// 2 3
		{"./common/加速.png"},{"./common/Y加速.png"},			// 4 5
		{"./common/加血.png"},{"./common/Y加血.png"},			// 6 7
		{"./common/子弹升级.png"},{"./common/Y子弹升级.png"},	// 8 9
		{"./common/子弹三发.png"},{"./common/Y子弹三发.png"},	// 10 11


	};

	My = new Object(plane_images[0], plane_images[1], Operation((WINDOWS_W - plane_images[0].GetImgW()) / 2, WINDOWS_H - 100,Operation::Leixing::Plane, Plane_speed, My_Plane_Blood,0, Operation::Dir::NO));
	Boss = new Object(plane_images[10], plane_images[11], Operation((WINDOWS_W / 2 - plane_images[10].GetImgW() / 2), -plane_images[10].GetImgH(), Operation::Leixing::Boss, 2, BOSS_BLOOD, 0, Operation::Dir::right));
	my_bullet = {};
	My_bullet_shanghai = My_Bullet1_Shanghai;
	enemys = {};
	enemy_bullet = {};
	Boss_bullet = {};
	tools = {};

	Enemys_Blood = { Enemy1_Blood,Enemy2_Blood ,Enemy3_Blood ,Enemy4_Blood };
	Enemys_Bullet_Shanghai = { Enemy1_Bullet_Shanghai,Enemy2_Bullet_Shanghai ,Enemy3_Bullet_Shanghai };

}

//游戏主循环
bool Game::Play_Game()
{
	start_time = clock();

	BeginBatchDraw();
	Draw();					//飞机对象绘制
	Draw_Other();			//其他绘制
	持续性动画的绘制();
	持续性动画的绘制结束();

	My->Move();
	Create_Bullet();		//子弹
	Create_Enemy();			//敌机
	Enemy_GrowUp();
	Bullet_To_Enemy();			//碰撞检测
	Bullet_To_Me();
	
	Create_Tools();
	Tools_Good();
	EndBatchDraw();

	ConrtolFPS(start_time);	//帧率控制
	//cout << start_time << endl;
	isWin();
	return Game_Over();
}

//游戏结束提示
bool Game::Game_Over()
{
	if (My->GetTarget().GetIsDied())
	{
		//主角爆炸动画绘制
		BoomZha(*My);
		while (1)
		{
			my_boom.DrawBoom();
			//cout << my.GetFrame() << endl;
			if (my_boom.GetFrame() == 0)
			{
				My->GetTarget().GetIsDied() = false;
				goto end;
			}
			Sleep(1);
		}
	end:;
		return GAME_OVER;		//游戏结束
	}
	return GAME_NOT_OVER;		//游戏继续
}

//绘制主要物品
void Game::Draw()
{
	putimage(0, 0, &bk);
	
	My->Draw();


	if (hedan_num > 0 && GetAsyncKeyState(VK_RETURN) &&Timer(9,500))
	{
		//使用核弹
		hedan_flag = true;
		--hedan_num;
	}
}

//绘制其他物品
void Game::Draw_Other()
{
	setfillcolor(RED);
	fillrectangle(WINDOWS_W, 0, WINDOWS_GAME_W, WINDOWS_GAME_H);
	setfillcolor(RED);

	char str[10][20] = { 0 };
	setbkmode(TRANSPARENT);
	settextstyle(30, 0, "微软雅黑");
	settextcolor(YELLOW);
	sprintf(str[0], "FPS:%d", FPS);
	outtextxy(10, 10, str[0]);

	settextstyle(35, 0, "微软雅黑");
	sprintf(str[1], "得分:%d", score);
	outtextxy(WINDOWS_W + 10, 10, str[1]);

	sprintf(str[2], "属性:");
	outtextxy(WINDOWS_W +2, 100, str[2]);

	sprintf(str[3], "血量:%d", My->GetTarget().GetBlood());
	outtextxy(WINDOWS_W + (WINDOWS_GAME_W - WINDOWS_W - textwidth(str[3])) / 2 - 20, 150, str[3]);

	sprintf(str[4], "速度: %d", My->GetTarget().GetSpeed());
	outtextxy(WINDOWS_W + (WINDOWS_GAME_W - WINDOWS_W - textwidth(str[4])) / 2 - 20, 200, str[4]);

	sprintf(str[5], "伤害: %d", My_bullet_shanghai);
	outtextxy(WINDOWS_W + (WINDOWS_GAME_W - WINDOWS_W - textwidth(str[5])) / 2 - 20, 250, str[5]);

	sprintf(str[6], "子弹: ");
	outtextxy(WINDOWS_W + (WINDOWS_GAME_W - WINDOWS_W - textwidth(str[6])) / 2 - 20, 300, str[6]);

	sprintf(str[7], "核弹: %d", hedan_num);
	outtextxy(WINDOWS_W + (WINDOWS_GAME_W - WINDOWS_W - textwidth(str[7])) / 2 - 20, 350, str[7]);

	setfillcolor(RGB(123, 255, 56));
	rectangle(WINDOWS_W / 2 -My_Plane_Blood / 2, WINDOWS_H - 20, WINDOWS_W / 2 + My_Plane_Blood / 2, WINDOWS_H - 10);
	int hp;
	hp = My_Plane_Blood / 2 - My->GetTarget().GetBlood();
	fillrectangle(WINDOWS_W / 2 - My_Plane_Blood / 2, WINDOWS_H - 20, WINDOWS_W / 2 - hp, WINDOWS_H - 10);
	
}

void  Game::持续性动画的绘制()
{
	//绘制爆炸
	for (int i = 0; i < MAX_Boom; ++i)
	{
		boom[i].DrawBoom();
	}

	//绘制护盾
	hudun.Draw(My->GetTarget().GetX(), My->GetTarget().GetY(), 动画::我方护盾);

	//绘制激光道具
	jiguang.Draw(My->GetTarget().GetX() + 10, My->GetTarget().GetY() - jiguang.Getimage(动画::我方激光)->getheight() + 50, 动画::我方激光);
	boss_jiguang.Draw(Boss->GetTarget().GetX() + 120, Boss->GetTarget().GetY() + Boss->GetTarget().GetH(), 动画::敌方激光);


	//绘制获取道具的提示
	biaozhi[0].Draw(WINDOWS_W / 2 - 200, WINDOWS_H / 2, 动画::武器升级提示);

	biaozhi[1].Draw(5, WINDOWS_H - 30, 动画::必杀提示);

	biaozhi[2].Draw(5, WINDOWS_H - 30, 动画::回血提示);

	biaozhi[3].Draw(5, WINDOWS_H - 30, 动画::护盾提示);

	biaozhi[4].Draw(WINDOWS_W / 2 - biaozhi[4].GetW(动画::Boss出现警告) / 2, WINDOWS_H / 2 - biaozhi[4].GetH(动画::Boss出现警告) / 2, 动画::Boss出现警告);

}

void  Game::持续性动画的绘制结束()
{
	//护盾结束绘制
	hudun.EndDraw();

	//激光结束绘制
	jiguang.EndDraw();

	//Boss激光绘制结束
	//boss_jiguang.EndDraw();

	//武器升级提示
	biaozhi[0].EndDraw();

	//必杀提示
	biaozhi[1].EndDraw();

	//回血提示
	biaozhi[2].EndDraw();

	//护盾提示
	biaozhi[3].EndDraw();

	//Boss出现警告
	biaozhi[4].EndDraw();
	cout << Boss->GetTarget().GetBlood() << endl;

}

//子弹的创建及发射
void Game::Create_Bullet()
{
	//我方创建子弹
	if (GetAsyncKeyState(VK_SPACE) && Timer(0, 150))
	{
		//第一阶段
		if (我的阶段==阶段::阶段一)
		{
			my_bullet.push_back({ my_bullet_images[0],my_bullet_images[1],Operation(My->GetTarget().GetX() + My->GetTarget().GetW() / 2 - 25,My->GetTarget().GetY(),Operation::Leixing::My_Bullet,Bullet_speed,0,My_Bullet1_Shanghai,Operation::up) });
			My_bullet_shanghai = my_bullet.back().GetTarget().GetShanghai();
		}
		//第二阶段
		else if (我的阶段 == 阶段::阶段二)
		{
			//两束子弹
			my_bullet.push_back({ my_bullet_images[0],my_bullet_images[1],Operation(My->GetTarget().GetX() + 20 ,My->GetTarget().GetY(),Operation::Leixing::My_Bullet,Bullet_speed,0,My_Bullet1_Shanghai,Operation::up) });
			my_bullet.push_back({ my_bullet_images[0],my_bullet_images[1],Operation(My->GetTarget().GetX() + My->GetTarget().GetW() - 20,My->GetTarget().GetY(),Operation::Leixing::My_Bullet,Bullet_speed,0,My_Bullet1_Shanghai,Operation::up) });
			My_bullet_shanghai = my_bullet.back().GetTarget().GetShanghai() * 2;

		}
		//第三阶段
		else if (我的阶段 == 阶段::阶段三)
		{
			//三束子弹
			my_bullet.push_back({ my_bullet_images[0],my_bullet_images[1],Operation(My->GetTarget().GetX() + My->GetTarget().GetW() / 2,My->GetTarget().GetY(),Operation::Leixing::My_Bullet,Bullet_speed,0,My_Bullet1_Shanghai,Operation::up) });

			my_bullet.push_back({ my_bullet_images[0],my_bullet_images[1],Operation(My->GetTarget().GetX() +20 ,My->GetTarget().GetY(),Operation::Leixing::My_Bullet,Bullet_speed,0,My_Bullet1_Shanghai,Operation::up) });
			my_bullet.push_back({ my_bullet_images[0],my_bullet_images[1],Operation(My->GetTarget().GetX() + My->GetTarget().GetW() - 20,My->GetTarget().GetY(),Operation::Leixing::My_Bullet,Bullet_speed,0,My_Bullet1_Shanghai,Operation::up) });
			My_bullet_shanghai = my_bullet.back().GetTarget().GetShanghai() * 3;

		}
		//第四阶段
		else if (我的阶段 == 阶段::阶段四)
		{
			//三束子弹 烟花弹
			my_bullet.push_back({ my_bullet_images[2],my_bullet_images[3],Operation(My->GetTarget().GetX() + My->GetTarget().GetW() / 2,My->GetTarget().GetY(),Operation::Leixing::My_Bullet,Bullet_speed,0,My_Bullet4_Shanghai,Operation::up) });

			my_bullet.push_back({ my_bullet_images[0],my_bullet_images[1],Operation(My->GetTarget().GetX() + 20 ,My->GetTarget().GetY(),Operation::Leixing::My_Bullet,Bullet_speed,0,My_Bullet1_Shanghai,Operation::up) });
			my_bullet.push_back({ my_bullet_images[0],my_bullet_images[1],Operation(My->GetTarget().GetX() + My->GetTarget().GetW() - 20,My->GetTarget().GetY(),Operation::Leixing::My_Bullet,Bullet_speed,0,My_Bullet1_Shanghai,Operation::up) });

			My_bullet_shanghai = My_Bullet1_Shanghai+ My_Bullet1_Shanghai+ My_Bullet4_Shanghai;

		}
		//第五阶段
		else if (我的阶段 == 阶段::阶段五)
		{
			//冰子弹
			my_bullet.push_back({ my_bullet_images[4],my_bullet_images[5],Operation(My->GetTarget().GetX() + 20 ,My->GetTarget().GetY(),Operation::Leixing::My_Bullet,Bullet_speed,0,My_Bullet2_Shanghai,Operation::up) });
			my_bullet.push_back({ my_bullet_images[4],my_bullet_images[5],Operation(My->GetTarget().GetX() + My->GetTarget().GetW() - 20,My->GetTarget().GetY(),Operation::Leixing::My_Bullet,Bullet_speed,0,My_Bullet2_Shanghai,Operation::up) });

			My_bullet_shanghai = My_Bullet2_Shanghai+ My_Bullet2_Shanghai;

		}
		//第六阶段
		else if (我的阶段 == 阶段::阶段六)
		{
			//火子弹
			my_bullet.push_back({ my_bullet_images[6],my_bullet_images[7],Operation(My->GetTarget().GetX() + 20 ,My->GetTarget().GetY(),Operation::Leixing::My_Bullet,Bullet_speed,0,My_Bullet3_Shanghai,Operation::up) });
			my_bullet.push_back({ my_bullet_images[6],my_bullet_images[7],Operation(My->GetTarget().GetX() + My->GetTarget().GetW() - 20,My->GetTarget().GetY(),Operation::Leixing::My_Bullet,Bullet_speed,0,My_Bullet3_Shanghai,Operation::up) });

			My_bullet_shanghai = My_Bullet3_Shanghai + My_Bullet3_Shanghai;


		}
		//第七阶段
		else if (我的阶段 == 阶段::阶段七)
		{
			//冰火两重天
			my_bullet.push_back({ my_bullet_images[4],my_bullet_images[5],Operation(My->GetTarget().GetX() + 20 ,My->GetTarget().GetY(),Operation::Leixing::My_Bullet,Ice_and_Fire_Bullet_speed,0,My_Bullet2_Shanghai,Operation::up) });
			my_bullet.push_back({ my_bullet_images[6],my_bullet_images[7],Operation(My->GetTarget().GetX() + My->GetTarget().GetW() - 20,My->GetTarget().GetY(),Operation::Leixing::My_Bullet,Ice_and_Fire_Bullet_speed,0,My_Bullet3_Shanghai,Operation::up) });

			My_bullet_shanghai = My_Bullet2_Shanghai + My_Bullet3_Shanghai;

		}
		//第八阶段
		else if (我的阶段 == 阶段::阶段八)
		{
			//两重烟花弹
			my_bullet.push_back({ my_bullet_images[2],my_bullet_images[3],Operation(My->GetTarget().GetX() + 20 ,My->GetTarget().GetY(),Operation::Leixing::My_Bullet,Bullet_speed,0,My_Bullet2_Shanghai,Operation::up) });
			my_bullet.push_back({ my_bullet_images[2],my_bullet_images[3],Operation(My->GetTarget().GetX() + My->GetTarget().GetW() - 20,My->GetTarget().GetY(),Operation::Leixing::My_Bullet,Bullet_speed,0,My_Bullet3_Shanghai,Operation::up) });

			My_bullet_shanghai = My_Bullet4_Shanghai + My_Bullet4_Shanghai;

		}
		//Boss阶段
		else if(我的阶段 == 阶段::BOSS阶段)
		{
			//两重烟花弹加终极子弹
			my_bullet.push_back({ my_bullet_images[2],my_bullet_images[3],Operation(My->GetTarget().GetX() + 20 ,My->GetTarget().GetY(),Operation::Leixing::My_Bullet,Bullet_speed,0,My_Bullet2_Shanghai,Operation::up) });
			my_bullet.push_back({ my_bullet_images[8],my_bullet_images[9],Operation(My->GetTarget().GetX() + My->GetTarget().GetW()/2,My->GetTarget().GetY(),Operation::Leixing::My_Bullet,Bullet_speed,0,My_Bullet3_Shanghai,Operation::up) });
			my_bullet.push_back({ my_bullet_images[2],my_bullet_images[3],Operation(My->GetTarget().GetX() + My->GetTarget().GetW() - 20,My->GetTarget().GetY(),Operation::Leixing::My_Bullet,Bullet_speed,0,My_Bullet3_Shanghai,Operation::up) });
			My_bullet_shanghai = My_Bullet4_Shanghai+ My_Bullet4_Shanghai+ My_Bullet5_Shanghai;
		}

	}
	//我方发射子弹
#if 0
	for (auto it = my_bullet.begin(); it != my_bullet.end();)
	{
		it->Draw();
		it->GetTarget().GetY() -= it->GetTarget().GetSpeed();

		if (it->GetTarget().GetY() <= 0)
		{
			it = my_bullet.erase(it);
		}
		else
		{
			++it;
		}
	}
#else
	for (auto it = my_bullet.begin(); it != my_bullet.end();)
	{
		it->Draw();
		it->GetTarget().GetY() -= it->GetTarget().GetSpeed();

		if (it->GetTarget().GetY() <= 0)
		{
			it = my_bullet.erase(it);
		}
		else
		{
			++it;
		}
	}
#endif

	//敌机创建子弹
	for (auto it = enemys.begin(); it != enemys.end(); ++it)
	{
		//第一阶段
		if (rand() % 100 == 2 && start_time<=20000)
		{
			if (it->GetTarget().GetLeixing() == Operation::Leixing::Enemy1)
			{
				enemy_bullet.push_back({ enemy_bullet_images[0],enemy_bullet_images[1],Operation(it->GetTarget().GetX() + it->GetTarget().GetW() / 2 - 25,it->GetTarget().GetY() + it->GetTarget().GetH(),Operation::Leixing::Enemy1_Bullet,Enemy_bullet_speed,0,Enemys_Bullet_Shanghai[0],Operation::down)});
			}
			else if (it->GetTarget().GetLeixing() == Operation::Leixing::Enemy3)
			{
				enemy_bullet.push_back({ enemy_bullet_images[2],enemy_bullet_images[3],Operation(it->GetTarget().GetX() + it->GetTarget().GetW() / 2 - 25,it->GetTarget().GetY() + it->GetTarget().GetH(),Operation::Leixing::Enemy3_Bullet,Enemy_bullet_speed,0,Enemys_Bullet_Shanghai[1],Operation::down)});
			}
			else if (it->GetTarget().GetLeixing() == Operation::Leixing::Enemy4)
			{
				enemy_bullet.push_back({ enemy_bullet_images[4],enemy_bullet_images[5],Operation(it->GetTarget().GetX() + it->GetTarget().GetW() / 2 - 25,it->GetTarget().GetY() + it->GetTarget().GetH(),Operation::Leixing::Enemy3_Bullet,Enemy_bullet_speed,0,Enemys_Bullet_Shanghai[2],Operation::down)});
			}
		}
		//第二阶段
		else if (rand() % 80 == 2 && start_time>=20000 && start_time<=40000)
		{
			if (it->GetTarget().GetLeixing() == Operation::Leixing::Enemy1)
			{
				enemy_bullet.push_back({ enemy_bullet_images[0],enemy_bullet_images[1],Operation(it->GetTarget().GetX() + it->GetTarget().GetW() / 2 - 25,it->GetTarget().GetY() + it->GetTarget().GetH(),Operation::Leixing::Enemy1_Bullet,Enemy_bullet_speed,0,Enemys_Bullet_Shanghai[0],Operation::down)});
			}
			else if (it->GetTarget().GetLeixing() == Operation::Leixing::Enemy3)
			{
				enemy_bullet.push_back({ enemy_bullet_images[2],enemy_bullet_images[3],Operation(it->GetTarget().GetX() + it->GetTarget().GetW() / 2 - 25,it->GetTarget().GetY() + it->GetTarget().GetH(),Operation::Leixing::Enemy3_Bullet,Enemy_bullet_speed,0,Enemys_Bullet_Shanghai[1],Operation::down)});
			}
			else if (it->GetTarget().GetLeixing() == Operation::Leixing::Enemy4)
			{
				enemy_bullet.push_back({ enemy_bullet_images[4],enemy_bullet_images[5],Operation(it->GetTarget().GetX() + it->GetTarget().GetW() / 2 - 25,it->GetTarget().GetY() + it->GetTarget().GetH(),Operation::Leixing::Enemy3_Bullet,Enemy_bullet_speed,0,Enemys_Bullet_Shanghai[2],Operation::down)});
			}

		}
		//第三阶段
		else if (rand() % 60 == 2 && start_time >= 40000)
		{
			if (it->GetTarget().GetLeixing() == Operation::Leixing::Enemy1)
			{
				enemy_bullet.push_back({ enemy_bullet_images[0],enemy_bullet_images[1],Operation(it->GetTarget().GetX() + it->GetTarget().GetW() / 2 - 25,it->GetTarget().GetY() + it->GetTarget().GetH(),Operation::Leixing::Enemy1_Bullet,Enemy_bullet_speed,0,Enemys_Bullet_Shanghai[0],Operation::down)});
			}
			else if (it->GetTarget().GetLeixing() == Operation::Leixing::Enemy3)
			{
				enemy_bullet.push_back({ enemy_bullet_images[2],enemy_bullet_images[3],Operation(it->GetTarget().GetX() + it->GetTarget().GetW() / 2 - 25,it->GetTarget().GetY() + it->GetTarget().GetH(),Operation::Leixing::Enemy3_Bullet,Enemy_bullet_speed,0,Enemys_Bullet_Shanghai[1],Operation::down)});
			}
			else if (it->GetTarget().GetLeixing() == Operation::Leixing::Enemy4)
			{
				enemy_bullet.push_back({ enemy_bullet_images[4],enemy_bullet_images[5],Operation(it->GetTarget().GetX() + it->GetTarget().GetW() / 2 - 25,it->GetTarget().GetY() + it->GetTarget().GetH(),Operation::Leixing::Enemy3_Bullet,Enemy_bullet_speed,0,Enemys_Bullet_Shanghai[2],Operation::down)});
			}

		}
		/*
		在此处创建敌方子弹
		*/
	}
	//Boss创建子弹
	if (Boss_come)
	{
		if (start_time >= 30000 && start_time <= 33000 && Timer(12, 200))
		{
			Boss_bullet.push_back({ enemy_bullet_images[4],enemy_bullet_images[5],Operation(Boss->GetTarget().GetX() + Boss->GetTarget().GetW() / 2 - 20,Boss->GetTarget().GetY() + Boss->GetTarget().GetH(),Operation::Leixing::Enemy1_Bullet,Enemy_bullet_speed,0,Enemys_Bullet_Shanghai[0],Operation::down) });
		}
		else if (start_time >= 36000 && start_time <= 39000 && Timer(12, 200))
		{
			Boss_bullet.push_back({ enemy_bullet_images[4],enemy_bullet_images[5],Operation(Boss->GetTarget().GetX() + Boss->GetTarget().GetW() / 2 - 100,Boss->GetTarget().GetY() + Boss->GetTarget().GetH()-50,Operation::Leixing::Enemy1_Bullet,Enemy_bullet_speed,0,Enemys_Bullet_Shanghai[0],Operation::down) });
			Boss_bullet.push_back({ enemy_bullet_images[4],enemy_bullet_images[5],Operation(Boss->GetTarget().GetX() + Boss->GetTarget().GetW() / 2 + 80,Boss->GetTarget().GetY() + Boss->GetTarget().GetH()-50,Operation::Leixing::Enemy1_Bullet,Enemy_bullet_speed,0,Enemys_Bullet_Shanghai[0],Operation::down) });

		}
		else if (start_time >= 42000 && start_time <= 45000 && Timer(12, 200))
		{
			Boss_bullet.push_back({ enemy_bullet_images[4],enemy_bullet_images[5],Operation(Boss->GetTarget().GetX() + Boss->GetTarget().GetW() / 2 - 60,Boss->GetTarget().GetY() + Boss->GetTarget().GetH() - 50,Operation::Leixing::Enemy1_Bullet,Enemy_bullet_speed,0,Enemys_Bullet_Shanghai[0],Operation::down) });
			Boss_bullet.push_back({ enemy_bullet_images[4],enemy_bullet_images[5],Operation(Boss->GetTarget().GetX() + Boss->GetTarget().GetW() / 2 ,Boss->GetTarget().GetY() + Boss->GetTarget().GetH() - 50,Operation::Leixing::Enemy1_Bullet,Enemy_bullet_speed,0,Enemys_Bullet_Shanghai[0],Operation::down) });

			Boss_bullet.push_back({ enemy_bullet_images[4],enemy_bullet_images[5],Operation(Boss->GetTarget().GetX() + Boss->GetTarget().GetW() / 2 + 60,Boss->GetTarget().GetY() + Boss->GetTarget().GetH() - 50,Operation::Leixing::Enemy1_Bullet,Enemy_bullet_speed,0,Enemys_Bullet_Shanghai[0],Operation::down) });
		}
		else if (start_time >= 48000/* && start_time <= 45000 */&& Timer(12, 200))
		{
			Boss_bullet.push_back({ enemy_bullet_images[4],enemy_bullet_images[5],Operation(Boss->GetTarget().GetX() + Boss->GetTarget().GetW() / 2 - 140,Boss->GetTarget().GetY() + Boss->GetTarget().GetH() - 50,Operation::Leixing::Enemy1_Bullet,Enemy_bullet_speed,0,Enemys_Bullet_Shanghai[0],Operation::down) });
			Boss_bullet.push_back({ enemy_bullet_images[4],enemy_bullet_images[5],Operation(Boss->GetTarget().GetX() + Boss->GetTarget().GetW() / 2 - 70 ,Boss->GetTarget().GetY() + Boss->GetTarget().GetH() - 50,Operation::Leixing::Enemy1_Bullet,Enemy_bullet_speed,0,Enemys_Bullet_Shanghai[0],Operation::down) });

			Boss_bullet.push_back({ enemy_bullet_images[4],enemy_bullet_images[5],Operation(Boss->GetTarget().GetX() + Boss->GetTarget().GetW() / 2 + 70,Boss->GetTarget().GetY() + Boss->GetTarget().GetH() - 50,Operation::Leixing::Enemy1_Bullet,Enemy_bullet_speed,0,Enemys_Bullet_Shanghai[0],Operation::down) });
			Boss_bullet.push_back({ enemy_bullet_images[4],enemy_bullet_images[5],Operation(Boss->GetTarget().GetX() + Boss->GetTarget().GetW() / 2 + 140,Boss->GetTarget().GetY() + Boss->GetTarget().GetH() - 50,Operation::Leixing::Enemy1_Bullet,Enemy_bullet_speed,0,Enemys_Bullet_Shanghai[0],Operation::down) });
		}
		

	}


	//Boss即将死亡，发射死亡激光
	if (Boss_come && Boss->GetTarget().GetBlood() <= BOSS_BLOOD / 5)
	{
		if (boss_jiguang.GetStart() != 动画::开始)		//如果此时没有激光
		{
			boss_jiguang.GetStart() = 动画::开始;		//当我发射激光的时候，设置此变量
			boss_jiguang.Gettime_start() = time(0);				//获得当前的时间
		}
		
	}

	//敌机发射子弹
	for (auto it = enemy_bullet.begin(); it != enemy_bullet.end();)
	{
		it->Draw();
		it->GetTarget().GetY() += it->GetTarget().GetSpeed();
		if (it->GetTarget().GetY() >= WINDOWS_H)
		{
			it = enemy_bullet.erase(it);
		}
		else
		{
			++it;
		}
		
	}
	//Boss发射子弹
	if (Boss_come)
	{
		for (auto it = Boss_bullet.begin(); it != Boss_bullet.end(); )
		{
			it->Draw();
			it->GetTarget().GetY() += it->GetTarget().GetSpeed();
			if (it->GetTarget().GetY() >= WINDOWS_H)
			{
				it = Boss_bullet.erase(it);
			}
			else
			{
				++it;
			}
		}
	}
}

//敌军的创建
void Game::Create_Enemy()
{
	int num = 0;
	num = rand() % 10;
	//产生敌人
	if (Timer(1, 250))	//敌机一号
	{
		enemys.push_back({ plane_images[2],plane_images[3], Operation(rand() % (WINDOWS_W - plane_images[2].GetImgW()), -50,Operation::Leixing::Enemy1, Enemy1_speed,Enemys_Blood[0],0, Operation::Dir::down)});
	}
	//8秒后产生冲锋飞机
	if (start_time>=6000 && Timer(2, 450) && (rand() % 10 == 5 || rand() % 10 == 6 || rand() % 10 == 8))	//敌机二号
	{
		enemys.push_back({ plane_images[4],plane_images[5], Operation(rand() % (WINDOWS_W - plane_images[4].GetImgW()), -50,Operation::Leixing::Enemy2, Enemy2_speed,Enemys_Blood[1],0, Operation::Dir::down)});
	}	
	//20秒后产生绿色飞机
	if (start_time >= 12000 && Timer(3, 500) && (rand() % 10 == 9))	//敌机三号
	{
		enemys.push_back({ plane_images[6],plane_images[7], Operation(rand() % (WINDOWS_W - plane_images[6].GetImgW()), -50,Operation::Leixing::Enemy3, Enemy3_speed,Enemys_Blood[2],0, Operation::Dir::down)});
	}
	//30秒后产生紫色飞机
	if (start_time >= 20000 && Timer(4, 600) && (rand()%10==5))	//敌机四号
	{
		enemys.push_back({ plane_images[8],plane_images[9], Operation(rand() % (WINDOWS_W - plane_images[8].GetImgW()), -50,Operation::Leixing::Enemy4, Enemy4_speed,Enemys_Blood[3],0, Operation::Dir::down)});
	}

	//Boss创建
	if (start_time >= 28000&&!Boss_come)
	{
		biaozhi[4].GetStart() = 动画::开始;
		biaozhi[4].Gettime_start() = clock();

	}
	// 30s后boss出现
	if (start_time >= 30000)
	{
		Boss_come = true;
		Boss->Draw();
		if (Boss->GetTarget().GetY() <= 0)
		{
			Boss->GetTarget().GetY() += Boss->GetTarget().GetSpeed();
		}
	}

	/*
	1. Boss的 出现时机
	
	2. Boss的子弹图片及射击方式完善
	
	3. Boss的子弹攻击我方
	
	4. 我方攻击Boss
	
	5. Boss的移动
	
	*/
	//敌机移动
	for (auto it = enemys.begin(); it != enemys.end();)
	{
		it->Draw();
		it->GetTarget().GetY() += it->GetTarget().GetSpeed();
		if (it->GetTarget().GetY() >= WINDOWS_H)
		{
			it = enemys.erase(it);
		}
		else
		{
			++it;
		}
	}


	//Boss左右移动
	if (Boss_come && Boss->GetTarget().GetBlood()<=BOSS_BLOOD/3)
	{
		if (Boss->GetTarget().GetDir() == Operation::Dir::right)
		{
			if (Boss->GetTarget().GetX() + Boss->GetTarget().GetW() <= WINDOWS_W)//往右移动
			{
				Boss->GetTarget().GetX() += Boss->GetTarget().GetSpeed();
			}
			else
			{
				Boss->GetTarget().GetDir() = Operation::Dir::left;
			}
		}
		if (Boss->GetTarget().GetDir() == Operation::Dir::left)
		{
			if (Boss->GetTarget().GetX() >= 0)//往左移动
			{
				Boss->GetTarget().GetX() -= Boss->GetTarget().GetSpeed();
			}
			else
			{
				Boss->GetTarget().GetDir() = Operation::Dir::right;
			}
		}
	}

}

//敌机的升级
void Game::Enemy_GrowUp()
{
	//每隔15秒，敌军升级一次
	if (Timer(11, 15000))
	{
		for (auto i = 0; i < Enemys_Blood.size(); ++i)
		{
			Enemys_Blood[i] += 1;
		}
		for (auto i = 0; i < Enemys_Bullet_Shanghai.size(); ++i)
		{
			Enemys_Bullet_Shanghai[i] += 1;
		}
	}
}

//攻击敌军
void Game::Bullet_To_Enemy()
{
	//我方攻击敌人
	for (auto it = my_bullet.begin(); it != my_bullet.end(); ++it)
	{
		for (auto it2 = enemys.begin(); it2 != enemys.end(); ++it2)
		{
			if (Bullet_Pengzhuang(*it, *it2))
			{
				it2->GetTarget().GetBlood() -= it->GetTarget().GetShanghai();
				if (it2->GetTarget().GetBlood() <= 0)
				{
					if (it2->GetTarget().GetLeixing() == Operation::Leixing::Enemy1)
					{
						score += Little_plane;
					}
					if (it2->GetTarget().GetLeixing() == Operation::Leixing::Enemy2)
					{

						score += Mid_plane;
					}
					if (it2->GetTarget().GetLeixing() == Operation::Leixing::Enemy3)
					{

						score += Big_plane;
					}
					if (it2->GetTarget().GetLeixing() == Operation::Leixing::Enemy4)
					{

						score += Biggg_plane;
					}

					it = my_bullet.erase(it);
					BoomZha(*it2);
					it2 = enemys.erase(it2);		//敌机死亡
					//绘制爆炸
					return;
				}
				it = my_bullet.erase(it);
				return;
			}
		}
	}
	//我方攻击Boss
	for (auto it = my_bullet.begin(); it != my_bullet.end(); ++it)
	{
		if (Bullet_Pengzhuang(*it, *Boss))
		{
			Boss->GetTarget().GetBlood() -= it->GetTarget().GetShanghai();
			if (Boss->GetTarget().GetBlood() <= 0)
			{
				Boss->GetTarget().GetIsDied() = true;
			}
			
			it = my_bullet.erase(it);
			return;
		}
	}

	//激光攻击敌军
	if (jiguang.GetStart() == 动画::开始)
	{
		for (auto it = enemys.begin(); it != enemys.end(); ++it)
		{
			if (Jiguang_Pengzhuang(*it, jiguang,动画::我方激光) && Timer(14,50))
			{
				it->GetTarget().GetBlood() -= 10;
				if (it->GetTarget().GetBlood() <= 0)
				{
					if (it->GetTarget().GetLeixing() == Operation::Leixing::Enemy1)
					{
						score += Little_plane;
					}
					if (it->GetTarget().GetLeixing() == Operation::Leixing::Enemy2)
					{

						score += Mid_plane;
					}
					if (it->GetTarget().GetLeixing() == Operation::Leixing::Enemy3)
					{

						score += Big_plane;
					}
					if (it->GetTarget().GetLeixing() == Operation::Leixing::Enemy4)
					{

						score += Biggg_plane;
					}

					BoomZha(*it);
					it = enemys.erase(it);
					return;
				}
			}

		}
	}
	//激光攻击Boss
	if (jiguang.GetStart() == 动画::开始 && Boss_come && Timer(18, 100))
	{
		/*
		只要发射激光，boss就掉血
		*/
		Boss->GetTarget().GetBlood() -= My激光伤害;
		if (Boss->GetTarget().GetBlood() <= 0)
		{
			Boss->GetTarget().GetIsDied() = true;
			return;
		}
	}
	
	//所有的敌人直接死亡
	if (hedan_flag)
	{

		for (auto it1 = enemys.begin(); it1 != enemys.end();)
		{
			if (it1->GetTarget().GetLeixing() == Operation::Leixing::Enemy1)
			{
				score += Little_plane;
			}
			if (it1->GetTarget().GetLeixing() == Operation::Leixing::Enemy2)
			{

				score += Mid_plane;
			}
			if (it1->GetTarget().GetLeixing() == Operation::Leixing::Enemy3)
			{

				score += Big_plane;
			}
			BoomZha(*it1);
			it1 = enemys.erase(it1);		//敌机死亡
			//绘制爆炸
		}
		hedan_flag = false;		//爆炸结束
	}
}

//敌军攻击我方
void Game::Bullet_To_Me()
{
	//敌人攻击我方
	for (auto it = enemy_bullet.begin(); it != enemy_bullet.end();)
	{
		if (Bullet_Pengzhuang(*it, *My))
		{
			if (hudun.GetStart() != 动画::开始)
			{
				//无敌状态
				My->GetTarget().GetBlood() -= it->GetTarget().GetShanghai();
			}
			it = enemy_bullet.erase(it);
			if (My->GetTarget().GetBlood() <= 0)
			{
				My->GetTarget().GetIsDied() = true;
				return;
			}
		}
		else
		{
			++it;
		}
	}
	//Boss子弹攻击我方
	if (Boss_come)
	{
		for (auto it = Boss_bullet.begin(); it != Boss_bullet.end();)
		{
			if (Bullet_Pengzhuang(*it, *My))
			{
				if (hudun.GetStart() != 动画::开始)
				{
					//无敌状态
					My->GetTarget().GetBlood() -= it->GetTarget().GetShanghai();
				}
				it = Boss_bullet.erase(it);
				if (My->GetTarget().GetBlood() <= 0)
				{
					My->GetTarget().GetIsDied() = true;
					return;
				}
			}
			else
			{
				++it;
			}
		}
	}
	//Boss激光攻击我方
	if (Boss_come && boss_jiguang.GetStart() == 动画::开始)
	{
		if (Jiguang_Pengzhuang(*My, boss_jiguang, 动画::敌方激光) && Timer(16, 100))
		{
			if (hudun.GetStart() != 动画::开始)
			{
				My->GetTarget().GetBlood() -= Boss激光伤害;
				if (My->GetTarget().GetBlood() <= 0)
				{
					My->GetTarget().GetIsDied() = true;
					return;
				}
			}
		}
	}

	//敌机碰撞我方飞机
	for (auto it2 = enemys.begin(); it2 != enemys.end(); ++it2)
	{
		if (Plane_Pengzhuang(*it2, *My) || Bullet_Pengzhuang(*it2,*My))
		{
			//不同敌人的类型有不同的碰撞伤害
			if (it2->GetTarget().GetLeixing() == Operation::Leixing::Enemy1)
			{
				if (hudun.GetStart() != 动画::开始)
				{
					My->GetTarget().GetBlood() -= Enemy1_Pengzhuang_Shanghai;
				}
			}
			else if (it2->GetTarget().GetLeixing() == Operation::Leixing::Enemy2)
			{
				if (hudun.GetStart() != 动画::开始)
				{
					My->GetTarget().GetBlood() -= Enemy2_Pengzhuang_Shanghai;
				}
			}
			else if (it2->GetTarget().GetLeixing() == Operation::Leixing::Enemy3)
			{
				if (hudun.GetStart() != 动画::开始)
				{
					My->GetTarget().GetBlood() -= Enemy3_Pengzhuang_Shanghai;
				}
			}
			else if (it2->GetTarget().GetLeixing() == Operation::Leixing::Enemy4)
			{
				if (hudun.GetStart() != 动画::开始)
				{
					My->GetTarget().GetBlood() -= Enemy4_Pengzhuang_Shanghai;
				}
			}

			BoomZha(*it2);
			it2 = enemys.erase(it2);
			return;
		}
	}
}

//随机产生道具
void Game::Create_Tools()
{
	//创建道具
	
	//核弹
	if (Timer(5, 15000))
	{
			
		tools.push_back({ Tool_images[0],Tool_images[1],Operation(rand() % (WINDOWS_W - Tool_images[0].GetImgW()),100,Operation::Leixing::核弹,Tools_Speed,-1,-1,Operation::Dir::down) });
	}
	//护盾
	if (Timer(6, 10000))
	{
		tools.push_back({ Tool_images[2],Tool_images[3],Operation(rand() % (WINDOWS_W - Tool_images[0].GetImgW()),100,Operation::Leixing::护盾,Tools_Speed,-1,-1,Operation::Dir::down) });
	}
	//加速
	if (Timer(7, 28000))
	{
		tools.push_back({ Tool_images[4],Tool_images[5],Operation(rand() % (WINDOWS_W - Tool_images[0].GetImgW()),100,Operation::Leixing::加速,Tools_Speed,-1,-1,Operation::Dir::down) });
	}
	//加血
	if (Timer(8, 25000))
	{
		tools.push_back({ Tool_images[6],Tool_images[7],Operation(rand() % (WINDOWS_W - Tool_images[0].GetImgW()),100,Operation::Leixing::加血,Tools_Speed,-1,-1,Operation::Dir::down) });
		
	}
	//子弹升级
	if (Timer(10, 8000))
	{
		tools.push_back({ Tool_images[10],Tool_images[11],Operation(rand() % (WINDOWS_W - Tool_images[0].GetImgW()),100,Operation::Leixing::子弹升级,Tools_Speed,-1,-1,Operation::Dir::down) });
	}
	if (Timer(13, 24000))
	{
		tools.push_back({ Tool_images[8],Tool_images[9],Operation(rand() % (WINDOWS_W - Tool_images[0].GetImgW()),100,Operation::Leixing::激光状态,Tools_Speed,-1,-1,Operation::Dir::down) });
	}


	//道具移动
	for (auto it = tools.begin(); it != tools.end(); )
	{
		it->Draw();
		it->GetTarget().GetY() += it->GetTarget().GetSpeed();
		//越界
		if (it->GetTarget().GetY() >= WINDOWS_H)
		{
			it = tools.erase(it);
		}
		else
		{
			++it;
		}
	}
}

//道具的效果
void Game::Tools_Good()
{
	char name[5][10] = { 0 };
	for (auto it = tools.begin(); it != tools.end(); ++it)
	{
		if ((Plane_Pengzhuang(*it,*My) || Bullet_Pengzhuang(*it,*My)) && it->GetTarget().GetLeixing() == Operation::Leixing::核弹)
		{
			biaozhi[1].GetFrame() = 1;
			biaozhi[1].GetStart() = 动画::开始;
			biaozhi[1].Gettime_start() = time(0);

			++hedan_num;
			//此核弹图片删除
			it = tools.erase(it);
			return;
		}
		else if ((Plane_Pengzhuang(*it, *My) || Bullet_Pengzhuang(*it, *My)) && it->GetTarget().GetLeixing() == Operation::Leixing::加血)
		{
			if (My->GetTarget().GetBlood() <= My_Plane_Blood)
			{
				biaozhi[2].GetFrame() = 1;
				biaozhi[2].GetStart() = 动画::开始;
				biaozhi[2].Gettime_start() = time(0);

				My->GetTarget().GetBlood() += 50;
			}

			it = tools.erase(it);
			return;
		}
		else if ((Plane_Pengzhuang(*it, *My) || Bullet_Pengzhuang(*it, *My)) && it->GetTarget().GetLeixing() == Operation::Leixing::加速)
		{
			if (My->GetTarget().GetSpeed() <= 20)
			{
				My->GetTarget().GetSpeed() += 1;
			}
			it = tools.erase(it);
			return;

		}
		else if ((Plane_Pengzhuang(*it, *My) || Bullet_Pengzhuang(*it, *My)) && it->GetTarget().GetLeixing() == Operation::Leixing::护盾)
		{
			biaozhi[3].GetFrame() = 1;
			biaozhi[3].GetStart() = 动画::开始;
			biaozhi[3].Gettime_start() = time(0);

			//效果 : 提供一个护盾，3秒内免疫伤害
			if (hudun.GetStart()!= 动画::开始)
			{
				hudun.GetStart() = 动画::开始;			//此变量护盾开始
				hudun.Gettime_start() = time(0);	//获得当前的时间
			}
			
			it = tools.erase(it);
			return;

		}
		else if ((Plane_Pengzhuang(*it, *My) || Bullet_Pengzhuang(*it, *My)) && it->GetTarget().GetLeixing() == Operation::Leixing::子弹升级)
		{
			if (我的阶段 < 阶段::BOSS阶段)
			{
				biaozhi[0].GetFrame() = 1;
				biaozhi[0].GetStart() = 动画::开始;
				biaozhi[0].Gettime_start() = time(0);

				++我的阶段;
			}
			it = tools.erase(it);
			return;
		}
		else if ((Plane_Pengzhuang(*it, *My) || Bullet_Pengzhuang(*it, *My)) && it->GetTarget().GetLeixing() == Operation::Leixing::激光状态)
		{
			//激光效果
			if (jiguang.GetStart() != 动画::开始)		//如果此时没有激光
			{
				jiguang.GetStart() = 动画::开始;					//当我发射激光的时候，设置此变量
				jiguang.Gettime_start() = time(0);				//获得当前的时间
			}
			it = tools.erase(it);
			return;
		}
	}

}

//爆炸信息传入
void Game::BoomZha(Object& baozha)
{
	if (baozha.GetTarget().GetIsDied())
	{
		//主角死亡
		my_boom.GetFrame() = 1;
		my_boom.GetX() = baozha.GetTarget().GetX();
		my_boom.GetY() = baozha.GetTarget().GetY();
		return;
	}
	//设置爆炸
	for (int i = 0; i < MAX_Boom; ++i)
	{
		if (boom[i].GetFrame() == 0)
		{
			boom[i].GetFrame() = 1;
			boom[i].GetX() = baozha.GetTarget().GetX();
			boom[i].GetY() = baozha.GetTarget().GetY();
			break;
		}
	}
	
}

//FPS控制
void Game::ConrtolFPS(int start_time)
{
	clock_t running_time = clock() - start_time;
	if (10 - running_time >= 0)
	{
		Sleep(10 - running_time);
	}
	FPS = 1000 / (clock() - start_time);
}

/*
碰撞检测
*/
//子弹的碰撞: a表示待检测的物体， b表示准备碰撞的物体
bool Game::Bullet_Pengzhuang(Object& a,Object& b)
{
	if (a.GetTarget().GetX() >= b.GetTarget().GetX() && a.GetTarget().GetX() <= b.GetTarget().GetX() + b.GetTarget().GetW() &&
		a.GetTarget().GetY() >= b.GetTarget().GetY() && a.GetTarget().GetY() <= b.GetTarget().GetY() + b.GetTarget().GetH())
	{
		return true;
	}
	return false;
}

//飞机的碰撞: a表示待检测的物体， b表示准备碰撞的物体
bool Game::Plane_Pengzhuang(Object& a, Object& b)
{
	if (a.GetTarget().GetX() + a.GetTarget().GetW() / 2 >= b.GetTarget().GetX() && a.GetTarget().GetX() + a.GetTarget().GetW() / 2 <= b.GetTarget().GetX() + b.GetTarget().GetW() &&
		a.GetTarget().GetY() + a.GetTarget().GetH() >= b.GetTarget().GetY() && a.GetTarget().GetY() + a.GetTarget().GetH() <= b.GetTarget().GetY() + b.GetTarget().GetH())
	{
		return true;
	}
	return false;
}

//激光的碰撞检测
bool Game::Jiguang_Pengzhuang(Object& a, 动画& b,动画::动画类型 type)
{
	if ((a.GetTarget().GetX() >= b.GetX() && a.GetTarget().GetX() <= b.GetX() + b.GetW(type)) ||
		(a.GetTarget().GetX()+a.GetTarget().GetW() >= b.GetX() && a.GetTarget().GetX()+a.GetTarget().GetW() <= b.GetX() + b.GetW(type)))
	{
		return true;
	}

	return false;
}


void  Game::isWin()
{
	if (Boss->GetTarget().GetIsDied())
	{
		auto ret = MessageBox(NULL, "你赢了", "提示", MB_SYSTEMMODAL | MB_YESNO);
		if (ret == IDYES)
		{
			exit(1);
		}
		else if (ret == IDNO)
		{
			exit(999);
		}
	}


}