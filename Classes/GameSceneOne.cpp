#include "GameSceneOne.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace ui;

Scene* GameSceneOne::createScene()
{
	//创建带物理引擎的scene
	Scene* scene = Scene::createWithPhysics();

	//调试
	//scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

	//设置重力加速度
	scene->getPhysicsWorld()->setGravity(Vec2(0.0f, -900.0f));

	auto layer = GameSceneOne::create();
	scene->addChild(layer);

	return scene;
}

bool GameSceneOne::init()
{
	if (!Scene::init())
	{
		return false;
	}

	//获取屏幕可见尺寸
	visibleSize = Director::getInstance()->getVisibleSize();

	//设置世界范围
	Size size;
	size.width = visibleSize.width * 2;
	size.height = visibleSize.height * 2;
	auto* edge = PhysicsBody::createEdgeBox(size);
	this->setPhysicsBody(edge);

	//背景色
	auto* bk = LayerColor::create(Color4B(100, 72, 60, 255));
	this->addChild(bk);

	//地图
	map = TMXTiledMap::create("map1.tmx");
	this->addChild(map);

	//地形对象层绑定刚体
	auto* groundLayer = map->getObjectGroup("ground");
	for (Value& v : groundLayer->getObjects())
	{
		ValueMap m = v.asValueMap();
		int x = m["x"].asInt();
		int y = m["y"].asInt();
		int w = m["width"].asInt();
		int h = m["height"].asInt();

		auto* phyBody = PhysicsBody::createBox(Size(w, h), PhysicsMaterial(1000.0f, 0.5f, 1.0f));
		phyBody->setDynamic(false);
		phyBody->setContactTestBitmask(0xFFFFFFFF);
		phyBody->setCategoryBitmask(0xFFFFFFFF);
		auto* ground = Node::create();
		ground->setPhysicsBody(phyBody);
		ground->setTag(Tag::GROUND);
		map->addChild(ground);
		ground->setPosition(x + (w / 2), y + (h / 2));
	}

	//平台，可从下方跳入
	auto* platformBody1 = PhysicsBody::createBox(Size(108, 18), PhysicsMaterial(1000.0f, 0.5f, 1.0f));
	platformBody1->setDynamic(false);
	platformBody1->setContactTestBitmask(0xFFFFFFFF);
	platformBody1->setCategoryBitmask(0xFFFFFFF0);
	platformBody1->setCollisionBitmask(0xFFFFFFF0);
	platform1 = Node::create();
	platform1->setPhysicsBody(platformBody1);
	platform1->setPosition(Vec2(2070.0f, 441.0f));
	platform1->setTag(Tag::GROUND);
	map->addChild(platform1);
	platformRect1.origin.x = 2016.0f;
	platformRect1.origin.y = 432.0f;
	platformRect1.size.width = 108.0f;
	platformRect1.size.height = 18.0f;

	auto* platformBody2 = PhysicsBody::createBox(Size(72, 18), PhysicsMaterial(1000.0f, 0.5f, 1.0f));
	platformBody2->setDynamic(false);
	platformBody2->setContactTestBitmask(0xFFFFFFFF);
	platformBody2->setCategoryBitmask(0xFFFFFFF0);
	platformBody2->setCollisionBitmask(0xFFFFFFF0);
	platform2 = Node::create();
	platform2->setPhysicsBody(platformBody2);
	platform2->setPosition(Vec2(2196.0f, 513.0f));
	platform2->setTag(Tag::GROUND);
	map->addChild(platform2);
	platformRect2.origin.x = 2160.0f;
	platformRect2.origin.y = 504.0f;
	platformRect2.size.width = 72.0f;
	platformRect2.size.height = 18.0f;

	auto* platformBody3 = PhysicsBody::createBox(Size(108, 18), PhysicsMaterial(1000.0f, 0.5f, 1.0f));
	platformBody3->setDynamic(false);
	platformBody3->setContactTestBitmask(0xFFFFFFFF);
	platformBody3->setCategoryBitmask(0xFFFFFFF0);
	platformBody3->setCollisionBitmask(0xFFFFFFF0);
	platform3 = Node::create();
	platform3->setPhysicsBody(platformBody3);
	platform3->setPosition(Vec2(2646.0f, 567.0f));
	platform3->setTag(Tag::GROUND);
	map->addChild(platform3);
	platformRect3.origin.x = 2592.0f;
	platformRect3.origin.y = 558.0f;
	platformRect3.size.width = 108.0f;
	platformRect3.size.height = 18.0f;

	auto* platformBody4 = PhysicsBody::createBox(Size(108, 18), PhysicsMaterial(1000.0f, 0.5f, 1.0f));
	platformBody4->setDynamic(false);
	platformBody4->setContactTestBitmask(0xFFFFFFFF);
	platformBody4->setCategoryBitmask(0xFFFFFFF0);
	platformBody4->setCollisionBitmask(0xFFFFFFF0);
	platform4 = Node::create();
	platform4->setPhysicsBody(platformBody4);
	platform4->setPosition(Vec2(2970.0f, 567.0f));
	platform4->setTag(Tag::GROUND);
	map->addChild(platform4);
	platformRect4.origin.x = 2916.0f;
	platformRect4.origin.y = 558.0f;
	platformRect4.size.width = 108.0f;
	platformRect4.size.height = 18.0f;

	auto* platformBody5 = PhysicsBody::createBox(Size(108, 18), PhysicsMaterial(1000.0f, 0.5f, 1.0f));
	platformBody5->setDynamic(false);
	platformBody5->setContactTestBitmask(0xFFFFFFFF);
	platformBody5->setCategoryBitmask(0xFFFFFFF0);
	platformBody5->setCollisionBitmask(0xFFFFFFF0);
	platform5 = Node::create();
	platform5->setPhysicsBody(platformBody5);
	platform5->setPosition(Vec2(2646.0f, 477.0f));
	platform5->setTag(Tag::GROUND);
	map->addChild(platform5);
	platformRect5.origin.x = 2592.0f;
	platformRect5.origin.y = 468.0f;
	platformRect5.size.width = 108.0f;
	platformRect5.size.height = 18.0f;

	auto* platformBody6 = PhysicsBody::createBox(Size(108, 18), PhysicsMaterial(1000.0f, 0.5f, 1.0f));
	platformBody6->setDynamic(false);
	platformBody6->setContactTestBitmask(0xFFFFFFFF);
	platformBody6->setCategoryBitmask(0xFFFFFFF0);
	platformBody6->setCollisionBitmask(0xFFFFFFF0);
	platform6 = Node::create();
	platform6->setPhysicsBody(platformBody6);
	platform6->setPosition(Vec2(2970.0f, 477.0f));
	platform6->setTag(Tag::GROUND);
	map->addChild(platform6);
	platformRect6.origin.x = 2916.0f;
	platformRect6.origin.y = 468.0f;
	platformRect6.size.width = 108.0f;
	platformRect6.size.height = 18.0f;

	//提示
	tip1 = Sprite::create("tip.png");
	tip1->setPosition(Vec2(414, 144 + tip1->getContentSize().height / 2));
	map->addChild(tip1);
	tipLabel1 = Label::createWithTTF("Press \"A\" to jump", "swfit.ttf", 12);
	tipLabel1->setPosition(Vec2(414, 200));
	tipLabel1->setOpacity(0);
	map->addChild(tipLabel1);
	tipRect1.origin.x = tip1->getPositionX() - 12.0f;
	tipRect1.origin.y = tip1->getPositionY() - 18.0f;
	tipRect1.size.width = 24.0f;
	tipRect1.size.height = 36.0f;
	isTipIn1 = false;

	tip2 = Sprite::create("tip.png");
	tip2->setPosition(Vec2(666, 216 + tip2->getContentSize().height / 2));
	map->addChild(tip2);
	tipLabel2 = Label::createWithTTF("Press and hold \"A\" to jump higher", "swfit.ttf", 12);
	tipLabel2->setPosition(Vec2(666, 272));
	tipLabel2->setOpacity(0);
	map->addChild(tipLabel2);
	tipRect2.origin.x = tip2->getPositionX() - 12.0f;
	tipRect2.origin.y = tip2->getPositionY() - 18.0f;
	tipRect2.size.width = 24.0f;
	tipRect2.size.height = 36.0f;
	isTipIn2 = false;

	tip3 = Sprite::create("tip.png");
	tip3->setPosition(Vec2(1206.0f, 216 + tip3->getContentSize().height / 2));
	map->addChild(tip3);
	tipLabel3 = Label::createWithTTF("Press \"B\" to attack", "swfit.ttf", 12);
	tipLabel3->setPosition(Vec2(1206.0f, 272));
	tipLabel3->setOpacity(0);
	map->addChild(tipLabel3);
	tipRect3.origin.x = tip3->getPositionX() - 12.0f;
	tipRect3.origin.y = tip3->getPositionY() - 18.0f;
	tipRect3.size.width = 24.0f;
	tipRect3.size.height = 36.0f;
	isTipIn3 = false;

	tip4 = Sprite::create("tip.png");
	tip4->setPosition(Vec2(2430, 594 + tip4->getContentSize().height / 2));
	map->addChild(tip4);
	tipLabel4 = Label::createWithTTF("Press and hold \"A\" to \ndrop through platform", "swfit.ttf", 12);
	tipLabel4->setPosition(Vec2(2430, 655));
	tipLabel4->setOpacity(0);
	map->addChild(tipLabel4);
	tipRect4.origin.x = tip4->getPositionX() - 12.0f;
	tipRect4.origin.y = tip4->getPositionY() - 18.0f;
	tipRect4.size.width = 24.0f;
	tipRect4.size.height = 36.0f;
	isTipIn4 = false;

	tip5 = Sprite::create("tip.png");
	tip5->setPosition(Vec2(3258, 594 + tip5->getContentSize().height / 2));
	map->addChild(tip5);
	tipLabel5 = Label::createWithTTF("Press \"B\" in the door to \nenter the next level", "swfit.ttf", 12);
	tipLabel5->setPosition(Vec2(3258, 655));
	tipLabel5->setOpacity(0);
	map->addChild(tipLabel5);
	tipRect5.origin.x = tip5->getPositionX() - 12.0f;
	tipRect5.origin.y = tip5->getPositionY() - 18.0f;
	tipRect5.size.width = 24.0f;
	tipRect5.size.height = 36.0f;
	isTipIn5 = false;

	//door
	door = Sprite::create("door.png");
	door->setPosition(Vec2(3528, 594 + door->getContentSize().height / 2));
	map->addChild(door);
	doorRect.origin.x = door->getPositionX() - 24.0f;
	doorRect.origin.y = door->getPositionY() - 29.0f;
	doorRect.size.width = 48.0f;
	doorRect.size.height = 58.0f;

	//Roles
	heroInit();
	enemiesInit();

	//coin
	coinSprite = Sprite::create("coin.png");
	coinSprite->setPosition(Vec2(300, 340));
	this->addChild(coinSprite);
	coinNumber = UserDefault::getInstance()->getIntegerForKey("coinNumber");
	coinLabel = Label::createWithTTF(__String::createWithFormat("%d", coinNumber)->getCString(), "04b24.ttf", 24);
	if (coinNumber < 10)
		coinLabel->setPosition(Vec2(325, 338));
	else if (coinNumber<100)
		coinLabel->setPosition(Vec2(330, 338));
	else if (coinNumber<1000)
		coinLabel->setPosition(Vec2(335, 338));
	else if (coinNumber<10000)
		coinLabel->setPosition(Vec2(340, 338));
	else if (coinNumber<100000)
		coinLabel->setPosition(Vec2(345, 338));
	else
		coinLabel->setPosition(Vec2(350, 338));
	this->addChild(coinLabel);

	//菜单按钮
	pauseItem = MenuItemImage::create("pause1.png", "pause1.png", CC_CALLBACK_0(GameSceneOne::pauseGame, this));
	pauseItem->setPosition(Vec2(620, 340));
	auto* menu = Menu::create(pauseItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu);

	//虚拟按键
	left = ui::Button::create("left1.png", "left2.png");
	left->setPosition(Vec2(70, 40));
	left->addTouchEventListener(ui::Widget::ccWidgetTouchCallback(CC_CALLBACK_2(GameSceneOne::onLeft, this)));
	this->addChild(left);
	right = ui::Button::create("right1.png", "right2.png");
	right->setPosition(Vec2(180, 40));
	right->addTouchEventListener(ui::Widget::ccWidgetTouchCallback(CC_CALLBACK_2(GameSceneOne::onRight, this)));
	this->addChild(right);
	jump = ui::Button::create("jump1.png", "jump2.png");
	jump->setPosition(Vec2(600, 40));
	jump->addTouchEventListener(ui::Widget::ccWidgetTouchCallback(CC_CALLBACK_2(GameSceneOne::onJump, this)));
	this->addChild(jump);
	attack = ui::Button::create("attack1.png", "attack2.png");
	attack->setPosition(Vec2(520, 40));
	attack->addTouchEventListener(ui::Widget::ccWidgetTouchCallback(CC_CALLBACK_2(GameSceneOne::onAttack, this)));
	this->addChild(attack);

	isLeft = false;
	isRight = false;
	isJump = false;
	isAttack = false;

	//键盘监听
	auto keyListener = EventListenerKeyboard::create();
	keyListener->onKeyPressed = CC_CALLBACK_2(GameSceneOne::onKeyPressed, this);
	keyListener->onKeyReleased = CC_CALLBACK_2(GameSceneOne::onKeyReleased, this);
	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(keyListener, this);

	//碰撞监听
	EventListenerPhysicsContact* contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(GameSceneOne::onContactBegin, this);
	contactListener->onContactSeparate = CC_CALLBACK_1(GameSceneOne::onContactSeperate, this);
	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);

	//this->scheduleUpdate();

	return true;
}

