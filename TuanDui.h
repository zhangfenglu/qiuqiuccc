//
//  RelationShipLayer.h
//  qiuFight
//
//  Created by 张跃东 on 16/4/8.
//
//

#ifndef TuanDui_h
#define TuanDui_h

#include "Global.h"
#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;

#include "WebSocketLayer.h"

// 公用底层
class TuanDui : public Layer, public TableViewDataSource, public TableViewDelegate
{
public:
    enum RS_TAG
    {
        TAG_NONE,
        TAG_ATTENTION,
        TAG_FRIEND,
        TAG_ENEMY,
        TAG_BLACK
    };
    
    TuanDui();
    ~TuanDui();
    
    virtual bool init();
    CREATE_FUNC(TuanDui);
    
    void initUI();

    void BackClick(Ref* pSender);
  
    void SenMSG(float ft);
    
    virtual void tableCellTouched(TableView* table, TableViewCell* cell);
    virtual TableViewCell* tableCellAtIndex(TableView* table, ssize_t idex);
    virtual Size cellSizeForTable(TableView* table);
    virtual ssize_t numberOfCellsInTableView(TableView* table);
    
    virtual void scrollViewDidScroll(ScrollView* view){}
    virtual void scrollViewDidZoom(ScrollView* view){}
    
    Size getTableSize();
    void createTableViewCell(Node* cell, TableView* table, int idex);
    
    void StartGame(Ref* pSender);
    void Yaoqing(Ref* pSender);
    
    void ReSetTabelView();
private:
    std::vector<TestAtt> m_atts;
};


// 公用底层
class YaoqingList : public Layer
{
public:
    enum RS_TAG
    {
        TAG_NONE,
        TAG_ATTENTION,
        TAG_FRIEND,
        TAG_ENEMY,
        TAG_BLACK
    };
    
    YaoqingList();
    ~YaoqingList();
    
    virtual bool init();
    CREATE_FUNC(YaoqingList);
    
    void initUI();
    void resetBtnState();
    
    void AttentionClick(Ref* pSender);
    void FriendClick(Ref* pSender);
    void EnemyClick(Ref* pSender);
    void BlackClick(Ref* pSender);
    
    void PrePageClick(Ref* pSender);
    void NextPageClick(Ref* pSender);
    void BackClick(Ref* pSender);
    
    RS_TAG GetCurrentTag()
    {
        return m_currentTag;
    }
    void respFans(const cocos2d::network::WebSocket::Data& data);
    void resIcon(std::vector<icon_data> icons);
    void respFriends(const cocos2d::network::WebSocket::Data& data);
    
    void SenMSG(float ft);
public:
    RS_TAG      m_currentTag;
    Button*     m_attention;
    Button*     m_friend;
    Button*     m_enemy;
    Button*     m_black;
};
// 关注
class TeamList : public Layer, public TableViewDataSource, public TableViewDelegate
{
public:
    TeamList();
    ~TeamList();
    
    virtual bool init();
    CREATE_FUNC(TeamList);
    
    virtual void tableCellTouched(TableView* table, TableViewCell* cell);
    virtual TableViewCell* tableCellAtIndex(TableView* table, ssize_t idex);
    virtual Size cellSizeForTable(TableView* table);
    virtual ssize_t numberOfCellsInTableView(TableView* table);
    
    virtual void scrollViewDidScroll(ScrollView* view);
    virtual void scrollViewDidZoom(ScrollView* view);
    
    void setLists(std::vector<TestAtt> ranks)
    {
        m_atts.clear();
        m_atts = ranks;
    }
    void initTableView(std::vector<TestAtt> fanses);
    void updateLists(std::vector<icon_data> datas);
    std::string getIconString(int roleID, std::vector<icon_data>datas);
    
    void SendYaoqing(Ref* pSender);
    void Xuanze(Ref* pSender);
    void XuanzeAll(Ref* pSender);
    
    virtual bool onTouchBegan(Touch* pTouch,Event* pEvent);
protected:
    Size getTableSize();
    void createTableViewCell(Node* cell, TableView* table, int idex);
    
private:
    //TableView* tableView;
    std::vector<TestAtt> m_atts;
};

// 粉丝


#endif /* RelationShipLayer_h */
