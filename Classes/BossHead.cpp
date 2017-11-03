#include "BossHead.h"

USING_NS_CC;

bool BossHead::init()
{
	if (!BaseRole::init())
		return false;

	this->setActionState(ActionState::IDLE);

	srand(int(time(0)) + rand());
	this->setVelX(-100 + rand() % 200);
	this->setVelY(rand() % 200);

	PhysicsBody* body;
	body = PhysicsBody::createBox(Size(36.0f, 40.0f), PhysicsMaterial(500.0f, 1.0f, 1.0f));
	body->setDynamic(true);
	body->setLinearDamping(0.0f);
	body->setGravityEnable(true);
	body->setCategoryBitmask(0x00);
	body->setCollisionBitmask(0x00);
	body->setRotationEnable(false);
	this->setPhysicsBody(body);

	return true;
}

cocos2d::Animate * BossHead::createAnimate()
{
	return nullptr;
}

void BossHead::runRoleAction()
{
	switch (this->getActionState())
	{
	case ActionState::IDLE:
		this->runIdleAction();
		break;

	default:
		CCLOG("error:BossHead.cpp,runRoleAction\n");
		break;
	}
}

void BossHead::runIdleAction()
{
	RotateBy* rotateBy;
	if (this->getDirection() == Direction::LEFT)
		rotateBy = RotateBy::create(5.0f, Vec3(0, 0, -1080));
	else
		rotateBy = RotateBy::create(5.0f, Vec3(0, 0, 1080));

	this->getRole()->runAction(rotateBy);
}
