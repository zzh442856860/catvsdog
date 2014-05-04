//
//  GameObjHero.cpp
//  MeowStarWars
//
//  Created by blues on 13-11-1.
//
//

#include "GameObjHero.h"
#include "GameMain.h"

GameObjHero::GameObjHero()
{
}

GameObjHero::~GameObjHero()
{
    this->unscheduleAllSelectors();
}

void GameObjHero::releaseBullet(float dt)
{
    if (isControlling)
    {
        CCPoint pos = getPosition();
        GameMain *pGameMain = (GameMain *)this->getParent();
        pGameMain->releaseHeroBullet(pos.x, pos.y + 30);
    }
}

CCRect GameObjHero::rect()
{
    CCSize s = CCSizeMake(85, 90);
    return CCRectMake(-s.width / 2, -s.height / 2, s.width, s.height);
}

void GameObjHero::onEnter()
{
    CCNode::onEnter();
    this->setContentSize(CCSizeMake(85, 90));
    CCDirector *pDirector = CCDirector::sharedDirector();
    pDirector->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
    
   
    CCSprite *mainSprite = CCSprite::create("catBody1.png");
    CCAnimation *animation = CCAnimation::create();
    animation->addSpriteFrameWithFileName("catBody1.png");
    animation->addSpriteFrameWithFileName("catBody2-4.png");
    animation->addSpriteFrameWithFileName("catBody3.png");
    animation->addSpriteFrameWithFileName("catBody2-4.png");
    animation->setDelayPerUnit(0.1f);
    animation->setRestoreOriginalFrame(true);
    mainSprite->runAction(CCRepeatForever::create(CCAnimate::create(animation)));
    this->addChild(mainSprite);
    
    CCSprite *tail = CCSprite::create("catTail.png");
    tail->setAnchorPoint(ccp(0.5, 1));
    tail->setPosition(ccp(-5, -29));
    tail->setScale(0.5f);
    tail->setRotation(20);
    tail->runAction(CCRepeatForever::create(CCSequence::create(CCRotateBy::create(0.5f, -40),
                                                               CCRotateBy::create(0.5f, 40),
                                                               NULL)));
    this->addChild(tail);
   
    leftHand = CCSprite::create("catHand1.png");
    leftHand->setAnchorPoint(ccp(1, 0.5));
    leftHand->setPosition(ccp(-18, -20));
    this->addChild(leftHand);
    rightHand = CCSprite::create("catHand2.png");
    rightHand->setAnchorPoint(ccp(0, 0.5));
    rightHand->setPosition(ccp(18, -20));
    this->addChild(rightHand);
    
    offset = ccp(0, 0);
    isControlling = false;
    this->schedule(schedule_selector(GameObjHero::releaseBullet), 1.0f);
}

void GameObjHero::onExit()
{
    CCDirector* pDirector = CCDirector::sharedDirector();
    pDirector->getTouchDispatcher()->removeDelegate(this);
    CCNode::onExit();
}

bool GameObjHero::containsTouchLocation(CCTouch *touch)
{
    return rect().containsPoint(convertTouchToNodeSpaceAR(touch));
}

bool GameObjHero::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    if (((GameMain *)this->getParent())->isOver)
        return false;
    if (!containsTouchLocation(pTouch))
    {
        return false;
    }
    else
    {
        isControlling = true;
        CCPoint touchPoint = pTouch->getLocationInView();
        touchPoint = CCDirector::sharedDirector()->convertToGL(touchPoint);
        offset.x = touchPoint.x - getPosition().x;
        offset.y = touchPoint.y - getPosition().y;
    }
    return true;
}

void GameObjHero::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
    if (isControlling)
    {
        CCPoint touchPoint = pTouch->getLocationInView();
        touchPoint = CCDirector::sharedDirector()->convertToGL(touchPoint);
   
        float x = touchPoint.x - offset.x;
        float y = touchPoint.y - offset.y;
        if (x < getPosition().x)
        {
            leftHand->setFlipY(true);
            rightHand->setFlipY(false);
        }
        else
        {
            leftHand->setFlipY(false);
            rightHand->setFlipY(true);
        }
        this->setPosition(x, y);
    }
}

void GameObjHero::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
    if (isControlling)
    {
        isControlling = false;
        leftHand->setFlipY(false);
        rightHand->setFlipY(false);
    }
}

void GameObjHero::touchDelegateRetain()
{
    this->retain();
}

void GameObjHero::touchDelegateRelease()
{
    this->release();
}
