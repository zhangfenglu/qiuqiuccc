//
//  ShopLayer.h
//  qiuFight
//
//  Created by 张跃东 on 16/4/10.
//
//

#ifndef ShopLayer_h
#define ShopLayer_h

#include "Global.h"
#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;

class ShopLayerBase : public Layer
{
public:
    enum S_TAG
    {
        TAG_NONE,
        TAG_WAIGUAN,
        TAG_HERO,
        TAG_JINHE,
        TAG_HDBS,
        TAG_HECHENG,
        TAG_CAILIAO,
        TAG_TONGQIAN_LAB,
        TAG_YUANBAO_LAB
    };
    
    ShopLayerBase();
    ~ShopLayerBase();
    
    virtual bool init();
    CREATE_FUNC(ShopLayerBase);
    
    void initUI();
    void resetBtnState();
    
    void WaiGuanClick(Ref* pSender);
    void HeroClick(Ref* pSender);
    void JinheClick(Ref* pSender);
    void HdbsClick(Ref* pSender);
    
    void BackClick(Ref* pSender);
    void RushLab();
    S_TAG   GetCurrentTag()
    {
        return m_shopTag;
    }
    
private:
    Button* waiguanBtn;
    Button* heroBtn;
    Button* jinheBtn;
    Button* hdbbBtn;
    
    S_TAG   m_shopTag;
};



// 外观
class ShopLayerWaiguan : public Layer, public TableViewDataSource, public TableViewDelegate
{
public:
    enum weiguan_tag
    {
        guanghuan_tag,
        baozi_tag,
        canyin_tag
    };
    
    ShopLayerWaiguan();
    ~ShopLayerWaiguan();
    
    virtual bool init();
    CREATE_FUNC(ShopLayerWaiguan);
    
    void GuangHuanClick(Ref* pSender);
    void BaoziClick(Ref* pSender);
    void CanyinClick(Ref* pSender);
    
    virtual void tableCellTouched(TableView* table, TableViewCell* cell);
    virtual TableViewCell* tableCellAtIndex(TableView* table, ssize_t idex);
    virtual Size cellSizeForTable(TableView* table);
    virtual ssize_t numberOfCellsInTableView(TableView* table);
    
    virtual void scrollViewDidScroll(ScrollView* view);
    virtual void scrollViewDidZoom(ScrollView* view);
    
    void initTableView(float ft);
    
    void resetBtnState();
    void rushTabel();
protected:
    Size getTableSize();
    void createTableViewCell(Node* cell, TableView* table, int idex);
    
private:
    Button* guanhuan;
    Button* baozi;
    Button* canyin;
    
    Size  childSize;
    
    weiguan_tag m_tag;
    
    TableView* tableView;
    
    std::vector<ChildItem> guanghuans;
    std::vector<ChildItem> baozis;
    std::vector<ChildItem> canyins;
};
// 购买界面
class BuyItemLayer : public CPZLayer
{
public:
    BuyItemLayer();
    ~BuyItemLayer();
    
    virtual bool init();
    CREATE_FUNC(BuyItemLayer);
    void BuyClick(Ref* pSender);
    void UseClick(Ref* pSender);
    void XiexiaClick(Ref* pSender);
    
    void InitItem(ChildItem ite,int itemType);
    
    virtual bool onTouchBegan(Touch* pTouch,Event* pEvent);
    virtual void onTouchEnded(Touch* pTouch,Event* pEvent);
    
private:
    ChildItem mItem;
    bool isTouchIn;
};
// 英雄
class ShopLayerHero : public Layer
{
public:
    ShopLayerHero();
    ~ShopLayerHero();
    
    virtual bool init();
    CREATE_FUNC(ShopLayerHero);
    
    void HechengClick(Ref* pSender);
    void BagClick(Ref* pSender);
    
    void InitShenshou();
    
    void helpClick(Ref* pSender);
    void LookClick(Ref* pSender);
    
private:
    Size childSize;
};

// 材料包裹
class CaiLiaoBag : public CPZLayer, public TableViewDataSource, public TableViewDelegate
{
public:
    CaiLiaoBag();
    ~CaiLiaoBag();
    
    virtual bool init();
    CREATE_FUNC(CaiLiaoBag);
    
    virtual void tableCellTouched(TableView* table, TableViewCell* cell);
    virtual TableViewCell* tableCellAtIndex(TableView* table, ssize_t idex);
    virtual Size cellSizeForTable(TableView* table);
    virtual ssize_t numberOfCellsInTableView(TableView* table);
    
    virtual void scrollViewDidScroll(ScrollView* view){}
    virtual void scrollViewDidZoom(ScrollView* view){}
    
    
    
    //virtual void registerWithTouchDispatcherEx(){
        //Director::getInstance()->getTouchDispatcher()->addTargetedDelegate(this,PRI,true);
    //}
    virtual bool onTouchBegan(Touch* pTouch,Event* pEvent);
    virtual void onTouchEnded(Touch* pTouch,Event* pEvent);
    
    //virtual void TouchesBegan(__Set* pTouches,Event* pEvent);
    //virtual void TouchesMoved(__Set* pTouches,Event* pEvent);
    //virtual void TouchesEnded(__Set* pTouches,Event* pEvent);
protected:
    Size getTableSize();
    void createTableViewCell(Node* cell, TableView* table, int idex);
    
private:
    std::vector<itemInfo> hInfo;
    bool isTouchIn;
};

// 合成
class HeCheng : public CPZLayer
{
public:
    HeCheng();
    ~HeCheng();
    
    virtual bool init();
    CREATE_FUNC(HeCheng);
    void BackClick(Ref* pSender);
    void HechengClick(Ref* pSender);
    
    void InitItem();
    
private:
    std::vector<itemInfo> hInfo;
    int itemMax;
    int starNum;
};
// 锦盒
class ShopLayerJinhe : public Layer
{
public:
    ShopLayerJinhe();
    ~ShopLayerJinhe();
    
    virtual bool init();
    CREATE_FUNC(ShopLayerJinhe);
    
    void OpenMuClick(Ref* pSender);
    void OpenHaoClick(Ref* pSender);
    
    void rushLab();
private:
    Size childSize;
};

// 获取元宝
class ShopLayerHuoqu : public Layer
{
public:
    ShopLayerHuoqu();
    ~ShopLayerHuoqu();
    
    virtual bool init();
    CREATE_FUNC(ShopLayerHuoqu);
    
    void LingquClick(Ref* pSender);
    void copyClick(Ref* pSender);
    void saveClick(Ref* pSender);
    
private:
    Size childSize;
};



#endif /* ShopLayer_h */
