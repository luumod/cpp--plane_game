#pragma once
#include "����.h"

class Game
{
public:
	enum �׶� { �׶�һ, �׶ζ�, �׶���, �׶���, �׶���, �׶���, �׶���, �׶ΰ�, BOSS�׶� };
	Game();
	bool Play_Game();								//��Ϸ��ѭ��
	void Draw();									//���ƹ���
	void Draw_Other();								//������Ʒ�Ļ���
	void �����Զ����Ļ���();
	void �����Զ����Ļ��ƽ���();
	void Create_Bullet();							//�����ӵ�
	void Create_Enemy();							//��������
	void Enemy_GrowUp();							//�о�����ʱ������
	
	void Bullet_To_Enemy();							//��������
	void Bullet_To_Me();							//���˹����ҷ�
	void Create_Tools();							//���ߵĲ���
	void Tools_Good();								//����Ч��
	void BoomZha(Object& baozha);					//��ը
	void ConrtolFPS(int start_time);				//֡�ʿ���
	bool Game_Over();								//�ж���Ϸ����
	void isWin();

	bool Bullet_Pengzhuang(Object& a, Object& b);	//�ӵ�����ײ���
	bool Plane_Pengzhuang(Object& a, Object& b);	//�л�����ײ���
	bool Jiguang_Pengzhuang(Object& a, ����& b, ����::�������� type);	//�������ײ���
private:

	clock_t start_time;
	int FPS;
	IMAGE bk;
	int My_bullet_shanghai;
	int hedan_num = 0;
	bool hedan_flag = false;				//�Ƿ�ʹ�ú˵�
	bool Boss_come = false;					//Boss��Ϯ
	int �ҵĽ׶� = �׶�һ;
	vector<int> Enemys_Blood;				//���˵�Ѫ��
	vector<int> Enemys_Bullet_Shanghai;		//���˵��ӵ��˺�
	Object* My;
	Object* Boss;							//Boss
	���� boom[MAX_Boom];	//�л���ը
	���� my_boom;			//�ҵı�ը	
	���� hudun;				//����
	���� jiguang;			//����
	���� boss_jiguang;		//Boss����

	vector<Button> button;					//��ť��
	vector<Picture> plane_images;			//�ɻ�ͼƬ
	vector<Picture> my_bullet_images;		//�ҷ��ӵ�ͼƬ
	vector<Picture> enemy_bullet_images;	//�л��ӵ�ͼƬ
	vector<Picture> Tool_images;			//����ͼƬ
	vector<Picture> Other_images;			//����ͼƬ


	vector<Object> my_bullet;				//�ҵ��ӵ�
	vector<Object> Super_bullet;			//�����ӵ�
	vector<Object> enemys;					//�л�
	vector<Object> enemy_bullet;			//�л��ӵ�
	vector<Object> Boss_bullet;				//Boss�ӵ�
	vector<Object> tools;					//������
	array<����,5> biaozhi;				//��־��
};