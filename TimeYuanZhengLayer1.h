#ifndef TimeYuanZhengLayer1_h__
#define TimeYuanZhengLayer1_h__
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "cocos2d.h"
USING_NS_CC;
#include "Common.h"
class TimeYuanZhengLayer1 : public Layer
{
public:
	CREATE_FUNC(TimeYuanZhengLayer1);
	virtual bool init();




	void menuItem1Callback(cocos2d::Ref* pSender);
	void menuItem2Callback(cocos2d::Ref* pSender);
	void menuItem3Callback(cocos2d::Ref* pSender);
	void menuItem4Callback(cocos2d::Ref* pSender);
	void menuItem5Callback(cocos2d::Ref* pSender);
	void menuItem6Callback(cocos2d::Ref* pSender);

	void hideAllSprite();
	cocos2d::Sprite *sprite[6];


private:
	Node* rootNode;

	cocos2d::ui::Button* copy1;
	cocos2d::ui::Button* copy2;
	cocos2d::ui::Button* copy3;
	cocos2d::ui::Button* copy4;
	cocos2d::ui::Button* copy5;
	cocos2d::ui::Button* copy6;
	

	cocos2d::ui::Text* text1;
	cocos2d::ui::Text* text2;
	cocos2d::ui::Text* text3;
	cocos2d::ui::Text* text4;
	cocos2d::ui::Text* text5;
	cocos2d::ui::Text* text6;



	char str1[2];
	char str2[2];
	char str3[2];
	char str4[2];
	char str5[2];
	char str6[2];


	int nSecond;

public:
	enum
	{
		teams = 15
	};
private:
	int Image_award_width;
	int Image_award_poiX;
	int Image_award_poiY;
	void initZuDuiAwardInfo();
	void showZuDuiBox(int tag);
	
	AwardInfo awards[teams];

	cocos2d::ui::Layout* baomingBox;


};

#endif // TimeYuanZhengLayer1_h__
