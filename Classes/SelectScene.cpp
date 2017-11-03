#include "SelectScene.h"

USING_NS_CC;

cocos2d::Scene * SelectScene::createScene()
{
	return SelectScene::create();
}

bool SelectScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	//±³¾°É«
	auto* bk = LayerColor::create(Color4B(100, 72, 60, 255));
	this->addChild(bk);

	//level button
	auto* levelOne = MenuItemImage::create("level1_1.png", "level1_2.png", CC_CALLBACK_0(SelectScene::enterLevelOne, this));
	levelOne->setPosition(Vec2(260, 180));

	auto* levelTwo = MenuItemImage::create("level2_1.png", "level2_2.png", CC_CALLBACK_0(SelectScene::enterLevelTwo, this));
	levelTwo->setPosition(Vec2(320, 180));

	auto* levelBoss = MenuItemImage::create("levelboss_1.png", "levelboss_2.png", CC_CALLBACK_0(SelectScene::enterLevelBoss, this));
	levelBoss->setPosition(Vec2(380, 180));

	//menu
	auto* menu = Menu::create(levelOne, levelTwo, levelBoss, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu);

	level = UserDefault::getInstance()->getIntegerForKey("level");
	if (level < 2)
	{
		levelTwo->setVisible(false);
		auto* levelLocked2 = Sprite::create("levellocked.png");
		levelLocked2 = Sprite::create("levellocked.png");
		levelLocked2->setPosition(levelTwo->getPosition());
		this->addChild(levelLocked2);

		levelBoss->setVisible(false);
		auto* levelLocked3 = Sprite::create("levellocked.png");
		levelLocked3 = Sprite::create("levellocked.png");
		levelLocked3->setPosition(levelBoss->getPosition());
		this->addChild(levelLocked3);
	}
	else if (level < 3)
	{
		levelBoss->setVisible(false);
		auto* levelLocked3 = Sprite::create("levellocked.png");
		levelLocked3 = Sprite::create("levellocked.png");
		levelLocked3->setPosition(levelBoss->getPosition());
		this->addChild(levelLocked3);
	}

	return true;
}

void SelectScene::enterLevelOne()
{
	auto gameScene = GameSceneOne::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(1.0f, gameScene));
}

void SelectScene::enterLevelTwo()
{
	auto gameScene = GameSceneTwo::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(1.0f, gameScene));
}

void SelectScene::enterLevelBoss()
{
	auto gameScene = BossScene::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(1.0f, gameScene));
}
