#pragma once
#include "cocos2d.h"
#include "cocos-ext.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "Common.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace cocos2d::ui;

class ApplySaveGoldLayer:public Layer, public TableViewDataSource, public TableViewDelegate
{
public:

	CREATE_FUNC(ApplySaveGoldLayer);

	bool init();

	//************************************
	// Method:    initData		初始化数据
	// FullName:  ApplySaveGoldLayer::initData
	// Access:    public 
	// Returns:   void
	// Qualifier:
	// Parameter: int danwei	段位
	//************************************
	void initData(int danwei);
private:

	//************************************
	// Method:    _initUI				初始化ui
	// FullName:  ApplySaveGoldLayer::initUI
	// Access:    private 
	// Returns:   void
	// Qualifier:
	//************************************
	void _initUI();

	virtual void tableCellTouched(TableView* table, TableViewCell* cell) {}
	virtual TableViewCell* tableCellAtIndex(TableView* table, ssize_t idex);
	virtual Size cellSizeForTable(TableView* table);
	virtual ssize_t numberOfCellsInTableView(TableView* table);


	void createTableViewCell(Node* cell, TableView* table, int idex) {}

private:

	Node* _mainNode;						// 主节点
	TableView* _duanWeiTableView;			// 段位
	int _duanwei;							// 段位
};

