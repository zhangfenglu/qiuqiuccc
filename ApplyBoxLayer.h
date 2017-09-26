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
	// Method:    initData				��ʼ������
	// FullName:  ApplyBoxLayer::initData
	// Access:    public 
	// Returns:   void
	// Qualifier:
	// Parameter: int grade				�ȼ�
	// Parameter: ValueMap & data		��������
	// Parameter: int week				ʹ������
	// Parameter: int useGold			ʹ�õĽ��
	// Parameter: int groupId			�����
	// Parameter: string playerId		���id
	//************************************
	void initData(int grade, ValueMap &data, int week, int useGold, int groupId, string playerId);

private:

	Node* _mainNode;				// ���ڵ�
	
	Text* _saveText;				// ��ʡ�ı�
	Text* _useText;					// ʹ���ı�

	ImageView* _dan;				// ��λͼƬ
	Text* _danName;					// ��λ����
	ImageView* _star[7];			// ����ͼƬ����
	Text* _starNumber;				// ���ǵȼ�

	string _playerId;				// ���id
	int _groupId;					// �����
	int _week;						// ����
	int _duanwei;					// ��λ
private:

	//************************************
	// Method:    _initUI				��ʼ��ui
	// FullName:  ApplyBoxLayer::_initUI
	// Access:    private 
	// Returns:   void
	// Qualifier:
	//************************************
	void _initUI();
};

