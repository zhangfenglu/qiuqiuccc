#ifndef TimeYuanZhengLayer_h__
#define TimeYuanZhengLayer_h__
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "cocos2d.h"
USING_NS_CC;
class TimeYuanZhengLayer : public Layer
{
public:
	CREATE_FUNC(TimeYuanZhengLayer);
	virtual bool init();




	void menuItem1Callback(cocos2d::Ref* pSender);
	void menuItem2Callback(cocos2d::Ref* pSender);
	void menuItem3Callback(cocos2d::Ref* pSender);
	void menuItem4Callback(cocos2d::Ref* pSender);
	void menuItem5Callback(cocos2d::Ref* pSender);
	void menuItem6Callback(cocos2d::Ref* pSender);

	void hideAllSprite();
	cocos2d::Sprite *sprite[6];
};

#endif // TimeYuanZhengLayer_h__
