//
//  GameMenu.cpp
//  MeowStarWars
//
//  Created by blues on 13-11-22.
//
//

#include "GameMenu.h"
#include "GameAbout.h"
#include "GameMain.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;

GameMenu::GameMenu()
{
}

GameMenu::~GameMenu()
{
}

CCScene* GameMenu::scene()
{
    CCScene *scene = CCScene::create();
    GameMenu *layer = GameMenu::create();
    scene->addChild(layer);
    
    return scene;
}

bool GameMenu::init()
{
    if (!CCLayer::init()) {
        return false;
    }
    
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
  
    CCSprite *bg = CCSprite::create("bg.png");
    bg->setScale(0.5f);
    bg->setPosition(ccp(size.width / 2, size.height / 2));
    this->addChild(bg, 0, 0);
    
   
    CCSprite *bgStar = CCSprite::create("moon.png");
    bgStar->setAnchorPoint(ccp(0.5, 0));
    bgStar->setScale(0.5);
    bgStar->setPosition(ccp(size.width / 3 * 2, 0));
    this->addChild(bgStar, 1, 1);
    
   
    CCNode *title = CCNode::create();
    title->setContentSize(CCSizeMake(size.width - 40, 50));
    
    CCSprite *ptmLabel = CCSprite::create("meowstar.png");
    ptmLabel->setPosition(ccp(0, 30));
    ptmLabel->setScale(0.5f);
    title->addChild(ptmLabel);
    
    CCSprite *ptbLabel = CCSprite::create("battle.png");
    ptbLabel->setPosition(ccp(0, -30));
    ptbLabel->setScale(0.5f);
    title->addChild(ptbLabel);
    
    title->setPosition(ccp(size.width / 2, size.height - 80));
    this->addChild(title, 2, 2);
    

    CCMenuItemImage *newGameItem = CCMenuItemImage::create("newgameA.png",
                                                           "newgameB.png",
                                                           this,
                                                           menu_selector(GameMenu::menuNewGameCallback));
    newGameItem->setPosition(ccp(size.width / 2, size.height / 2 - 20));
    newGameItem->setScale(0.5f);
    newGameItem->setEnabled(false);
    
    CCMenuItemImage *continueItem = CCMenuItemImage::create("continueA.png",
                                                            "continueB.png",
                                                            this,
                                                            menu_selector(GameMenu::menuContinueCallback));
    continueItem->setPosition(ccp(size.width / 2, size.height / 2 - 80));
    continueItem->setScale(0.5f);
    continueItem->setEnabled(false);
    
    CCMenuItemImage *aboutItem = CCMenuItemImage::create("aboutA.png",
                                                         "aboutB.png",
                                                         this,
                                                         menu_selector(GameMenu::menuAboutCallback));
    aboutItem->setPosition(ccp(size.width / 2, size.height / 2 - 140));
    aboutItem->setScale(0.5f);
    aboutItem->setEnabled(false);
    
    soundItem = CCMenuItemImage::create("sound-on-A.png",
                                        "sound-on-B.png",
                                        this,
                                        menu_selector(GameMenu::menuSoundCallback));
    soundItem->setPosition(ccp(40, 40));
    soundItem->setScale(0.5f);
    soundItem->setEnabled(false);
    
  
    CCMenu *mainMenu = CCMenu::create(newGameItem, continueItem, aboutItem, soundItem, NULL);
    mainMenu->setPosition(ccp(0, 0));
    this->addChild(mainMenu, 1, 3);
    
    
    isSound = true;
    SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic(CCFileUtils::sharedFileUtils()->fullPathForFilename("background.mp3").c_str());
    SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(0.5);
    SimpleAudioEngine::sharedEngine()->playBackgroundMusic(CCFileUtils::sharedFileUtils()->fullPathForFilename("background.mp3").c_str(), true);
    
    return true;
}

void GameMenu::onEnter()
{
    CCLayer::onEnter();
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    CCNode *mainMenu = this->getChildByTag(3);
    mainMenu->setPositionX(-200);
    mainMenu->runAction(CCSequence::create(CCEaseElasticIn::create(CCMoveTo::create(1.5f, ccp(0, 0))), CCCallFunc::create(this, callfunc_selector(GameMenu::menuEnter)), NULL));
    
    CCNode *title = this->getChildByTag(2);
    title->setPositionY(size.height + 20);
    title->runAction(CCEaseElasticIn::create(CCMoveBy::create(1.5f, ccp(0, -100))));
    
    CCNode *bgStar = this->getChildByTag(1);
    bgStar->setPositionX(size.width / 3);
    bgStar->runAction(CCMoveBy::create(1.5f, ccp(size.width / 3, 0)));
}

void GameMenu::onExit()
{
    CCLayer::onExit();
}

void GameMenu::menuEnter()
{
    CCNode *mainMenu = this->getChildByTag(3);
    CCArray *temp = mainMenu->getChildren();
    for (int i = 0; i < temp->count(); i++) {
        ((CCMenuItemImage *)temp->objectAtIndex(i))->setEnabled(true);
    }
}

void GameMenu::menuNewGameCallback(CCObject *pSender)
{
    CCDirector::sharedDirector()->replaceScene(GameMain::scene());
}

void GameMenu::menuContinueCallback(CCObject *pSender)
{
    CCDirector::sharedDirector()->replaceScene(GameMain::scene());
}

void GameMenu::menuAboutCallback(CCObject *pSender)
{
    CCDirector::sharedDirector()->replaceScene(GameAbout::scene());
}

void GameMenu::menuSoundCallback(CCObject *pSender)
{
    if (!isSound) {
        isSound = true;
        soundItem->setNormalImage(CCSprite::create("sound-on-A.png"));
        soundItem->setDisabledImage(CCSprite::create("sound-on-B.png"));
        SimpleAudioEngine::sharedEngine()->playBackgroundMusic(CCFileUtils::sharedFileUtils()->fullPathForFilename("background.mp3").c_str(), true);
    } else {
        isSound = false;
        soundItem->setNormalImage(CCSprite::create("sound-off-A.png"));
        soundItem->setDisabledImage(CCSprite::create("sound-off-B.png"));
        SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
    }
}
