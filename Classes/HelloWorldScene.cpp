
#include "HelloWorldScene.h"
#include "PlayScene.h"
#include"GameOver.h"
#include "AudioEngine.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }
    CCLOG("HELLOSCNE");

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    AudioEngine::play2d("BGMusic.wav", true, 0.1f);
    auto BG = Sprite::create("Bg_1.png");
    BG->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    BG->setScale(1);
    this->addChild(BG);


    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));

    if (closeItem == nullptr ||
        closeItem->getContentSize().width <= 0 ||
        closeItem->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width - closeItem->getContentSize().width/2;
        float y = origin.y + closeItem->getContentSize().height/2;
        closeItem->setPosition(Vec2(x,y));
    }
   
    auto spriteframeCache = SpriteFrameCache::getInstance();
    spriteframeCache->addSpriteFramesWithFile("Shop.plist", "Shop.png");

    auto shop = Sprite::createWithSpriteFrameName("shop1.png");
    shop->setScale(2.3);
    shop->setPosition(Vec2(800, 240));
    this->addChild(shop);
    SpriteFrame* frame = NULL;

    char file[100] = { 0 };

    Vector<SpriteFrame*>frameVector;

    //-----Idle-----
    for (int i = 1; i <= 6; i++) {
        sprintf(file, "shop%d.png", i);
        frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(file);
        frameVector.pushBack(frame);
    }
    auto shop_animation = Animation::createWithSpriteFrames(frameVector, 0.1f, -1);
    AnimationCache::getInstance()->addAnimation(shop_animation, "shop");
    auto animation = AnimationCache::getInstance()->getAnimation("shop");
    auto action = Animate::create(animation);
    shop->runAction(action);

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    auto UiplayScene = MenuItemImage::create(
        "play1.png",
        "play2.png",
        [&](Ref* sender)
        {
            Scene* playScene = TransitionFade::create(1, PlayScene::createScene());
            Director::getInstance()->replaceScene(playScene);
        });
    UiplayScene->setPosition(Vec2(0, 0));
    UiplayScene->setScale(0.5);
    auto menuP = Menu::create(UiplayScene, NULL);
    this->addChild(menuP);

    auto label = Label::createWithTTF("NINJA FIGTHTER", "fonts/Picxel.ttf", 40);

    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width / 2,
        origin.y + visibleSize.height - label->getContentSize().height-100));

    // add the label as a child to this layer
    this->addChild(label, 1);

    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
}
