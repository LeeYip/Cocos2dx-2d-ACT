#include "GameSceneTwo.h"

USING_NS_CC;
using namespace ui;

cocos2d::Scene * GameSceneTwo::createScene()
{
	//创建带物理引擎的scene
	Scene* scene = Scene::createWithPhysics();

	//调试
	//scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

	//设置重力加速度
	scene->getPhysicsWorld()->setGravity(Vec2(0.0f, -900.0f));

	auto layer = GameSceneTwo::create();
	scene->addChild(layer);

	return scene;
}

bool GameSceneTwo::init()
{
	if (!Scene::init())
	{
		return false;
	}

	//更新解锁的关卡
	if (UserDefault::getInstance()->getIntegerForKey("level") < 2)
		UserDefault::getInstance()->setIntegerForKey("level", 2);

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
	map = TMXTiledMap::create("map2.tmx");
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
	auto* platformBody1 = PhysicsBody::createBox(Size(72, 18), PhysicsMaterial(1000.0f, 0.5f, 1.0f));
	platformBody1->setDynamic(false);
	platformBody1->setContactTestBitmask(0xFFFFFFFF);
	platformBody1->setCategoryBitmask(0xFFFFFFF0);
	platformBody1->setCollisionBitmask(0xFFFFFFF0);
	platform1 = Node::create();
	platform1->setPhysicsBody(platformBody1);
	platform1->setPosition(Vec2(216.0f, 171.0f));
	platform1->setTag(Tag::GROUND);
	map->addChild(platform1);
	platformRect1.origin.x = 180.0f;
	platformRect1.origin.y = 162.0f;
	platformRect1.size.width = 72.0f;
	platformRect1.size.height = 18.0f;

	auto* platformBody2 = PhysicsBody::createBox(Size(180, 18), PhysicsMaterial(1000.0f, 0.5f, 1.0f));
	platformBody2->setDynamic(false);
	platformBody2->setContactTestBitmask(0xFFFFFFFF);
	platformBody2->setCategoryBitmask(0xFFFFFFF0);
	platformBody2->setCollisionBitmask(0xFFFFFFF0);
	platform2 = Node::create();
	platform2->setPhysicsBody(platformBody2);
	platform2->setPosition(Vec2(90.0f, 243.0f));
	platform2->setTag(Tag::GROUND);
	map->addChild(platform2);
	platformRect2.origin.x = 0.0f;
	platformRect2.origin.y = 234.0f;
	platformRect2.size.width = 180.0f;
	platformRect2.size.height = 18.0f;

	auto* platformBody3 = PhysicsBody::createBox(Size(72, 18), PhysicsMaterial(1000.0f, 0.5f, 1.0f));
	platformBody3->setDynamic(false);
	platformBody3->setContactTestBitmask(0xFFFFFFFF);
	platformBody3->setCategoryBitmask(0xFFFFFFF0);
	platformBody3->setCollisionBitmask(0xFFFFFFF0);
	platform3 = Node::create();
	platform3->setPhysicsBody(platformBody3);
	platform3->setPosition(Vec2(180.0f, 333.0f));
	platform3->setTag(Tag::GROUND);
	map->addChild(platform3);
	platformRect3.origin.x = 144.0f;
	platformRect3.origin.y = 324.0f;
	platformRect3.size.width = 72.0f;
	platformRect3.size.height = 18.0f;

	auto* platformBody4 = PhysicsBody::createBox(Size(324, 18), PhysicsMaterial(1000.0f, 0.5f, 1.0f));
	platformBody4->setDynamic(false);
	platformBody4->setContactTestBitmask(0xFFFFFFFF);
	platformBody4->setCategoryBitmask(0xFFFFFFF0);
	platformBody4->setCollisionBitmask(0xFFFFFFF0);
	platform4 = Node::create();
	platform4->setPhysicsBody(platformBody4);
	platform4->setPosition(Vec2(846.0f, 441.0f));
	platform4->setTag(Tag::GROUND);
	map->addChild(platform4);
	platformRect4.origin.x = 684.0f;
	platformRect4.origin.y = 432.0f;
	platformRect4.size.width = 324.0f;
	platformRect4.size.height = 18.0f;

	auto* platformBody5 = PhysicsBody::createBox(Size(72, 18), PhysicsMaterial(1000.0f, 0.5f, 1.0f));
	platformBody5->setDynamic(false);
	platformBody5->setContactTestBitmask(0xFFFFFFFF);
	platformBody5->setCategoryBitmask(0xFFFFFFF0);
	platformBody5->setCollisionBitmask(0xFFFFFFF0);
	platform5 = Node::create();
	platform5->setPhysicsBody(platformBody5);
	platform5->setPosition(Vec2(648.0f, 531.0f));
	platform5->setTag(Tag::GROUND);
	map->addChild(platform5);
	platformRect5.origin.x = 612.0f;
	platformRect5.origin.y = 522.0f;
	platformRect5.size.width = 72.0f;
	platformRect5.size.height = 18.0f;

	auto* platformBody6 = PhysicsBody::createBox(Size(108, 18), PhysicsMaterial(1000.0f, 0.5f, 1.0f));
	platformBody6->setDynamic(false);
	platformBody6->setContactTestBitmask(0xFFFFFFFF);
	platformBody6->setCategoryBitmask(0xFFFFFFF0);
	platformBody6->setCollisionBitmask(0xFFFFFFF0);
	platform6 = Node::create();
	platform6->setPhysicsBody(platformBody6);
	platform6->setPosition(Vec2(1530.0f, 315.0f));
	platform6->setTag(Tag::GROUND);
	map->addChild(platform6);
	platformRect6.origin.x = 1476.0f;
	platformRect6.origin.y = 306.0f;
	platformRect6.size.width = 108.0f;
	platformRect6.size.height = 18.0f;

	auto* platformBody7 = PhysicsBody::createBox(Size(325, 18), PhysicsMaterial(1000.0f, 0.5f, 1.0f));
	platformBody7->setDynamic(false);
	platformBody7->setContactTestBitmask(0xFFFFFFFF);
	platformBody7->setCategoryBitmask(0xFFFFFFF0);
	platformBody7->setCollisionBitmask(0xFFFFFFF0);
	platform7 = Node::create();
	platform7->setPhysicsBody(platformBody7);
	platform7->setPosition(Vec2(1602.0f, 171.0f));
	platform7->setTag(Tag::GROUND);
	map->addChild(platform7);
	platformRect7.origin.x = 1440.0f;
	platformRect7.origin.y = 162.0f;
	platformRect7.size.width = 324.0f;
	platformRect7.size.height = 18.0f;

	auto* platformBody8 = PhysicsBody::createBox(Size(108, 18), PhysicsMaterial(1000.0f, 0.5f, 1.0f));
	platformBody8->setDynamic(false);
	platformBody8->setContactTestBitmask(0xFFFFFFFF);
	platformBody8->setCategoryBitmask(0xFFFFFFF0);
	platformBody8->setCollisionBitmask(0xFFFFFFF0);
	platform8 = Node::create();
	platform8->setPhysicsBody(platformBody8);
	platform8->setPosition(Vec2(1674.0f, 243.0f));
	platform8->setTag(Tag::GROUND);
	map->addChild(platform8);
	platformRect8.origin.x = 1620.0f;
	platformRect8.origin.y = 234.0f;
	platformRect8.size.width = 108.0f;
	platformRect8.size.height = 18.0f;

	auto* platformBody9 = PhysicsBody::createBox(Size(108, 18), PhysicsMaterial(1000.0f, 0.5f, 1.0f));
	platformBody9->setDynamic(false);
	platformBody9->setContactTestBitmask(0xFFFFFFFF);
	platformBody9->setCategoryBitmask(0xFFFFFFF0);
	platformBody9->setCollisionBitmask(0xFFFFFFF0);
	platform9 = Node::create();
	platform9->setPhysicsBody(platformBody9);
	platform9->setPosition(Vec2(1602.0f, 423.0f));
	platform9->setTag(Tag::GROUND);
	map->addChild(platform9);
	platformRect9.origin.x = 1548.0f;
	platformRect9.origin.y = 414.0f;
	platformRect9.size.width = 108.0f;
	platformRect9.size.height = 18.0f;

	auto* platformBody10 = PhysicsBody::createBox(Size(108, 18), PhysicsMaterial(1000.0f, 0.5f, 1.0f));
	platformBody10->setDynamic(false);
	platformBody10->setContactTestBitmask(0xFFFFFFFF);
	platformBody10->setCategoryBitmask(0xFFFFFFF0);
	platformBody10->setCollisionBitmask(0xFFFFFFF0);
	platform10 = Node::create();
	platform10->setPhysicsBody(platformBody10);
	platform10->setPosition(Vec2(1746.0f, 513.0f));
	platform10->setTag(Tag::GROUND);
	map->addChild(platform10);
	platformRect10.origin.x = 1692.0f;
	platformRect10.origin.y = 504.0f;
	platformRect10.size.width = 108.0f;
	platformRect10.size.height = 18.0f;

	auto* platformBody11 = PhysicsBody::createBox(Size(108, 18), PhysicsMaterial(1000.0f, 0.5f, 1.0f));
	platformBody11->setDynamic(false);
	platformBody11->setContactTestBitmask(0xFFFFFFFF);
	platformBody11->setCategoryBitmask(0xFFFFFFF0);
	platformBody11->setCollisionBitmask(0xFFFFFFF0);
	platform11 = Node::create();
	platform11->setPhysicsBody(platformBody11);
	platform11->setPosition(Vec2(1566.0f, 603.0f));
	platform11->setTag(Tag::GROUND);
	map->addChild(platform11);
	platformRect11.origin.x = 1512.0f;
	platformRect11.origin.y = 594.0f;
	platformRect11.size.width = 108.0f;
	platformRect11.size.height = 18.0f;

	auto* platformBody12 = PhysicsBody::createBox(Size(108, 18), PhysicsMaterial(1000.0f, 0.5f, 1.0f));
	platformBody12->setDynamic(false);
	platformBody12->setContactTestBitmask(0xFFFFFFFF);
	platformBody12->setCategoryBitmask(0xFFFFFFF0);
	platformBody12->setCollisionBitmask(0xFFFFFFF0);
	platform12 = Node::create();
	platform12->setPhysicsBody(platformBody12);
	platform12->setPosition(Vec2(1638.0f, 693.0f));
	platform12->setTag(Tag::GROUND);
	map->addChild(platform12);
	platformRect12.origin.x = 1584.0f;
	platformRect12.origin.y = 684.0f;
	platformRect12.size.width = 108.0f;
	platformRect12.size.height = 18.0f;

	auto* platformBody13 = PhysicsBody::createBox(Size(108, 18), PhysicsMaterial(1000.0f, 0.5f, 1.0f));
	platformBody13->setDynamic(false);
	platformBody13->setContactTestBitmask(0xFFFFFFFF);
	platformBody13->setCategoryBitmask(0xFFFFFFF0);
	platformBody13->setCollisionBitmask(0xFFFFFFF0);
	platform13 = Node::create();
	platform13->setPhysicsBody(platformBody13);
	platform13->setPosition(Vec2(1530.0f, 783.0f));
	platform13->setTag(Tag::GROUND);
	map->addChild(platform13);
	platformRect13.origin.x = 1476.0f;
	platformRect13.origin.y = 774.0f;
	platformRect13.size.width = 108.0f;
	platformRect13.size.height = 18.0f;

	auto* platformBody14 = PhysicsBody::createBox(Size(108, 18), PhysicsMaterial(1000.0f, 0.5f, 1.0f));
	platformBody14->setDynamic(false);
	platformBody14->setContactTestBitmask(0xFFFFFFFF);
	platformBody14->setCategoryBitmask(0xFFFFFFF0);
	platformBody14->setCollisionBitmask(0xFFFFFFF0);
	platform14 = Node::create();
	platform14->setPhysicsBody(platformBody14);
	platform14->setPosition(Vec2(1674.0f, 873.0f));
	platform14->setTag(Tag::GROUND);
	map->addChild(platform14);
	platformRect14.origin.x = 1620.0f;
	platformRect14.origin.y = 864.0f;
	platformRect14.size.width = 108.0f;
	platformRect14.size.height = 18.0f;

	auto* platformBody15 = PhysicsBody::createBox(Size(108, 18), PhysicsMaterial(1000.0f, 0.5f, 1.0f));
	platformBody15->setDynamic(false);
	platformBody15->setContactTestBitmask(0xFFFFFFFF);
	platformBody15->setCategoryBitmask(0xFFFFFFF0);
	platformBody15->setCollisionBitmask(0xFFFFFFF0);
	platform15 = Node::create();
	platform15->setPhysicsBody(platformBody15);
	platform15->setPosition(Vec2(1530.0f, 963.0f));
	platform15->setTag(Tag::GROUND);
	map->addChild(platform15);
	platformRect15.origin.x = 1476.0f;
	platformRect15.origin.y = 954.0f;
	platformRect15.size.width = 108.0f;
	platformRect15.size.height = 18.0f;

	auto* platformBody16 = PhysicsBody::createBox(Size(72, 18), PhysicsMaterial(1000.0f, 0.5f, 1.0f));
	platformBody16->setDynamic(false);
	platformBody16->setContactTestBitmask(0xFFFFFFFF);
	platformBody16->setCategoryBitmask(0xFFFFFFF0);
	platformBody16->setCollisionBitmask(0xFFFFFFF0);
	platform16 = Node::create();
	platform16->setPhysicsBody(platformBody16);
	platform16->setPosition(Vec2(900.0f, 1143.0f));
	platform16->setTag(Tag::GROUND);
	map->addChild(platform16);
	platformRect16.origin.x = 864.0f;
	platformRect16.origin.y = 1134.0f;
	platformRect16.size.width = 72.0f;
	platformRect16.size.height = 18.0f;

	auto* platformBody17 = PhysicsBody::createBox(Size(72, 18), PhysicsMaterial(1000.0f, 0.5f, 1.0f));
	platformBody17->setDynamic(false);
	platformBody17->setContactTestBitmask(0xFFFFFFFF);
	platformBody17->setCategoryBitmask(0xFFFFFFF0);
	platformBody17->setCollisionBitmask(0xFFFFFFF0);
	platform17 = Node::create();
	platform17->setPhysicsBody(platformBody17);
	platform17->setPosition(Vec2(828.0f, 1233.0f));
	platform17->setTag(Tag::GROUND);
	map->addChild(platform17);
	platformRect17.origin.x = 792.0f;
	platformRect17.origin.y = 1224.0f;
	platformRect17.size.width = 72.0f;
	platformRect17.size.height = 18.0f;

	auto* platformBody18 = PhysicsBody::createBox(Size(72, 18), PhysicsMaterial(1000.0f, 0.5f, 1.0f));
	platformBody18->setDynamic(false);
	platformBody18->setContactTestBitmask(0xFFFFFFFF);
	platformBody18->setCategoryBitmask(0xFFFFFFF0);
	platformBody18->setCollisionBitmask(0xFFFFFFF0);
	platform18 = Node::create();
	platform18->setPhysicsBody(platformBody18);
	platform18->setPosition(Vec2(900.0f, 1323.0f));
	platform18->setTag(Tag::GROUND);
	map->addChild(platform18);
	platformRect18.origin.x = 864.0f;
	platformRect18.origin.y = 1314.0f;
	platformRect18.size.width = 72.0f;
	platformRect18.size.height = 18.0f;

	//door
	door = Sprite::create("door.png");
	door->setPosition(Vec2(288, 1188 + door->getContentSize().height / 2));
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
	pauseItem = MenuItemImage::create("pause1.png", "pause1.png", CC_CALLBACK_0(GameSceneTwo::pauseGame, this));
	pauseItem->setPosition(Vec2(620, 340));
	auto* menu = Menu::create(pauseItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu);

	//虚拟按键
	left = ui::Button::create("left1.png", "left2.png");
	left->setPosition(Vec2(70, 40));
	left->addTouchEventListener(ui::Widget::ccWidgetTouchCallback(CC_CALLBACK_2(GameSceneTwo::onLeft, this)));
	this->addChild(left);
	right = ui::Button::create("right1.png", "right2.png");
	right->setPosition(Vec2(180, 40));
	right->addTouchEventListener(ui::Widget::ccWidgetTouchCallback(CC_CALLBACK_2(GameSceneTwo::onRight, this)));
	this->addChild(right);
	jump = ui::Button::create("jump1.png", "jump2.png");
	jump->setPosition(Vec2(600, 40));
	jump->addTouchEventListener(ui::Widget::ccWidgetTouchCallback(CC_CALLBACK_2(GameSceneTwo::onJump, this)));
	this->addChild(jump);
	attack = ui::Button::create("attack1.png", "attack2.png");
	attack->setPosition(Vec2(520, 40));
	attack->addTouchEventListener(ui::Widget::ccWidgetTouchCallback(CC_CALLBACK_2(GameSceneTwo::onAttack, this)));
	this->addChild(attack);

	isLeft = false;
	isRight = false;
	isJump = false;
	isAttack = false;

	//键盘监听
	auto keyListener = EventListenerKeyboard::create();
	keyListener->onKeyPressed = CC_CALLBACK_2(GameSceneTwo::onKeyPressed, this);
	keyListener->onKeyReleased = CC_CALLBACK_2(GameSceneTwo::onKeyReleased, this);
	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(keyListener, this);

	//碰撞监听
	EventListenerPhysicsContact* contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(GameSceneTwo::onContactBegin, this);
	contactListener->onContactSeparate = CC_CALLBACK_1(GameSceneTwo::onContactSeperate, this);
	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);

	return true;
}

