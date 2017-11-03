#ifndef _BOSSROCKBROKEN_H_
#define _BOSSROCKBROKEN_H_

#include "cocos2d.h"
#include "BaseRole.h"

class BossRockBroken : public BaseRole
{
private:
	//���ݷ����״̬�Լ�֡����ȡ����
	virtual cocos2d::Animate* createAnimate();

	//��ͬ�Ķ���
	void runIdleAction();

public:
	virtual bool init();
	CREATE_FUNC(BossRockBroken);

	//ִ�ж���
	virtual void runRoleAction();
};

#endif // !_BOSSROCKBROKEN_H_


