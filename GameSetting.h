/*!
 * \class GameSetting
 *
 * TODO: 账号设置
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
#ifndef GameSetting_h__
#define GameSetting_h__

#include "cocos2d.h"
USING_NS_CC;

#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

#include "network/HttpClient.h"
class GameSetting : public Layer
{
public:
	CREATE_FUNC(GameSetting);
	virtual bool init();

	//Http Response Callback
	void onHttpRequestCompleted(cocos2d::network::HttpClient *sender, cocos2d::network::HttpResponse *response);

	void clickBtnToLogin();

private:
	//’À∫≈…Ë÷√∫–◊”
	cocos2d::ui::TextField* TextFieldpPone;
	cocos2d::ui::Button* btnBangDing;
	cocos2d::ui::Button* btnChange;


	cocos2d::ui::Button* btnLogin;
	cocos2d::ui::TextField* zhangHao;
	cocos2d::ui::TextField* miMa;
};
#endif // GameSetting_h__
