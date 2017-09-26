#pragma once
#include "SunHeader.h"
#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "cocos-ext.h"
USING_NS_CC;


class ExchangeAwardLayer : public Layer
{
public:
	CREATE_FUNC(ExchangeAwardLayer);

	bool init();

	void initData(std::vector<Prop> data);
private:
	Node* _mainNode;			// 主节点
private:

	//************************************
	// Method:    _initUI
	// FullName:  ExchangeAwardLayer::_initUI
	// Access:    private 
	// Returns:   void
	// Qualifier:
	//************************************
	void _initUI();

	//************************************
	// Method:    _pushListViewItem	压入节点
	// FullName:  ExchangeAwardLayer::_pushListViewItem
	// Access:    private 
	// Returns:   Layout*
	// Qualifier:
	// Parameter: Prop & prop
	//************************************
	ui::Layout* _pushListViewItem(Prop &prop);
};

