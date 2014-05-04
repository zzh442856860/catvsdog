//
//  GameHeroBullet.h
//  MeowStarWars
//
//  Created by blues on 13-11-4.
//
//

#ifndef __MeowStarWars__GameHeroBullet__
#define __MeowStarWars__GameHeroBullet__

#include "cocos2d.h"

using namespace cocos2d;

class GameHeroBullet : public CCNode
{
public:
    bool isVisible;
    
    GameHeroBullet();
    virtual ~GameHeroBullet();
    void setVisible();
    void setNotVisible();
    bool getVisible();
    virtual void onEnter();
    virtual void onExit();
};

#endif /* defined(__MeowStarWars__GameHeroBullet__) */
