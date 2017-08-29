//
//  DropDownListLayer.h
//  qiuFight
//
//  Created by 张跃东 on 16/4/12.
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
    CCMenu* mainMenu; // 下拉列表选项的集合
    CCLabelTTF* showLabel; // 显示选中的结果
    std::vector<CCLabelTTF*> selectLabels; //下拉列表label
    std::vector<LayerColor*> bgLayers; //设置背景
    bool isShowMenu; //是否显示了下拉列表
    int lastSelectedIndex;  //选中下拉列表的index
};


#endif /* DropDownListLayer_h */
