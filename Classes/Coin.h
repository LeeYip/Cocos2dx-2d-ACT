#ifndef _COIN_H_
#define _COIN_H_

#include "cocos2d.h"
#include "BaseRole.h"

class Coin : public BaseRole
{
private:
	//根据方向和状态以及帧数获取动画
	virtual cocos2d::Animate* createAnimate();

	//不同的动作
	void runIdleAction(cocos2d::Animate * action);
	void runDieAction(cocos2d::Animate* action);

public:
	virtual bool init();
	CREATE_FUNC(Coin);

	//执行动画
	virtual void runRoleAction();
};

#endif 

