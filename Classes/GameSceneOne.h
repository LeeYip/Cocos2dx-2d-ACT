#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "GameSceneTwo.h"
#include "SelectScene.h"
#include "Hero.h"
#include "Enemy.h"
#include "Coin.h"
#include "Tag.h"

class GameSceneOne : public cocos2d::Scene
{
private:
	//屏幕可见尺寸
	cocos2d::Size visibleSize;

	//地图
	cocos2d::TMXTiledMap* map;

	//platforms，可从下方跳入
	cocos2d::Node* platform1, *platform2, *platform3, *platform4, *platform5, *platform6;
	cocos2d::Rect platformRect1, platformRect2, platformRect3, platformRect4, platformRect5, platformRect6;

	//tips
	cocos2d::Sprite* tip1,* tip2,* tip3,* tip4, *tip5;
	cocos2d::Label* tipLabel1, *tipLabel2, *tipLabel3,* tipLabel4, *tipLabel5;
	cocos2d::Rect tipRect1, tipRect2, tipRect3, tipRect4, tipRect5;
	bool isTipIn1, isTipIn2, isTipIn3, isTipIn4, isTipIn5;

	//door，进入下一关
	cocos2d::Sprite* door;
	cocos2d::Rect doorRect;

	//生命值
	cocos2d::Sprite* heart[5];
	int heartCount;

	//金币
	cocos2d::Sprite* coinSprite;
	cocos2d::Label* coinLabel;
	int coinNumber;
	std::vector<Coin*> coin;

	//role
	Hero* hero;
	Enemy* enemy;
	Enemy* enemyx;

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
    CREATE_FUNC(GameSceneOne);

	//init
	void heroInit();
	void enemiesInit();

	//update
	virtual void update(float dt);
	void heroUpdate();
	void enemiesUpdate();
	void coinsUpdate();
	void mapUpdate();  //platforms,tips,door,map

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

	//下一关
	void enterNextLevel();
};

#endif // __HELLOWORLD_SCENE_H__
