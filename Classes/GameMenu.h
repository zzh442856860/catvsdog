//
//  GameMenu.h
//  MeowStarWars
//
//  Created by blues on 13-11-22.
//
//

#ifndef __MeowStarWars__GameMenu__
#define __MeowStarWars__GameMenu__

#include "cocos2d.h"

USING_NS_CC;

class GameMenu : public CCLayer
{
public:
    bool isSound;
    CCMenuItemImage *soundItem;
    
    GameMenu();
    virtual ~GameMenu();
    CREATE_FUNC(GameMenu);
    static CCScene* scene();
    virtual bool init();
    virtual void onEnter();
    virtual void onExit();
    void menuEnter();
    void menuNewGameCallback(CCObject *pSender);
    void menuContinueCallback(CCObject *pSender);
    void menuAboutCallback(CCObject *pSender);
    void menuSoundCallback(CCObject *pSender);
};

#endif /* defined(__MeowStarWars__GameMenu__) */
