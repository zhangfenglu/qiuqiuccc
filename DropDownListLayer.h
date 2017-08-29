//
//  DropDownListLayer.h
//  qiuFight
//
//  Created by ��Ծ�� on 16/4/12.
//
//

#ifndef DropDownListLayer_h
#define DropDownListLayer_h

#include "cocos2d.h"
#include "Global.h"

USING_NS_CC;

class DropDownListLayer : public CPZLayer
{
public:
    DropDownListLayer(CCLabelTTF* label, Size size);
    ~DropDownListLayer();
    
    static DropDownListLayer* create(CCLabelTTF* label, Size size);
    std::string getString();
    int getSelectedIndex();
    void setSelectedIndex(int index);
    virtual void onEnter();
    virtual void registerWithTouchDispatcherEx();
    virtual bool onTouchBegan(Touch* touch, Event* event);
    void addLabel(CCLabelTTF* label);
    void onSelected(Ref* sender);
    void onClose();
    bool isShowDropDown();
    
private:
    CCMenu* mainMenu; // �����б�ѡ��ļ���
    CCLabelTTF* showLabel; // ��ʾѡ�еĽ��
    std::vector<CCLabelTTF*> selectLabels; //�����б�label
    std::vector<LayerColor*> bgLayers; //���ñ���
    bool isShowMenu; //�Ƿ���ʾ�������б�
    int lastSelectedIndex;  //ѡ�������б��index
};


#endif /* DropDownListLayer_h */
