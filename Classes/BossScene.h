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
	//��Ļ�ɼ��ߴ�
	cocos2d::Size visibleSize;

	//��ͼ
	cocos2d::TMXTiledMap* map;

	//����ֵ
	cocos2d::Sprite* heart[5];
	int heartCount;

	//���
	cocos2d::Sprite* coinSprite;
	cocos2d::Label* coinLabel;
	int coinNumber;
	std::vector<Coin*> coin;  //�������������Ľ��

	//role
	Hero* hero;
	Boss* boss;
	cocos2d::Sprite* bossPrick;
	cocos2d::Rect bossPrickRect;
	std::vector<BossRock*> bossRock;            //boss�ӳ���ʯͷ    
	std::vector<BossRockBroken*> bossRockBroken;//ʯͷ��ײ�����ʯ
	BossHead* bossHead;       //boss�����������Դ�
	std::vector<Blood*> blood;//boss����������ѪҺ

	//bossѪ����
	cocos2d::Sprite* bgHP;
	cocos2d::Sprite* numBar;

	std::map<cocos2d::EventKeyboard::KeyCode, bool> keyMap;

	//���ⰴ��
	cocos2d::ui::Button* left;
	cocos2d::ui::Button* right;
	cocos2d::ui::Button* jump;
	cocos2d::ui::Button* attack;
	//�жϰ����Ƿ���
	bool isLeft;
	bool isRight;
	bool isJump;
	bool isAttack;
	//��Ծ����ʱ�����
	int jumpCount;

	//�˵���ť
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
	void bossRockUpdate();  //attackMode2���ɵ�rocks���Լ�rocks�������ɵ�rockbroken
	void bossDeathUpdate(); //boss������head��blood
	void coinsUpdate();
	void mapUpdate();   //platforms,tips,door,map

	//�����¼�
	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event);
	void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event);

	//���ⰴ���¼�
	void onLeft(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type);
	void onRight(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type);
	void onJump(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type);
	void onAttack(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type);

	//��ײ�¼�
	bool onContactBegin(cocos2d::PhysicsContact& contact);
	void onContactSeperate(cocos2d::PhysicsContact& contact);

	//��ײ���
	bool collisionDetection(cocos2d::Rect hitBox, cocos2d::Rect bodyBox);

	//pause game
	void pauseGame();

	//resume game
	void resumeGame();

	//back to select scene
	void back();
};

#endif // !_BOSS_SCENE_H_
