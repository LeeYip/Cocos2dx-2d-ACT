#include "Boss.h"

USING_NS_CC;

bool Boss::init()
{
	if (!BaseRole::init())
		return false;

	//初始化方向，动作，血量,速度
	this->setDirection(Direction::LEFT);
	this->setActionState(ActionState::IDLE);
	this->setHP(20);
	this->setVelX(250);

	isCanHurt = true;
	idleDuration = -1;
	attackDuration = -1;
	attackCount = 0;
	walkCount = 0;
	return true;
}

void Boss::setMoveEdge(float leftX, float rightX)
{
	this->moveEdge.leftX = leftX;
	this->moveEdge.rightX = rightX;
}

MoveEdge Boss::getMoveEdge()
{
	return this->moveEdge;
}

cocos2d::Animate * Boss::createAnimate()
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
		if (attackMode == 1)
		{
			acString = "attack1_";
			num = 10;
		}
		else
		{
			acString = "attack2_";
			num = 7;
		}

		loops = 1;
		break;

	case ActionState::DIE:
		
		break;

	case ActionState::HURT:

		break;

	case ActionState::IDLE:
		acString = "idle";
		num = 4;
		loops = -1;
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
		animation->addSpriteFrameWithFile(__String::createWithFormat("boss_%s%s%d.png", diString.c_str(), acString.c_str(), i)->getCString());
	}
	animation->setLoops(loops);
	animation->setDelayPerUnit(0.1f);
	return Animate::create(animation);
}

void Boss::runRoleAction()
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

		break;

	case ActionState::ATTACK:
		this->runAttackAction(this->createAnimate());
		break;

	case ActionState::HURT:
		
		break;

	case ActionState::DIE:
		
		break;

	default:
		CCLOG("error:enemy.cpp,runRoleAction\n");
		break;
	}
}

void Boss::runIdleAction(cocos2d::Animate * action)
{
	this->getRole()->setVisible(true);
	this->getRole()->stopAllActions();
	this->getRole()->runAction(action);
}

void Boss::runWalkAction(cocos2d::Animate * action)
{
	this->getRole()->setVisible(true);
	this->getRole()->stopAllActions();
	this->getRole()->runAction(action);
}

void Boss::runJumpAction(cocos2d::Animate * action)
{

}

void Boss::runAttackAction(cocos2d::Animate * action)
{
	this->getRole()->setVisible(true);
	this->getRole()->stopAllActions();
	auto* callFunc = CallFunc::create(CC_CALLBACK_0(Boss::bossAttackResume, this));
	auto* sequence = Sequence::create(action, callFunc, NULL);
	this->getRole()->runAction(sequence);
}

void Boss::runHurtAction()
{
	this->getRole()->setVisible(true);
	this->setHP(this->getHP() - 1);

	if (this->getHP() > 0)
	{
		auto* blink = Blink::create(0.4f, 2);
		this->runAction(blink);

		isCanHurt = false;
	}
	else
	{
		this->setActionState(ActionState::REMOVE);
		//this->setActionState(ActionState::DIE);
		//this->runDieAction(this->createAnimate());
	}
}

void Boss::runDieAction(cocos2d::Animate* action)
{
	
}

void Boss::bossAttackResume()
{
	attackCount++;

	this->getRole()->setVisible(true);
	this->setActionState(ActionState::IDLE);
	this->runIdleAction(this->createAnimate());
}
