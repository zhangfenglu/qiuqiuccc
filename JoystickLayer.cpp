//
//  JoystickLayer.cpp
//  qiuFight
//
//  Created by ÕÅÔ¾¶« on 16/2/25.
//
//

#include "JoystickLayer.h"
#include "Common.h"


JoystickLayer::JoystickLayer()
{
    
}

JoystickLayer::~JoystickLayer()
{
    
}

bool JoystickLayer::init()
{
    if(!Layer::init())
        return false;
    
    out = Sprite::create("Joystick_01.png");
    out->setScale(0.5f);
    out->setPosition(Vec2(0,0));
    addChild(out, 0, 1);
    
    in = Sprite::create("Joystick_02.png");
    in->setPosition(Vec2(0,0));
    in->setScale(0.5f);
    addChild(in, 1, 2);
    
    return true;
}

void JoystickLayer::setOutPos(cocos2d::Point pos)
{
    out->setPosition(pos);
    outSize = out->getContentSize() * 0.2f;
    
    in->setPosition(pos);
}

void JoystickLayer::updateJoystick(const Vec2& pos)
{
	Vec2 outPos = out->getPosition();
	auto len = outPos.distance(pos);
	if (len < R_LENGTH)
	{
		in->setPosition(pos);
	}
	else
	{
		auto inpos = outPos + (pos - outPos) * (R_LENGTH / len);
		in->setPosition(inpos);
	}

//    Point outPos = out->getPosition();
//    
//    Point currentPos = in->getPosition();
//    Point destPos = ccpAdd(currentPos, dif);
//    
//    float x = destPos.x - outPos.x;
//    float y = destPos.y - outPos.y;
////    float r = outSize.width * 0.5f;
//    float r = R_LENGTH;
//    
//    
//    if((x * x + y * y ) < r * r)
//    {
//        
//    }
//    else
//    {
//        float a = atanf(y/x);
//        float ran = 0;
//        if(x > 0 && y > 0)
//        {
//            ran = a;
//        }
//        else if(x < 0 && y > 0)
//        {
//            ran = M_PI + a;
//        }
//        else if(x < 0 && y < 0)
//        {
//            ran = M_PI + a;
//        }
//        else if(x > 0 && y < 0)
//        {
//            ran = a;
//        }
//        
//        destPos.x = outPos.x + r * cosf(ran);
//        destPos.y = outPos.y + r * sinf(ran);
//    }
//    
//    
//    in->setPosition(destPos);
    
}

Point JoystickLayer::GetJoyPos()
{
    return in->getPosition();
}

