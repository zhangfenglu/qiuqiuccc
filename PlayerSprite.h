//
//  FoodSprite.h
//  qiuFight
//
//  Created by ÕÅÔ¾¶« on 16/3/2.
//
//

#ifndef PlayerSprite_h
#define PlayerSprite_h

#include "cocos2d.h"
USING_NS_CC;

class PlayerSprite : public Sprite
{
public:
    PlayerSprite(){}
    ~PlayerSprite(){}
    static PlayerSprite* createWithPlayerIndex(uint16_t index);
};

#endif /* PlayerSprite_h */
