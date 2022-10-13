#ifndef __PLAYS_CENE_H__
#define __PLAY_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "ui/UIWidget.h"
#include "Hero.h"
#include "Enimies.h"

using namespace cocos2d;

class PlayScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
	void initBG();
	void HPbar();
	void Shop();
	//void time(float dt);

	void PlayScene::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	void PlayScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);

	void PlayScene::update(float dt);

	//void SpawnCP(float dt);
	bool onTouchBegan(Touch* touch, Event* event);

	//void onEnter();
	//void onExit();
	bool onContactBegin(cocos2d::PhysicsContact& contact);

	void GameOver();

    CREATE_FUNC(PlayScene);

private:
	void initPhysicWorld();
	Hero* _hero;
	Hero* hp1;
	Hero* maxHP;

	Enimies* _CP;
	Enimies* hp2;

	float timeRemaining;
	Label* labelTime;

	cocos2d::Sprite* bgSprite1;
	cocos2d::Sprite* bgSprite2;

	cocos2d::PhysicsWorld* world;
	void setPhysicWorld(cocos2d::PhysicsWorld* m_world)
	{
		world = m_world;
	}

};

#endif
