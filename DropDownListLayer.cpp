//
//  DropDownListLayer.cpp
//  qiuFight
//
//  Created by 张跃东 on 16/4/12.
//
//

#include "DropDownListLayer.h"

#define DROPDOWNLIST_NORMAL_COLOR       Color4B(128, 128, 128, 255)
#define DROPDOWNLIST_SELECTED_COLOR     Color4B(200, 200, 200, 255)
#define DROPDOWNLIST_HIGHLIGHT_COLOR    Color4B(0, 0, 255, 255)

#define DROPDOWNLIST_NORMAL_COLOR3      Color3B(128, 128, 128)
#define DROPDOWNLIST_SELECTED_COLOR3    Color3B(200, 200, 200)
#define DROPDOWNLIST_HIGHLIGHT_COLOR3   Color3B(0, 0, 255)

DropDownListLayer::DropDownListLayer(CCLabelTTF* label, Size size)
: showLabel(label)
, isShowMenu(false)
, lastSelectedIndex(0)

{
    mainMenu = CCMenu::create();
    mainMenu->setPosition(Vec2(size.width * 0.5f, size.height * 0.5f));
    mainMenu->retain();
    
    showLabel->setPosition(Vec2(size.width * 0.5f, size.height * 0.5f));
    addChild(showLabel);
    
    setContentSize(size);
}

DropDownListLayer::~DropDownListLayer()
{
    mainMenu->release();
}

DropDownListLayer* DropDownListLayer::create(cocos2d::CCLabelTTF *label, cocos2d::Size size)
{
    DropDownListLayer* layer = new DropDownListLayer(label, size);
    layer->autorelease();
    return layer;
}

// 获取当前选中的label
std::string DropDownListLayer::getString()
{
    return showLabel->getString();
}

// 获取当前选中的index
int DropDownListLayer::getSelectedIndex()
{
    return lastSelectedIndex;
}

// 设置选中index
void DropDownListLayer::setSelectedIndex(int index)
{
    lastSelectedIndex = index;
    
    for(int i = 0, j = (int)selectLabels.size(); i < j; ++i)
    {
        if(i == lastSelectedIndex)
        {
            bgLayers[i]->setColor(DROPDOWNLIST_HIGHLIGHT_COLOR3);
            showLabel->setString(selectLabels[i]->getString());
        }
        else
        {
            bgLayers[i]->setColor(DROPDOWNLIST_NORMAL_COLOR3);
        }
    }
}

void DropDownListLayer::onEnter()
{
    setTouchMode(Touch::DispatchMode::ONE_BY_ONE);
    setTouchEnabled(true);
    Layer::onEnter();
}

void DropDownListLayer::registerWithTouchDispatcherEx()
{
    //TouchDispatcher::getInstance()->addTargetedDelegate(this,PRI,true);
    //Director* pDirector = Director::getInstance();
    //pDirector->getTouchDispatcher()->addTargetedDelegate(this, kCCMenuHandlerPriority, true);
}

bool DropDownListLayer::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event)
{
    if(!isShowMenu)
    {
        Rect rect;
        rect.origin = Vec2::ZERO;
        rect.size = getContentSize();
        Point position = convertTouchToNodeSpace(touch);
        
        if(rect.containsPoint(position))
        {
            isShowMenu = true;
            
            // 点击，显示下拉列表框，也就是mainMenu
            addChild(mainMenu);
            for(int i = 0, j = (int)selectLabels.size(); i < j; ++i)
            {
                if(i == lastSelectedIndex)
                {
                    bgLayers[i]->setColor(DROPDOWNLIST_HIGHLIGHT_COLOR3);
                }
                else
                {
                    bgLayers[i]->setColor(DROPDOWNLIST_NORMAL_COLOR3);
                }
            }
            
            return true;
        }
    }
    
    return true;
}

// 创建以menu item并添加一个label覆盖到上面
void DropDownListLayer::addLabel(cocos2d::CCLabelTTF *label)
{
    Size size = getContentSize();
    
    LayerColor* normal = LayerColor::create(DROPDOWNLIST_NORMAL_COLOR, size.width, size.height);
    LayerColor* selected = LayerColor::create(DROPDOWNLIST_SELECTED_COLOR, size.width, size.height);
    
    bgLayers.push_back(normal);
    selectLabels.push_back(label);
    
    CCMenuItem* item = CCMenuItemSprite::create(normal, selected, NULL, this, SEL_MenuHandler(&DropDownListLayer::onSelected));
    
    label->setPosition(Vec2(size.width * 0.5f, size.height * 0.5f));
    item->addChild(label);
    item->setTag((int)selectLabels.size() - 1);
    item->setPosition(0, -(int)selectLabels.size() * size.height);
    
    mainMenu->addChild(item, 10);
}

// 选中下拉列表后
void DropDownListLayer::onSelected(Ref* pSender)
{
    CCMenuItem* item = dynamic_cast<CCMenuItem*>(pSender);
    if(item)
    {
        lastSelectedIndex = item->getTag();
        showLabel->setString(selectLabels[item->getTag()]->getString());
    }
    onClose();
}

void DropDownListLayer::onClose()
{
    removeChild(mainMenu, true);
    isShowMenu = false;
}

bool DropDownListLayer::isShowDropDown()
{
    return isShowMenu;
}

