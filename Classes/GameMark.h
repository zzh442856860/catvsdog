//
//  GameMark.h
//  MeowStarWars
//
//  Created by blues on 13-11-5.
//
//

#ifndef __MeowStarWars__GameMark__
#define __MeowStarWars__GameMark__

#include "cocos2d.h"

using namespace cocos2d;

class GameMark : public CCNode
{
public:
    GameMark(void);
    virtual ~GameMark(void);
    virtual void onEnter();
    virtual void onExit();
    void addNumber(int var);
    
    int         mark;
    CCArray     *digits;
    CCTexture2D *texture;
};

#endif /* defined(__MeowStarWars__GameMark__) */
