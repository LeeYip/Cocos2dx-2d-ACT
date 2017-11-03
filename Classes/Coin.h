#ifndef _COIN_H_
#define _COIN_H_

#include "cocos2d.h"
#include "BaseRole.h"

class Coin : public BaseRole
{
private:
	//���ݷ����״̬�Լ�֡����ȡ����
	virtual cocos2d::Animate* createAnimate();

	//��ͬ�Ķ���
	void runIdleAction(cocos2d::Animate * action);
	void runDieAction(cocos2d::Animate* action);

public:
	virtual bool init();
	CREATE_FUNC(Coin);

	//ִ�ж���
	virtual void runRoleAction();
};

#endif 

