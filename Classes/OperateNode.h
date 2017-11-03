#ifndef _OPERATENODE_H_
#define _OPERATENODE_H_

#include "cocos2d.h"
#include "ui/CocosGUI.h"

class OperateNode : public cocos2d::Node
{
private:
	//虚拟按键
	cocos2d::ui::Button* left;
	cocos2d::ui::Button* right;
	cocos2d::ui::Button* jump;
	cocos2d::ui::Button* attack;

public:
	//判断相应按键是否按下
	bool isLeft;
	bool isRight;
	bool isJump;
	bool isAttack;

public:
	virtual bool init();
	CREATE_FUNC(OperateNode);

	//虚拟按键事件
	void onLeft(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type);
	void onRight(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type);
	void onJump(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type);
	void onAttack(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type);
};

#endif // !_OPERATENODE_H_
