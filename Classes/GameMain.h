//
//  GameMain.h
//  MeowStarWars
//
//  Created by blues on 13-11-4.
//
//

#ifndef __MeowStarWars__GameMain__
#define __MeowStarWars__GameMain__

#include "cocos2d.h"
#include "GameObjHero.h"
#include "GameObjEnemy.h"
#include "GameMark.h"

USING_NS_CC;

class GameMain : public CCLayer
{
public:
    CREATE_FUNC(GameMain);
    static CCScene *scene();
    virtual bool init();
    virtual void update(float time);
    void menuBackCallback(CCObject* pSender);
    void setOver();
    void releaseHeroBullet(int x, int y);
    void releaseEnemyBullet(int x, int y);
    bool isCollision(CCPoint p1, CCPoint p2, int w1, int h1, int w2, int h2);
    void setHeroHurt();
    void resetReduce(float dt);
    
    static GameMain sGameMain;
    CCSprite        *bg1;
    CCSprite        *bg2;
    CCSprite        *blood1;
    CCSprite        *blood2;
    CCSprite        *blood3;
    short           blood;
    CCArray         *heroBullets;
    CCArray         *enemyBullets;
    bool            isReduce;
    bool            isOver;
    GameObjHero     *hero;
    CCSprite        *gameOver;
    CCArray         *enemys;
    GameMark        *gameMark;
};

#endif /* defined(__MeowStarWars__GameMain__) */
