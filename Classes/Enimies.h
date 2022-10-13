#ifndef __Enimies__H__
#define __Enimies__H__

#include "cocos2d.h"
//#include "Hero.h"

enum CPState {
	K_idle,
	K_running,
	K_jump,
	K_fall,
	K_attack,
	K_takeHit,
	K_death
};

class Enimies : public cocos2d::Node{
public:
	virtual bool init();

	void initBody();
	void doAction(const char* actionName);
	void actionSet();
	CPState getState() { return k_state; };//
	
	void K_Idle();
	void K_RunRight();
	void K_RunLeft();
	void K_Attack();
	void K_Jump();
	void K_Fall();
	void K_TakeHit();
	void K_Death();

	void SpawnCP();
	//void createCP(cocos2d::Size visibleSize);
	virtual void update(float dt);

	CREATE_FUNC(Enimies);

private:
	cocos2d::Sprite* _CP;
	CPState k_state;

	float hp2 = 100;
	//Hero* _hero;

	cocos2d::Vec2 m_CParr;
};/**/

#endif