#ifndef _BOSS_H_
#define _BOSS_H_

#include "cocos2d.h"
#include "BaseRole.h"

class Boss :public BaseRole
{
private:
	//可自动移动的左右边缘
	MoveEdge moveEdge;

	//根据方向和状态以及帧数获取动画
	virtual cocos2d::Animate* createAnimate();

public:
	//攻击模式
	char attackMode;

	//判断当前攻击是否能使boss受伤
	bool isCanHurt;

	//动作的时间间隔
	int idleDuration;
	int attackDuration;
	//计算walk时改变方向的次数
	int walkCount;
	//攻击次数计数
	int attackCount;

public:
	virtual bool init();
	CREATE_FUNC(Boss);

	//设置与获取左右边缘
	void setMoveEdge(float leftX, float rightX);
	MoveEdge getMoveEdge();

	//执行动画
	virtual void runRoleAction();

	//不同的动作
	void runIdleAction(cocos2d::Animate* action);
	void runWalkAction(cocos2d::Animate* action);
	void runJumpAction(cocos2d::Animate* action);
	void runAttackAction(cocos2d::Animate* action);
	void runHurtAction();
	void runDieAction(cocos2d::Animate* action);

	void bossAttackResume();
};

#endif // !_BOSS_H_
