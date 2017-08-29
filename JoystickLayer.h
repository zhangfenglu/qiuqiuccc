//
//  JoystickLayer.h
//  qiuFight
//
//  Created by ÕÅÔ¾¶« on 16/2/25.
//
//

#ifndef JoystickLayer_h
#define JoystickLayer_h

#include "cocos2d.h"
USING_NS_CC;

class JoystickLayer : public Layer
{
public:
    JoystickLayer();
    ~JoystickLayer();
    
    virtual bool init();
    CREATE_FUNC(JoystickLayer);
    
    void setOutPos(Point pos);
    void updateJoystick(const Vec2& dif);
    
    Point GetJoyPos();
    
private:
    Sprite* in;
    Sprite* out;
    
    Size outSize;
};

#endif /* JoystickLayer_h */
