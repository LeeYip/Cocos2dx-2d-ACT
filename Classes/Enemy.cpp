#include "Enemy.h"

USING_NS_CC;

bool Enemy::init()
{
	if (!BaseRole::init())
		return false;

	//初始化方向，动作，血量,速度
	this->setDirection(Direction::RIGHT);
	this->setActionState(ActionState::IDLE);
	this->setHP(3);
	this->setVelX(100);

	return true;
}

void Enemy::setMoveEdge(float leftX, float rightX)
{
	this->moveEdge.leftX = leftX;
	this->moveEdge.rightX = rightX;
}

MoveEdge Enemy::getMoveEdge()
{
	return this->moveEdge;
}

cocos2d::Animate * Enemy::createAnimate()
{
	std::string diString;
	std::string acString;
	int num;
	unsigned int loops;

	switch (this->getDirection())
	{
	case Direction::LEFT:
		diString = "left";
		break;

	case Direction::RIGHT:
		diString = "right";
		break;

	default:
		CCLOG("error direction\n");
		break;
	}

	switch (this->getActionState())
	{
	case ActionState::ATTACK:
		
		break;

	case ActionState::DIE:
		diString = "";
		acString = "die";
		num = 4;
		loops = 1;
		break;

	case ActionState::HURT:
		
		break;

	case ActionState::IDLE:
		
		break;

	case ActionState::JUMP:

		break;

	case ActionState::WALK:
		acString = "walk";
		num = 4;
		loops = -1;
		break;

	default:
		CCLOG("error actionstate\n");
		break;
	}

	//创建动画
	auto* animation = Animation::create();
	for (int i = 1; i <= num; i++)
	{                                                                  /*图片格式*/
		animation->addSpriteFrameWithFile(__String::createWithFormat("enemy_%s%s%d.png", diString.c_str(), acString.c_str(), i)->getCString());
	}
	animation->setLoops(loops);
	animation->setDelayPerUnit(0.1f);
	return Animate::create(animation);
}

void Enemy::runRoleAction()
{
	switch (this->getActionState())
	{
	case ActionState::IDLE:
		
		break;

	case ActionState::WALK:
		this->runWalkAction(this->createAnimate());
		break;

	case ActionState::JUMP:
		
		break;

	case ActionState::ATTACK:
		
		break;

	case ActionState::HURT:
		this->runHurtAction();
		break;

	case ActionState::DIE:
		this->runDieAction(this->createAnimate());
		break;

	default:
		CCLOG("error:enemy.cpp,runRoleAction\n");
		break;
	}
}

void Enemy::runIdleAction(cocos2d::Animate * action)
{
	
}

void Enemy::runWalkAction(cocos2d::Animate * action)
{
	this->getRole()->stopAllActions();
	this->getRole()->runAction(action);
}

void Enemy::runJumpAction(cocos2d::Animate * action)
{
	
}

void Enemy::runAttackAction(cocos2d::Animate * action)
{
	
}

void Enemy::runHurtAction()
{
	this->setHP(this->getHP() - 1);

	if (this->getHP() > 0)
	{
		this->getRole()->stopAllActions();
		auto* blink = Blink::create(0.5f, 2);
		auto* callFunc = CallFunc::create(CC_CALLBACK_0(Enemy::enemyHurtResume, this));
		auto* sequence = Sequence::create(blink, callFunc, NULL);
		this->getRole()->runAction(sequence);
	}
	else
	{
		this->setActionState(ActionState::DIE);
		this->runDieAction(this->createAnimate());
	}
}

void Enemy::runDieAction(cocos2d::Animate* action)
{
	this->getRole()->setVisible(true);
	this->getRole()->stopAllActions();
	auto* callFunc = CallFunc::create(CC_CALLBACK_0(Enemy::enemyDieResume, this));
	auto* sequence = Sequence::create(action, callFunc, NULL);
	this->getRole()->runAction(sequence);
}

void Enemy::enemyAttackResume()
{
	
}

void Enemy::enemyHurtResume()
{
	this->getRole()->setVisible(true);

	this->setActionState(WALK);
	this->runWalkAction(this->createAnimate());
}

void Enemy::enemyDieResume()
{
	this->setActionState(ActionState::REMOVE);
}
