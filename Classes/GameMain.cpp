//
//  GameMain.cpp
//  MeowStarWars
//
//  Created by blues on 13-11-4.
//
//

#include "GameMain.h"
#include "GameMenu.h"
#include "GameHeroBullet.h"
#include "GameEnemyBullet.h"

CCScene* GameMain::scene()
{
    CCScene *scene = CCScene::create();
    GameMain *layer = GameMain::create();
    scene->addChild(layer);
    return scene;
}

bool GameMain::init()
{
    if (!CCLayer::init())
        return false;
    
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    bg1 = CCSprite::create("bg.png");
    bg1->setScale(0.5f);
    bg1->setAnchorPoint(CCPointZero);
    bg1->setPosition(CCPointZero);
    this->addChild(bg1, 0);
    
    bg2 = CCSprite::create("bg.png");
    bg2->setScale(0.5f);
    bg2->setAnchorPoint(CCPointZero);
    bg2->setPosition(ccp(0, size.height));//搞了两个连接起来
    this->addChild(bg2, 0);
    
    hero = new GameObjHero();
    hero->setPosition(ccp(size.width / 2, -50));
    hero->setScale(0.5f);
    this->addChild(hero, 2, 1);//init里直接就runAction了。前面的都是在onEnter里面做的
    hero->runAction(CCMoveBy::create(0.5f, ccp(0, 150)));
    
    enemys = CCArray::createWithCapacity(3);
    for (int i = 0; i < 3; i++)
    {
        int type = i + 1;
        GameObjEnemy *enemy = new GameObjEnemy();
        enemy->setPosition(ccp(size.width/4 * type, size.height + 50));
        enemy->setScale(0.5f);
        enemy->setType(type);
        enemys->addObject(enemy);
        this->addChild(enemy, 1);
        enemy->moveStart();
    }
    enemys->retain();//为何都要retain，目的是什么
    
    blood = 3;//就一个猫，还用批处理？
    CCSpriteBatchNode *ui = CCSpriteBatchNode::create("cat.png");
    
    blood1 = CCSprite::createWithTexture(ui->getTexture());
    blood1->setPosition(ccp(20, size.height - 20));
    blood1->setScale(0.2f);
    ui->addChild(blood1);
    
    blood2 = CCSprite::createWithTexture(ui->getTexture());
    blood2->setPosition(ccp(50, size.height - 20));
    blood2->setScale(0.2f);
    ui->addChild(blood2);
    
    blood3 = CCSprite::createWithTexture(ui->getTexture());
    blood3->setPosition(ccp(80, size.height - 20));
    blood3->setScale(0.2f);
    ui->addChild(blood3);
    
    this->addChild(ui, 4);
    
    heroBullets = CCArray::createWithCapacity(5);
    for (int i = 0; i < heroBullets->capacity(); i++)
    {
        GameHeroBullet *bullet = new GameHeroBullet();
        bullet->setNotVisible();
        bullet->setScale(0.5f);
        heroBullets->addObject(bullet);
        this->addChild(bullet, 3);
    }
    heroBullets->retain();
    
    enemyBullets = CCArray::createWithCapacity(10);
    for (int i = 0; i < enemyBullets->capacity(); i++)
    {
        GameEnemyBullet *bullet = new GameEnemyBullet();
        bullet->setNotVisible();
        bullet->setScale(0.5f);
        enemyBullets->addObject(bullet);
        this->addChild(bullet, 3);
    }
    enemyBullets->retain();
    
    gameMark = new GameMark();
    this->addChild(gameMark, 4);
    
    gameOver = CCSprite::create("gameover.png");
    gameOver->setPosition(ccp(size.width/2, size.height/2 + 70));
    gameOver->setVisible(false);
    gameOver->setScale(0.5f);
    this->addChild(gameOver, 5);
    
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create("back.png",
                                                          "back.png",
                                                          this,
                                                          menu_selector(GameMain::menuBackCallback));
    pCloseItem->setPosition(ccp(size.width/2, size.height/2 - 50));
    pCloseItem->setScale(0.5f);
    CCMenu *pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 5, 25);
    pMenu->setVisible(false);
    pMenu->setEnabled(false);
    isReduce = false;
    isOver = false;
    scheduleUpdate();
    
    return true;
}

