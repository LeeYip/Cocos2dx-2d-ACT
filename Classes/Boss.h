#ifndef _BOSS_H_
#define _BOSS_H_

#include "cocos2d.h"
#include "BaseRole.h"

class Boss :public BaseRole
{
private:
	//���Զ��ƶ������ұ�Ե
	MoveEdge moveEdge;

	//���ݷ����״̬�Լ�֡����ȡ����
	virtual cocos2d::Animate* createAnimate();

public:
	//����ģʽ
	char attackMode;

	//�жϵ�ǰ�����Ƿ���ʹboss����
	bool isCanHurt;

	//������ʱ����
	int idleDuration;
	int attackDuration;
	//����walkʱ�ı䷽��Ĵ���
	int walkCount;
	//������������
	int attackCount;

public:
	virtual bool init();
	CREATE_FUNC(Boss);

	//�������ȡ���ұ�Ե
	void setMoveEdge(float leftX, float rightX);
	MoveEdge getMoveEdge();

	//ִ�ж���
	virtual void runRoleAction();

	//��ͬ�Ķ���
	void runIdleAction(cocos2d::Animate* action);
	void runWalkAction(cocos2d::Animate* action);
	void runJumpAction(cocos2d::Animate* action);
	void runAttackAction(cocos2d::Animate* action);
	void runHurtAction();
	void runDieAction(cocos2d::Animate* action);

	void bossAttackResume();
};

#endif // !_BOSS_H_
