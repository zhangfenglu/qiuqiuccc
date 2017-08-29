/*!
 * \class LoginningLayer
 *
 * TODO: 进度加载界面
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
#ifndef LoginningLayer_h__
#define LoginningLayer_h__
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "cocos2d.h"
USING_NS_CC;

#include "network/HttpClient.h"

//#include "cocos-ext.h"


//#include "cocos-ext.h"
//USING_NS_CC_EXT;

using namespace cocostudio::timeline;
//using namespace cocos2d::ui;

class LoginingLayer : public Layer
{
public:
	LoginingLayer();
	~LoginingLayer();
	CREATE_FUNC(LoginingLayer);
	virtual bool init();
	void update(float delta);

	//Http Response Callback
	//void onHttpRequestCompleted(cocos2d::network::HttpClient *sender, cocos2d::network::HttpResponse *response);

private:
	int m_nCount;
	cocos2d::ui::LoadingBar* loadingBar;
	std::string str;
	cocos2d::ui::Text* tishi;
	
	cocos2d::ui::ImageView* box;
	cocos2d::ui::Button* btnGenXin;
};

#endif // LoginningLayer_h__
