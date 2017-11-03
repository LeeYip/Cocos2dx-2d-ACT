#include "BaseRole.h"

USING_NS_CC;

bool BaseRole::init()
{
	if (!Node::init())
		return false;

	return true;
}

void BaseRole::setRole(cocos2d::Sprite * sprite)
{
	this->baseSprite = sprite;
	this->addChild(baseSprite);
}

cocos2d::Sprite * BaseRole::getRole()
{
	return this->baseSprite;
}

void BaseRole::setDirection(Direction di)
{
	//this->lastDirection = this->direction;
	this->direction = di;
}

Direction BaseRole::getDirection()
{
	return this->direction;
}

//Direction BaseRole::getLastDirection()
//{
//	return this->lastDirection;
//}

void BaseRole::setActionState(ActionState ac)
{
	//this->lastActionState = this->actionState;
	this->actionState = ac;
}

ActionState BaseRole::getActionState()
{
	return this->actionState;
}

//ActionState BaseRole::getLastActionState()
//{
//	return this->lastActionState;
//}

void BaseRole::setHP(int hp)
{
	this->HP = hp;
}

int BaseRole::getHP()
{
	return this->HP;
}

void BaseRole::setVelX(float x)
{
	this->velX = x;
}

void BaseRole::setVelY(float y)
{
	this->velY = y;
}

float BaseRole::getVelX()
{
	return this->velX;
}

float BaseRole::getVelY()
{
	return this->velY;
}

void BaseRole::setHitBox(cocos2d::Point origin, cocos2d::Size size)
{
	this->hitBox.origin = origin;
	this->hitBox.size = size;
}

cocos2d::Rect BaseRole::getHitBox()
{
	return this->hitBox;
}

void BaseRole::setBodyBox(cocos2d::Point origin, cocos2d::Size size)
{
	this->bodyBox.origin = origin;
	this->bodyBox.size = size;
}

cocos2d::Rect BaseRole::getBodyBox()
{
	return this->bodyBox;
}

void BaseRole::setAlertBox(cocos2d::Point origin, cocos2d::Size size)
{
	this->alertBox.origin = origin;
	this->alertBox.size = size;
}

cocos2d::Rect BaseRole::getAlertBox()
{
	return this->alertBox;
}
