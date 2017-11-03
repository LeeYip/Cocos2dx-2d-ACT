#include "OperateNode.h"

USING_NS_CC;

bool OperateNode::init()
{
	if (!Node::init())
		return false;

	isLeft = false;
	isRight = false;
	isJump = false;
	isAttack = false;

	//ÐéÄâ°´¼ü
	left = ui::Button::create("left1.png", "left2.png");
	left->setPosition(Vec2(70, 40));
	left->addTouchEventListener(ui::Widget::ccWidgetTouchCallback(CC_CALLBACK_2(OperateNode::onLeft, this)));
	this->addChild(left);
	right = ui::Button::create("right1.png", "right2.png");
	right->setPosition(Vec2(180, 40));
	right->addTouchEventListener(ui::Widget::ccWidgetTouchCallback(CC_CALLBACK_2(OperateNode::onRight, this)));
	this->addChild(right);
	jump = ui::Button::create("jump1.png", "jump2.png");
	jump->setPosition(Vec2(600, 40));
	jump->addTouchEventListener(ui::Widget::ccWidgetTouchCallback(CC_CALLBACK_2(OperateNode::onJump, this)));
	this->addChild(jump);
	attack = ui::Button::create("attack1.png", "attack2.png");
	attack->setPosition(Vec2(520, 40));
	attack->addTouchEventListener(ui::Widget::ccWidgetTouchCallback(CC_CALLBACK_2(OperateNode::onAttack, this)));
	this->addChild(attack);

	return true;
}

void OperateNode::onLeft(cocos2d::Ref * pSender, cocos2d::ui::Widget::TouchEventType type)
{
}

void OperateNode::onRight(cocos2d::Ref * pSender, cocos2d::ui::Widget::TouchEventType type)
{
}

void OperateNode::onJump(cocos2d::Ref * pSender, cocos2d::ui::Widget::TouchEventType type)
{
}

void OperateNode::onAttack(cocos2d::Ref * pSender, cocos2d::ui::Widget::TouchEventType type)
{
}
