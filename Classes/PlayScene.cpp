#include "PlayScene.h"
#include "ui/CocosGUI.h"
#include "ui/UIWidget.h"
#include "GameOver.h"
#include "Tag.h"

USING_NS_CC;

Scene* PlayScene::createScene()
{
    auto scene = PlayScene::createWithPhysics();
    scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_NONE);
    //scene->getPhysicsWorld()->setGravity(Vec2(0,-150));
    auto layer = PlayScene::create();
    layer->setPhysicWorld(scene->getPhysicsWorld());
    scene->addChild(layer);
    return scene;
}
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool PlayScene::init()
{
    if (!Scene::initWithPhysics())
    {
        return false;
    }
    CCLOG("PLAYSCENE");
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    initPhysicWorld();
    initBG();
    HPbar();
    Shop();


 /*   this->scheduleUpdate();*/

    _hero = Hero::create();
    _hero->setPosition(200, 300);
    _hero->Idle();

    this->addChild(_hero);

    _CP = Enimies::create();
    _CP->setPosition(700, 300);
    this->addChild(_CP);
    _CP->K_Idle();


    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = CC_CALLBACK_2(PlayScene::onTouchBegan, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

    auto listenerContact = EventListenerPhysicsContact::create();
    listenerContact->onContactBegin = CC_CALLBACK_1(PlayScene::onContactBegin, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listenerContact, this);

    auto listener = EventListenerKeyboard::create();
    listener->onKeyPressed = CC_CALLBACK_2(PlayScene::onKeyPressed, this);
    listener->onKeyReleased = CC_CALLBACK_2(PlayScene::onKeyReleased, this);

    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    //this->schedule(SEL_SCHEDULE(&PlayScene::time),1.5);
    timeRemaining = 100.f;
    //labelTime = Label::
    //:createWithTTF("fonts/Picxel.ttf", 40);
    this->scheduleUpdate();
    return true;
}
void PlayScene::initPhysicWorld() {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();
    Size gSize;
    gSize.width -= 1200;
    gSize.height -= 115;

    auto boxBody = PhysicsBody::createBox(gSize, PhysicsMaterial(0.0f, 0.0f, 0.0f));
    boxBody->setDynamic(false);

    auto boxNode = Node::create();

    boxNode->setPhysicsBody(boxBody);

    boxNode->setPosition(600, 30);

    this->addChild(boxNode);
}
void PlayScene::initBG() {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    bgSprite1 = Sprite::create("Bg_1.png");
    bgSprite1->setPosition(visibleSize.width / 2, visibleSize.height / 2);
    this->addChild(bgSprite1);
}
void PlayScene::HPbar() {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto HPSprite1 = Sprite::create("HpBar_1.png");
    HPSprite1->setPosition(220, 500);
    this->addChild(HPSprite1);
    auto _hpBarP1 = ui::LoadingBar::create("HP.png");
    _hpBarP1->setDirection(ui::LoadingBar::Direction::LEFT);
    _hpBarP1->setScale(1);
    _hpBarP1->setPosition(Vec2(260, 515));
    _hpBarP1->setPercent(100);
    this->addChild(_hpBarP1);

    auto P1 = Label::createWithTTF("Player 1", "fonts/Picxel.ttf", 20);
    P1->setPosition(Vec2(165,485));
    this->addChild(P1);
///------P2
    auto HPSprite2 = Sprite::create("Hpbar_2.png");
    HPSprite2->setPosition(800, 500);
    this->addChild(HPSprite2);

    auto _hpBarP2 = ui::LoadingBar::create("HP.png");
    _hpBarP2->setDirection(ui::LoadingBar::Direction::RIGHT);
    _hpBarP2->setScale(1);
    _hpBarP2->setPosition(Vec2(760, 515));
    _hpBarP2->setPercent(100);
    this->addChild(_hpBarP2);

    auto P2 = Label::createWithTTF("Player 2", "fonts/Picxel.ttf", 20);
    P2->setPosition(Vec2(855, 485));
    this->addChild(P2);

    //auto _hpBar = ui::LoadingBar::create("sprites/GameUI/hp-bar.png");
    //_hpBar->setDirection(ui::LoadingBar::Direction::LEFT);
    //_hpBar->setScale(SIZE_SLIME / _hpBar->getContentSize().width);
    //_hpBar->setPosition(Vec2(0, SIZE_SLIME / 2 + 5));
    //_hpBar->setPercent(((*_hp) / (*_max_hp)) * 100);
    //-----TimeBox-----
    auto timeBox = Sprite::create("timeBox.png");
    timeBox->setPosition(Vec2(visibleSize.width/2,520));
    this->addChild(timeBox);
}

void PlayScene::Shop() {
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
}

bool PlayScene::onTouchBegan(Touch* touch, Event* event) {
    _hero->Attack();
    _CP->K_Attack();
    //_hero->Jump();
    // 
    //_CP->K_Jump();
    return true;
}


bool PlayScene::onContactBegin(PhysicsContact& contact)
{
    {
        auto a = contact.getShapeA()->getBody();
        auto b = contact.getShapeB()->getBody();

        if (a->getCollisionBitmask() == P1Atk && b->getCollisionBitmask() == Player2 ||
            a->getCollisionBitmask() == Player2 && b->getCollisionBitmask() == P1Atk)
        {
            log("contact p1");
            _CP->stopAllActions();
            _CP->K_TakeHit();
        }
        else if (a->getCollisionBitmask() == P2Atk && b->getCollisionBitmask() == Player1 ||
            a->getCollisionBitmask() == Player1 && b->getCollisionBitmask() == P2Atk)
        {
            log("contact p2");
            _hero->stopAllActions();
            _hero->takeHit();
        }
    }

    auto body_1 = contact.getShapeA()->getBody()->getNode();
    auto body_2 = contact.getShapeB()->getBody()->getNode();


    if (body_1->getTag() == 2 && body_2->getTag() == 8)
    {

        CCLOG("P1 -10HP");
        //GameOver();
    }
    else if(body_1->getTag() ==  4 && body_2->getTag() == 6)
    {
        CCLOG("P2 -10HP");
    }

    //if (body_1->getTag() == 2)
    //{
    //    CCLOG("-10HP");
    //    body_1->setVisible(false);
    //}
    //if (body_2->getTag() == 2)
    //{
    //    CCLOG("-10HP");
    //    body_2->setVisible(false);
    //}

    return true;
}
void PlayScene::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{


    //------Player1-----
    if (keyCode == EventKeyboard::KeyCode::KEY_W) {
        _hero->stopAllActions();
        _hero->Jump();
    }
    if (keyCode == EventKeyboard::KeyCode::KEY_S)
    {
        _hero->stopAllActions();
        _hero->Attack();
    }
    if (keyCode == EventKeyboard::KeyCode::KEY_D) {
        //_hero->stopAllActions();
        _hero->RunRight();
    }
    if (keyCode == EventKeyboard::KeyCode::KEY_A) {
        //_hero->stopAllActions();
        _hero->RunLeft();
    }
    //-------Player2-------
    if (keyCode == EventKeyboard::KeyCode::KEY_UP_ARROW) {
        _CP->stopAllActions();
        _CP->K_Jump();
    }
    if (keyCode == EventKeyboard::KeyCode::KEY_DOWN_ARROW)
    {
        _CP->stopAllActions();
        _CP->K_Attack();
    }
    if (keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW) {
        _CP->stopAllActions();
        _CP->K_RunRight();
    }
    if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW) {
        _CP->stopAllActions();
        _CP->K_RunLeft();
    }
    //-------Quit Game-----
    if (keyCode == EventKeyboard::KeyCode::KEY_X) {
        GameOver();
    }
}


void PlayScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
    //------Player1--------
    if (keyCode == EventKeyboard::KeyCode::KEY_W)
    {
    }
    if (keyCode == EventKeyboard::KeyCode::KEY_S) {
    }
    if (keyCode == EventKeyboard::KeyCode::KEY_D) {
        _hero->stopAllActions();
        _hero->Idle ();
    }
    if (keyCode == EventKeyboard::KeyCode::KEY_A) {
        _hero->stopAllActions();
        _hero->Idle ();
    }
    //-------Player2-------
    if (keyCode == EventKeyboard::KeyCode::KEY_UP_ARROW)
    {
    }
    if (keyCode == EventKeyboard::KeyCode::KEY_DOWN_ARROW) {
    }
    if (keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW) {
        _CP->stopAllActions();
        _CP->K_Idle();
    }
    if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW) {
        _CP->stopAllActions();
        _CP->K_Idle();
    }
    if (keyCode == EventKeyboard::KeyCode::KEY_X) {
        GameOver();
    }
}

void PlayScene::GameOver()
{
    //SimpleAudioEngine::end();
    auto OverScene = GameOver::createscene();
    Director::getInstance()->replaceScene(OverScene);
}
void PlayScene::update(float dt) {
    if (timeRemaining > 0.f) {
        timeRemaining -= dt;
        // update the label or whatever displays the time here. if displaying the number, use ceilf to round
        // up the time remaining so that you don't display lots of numbers after the decimal point
        //labelTime->setString("Time Remaining: " + std::to_string(ceilf(timeRemaining)));
        // check if time ran out
        if (timeRemaining <= 0.f) {
            // timer ran out; react here
        }
    }
}