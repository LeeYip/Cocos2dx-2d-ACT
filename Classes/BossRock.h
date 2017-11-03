#ifndef _BOSSROCK_H_
#define _BOSSROCK_H_

#include "cocos2d.h"
#include "BaseRole.h"

class BossRock : public BaseRole
{
private:
	//���ݷ����״̬�Լ�֡����ȡ����
	virtual cocos2d::Animate* createAnimate();

	//��ͬ�Ķ���
	void runIdleAction();

public:
	virtual bool init();
	CREATE_FUNC(BossRock);

	//ִ�ж���
	virtual void runRoleAction();
};

#endif // !_BOSSROCK_H_