void GameSceneOne::heroInit()
{
	hero = Hero::create();
	hero->setRole(Sprite::create("hero_rightidle1.png"));
	hero->setPosition(Vec2(50.0f, 167.0f));
	hero->setTag(Tag::HERO);

	auto* body = PhysicsBody::createBox(Size(32.0f, 46.0f), PhysicsMaterial(500.0f, 0.0f, 1.0f));
	body->setDynamic(true);
	body->setLinearDamping(0.0f);
	body->setGravityEnable(true);
	body->setContactTestBitmask(0x01);
	body->setCategoryBitmask(0x01);
	body->setCollisionBitmask(0x01);
	body->setRotationEnable(false);
	hero->setPhysicsBody(body);
	
	map->addChild(hero, 5);

	//hero碰撞盒初始化
	Point bodyOrign;
	bodyOrign.x = hero->getPositionX() - 16.0f;
	bodyOrign.y = hero->getPositionY() - 23.0f;
	Size bodySize;
	bodySize.width = 32.0f;
	bodySize.height = 46.0f;
	hero->setBodyBox(bodyOrign, bodySize);
	Point hitOrign;
	Size hitSize;
	if (hero->getDirection() == Direction::RIGHT)
		hitOrign.x = hero->getPositionX();
	else
		hitOrign.x = hero->getPositionX() - 50.0f;
	hitOrign.y = hero->getPositionY() - 25.0f;
	hitSize.width = 50.0f;
	hitSize.height = 58.0f;
	hero->setHitBox(hitOrign, hitSize);

	//初始化动作
	hero->runRoleAction();

	//生命值
	heartCount = 5;
	for (int i = 0; i < 5; i++)
	{
		heart[i] = Sprite::create("heart.png");
		heart[i]->setPosition(Vec2(20 + 25 * i, 340));
		this->addChild(heart[i]);
	}
}

