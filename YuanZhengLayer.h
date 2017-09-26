#ifndef YuanZhengLayer_h__
#define YuanZhengLayer_h__
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "cocos2d.h"
USING_NS_CC;
#include "RotateMenu.h"
#include "Global.h"
#include "Common.h"

#include "network/HttpClient.h"
using namespace cocos2d::network;
class YuanZhengLayer : public Layer
{
public:
	CREATE_FUNC(YuanZhengLayer);
	virtual bool init();




	void menuItem1Callback(cocos2d::Ref* pSender);
	void menuItem2Callback(cocos2d::Ref* pSender);
	void menuItem3Callback(cocos2d::Ref* pSender);
	void menuItem4Callback(cocos2d::Ref* pSender);
	void menuItem5Callback(cocos2d::Ref* pSender);
	void menuItem6Callback(cocos2d::Ref* pSender);


	void baoming1Click(Ref*, cocos2d::ui::Widget::TouchEventType type);
	void baoming2Click(Ref*, cocos2d::ui::Widget::TouchEventType type);
	void baoming3Click(Ref*, cocos2d::ui::Widget::TouchEventType type);
	void baoming4Click(Ref*, cocos2d::ui::Widget::TouchEventType type);
private:
	void initPlayerBaoMingState();
	void initCangKuObj();
	void initUI();
private:
	std::vector<yuanzhengBaoMing_Info> baomingInfos;

	Node* rootNode;
	Node* tishiNode;
	float tishiY;
	float tishiX;

	cocos2d::ui::Button* copy1;
	cocos2d::ui::Button* copy2;
	cocos2d::ui::Button* copy3;
	cocos2d::ui::Button* copy4;
	cocos2d::ui::Button* copy5;
	cocos2d::ui::Button* copy6;
	

public:
	enum
	{
		teams = 15
	};
private:
	//当前的 星级 包名
	int star_level;
	int Image_award_width;
	int Image_award_poiX;
	int Image_award_poiY;
	void initZuDuiAwardInfo();
	void showZuDuiBox(int tag);
	
	AwardInfo awards[15];

	cocos2d::ui::Layout* baomingBox;

	account_info infos;


};

#endif // YuanZhengLayer_h__
