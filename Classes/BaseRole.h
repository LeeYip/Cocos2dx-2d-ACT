#ifndef _BASEROLE_H_
#define _BASEROLE_H_

#include "cocos2d.h"

//方向
enum Direction
{
	LEFT,
	RIGHT
};

//状态,按优先级从小到大排列
enum ActionState
{
	NONE = 10,
	IDLE,
	WALK,
	JUMP,
	ATTACK,
	HURT,
	DIE,
	REMOVE
};

//移动范围
struct MoveEdge
{
	float leftX;
	float rightX;
};

class BaseRole :public cocos2d::Node
{
private:
	//当前的方向与状态
	Direction direction;
	ActionState actionState;
	//上一次的方向与状态
	//Direction lastDirection;
	//ActionState lastActionState;

	//血量
	int HP;

	//速度
	float velX;
	float velY;

	//角色
	cocos2d::Sprite* baseSprite;

	//攻击范围与身体范围碰撞盒
	cocos2d::Rect hitBox;
	cocos2d::Rect bodyBox;

	//怪物的警觉区域
	cocos2d::Rect alertBox;

public:
	virtual bool init();
	//CREATE_FUNC(BaseRole);

	//根据方向和状态以及帧数获取动画
	virtual cocos2d::Animate* createAnimate() = 0;

	//执行动画
	virtual void runRoleAction() = 0;

	//设置与获取角色
	void setRole(cocos2d::Sprite* sprite);
	cocos2d::Sprite* getRole();

	//设置与获取方向
	void setDirection(Direction di);
	Direction getDirection();
	/*Direction getLastDirection();*/

	//设置与获取动作状态
	void setActionState(ActionState ac);
	ActionState getActionState();
	/*ActionState getLastActionState();*/

	//设置与获取血量
	void setHP(int hp);
	int getHP();

	//设置与获取速度
	void setVelX(float x);
	void setVelY(float y);
	float getVelX();
	float getVelY();

	//设置与获取碰撞盒
	void setHitBox(cocos2d::Point origin, cocos2d::Size size);
	cocos2d::Rect getHitBox();
	void setBodyBox(cocos2d::Point origin, cocos2d::Size size);
	cocos2d::Rect getBodyBox();

	//设置与获取警觉区域
	void setAlertBox(cocos2d::Point origin, cocos2d::Size size);
	cocos2d::Rect getAlertBox();
};

#endif // !_BASEROLE_H