void GameSceneTwo::heroInit()
{
	hero = Hero::create();
	hero->setRole(Sprite::create("hero_rightidle1.png"));
	hero->setPosition(Vec2(50.0f, 113.0f));
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
	hero->getPhysicsBody()->setVelocity(Vec2(0, 0));

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

void GameSceneTwo::enemiesInit()
{
	//enemyA
	enemyA = Enemy::create();
	enemyA->setRole(Sprite::create("enemy_rightwalk1.png"));
	enemyA->setPosition(Vec2(302.0f, 379.0f));
	enemyA->setMoveEdge(302.0f, 1426.0f);
	enemyA->setTag(Tag::ENEMYA);
	{
		auto* body = PhysicsBody::createBox(Size(28.0f, 38.0f), PhysicsMaterial(500.0f, 0.0f, 1.0f));
		body->setDynamic(true);
		body->setLinearDamping(0.0f);
		body->setGravityEnable(true);
		body->setContactTestBitmask(0x10);
		body->setCategoryBitmask(0x10);
		body->setCollisionBitmask(0x10);
		body->setRotationEnable(false);
		enemyA->setPhysicsBody(body);
	}
	map->addChild(enemyA);
	enemyA->setActionState(ActionState::WALK);
	enemyA->runRoleAction();
	//碰撞盒初始化
	{
		Point bodyOrign;
		bodyOrign.x = enemyA->getPositionX() - 14.0f;
		bodyOrign.y = enemyA->getPositionY() - 19.0f;
		Size bodySize;
		bodySize.width = 28.0f;
		bodySize.height = 38.0f;
		enemyA->setBodyBox(bodyOrign, bodySize);
	}

	//enemyB
	enemyB = Enemy::create();
	enemyB->setRole(Sprite::create("enemy_rightwalk1.png"));
	enemyB->setPosition(Vec2(1454.0f, 199.0f));
	enemyB->setMoveEdge(1454.0f, 1750.0f);
	enemyB->setTag(Tag::ENEMYB);
	{
		auto* body = PhysicsBody::createBox(Size(28.0f, 38.0f), PhysicsMaterial(500.0f, 0.0f, 1.0f));
		body->setDynamic(true);
		body->setLinearDamping(0.0f);
		body->setGravityEnable(true);
		body->setContactTestBitmask(0x10);
		body->setCategoryBitmask(0x10);
		body->setCollisionBitmask(0x10);
		body->setRotationEnable(false);
		enemyB->setPhysicsBody(body);
	}
	map->addChild(enemyB);
	enemyB->setActionState(ActionState::WALK);
	enemyB->runRoleAction();
	//碰撞盒初始化
	{
		Point bodyOrign;
		bodyOrign.x = enemyB->getPositionX() - 14.0f;
		bodyOrign.y = enemyB->getPositionY() - 19.0f;
		Size bodySize;
		bodySize.width = 28.0f;
		bodySize.height = 38.0f;
		enemyB->setBodyBox(bodyOrign, bodySize);
	}

	//enemyC
	enemyC = Enemy::create();
	enemyC->setRole(Sprite::create("enemy_rightwalk1.png"));
	enemyC->setPosition(Vec2(878.0f, 1045.0f));
	enemyC->setMoveEdge(878.0f, 1426.0f);
	enemyC->setTag(Tag::ENEMYC);
	{
		auto* body = PhysicsBody::createBox(Size(28.0f, 38.0f), PhysicsMaterial(500.0f, 0.0f, 1.0f));
		body->setDynamic(true);
		body->setLinearDamping(0.0f);
		body->setGravityEnable(true);
		body->setContactTestBitmask(0x10);
		body->setCategoryBitmask(0x10);
		body->setCollisionBitmask(0x10);
		body->setRotationEnable(false);
		enemyC->setPhysicsBody(body);
	}
	map->addChild(enemyC);
	enemyC->setActionState(ActionState::WALK);
	enemyC->runRoleAction();
	//碰撞盒初始化
	{
		Point bodyOrign;
		bodyOrign.x = enemyC->getPositionX() - 14.0f;
		bodyOrign.y = enemyC->getPositionY() - 19.0f;
		Size bodySize;
		bodySize.width = 28.0f;
		bodySize.height = 38.0f;
		enemyC->setBodyBox(bodyOrign, bodySize);
	}

	//batA
	batA = Bat::create();
	batA->setRole(Sprite::create("bat_rightwalk1.png"));
	batA->setPosition(Vec2(360, 720));
	batA->setTag(Tag::BATA);
	{
		auto* body = PhysicsBody::createBox(Size(46.0f, 28.0f), PhysicsMaterial(500.0f, 0.0f, 1.0f));
		body->setDynamic(true);
		body->setLinearDamping(0.0f);
		body->setGravityEnable(false);
		body->setContactTestBitmask(0x02);
		body->setCategoryBitmask(0x02);
		body->setCollisionBitmask(0x02);
		body->setRotationEnable(false);
		batA->setPhysicsBody(body);
	}
	map->addChild(batA, 4);
	batA->runRoleAction();
	//碰撞盒与警觉区域初始化
	{
		Point bodyOrign;
		bodyOrign.x = batA->getPositionX() - 23.0f;
		bodyOrign.y = batA->getPositionY() - 14.0f;
		Size bodySize;
		bodySize.width = 46.0f;
		bodySize.height = 28.0f;
		batA->setBodyBox(bodyOrign, bodySize);

		Point alertOrign;
		alertOrign.x = batA->getPositionX() - 400.0f;
		alertOrign.y = batA->getPositionY() - 300.0f;
		Size alertSize;
		alertSize.width = 800.0f;
		alertSize.height = 600.0f;
		batA->setAlertBox(alertOrign, alertSize);
	}

	//batB
	batB = Bat::create();
	batB->setRole(Sprite::create("bat_rightwalk1.png"));
	batB->setPosition(Vec2(1692, 1080));
	batB->setTag(Tag::BATB);
	{
		auto* body = PhysicsBody::createBox(Size(46.0f, 28.0f), PhysicsMaterial(500.0f, 0.0f, 1.0f));
		body->setDynamic(true);
		body->setLinearDamping(0.0f);
		body->setGravityEnable(false);
		body->setContactTestBitmask(0x02);
		body->setCategoryBitmask(0x02);
		body->setCollisionBitmask(0x02);
		body->setRotationEnable(false);
		batB->setPhysicsBody(body);
	}
	map->addChild(batB, 4);
	batB->runRoleAction();
	//碰撞盒与警觉区域初始化
	{
		Point bodyOrign;
		bodyOrign.x = batB->getPositionX() - 23.0f;
		bodyOrign.y = batB->getPositionY() - 14.0f;
		Size bodySize;
		bodySize.width = 46.0f;
		bodySize.height = 28.0f;
		batB->setBodyBox(bodyOrign, bodySize);

		Point alertOrign;
		alertOrign.x = batB->getPositionX() - 400.0f;
		alertOrign.y = batB->getPositionY() - 300.0f;
		Size alertSize;
		alertSize.width = 800.0f;
		alertSize.height = 600.0f;
		batB->setAlertBox(alertOrign, alertSize);
	}

	//batC
	batC = Bat::create();
	batC->setRole(Sprite::create("bat_rightwalk1.png"));
	batC->setPosition(Vec2(108, 1296));
	batC->setTag(Tag::BATC);
	{
		auto* body = PhysicsBody::createBox(Size(46.0f, 28.0f), PhysicsMaterial(500.0f, 0.0f, 1.0f));
		body->setDynamic(true);
		body->setLinearDamping(0.0f);
		body->setGravityEnable(false);
		body->setContactTestBitmask(0x02);
		body->setCategoryBitmask(0x02);
		body->setCollisionBitmask(0x02);
		body->setRotationEnable(false);
		batC->setPhysicsBody(body);
	}
	map->addChild(batC, 4);
	batC->runRoleAction();
	//碰撞盒与警觉区域初始化
	{
		Point bodyOrign;
		bodyOrign.x = batC->getPositionX() - 23.0f;
		bodyOrign.y = batC->getPositionY() - 14.0f;
		Size bodySize;
		bodySize.width = 46.0f;
		bodySize.height = 28.0f;
		batC->setBodyBox(bodyOrign, bodySize);

		Point alertOrign;
		alertOrign.x = batC->getPositionX() - 400.0f;
		alertOrign.y = batC->getPositionY() - 300.0f;
		Size alertSize;
		alertSize.width = 800.0f;
		alertSize.height = 600.0f;
		batC->setAlertBox(alertOrign, alertSize);
	}
}

void GameSceneTwo::update(float dt)
{
	if (isPauseGame)
	{
		if (batA != NULL)
		{
			batA->getPhysicsBody()->setVelocity(Vec2(0, 0));
		}
		if (batB != NULL)
		{
			batB->getPhysicsBody()->setVelocity(Vec2(0, 0));
		}
		if (batC != NULL)
		{
			batC->getPhysicsBody()->setVelocity(Vec2(0, 0));
		}
	}
	else if (!isPauseGame)
	{
		//更新速度、状态等
		heroUpdate();
		enemiesUpdate();
		coinsUpdate();
		mapUpdate();
	}
}

void GameSceneTwo::heroUpdate()
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
		//enemyA
		if (enemyA != NULL&&enemyA->getActionState() < ActionState::HURT)
		{
			if (collisionDetection(hero->getHitBox(), enemyA->getBodyBox()))
			{
				enemyA->setActionState(ActionState::HURT);
				enemyA->runRoleAction();
			}
		}
		//enemyB
		if (enemyB != NULL&&enemyB->getActionState() < ActionState::HURT)
		{
			if (collisionDetection(hero->getHitBox(), enemyB->getBodyBox()))
			{
				enemyB->setActionState(ActionState::HURT);
				enemyB->runRoleAction();
			}
		}
		//enemyC
		if (enemyC != NULL&&enemyC->getActionState() < ActionState::HURT)
		{
			if (collisionDetection(hero->getHitBox(), enemyC->getBodyBox()))
			{
				enemyC->setActionState(ActionState::HURT);
				enemyC->runRoleAction();
			}
		}

		//batA
		if (batA != NULL&&batA->getActionState() < ActionState::HURT)
		{
			if (collisionDetection(hero->getHitBox(), batA->getBodyBox()))
			{
				batA->setActionState(ActionState::HURT);
				batA->runRoleAction();
			}
		}
		//batB
		if (batB != NULL&&batB->getActionState() < ActionState::HURT)
		{
			if (collisionDetection(hero->getHitBox(), batB->getBodyBox()))
			{
				batB->setActionState(ActionState::HURT);
				batB->runRoleAction();
			}
		}
		//batC
		if (batC != NULL&&batC->getActionState() < ActionState::HURT)
		{
			if (collisionDetection(hero->getHitBox(), batC->getBodyBox()))
			{
				batC->setActionState(ActionState::HURT);
				batC->runRoleAction();
			}
		}
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

void GameSceneTwo::enemiesUpdate()
{
	//enemyA
	if (enemyA != NULL)
	{
		if (enemyA->getActionState() == ActionState::WALK)
		{
			//enemyA变更速度
			if (enemyA->getDirection() == Direction::RIGHT)
			{
				Vec2 temp = enemyA->getPhysicsBody()->getVelocity();
				temp.x = enemyA->getVelX();
				enemyA->getPhysicsBody()->setVelocity(temp);
			}
			else
			{
				Vec2 temp = enemyA->getPhysicsBody()->getVelocity();
				temp.x = -enemyA->getVelX();
				enemyA->getPhysicsBody()->setVelocity(temp);
			}

			//改变enemy方向
			if (enemyA->getHP() > 0 && enemyA->getPositionX() + enemyA->getContentSize().width / 2 >= enemyA->getMoveEdge().rightX)
			{
				enemyA->setDirection(Direction::LEFT);
				enemyA->runRoleAction();
			}
			else if (enemyA->getHP() > 0 && enemyA->getPositionX() - enemyA->getContentSize().width / 2 <= enemyA->getMoveEdge().leftX)
			{
				enemyA->setDirection(Direction::RIGHT);
				enemyA->runRoleAction();
			}
		}

		//enemy碰撞hero
		if (enemyA->getHP() > 0 && collisionDetection(enemyA->getBodyBox(), hero->getBodyBox()) && hero->getActionState() < ActionState::HURT)
		{
			if (hero->invincibilityDuration < 0)
			{
				hero->runHurtAction();
			}
		}

		//碰撞盒更新
		Point bodyOrign;
		bodyOrign.x = enemyA->getPositionX() - 14.0f;
		bodyOrign.y = enemyA->getPositionY() - 29.0f;
		Size bodySize;
		bodySize.width = 18.0f;
		bodySize.height = 38.0f;
		enemyA->setBodyBox(bodyOrign, bodySize);

		//死亡判断
		if (enemyA->getActionState() == ActionState::REMOVE)
		{
			//生成coin
			for (int i = 0; i < 5; i++)
			{
				auto* tempCoin = Coin::create();
				tempCoin->setRole(Sprite::create("coin_idle1.png"));
				tempCoin->setPosition(enemyA->getPosition());
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
			map->removeChild(enemyA);
			enemyA = NULL;
		}
	}
	//enemyB
	if (enemyB != NULL)
	{
		if (enemyB->getActionState() == ActionState::WALK)
		{
			//变更速度
			if (enemyB->getDirection() == Direction::RIGHT)
			{
				Vec2 temp = enemyB->getPhysicsBody()->getVelocity();
				temp.x = enemyB->getVelX();
				enemyB->getPhysicsBody()->setVelocity(temp);
			}
			else
			{
				Vec2 temp = enemyB->getPhysicsBody()->getVelocity();
				temp.x = -enemyB->getVelX();
				enemyB->getPhysicsBody()->setVelocity(temp);
			}

			//改变enemy方向
			if (enemyB->getHP() > 0 && enemyB->getPositionX() + enemyB->getContentSize().width / 2 >= enemyB->getMoveEdge().rightX)
			{
				enemyB->setDirection(Direction::LEFT);
				enemyB->runRoleAction();
			}
			else if (enemyB->getHP() > 0 && enemyB->getPositionX() - enemyB->getContentSize().width / 2 <= enemyB->getMoveEdge().leftX)
			{
				enemyB->setDirection(Direction::RIGHT);
				enemyB->runRoleAction();
			}
		}

		//enemy碰撞hero
		if (enemyB->getHP() > 0 && collisionDetection(enemyB->getBodyBox(), hero->getBodyBox()) && hero->getActionState() < ActionState::HURT)
		{
			if (hero->invincibilityDuration < 0)
			{
				hero->runHurtAction();
			}
		}

		//碰撞盒更新
		Point bodyOrign;
		bodyOrign.x = enemyB->getPositionX() - 14.0f;
		bodyOrign.y = enemyB->getPositionY() - 29.0f;
		Size bodySize;
		bodySize.width = 18.0f;
		bodySize.height = 38.0f;
		enemyB->setBodyBox(bodyOrign, bodySize);

		//死亡判断
		if (enemyB->getActionState() == ActionState::REMOVE)
		{
			//生成coin
			for (int i = 0; i < 5; i++)
			{
				auto* tempCoin = Coin::create();
				tempCoin->setRole(Sprite::create("coin_idle1.png"));
				tempCoin->setPosition(enemyB->getPosition());
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
			map->removeChild(enemyB);
			enemyB = NULL;
		}
	}
	//enemyC
	if (enemyC != NULL)
	{
		if (enemyC->getActionState() == ActionState::WALK)
		{
			//变更速度
			if (enemyC->getDirection() == Direction::RIGHT)
			{
				Vec2 temp = enemyC->getPhysicsBody()->getVelocity();
				temp.x = enemyC->getVelX();
				enemyC->getPhysicsBody()->setVelocity(temp);
			}
			else
			{
				Vec2 temp = enemyC->getPhysicsBody()->getVelocity();
				temp.x = -enemyC->getVelX();
				enemyC->getPhysicsBody()->setVelocity(temp);
			}

			//改变enemy方向
			if (enemyC->getHP() > 0 && enemyC->getPositionX() + enemyC->getContentSize().width / 2 >= enemyC->getMoveEdge().rightX)
			{
				enemyC->setDirection(Direction::LEFT);
				enemyC->runRoleAction();
			}
			else if (enemyC->getHP() > 0 && enemyC->getPositionX() - enemyC->getContentSize().width / 2 <= enemyC->getMoveEdge().leftX)
			{
				enemyC->setDirection(Direction::RIGHT);
				enemyC->runRoleAction();
			}
		}

		//enemy碰撞hero
		if (enemyC->getHP() > 0 && collisionDetection(enemyC->getBodyBox(), hero->getBodyBox()) && hero->getActionState() < ActionState::HURT)
		{
			if (hero->invincibilityDuration < 0)
			{
				hero->runHurtAction();
			}
		}

		//碰撞盒更新
		Point bodyOrign;
		bodyOrign.x = enemyC->getPositionX() - 14.0f;
		bodyOrign.y = enemyC->getPositionY() - 29.0f;
		Size bodySize;
		bodySize.width = 18.0f;
		bodySize.height = 38.0f;
		enemyC->setBodyBox(bodyOrign, bodySize);

		//死亡判断
		if (enemyC->getActionState() == ActionState::REMOVE)
		{
			//生成coin
			for (int i = 0; i < 5; i++)
			{
				auto* tempCoin = Coin::create();
				tempCoin->setRole(Sprite::create("coin_idle1.png"));
				tempCoin->setPosition(enemyC->getPosition());
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
			map->removeChild(enemyC);
			enemyC = NULL;
		}
	}

	//batA
	if (batA != NULL)
	{
		//碰撞盒与警觉区域更新
		{
			Point bodyOrign;
			bodyOrign.x = batA->getPositionX() - 23.0f;
			bodyOrign.y = batA->getPositionY() - 14.0f;
			Size bodySize;
			bodySize.width = 46.0f;
			bodySize.height = 28.0f;
			batA->setBodyBox(bodyOrign, bodySize);

			Point alertOrign;
			alertOrign.x = batA->getPositionX() - 400.0f;
			alertOrign.y = batA->getPositionY() - 300.0f;
			Size alertSize;
			alertSize.width = 800.0f;
			alertSize.height = 600.0f;
			batA->setAlertBox(alertOrign, alertSize);
		}

		//batA碰撞hero
		if (batA->getHP() > 0 && collisionDetection(batA->getBodyBox(), hero->getBodyBox()) && hero->getActionState() < ActionState::HURT)
		{
			if (hero->invincibilityDuration < 0)
			{
				hero->runHurtAction();
			}
		}

		//根据状态执行行为
		switch (batA->getActionState())
		{
		case ActionState::WALK:
			//判断是否在警觉区域内
			if (collisionDetection(hero->getBodyBox(), batA->getAlertBox()))
			{   //变更X方向速度
				if (hero->getPositionX() - batA->getPositionX() > 0 && batA->getVelX() < 0)
				{
					batA->setDirection(Direction::RIGHT);
					batA->runRoleAction();
					batA->setVelX(-batA->getVelX());
				}
				else if (hero->getPositionX() - batA->getPositionX() < 0 && batA->getVelX() > 0)
				{
					batA->setDirection(Direction::LEFT);
					batA->runRoleAction();
					batA->setVelX(-batA->getVelX());
				}
				//变更Y方向速度
				if (hero->getPositionY() - batA->getPositionY() > 0 && batA->getVelY() < 0)
				{
					batA->setVelY(-batA->getVelY());
				}
				else if (hero->getPositionY() - batA->getPositionY() < 0 && batA->getVelY() > 0)
				{
					batA->setVelY(-batA->getVelY());
				}

				//更新位置
				if (hero->getBodyBox().containsPoint(batA->getPosition()))
				{
					batA->getPhysicsBody()->setVelocity(Vec2(0, 0));
				}
				else if (hero->getPositionX() - 5.0f < batA->getPositionX() && hero->getPositionX() + 5.0f > batA->getPositionX())
				{
					batA->getPhysicsBody()->setVelocity(Vec2(0, batA->getVelY()));
				}
				else if (hero->getPositionY() - 5.0f < batA->getPositionY() && hero->getPositionY() + 5.0f > batA->getPositionY())
				{
					batA->getPhysicsBody()->setVelocity(Vec2(batA->getVelX(), 0));
				}
				else
				{
					batA->getPhysicsBody()->setVelocity(Vec2(batA->getVelX(), batA->getVelY()));
				}
			}
			else
			{
				batA->getPhysicsBody()->setVelocity(Vec2(0, 0));
			}

			break;

		case ActionState::HURT:
			batA->getPhysicsBody()->setVelocity(Vec2(0, 0));
			break;

		case ActionState::DIE:
			batA->getPhysicsBody()->setVelocity(Vec2(0, 0));
			break;

		case ActionState::REMOVE:
			//生成coin
			for (int i = 0; i < 6; i++)
			{
				auto* tempCoin = Coin::create();
				tempCoin->setRole(Sprite::create("coin_idle1.png"));
				tempCoin->setPosition(batA->getPosition());
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
			map->removeChild(batA);
			batA = NULL;
			break;

		default:
			CCLOG("error:Action\n");
			break;
		}
	}

	//batB
	if (batB != NULL)
	{
		//碰撞盒与警觉区域更新
		{
			Point bodyOrign;
			bodyOrign.x = batB->getPositionX() - 23.0f;
			bodyOrign.y = batB->getPositionY() - 14.0f;
			Size bodySize;
			bodySize.width = 46.0f;
			bodySize.height = 28.0f;
			batB->setBodyBox(bodyOrign, bodySize);

			Point alertOrign;
			alertOrign.x = batB->getPositionX() - 400.0f;
			alertOrign.y = batB->getPositionY() - 300.0f;
			Size alertSize;
			alertSize.width = 800.0f;
			alertSize.height = 600.0f;
			batB->setAlertBox(alertOrign, alertSize);
		}

		//batA碰撞hero
		if (batB->getHP() > 0 && collisionDetection(batB->getBodyBox(), hero->getBodyBox()) && hero->getActionState() < ActionState::HURT)
		{
			if (hero->invincibilityDuration < 0)
			{
				hero->runHurtAction();
			}
		}

		//根据状态执行行为
		switch (batB->getActionState())
		{
		case ActionState::WALK:
			//判断是否在警觉区域内
			if (collisionDetection(hero->getBodyBox(), batB->getAlertBox()))
			{   //变更X方向速度
				if (hero->getPositionX() - batB->getPositionX() > 0 && batB->getVelX() < 0)
				{
					batB->setDirection(Direction::RIGHT);
					batB->runRoleAction();
					batB->setVelX(-batB->getVelX());
				}
				else if (hero->getPositionX() - batB->getPositionX() < 0 && batB->getVelX() > 0)
				{
					batB->setDirection(Direction::LEFT);
					batB->runRoleAction();
					batB->setVelX(-batB->getVelX());
				}
				//变更Y方向速度
				if (hero->getPositionY() - batB->getPositionY() > 0 && batB->getVelY() < 0)
				{
					batB->setVelY(-batB->getVelY());
				}
				else if (hero->getPositionY() - batB->getPositionY() < 0 && batB->getVelY() > 0)
				{
					batB->setVelY(-batB->getVelY());
				}

				//更新位置
				if (hero->getBodyBox().containsPoint(batB->getPosition()))
				{
					batB->getPhysicsBody()->setVelocity(Vec2(0, 0));
				}
				else if (hero->getPositionX() - 5.0f < batB->getPositionX() && hero->getPositionX() + 5.0f > batB->getPositionX())
				{
					batB->getPhysicsBody()->setVelocity(Vec2(0, batB->getVelY()));
				}
				else if (hero->getPositionY() - 5.0f < batB->getPositionY() && hero->getPositionY() + 5.0f > batB->getPositionY())
				{
					batB->getPhysicsBody()->setVelocity(Vec2(batB->getVelX(), 0));
				}
				else
				{
					batB->getPhysicsBody()->setVelocity(Vec2(batB->getVelX(), batB->getVelY()));
				}
			}
			else
			{
				batB->getPhysicsBody()->setVelocity(Vec2(0, 0));
			}

			break;

		case ActionState::HURT:
			batB->getPhysicsBody()->setVelocity(Vec2(0, 0));
			break;

		case ActionState::DIE:
			batB->getPhysicsBody()->setVelocity(Vec2(0, 0));
			break;

		case ActionState::REMOVE:
			//生成coin
			for (int i = 0; i < 6; i++)
			{
				auto* tempCoin = Coin::create();
				tempCoin->setRole(Sprite::create("coin_idle1.png"));
				tempCoin->setPosition(batB->getPosition());
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
			map->removeChild(batB);
			batB = NULL;
			break;

		default:
			CCLOG("error:Action\n");
			break;
		}
	}

	//batC
	if (batC != NULL)
	{
		//碰撞盒与警觉区域更新
		{
			Point bodyOrign;
			bodyOrign.x = batC->getPositionX() - 23.0f;
			bodyOrign.y = batC->getPositionY() - 14.0f;
			Size bodySize;
			bodySize.width = 46.0f;
			bodySize.height = 28.0f;
			batC->setBodyBox(bodyOrign, bodySize);

			Point alertOrign;
			alertOrign.x = batC->getPositionX() - 400.0f;
			alertOrign.y = batC->getPositionY() - 300.0f;
			Size alertSize;
			alertSize.width = 800.0f;
			alertSize.height = 600.0f;
			batC->setAlertBox(alertOrign, alertSize);
		}

		//batA碰撞hero
		if (batC->getHP() > 0 && collisionDetection(batC->getBodyBox(), hero->getBodyBox()) && hero->getActionState() < ActionState::HURT)
		{
			if (hero->invincibilityDuration < 0)
			{
				hero->runHurtAction();
			}
		}

		//根据状态执行行为
		switch (batC->getActionState())
		{
		case ActionState::WALK:
			//判断是否在警觉区域内
			if (collisionDetection(hero->getBodyBox(), batC->getAlertBox()))
			{   //变更X方向速度
				if (hero->getPositionX() - batC->getPositionX() > 0 && batC->getVelX() < 0)
				{
					batC->setDirection(Direction::RIGHT);
					batC->runRoleAction();
					batC->setVelX(-batC->getVelX());
				}
				else if (hero->getPositionX() - batC->getPositionX() < 0 && batC->getVelX() > 0)
				{
					batC->setDirection(Direction::LEFT);
					batC->runRoleAction();
					batC->setVelX(-batC->getVelX());
				}
				//变更Y方向速度
				if (hero->getPositionY() - batC->getPositionY() > 0 && batC->getVelY() < 0)
				{
					batC->setVelY(-batC->getVelY());
				}
				else if (hero->getPositionY() - batC->getPositionY() < 0 && batC->getVelY() > 0)
				{
					batC->setVelY(-batC->getVelY());
				}

				//更新位置
				if (hero->getBodyBox().containsPoint(batC->getPosition()))
				{
					batC->getPhysicsBody()->setVelocity(Vec2(0, 0));
				}
				else if (hero->getPositionX() - 5.0f < batC->getPositionX() && hero->getPositionX() + 5.0f > batC->getPositionX())
				{
					batC->getPhysicsBody()->setVelocity(Vec2(0, batC->getVelY()));
				}
				else if (hero->getPositionY() - 5.0f < batC->getPositionY() && hero->getPositionY() + 5.0f > batC->getPositionY())
				{
					batC->getPhysicsBody()->setVelocity(Vec2(batC->getVelX(), 0));
				}
				else
				{
					batC->getPhysicsBody()->setVelocity(Vec2(batC->getVelX(), batC->getVelY()));
				}
			}
			else
			{
				batC->getPhysicsBody()->setVelocity(Vec2(0, 0));
			}

			break;

		case ActionState::HURT:
			batC->getPhysicsBody()->setVelocity(Vec2(0, 0));
			break;

		case ActionState::DIE:
			batC->getPhysicsBody()->setVelocity(Vec2(0, 0));
			break;

		case ActionState::REMOVE:
			//生成coin
			for (int i = 0; i < 6; i++)
			{
				auto* tempCoin = Coin::create();
				tempCoin->setRole(Sprite::create("coin_idle1.png"));
				tempCoin->setPosition(batC->getPosition());
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
			map->removeChild(batC);
			batC = NULL;
			break;

		default:
			CCLOG("error:Action\n");
			break;
		}
	}
}

void GameSceneTwo::coinsUpdate()
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

void GameSceneTwo::mapUpdate()
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
		platform7->getPhysicsBody()->setCategoryBitmask(0xFFFFFFF0);
		platform7->getPhysicsBody()->setCollisionBitmask(0xFFFFFFF0);
		platform8->getPhysicsBody()->setCategoryBitmask(0xFFFFFFF0);
		platform8->getPhysicsBody()->setCollisionBitmask(0xFFFFFFF0);
		platform9->getPhysicsBody()->setCategoryBitmask(0xFFFFFFF0);
		platform9->getPhysicsBody()->setCollisionBitmask(0xFFFFFFF0);
		platform10->getPhysicsBody()->setCategoryBitmask(0xFFFFFFF0);
		platform10->getPhysicsBody()->setCollisionBitmask(0xFFFFFFF0);
		platform11->getPhysicsBody()->setCategoryBitmask(0xFFFFFFF0);
		platform11->getPhysicsBody()->setCollisionBitmask(0xFFFFFFF0);
		platform12->getPhysicsBody()->setCategoryBitmask(0xFFFFFFF0);
		platform12->getPhysicsBody()->setCollisionBitmask(0xFFFFFFF0);
		platform13->getPhysicsBody()->setCategoryBitmask(0xFFFFFFF0);
		platform13->getPhysicsBody()->setCollisionBitmask(0xFFFFFFF0);
		platform14->getPhysicsBody()->setCategoryBitmask(0xFFFFFFF0);
		platform14->getPhysicsBody()->setCollisionBitmask(0xFFFFFFF0);
		platform15->getPhysicsBody()->setCategoryBitmask(0xFFFFFFF0);
		platform15->getPhysicsBody()->setCollisionBitmask(0xFFFFFFF0);
		platform16->getPhysicsBody()->setCategoryBitmask(0xFFFFFFF0);
		platform16->getPhysicsBody()->setCollisionBitmask(0xFFFFFFF0);
		platform17->getPhysicsBody()->setCategoryBitmask(0xFFFFFFF0);
		platform17->getPhysicsBody()->setCollisionBitmask(0xFFFFFFF0);
		platform18->getPhysicsBody()->setCategoryBitmask(0xFFFFFFF0);
		platform18->getPhysicsBody()->setCollisionBitmask(0xFFFFFFF0);
	}
	else if (hero->getPhysicsBody()->getVelocity().y < 0)
	{
		if (platform1->getPhysicsBody()->getCategoryBitmask() == 0xFFFFFFF0 && hero->getBodyBox().origin.y > platformRect1.origin.y + platformRect1.size.height)
		{
			platform1->getPhysicsBody()->setCategoryBitmask(0xFFFFFFF1);
			platform1->getPhysicsBody()->setCollisionBitmask(0xFFFFFFF1);
		}
		if (platform2->getPhysicsBody()->getCategoryBitmask() == 0xFFFFFFF0 && hero->getBodyBox().origin.y > platformRect2.origin.y + platformRect2.size.height)
		{
			platform2->getPhysicsBody()->setCategoryBitmask(0xFFFFFFF1);
			platform2->getPhysicsBody()->setCollisionBitmask(0xFFFFFFF1);
		}
		if (platform3->getPhysicsBody()->getCategoryBitmask() == 0xFFFFFFF0 && hero->getBodyBox().origin.y > platformRect3.origin.y + platformRect3.size.height)
		{
			platform3->getPhysicsBody()->setCategoryBitmask(0xFFFFFFF1);
			platform3->getPhysicsBody()->setCollisionBitmask(0xFFFFFFF1);
		}
		if (platform4->getPhysicsBody()->getCategoryBitmask() == 0xFFFFFFF0 && hero->getBodyBox().origin.y > platformRect4.origin.y + platformRect4.size.height)
		{
			platform4->getPhysicsBody()->setCategoryBitmask(0xFFFFFFF1);
			platform4->getPhysicsBody()->setCollisionBitmask(0xFFFFFFF1);
		}
		if (platform5->getPhysicsBody()->getCategoryBitmask() == 0xFFFFFFF0 && hero->getBodyBox().origin.y > platformRect5.origin.y + platformRect5.size.height)
		{
			platform5->getPhysicsBody()->setCategoryBitmask(0xFFFFFFF1);
			platform5->getPhysicsBody()->setCollisionBitmask(0xFFFFFFF1);
		}
		if (platform6->getPhysicsBody()->getCategoryBitmask() == 0xFFFFFFF0 && hero->getBodyBox().origin.y > platformRect6.origin.y + platformRect6.size.height)
		{
			platform6->getPhysicsBody()->setCategoryBitmask(0xFFFFFFF1);
			platform6->getPhysicsBody()->setCollisionBitmask(0xFFFFFFF1);
		}
		if (platform7->getPhysicsBody()->getCategoryBitmask() == 0xFFFFFFF0 && hero->getBodyBox().origin.y > platformRect7.origin.y + platformRect7.size.height)
		{
			platform7->getPhysicsBody()->setCategoryBitmask(0xFFFFFFF1);
			platform7->getPhysicsBody()->setCollisionBitmask(0xFFFFFFF1);
		}
		if (platform8->getPhysicsBody()->getCategoryBitmask() == 0xFFFFFFF0 && hero->getBodyBox().origin.y > platformRect8.origin.y + platformRect8.size.height)
		{
			platform8->getPhysicsBody()->setCategoryBitmask(0xFFFFFFF1);
			platform8->getPhysicsBody()->setCollisionBitmask(0xFFFFFFF1);
		}
		if (platform9->getPhysicsBody()->getCategoryBitmask() == 0xFFFFFFF0 && hero->getBodyBox().origin.y > platformRect9.origin.y + platformRect9.size.height)
		{
			platform9->getPhysicsBody()->setCategoryBitmask(0xFFFFFFF1);
			platform9->getPhysicsBody()->setCollisionBitmask(0xFFFFFFF1);
		}
		if (platform10->getPhysicsBody()->getCategoryBitmask() == 0xFFFFFFF0 && hero->getBodyBox().origin.y > platformRect10.origin.y + platformRect10.size.height)
		{
			platform10->getPhysicsBody()->setCategoryBitmask(0xFFFFFFF1);
			platform10->getPhysicsBody()->setCollisionBitmask(0xFFFFFFF1);
		}
		if (platform11->getPhysicsBody()->getCategoryBitmask() == 0xFFFFFFF0 && hero->getBodyBox().origin.y > platformRect11.origin.y + platformRect11.size.height)
		{
			platform11->getPhysicsBody()->setCategoryBitmask(0xFFFFFFF1);
			platform11->getPhysicsBody()->setCollisionBitmask(0xFFFFFFF1);
		}
		if (platform12->getPhysicsBody()->getCategoryBitmask() == 0xFFFFFFF0 && hero->getBodyBox().origin.y > platformRect12.origin.y + platformRect12.size.height)
		{
			platform12->getPhysicsBody()->setCategoryBitmask(0xFFFFFFF1);
			platform12->getPhysicsBody()->setCollisionBitmask(0xFFFFFFF1);
		}
		if (platform13->getPhysicsBody()->getCategoryBitmask() == 0xFFFFFFF0 && hero->getBodyBox().origin.y > platformRect13.origin.y + platformRect13.size.height)
		{
			platform13->getPhysicsBody()->setCategoryBitmask(0xFFFFFFF1);
			platform13->getPhysicsBody()->setCollisionBitmask(0xFFFFFFF1);
		}
		if (platform14->getPhysicsBody()->getCategoryBitmask() == 0xFFFFFFF0 && hero->getBodyBox().origin.y > platformRect14.origin.y + platformRect14.size.height)
		{
			platform14->getPhysicsBody()->setCategoryBitmask(0xFFFFFFF1);
			platform14->getPhysicsBody()->setCollisionBitmask(0xFFFFFFF1);
		}
		if (platform15->getPhysicsBody()->getCategoryBitmask() == 0xFFFFFFF0 && hero->getBodyBox().origin.y > platformRect15.origin.y + platformRect15.size.height)
		{
			platform15->getPhysicsBody()->setCategoryBitmask(0xFFFFFFF1);
			platform15->getPhysicsBody()->setCollisionBitmask(0xFFFFFFF1);
		}
		if (platform16->getPhysicsBody()->getCategoryBitmask() == 0xFFFFFFF0 && hero->getBodyBox().origin.y > platformRect16.origin.y + platformRect16.size.height)
		{
			platform16->getPhysicsBody()->setCategoryBitmask(0xFFFFFFF1);
			platform16->getPhysicsBody()->setCollisionBitmask(0xFFFFFFF1);
		}
		if (platform17->getPhysicsBody()->getCategoryBitmask() == 0xFFFFFFF0 && hero->getBodyBox().origin.y > platformRect17.origin.y + platformRect17.size.height)
		{
			platform17->getPhysicsBody()->setCategoryBitmask(0xFFFFFFF1);
			platform17->getPhysicsBody()->setCollisionBitmask(0xFFFFFFF1);
		}
		if (platform18->getPhysicsBody()->getCategoryBitmask() == 0xFFFFFFF0 && hero->getBodyBox().origin.y > platformRect18.origin.y + platformRect18.size.height)
		{
			platform18->getPhysicsBody()->setCategoryBitmask(0xFFFFFFF1);
			platform18->getPhysicsBody()->setCollisionBitmask(0xFFFFFFF1);
		}
	}

	//door
	if (collisionDetection(hero->getBodyBox(), doorRect) && hero->getActionState() == ActionState::ATTACK)
	{
		isPauseGame = true;
		batA = batB = batC = NULL;
		auto* rotate = RotateBy::create(1.0f, Vec3(0, 0, 1080.0f));
		auto* scale = ScaleBy::create(1.0f, 0.2f);
		auto* action = Spawn::create(rotate, scale, NULL);
		auto* callFunc = CallFunc::create(CC_CALLBACK_0(GameSceneTwo::enterNextLevel, this));
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

void GameSceneTwo::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event * event)
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
}

void GameSceneTwo::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event * event)
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

void GameSceneTwo::onLeft(cocos2d::Ref * pSender, cocos2d::ui::Widget::TouchEventType type)
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

void GameSceneTwo::onRight(cocos2d::Ref * pSender, cocos2d::ui::Widget::TouchEventType type)
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

void GameSceneTwo::onJump(cocos2d::Ref * pSender, cocos2d::ui::Widget::TouchEventType type)
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

void GameSceneTwo::onAttack(cocos2d::Ref * pSender, cocos2d::ui::Widget::TouchEventType type)
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

bool GameSceneTwo::onContactBegin(cocos2d::PhysicsContact & contact)
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

	//batA与ground碰撞
	if (batA != NULL)
	{
		if ((nodeA->getTag() == Tag::GROUND && nodeB->getTag() == Tag::BATA) || (nodeA->getTag() == Tag::BATA && nodeB->getTag() == Tag::GROUND))
		{
			auto contactData = contact.getContactData();

			//侧面碰撞
			if (contactData->normal.y == 0)
			{
				batA->setVelX(1);
			}
			//水平面碰撞
			if (contactData->normal.x == 0)
			{
				batA->setVelY(1);
			}
		}
	}
	//batB与ground碰撞
	if (batB != NULL)
	{
		if ((nodeA->getTag() == Tag::GROUND && nodeB->getTag() == Tag::BATB) || (nodeA->getTag() == Tag::BATB && nodeB->getTag() == Tag::GROUND))
		{
			auto contactData = contact.getContactData();

			//侧面碰撞
			if (contactData->normal.y == 0)
			{
				batB->setVelX(1);
			}
			//水平面碰撞
			if (contactData->normal.x == 0)
			{
				batB->setVelY(1);
			}
		}
	}
	//batC与ground碰撞
	if (batC != NULL)
	{
		if ((nodeA->getTag() == Tag::GROUND && nodeB->getTag() == Tag::BATC) || (nodeA->getTag() == Tag::BATC && nodeB->getTag() == Tag::GROUND))
		{
			auto contactData = contact.getContactData();

			//侧面碰撞
			if (contactData->normal.y == 0)
			{
				batC->setVelX(1);
			}
			//水平面碰撞
			if (contactData->normal.x == 0)
			{
				batC->setVelY(1);
			}
		}
	}

	return true;
}

void GameSceneTwo::onContactSeperate(cocos2d::PhysicsContact & contact)
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
	//batA与ground分离
	if (batA != NULL)
	{
		if ((nodeA->getTag() == Tag::GROUND && nodeB->getTag() == Tag::BATA) || (nodeA->getTag() == Tag::BATA && nodeB->getTag() == Tag::GROUND))
		{
			auto contactData = contact.getContactData();

			//侧面分离
			if (contactData->normal.x != 0)
				batA->setVelX(120);
			//水平面分离
			if (contactData->normal.y != 0)
			{
				batA->setVelY(120);
			}
		}
	}
	//batB与ground分离
	if (batB != NULL)
	{
		if ((nodeA->getTag() == Tag::GROUND && nodeB->getTag() == Tag::BATB) || (nodeA->getTag() == Tag::BATB && nodeB->getTag() == Tag::GROUND))
		{
			auto contactData = contact.getContactData();

			//侧面分离
			if (contactData->normal.x != 0)
				batB->setVelX(120);
			//水平面分离
			if (contactData->normal.y != 0)
			{
				batB->setVelY(120);
			}
		}
	}
	//batC与ground分离
	if (batC != NULL)
	{
		if ((nodeA->getTag() == Tag::GROUND && nodeB->getTag() == Tag::BATC) || (nodeA->getTag() == Tag::BATC && nodeB->getTag() == Tag::GROUND))
		{
			auto contactData = contact.getContactData();

			//侧面分离
			if (contactData->normal.x != 0)
				batC->setVelX(120);
			//水平面分离
			if (contactData->normal.y != 0)
			{
				batC->setVelY(120);
			}
		}
	}
}

bool GameSceneTwo::collisionDetection(cocos2d::Rect hitBox, cocos2d::Rect bodyBox)
{
	if (hitBox.intersectsRect(bodyBox))
		return true;
	else
		return false;
}

void GameSceneTwo::pauseGame()
{
	if (!isPauseGame)
	{
		isPauseGame = true;

		pauseBG = LayerColor::create(Color4B(0, 0, 0, 200));
		this->addChild(pauseBG);

		resumeItem = MenuItemImage::create("resume1.png", "resume1.png", CC_CALLBACK_0(GameSceneTwo::resumeGame, this));
		resumeItem->setPosition(Vec2(360, 180));
		backItem = MenuItemImage::create("back1.png", "back1.png", CC_CALLBACK_0(GameSceneTwo::back, this));
		backItem->setPosition(Vec2(280, 180));
		pauseMenu = Menu::create(resumeItem, backItem, NULL);
		pauseMenu->setPosition(Vec2::ZERO);
		this->addChild(pauseMenu);
	}
}

void GameSceneTwo::resumeGame()
{
	if (isPauseGame)
	{
		isPauseGame = false;

		this->removeChild(pauseBG);
		this->removeChild(pauseMenu);
	}
}

void GameSceneTwo::back()
{
	if (isPauseGame)
	{
		isPauseGame = false;

		auto selectScene = SelectScene::createScene();
		Director::getInstance()->replaceScene(TransitionFade::create(1.0f, selectScene));
	}
}

void GameSceneTwo::enterNextLevel()
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

	auto gameScene = BossScene::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(1.0f, gameScene));
}
