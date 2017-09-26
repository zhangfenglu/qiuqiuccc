#pragma once

#include "cocos2d.h"
#include "network/HttpClient.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
USING_NS_CC;
using namespace cocos2d::ui;
using namespace cocostudio::timeline;
using namespace std;

class ApplyBoxLayer:public Layer
{
public:

	virtual bool init();

	// implement the "static create()" method manually
	CREATE_FUNC(ApplyBoxLayer);

	//************************************
	// Method:    initData				初始化数据
	// FullName:  ApplyBoxLayer::initData
	// Access:    public 
	// Returns:   void
	// Qualifier:
	// Parameter: int grade				等级
	// Parameter: ValueMap & data		本地数据
	// Parameter: int week				使用周数
	// Parameter: int useGold			使用的金币
	// Parameter: int groupId			房间号
	// Parameter: string playerId		玩家id
	//************************************
	void initData(int grade, ValueMap &data, int week, int useGold, int groupId, string playerId);

private:

	Node* _mainNode;				// 主节点
	
	Text* _saveText;				// 节省文本
	Text* _useText;					// 使用文本

	ImageView* _dan;				// 段位图片
	Text* _danName;					// 段位名字
	ImageView* _star[7];			// 星星图片数组
	Text* _starNumber;				// 星星等级

	string _playerId;				// 玩家id
	int _groupId;					// 房间号
	int _week;						// 周数
	int _duanwei;					// 段位
private:

	//************************************
	// Method:    _initUI				初始化ui
	// FullName:  ApplyBoxLayer::_initUI
	// Access:    private 
	// Returns:   void
	// Qualifier:
	//************************************
	void _initUI();
};

