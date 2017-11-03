#include "Coin.h"

USING_NS_CC;

bool Coin::init()
{
	if (!BaseRole::init())
		return false;

	//初始化方向，动作，速度
	srand(int(time(0)) + rand());
	if (rand() % 2)
	{
		this->setDirection(Direction::LEFT);
		this->setVelX(-(rand() % 300));
		this->setVelY((rand() % 350));
	}
	else
	{
		this->setDirection(Direction::RIGHT);
		this->setVelX(rand() % 300);
		this->setVelY((rand() % 350));
	}
	this->setActionState(ActionState::IDLE);

	return true;
}

cocos2d::Animate * Coin::createAnimate()
{
	std::string acString;
	int num;
	unsigned int loops;

	switch (this->getActionState())
	{
	case ActionState::IDLE:
		acString = "idle";
		num = 4;
		loops = -1;
		break;

	case ActionState::DIE:

		break;

	default:
		CCLOG("error actionstate\n");
		break;
	}

	//创建动画
	auto* animation = Animation::create();
	for (int i = 1; i <= num; i++)
	{                                                                  /*图片格式*/
		animation->addSpriteFrameWithFile(__String::createWithFormat("coin_%s%d.png", acString.c_str(), i)->getCString());
	}
	animation->setLoops(loops);
	animation->setDelayPerUnit(0.1f);
	return Animate::create(animation);
}

void Coin::runRoleAction()
{
	switch (this->getActionState())
	{
	case ActionState::IDLE:
		this->runIdleAction(this->createAnimate());
		break;

	case ActionState::DIE:
		
		break;

	default:
		CCLOG("error:coin.cpp,runRoleAction\n");
		break;
	}
}

void Coin::runIdleAction(cocos2d::Animate * action)
{
	this->getRole()->stopAllActions();
	this->getRole()->runAction(action);
}

void Coin::runDieAction(cocos2d::Animate * action)
{
}

