#ifndef __GameOver__H__
#define __GameOver__H__

#include "cocos2d.h"
USING_NS_CC;
class GameOver : public cocos2d::Scene{
public:
	virtual bool init();
	static cocos2d::Scene* createscene();
	CREATE_FUNC(GameOver);

	void createBG();

	void reStart(cocos2d::Ref *sender);
};/**/

#endif