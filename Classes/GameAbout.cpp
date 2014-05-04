//
//  GameAbout.cpp
//  MeowStarWars
//
//  Created by blues on 13-11-22.
//
//

#include "GameAbout.h"
#include "GameMenu.h"

CCScene* GameAbout::scene()
{
    CCScene *scene = CCScene::create();
    GameAbout *layer = GameAbout::create();
    scene->addChild(layer);
    
    return scene;
}

bool GameAbout::init()
{
    if (!CCLayer::init()) {
        return false;
    }
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
  
    CCSprite *bg = CCSprite::create("bg.png");
    bg->setPosition(ccp(size.width/2, size.height/2));
    bg->setScale(0.5f);
    this->addChild(bg, 0, 0);
    
   
    CCSprite *bgStar = CCSprite::create("moon.png");
    bgStar->setAnchorPoint(ccp(0.5, 0));
    bgStar->setPosition(ccp(size.width/3, 0));
    bgStar->setScale(0.5f);
    this->addChild(bgStar, 1, 1);
    
   
    CCSprite *frame = CCSprite::create("tb.png");
    frame->setPosition(ccp(size.width/2, size.height/2));
    frame->setScale(0.5f);
    this->addChild(frame, 2, 2);
    
    char info[256];
    sprintf(info, "name: meow war\n\nprogram: aiyiai\n\nart design: wa wa\n\ncompany: xi an men\n\n     powered by cocos2d-x");
    CCLabelTTF *label = CCLabelTTF::create(info, "Marker Felt", 40, CCSizeMake(400, 400), kCCTextAlignmentLeft);
    label->setAnchorPoint(ccp(0, 1));
    label->setPosition(ccp(50, 600));
    label->setColor(ccc3(200, 200, 200));
    frame->addChild(label);
    

    CCSprite *aboutTitle = CCSprite::create("about.png");
    aboutTitle->setPosition(ccp(size.width/2, size.height - 20));
    aboutTitle->setScale(0.5f);
    this->addChild(aboutTitle, 3, 3);
    
  
    CCMenuItemImage *backItem = CCMenuItemImage::create("backA.png", "backB.png", this, menu_selector(GameAbout::menuBackCallback));
    backItem->setPosition(ccp(size.width - 20, size.height - 20));
    backItem->setScale(0.5f);
    backItem->setEnabled(false);
    
    CCMenu *mainMenu = CCMenu::create(backItem, NULL);
    mainMenu->setPosition(CCPointZero);
    this->addChild(mainMenu, 3, 4);
    
    return true;
}

void GameAbout::onEnter()
{
    CCLayer::onEnter();
    
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    CCNode *mainMenu = this->getChildByTag(4);
    mainMenu->setPositionX(-100);
    mainMenu->runAction(CCSequence::create(CCEaseElasticIn::create(CCMoveBy::create(1.5f, ccp(100, 0))),
                                           CCCallFunc::create(this, callfunc_selector(GameAbout::menuEnter)),
                                           NULL));
    
    CCNode *aboutTitle = this->getChildByTag(3);
    aboutTitle->setPositionY(size.height + 20);
    aboutTitle->runAction(CCEaseElasticIn::create(CCMoveBy::create(1.5f, ccp(0, -40))));
    
    CCNode *frame = this->getChildByTag(2);
    frame->setPositionX(-200);
    frame->runAction(CCEaseElasticIn::create(CCMoveTo::create(1.5f, ccp(size.width/2, size.height/2))));
    
    CCNode *bgStar = this->getChildByTag(1);
    bgStar->setPositionX(size.width/3 * 2);
    bgStar->runAction(CCMoveBy::create(1.5f, ccp(-size.width/3, 0)));
}

void GameAbout::onExit()
{
    CCLayer::onExit();
}

void GameAbout::menuBackCallback(CCObject *pSender)
{
    CCDirector::sharedDirector()->replaceScene(GameMenu::scene());
}

void GameAbout::menuEnter()
{
    CCNode *mainMenu = this->getChildByTag(4);
    CCArray *temp = mainMenu->getChildren();
    ((CCMenuItemImage *)temp->objectAtIndex(0))->setEnabled(true);
}
