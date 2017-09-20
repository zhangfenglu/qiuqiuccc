#ifndef YuanZhengLayer_h__
#define YuanZhengLayer_h__
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "cocos2d.h"
USING_NS_CC;
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


	void baoming1Click();
	void baoming2Click();
	void baoming3Click();
	void baoming4Click();
private:
	void initCangKuObj();
	void initUI();
private:
	Node* rootNode;

	cocos2d::ui::Button* copy1;
	cocos2d::ui::Button* copy2;
	cocos2d::ui::Button* copy3;
	cocos2d::ui::Button* copy4;
	cocos2d::ui::Button* copy5;
	cocos2d::ui::Button* copy6;
	





	/*char str1[2];
	char str2[2];
	char str3[2];
	char str4[2];
	char str5[2];
	char str6[2];*/


	//int nSecond;

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
	
	AwardInfo awards[teams];

	cocos2d::ui::Layout* baomingBox;


};

#endif // YuanZhengLayer_h__
