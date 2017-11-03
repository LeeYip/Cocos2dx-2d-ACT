#include "BossScene.h"

USING_NS_CC;
using namespace ui;

cocos2d::Scene * BossScene::createScene()
{
	//创建带物理引擎的scene
	Scene* scene = Scene::createWithPhysics();

	//调试
	//scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

	//设置重力加速度
	scene->getPhysicsWorld()->setGravity(Vec2(0.0f, -900.0f));

	auto layer = BossScene::create();
	scene->addChild(layer);

	return scene;
}

bool BossScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	//更新解锁的关卡
	if (UserDefault::getInstance()->getIntegerForKey("level") < 3)
		UserDefault::getInstance()->setIntegerForKey("level", 3);

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
	map = TMXTiledMap::create("mapboss.tmx");
	this->addChild(map);
	map->setPosition(Vec2(0, 180));

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
	
	//Roles
	heroInit();
	bossInit();

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
	pauseItem = MenuItemImage::create("pause1.png", "pause1.png", CC_CALLBACK_0(BossScene::pauseGame, this));
	pauseItem->setPosition(Vec2(620, 340));
	auto* menu = Menu::create(pauseItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu);

	//虚拟按键
	left = ui::Button::create("left1.png", "left2.png");
	left->setPosition(Vec2(70, 40));
	left->addTouchEventListener(ui::Widget::ccWidgetTouchCallback(CC_CALLBACK_2(BossScene::onLeft, this)));
	this->addChild(left);
	right = ui::Button::create("right1.png", "right2.png");
	right->setPosition(Vec2(180, 40));
	right->addTouchEventListener(ui::Widget::ccWidgetTouchCallback(CC_CALLBACK_2(BossScene::onRight, this)));
	this->addChild(right);
	jump = ui::Button::create("jump1.png", "jump2.png");
	jump->setPosition(Vec2(600, 40));
	jump->addTouchEventListener(ui::Widget::ccWidgetTouchCallback(CC_CALLBACK_2(BossScene::onJump, this)));
	this->addChild(jump);
	attack = ui::Button::create("attack1.png", "attack2.png");
	attack->setPosition(Vec2(520, 40));
	attack->addTouchEventListener(ui::Widget::ccWidgetTouchCallback(CC_CALLBACK_2(BossScene::onAttack, this)));
	this->addChild(attack);

	isLeft = false;
	isRight = false;
	isJump = false;
	isAttack = false;

	//键盘监听
	auto keyListener = EventListenerKeyboard::create();
	keyListener->onKeyPressed = CC_CALLBACK_2(BossScene::onKeyPressed, this);
	keyListener->onKeyReleased = CC_CALLBACK_2(BossScene::onKeyReleased, this);
	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(keyListener, this);

	//碰撞监听
	EventListenerPhysicsContact* contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(BossScene::onContactBegin, this);
	contactListener->onContactSeparate = CC_CALLBACK_1(BossScene::onContactSeperate, this);
	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);

	return true;
}

