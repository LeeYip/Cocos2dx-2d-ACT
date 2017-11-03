#include "BossRock.h"

USING_NS_CC;

bool BossRock::init()
{
	if (!BaseRole::init())
		return false;

	this->setActionState(ActionState::IDLE);

	auto* body = PhysicsBody::createBox(Size(24.0f, 26.0f), PhysicsMaterial(500.0f, 1.0f, 1.0f));
	body->setDynamic(true);
	body->setLinearDamping(0.0f);
	body->setGravityEnable(true);
	body->setCategoryBitmask(0x00);
	body->setCollisionBitmask(0x00);
	body->setRotationEnable(false);
	this->setPhysicsBody(body);

	return true;
}

cocos2d::Animate * BossRock::createAnimate()
{
	return nullptr;
}

void BossRock::runRoleAction()
{
	switch (this->getActionState())
	{
	case ActionState::IDLE:
		this->runIdleAction();
		break;

	case ActionState::DIE:

		break;

	default:
		CCLOG("error:BossRock.cpp,runRoleAction\n");
		break;
	}
}

void BossRock::runIdleAction()
{
	RotateBy* rotateBy;
	if (this->getDirection() == Direction::LEFT)
		rotateBy = RotateBy::create(4.0f, Vec3(0, 0, -1080));
	else
		rotateBy = RotateBy::create(4.0f, Vec3(0, 0, 1080));

	this->getRole()->runAction(rotateBy);
}
