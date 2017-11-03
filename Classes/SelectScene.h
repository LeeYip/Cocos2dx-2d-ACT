#ifndef _SELECTSCENE_H_
#define _SELECTSCENE_H_

#include "cocos2d.h"
#include "GameSceneOne.h"
#include "GameSceneTwo.h"
#include "BossScene.h"

class SelectScene : public cocos2d::Scene
{
private:
	//已解锁的关卡数
	int level;

public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(SelectScene);

	void enterLevelOne();
	void enterLevelTwo();
	void enterLevelBoss();
};

#endif // !_SELECTSCENE_H_