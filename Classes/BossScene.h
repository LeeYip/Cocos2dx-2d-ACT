#ifndef _BOSS_SCENE_H_
#define _BOSS_SCENE_H_

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "SelectScene.h"
#include "Hero.h"
#include "Boss.h"
#include "BossRock.h"
#include "BossRockBroken.h"
#include "BossHead.h"
#include "Blood.h"
#include "Coin.h"
#include "Tag.h"

class BossScene :public cocos2d::Scene
{
private:
	//屏幕可见尺寸
	cocos2d::Size visibleSize;

	//地图
	cocos2d::TMXTiledMap* map;

	//生命值
	cocos2d::Sprite* heart[5];
	int heartCount;

	//金币
	cocos2d::Sprite* coinSprite;
	cocos2d::Label* coinLabel;
	int coinNumber;
	std::vector<Coin*> coin;  //怪物死亡后掉落的金币

	//role
	Hero* hero;
	Boss* boss;
	cocos2d::Sprite* bossPrick;
	cocos2d::Rect bossPrickRect;
	std::vector<BossRock*> bossRock;            //boss扔出的石头    
	std::vector<BossRockBroken*> bossRockBroken;//石头碰撞后的碎石
	BossHead* bossHead;       //boss死亡后掉落的脑袋
	std::vector<Blood*> blood;//boss死亡后掉落的血液

	//boss血量条
	cocos2d::Sprite* bgHP;
	cocos2d::Sprite* numBar;

	std::map<cocos2d::EventKeyboard::KeyCode, bool> keyMap;

	//虚拟按键
	cocos2d::ui::Button* left;
	cocos2d::ui::Button* right;
	cocos2d::ui::Button* jump;
	cocos2d::ui::Button* attack;
	//判断按键是否按下
	bool isLeft;
	bool isRight;
	bool isJump;
	bool isAttack;
	//跳跃按键时间计数
	int jumpCount;

	//菜单按钮
	cocos2d::MenuItemImage* pauseItem;
	cocos2d::MenuItemImage* resumeItem;
	cocos2d::MenuItemImage* backItem;
	bool isPauseGame;
	cocos2d::LayerColor* pauseBG;
	cocos2d::Menu* pauseMenu;

public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(BossScene);

	//init
	void heroInit();
	void bossInit();

	//update
	virtual void update(float dt);
	void heroUpdate();
	void bossUpdate();
	void bossRockUpdate();  //attackMode2生成的rocks，以及rocks碎裂生成的rockbroken
	void bossDeathUpdate(); //boss死亡的head，blood
	void coinsUpdate();
	void mapUpdate();   //platforms,tips,door,map

	//按键事件
	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event);
	void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event);

	//虚拟按键事件
	void onLeft(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type);
	void onRight(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type);
	void onJump(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type);
	void onAttack(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type);

	//碰撞事件
	bool onContactBegin(cocos2d::PhysicsContact& contact);
	void onContactSeperate(cocos2d::PhysicsContact& contact);

	//碰撞检测
	bool collisionDetection(cocos2d::Rect hitBox, cocos2d::Rect bodyBox);

	//pause game
	void pauseGame();

	//resume game
	void resumeGame();

	//back to select scene
	void back();
};

#endif // !_BOSS_SCENE_H_
