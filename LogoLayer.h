/*!
 * \class LogoLayer
 *
 * TODO: 闪屏
 *
 * \note
 *
 * \author 张锋露
 *
 * \version 1.0
 *
 * \date 八月 2017
 *
 * Contact: 373510848@qq.com
 *
 */
#ifndef LogoLayer_h__
#define LogoLayer_h__
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "cocos2d.h"
USING_NS_CC;

using namespace cocostudio::timeline;

class LogoLayer : public Layer
{
public:
	CREATE_FUNC(LogoLayer);
	virtual bool init();

private:
	void goToLoginLayer();

};

#endif // LogoLayer_h__
