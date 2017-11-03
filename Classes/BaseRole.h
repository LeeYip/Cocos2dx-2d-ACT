#ifndef _BASEROLE_H_
#define _BASEROLE_H_

#include "cocos2d.h"

//����
enum Direction
{
	LEFT,
	RIGHT
};

//״̬,�����ȼ���С��������
enum ActionState
{
	NONE = 10,
	IDLE,
	WALK,
	JUMP,
	ATTACK,
	HURT,
	DIE,
	REMOVE
};

//�ƶ���Χ
struct MoveEdge
{
	float leftX;
	float rightX;
};

class BaseRole :public cocos2d::Node
{
private:
	//��ǰ�ķ�����״̬
	Direction direction;
	ActionState actionState;
	//��һ�εķ�����״̬
	//Direction lastDirection;
	//ActionState lastActionState;

	//Ѫ��
	int HP;

	//�ٶ�
	float velX;
	float velY;

	//��ɫ
	cocos2d::Sprite* baseSprite;

	//������Χ�����巶Χ��ײ��
	cocos2d::Rect hitBox;
	cocos2d::Rect bodyBox;

	//����ľ�������
	cocos2d::Rect alertBox;

public:
	virtual bool init();
	//CREATE_FUNC(BaseRole);

	//���ݷ����״̬�Լ�֡����ȡ����
	virtual cocos2d::Animate* createAnimate() = 0;

	//ִ�ж���
	virtual void runRoleAction() = 0;

	//�������ȡ��ɫ
	void setRole(cocos2d::Sprite* sprite);
	cocos2d::Sprite* getRole();

	//�������ȡ����
	void setDirection(Direction di);
	Direction getDirection();
	/*Direction getLastDirection();*/

	//�������ȡ����״̬
	void setActionState(ActionState ac);
	ActionState getActionState();
	/*ActionState getLastActionState();*/

	//�������ȡѪ��
	void setHP(int hp);
	int getHP();

	//�������ȡ�ٶ�
	void setVelX(float x);
	void setVelY(float y);
	float getVelX();
	float getVelY();

	//�������ȡ��ײ��
	void setHitBox(cocos2d::Point origin, cocos2d::Size size);
	cocos2d::Rect getHitBox();
	void setBodyBox(cocos2d::Point origin, cocos2d::Size size);
	cocos2d::Rect getBodyBox();

	//�������ȡ��������
	void setAlertBox(cocos2d::Point origin, cocos2d::Size size);
	cocos2d::Rect getAlertBox();
};

#endif // !_BASEROLE_H

