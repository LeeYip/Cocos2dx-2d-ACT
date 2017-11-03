#ifndef _BOSSHEAD_H_
#define _BOSSHEAD_H_

#include "cocos2d.h"
#include "BaseRole.h"

class BossHead : public BaseRole
{
private:
	//根据方向和状态以及帧数获取动画
	virtual cocos2d::Animate* createAnimate();

	//不同的动作
	void runIdleAction();

public:
	virtual bool init();
	CREATE_FUNC(BossHead);

	//执行动画
	virtual void runRoleAction();
};

#endif // !_BOSSHEAD_H_