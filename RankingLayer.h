//
//  RankingLayer.h
//  qiuFight
//
//  Created by 张跃东 on 16/4/9.
//
//

#ifndef RankingLayer_h
#define RankingLayer_h

#include "Global.h"
#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;

#include "WebSocketLayer.h"

// test
struct TestRank
{
    int         m_id;
    int         m_sex;
    int         m_iconDex;
    int         m_rank;
    int         m_duanwei;
    int         m_xing;
    std::string m_name;
    std::string m_zjrs;      //最近获得人数
    std::string m_zcbs;      //总崇拜数
    std::string m_zjymz;     //最近仰慕者数
    std::string m_zymz;      //总仰慕数
    std::string m_zjhds;     //最近获得珍珠数
    std::string m_hdzs;      //总获得数
    std::string m_zjjss;     //最近击杀数
    std::string m_zjss;      //总击杀数
    std::string m_iconStr;   //icon照片
};

class RankingLayerBase : public CPZLayer
{
public:
    enum R_TAG
    {
        TAG_NONE,
        TAG_JHDW,
        TAG_CBZ,
        TAG_YMZ,
        TAG_XZZ,
        TAG_JSS
    };
    
    RankingLayerBase();
    ~RankingLayerBase();
    
    virtual bool init();
    CREATE_FUNC(RankingLayerBase);
    
    void initUI();
    void resetBtnState();
    
    void JhdwClick(Ref* pSender);
    void CbzClick(Ref* pSender);
    void YmzClick(Ref* pSender);
    void XzzClick(Ref* pSender);
    void JssClick(Ref* pSender);
    
    void BackClick(Ref* pSender);
    
    R_TAG   GetCurrentTag()
    {
        return m_rankTag;
    }
    
    void respRanks(const cocos2d::network::WebSocket::Data &data);
    void SenMSG(float ft);
    
    void respRankIcons(std::vector<icon_data> icons);
private:
    Button* jhdwBtn;
    Button* cbzBtn;
    Button* ymzBtn;
    Button* xzzBtn;
    Button* jssBtn;
    
    R_TAG   m_rankTag;
};


class RankingLayerChild : public Layer, public TableViewDataSource, public TableViewDelegate
{
public:
    RankingLayerChild();
    ~RankingLayerChild();
    
    
    virtual bool init();
    CREATE_FUNC(RankingLayerChild);
    
    virtual void tableCellTouched(TableView* table, TableViewCell* cell);
    virtual TableViewCell* tableCellAtIndex(TableView* table, ssize_t idex);
    virtual Size cellSizeForTable(TableView* table);
    virtual ssize_t numberOfCellsInTableView(TableView* table);
    
    virtual void scrollViewDidScroll(ScrollView* view);
    virtual void scrollViewDidZoom(ScrollView* view);
    
    void setRanks(std::vector<TestRank> ranks);
    void updateRanks(std::vector<icon_data> datas);
    std::string getIconString(int roleID, std::vector<icon_data> datas);
    void initTableView();
protected:
    Size getTableSize();
    void createTableViewCell(Node* cell, TableView* table, int idex);
    
    void clickBtn1(Ref* pSender);
    void clickBtn2(Ref* pSender);
    void clickBtn3(Ref* pSender);
    
    void resetBtnState();
    
private:
    //TableView* tableView;
    std::vector<TestRank> m_atts;
    RankingLayerBase::R_TAG m_tag;
    
    Button* btn1;
    Button* btn2;
    Button* btn3;
    
    int current_click_index;
};


#endif /* RankingLayer_h */