void BossScene::heroInit()
{
	hero = Hero::create();
	hero->setRole(Sprite::create("hero_rightidle1.png"));
	hero->setPosition(Vec2(54.0f, 383.0f));
	hero->setTag(Tag::HERO);

	auto* body = PhysicsBody::createBox(Size(32.0f, 46.0f), PhysicsMaterial(500.0f, 0.0f, 1.0f));
	body->setDynamic(true);
	body->setLinearDamping(0.0f);
	body->setGravityEnable(true);
	body->setContactTestBitmask(0xFFFFFFFF);
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

void BossScene::bossInit()
{
	//boss
	boss = Boss::create();
	boss->setRole(Sprite::create("boss_leftidle1.png"));
	boss->setPosition(Vec2(522.0f, 128.0f));
	boss->setMoveEdge(110.0f, 610.0f);
	boss->setTag(Tag::BOSS);
	{
		auto* body = PhysicsBody::createBox(Size(72.0f, 76.0f), PhysicsMaterial(500.0f, 0.0f, 1.0f));
		body->setDynamic(true);
		body->setLinearDamping(0.0f);
		body->setGravityEnable(true);
		body->setContactTestBitmask(0x10);
		body->setCategoryBitmask(0x10);
		body->setCollisionBitmask(0x10);
		body->setRotationEnable(false);
		boss->setPhysicsBody(body);
	}
	map->addChild(boss, 4);

	//初始化动作
	boss->runRoleAction();

	//碰撞盒初始化
	Point bodyOrign;
	bodyOrign.x = boss->getPositionX() - 36.0f;
	bodyOrign.y = boss->getPositionY() - 38.0f;
	Size bodySize;
	bodySize.width = 72.0f;
	bodySize.height = 76.0f;
	boss->setBodyBox(bodyOrign, bodySize);

	Point hitOrign;
	hitOrign.x = boss->getPositionX() - 28.0f;
	hitOrign.y = boss->getPositionY() - 38.5f;
	Size hitSize;
	hitSize.width = 56.0f;
	hitSize.height = 76.0f;
	boss->setHitBox(hitOrign, hitSize);

	//血量条初始化
	bgHP = Sprite::create("HPBG.png");
	bgHP->setPosition(Vec2(320, 300));
	this->addChild(bgHP);
	numBar = Sprite::create("HPNumberBar.png");
	numBar->setAnchorPoint(Vec2(0, 0));
	numBar->setPosition(Vec2(220, 296));
	numBar->setContentSize(Size(200, 8));
	this->addChild(numBar);
	auto* labelHP = Label::createWithTTF("The King of the Nature", "swfit.ttf", 12);
	labelHP->setPosition(Vec2(320, 280));
	this->addChild(labelHP);

	//bossPrick
	bossPrick = Sprite::create("boss_prick1.png");
	bossPrick->setVisible(false);
	map->addChild(bossPrick, 6);
}

void BossScene::update(float dt)
{
	if (!isPauseGame)
	{
		//更新速度、状态等
		heroUpdate();

		if (hero->getPositionY() < 360.0f)
		{
			bossUpdate();
			bossDeathUpdate();
		}

		coinsUpdate();
		mapUpdate();
	}
}

void BossScene::heroUpdate()
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
		if (boss != NULL&&boss->isCanHurt)
		{
			if (collisionDetection(hero->getHitBox(), boss->getBodyBox()))
			{
				boss->runHurtAction();
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

		for (auto&i : bossRock)
		{
			if (i != NULL)
			{
				i = NULL;
			}
		}
		bossRock.clear();

		for (auto&i : bossRockBroken)
		{
			if (i != NULL)
			{
				i = NULL;
			}
		}
		bossRockBroken.clear();

		for (auto &i : blood)
		{
			if (i != NULL)
			{
				i = NULL;
			}
		}
		blood.clear();

		removeAllChildren();
		this->init();
	}
}

void BossScene::bossUpdate()
{
	if (boss != NULL)
	{
		switch (boss->getActionState())
		{
		case ActionState::IDLE:
			//attackMode1
			//连续攻击五次后结束攻击
			if (boss->attackMode == 1)
			{
				if (boss->attackCount > 0 && boss->attackCount < 5)
				{
					boss->setActionState(ActionState::ATTACK);
					boss->runRoleAction();
					break;
				}
				else if (boss->attackCount >= 5)
				{
					boss->attackCount = 0;
				}
			}
			else //attackMode2 连续攻击十次后结束攻击
			{
				if (boss->attackCount > 0 && boss->attackCount < 10)
				{
					boss->setActionState(ActionState::ATTACK);
					boss->runRoleAction();
					break;
				}
				else if (boss->attackCount >= 10)
				{
					boss->attackCount = 0;
				}
			}

			//开启idle时间计数
			if (boss->idleDuration == -1)
				boss->idleDuration = 0;
			break;

		case ActionState::WALK:
			//方向计数重置，结束walk状态
			if (boss->walkCount >= 3)
			{
				boss->walkCount = 0;
				boss->setActionState(ActionState::IDLE);
				boss->runRoleAction();
				break;
			}

			//boss变更速度
			if (boss->getDirection() == Direction::RIGHT)
			{
				Vec2 temp = boss->getPhysicsBody()->getVelocity();
				temp.x = boss->getVelX();
				boss->getPhysicsBody()->setVelocity(temp);
			}
			else
			{
				Vec2 temp = boss->getPhysicsBody()->getVelocity();
				temp.x = -boss->getVelX();
				boss->getPhysicsBody()->setVelocity(temp);
			}

			//改变方向
			if (boss->getHP() > 0 && boss->getPositionX() + boss->getContentSize().width / 2 >= boss->getMoveEdge().rightX && boss->getDirection() == Direction::RIGHT)
			{
				boss->setDirection(Direction::LEFT);
				boss->runRoleAction();
				
				//记录方向改变的次数
				boss->walkCount++;
			}
			else if (boss->getHP() > 0 && boss->getPositionX() - boss->getContentSize().width / 2 <= boss->getMoveEdge().leftX && boss->getDirection() == Direction::LEFT)
			{
				boss->setDirection(Direction::RIGHT);
				boss->runRoleAction();

				//记录方向改变的次数
				boss->walkCount++;
			}
			break;

		case ActionState::ATTACK:
            //开启attack时间计数
			if (boss->attackDuration == -1)
				boss->attackDuration = 0;
			break;

		default:
			break;
			
		}

		//idle间隔满计数后重置，用作变更boss状态
		if (boss->idleDuration >= 60 * 2.5)
		{
			boss->idleDuration = -1;

			srand((unsigned int)(time(0)) + rand());
			int randValue = rand() % 3;
			if (randValue == 0)
			{
				boss->attackMode = 1;
				boss->setActionState(ActionState::ATTACK);
				boss->runRoleAction();
			}
			else if(randValue == 1)
			{
				boss->attackMode = 2;
				boss->setActionState(ActionState::ATTACK);
				boss->runRoleAction();
			}
			else
			{
				boss->setActionState(ActionState::WALK);
				boss->runRoleAction();
			}
		}
		else if (boss->idleDuration >= 0)
		{
			boss->idleDuration++;
		}

		//attackMode1
		if (boss->attackMode == 1)
		{
			//攻击间隔满计数后重置，攻击期间生成prick
			if (boss->attackDuration >= 6 * 10)
			{
				boss->attackDuration = -1;
				bossPrick->setVisible(false);
			}
			else if (boss->attackDuration >= 0)
			{
				if (boss->attackDuration >= 6 * 5)
				{
					if (boss->attackDuration == 6 * 5)
					{
						bossPrick->setVisible(true);
						bossPrick->setPosition(Vec2(hero->getPositionX(), 90.0f + 28.0f));
						//创建动画
						auto* animation = Animation::create();
						for (int i = 1; i <= 5; i++)
						{                                                                  /*图片格式*/
							animation->addSpriteFrameWithFile(__String::createWithFormat("boss_prick%d.png", i)->getCString());
						}
						animation->setLoops(1);
						animation->setDelayPerUnit(0.1f);
						bossPrick->runAction(Animate::create(animation));

						//prick更新碰撞盒
						bossPrickRect.origin.x = bossPrick->getPositionX() - 8.0f;
						bossPrickRect.origin.y = bossPrick->getPositionY() - 28.0f;
						bossPrickRect.size.width = 16.0f;
						bossPrickRect.size.height = 34.0f;
					}
					else if (boss->attackDuration == 6 * 6)
					{
						//prick更新碰撞盒
						bossPrickRect.origin.x = bossPrick->getPositionX() - 12.0f;
						bossPrickRect.origin.y = bossPrick->getPositionY() - 28.0f;
						bossPrickRect.size.width = 24.0f;
						bossPrickRect.size.height = 56.0f;
					}
					else if (boss->attackDuration == 6 * 7)
					{
						//prick更新碰撞盒
						bossPrickRect.origin.x = bossPrick->getPositionX() - 10.0f;
						bossPrickRect.origin.y = bossPrick->getPositionY() - 28.0f;
						bossPrickRect.size.width = 20.0f;
						bossPrickRect.size.height = 48.0f;
					}
					else if (boss->attackDuration == 6 * 8)
					{
						//prick更新碰撞盒
						bossPrickRect.origin.x = bossPrick->getPositionX() - 10.0f;
						bossPrickRect.origin.y = bossPrick->getPositionY() - 28.0f;
						bossPrickRect.size.width = 20.0f;
						bossPrickRect.size.height = 40.0f;
					}
					else if (boss->attackDuration == 6 * 9)
					{
						//prick更新碰撞盒
						bossPrickRect.origin.x = bossPrick->getPositionX() - 6.0f;
						bossPrickRect.origin.y = bossPrick->getPositionY() - 28.0f;
						bossPrickRect.size.width = 12.0f;
						bossPrickRect.size.height = 24.0f;
					}

					//prick碰撞hero
					if (collisionDetection(bossPrickRect, hero->getBodyBox()) && hero->getActionState() < ActionState::HURT)
					{
						if (hero->invincibilityDuration < 0)
						{
							hero->runHurtAction();
						}
					}
				}
				boss->attackDuration++;
			}
		}
		else //attackMode2
		{
			//攻击间隔满计数后重置，攻击期间生成rock
			if (boss->attackDuration >= 6 * 7)
			{
				boss->attackDuration = -1;
			}
			else if (boss->attackDuration >= 0)
			{
				if (boss->attackDuration == 6 * 5)
				{
					//生成rock
					BossRock* tempRock;
					if (boss->getDirection() == Direction::LEFT)
					{
						tempRock = BossRock::create();
						tempRock->setRole(Sprite::create("boss_rockleft.png"));
						tempRock->setDirection(Direction::LEFT);
					}
					else
					{
						tempRock = BossRock::create();
						tempRock->setRole(Sprite::create("boss_rockright.png"));
						tempRock->setDirection(Direction::RIGHT);
					}
					tempRock->setPosition(boss->getPositionX(), boss->getPositionY() + 39);
					map->addChild(tempRock, 6);
					tempRock->getPhysicsBody()->setVelocity(Vec2(hero->getPositionX() - boss->getPositionX(), 400));
					tempRock->runRoleAction();
					bossRock.push_back(tempRock);
				}
				boss->attackDuration++;
			}
		}

		//rocks update
		bossRockUpdate();

		//boss碰撞hero
		if (boss->getHP() > 0 && collisionDetection(boss->getHitBox(), hero->getBodyBox()) && hero->getActionState() < ActionState::HURT)
		{
			if (hero->invincibilityDuration < 0)
			{
				hero->runHurtAction();
			}
		}

		//boss更新受伤状态
		if (hero->getActionState() != ATTACK)
		{
			boss->isCanHurt = true;
		}

		//boss血条更新
		numBar->setContentSize(Size(10 * boss->getHP(), 8));

		//boss更新碰撞盒
		Point bodyOrign;
		bodyOrign.x = boss->getPositionX() - 36.0f;
		bodyOrign.y = boss->getPositionY() - 38.0f;
		Size bodySize;
		bodySize.width = 72.0f;
		bodySize.height = 76.0f;
		boss->setBodyBox(bodyOrign, bodySize);

		Point hitOrign;
		hitOrign.x = boss->getPositionX() - 28.0f;
		hitOrign.y = boss->getPositionY() - 38.5f;
		Size hitSize;
		hitSize.width = 56.0f;
		hitSize.height = 76.0f;
		boss->setHitBox(hitOrign, hitSize);

		//boss死亡判断
		if (boss->getActionState() == ActionState::REMOVE)
		{
			//生成head
			bossHead = BossHead::create();
			if (boss->getDirection() == Direction::LEFT)
				bossHead->setRole(Sprite::create("bosshead_left.png"));
			else
				bossHead->setRole(Sprite::create("bosshead_right.png"));
			bossHead->setPosition(Vec2(boss->getPositionX(), boss->getPositionY() + 18.0f));
			map->addChild(bossHead, 6);
			bossHead->getPhysicsBody()->setVelocity(Vec2(bossHead->getVelX(), bossHead->getVelY()));
			bossHead->runRoleAction();

			//生成blood
			for (int i = 0; i < 10; i++)
			{
				auto* tempBlood = Blood::create();
				tempBlood->setPosition(boss->getPosition());
				map->addChild(tempBlood, 6);
				tempBlood->getPhysicsBody()->setVelocity(Vec2(tempBlood->getVelX(), tempBlood->getVelY()));
				tempBlood->runRoleAction();
				blood.push_back(tempBlood);
			}

			//生成coin
			for (int i = 0; i < 15; i++)
			{
				auto* tempCoin = Coin::create();
				tempCoin->setRole(Sprite::create("coin_idle1.png"));
				tempCoin->setPosition(boss->getPosition());
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

			//remove
			map->removeChild(boss);
			boss = NULL;
		}
	}
}

void BossScene::bossRockUpdate()
{
	//rock
	for (auto& i : bossRock)
	{
		if (i != NULL)
		{
			//rock碰撞盒更新
			Point bodyOrign;
			bodyOrign.x = i->getPositionX() - 12.0f;
			bodyOrign.y = i->getPositionY() - 13.0f;
			Size bodySize;
			bodySize.width = 24.0f;
			bodySize.height = 26.0f;
			i->setBodyBox(bodyOrign, bodySize);

			//rock碰撞碎裂
			if (collisionDetection(hero->getBodyBox(), i->getBodyBox()) || i->getPositionX() < 72.0f || i->getPositionX() > 648.0f || i->getPositionY() < 90.0f)
			{
				//生成碎块
				for (int j = 0; j < 10; j++)
				{
					auto* tempRockBroken = BossRockBroken::create();
					tempRockBroken->setPosition(i->getPosition());
					map->addChild(tempRockBroken,6);
					tempRockBroken->getPhysicsBody()->setVelocity(Vec2(tempRockBroken->getVelX(), tempRockBroken->getVelY()));
					tempRockBroken->runRoleAction();
					bossRockBroken.push_back(tempRockBroken);
				}

				//rock与hero碰撞
				if (collisionDetection(hero->getBodyBox(), i->getBodyBox()) && hero->invincibilityDuration < 0)
				{
					hero->runHurtAction();
				}

				//移除rock
				map->removeChild(i);
				i = NULL;

				continue;
			}
		}
	}

	//rock broken
	for (auto &i : bossRockBroken)
	{
		if (i != NULL)
		{   //掉出地图外
			if (i->getPositionY() < 0)
			{
				map->removeChild(i);
				i = NULL;

				continue;
			}
		}
	}
}

void BossScene::bossDeathUpdate()
{
	if (bossHead != NULL)
	{
		//掉出地图外
		if (bossHead->getPositionY() < 0 - 20)
		{
			map->removeChild(bossHead);
			bossHead = NULL;
		}
	}

	for (auto &i : blood)
	{
		if (i != NULL)
		{
			if (i->getPositionY() < 0)
			{
				map->removeChild(i);
				i = NULL;
			}
		}
	}
}

void BossScene::coinsUpdate()
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

void BossScene::mapUpdate()
{
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

void BossScene::onKeyPressed(EventKeyboard::KeyCode keyCode, Event *event)
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

void BossScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event *event)
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

void BossScene::onLeft(cocos2d::Ref * pSender, cocos2d::ui::Widget::TouchEventType type)
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

void BossScene::onRight(cocos2d::Ref * pSender, cocos2d::ui::Widget::TouchEventType type)
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

void BossScene::onJump(cocos2d::Ref * pSender, cocos2d::ui::Widget::TouchEventType type)
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

void BossScene::onAttack(cocos2d::Ref * pSender, cocos2d::ui::Widget::TouchEventType type)
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

bool BossScene::onContactBegin(cocos2d::PhysicsContact & contact)
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

	return true;
}

void BossScene::onContactSeperate(cocos2d::PhysicsContact & contact)
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

bool BossScene::collisionDetection(cocos2d::Rect hitBox, cocos2d::Rect bodyBox)
{
	if (hitBox.intersectsRect(bodyBox))
		return true;
	else
		return false;
}

void BossScene::pauseGame()
{
	if (!isPauseGame)
	{
		isPauseGame = true;

		pauseBG = LayerColor::create(Color4B(0, 0, 0, 200));
		this->addChild(pauseBG);

		resumeItem = MenuItemImage::create("resume1.png", "resume1.png", CC_CALLBACK_0(BossScene::resumeGame, this));
		resumeItem->setPosition(Vec2(360, 180));
		backItem = MenuItemImage::create("back1.png", "back1.png", CC_CALLBACK_0(BossScene::back, this));
		backItem->setPosition(Vec2(280, 180));
		pauseMenu = Menu::create(resumeItem, backItem, NULL);
		pauseMenu->setPosition(Vec2::ZERO);
		this->addChild(pauseMenu);
	}
}

void BossScene::resumeGame()
{
	if (isPauseGame)
	{
		isPauseGame = false;

		this->removeChild(pauseBG);
		this->removeChild(pauseMenu);
	}
}

void BossScene::back()
{
	if (isPauseGame)
	{
		isPauseGame = false;

		auto selectScene = SelectScene::createScene();
		Director::getInstance()->replaceScene(TransitionFade::create(1.0f, selectScene));
	}
}