void GameSceneOne::enemiesInit()
{
	//enemy
	enemy = Enemy::create();
	enemy->setRole(Sprite::create("enemy_rightwalk1.png"));
	enemy->setPosition(Vec2(1418.0f, 230.0f));
	enemy->setMoveEdge(1418.0f, 1858.0f);
	enemy->setTag(Tag::ENEMYA);
	{
		auto* body = PhysicsBody::createBox(Size(28.0f, 38.0f), PhysicsMaterial(500.0f, 0.0f, 1.0f));
		body->setDynamic(true);
		body->setLinearDamping(0.0f);
		body->setGravityEnable(true);
		body->setContactTestBitmask(0x10);
		body->setCategoryBitmask(0x10);
		body->setCollisionBitmask(0x10);
		body->setRotationEnable(false);
		enemy->setPhysicsBody(body);
	}
	map->addChild(enemy);
	//碰撞盒初始化
	{
		Point bodyOrign;
		bodyOrign.x = enemy->getPositionX() - 14.0f;
		bodyOrign.y = enemy->getPositionY() - 19.0f;
		Size bodySize;
		bodySize.width = 28.0f;
		bodySize.height = 38.0f;
		enemy->setBodyBox(bodyOrign, bodySize);
	}

	//enemybxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
	enemyx = Enemy::create();
	enemyx->setRole(Sprite::create("enemy_rightwalk1.png"));
	enemyx->setPosition(Vec2(1922.0f, 361.0f));
	enemyx->setMoveEdge(1922.0f, 2182.0f);
	enemyx->setTag(Tag::ENEMYB);
	{
		auto* body = PhysicsBody::createBox(Size(28.0f, 38.0f), PhysicsMaterial(500.0f, 0.0f, 1.0f));
		body->setDynamic(true);
		body->setLinearDamping(0.0f);
		body->setGravityEnable(true);
		body->setContactTestBitmask(0x10);
		body->setCategoryBitmask(0x10);
		body->setCollisionBitmask(0x10);
		body->setRotationEnable(false);
		enemyx->setPhysicsBody(body);
	}
	map->addChild(enemyx);
	{
		Point bodyOrign;
		bodyOrign.x = enemyx->getPositionX() - 14.0f;
		bodyOrign.y = enemyx->getPositionY() - 19.0f;
		Size bodySize;
		bodySize.width = 28.0f;
		bodySize.height = 38.0f;
		enemyx->setBodyBox(bodyOrign, bodySize);
	}
	//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
}

void GameSceneOne::update(float dt)
{
	if (!isPauseGame)
	{
		//更新速度、状态等
		heroUpdate();
		enemiesUpdate();
		coinsUpdate();
		mapUpdate();
	}
}

