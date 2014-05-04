//
//  GameAbout.h
//  MeowStarWars
//
//  Created by blues on 13-11-22.
//
//

#ifndef __MeowStarWars__GameAbout__
#define __MeowStarWars__GameAbout__

#include "cocos2d.h"

USING_NS_CC;

class GameAbout : public CCLayer
{
public:
    CREATE_FUNC(GameAbout);
    static CCScene* scene();
    virtual bool init();
    virtual void onEnter();
    virtual void onExit();
    void menuBackCallback(CCObject *pSender);
    void menuEnter();
};

#endif /* defined(__MeowStarWars__GameAbout__) */
