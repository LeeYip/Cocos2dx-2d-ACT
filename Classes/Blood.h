#ifndef _BLOOD_H_
#define _BLOOD_H_

#include "cocos2d.h"
#include "BaseRole.h"

class Blood : public BaseRole
{
private:
	//���ݷ����״̬�Լ�֡����ȡ����
	virtual cocos2d::Animate* createAnimate();

	//��ͬ�Ķ���
	void runIdleAction();

public:
	virtual bool init();
	CREATE_FUNC(Blood);

	//ִ�ж���
	virtual void runRoleAction();
};

#endif // !_BLOOD_H_