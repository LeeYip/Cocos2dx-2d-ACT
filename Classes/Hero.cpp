#include "Hero.h"

USING_NS_CC;

bool Hero::init()
{
	if (!BaseRole::init())
		return false;

	//初始化方向，动作，血量，速度
	this->setDirection(Direction::RIGHT);
	this->setActionState(ActionState::IDLE);
	this->setHP(5);
	this->setVelX(200);
	this->setVelY(450);
	this->invincibilityDuration = -1;

	return true;
}

Animate * Hero::createAnimate()
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
		CCLOG("error:hero.cpp,createAnimate\n");
		break;
	}

	switch (this->getActionState())
	{
	case ActionState::ATTACK:
		acString = "attack";
		num = 3;
		loops = 1;
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
		acString = "idle";
		num = 1;
		loops = -1;
		break;

	case ActionState::JUMP:
		if (isJumpUp)
		{
			acString = "jumpup";
		}
		else
		{
			acString = "jumpdown";
		}
		num = 1;
		loops = -1;
		break;

	case ActionState::WALK:
		acString = "walk";
		num = 4;
		loops = -1;
		break;

	default:
		CCLOG("error:hero.cpp,createAnimate\n");
		break;
	}

	//创建动画
	auto* animation = Animation::create();
	for (int i = 1; i <= num; i++)
	{                                                                  /*图片格式*/
		animation->addSpriteFrameWithFile(__String::createWithFormat("hero_%s%s%d.png", diString.c_str(), acString.c_str(), i)->getCString());
	}
	animation->setLoops(loops);
	animation->setDelayPerUnit(0.1f);
	return Animate::create(animation);
}

void Hero::runRoleAction()
{
	switch (this->getActionState())
	{
	case ActionState::IDLE:
		this->runIdleAction(this->createAnimate());
		break;

	case ActionState::WALK:
		this->runWalkAction(this->createAnimate());
		break;

	case ActionState::JUMP:
		this->runJumpAction(this->createAnimate());
		break;

	case ActionState::ATTACK:
		this->runAttackAction(this->createAnimate());
		break;

	case ActionState::HURT:
		
		break;

	case ActionState::DIE:
		this->runDieAction(this->createAnimate());
		break;

	default:
		CCLOG("error:hero.cpp,runRoleAction\n");
		break;
	}
}

void Hero::runIdleAction(cocos2d::Animate * action)
{
	this->getRole()->setVisible(true);
	this->getRole()->stopAllActions();
	this->getRole()->runAction(action);
}

void Hero::runWalkAction(cocos2d::Animate * action)
{
	this->getRole()->stopAllActions();
	this->getRole()->runAction(action);
}

void Hero::runJumpAction(cocos2d::Animate * action)
{
	this->getRole()->stopAllActions();
	this->getRole()->runAction(action);
}

void Hero::runAttackAction(cocos2d::Animate * action)
{
	this->getRole()->stopAllActions();
	auto* callFunc = CallFunc::create(CC_CALLBACK_0(Hero::heroAttackResume, this));
	auto* sequence = Sequence::create(action, callFunc, NULL);
	this->getRole()->runAction(sequence);
}

void Hero::runHurtAction()
{
	this->setHP(this->getHP() - 1);

	if (this->getHP() > 0)
	{
		auto* blink = Blink::create(0.4f, 2);
		this->runAction(blink);

		//开启无敌时间
		if (this->invincibilityDuration == -1)
		{
			this->invincibilityDuration = 0;
		}
	}
	else
	{
		this->setActionState(ActionState::DIE);
		this->runDieAction(this->createAnimate());
	}
}

void Hero::runDieAction(cocos2d::Animate* action)
{
	this->getRole()->setVisible(true);
	this->getRole()->stopAllActions();
	auto fade = FadeOut::create(0.2f);
	auto* callFunc = CallFunc::create(CC_CALLBACK_0(Hero::heroDieResume, this));
	auto* sequence = Sequence::create(action, fade, callFunc, NULL);
	this->getRole()->runAction(sequence);
}

void Hero::heroAttackResume()
{
	this->getRole()->setVisible(true);
	this->setActionState(ActionState::IDLE);
	this->runIdleAction(this->createAnimate());
}

//void Hero::heroHurtResume()
//{
//	this->getRole()->setVisible(true);
//	this->setActionState(ActionState::IDLE);
//	this->runIdleAction(this->createAnimate());
//}

void Hero::heroDieResume()
{
	this->setActionState(ActionState::REMOVE);
}

