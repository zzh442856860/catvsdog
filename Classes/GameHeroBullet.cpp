//
//  GameHeroBullet.cpp
//  MeowStarWars
//
//  Created by blues on 13-11-4.
//
//

#include "GameHeroBullet.h"

GameHeroBullet::GameHeroBullet()
{
    isVisible = false;
}

GameHeroBullet::~GameHeroBullet()
{
}

void GameHeroBullet::setVisible()
{
    this->CCNode::setVisible(true);
    isVisible = true;
    this->runAction(CCSequence::create(CCMoveTo::create((-getPosition().y + 550) / 150, ccp(getPosition().x, 550)),
                                       CCCallFunc::create(this, callfunc_selector(GameHeroBullet::setNotVisible)),
                                       NULL));
}

void GameHeroBullet::setNotVisible()
{
    this->CCNode::setVisible(false);
    isVisible = false;
    this->stopAllActions();
}

bool GameHeroBullet::getVisible()
{
    return isVisible;
}

void GameHeroBullet::onEnter()
{
    CCNode::onEnter();
    this->setContentSize(CCSizeMake(21, 52));
    CCSprite *mainBody = CCSprite::create("YuGuZD.png");
    this->addChild(mainBody);
}

void GameHeroBullet::onExit()
{
    CCNode::onExit();
}
