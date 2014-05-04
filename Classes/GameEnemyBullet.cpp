//
//  GameEnemyBullet.cpp
//  MeowStarWars
//
//  Created by blues on 13-11-4.
//
//

#include "GameEnemyBullet.h"

GameEnemyBullet::GameEnemyBullet()
{
    isVisible = false;
}

GameEnemyBullet::~GameEnemyBullet()
{
}

void GameEnemyBullet::setVisible()
{
    CCNode::setVisible(true);
    isVisible = true;
    this->runAction(CCRepeatForever::create(CCRotateBy::create(1.0f, 360)));
    this->runAction(CCSequence::create(CCMoveTo::create((getPosition().y + 50) / 150,
                                                        ccp(getPosition().x, -50)),
                                       CCCallFunc::create(this, callfunc_selector(GameEnemyBullet::setNotVisible)),
                                       NULL));
}

void GameEnemyBullet::setNotVisible()
{
    CCNode::setVisible(false);
    isVisible = false;
    this->stopAllActions();
}

bool GameEnemyBullet::getVisible()
{
    return isVisible;
}

void GameEnemyBullet::onEnter()
{
    CCNode::onEnter();
    this->setContentSize(CCSizeMake(21, 52));
    CCSprite *mainBody = CCSprite::create("DrDogZD.png");
    mainBody->runAction(CCRepeatForever::create(CCRotateBy::create(1.0f, 360)));
    this->addChild(mainBody);
}

void GameEnemyBullet::onExit()
{
    CCNode::onExit();
}
