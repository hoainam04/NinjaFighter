#ifndef __Hero__H__
#define __Hero__H__

#include "cocos2d.h"
//#include "Enimies.h"

enum heroState {
	idle,
	running,
	jump,
	fall,
	attack,
	take_hit,
	death
};

class Hero : public cocos2d::Node{
public:
	virtual bool init();

	void Hero::initBody();
	void Hero::atkBox();
	void Hero::doAction(const char* actionName);
	void Hero::actionSet();
	heroState getState() { return m_state; };//

	void Idle();

	void RunRight();
	void RunLeft();

	void Jump();

	void Attack();

	void takeHit();

	void Death();

	virtual void update(float dt);

	CREATE_FUNC(Hero);

private:
	cocos2d::Sprite* _hero;
	heroState m_state;
	float hp1=100;
	float maxHP = 100.0;

	//Enimies *_CP;
	//
	bool _isAttack;
};/**/

#endif