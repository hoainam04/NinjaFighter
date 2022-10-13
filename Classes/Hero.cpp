#include "Hero.h"
#include "Tag.h"

USING_NS_CC;

bool Hero::init() {


	auto spriteframeCache = SpriteFrameCache::getInstance();
	spriteframeCache->addSpriteFramesWithFile("Hero.plist", "Hero.png");

	_hero = Sprite::createWithSpriteFrameName("Idle1.png");
	_hero->setScale(2);
	_hero->setPosition(Vec2(-10, 0));
	this->addChild(_hero);
	_isAttack = false;

	actionSet();

	initBody();

	this->scheduleUpdate();

	this->setTag(Player1);

	return true;
}

void Hero::initBody() {
	Size bodySize;
	bodySize.width -= 50;
	bodySize.height -= 110;

	auto heroBody = PhysicsBody::createBox(bodySize, PhysicsMaterial(0.0f, 0.0f, 0.0f));

	heroBody->setRotationEnable(false);
	heroBody->setCategoryBitmask(Player1);
	heroBody->setCollisionBitmask(Player1);
	heroBody->setContactTestBitmask(contactTestP1);


	this->setPhysicsBody(heroBody);
}
//void Hero::atkBox() {
//    Size AttackBox;
//    AttackBox.width = 100;
//    AttackBox.height = 50;
//
//    auto AtkBody = PhysicsBody::createBox(AttackBox, PhysicsMaterial(1.0f, 0.0f, 0.0f));
//    AtkBody->setCollisionBitmask(4);
//    AtkBody->setContactTestBitmask(4);
//    AtkBody->setDynamic(false);
//    auto atkNode = Node::create();
//    atkNode->setPosition(Vec2(_hero->getPositionX(), _hero->getPositionY() + 25));
//
//    atkNode->setPhysicsBody(AtkBody);
//    this->addChild(atkNode);
//}

void Hero::actionSet() {

	SpriteFrame* frame = NULL;

	char file[100] = { 0 };

	Vector<SpriteFrame*>frameVector;

	//-----Idle-----
	for (int i = 1; i <= 8; i++) {
		sprintf(file, "Idle%d.png", i);
		frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(file);
		frameVector.pushBack(frame);
	}
	auto idle_animation = Animation::createWithSpriteFrames(frameVector, 0.1f, -1);
	AnimationCache::getInstance()->addAnimation(idle_animation, "idle");
	//-----Run-----
	frameVector.clear();
	for (int i = 1; i <= 6; i++) {
		sprintf(file, "Run%d.png", i);
		frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(file);
		frameVector.pushBack(frame);
	}
	sprintf(file, "Run8.png");
	frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(file);
	frameVector.pushBack(frame);
	auto Run_animation = Animation::createWithSpriteFrames(frameVector, 0.1f, -1);
	AnimationCache::getInstance()->addAnimation(Run_animation, "run");
	//-----Jump----
	frameVector.clear();
	for (int i = 1; i <= 2; i++) {
		sprintf(file, "jump%d.png", i);
		frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(file);
		frameVector.pushBack(frame);
	}
	auto jump_animation = Animation::createWithSpriteFrames(frameVector, 0.1f, -1);
	AnimationCache::getInstance()->addAnimation(jump_animation, "jump");

	//-----fall----
	frameVector.clear();
	for (int i = 1; i <= 2; i++) {
		sprintf(file, "fall%d.png", i);
		frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(file);
		frameVector.pushBack(frame);
	}
	auto fall_animation = Animation::createWithSpriteFrames(frameVector, 0.1f, -1);
	AnimationCache::getInstance()->addAnimation(fall_animation, "fall");

	//*-----takeHit-----
	frameVector.clear();
	for (int i = 1; i <= 3; i++) {
		sprintf(file, "TakeHit%d.png", i);
		frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(file);

		frameVector.pushBack(frame);
	}
	auto take_hit_animation = Animation::createWithSpriteFrames(frameVector, 0.1f);
	AnimationCache::getInstance()->addAnimation(take_hit_animation, "takeHit");

	//-----death-----
	frameVector.clear();
	for (int i = 1; i <= 6; i++) {
		sprintf(file, "death%d.png", i);
		frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(file);
		frameVector.pushBack(frame);
	}
	auto death_animation = Animation::createWithSpriteFrames(frameVector, 0.1f);
	AnimationCache::getInstance()->addAnimation(death_animation, "death");

	//-----Attack-----
	frameVector.clear();
	for (int i = 1; i <= 3; i++) {
		sprintf(file, "attack%d.png", i);
		frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(file);
		frameVector.pushBack(frame);
	}
	for (int i = 5; i <= 6; i++) {
		sprintf(file, "attack%d.png", i);
		frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(file);
		frameVector.pushBack(frame);
	}
	auto atk1_animation = Animation::createWithSpriteFrames(frameVector, 0.1f);
	AnimationCache::getInstance()->addAnimation(atk1_animation, "attack");

}
void Hero::doAction(const char* actionName) {
	auto animation = AnimationCache::getInstance()->getAnimation(actionName);
	auto action = Animate::create(animation);
	_hero->runAction(action);
}