void GameSceneOne::heroUpdate()
{
	//防止hero超出地图
	if (hero->getPositionX() < 10)
	{
		hero->setPositionX(10);
	}
	else if (hero->getPositionX() > map->getContentSize().width - 10)
	{
		hero->setPositionX(map->getContentSize().width - 10);
	}

	//根据状态变更hero
	switch (hero->getActionState())
	{
	case ActionState::IDLE:
		if (hero->getPhysicsBody()->getVelocity().y < -5.0f)
		{
			hero->setActionState(ActionState::JUMP);
			hero->runRoleAction();
		}
		else if (keyMap[EventKeyboard::KeyCode::KEY_LEFT_ARROW] || keyMap[EventKeyboard::KeyCode::KEY_RIGHT_ARROW] || isLeft || isRight)
		{
			hero->setActionState(ActionState::WALK);
			hero->runRoleAction();
		}
		break;

	case ActionState::WALK:
		if (hero->getDirection() == Direction::LEFT)
		{
			Vec2 temp = hero->getPhysicsBody()->getVelocity();
			temp.x = -hero->getVelX();
			hero->getPhysicsBody()->setVelocity(temp);
		}
		else
		{
			Vec2 temp = hero->getPhysicsBody()->getVelocity();
			temp.x = hero->getVelX();
			hero->getPhysicsBody()->setVelocity(temp);
		}
		break;

	case ActionState::JUMP:
		if (keyMap[EventKeyboard::KeyCode::KEY_LEFT_ARROW] || isLeft)
		{
			Vec2 temp = hero->getPhysicsBody()->getVelocity();
			temp.x = -hero->getVelX();
			hero->getPhysicsBody()->setVelocity(temp);
		}
		else if (keyMap[EventKeyboard::KeyCode::KEY_RIGHT_ARROW] || isRight)
		{
			Vec2 temp = hero->getPhysicsBody()->getVelocity();
			temp.x = hero->getVelX();
			hero->getPhysicsBody()->setVelocity(temp);
		}

		//更改跳跃动作
		if (hero->getPhysicsBody()->getVelocity().y < 0)
		{
			hero->isJumpUp = false;
			hero->runRoleAction();
		}
		break;

	case ActionState::ATTACK:
		if (enemy != NULL&&enemy->getActionState() < ActionState::HURT)
		{
			if (collisionDetection(hero->getHitBox(), enemy->getBodyBox()))
			{
				enemy->setActionState(ActionState::HURT);
				enemy->runRoleAction();
			}
		}
		//enemyxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
		if (enemyx != NULL&&enemyx->getActionState() < ActionState::HURT)
		{
			if (collisionDetection(hero->getHitBox(), enemyx->getBodyBox()))
			{
				enemyx->setActionState(ActionState::HURT);
				enemyx->runRoleAction();
			}
		}
		//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
		break;

	case ActionState::HURT:

		break;

	case ActionState::DIE:

		break;

	case ActionState::REMOVE:

		break;

	default:
		CCLOG("error:Action\n");
		break;
	}

	//无敌时间满计数后重置
	if (hero->invincibilityDuration == 6 * 7)
	{
		hero->invincibilityDuration = -1;
	}
	else if (hero->invincibilityDuration >= 0)
	{
		hero->invincibilityDuration++;
	}

	//根据跳跃按键时间改变跳跃高度
	if (jumpCount >= 0)
	{
		jumpCount++;
	}
	if (isJump&&jumpCount < 0)
	{
		jumpCount = 0;
	}
	else if (!isJump&&jumpCount >= 0)
	{
		if (jumpCount == 5)
		{
			jumpCount = -1;

			if (hero->getPhysicsBody()->getVelocity().y > 0)
			{
				Vec2 temp = hero->getPhysicsBody()->getVelocity();
				temp.y = 75;
				hero->getPhysicsBody()->setVelocity(temp);
			}
		}
		else if (jumpCount == 10)
		{
			jumpCount = -1;

			if (hero->getPhysicsBody()->getVelocity().y > 0)
			{
				Vec2 temp = hero->getPhysicsBody()->getVelocity();
				temp.y = 75;
				hero->getPhysicsBody()->setVelocity(temp);
			}
		}
		else if (jumpCount == 15)
		{
			jumpCount = -1;

			if (hero->getPhysicsBody()->getVelocity().y > 0)
			{
				Vec2 temp = hero->getPhysicsBody()->getVelocity();
				temp.y = 75;
				hero->getPhysicsBody()->setVelocity(temp);
			}
		}
		else if (jumpCount == 20)
		{
			jumpCount = -1;

			if (hero->getPhysicsBody()->getVelocity().y > 0)
			{
				Vec2 temp = hero->getPhysicsBody()->getVelocity();
				temp.y = 75;
				hero->getPhysicsBody()->setVelocity(temp);
			}
		}
		else if (jumpCount > 20)
		{
			jumpCount = -1;
		}
	}

	//hero更新碰撞盒
	Point bodyOrign;
	bodyOrign.x = hero->getPositionX() - 16.0f;
	bodyOrign.y = hero->getPositionY() - 23.0f;
	Size bodySize;
	bodySize.width = 32.0f;
	bodySize.height = 46.0f;
	hero->setBodyBox(bodyOrign, bodySize);
	Point hitOrign;
	Size hitSize;
	if (hero->getDirection() == Direction::RIGHT)
		hitOrign.x = hero->getPositionX();
	else
		hitOrign.x = hero->getPositionX() - 50.0f;
	hitOrign.y = hero->getPositionY() - 25.0f;
	hitSize.width = 50.0f;
	hitSize.height = 58.0f;
	hero->setHitBox(hitOrign, hitSize);

	//更新heart
	if (heartCount != hero->getHP() && hero->getHP() >= 0)
	{
		heartCount = hero->getHP();
		this->removeChild(heart[heartCount]);
	}

	//死亡判断
	if (hero->getActionState() == ActionState::REMOVE)
	{
		//重启游戏
		for (auto &i : coin)
		{
			if (i != NULL)
			{
				i = NULL;
			}
		}
		coin.clear();

		removeAllChildren();
		this->init();
	}
}

