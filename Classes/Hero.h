#ifndef _HERO_H_
#define _HERO_H_

#include "cocos2d.h"
#include "BaseRole.h"

class Hero :public BaseRole
{
private:
	//���ݷ����״̬�Լ�֡����ȡ����
	virtual cocos2d::Animate* createAnimate();

public:
	//�ж���Ծ��״̬�Ƿ�Ϊ������
	bool isJumpUp;

	//�޵�ʱ��
	int invincibilityDuration;

public:
	virtual bool init();
	CREATE_FUNC(Hero);

	//ִ�ж���
	virtual void runRoleAction();

	//��ͬ�Ķ���
	void runIdleAction(cocos2d::Animate* action);
	void runWalkAction(cocos2d::Animate* action);
	void runJumpAction(cocos2d::Animate* action);
	void runAttackAction(cocos2d::Animate* action);
	void runHurtAction();
	void runDieAction(cocos2d::Animate* action);

	void heroAttackResume();
	//void heroHurtResume();
	void heroDieResume();
};

#endif // !_HERO_H_

