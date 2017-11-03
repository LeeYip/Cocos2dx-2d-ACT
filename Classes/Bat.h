#ifndef _BAT_H_
#define _BAT_H_

#include "cocos2d.h"
#include "BaseRole.h"

class Bat :public BaseRole
{
private:
	//可自动移动的左右边缘
	MoveEdge moveEdge;

	//根据方向和状态以及帧数获取动画
	virtual cocos2d::Animate* createAnimate();

	//不同的动作
	void runWalkAction(cocos2d::Animate* action);
	void runHurtAction();
	void runDieAction(cocos2d::Animate* action);

	void batHurtResume();
	void batDieResume();

public:
	virtual bool init();
	CREATE_FUNC(Bat);

	//执行动画
	virtual void runRoleAction();
};

#endif // !_BAT_H_

