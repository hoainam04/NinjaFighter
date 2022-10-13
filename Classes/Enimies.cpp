#include "Enimies.h"
#include "Tag.h"

USING_NS_CC;

bool Enimies::init(){
    auto visibleSize = Director::getInstance()->getVisibleSize();


    auto spriteframeCache = SpriteFrameCache::getInstance();
    spriteframeCache->addSpriteFramesWithFile("KenJi.plist", "KenJi.png");

    _CP = Sprite::createWithSpriteFrameName("Nhuns (1).png");
    _CP->setScale(2);
    _CP->setPosition(Vec2(10, 7));
    this->addChild(_CP);

    actionSet();

    initBody();

    this->scheduleUpdate();

    this->setTag(Player2);

    //createCP(visibleSize);

	return true;
}

void Enimies::initBody() {
    Size bodySize;
    bodySize.width -= 50;
    bodySize.height -= 110;

    auto heroBody = PhysicsBody::createBox(bodySize, PhysicsMaterial(1.0f, 0.0f, 0.0f));
    //heroBody->setDynamic(false);
    heroBody->setRotationEnable(false);
    heroBody->setCategoryBitmask(Player2);
    heroBody->setCollisionBitmask(Player2);
    heroBody->setContactTestBitmask(true);

    this->setPhysicsBody(heroBody);
}

