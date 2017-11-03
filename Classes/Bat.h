#ifndef _BAT_H_
#define _BAT_H_

#include "cocos2d.h"
#include "BaseRole.h"

class Bat :public BaseRole
{
private:
	//���Զ��ƶ������ұ�Ե
	MoveEdge moveEdge;

	//���ݷ����״̬�Լ�֡����ȡ����
	virtual cocos2d::Animate* createAnimate();

	//��ͬ�Ķ���
	void runWalkAction(cocos2d::Animate* action);
	void runHurtAction();
	void runDieAction(cocos2d::Animate* action);

	void batHurtResume();
	void batDieResume();

public:
	virtual bool init();
	CREATE_FUNC(Bat);

	//ִ�ж���
	virtual void runRoleAction();
};

#endif // !_BAT_H_

