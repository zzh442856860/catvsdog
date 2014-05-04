//
//  GameObjEnemy.h
//  MeowStarWars
//
//  Created by blues on 13-11-4.
//
//

#ifndef __MeowStarWars__GameObjEnemy__
#define __MeowStarWars__GameObjEnemy__

#include "cocos2d.h"

USING_NS_CC;

class GameObjEnemy : public CCNode
{
public:
    CCSprite *mainBody;
    CCSprite *boom;
    short    type;
    bool     isLife;
    
    GameObjEnemy();
    virtual ~GameObjEnemy();
    void releaseBullet(float dt);
    virtual void onEnter();
    virtual void onExit();
    void moveStart();
    void restart();
    void setDie();
    void setType(short var);
};

#endif /* defined(__MeowStarWars__GameObjEnemy__) */
