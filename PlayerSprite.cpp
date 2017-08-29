//
//  FoodSprite.cpp
//  qiuFight
//
//  Created by ÕÅÔ¾¶« on 16/3/2.
//
//

#include "PlayerSprite.h"
#include "Common.h"

#define IMAGE_PRE "color_"


PlayerSprite* PlayerSprite::createWithPlayerIndex(uint16_t index)
{
    PlayerSprite* sprite = new PlayerSprite();
    int idx = index % MAXIMUM_PICTURE_NUM;
    char temp[16];
    sprintf(temp, "%s%d.png", IMAGE_PRE, idx);
    if (sprite && sprite->initWithFile(temp))
    {
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return NULL;
}

