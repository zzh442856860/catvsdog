//
//  GameEnemyBullet.h
//  MeowStarWars
//
//  Created by blues on 13-11-4.
//
//

#ifndef __MeowStarWars__GameEnemyBullet__
#define __MeowStarWars__GameEnemyBullet__

#include "cocos2d.h"

using namespace cocos2d;

class GameEnemyBullet : public CCNode
{
public:
    bool isVisible;
    
    GameEnemyBullet();
    virtual ~GameEnemyBullet();
    void setVisible();
    void setNotVisible();
    bool getVisible();
    virtual void onEnter();
    virtual void onExit();
};

#endif /* defined(__MeowStarWars__GameEnemyBullet__) */