void GameMain::update(float time)
{
    bg1->setPosition(ccp(bg1->getPosition().x, bg1->getPosition().y - 2));
    bg2->setPosition(ccp(bg2->getPosition().x, bg2->getPosition().y - 2));
    if (bg2->getPosition().y < 0)
    {
        float temp = bg2->getPosition().y + 480;
        bg1->setPosition(ccp(bg2->getPosition().x, temp));
    }
    if (bg1->getPosition().y < 0)
    {
        float temp = bg1->getPosition().y + 480;
        bg2->setPosition(ccp(bg1->getPosition().x, temp));
    }
    
    CCPoint heroPos = hero->getPosition();
    for (int i = 0; i < 3; i++)
    {
        GameObjEnemy *enemy = (GameObjEnemy *)enemys->objectAtIndex(i);
        CCPoint enemyPos = enemy->getPosition();
        if (enemy->isLife)
        {
            for (int i = 0; i < heroBullets->capacity(); i++)
            {
                if (((GameHeroBullet *)heroBullets->objectAtIndex(i))->getVisible())
                {
                    if (isCollision(((GameHeroBullet *)heroBullets->objectAtIndex(i))->getPosition(), enemyPos, 5, 13, 21, 28))
                    {
                        enemy->setDie();
                        gameMark->addNumber(100);
                        break;
                    }
                }
            }
        }
        if (!isReduce && enemy->isLife && isCollision(heroPos, enemyPos, 21, 22.5, 21, 28))
        {
            enemy->setDie();
            gameMark->addNumber(100);
            setHeroHurt();
        }
    }
    if (!isReduce)
    {
        for (int i = 0; i < enemyBullets->capacity(); i++)
        {
            if (((GameEnemyBullet *)enemyBullets->objectAtIndex(i))->getVisible()
                && isCollision(heroPos, ((GameEnemyBullet *)enemyBullets->objectAtIndex(i))->getPosition(), 21, 22.5, 5, 13))
                setHeroHurt();
        }
    }
}

void GameMain::menuBackCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->replaceScene(GameMenu::scene());
}

void GameMain::setOver()
{
    CCMenu *pMenu = (CCMenu *)this->getChildByTag(25);
    pMenu->setVisible(true);
    pMenu->setEnabled(true);
    pMenu->setScale(0.0f);
    gameOver->setVisible(true);
    gameOver->setScale(0.0f);
    pMenu->runAction(CCScaleTo::create(0.5f, 1.0f));
    gameOver->runAction(CCScaleTo::create(0.5f, 0.5f));
}

void GameMain::releaseHeroBullet(int x, int y)
{
    for (int i = 0; heroBullets->capacity(); i++)
    {
        if (!((GameHeroBullet *)heroBullets->objectAtIndex(i))->getVisible())
        {
            ((GameHeroBullet *)heroBullets->objectAtIndex(i))->setPosition(ccp(x, y));
            ((GameHeroBullet *)heroBullets->objectAtIndex(i))->setVisible();
            break;
        }
    }
}

void GameMain::releaseEnemyBullet(int x, int y)
{
    for (int i = 0; enemyBullets->capacity(); i++)
    {
        if (!((GameEnemyBullet *)enemyBullets->objectAtIndex(i))->getVisible())
        {
            ((GameEnemyBullet *)enemyBullets->objectAtIndex(i))->setPosition(ccp(x, y));
            ((GameEnemyBullet *)enemyBullets->objectAtIndex(i))->setVisible();
            break;
        }
    }
}

bool GameMain::isCollision(CCPoint p1, CCPoint p2, int w1, int h1, int w2, int h2)
{
    if (abs(p1.x - p2.x) < w1 + w2 && abs(p1.y - p2.y) < h1 + h2)
        return true;
    return false;
}

void GameMain::setHeroHurt()
{
    hero->stopAllActions();
    switch (blood)
    {
        case 3:
            blood1->setVisible(false);
            blood--;
            break;
            
        case 2:
            blood2->setVisible(false);
            blood--;
            break;
            
        case 1:
            blood3->setVisible(false);
            blood--;
            break;
            
        case 0:
            if (!isOver)
            {
                isOver = true;
                setOver();
            }
            break;
            
        default:
            break;
    }
    CCActionInterval *action = CCBlink::create(1.0f, 5);
    hero->runAction(action);
    schedule(schedule_selector(GameMain::resetReduce), 1.0f);
    isReduce = true;
}

void GameMain::resetReduce(float dt)
{
    isReduce = false;
}