void GameSceneOne::enemiesUpdate()
{
	if (enemy != NULL)
	{
		if (enemy->getActionState() == ActionState::WALK)
		{   
			//enemy变更速度
			if (enemy->getDirection() == Direction::RIGHT)
			{
				Vec2 temp = enemy->getPhysicsBody()->getVelocity();
				temp.x = enemy->getVelX();
				enemy->getPhysicsBody()->setVelocity(temp);
			}
			else
			{
				Vec2 temp = enemy->getPhysicsBody()->getVelocity();
				temp.x = -enemy->getVelX();
				enemy->getPhysicsBody()->setVelocity(temp);
			}

			//改变enemy方向
			if (enemy->getHP() > 0 && enemy->getPositionX() + enemy->getContentSize().width / 2 >= enemy->getMoveEdge().rightX)
			{
				enemy->setDirection(Direction::LEFT);
				enemy->runRoleAction();
			}
			else if (enemy->getHP() > 0 && enemy->getPositionX() - enemy->getContentSize().width / 2 <= enemy->getMoveEdge().leftX)
			{
				enemy->setDirection(Direction::RIGHT);
				enemy->runRoleAction();
			}
		}

		//enemy碰撞hero
		if (enemy->getHP() > 0 && collisionDetection(enemy->getBodyBox(), hero->getBodyBox()) && hero->getActionState() < ActionState::HURT)
		{
			if (hero->invincibilityDuration < 0)
			{
				hero->runHurtAction();
			}
		}

		//碰撞盒更新
		Point bodyOrign;
		bodyOrign.x = enemy->getPositionX() - 14.0f;
		bodyOrign.y = enemy->getPositionY() - 29.0f;
		Size bodySize;
		bodySize.width = 18.0f;
		bodySize.height = 38.0f;
		enemy->setBodyBox(bodyOrign, bodySize);

		//死亡判断
		if (enemy->getActionState() == ActionState::REMOVE)
		{
			//生成coin
			for (int i = 0; i < 5; i++)
			{
				auto* tempCoin = Coin::create();
				tempCoin->setRole(Sprite::create("coin_idle1.png"));
				tempCoin->setPosition(enemy->getPosition());
				{
					auto* body = PhysicsBody::createBox(Size(20.0f, 30.0f), PhysicsMaterial(500.0f, 1.0f, 1.0f));
					body->setDynamic(true);
					body->setLinearDamping(0.0f);
					body->setGravityEnable(true);
					body->setContactTestBitmask(0x10);
					body->setCategoryBitmask(0x10);
					body->setCollisionBitmask(0x10 << i);
					body->setRotationEnable(false);
					tempCoin->setPhysicsBody(body);
				}
				map->addChild(tempCoin);
				tempCoin->getPhysicsBody()->setVelocity(Vec2(tempCoin->getVelX(), tempCoin->getVelY()));
				tempCoin->runRoleAction();
				coin.push_back(tempCoin);
			}

			//remove enemy
			map->removeChild(enemy);
			enemy = NULL;
		}
	}

	//enemyxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
	if (enemyx != NULL)
	{
		if (enemyx->getActionState() == ActionState::WALK)
		{
			if (enemyx->getDirection() == Direction::RIGHT)
			{
				Vec2 temp = enemyx->getPhysicsBody()->getVelocity();
				temp.x = enemyx->getVelX();
				enemyx->getPhysicsBody()->setVelocity(temp);
			}
			else
			{
				Vec2 temp = enemyx->getPhysicsBody()->getVelocity();
				temp.x = -enemyx->getVelX();
				enemyx->getPhysicsBody()->setVelocity(temp);
			}
		}
		if (enemyx->getHP() > 0 && enemyx->getPositionX() + enemyx->getContentSize().width / 2 >= enemyx->getMoveEdge().rightX)
		{
			enemyx->setDirection(Direction::LEFT);
			if (enemyx->getActionState() == ActionState::WALK)
				enemyx->runRoleAction();
		}
		else if (enemyx->getHP() > 0 && enemyx->getPositionX() - enemyx->getContentSize().width / 2 <= enemyx->getMoveEdge().leftX)
		{
			enemyx->setDirection(Direction::RIGHT);
			if (enemyx->getActionState() == ActionState::WALK)
				enemyx->runRoleAction();
		}
		if (enemyx->getHP() > 0 && collisionDetection(enemyx->getBodyBox(), hero->getBodyBox()) && hero->getActionState() < ActionState::HURT)
		{
			if (hero->invincibilityDuration < 0)
			{
				hero->runHurtAction();
			}
		}
		Point bodyOrign;
		bodyOrign.x = enemyx->getPositionX() - 14.0f;
		bodyOrign.y = enemyx->getPositionY() - 19.0f;
		Size bodySize;
		bodySize.width = 28.0f;
		bodySize.height = 38.0f;
		enemyx->setBodyBox(bodyOrign, bodySize);

		if (enemyx->getActionState() == ActionState::REMOVE)
		{
			//生成coin
			for (int i = 0; i < 5; i++)
			{
				auto* tempCoin = Coin::create();
				tempCoin->setRole(Sprite::create("coin_idle1.png"));
				tempCoin->setPosition(enemyx->getPosition());
				{
					auto* body = PhysicsBody::createBox(Size(20.0f, 30.0f), PhysicsMaterial(500.0f, 1.0f, 1.0f));
					body->setDynamic(true);
					body->setLinearDamping(0.0f);
					body->setGravityEnable(true);
					body->setContactTestBitmask(0x10);
					body->setCategoryBitmask(0x10);
					body->setCollisionBitmask(0x10 << i);
					body->setRotationEnable(false);
					tempCoin->setPhysicsBody(body);
				}
				map->addChild(tempCoin);
				tempCoin->getPhysicsBody()->setVelocity(Vec2(tempCoin->getVelX(), tempCoin->getVelY()));
				tempCoin->runRoleAction();
				coin.push_back(tempCoin);
			}

			map->removeChild(enemyx);
			enemyx = NULL;
		}
	}
	//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
}

void GameSceneOne::coinsUpdate()
{
	for (auto &i : coin)
	{
		if (i != NULL)
		{
			//hero吃掉coin
			if (collisionDetection(hero->getBodyBox(), i->getBodyBox()))
			{
				map->removeChild(i);
				i = NULL;

				//更新coin数量
				coinNumber++;
				UserDefault::getInstance()->setIntegerForKey("coinNumber", coinNumber);
				coinLabel->setString(__String::createWithFormat("%d", coinNumber)->getCString());
				if (coinNumber < 10)
					coinLabel->setPosition(Vec2(325, 338));
				else if (coinNumber<100)
					coinLabel->setPosition(Vec2(330, 338));
				else if (coinNumber<1000)
					coinLabel->setPosition(Vec2(335, 338));
				else if (coinNumber<10000)
					coinLabel->setPosition(Vec2(340, 338));
				else if (coinNumber<100000)
					coinLabel->setPosition(Vec2(345, 338));
				else
					coinLabel->setPosition(Vec2(350, 338));

				continue;
			}

			//coin更新碰撞盒
			Point bodyOrign;
			bodyOrign.x = i->getPositionX() - 5.0f;
			bodyOrign.y = i->getPositionY() - 5.0f;
			Size bodySize;
			bodySize.width = 10.0f;
			bodySize.height = 10.0f;
			i->setBodyBox(bodyOrign, bodySize);
		}
	}
}

