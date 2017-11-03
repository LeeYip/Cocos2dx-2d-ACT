#include "Blood.h"

USING_NS_CC;

bool Blood::init()
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

	this->setVelY(rand() % 400);

	PhysicsBody* body;
	if (randValue < 2)
	{
		this->setRole(Sprite::create("blood1.png"));
		body = PhysicsBody::createBox(Size(6.0f, 6.0f), PhysicsMaterial(500.0f, 1.0f, 1.0f));
	}
	else if (randValue < 7)
	{
		this->setRole(Sprite::create("blood2.png"));
		body = PhysicsBody::createBox(Size(8.0f, 8.0f), PhysicsMaterial(500.0f, 1.0f, 1.0f));
	}
	else
	{
		this->setRole(Sprite::create("blood3.png"));
		body = PhysicsBody::createBox(Size(10.0f, 10.0f), PhysicsMaterial(500.0f, 1.0f, 1.0f));
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

void Blood::runRoleAction()
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

cocos2d::Animate * Blood::createAnimate()
{
	return nullptr;
}

void Blood::runIdleAction()
{
	RotateBy* rotateBy;
	if (this->getDirection() == Direction::LEFT)
		rotateBy = RotateBy::create(4.0f, Vec3(0, 0, -1080));
	else
		rotateBy = RotateBy::create(4.0f, Vec3(0, 0, 1080));

	this->getRole()->runAction(rotateBy);
}