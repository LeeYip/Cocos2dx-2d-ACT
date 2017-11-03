#ifndef _HERO_H_
#define _HERO_H_

#include "cocos2d.h"
#include "BaseRole.h"

class Hero :public BaseRole
{
private:
	//根据方向和状态以及帧数获取动画
	virtual cocos2d::Animate* createAnimate();

public:
	//判断跳跃的状态是否为向上跳
	bool isJumpUp;

	//无敌时间
	int invincibilityDuration;

public:
	virtual bool init();
	CREATE_FUNC(Hero);

	//执行动画
	virtual void runRoleAction();

	//不同的动作
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

