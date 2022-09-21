#include "���.h"

//ͼƬ��Դ�ļ���
Game::Game()
{
	loadimage(&bk, "./images1/bg5.jpg");
	start_time = 0;
	FPS = 0;
	plane_images = {
		{"./images1/plane1.png"},{"./images1/Yplane1.png" },//�ҷ��ɻ�		0 1
		{"./images1/enemy1.png"},{"./images1/Yenemy1.png"},	//�л�һ��		2 3
		{"./images1/enemy2.png"},{"./images1/Yenemy2.png"},	//�л�����		4 5
		{"./images1/enemy3.png"},{"./images1/Yenemy3.png"},	//�л�����		6 7
		{"./images1/enemy4.png"},{"./images1/Yenemy4.png"},	//�л��ĺ�		8 9
		{"./images1/Boss.png"},{"./images1/YBoss.png"},		//Boss		    10 11

	};
	my_bullet_images = {
		{"./images1/biu1.png"},{"./images1/Ybiu1.png"},		//�ҷ��ɻ��ӵ�	0 1
		{"./images1/biu2.png"},{"./images1/Ybiu2.png"},		//�ҷ��ɻ��ӵ�	2 3
		{"./images1/biu3.png"},{"./images1/Ybiu3.png"},		//�ҷ��ɻ��ӵ�	4 5
		{"./images1/biu4.png"},{"./images1/Ybiu4.png"},		//�ҷ��ɻ��ӵ�	6 7
		{"./images1/biu5.png"},{"./images1/Ybiu5.png"},		//�ҷ��ɻ��ӵ�	8 9
		{"./images1/biu5.png"},{"./images1/Ybiu5.png"},		//�ҷ��ɻ��ӵ�	8 9
		{"./images1/����.png"},{"./images1/Y����.png"},		//�ҷ��ɻ��ӵ�	10 11


	};

	enemy_bullet_images = {
		{"./images1/enemy_bullet1.png"},{"./images1/Yenemy_bullet1.png"},// 0 1
		{"./images1/enemy_bullet2.png"},{"./images1/Yenemy_bullet2.png"},// 2 3
		{"./images1/enemy_bullet3.png"},{"./images1/Yenemy_bullet3.png"},// 4 5
		{"./images1/Boss_bullet1.png"},{"./images1/YBoss_bullet1.png"},	// 6 7
		{"./images1/Boss����.png"},{"./images1/YBoss����.png"},	// 6 7

	};

	Tool_images = {
		{"./common/�˵�����.png"},{"./common/Y�˵�����.png"},	// 0 1
		{"./common/����.png"},{"./common/Y����.png"},			// 2 3
		{"./common/����.png"},{"./common/Y����.png"},			// 4 5
		{"./common/��Ѫ.png"},{"./common/Y��Ѫ.png"},			// 6 7
		{"./common/�ӵ�����.png"},{"./common/Y�ӵ�����.png"},	// 8 9
		{"./common/�ӵ�����.png"},{"./common/Y�ӵ�����.png"},	// 10 11


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

//��Ϸ��ѭ��
bool Game::Play_Game()
{
	start_time = clock();

	BeginBatchDraw();
	Draw();					//�ɻ��������
	Draw_Other();			//��������
	�����Զ����Ļ���();
	�����Զ����Ļ��ƽ���();

	My->Move();
	Create_Bullet();		//�ӵ�
	Create_Enemy();			//�л�
	Enemy_GrowUp();
	Bullet_To_Enemy();			//��ײ���
	Bullet_To_Me();
	
	Create_Tools();
	Tools_Good();
	EndBatchDraw();

	ConrtolFPS(start_time);	//֡�ʿ���
	//cout << start_time << endl;
	isWin();
	return Game_Over();
}

//��Ϸ������ʾ
bool Game::Game_Over()
{
	if (My->GetTarget().GetIsDied())
	{
		//���Ǳ�ը��������
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
		return GAME_OVER;		//��Ϸ����
	}
	return GAME_NOT_OVER;		//��Ϸ����
}

//������Ҫ��Ʒ
void Game::Draw()
{
	putimage(0, 0, &bk);
	
	My->Draw();


	if (hedan_num > 0 && GetAsyncKeyState(VK_RETURN) &&Timer(9,500))
	{
		//ʹ�ú˵�
		hedan_flag = true;
		--hedan_num;
	}
}

//����������Ʒ
void Game::Draw_Other()
{
	setfillcolor(RED);
	fillrectangle(WINDOWS_W, 0, WINDOWS_GAME_W, WINDOWS_GAME_H);
	setfillcolor(RED);

	char str[10][20] = { 0 };
	setbkmode(TRANSPARENT);
	settextstyle(30, 0, "΢���ź�");
	settextcolor(YELLOW);
	sprintf(str[0], "FPS:%d", FPS);
	outtextxy(10, 10, str[0]);

	settextstyle(35, 0, "΢���ź�");
	sprintf(str[1], "�÷�:%d", score);
	outtextxy(WINDOWS_W + 10, 10, str[1]);

	sprintf(str[2], "����:");
	outtextxy(WINDOWS_W +2, 100, str[2]);

	sprintf(str[3], "Ѫ��:%d", My->GetTarget().GetBlood());
	outtextxy(WINDOWS_W + (WINDOWS_GAME_W - WINDOWS_W - textwidth(str[3])) / 2 - 20, 150, str[3]);

	sprintf(str[4], "�ٶ�: %d", My->GetTarget().GetSpeed());
	outtextxy(WINDOWS_W + (WINDOWS_GAME_W - WINDOWS_W - textwidth(str[4])) / 2 - 20, 200, str[4]);

	sprintf(str[5], "�˺�: %d", My_bullet_shanghai);
	outtextxy(WINDOWS_W + (WINDOWS_GAME_W - WINDOWS_W - textwidth(str[5])) / 2 - 20, 250, str[5]);

	sprintf(str[6], "�ӵ�: ");
	outtextxy(WINDOWS_W + (WINDOWS_GAME_W - WINDOWS_W - textwidth(str[6])) / 2 - 20, 300, str[6]);

	sprintf(str[7], "�˵�: %d", hedan_num);
	outtextxy(WINDOWS_W + (WINDOWS_GAME_W - WINDOWS_W - textwidth(str[7])) / 2 - 20, 350, str[7]);

	setfillcolor(RGB(123, 255, 56));
	rectangle(WINDOWS_W / 2 -My_Plane_Blood / 2, WINDOWS_H - 20, WINDOWS_W / 2 + My_Plane_Blood / 2, WINDOWS_H - 10);
	int hp;
	hp = My_Plane_Blood / 2 - My->GetTarget().GetBlood();
	fillrectangle(WINDOWS_W / 2 - My_Plane_Blood / 2, WINDOWS_H - 20, WINDOWS_W / 2 - hp, WINDOWS_H - 10);
	
}

void  Game::�����Զ����Ļ���()
{
	//���Ʊ�ը
	for (int i = 0; i < MAX_Boom; ++i)
	{
		boom[i].DrawBoom();
	}

	//���ƻ���
	hudun.Draw(My->GetTarget().GetX(), My->GetTarget().GetY(), ����::�ҷ�����);

	//���Ƽ������
	jiguang.Draw(My->GetTarget().GetX() + 10, My->GetTarget().GetY() - jiguang.Getimage(����::�ҷ�����)->getheight() + 50, ����::�ҷ�����);
	boss_jiguang.Draw(Boss->GetTarget().GetX() + 120, Boss->GetTarget().GetY() + Boss->GetTarget().GetH(), ����::�з�����);


	//���ƻ�ȡ���ߵ���ʾ
	biaozhi[0].Draw(WINDOWS_W / 2 - 200, WINDOWS_H / 2, ����::����������ʾ);

	biaozhi[1].Draw(5, WINDOWS_H - 30, ����::��ɱ��ʾ);

	biaozhi[2].Draw(5, WINDOWS_H - 30, ����::��Ѫ��ʾ);

	biaozhi[3].Draw(5, WINDOWS_H - 30, ����::������ʾ);

	biaozhi[4].Draw(WINDOWS_W / 2 - biaozhi[4].GetW(����::Boss���־���) / 2, WINDOWS_H / 2 - biaozhi[4].GetH(����::Boss���־���) / 2, ����::Boss���־���);

}

void  Game::�����Զ����Ļ��ƽ���()
{
	//���ܽ�������
	hudun.EndDraw();

	//�����������
	jiguang.EndDraw();

	//Boss������ƽ���
	//boss_jiguang.EndDraw();

	//����������ʾ
	biaozhi[0].EndDraw();

	//��ɱ��ʾ
	biaozhi[1].EndDraw();

	//��Ѫ��ʾ
	biaozhi[2].EndDraw();

	//������ʾ
	biaozhi[3].EndDraw();

	//Boss���־���
	biaozhi[4].EndDraw();
	cout << Boss->GetTarget().GetBlood() << endl;

}

//�ӵ��Ĵ���������
void Game::Create_Bullet()
{
	//�ҷ������ӵ�
	if (GetAsyncKeyState(VK_SPACE) && Timer(0, 150))
	{
		//��һ�׶�
		if (�ҵĽ׶�==�׶�::�׶�һ)
		{
			my_bullet.push_back({ my_bullet_images[0],my_bullet_images[1],Operation(My->GetTarget().GetX() + My->GetTarget().GetW() / 2 - 25,My->GetTarget().GetY(),Operation::Leixing::My_Bullet,Bullet_speed,0,My_Bullet1_Shanghai,Operation::up) });
			My_bullet_shanghai = my_bullet.back().GetTarget().GetShanghai();
		}
		//�ڶ��׶�
		else if (�ҵĽ׶� == �׶�::�׶ζ�)
		{
			//�����ӵ�
			my_bullet.push_back({ my_bullet_images[0],my_bullet_images[1],Operation(My->GetTarget().GetX() + 20 ,My->GetTarget().GetY(),Operation::Leixing::My_Bullet,Bullet_speed,0,My_Bullet1_Shanghai,Operation::up) });
			my_bullet.push_back({ my_bullet_images[0],my_bullet_images[1],Operation(My->GetTarget().GetX() + My->GetTarget().GetW() - 20,My->GetTarget().GetY(),Operation::Leixing::My_Bullet,Bullet_speed,0,My_Bullet1_Shanghai,Operation::up) });
			My_bullet_shanghai = my_bullet.back().GetTarget().GetShanghai() * 2;

		}
		//�����׶�
		else if (�ҵĽ׶� == �׶�::�׶���)
		{
			//�����ӵ�
			my_bullet.push_back({ my_bullet_images[0],my_bullet_images[1],Operation(My->GetTarget().GetX() + My->GetTarget().GetW() / 2,My->GetTarget().GetY(),Operation::Leixing::My_Bullet,Bullet_speed,0,My_Bullet1_Shanghai,Operation::up) });

			my_bullet.push_back({ my_bullet_images[0],my_bullet_images[1],Operation(My->GetTarget().GetX() +20 ,My->GetTarget().GetY(),Operation::Leixing::My_Bullet,Bullet_speed,0,My_Bullet1_Shanghai,Operation::up) });
			my_bullet.push_back({ my_bullet_images[0],my_bullet_images[1],Operation(My->GetTarget().GetX() + My->GetTarget().GetW() - 20,My->GetTarget().GetY(),Operation::Leixing::My_Bullet,Bullet_speed,0,My_Bullet1_Shanghai,Operation::up) });
			My_bullet_shanghai = my_bullet.back().GetTarget().GetShanghai() * 3;

		}
		//���Ľ׶�
		else if (�ҵĽ׶� == �׶�::�׶���)
		{
			//�����ӵ� �̻���
			my_bullet.push_back({ my_bullet_images[2],my_bullet_images[3],Operation(My->GetTarget().GetX() + My->GetTarget().GetW() / 2,My->GetTarget().GetY(),Operation::Leixing::My_Bullet,Bullet_speed,0,My_Bullet4_Shanghai,Operation::up) });

			my_bullet.push_back({ my_bullet_images[0],my_bullet_images[1],Operation(My->GetTarget().GetX() + 20 ,My->GetTarget().GetY(),Operation::Leixing::My_Bullet,Bullet_speed,0,My_Bullet1_Shanghai,Operation::up) });
			my_bullet.push_back({ my_bullet_images[0],my_bullet_images[1],Operation(My->GetTarget().GetX() + My->GetTarget().GetW() - 20,My->GetTarget().GetY(),Operation::Leixing::My_Bullet,Bullet_speed,0,My_Bullet1_Shanghai,Operation::up) });

			My_bullet_shanghai = My_Bullet1_Shanghai+ My_Bullet1_Shanghai+ My_Bullet4_Shanghai;

		}
		//����׶�
		else if (�ҵĽ׶� == �׶�::�׶���)
		{
			//���ӵ�
			my_bullet.push_back({ my_bullet_images[4],my_bullet_images[5],Operation(My->GetTarget().GetX() + 20 ,My->GetTarget().GetY(),Operation::Leixing::My_Bullet,Bullet_speed,0,My_Bullet2_Shanghai,Operation::up) });
			my_bullet.push_back({ my_bullet_images[4],my_bullet_images[5],Operation(My->GetTarget().GetX() + My->GetTarget().GetW() - 20,My->GetTarget().GetY(),Operation::Leixing::My_Bullet,Bullet_speed,0,My_Bullet2_Shanghai,Operation::up) });

			My_bullet_shanghai = My_Bullet2_Shanghai+ My_Bullet2_Shanghai;

		}
		//�����׶�
		else if (�ҵĽ׶� == �׶�::�׶���)
		{
			//���ӵ�
			my_bullet.push_back({ my_bullet_images[6],my_bullet_images[7],Operation(My->GetTarget().GetX() + 20 ,My->GetTarget().GetY(),Operation::Leixing::My_Bullet,Bullet_speed,0,My_Bullet3_Shanghai,Operation::up) });
			my_bullet.push_back({ my_bullet_images[6],my_bullet_images[7],Operation(My->GetTarget().GetX() + My->GetTarget().GetW() - 20,My->GetTarget().GetY(),Operation::Leixing::My_Bullet,Bullet_speed,0,My_Bullet3_Shanghai,Operation::up) });

			My_bullet_shanghai = My_Bullet3_Shanghai + My_Bullet3_Shanghai;


		}
		//���߽׶�
		else if (�ҵĽ׶� == �׶�::�׶���)
		{
			//����������
			my_bullet.push_back({ my_bullet_images[4],my_bullet_images[5],Operation(My->GetTarget().GetX() + 20 ,My->GetTarget().GetY(),Operation::Leixing::My_Bullet,Ice_and_Fire_Bullet_speed,0,My_Bullet2_Shanghai,Operation::up) });
			my_bullet.push_back({ my_bullet_images[6],my_bullet_images[7],Operation(My->GetTarget().GetX() + My->GetTarget().GetW() - 20,My->GetTarget().GetY(),Operation::Leixing::My_Bullet,Ice_and_Fire_Bullet_speed,0,My_Bullet3_Shanghai,Operation::up) });

			My_bullet_shanghai = My_Bullet2_Shanghai + My_Bullet3_Shanghai;

		}
		//�ڰ˽׶�
		else if (�ҵĽ׶� == �׶�::�׶ΰ�)
		{
			//�����̻���
			my_bullet.push_back({ my_bullet_images[2],my_bullet_images[3],Operation(My->GetTarget().GetX() + 20 ,My->GetTarget().GetY(),Operation::Leixing::My_Bullet,Bullet_speed,0,My_Bullet2_Shanghai,Operation::up) });
			my_bullet.push_back({ my_bullet_images[2],my_bullet_images[3],Operation(My->GetTarget().GetX() + My->GetTarget().GetW() - 20,My->GetTarget().GetY(),Operation::Leixing::My_Bullet,Bullet_speed,0,My_Bullet3_Shanghai,Operation::up) });

			My_bullet_shanghai = My_Bullet4_Shanghai + My_Bullet4_Shanghai;

		}
		//Boss�׶�
		else if(�ҵĽ׶� == �׶�::BOSS�׶�)
		{
			//�����̻������ռ��ӵ�
			my_bullet.push_back({ my_bullet_images[2],my_bullet_images[3],Operation(My->GetTarget().GetX() + 20 ,My->GetTarget().GetY(),Operation::Leixing::My_Bullet,Bullet_speed,0,My_Bullet2_Shanghai,Operation::up) });
			my_bullet.push_back({ my_bullet_images[8],my_bullet_images[9],Operation(My->GetTarget().GetX() + My->GetTarget().GetW()/2,My->GetTarget().GetY(),Operation::Leixing::My_Bullet,Bullet_speed,0,My_Bullet3_Shanghai,Operation::up) });
			my_bullet.push_back({ my_bullet_images[2],my_bullet_images[3],Operation(My->GetTarget().GetX() + My->GetTarget().GetW() - 20,My->GetTarget().GetY(),Operation::Leixing::My_Bullet,Bullet_speed,0,My_Bullet3_Shanghai,Operation::up) });
			My_bullet_shanghai = My_Bullet4_Shanghai+ My_Bullet4_Shanghai+ My_Bullet5_Shanghai;
		}

	}
	//�ҷ������ӵ�
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

	//�л������ӵ�
	for (auto it = enemys.begin(); it != enemys.end(); ++it)
	{
		//��һ�׶�
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
		//�ڶ��׶�
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
		//�����׶�
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
		�ڴ˴������з��ӵ�
		*/
	}
	//Boss�����ӵ�
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


	//Boss����������������������
	if (Boss_come && Boss->GetTarget().GetBlood() <= BOSS_BLOOD / 5)
	{
		if (boss_jiguang.GetStart() != ����::��ʼ)		//�����ʱû�м���
		{
			boss_jiguang.GetStart() = ����::��ʼ;		//���ҷ��伤���ʱ�����ô˱���
			boss_jiguang.Gettime_start() = time(0);				//��õ�ǰ��ʱ��
		}
		
	}

	//�л������ӵ�
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
	//Boss�����ӵ�
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

//�о��Ĵ���
void Game::Create_Enemy()
{
	int num = 0;
	num = rand() % 10;
	//��������
	if (Timer(1, 250))	//�л�һ��
	{
		enemys.push_back({ plane_images[2],plane_images[3], Operation(rand() % (WINDOWS_W - plane_images[2].GetImgW()), -50,Operation::Leixing::Enemy1, Enemy1_speed,Enemys_Blood[0],0, Operation::Dir::down)});
	}
	//8���������ɻ�
	if (start_time>=6000 && Timer(2, 450) && (rand() % 10 == 5 || rand() % 10 == 6 || rand() % 10 == 8))	//�л�����
	{
		enemys.push_back({ plane_images[4],plane_images[5], Operation(rand() % (WINDOWS_W - plane_images[4].GetImgW()), -50,Operation::Leixing::Enemy2, Enemy2_speed,Enemys_Blood[1],0, Operation::Dir::down)});
	}	
	//20��������ɫ�ɻ�
	if (start_time >= 12000 && Timer(3, 500) && (rand() % 10 == 9))	//�л�����
	{
		enemys.push_back({ plane_images[6],plane_images[7], Operation(rand() % (WINDOWS_W - plane_images[6].GetImgW()), -50,Operation::Leixing::Enemy3, Enemy3_speed,Enemys_Blood[2],0, Operation::Dir::down)});
	}
	//30��������ɫ�ɻ�
	if (start_time >= 20000 && Timer(4, 600) && (rand()%10==5))	//�л��ĺ�
	{
		enemys.push_back({ plane_images[8],plane_images[9], Operation(rand() % (WINDOWS_W - plane_images[8].GetImgW()), -50,Operation::Leixing::Enemy4, Enemy4_speed,Enemys_Blood[3],0, Operation::Dir::down)});
	}

	//Boss����
	if (start_time >= 28000&&!Boss_come)
	{
		biaozhi[4].GetStart() = ����::��ʼ;
		biaozhi[4].Gettime_start() = clock();

	}
	// 30s��boss����
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
	1. Boss�� ����ʱ��
	
	2. Boss���ӵ�ͼƬ�������ʽ����
	
	3. Boss���ӵ������ҷ�
	
	4. �ҷ�����Boss
	
	5. Boss���ƶ�
	
	*/
	//�л��ƶ�
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


	//Boss�����ƶ�
	if (Boss_come && Boss->GetTarget().GetBlood()<=BOSS_BLOOD/3)
	{
		if (Boss->GetTarget().GetDir() == Operation::Dir::right)
		{
			if (Boss->GetTarget().GetX() + Boss->GetTarget().GetW() <= WINDOWS_W)//�����ƶ�
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
			if (Boss->GetTarget().GetX() >= 0)//�����ƶ�
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

//�л�������
void Game::Enemy_GrowUp()
{
	//ÿ��15�룬�о�����һ��
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

//�����о�
void Game::Bullet_To_Enemy()
{
	//�ҷ���������
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
					it2 = enemys.erase(it2);		//�л�����
					//���Ʊ�ը
					return;
				}
				it = my_bullet.erase(it);
				return;
			}
		}
	}
	//�ҷ�����Boss
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

	//���⹥���о�
	if (jiguang.GetStart() == ����::��ʼ)
	{
		for (auto it = enemys.begin(); it != enemys.end(); ++it)
		{
			if (Jiguang_Pengzhuang(*it, jiguang,����::�ҷ�����) && Timer(14,50))
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
	//���⹥��Boss
	if (jiguang.GetStart() == ����::��ʼ && Boss_come && Timer(18, 100))
	{
		/*
		ֻҪ���伤�⣬boss�͵�Ѫ
		*/
		Boss->GetTarget().GetBlood() -= My�����˺�;
		if (Boss->GetTarget().GetBlood() <= 0)
		{
			Boss->GetTarget().GetIsDied() = true;
			return;
		}
	}
	
	//���еĵ���ֱ������
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
			it1 = enemys.erase(it1);		//�л�����
			//���Ʊ�ը
		}
		hedan_flag = false;		//��ը����
	}
}

//�о������ҷ�
void Game::Bullet_To_Me()
{
	//���˹����ҷ�
	for (auto it = enemy_bullet.begin(); it != enemy_bullet.end();)
	{
		if (Bullet_Pengzhuang(*it, *My))
		{
			if (hudun.GetStart() != ����::��ʼ)
			{
				//�޵�״̬
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
	//Boss�ӵ������ҷ�
	if (Boss_come)
	{
		for (auto it = Boss_bullet.begin(); it != Boss_bullet.end();)
		{
			if (Bullet_Pengzhuang(*it, *My))
			{
				if (hudun.GetStart() != ����::��ʼ)
				{
					//�޵�״̬
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
	//Boss���⹥���ҷ�
	if (Boss_come && boss_jiguang.GetStart() == ����::��ʼ)
	{
		if (Jiguang_Pengzhuang(*My, boss_jiguang, ����::�з�����) && Timer(16, 100))
		{
			if (hudun.GetStart() != ����::��ʼ)
			{
				My->GetTarget().GetBlood() -= Boss�����˺�;
				if (My->GetTarget().GetBlood() <= 0)
				{
					My->GetTarget().GetIsDied() = true;
					return;
				}
			}
		}
	}

	//�л���ײ�ҷ��ɻ�
	for (auto it2 = enemys.begin(); it2 != enemys.end(); ++it2)
	{
		if (Plane_Pengzhuang(*it2, *My) || Bullet_Pengzhuang(*it2,*My))
		{
			//��ͬ���˵������в�ͬ����ײ�˺�
			if (it2->GetTarget().GetLeixing() == Operation::Leixing::Enemy1)
			{
				if (hudun.GetStart() != ����::��ʼ)
				{
					My->GetTarget().GetBlood() -= Enemy1_Pengzhuang_Shanghai;
				}
			}
			else if (it2->GetTarget().GetLeixing() == Operation::Leixing::Enemy2)
			{
				if (hudun.GetStart() != ����::��ʼ)
				{
					My->GetTarget().GetBlood() -= Enemy2_Pengzhuang_Shanghai;
				}
			}
			else if (it2->GetTarget().GetLeixing() == Operation::Leixing::Enemy3)
			{
				if (hudun.GetStart() != ����::��ʼ)
				{
					My->GetTarget().GetBlood() -= Enemy3_Pengzhuang_Shanghai;
				}
			}
			else if (it2->GetTarget().GetLeixing() == Operation::Leixing::Enemy4)
			{
				if (hudun.GetStart() != ����::��ʼ)
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

//�����������
void Game::Create_Tools()
{
	//��������
	
	//�˵�
	if (Timer(5, 15000))
	{
			
		tools.push_back({ Tool_images[0],Tool_images[1],Operation(rand() % (WINDOWS_W - Tool_images[0].GetImgW()),100,Operation::Leixing::�˵�,Tools_Speed,-1,-1,Operation::Dir::down) });
	}
	//����
	if (Timer(6, 10000))
	{
		tools.push_back({ Tool_images[2],Tool_images[3],Operation(rand() % (WINDOWS_W - Tool_images[0].GetImgW()),100,Operation::Leixing::����,Tools_Speed,-1,-1,Operation::Dir::down) });
	}
	//����
	if (Timer(7, 28000))
	{
		tools.push_back({ Tool_images[4],Tool_images[5],Operation(rand() % (WINDOWS_W - Tool_images[0].GetImgW()),100,Operation::Leixing::����,Tools_Speed,-1,-1,Operation::Dir::down) });
	}
	//��Ѫ
	if (Timer(8, 25000))
	{
		tools.push_back({ Tool_images[6],Tool_images[7],Operation(rand() % (WINDOWS_W - Tool_images[0].GetImgW()),100,Operation::Leixing::��Ѫ,Tools_Speed,-1,-1,Operation::Dir::down) });
		
	}
	//�ӵ�����
	if (Timer(10, 8000))
	{
		tools.push_back({ Tool_images[10],Tool_images[11],Operation(rand() % (WINDOWS_W - Tool_images[0].GetImgW()),100,Operation::Leixing::�ӵ�����,Tools_Speed,-1,-1,Operation::Dir::down) });
	}
	if (Timer(13, 24000))
	{
		tools.push_back({ Tool_images[8],Tool_images[9],Operation(rand() % (WINDOWS_W - Tool_images[0].GetImgW()),100,Operation::Leixing::����״̬,Tools_Speed,-1,-1,Operation::Dir::down) });
	}


	//�����ƶ�
	for (auto it = tools.begin(); it != tools.end(); )
	{
		it->Draw();
		it->GetTarget().GetY() += it->GetTarget().GetSpeed();
		//Խ��
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

//���ߵ�Ч��
void Game::Tools_Good()
{
	char name[5][10] = { 0 };
	for (auto it = tools.begin(); it != tools.end(); ++it)
	{
		if ((Plane_Pengzhuang(*it,*My) || Bullet_Pengzhuang(*it,*My)) && it->GetTarget().GetLeixing() == Operation::Leixing::�˵�)
		{
			biaozhi[1].GetFrame() = 1;
			biaozhi[1].GetStart() = ����::��ʼ;
			biaozhi[1].Gettime_start() = time(0);

			++hedan_num;
			//�˺˵�ͼƬɾ��
			it = tools.erase(it);
			return;
		}
		else if ((Plane_Pengzhuang(*it, *My) || Bullet_Pengzhuang(*it, *My)) && it->GetTarget().GetLeixing() == Operation::Leixing::��Ѫ)
		{
			if (My->GetTarget().GetBlood() <= My_Plane_Blood)
			{
				biaozhi[2].GetFrame() = 1;
				biaozhi[2].GetStart() = ����::��ʼ;
				biaozhi[2].Gettime_start() = time(0);

				My->GetTarget().GetBlood() += 50;
			}

			it = tools.erase(it);
			return;
		}
		else if ((Plane_Pengzhuang(*it, *My) || Bullet_Pengzhuang(*it, *My)) && it->GetTarget().GetLeixing() == Operation::Leixing::����)
		{
			if (My->GetTarget().GetSpeed() <= 20)
			{
				My->GetTarget().GetSpeed() += 1;
			}
			it = tools.erase(it);
			return;

		}
		else if ((Plane_Pengzhuang(*it, *My) || Bullet_Pengzhuang(*it, *My)) && it->GetTarget().GetLeixing() == Operation::Leixing::����)
		{
			biaozhi[3].GetFrame() = 1;
			biaozhi[3].GetStart() = ����::��ʼ;
			biaozhi[3].Gettime_start() = time(0);

			//Ч�� : �ṩһ�����ܣ�3���������˺�
			if (hudun.GetStart()!= ����::��ʼ)
			{
				hudun.GetStart() = ����::��ʼ;			//�˱������ܿ�ʼ
				hudun.Gettime_start() = time(0);	//��õ�ǰ��ʱ��
			}
			
			it = tools.erase(it);
			return;

		}
		else if ((Plane_Pengzhuang(*it, *My) || Bullet_Pengzhuang(*it, *My)) && it->GetTarget().GetLeixing() == Operation::Leixing::�ӵ�����)
		{
			if (�ҵĽ׶� < �׶�::BOSS�׶�)
			{
				biaozhi[0].GetFrame() = 1;
				biaozhi[0].GetStart() = ����::��ʼ;
				biaozhi[0].Gettime_start() = time(0);

				++�ҵĽ׶�;
			}
			it = tools.erase(it);
			return;
		}
		else if ((Plane_Pengzhuang(*it, *My) || Bullet_Pengzhuang(*it, *My)) && it->GetTarget().GetLeixing() == Operation::Leixing::����״̬)
		{
			//����Ч��
			if (jiguang.GetStart() != ����::��ʼ)		//�����ʱû�м���
			{
				jiguang.GetStart() = ����::��ʼ;					//���ҷ��伤���ʱ�����ô˱���
				jiguang.Gettime_start() = time(0);				//��õ�ǰ��ʱ��
			}
			it = tools.erase(it);
			return;
		}
	}

}

//��ը��Ϣ����
void Game::BoomZha(Object& baozha)
{
	if (baozha.GetTarget().GetIsDied())
	{
		//��������
		my_boom.GetFrame() = 1;
		my_boom.GetX() = baozha.GetTarget().GetX();
		my_boom.GetY() = baozha.GetTarget().GetY();
		return;
	}
	//���ñ�ը
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

//FPS����
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
��ײ���
*/
//�ӵ�����ײ: a��ʾ���������壬 b��ʾ׼����ײ������
bool Game::Bullet_Pengzhuang(Object& a,Object& b)
{
	if (a.GetTarget().GetX() >= b.GetTarget().GetX() && a.GetTarget().GetX() <= b.GetTarget().GetX() + b.GetTarget().GetW() &&
		a.GetTarget().GetY() >= b.GetTarget().GetY() && a.GetTarget().GetY() <= b.GetTarget().GetY() + b.GetTarget().GetH())
	{
		return true;
	}
	return false;
}

//�ɻ�����ײ: a��ʾ���������壬 b��ʾ׼����ײ������
bool Game::Plane_Pengzhuang(Object& a, Object& b)
{
	if (a.GetTarget().GetX() + a.GetTarget().GetW() / 2 >= b.GetTarget().GetX() && a.GetTarget().GetX() + a.GetTarget().GetW() / 2 <= b.GetTarget().GetX() + b.GetTarget().GetW() &&
		a.GetTarget().GetY() + a.GetTarget().GetH() >= b.GetTarget().GetY() && a.GetTarget().GetY() + a.GetTarget().GetH() <= b.GetTarget().GetY() + b.GetTarget().GetH())
	{
		return true;
	}
	return false;
}

//�������ײ���
bool Game::Jiguang_Pengzhuang(Object& a, ����& b,����::�������� type)
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
		auto ret = MessageBox(NULL, "��Ӯ��", "��ʾ", MB_SYSTEMMODAL | MB_YESNO);
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