void GameSceneOne::mapUpdate()
{
	//platforms
	if (hero->getPhysicsBody()->getVelocity().y > 0 || isJump)
	{
		platform1->getPhysicsBody()->setCategoryBitmask(0xFFFFFFF0);
		platform1->getPhysicsBody()->setCollisionBitmask(0xFFFFFFF0);
		platform2->getPhysicsBody()->setCategoryBitmask(0xFFFFFFF0);
		platform2->getPhysicsBody()->setCollisionBitmask(0xFFFFFFF0);
		platform3->getPhysicsBody()->setCategoryBitmask(0xFFFFFFF0);
		platform3->getPhysicsBody()->setCollisionBitmask(0xFFFFFFF0);
		platform4->getPhysicsBody()->setCategoryBitmask(0xFFFFFFF0);
		platform4->getPhysicsBody()->setCollisionBitmask(0xFFFFFFF0);
		platform5->getPhysicsBody()->setCategoryBitmask(0xFFFFFFF0);
		platform5->getPhysicsBody()->setCollisionBitmask(0xFFFFFFF0);
		platform6->getPhysicsBody()->setCategoryBitmask(0xFFFFFFF0);
		platform6->getPhysicsBody()->setCollisionBitmask(0xFFFFFFF0);
	}
	else if (hero->getPhysicsBody()->getVelocity().y < 0)
	{
		if (platform1->getPhysicsBody()->getCategoryBitmask() == 0xFFFFFFF0 && hero->getBodyBox().origin.y > platformRect1.origin.y + platformRect1.size.height)
		{
			platform1->getPhysicsBody()->setCategoryBitmask(0xFFFFFFFF);
			platform1->getPhysicsBody()->setCollisionBitmask(0xFFFFFFFF);
		}
		if (platform2->getPhysicsBody()->getCategoryBitmask() == 0xFFFFFFF0 && hero->getBodyBox().origin.y > platformRect2.origin.y + platformRect2.size.height)
		{
			platform2->getPhysicsBody()->setCategoryBitmask(0xFFFFFFFF);
			platform2->getPhysicsBody()->setCollisionBitmask(0xFFFFFFFF);
		}
		if (platform3->getPhysicsBody()->getCategoryBitmask() == 0xFFFFFFF0 && hero->getBodyBox().origin.y > platformRect3.origin.y + platformRect3.size.height)
		{
			platform3->getPhysicsBody()->setCategoryBitmask(0xFFFFFFFF);
			platform3->getPhysicsBody()->setCollisionBitmask(0xFFFFFFFF);
		}
		if (platform4->getPhysicsBody()->getCategoryBitmask() == 0xFFFFFFF0 && hero->getBodyBox().origin.y > platformRect4.origin.y + platformRect4.size.height)
		{
			platform4->getPhysicsBody()->setCategoryBitmask(0xFFFFFFFF);
			platform4->getPhysicsBody()->setCollisionBitmask(0xFFFFFFFF);
		}
		if (platform5->getPhysicsBody()->getCategoryBitmask() == 0xFFFFFFF0 && hero->getBodyBox().origin.y > platformRect5.origin.y + platformRect5.size.height)
		{
			platform5->getPhysicsBody()->setCategoryBitmask(0xFFFFFFFF);
			platform5->getPhysicsBody()->setCollisionBitmask(0xFFFFFFFF);
		}
		if (platform6->getPhysicsBody()->getCategoryBitmask() == 0xFFFFFFF0 && hero->getBodyBox().origin.y > platformRect6.origin.y + platformRect6.size.height)
		{
			platform6->getPhysicsBody()->setCategoryBitmask(0xFFFFFFFF);
			platform6->getPhysicsBody()->setCollisionBitmask(0xFFFFFFFF);
		}
	}

	//tips
	if (collisionDetection(hero->getBodyBox(), tipRect1))
	{
		if (!isTipIn1)
		{
			isTipIn1 = true;
			auto* fadein = FadeIn::create(0.6f);
			tipLabel1->runAction(fadein);
		}
	}
	else
	{
		if (isTipIn1)
		{
			isTipIn1 = false;
			auto* fadeout = FadeOut::create(0.8f);
			tipLabel1->runAction(fadeout);
		}
	}
	if (collisionDetection(hero->getBodyBox(), tipRect2))
	{
		if (!isTipIn2)
		{
			isTipIn2 = true;
			auto* fadein = FadeIn::create(0.6f);
			tipLabel2->runAction(fadein);
		}
	}
	else
	{
		if (isTipIn2)
		{
			isTipIn2 = false;
			auto* fadeout = FadeOut::create(0.8f);
			tipLabel2->runAction(fadeout);
		}
	}
	if (collisionDetection(hero->getBodyBox(), tipRect3))
	{
		if (!isTipIn3)
		{
			isTipIn3 = true;
			auto* fadein = FadeIn::create(0.6f);
			tipLabel3->runAction(fadein);
		}
	}
	else
	{
		if (isTipIn3)
		{
			isTipIn3 = false;
			auto* fadeout = FadeOut::create(0.8f);
			tipLabel3->runAction(fadeout);
		}
	}
	if (collisionDetection(hero->getBodyBox(), tipRect4))
	{
		if (!isTipIn4)
		{
			isTipIn4 = true;
			auto* fadein = FadeIn::create(0.6f);
			tipLabel4->runAction(fadein);
		}
	}
	else
	{
		if (isTipIn4)
		{
			isTipIn4 = false;
			auto* fadeout = FadeOut::create(0.8f);
			tipLabel4->runAction(fadeout);
		}
	}
	if (collisionDetection(hero->getBodyBox(), tipRect5))
	{
		if (!isTipIn5)
		{
			isTipIn5 = true;
			auto* fadein = FadeIn::create(0.6f);
			tipLabel5->runAction(fadein);
		}
	}
	else
	{
		if (isTipIn5)
		{
			isTipIn5 = false;
			auto* fadeout = FadeOut::create(0.8f);
			tipLabel5->runAction(fadeout);
		}
	}

	//door
	if (collisionDetection(hero->getBodyBox(), doorRect) && hero->getActionState() == ActionState::ATTACK)
	{
		isPauseGame = true;
		auto* rotate = RotateBy::create(1.0f, Vec3(0, 0, 1080.0f));
		auto* scale = ScaleBy::create(1.0f, 0.2f);
		auto* action = Spawn::create(rotate, scale, NULL);
		auto* callFunc = CallFunc::create(CC_CALLBACK_0(GameSceneOne::enterNextLevel, this));
		auto* sequence = Sequence::create(action, callFunc, NULL);
		hero->runAction(sequence);
	}

	//移动地图，更新可视区域
	map->setPositionX(visibleSize.width / 2 - hero->getPositionX());
	map->setPositionY(visibleSize.height / 2 - hero->getPositionY());
	if (map->getPositionX() > 0)
	{
		map->setPositionX(0);
	}
	else if (map->getPositionX() < visibleSize.width - map->getContentSize().width)
	{
		map->setPositionX(visibleSize.width - map->getContentSize().width);
	}
	if (map->getPositionY() > 0)
	{
		map->setPositionY(0);
	}
	else if (map->getPositionY() < visibleSize.height - map->getContentSize().height)
	{
		map->setPositionY(visibleSize.height - map->getContentSize().height);
	}
}

