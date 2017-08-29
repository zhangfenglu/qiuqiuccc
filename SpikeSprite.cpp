//
//  SpikeSprite.cpp
//  qiuFight
//
//  Created by ÕÅÔ¾¶« on 16/3/2.
//
//

#include "SpikeSprite.h"

#define SPIKE_FILE_PNG      "ci1.png"

SpikeSprite* SpikeSprite::createSpike()
{
    SpikeSprite* sprite = new SpikeSprite();
    if(sprite && sprite->initWithFile(SPIKE_FILE_PNG))
    {
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return NULL;
}