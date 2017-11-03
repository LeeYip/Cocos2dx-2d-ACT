#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "cocos2d.h"
#include "BaseRole.h"

class Enemy :public BaseRole
{
private:
	//可自动移动的左右边缘
	MoveEdge moveEdge;

	//根据方向和状态以及帧数获取动画
	virtual cocos2d::Animate* createAnimate();

	//不同的动作
	void runIdleAction(cocos2d::Animate* action);
	void runWalkAction(cocos2d::Animate* action);
	void runJumpAction(cocos2d::Animate* action);
	void runAttackAction(cocos2d::Animate* action);
	void runHurtAction();
	void runDieAction(cocos2d::Animate* action);

	void enemyAttackResume();
	void enemyHurtResume();
	void enemyDieResume();

public:
	virtual bool init();
	CREATE_FUNC(Enemy);

	//设置与获取左右边缘
	void setMoveEdge(float leftX, float rightX);
	MoveEdge getMoveEdge();

	//执行动画
	virtual void runRoleAction();
};

#endif // !_ENEMY_H_

