#ifndef _BOSSHEAD_H_
#define _BOSSHEAD_H_

#include "cocos2d.h"
#include "BaseRole.h"

class BossHead : public BaseRole
{
private:
	//���ݷ����״̬�Լ�֡����ȡ����
	virtual cocos2d::Animate* createAnimate();

	//��ͬ�Ķ���
	void runIdleAction();

public:
	virtual bool init();
	CREATE_FUNC(BossHead);

	//ִ�ж���
	virtual void runRoleAction();
};

#endif // !_BOSSHEAD_H_