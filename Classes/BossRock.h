#ifndef _BOSSROCK_H_
#define _BOSSROCK_H_

#include "cocos2d.h"
#include "BaseRole.h"

class BossRock : public BaseRole
{
private:
	//根据方向和状态以及帧数获取动画
	virtual cocos2d::Animate* createAnimate();

	//不同的动作
	void runIdleAction();

public:
	virtual bool init();
	CREATE_FUNC(BossRock);

	//执行动画
	virtual void runRoleAction();
};

#endif // !_BOSSROCK_H_

