#pragma once
#include "SunHeader.h"
#include "cocos2d.h"
USING_NS_CC;

class ExchangeLayer:public Layer
{
public:
	CREATE_FUNC(ExchangeLayer);
	
	bool init();

private:

	Node* _mainNode;	// ���ڵ�

private:

	//************************************
	// Method:    _initUI	��ʼ������
	// FullName:  ExchangeLayer::_initUI
	// Access:    private 
	// Returns:   void
	// Qualifier:
	//************************************
	void _initUI();

};

