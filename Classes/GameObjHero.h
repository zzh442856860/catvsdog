//
//  GameObjHero.h
//  MeowStarWars
//
//  Created by blues on 13-11-1.
//
//

#ifndef __MeowStarWars__GameObjHero__
#define __MeowStarWars__GameObjHero__

#include "cocos2d.h"

using namespace cocos2d;

class GameObjHero : public CCNode, public CCTargetedTouchDelegate
{
public:
    CCSprite *leftHand;    
    CCSprite *rightHand;    
    CCPoint  offset;       
    bool     isControlling;
    
    GameObjHero();
    virtual ~GameObjHero();
    void releaseBullet(float dt);   
    CCRect rect();
    virtual void onEnter();
    virtual void onExit();
    
   
    bool containsTouchLocation(CCTouch *touch);
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    
    virtual void touchDelegateRetain();
    virtual void touchDelegateRelease();
};

#endif /* defined(__MeowStarWars__GameObjHero__) */
