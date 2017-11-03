#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "cocos2d.h"
#include "BaseRole.h"

class Enemy :public BaseRole
{
private:
	//���Զ��ƶ������ұ�Ե
	MoveEdge moveEdge;

	//���ݷ����״̬�Լ�֡����ȡ����
	virtual cocos2d::Animate* createAnimate();

	//��ͬ�Ķ���
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

	//�������ȡ���ұ�Ե
	void setMoveEdge(float leftX, float rightX);
	MoveEdge getMoveEdge();

	//ִ�ж���
	virtual void runRoleAction();
};

#endif // !_ENEMY_H_