void GameSceneOne::onKeyPressed(EventKeyboard::KeyCode keyCode, Event *event)
{
	keyMap[keyCode] = true;
	switch (keyCode) 
	{
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		keyMap[EventKeyboard::KeyCode::KEY_RIGHT_ARROW] = false;
		break;
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		keyMap[EventKeyboard::KeyCode::KEY_LEFT_ARROW] = false;
		break;
	case EventKeyboard::KeyCode::KEY_UP_ARROW:
		keyMap[EventKeyboard::KeyCode::KEY_DOWN_ARROW] = false;
		break;
	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		keyMap[EventKeyboard::KeyCode::KEY_UP_ARROW] = false;
		break;
	default:
		break;
	}

	//更改hero的状态，并播放动画
	if (keyMap[EventKeyboard::KeyCode::KEY_LEFT_ARROW])
	{
		hero->setDirection(Direction::LEFT);
		if (hero->getActionState() < ActionState::WALK)
		{
			hero->setActionState(WALK);
			hero->runRoleAction();
		}
		else if (hero->getActionState() == ActionState::JUMP)
		{
			hero->runRoleAction();
		}
		else if (hero->getActionState() == ActionState::WALK)
		{
			hero->runRoleAction();
		}
	}
	else if (keyMap[EventKeyboard::KeyCode::KEY_RIGHT_ARROW])
	{
		hero->setDirection(Direction::RIGHT);
		if (hero->getActionState() < ActionState::WALK)
		{
			hero->setActionState(WALK);
			hero->runRoleAction();
		}
		else if (hero->getActionState() == ActionState::JUMP)
		{
			hero->runRoleAction();
		}
		else if (hero->getActionState() == ActionState::WALK)
		{
			hero->runRoleAction();
		}
	}
	//if (keyMap[EventKeyboard::KeyCode::KEY_C])
	//{
	//	if (hero->getActionState() < ActionState::ATTACK)
	//	{
	//		hero->setActionState(ActionState::ATTACK);
	//		hero->runRoleAction();
	//		if (enemy != NULL&&enemy->getActionState() != ActionState::DIE)
	//		{
	//			if (collisionDetection(hero->getHitBox(), enemy->getBodyBox()))
	//			{
	//				enemy->setActionState(ActionState::HURT);
	//				enemy->runRoleAction();
	//			}
	//		}
	//	}
	//}
	//if (keyMap[EventKeyboard::KeyCode::KEY_SPACE])
	//{
	//	if (hero->getActionState() < ActionState::ATTACK)
	//	{
	//		Vec2 temp = hero->getPhysicsBody()->getVelocity();
	//		if (hero->getPhysicsBody()->getVelocity().y <= 0.01f&& hero->getPhysicsBody()->getVelocity().y >= -0.01f)
	//		{
	//			Vec2 temp = hero->getPhysicsBody()->getVelocity();
	//			temp.y = 330;
	//			hero->getPhysicsBody()->setVelocity(temp);

	//			hero->setActionState(ActionState::JUMP);
	//			hero->runRoleAction();
	//		}
	//	}
	//}
}

void GameSceneOne::onKeyReleased(EventKeyboard::KeyCode keyCode, Event *event)
{
	//更改hero的状态
	if (hero->getActionState() == ActionState::WALK)
	{
		if (keyMap[EventKeyboard::KeyCode::KEY_LEFT_ARROW])
		{
			hero->setActionState(ActionState::IDLE);
			hero->runRoleAction();
		}
		else if (keyMap[EventKeyboard::KeyCode::KEY_RIGHT_ARROW])
		{
			hero->setActionState(ActionState::IDLE);
			hero->runRoleAction();
		}
	}

	keyMap[keyCode] = false;
}

void GameSceneOne::onLeft(cocos2d::Ref * pSender, cocos2d::ui::Widget::TouchEventType type)
{
	switch (type)
	{
	case ui::Widget::TouchEventType::BEGAN:
		isLeft = true;
		isRight = false;
		if (hero->getActionState() < ActionState::WALK)
		{
			hero->setDirection(Direction::LEFT);
			hero->setActionState(WALK);
			hero->runRoleAction();
		}
		else if (hero->getActionState() == ActionState::JUMP&&hero->getDirection() != Direction::LEFT)
		{
			hero->setDirection(Direction::LEFT);
			hero->runRoleAction();
		}
		else if (hero->getActionState() == ActionState::WALK&&hero->getDirection() != Direction::LEFT)
		{
			hero->setDirection(Direction::LEFT);
			hero->runRoleAction();
		}
		else
		{
			hero->setDirection(Direction::LEFT);
		}
		break;
	case ui::Widget::TouchEventType::ENDED:
		isLeft = false;
		if (hero->getActionState() == ActionState::WALK)
		{
			hero->setActionState(ActionState::IDLE);
			hero->runRoleAction();
		}
		break;
	case ui::Widget::TouchEventType::CANCELED:
		isLeft = false;
		if (hero->getActionState() == ActionState::WALK)
		{
			hero->setActionState(ActionState::IDLE);
			hero->runRoleAction();
		}
		break;
	default:
		break;
	}
}

void GameSceneOne::onRight(cocos2d::Ref * pSender, cocos2d::ui::Widget::TouchEventType type)
{
	switch (type)
	{
	case ui::Widget::TouchEventType::BEGAN:
		isRight = true;
		isLeft = false;
		if (hero->getActionState() < ActionState::WALK)
		{
			hero->setDirection(Direction::RIGHT);
			hero->setActionState(WALK);
			hero->runRoleAction();
		}
		else if (hero->getActionState() == ActionState::JUMP&&hero->getDirection() != Direction::RIGHT)
		{
			hero->setDirection(Direction::RIGHT);
			hero->runRoleAction();
		}
		else if (hero->getActionState() == ActionState::WALK&&hero->getDirection() != Direction::RIGHT)
		{
			hero->setDirection(Direction::RIGHT);
			hero->runRoleAction();
		}
		else
		{
			hero->setDirection(Direction::RIGHT);
		}
		break;
	case ui::Widget::TouchEventType::ENDED:
		isRight = false;
		if (hero->getActionState() == ActionState::WALK)
		{
			hero->setActionState(ActionState::IDLE);
			hero->runRoleAction();
		}
		break;
	case ui::Widget::TouchEventType::CANCELED:
		isRight = false;
		if (hero->getActionState() == ActionState::WALK)
		{
			hero->setActionState(ActionState::IDLE);
			hero->runRoleAction();
		}
		break;
	default:
		break;
	}
}

