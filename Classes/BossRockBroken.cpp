#include "BossRockBroken.h"

USING_NS_CC;

bool BossRockBroken::init()
{
	if (!BaseRole::init())
		return false;

	this->setActionState(ActionState::IDLE);

	srand(int(time(0)) + rand());
	int randValue = rand() % 10;

	if (randValue % 2 == 0)
	{
		this->setDirection(Direction::LEFT);
		this->setVelX(-rand() % 250);
	}
	else
	{
		this->setDirection(Direction::RIGHT);
		this->setVelX(rand() % 250);
	}

	this->setVelY(rand() % 300);

	PhysicsBody* body;
	if (randValue < 4)
	{
		this->setRole(Sprite::create("boss_rockbroken1.png"));
		body = PhysicsBody::createBox(Size(6.0f, 10.0f), PhysicsMaterial(500.0f, 1.0f, 1.0f));
	}
	else if (randValue < 8)
	{
		this->setRole(Sprite::create("boss_rockbroken2.png"));
		body = PhysicsBody::createBox(Size(6.0f, 10.0f), PhysicsMaterial(500.0f, 1.0f, 1.0f));
	}
	else if (randValue < 9)
	{
		this->setRole(Sprite::create("boss_rockbroken3.png"));
		body = PhysicsBody::createBox(Size(6.0f, 6.0f), PhysicsMaterial(500.0f, 1.0f, 1.0f));
	}
	else
	{
		this->setRole(Sprite::create("boss_rockbroken4.png"));
		body = PhysicsBody::createBox(Size(6.0f, 6.0f), PhysicsMaterial(500.0f, 1.0f, 1.0f));
	}
	body->setDynamic(true);
	body->setLinearDamping(0.0f);
	body->setGravityEnable(true);
	body->setCategoryBitmask(0x00);
	body->setCollisionBitmask(0x00);
	body->setRotationEnable(false);
	this->setPhysicsBody(body);

	return true;
}

void BossRockBroken::runRoleAction()
{
	switch (this->getActionState())
	{
	case ActionState::IDLE:
		this->runIdleAction();
		break;

	default:
		CCLOG("error:BossRockBroken.cpp,runRoleAction\n");
		break;
	}
}

cocos2d::Animate * BossRockBroken::createAnimate()
{
	return nullptr;
}

void BossRockBroken::runIdleAction()
{
	RotateBy* rotateBy;
	if (this->getDirection() == Direction::LEFT)
		rotateBy = RotateBy::create(4.0f, Vec3(0, 0, -1080));
	else
		rotateBy = RotateBy::create(4.0f, Vec3(0, 0, 1080));

	this->getRole()->runAction(rotateBy);
}
