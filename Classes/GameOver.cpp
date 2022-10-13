#include "GameOver.h"
//#include "MainScene.h"
#include "PlayScene.h"

USING_NS_CC;

Scene* GameOver::createscene()
{
    //Scene* scene = Scene::create();
    //Layer* layer = GameOver::create();
    //scene->addChild(layer);
    return GameOver::create();
}

bool GameOver::init()
{
    if(!Scene::init())
    {
        return false;
    }
    CCLOG("GAMEOVER");
    //create background
    createBG();

    return true;
}

void GameOver::createBG()
{
    auto winSize = Director::getInstance()->getWinSize();
    auto centerPoint = Vec2(winSize.width / 2, winSize.height / 2);
    //BG
    auto spriteBg = Sprite::create("Bg_1.png");
    spriteBg->setPosition(centerPoint);
    this->addChild(spriteBg);

    //create button//Start mutton
    MenuItemImage* menuItem = MenuItemImage::create(
                                  "play1.png",
                                  "play2.png",
                                  CC_CALLBACK_1(GameOver::reStart,this));

    Menu* menu = Menu::create(menuItem,NULL);

    menu->setPosition(centerPoint);

    this->addChild(menu);
}

void GameOver::reStart(cocos2d::Ref *sender)
{
    CCLOG("game is restart !");
    Scene* playScene = TransitionFade::create(1,PlayScene::createScene());
    Director::getInstance()->replaceScene(playScene);
}