void GameSceneOne::onJump(cocos2d::Ref * pSender, cocos2d::ui::Widget::TouchEventType type)
{
	switch (type)
	{
	case ui::Widget::TouchEventType::BEGAN:
		isJump = true;
		if (hero->getActionState() < ActionState::JUMP)
		{
			Vec2 temp = hero->getPhysicsBody()->getVelocity();
			temp.y = hero->getVelY();
			hero->getPhysicsBody()->setVelocity(temp);

			hero->isJumpUp = true;
			hero->setActionState(ActionState::JUMP);
			hero->runRoleAction();
		}
		break;
	case ui::Widget::TouchEventType::ENDED:
		isJump = false;
		break;
	case ui::Widget::TouchEventType::CANCELED:
		isJump = false;
		break;
	default:
		break;
	}
}

void GameSceneOne::onAttack(cocos2d::Ref * pSender, cocos2d::ui::Widget::TouchEventType type)
{
	switch (type)
	{
	case ui::Widget::TouchEventType::BEGAN:
		isAttack = true;
		if (hero->getActionState() < ActionState::ATTACK)
		{
			hero->setActionState(ActionState::ATTACK);
			hero->runRoleAction();
		}
		break;
	case ui::Widget::TouchEventType::ENDED:
		isAttack = false;
		break;
	case ui::Widget::TouchEventType::CANCELED:
		isAttack = false;
		break;
	default:
		break;
	}
}

bool GameSceneOne::onContactBegin(cocos2d::PhysicsContact & contact)
{
	Node* nodeA = contact.getShapeA()->getBody()->getNode();
	Node* nodeB = contact.getShapeB()->getBody()->getNode();

	//hero与ground的碰撞
	if ((nodeA->getTag() == Tag::GROUND && nodeB->getTag() == Tag::HERO) || (nodeA->getTag() == Tag::HERO && nodeB->getTag() == Tag::GROUND))
	{
		auto contactData = contact.getContactData();

		//侧面碰撞
		if (contactData->normal.y == 0)
		{
			hero->setVelX(2);
		}
		//水平面碰撞
		if (contactData->normal.x == 0)
		{
			if (hero->getActionState() == ActionState::JUMP&&hero->getPhysicsBody()->getVelocity().y < 0)
			{
				Vec2 temp(0, 0);
				hero->getPhysicsBody()->setVelocity(temp);

				hero->setActionState(ActionState::IDLE);
				hero->runRoleAction();
			}
		}
	}

	//enemy与ground碰撞
	if ((nodeA->getTag() == Tag::GROUND && nodeB->getTag() == Tag::ENEMYA) || (nodeA->getTag() == Tag::ENEMYA && nodeB->getTag() == Tag::GROUND))
	{
		enemy->setActionState(ActionState::WALK);
		enemy->runRoleAction();
	}
	//enemyxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
	if ((nodeA->getTag() == Tag::GROUND && nodeB->getTag() == Tag::ENEMYB) || (nodeA->getTag() == Tag::ENEMYB && nodeB->getTag() == Tag::GROUND))
	{
		enemyx->setActionState(ActionState::WALK);
		enemyx->runRoleAction();
	}
	//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
	return true;
}

void GameSceneOne::onContactSeperate(cocos2d::PhysicsContact & contact)
{
	Node* nodeA = contact.getShapeA()->getBody()->getNode();
	Node* nodeB = contact.getShapeB()->getBody()->getNode();

	//hero与ground的分离
	if ((nodeA->getTag() == Tag::GROUND && nodeB->getTag() == Tag::HERO) || (nodeA->getTag() == Tag::HERO && nodeB->getTag() == Tag::GROUND))
	{
		auto contactData = contact.getContactData();

		//侧面分离
		if (contactData->normal.x != 0)
			hero->setVelX(200);
		//水平面分离
		if (contactData->normal.y != 0)
		{
			if (hero->getActionState() < ActionState::JUMP)
			{
				hero->setActionState(ActionState::JUMP);
				hero->runRoleAction();
			}
		}
	}
}

bool GameSceneOne::collisionDetection(cocos2d::Rect hitBox, cocos2d::Rect bodyBox)
{
	if (hitBox.intersectsRect(bodyBox))
		return true;
	else
		return false;
}

void GameSceneOne::pauseGame()
{
	if (!isPauseGame)
	{
		isPauseGame = true;

		pauseBG = LayerColor::create(Color4B(0, 0, 0, 200));
		this->addChild(pauseBG);

		resumeItem = MenuItemImage::create("resume1.png", "resume1.png", CC_CALLBACK_0(GameSceneOne::resumeGame, this));
		resumeItem->setPosition(Vec2(360, 180));
		backItem = MenuItemImage::create("back1.png", "back1.png", CC_CALLBACK_0(GameSceneOne::back, this));
		backItem->setPosition(Vec2(280, 180));
		pauseMenu = Menu::create(resumeItem, backItem, NULL);
		pauseMenu->setPosition(Vec2::ZERO);
		this->addChild(pauseMenu);
	}
}

void GameSceneOne::resumeGame()
{
	if (isPauseGame)
	{
		isPauseGame = false;

		this->removeChild(pauseBG);
		this->removeChild(pauseMenu);
	}
}

void GameSceneOne::back()
{
	if (isPauseGame)
	{
		isPauseGame = false;

		auto selectScene = SelectScene::createScene();
		Director::getInstance()->replaceScene(TransitionFade::create(1.0f, selectScene));
	}
}

void GameSceneOne::enterNextLevel()
{
	//清除子节点
	for (auto &i : coin)
	{
		if (i != NULL)
		{
			i = NULL;
		}
	}
	coin.clear();

	removeAllChildren();

	auto gameScene = GameSceneTwo::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(1.0f, gameScene));
}
