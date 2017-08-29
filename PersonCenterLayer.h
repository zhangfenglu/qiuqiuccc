//
//  PersonCenterLayer.h
//  qiuFight
//
//  Created by 张跃东 on 16/4/1.
//
//

#ifndef PersonCenterLayer_h
#define PersonCenterLayer_h

#include "Global.h"
#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;

// 公用底层
class PersonCenterBase : public Layer
{
public:
    enum PC_TAG
    {
        TAG_NONE,
        TAG_ZILIAO,
        TAG_XINXI,
        TAG_RONGYU,
        TAG_BISAI
    };
    
    PersonCenterBase();
    ~PersonCenterBase();
    
    virtual bool init();
    CREATE_FUNC(PersonCenterBase);
    
    void initUI();
    void resetBtnState();
    
    void ZiliaoClick(Ref* pSender);
    void RongyuClick(Ref* pSender);
    void BisaiClick(Ref* pSender);
    void XinxiClick(Ref* pSender);
    
    void SetClick(Ref* pSender);
    void BackClick(Ref* pSender);
    
private:
    PC_TAG m_currentTag;
    Button* ziliao;
    Button* xinxi;
    Button* rongyu;
    Button* bisai;
};

// 个人资料
class PersonInfo : public Layer
{
public:
    PersonInfo();
    ~PersonInfo();
    
    virtual bool init();
    CREATE_FUNC(PersonInfo);
    
    void ChangeHead(Ref* pSender);
};

// 个人信息
class PersonXinxi : public Layer
{
public:
    PersonXinxi();
    ~PersonXinxi();
    
    virtual bool init();
    CREATE_FUNC(PersonXinxi);
    
    void ChangePlayer(Ref* pSender);
    void RegisterClick(Ref* pSender);
};

// 个人荣誉
class PersonRongyu : public Layer
{
public:
    PersonRongyu();
    ~PersonRongyu();
    
    virtual bool init();
    CREATE_FUNC(PersonRongyu);
};

// 比赛
class PersonCenterLayer : public Layer, public TableViewDataSource, public TableViewDelegate
{
public:
    PersonCenterLayer();
    ~PersonCenterLayer();
    
    virtual bool init();
    CREATE_FUNC(PersonCenterLayer);
    
    virtual void tableCellTouched(TableView* table, TableViewCell* cell);
    virtual TableViewCell* tableCellAtIndex(TableView* table, ssize_t idex);
    virtual Size cellSizeForTable(TableView* table);
    virtual ssize_t numberOfCellsInTableView(TableView* table);
    
    virtual void scrollViewDidScroll(ScrollView* view);
    virtual void scrollViewDidZoom(ScrollView* view);
    
protected:
    Size getTableSize();
    void createTableViewCell(Node* cell, TableView* table, int idex);
    
private:
    //TableView* tableView;
    std::vector<bisaiInfo>  infos;
};



#endif /* PersonCenterLayer_h */
