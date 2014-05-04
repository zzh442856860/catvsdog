//
//  GameMark.cpp
//  MeowStarWars
//
//  Created by blues on 13-11-5.
//
//

#include "GameMark.h"

GameMark::GameMark()
{
}

GameMark::~GameMark()
{
}

void GameMark::onEnter()
{
    CCNode::onEnter();
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    this->setContentSize(size);
    
    CCSprite *title = CCSprite::create("score.png");
    title->setPosition(ccp(size.width / 2 + 40, size.height - 15));
    title->setScale(0.5f);
    this->addChild(title);
    
    digits = CCArray::createWithCapacity(5);
    for (int i = 0; i < 5; i++)
    {
        CCSprite *shu = CCSprite::create("shu.png");
        texture = shu->getTexture();
        shu->setScale(0.5f);
        shu->setTextureRect(CCRectMake(234, 0, 26, 31));
        shu->setPosition(ccp(size.width - 15 - i*15, size.height - 15));
        digits->addObject(shu);
        this->addChild(shu);
    }
    digits->retain();
    
    mark = 0;
}

void GameMark::onExit()
{
    CCNode::onExit();
}

void GameMark::addNumber(int var)
{
    mark += var;
    if (mark >= 100 && mark <= 900)
    {
        int temp = mark/100;
        ((CCSprite *)digits->objectAtIndex(2))->setTexture(texture);
        ((CCSprite *)digits->objectAtIndex(2))->setTextureRect(CCRectMake((temp - 1)*26, 0, 26, 31));
    }
    else if(mark >= 1000 && mark <= 9900)
    {
        int tempOne = mark/1000;
        ((CCSprite *)digits->objectAtIndex(3))->setTexture(texture);
        ((CCSprite *)digits->objectAtIndex(3))->setTextureRect(CCRectMake((tempOne - 1)*26, 0, 26, 31));
        
        int tempTwo = ((double)mark/1000 - tempOne) * 10;
        ((CCSprite *)digits->objectAtIndex(2))->setTexture(texture);
        if (tempTwo == 0) {
            ((CCSprite *)digits->objectAtIndex(2))->setTextureRect(CCRectMake(234, 0, 26, 31));
        } else {
            ((CCSprite *)digits->objectAtIndex(2))->setTextureRect(CCRectMake((tempTwo - 1)*26, 0, 26, 31));
        }
    }
    else if(mark >= 10000 && mark <=99900)
    {
        int tempOne = mark/10000;
        ((CCSprite *)digits->objectAtIndex(4))->setTexture(texture);
        ((CCSprite *)digits->objectAtIndex(4))->setTextureRect(CCRectMake((tempOne - 1)*26, 0, 26, 31));
        
        int tempTwo = ((double)mark/10000 - tempOne) * 10;
        ((CCSprite *)digits->objectAtIndex(3))->setTexture(texture);
        if (tempTwo == 0) {
            ((CCSprite *)digits->objectAtIndex(3))->setTextureRect(CCRectMake(234, 0, 26, 31));
        } else {
            ((CCSprite *)digits->objectAtIndex(3))->setTextureRect(CCRectMake((tempTwo - 1)*26, 0, 26, 31));
        }
        
        int tempThree = ((((double)mark/10000 - tempOne) * 10) - tempTwo) * 10;
        ((CCSprite *)digits->objectAtIndex(2))->setTexture(texture);
        if (tempThree == 0) {
            ((CCSprite *)digits->objectAtIndex(2))->setTextureRect(CCRectMake(234, 0, 26, 31));
        } else {
            ((CCSprite *)digits->objectAtIndex(2))->setTextureRect(CCRectMake((tempThree - 1)*26, 0, 26, 31));
        }
    }
    else
    {
    }
}