void Enimies::actionSet() {

    SpriteFrame* frame = NULL;

    char file[100] = { 0 };

    Vector<SpriteFrame*>frameVector;

    //-----Idle-----
    for (int i = 1; i <= 4; i++) {
        sprintf(file, "Nhuns (%d).png", i);
        frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(file);
        frameVector.pushBack(frame);
    }
    auto idle_animation = Animation::createWithSpriteFrames(frameVector, 0.1f, -1);
    AnimationCache::getInstance()->addAnimation(idle_animation, "idlee");
    //-----Run-----
    frameVector.clear();
    for (int i = 1; i <= 8; i++) {
        sprintf(file, "Runn (%d).png", i);
        frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(file);
        frameVector.pushBack(frame);
    }
    auto Run_animation = Animation::createWithSpriteFrames(frameVector, 0.1f, -1);
    AnimationCache::getInstance()->addAnimation(Run_animation, "runn");
    //-----Jump----
    frameVector.clear();
    for (int i = 1; i <= 2; i++) {
        sprintf(file, "Nhayr (%d).png", i);
        frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(file);
        frameVector.pushBack(frame);
    }
    auto jump_animation = Animation::createWithSpriteFrames(frameVector, 0.1f, -1);
    AnimationCache::getInstance()->addAnimation(jump_animation, "jumpp");

    //-----fall----
    frameVector.clear();
    for (int i = 1; i <= 2; i++) {
        sprintf(file, "Roiw (%d).png", i);
        frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(file);
        frameVector.pushBack(frame);
    }
    auto fall_animation = Animation::createWithSpriteFrames(frameVector, 0.1f, -1);
    AnimationCache::getInstance()->addAnimation(fall_animation, "falll");

    //*-----takeHit-----
    frameVector.clear();
    for (int i = 2; i <= 3; i++) {
        sprintf(file, "Thit (%d).png", i);
        frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(file);

        frameVector.pushBack(frame);
    }
    auto take_hit_animation = Animation::createWithSpriteFrames(frameVector, 0.1f);
    AnimationCache::getInstance()->addAnimation(take_hit_animation, "takeHitt");

    //-----death-----
    frameVector.clear();
    for (int i = 3; i <= 6; i++) {
        sprintf(file, "Die (%d).png", i);
        frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(file);
        frameVector.pushBack(frame);
    }
    auto death_animation = Animation::createWithSpriteFrames(frameVector, 0.1f);
    AnimationCache::getInstance()->addAnimation(death_animation, "deathh");

    //-----Attack-----
    frameVector.clear();
    for (int i = 1; i <= 4; i++) {
        sprintf(file, "ATK_%d.png", i);
        //sprintf(file, "Katk_Crit (%d).png", i);

        frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(file);
        frameVector.pushBack(frame);
    }
    auto atk1_animation = Animation::createWithSpriteFrames(frameVector, 0.1f);
    AnimationCache::getInstance()->addAnimation(atk1_animation, "attackk");
}
void Enimies::doAction(const char* actionName) {
    auto animation = AnimationCache::getInstance()->getAnimation(actionName);
    auto action = Animate::create(animation);
    _CP->runAction(action);
}
void Enimies::K_Idle() {
    k_state = K_idle;
    _CP->stopAllActions();
    initBody();
    doAction("idlee");

}
void Enimies::K_RunRight() {
    k_state = K_running;
    _CP->stopAllActions();
    initBody();
    auto mass = this->getPhysicsBody()->getMass() * 200;

    this->getPhysicsBody()->applyImpulse(Vect(mass, 0));
    auto finishAction = CallFunc::create([=] {
        this->K_Idle();
        });
    auto animation = AnimationCache::getInstance()->getAnimation("runn");
    auto action = Animate::create(animation);
    _CP->runAction(Sequence::create(action, finishAction, nullptr));

}
void Enimies::K_RunLeft() {
    k_state = K_running;
    _CP->stopAllActions();
    initBody();
    auto mass = this->getPhysicsBody()->getMass() * 200;

    this->getPhysicsBody()->applyImpulse(Vect(-mass, 0));
    auto finishAction = CallFunc::create([=] {
        this->K_Idle();
        });
    auto animation = AnimationCache::getInstance()->getAnimation("runn");
    auto action = Animate::create(animation);
    _CP->runAction(Sequence::create(action, finishAction, nullptr));

}
void Enimies::K_Jump() {
    if (k_state == K_idle) {
        k_state = K_jump;

        auto mass = this->getPhysicsBody()->getMass() * 200;

        this->getPhysicsBody()->applyImpulse(Vect(0, mass));

        _CP->stopAllActions();

        doAction("jumpp");
    }
}
void Enimies::update(float dt) {
    auto vel = this->getPhysicsBody()->getVelocity();
    if (k_state == K_jump) {
        if (vel.y < 0.1) {
            k_state = K_fall;
            _CP->stopAllActions();
            doAction("falll");
        }
    }

    if (k_state == K_fall) {
        CCLOG("%f", vel.y);
        if (vel.y > 0) {
           _CP->stopAllActions();
            K_Idle();
        }
    }
}
void Enimies::K_Attack() {
    Size AttackBox;
    AttackBox.width = 140;
    AttackBox.height = 50;

    auto AtkBody = PhysicsBody::createBox(AttackBox, PhysicsMaterial(1.0f, 0.0f, 0.0f));
    AtkBody->setCollisionBitmask(P2Atk);
    AtkBody->setCategoryBitmask(P2Atk);
    AtkBody->setContactTestBitmask(contactTestP2A);
    AtkBody->setDynamic(false);
    auto atkNode = Node::create();
    atkNode->setPosition(Vec2(_CP->getPositionX() - 105, _CP->getPositionY()));
    atkNode->setPhysicsBody(AtkBody);

    //_hero = Hero::create();
    //if (AtkBody->getPosition() == _hero->getPhysicsBody()->getPosition()) {
    //    //_hero->takeHit();
    //}

    if (k_state == K_idle|| k_state == K_jump ||k_state== K_fall) {
        k_state = K_attack;

        _CP->stopAllActions();
        initBody();
        this->addChild(atkNode);
        this->setTag(P2Atk);

        auto finishAction = CallFunc::create([=] {
            this->removeChild(atkNode);
            this->K_Idle();
            });
        auto animation = AnimationCache::getInstance()->getAnimation("attackk");
        auto action = Animate::create(animation);
        _CP->runAction(Sequence::create(action, finishAction, nullptr));

    }
}
void Enimies::K_TakeHit() {
    k_state = K_takeHit;
    //_CP->hp2 - 10;
    initBody();
    _CP->stopAllActions();
    doAction("takeHitt");
    CCLOG("\n PLAYER 2 take hit -10HP \n");
    //if (0 <= hp2) {
    //    K_Death();
    //}
}
void Enimies::K_Death() {
    k_state = K_death;
    _CP->stopAllActions();
    doAction("deathh");
    //_CP->getPhysicsBody()->removeFromWorld();
}
//void update(float dt) {
//
//}


