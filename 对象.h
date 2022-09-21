#pragma once
#include "����.h"
#include "�ӵ�.h"
#include "ͼƬ.h"
#include "Timer.h"
#include "��ť.h"
#include "��־.h"
#include "�����Զ�������.h"

//������
class Object
{
public:
	enum Limits { up, down, left, right, NO };
	Object() = default;
	Object(const Picture& image, const Picture& Yimage, const Operation& target);	//����
	~Object() {}
	Picture GetImage()const;
	Picture GetYimage()const;
	//��ȡ��ǰ����
	Operation& GetTarget();
	//����Ļ���
	void Draw();
	//����ķ�������
	void SetDir(Operation::Dir dir);
	//������ƶ�
	void Move();
	
private:
	Operation target;	//����Ŀ��
	Picture image;		//ԭͼ
	Picture Yimage;		//����ͼ
};