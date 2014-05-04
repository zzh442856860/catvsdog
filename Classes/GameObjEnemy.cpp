//
//  GameObjEnemy.cpp
//  MeowStarWars
//
//  Created by blues on 13-11-4.
//
//

#include "GameObjEnemy.h"
#include "GameMain.h"

GameObjEnemy::GameObjEnemy()
{
}

GameObjEnemy::~GameObjEnemy()
{
}

void GameObjEnemy::releaseBullet(float dt)
{
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    CCPoint pos = this->getPosition();
    if (pos.y > 20 && pos.y < size.height && isLife)
    {
        GameMain *p = (GameMain *)this->getParent();
        p->releaseEnemyBullet(pos.x, pos.y - 30);
    }
}

void GameObjEnemy::onEnter()
{
    CCNode::onEnter();
    this->setContentSize(CCSizeMake(99, 111));
    
    mainBody = CCSprite::create("DrDog1.png");
    CCAnimation *animation = CCAnimation::create();
    animation->addSpriteFrameWithFileName("DrDog1.png");
    animation->addSpriteFrameWithFileName("DrDog2.png");
    animation->setDelayPerUnit(0.1f);
    animation->setRestoreOriginalFrame(true);
    mainBody->runAction(CCRepeatForever::create(CCAnimate::create(animation)));
    this->addChild(mainBody);
    
    boom = CCSprite::create("boom1.png");
    this->addChild(boom);
    boom->setVisible(false);
    
    isLife = true;
}

void GameObjEnemy::onExit()
{
    CCNode::onExit();
}

void GameObjEnemy::moveStart()
{
    isLife = true;
    int type = CCRANDOM_0_1() * 4;
  
    ccBezierConfig bezier2;
    bezier2.controlPoint_1 = CCPointMake(this->getPosition().x - 400, 330);
    bezier2.controlPoint_2 = CCPointMake(this->getPosition().x + 400, 280);
    bezier2.endPosition = CCPointMake(this->getPosition().x, -70);
    CCBezierTo *bezierBy2 = CCBezierTo::create(6.0f, bezier2);
    
    ccBezierConfig bezier1;
    bezier1.controlPoint_1 = CCPointMake(this->getPosition().x + 400, 330);
    bezier1.controlPoint_2 = CCPointMake(this->getPosition().x - 400, 280);
    bezier1.endPosition = CCPointMake(this->getPosition().x, -70);
    CCBezierTo *bezierBy1 = CCBezierTo::create(6.0f, bezier1);
    
    switch (type)
    {
        case 0:
        case 1:
            this->runAction(CCSequence::create(CCMoveBy::create(6.0f, ccp(0, -600)), CCCallFunc::create(this, callfunc_selector(GameObjEnemy::restart)), NULL));
            break;
            
        case 2:
            this->runAction(CCSequence::create(bezierBy2, CCCallFunc::create(this, callfunc_selector(GameObjEnemy::restart)), NULL));
            break;
            
        case 3:
            this->runAction(CCSequence::create(bezierBy1, CCCallFunc::create(this, callfunc_selector(GameObjEnemy::restart)), NULL));
            break;
            
        default:
            break;
    }
    schedule(schedule_selector(GameObjEnemy::releaseBullet), 1.2f);
}

void GameObjEnemy::restart()
{
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    this->setPosition(ccp(size.width / 4 * type, size.height + 50));
    isLife = true;
    mainBody->setVisible(true);
    boom->setVisible(false);
    moveStart();
}

void GameObjEnemy::setDie()
{
    isLife = false;
    mainBody->setVisible(false);
    boom->setVisible(true);
    this->stopAllActions();
    
    CCAnimation *boomAnimation = CCAnimation::create();
    boomAnimation->addSpriteFrameWithFileName("boom1.png");
    boomAnimation->addSpriteFrameWithFileName("boom2.png");
    boomAnimation->addSpriteFrameWithFileName("boom3.png");
    boomAnimation->addSpriteFrameWithFileName("boom4.png");
    boomAnimation->addSpriteFrameWithFileName("boom5.png");
    boomAnimation->setDelayPerUnit(0.1f);
    boomAnimation->setRestoreOriginalFrame(true);
    
    boom->runAction(CCSequence::create(CCAnimate::create(boomAnimation),
                                       CCCallFunc::create(this, callfunc_selector(GameObjEnemy::restart)),
                                       NULL));
}

void GameObjEnemy::setType(short var)
{
    type = var;
}
