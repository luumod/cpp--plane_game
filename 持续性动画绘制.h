#pragma once
#include "common.h"
#include "ͼƬ.h"

/*
�����Զ����Ļ���
*/
class ����
{
public:
	enum �������� {�ҷ�����,�з�����,�ҷ�����,����������ʾ,��ɱ��ʾ,��Ѫ��ʾ,������ʾ,Boss���־���};
	enum ״̬ {��ʼ, ���� };
	����();
	int& GetX();
	int& GetY();
	int GetW(�������� x)const;
	int GetH(�������� x)const;
	//��ȡ��ǰ����״̬
	״̬& GetStart();
	//���ƿ�ʼʱ��
	int& Gettime_start();
	//���ƽ���ʱ��
	int& Gettime_end();
	//��ȡ����֡��
	int& GetFrame();
	//��ȡ���Ƶ�ͼƬ����
	IMAGE* GetYimage(�������� x);
	//��ȡ����ԭͼƬ
	IMAGE* Getimage(�������� x);

	//���Ƹ����Ե���
	void Draw(int x, int y, �������� type);
	//���ƹ̶��Ե��ߣ���ը
	void DrawBoom();
	//��������
	void EndDraw();
private:
	int x;
	int y;
	int w;
	int h;
	////�ǹ̶���ͼƬ
	vector<Picture> Yimage; 
	vector<Picture> image;
	//�̶�λ�õı�ը������ı�ը������
	vector<Picture> boom_image;		
	vector<Picture> boom_Yimage;

	int frame;		//֡��
	״̬ start;	//�˱�����ʾʱ��ı��
	int time_start;	//���⿪ʼ��ʱ��
	int time_end;	//�������ʱ��
};