void Hero::Idle() {
	m_state = idle;
	_hero->stopAllActions();
	initBody();
	doAction("idle");
	//this->setPosition(0,0);
}
void Hero::RunRight() {
	if (m_state != attack) {
		m_state = running;
		_hero->stopAllActions();
		initBody();
		auto mass = this->getPhysicsBody()->getMass() * 200;
		this->getPhysicsBody()->applyImpulse(Vect(mass, 0));
		auto finishAction = CallFunc::create([=] {
			this->Idle();
			});
		auto animation = AnimationCache::getInstance()->getAnimation("run");
		auto action = Animate::create(animation);
		_hero->runAction(Sequence::create(action, finishAction, nullptr));
	}
}
void Hero::RunLeft() {
	if (m_state != attack) {
		m_state = running;
		_hero->stopAllActions();
		initBody();
		auto mass = this->getPhysicsBody()->getMass() * 200;

		this->getPhysicsBody()->applyImpulse(Vect(-mass, 0));
		auto finishAction = CallFunc::create([=] {
			this->Idle();
			});
		auto animation = AnimationCache::getInstance()->getAnimation("run");
		auto action = Animate::create(animation);
		_hero->runAction(Sequence::create(action, finishAction, nullptr));
	}
}
void Hero::Jump() {
	if (m_state == idle) {
		m_state = jump;

		auto mass = this->getPhysicsBody()->getMass() * 200;

		this->getPhysicsBody()->applyImpulse(Vect(0, mass));

		_hero->stopAllActions();

		doAction("jump");
	}
}
void Hero::update(float dt) {
	auto vel = this->getPhysicsBody()->getVelocity();
	if (m_state == jump) {
		CCLOG("vel(jump) %f", vel.y);
		if (vel.y < 0.1) {
			m_state = fall;
			_hero->stopAllActions();
			doAction("fall");
		}
	}
	if (m_state == fall) {
		CCLOG("vel(fall) %f", vel.y);
		if (vel.y > 0) {
			_hero->stopAllActions();
			Idle();
		}
	}
}

void Hero::Attack() {
	Size AttackBox;
	AttackBox.width = 150;
	AttackBox.height = 50;

	auto AtkBody = PhysicsBody::createBox(AttackBox, PhysicsMaterial(1.0f, 0.0f, 0.0f));
	AtkBody->setCollisionBitmask(P1Atk);
	AtkBody->setContactTestBitmask(P1Atk);
	AtkBody->setDynamic(false);
	auto atkNode = Node::create();
	atkNode->setPosition(Vec2(_hero->getPositionX() + 110, _hero->getPositionY()));
	atkNode->setPhysicsBody(AtkBody);


	if (m_state == idle || m_state == jump || m_state == fall || m_state == running || m_state == take_hit) {
		m_state = attack;
		_hero->stopAllActions();
		CCLOG("P1 Attack");
		initBody();
		this->addChild(atkNode);
		this->setTag(P1Atk);

		auto finishAction = CallFunc::create([=] {
			this->removeChild(atkNode);
			this->Idle();
			});
		auto animation = AnimationCache::getInstance()->getAnimation("attack");
		auto action = Animate::create(animation);
		_hero->runAction(Sequence::create(action, finishAction, nullptr));

	}
}
void Hero::takeHit() {
	m_state = take_hit;
	hp1 - 10;
	_hero->stopAllActions();
	CCLOG("hero take hit -10HP");
	auto finishAction = CallFunc::create([=] {
		this->Idle();
		});
	auto animation = AnimationCache::getInstance()->getAnimation("takeHit");
	auto action = Animate::create(animation);
	_hero->runAction(Sequence::create(action, finishAction, nullptr));
	//if (0 <= hp1) {
	//	Death();
	//}
}
void Hero::Death() {
	_hero->stopAllActions();
	doAction("death");
}
