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
	// Method:    initData		��ʼ������
	// FullName:  ApplySaveGoldLayer::initData
	// Access:    public 
	// Returns:   void
	// Qualifier:
	// Parameter: int danwei	��λ
	//************************************
	void initData(int danwei);
private:

	//************************************
	// Method:    _initUI				��ʼ��ui
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

	Node* _mainNode;						// ���ڵ�
	TableView* _duanWeiTableView;			// ��λ
	int _duanwei;							// ��λ
};

