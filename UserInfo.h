//
//  PersonCenterLayer.h
//  qiuFight
//
//  Created by 张跃东 on 16/4/1.
//
//

#ifndef UserInfo_h
#define UserInfo_h

#include "Global.h"
#include "cocos2d.h"
#include "cocos-ext.h"
#include "WebSocketLayer.h"
USING_NS_CC;
USING_NS_CC_EXT;

// 公用底层
class UserInfo : public Layer
{
public:
    enum PC_TAG
    {
        TAG_NONE,
        TAG_SHOUYE,
        TAG_ZHAOPIAN,
        TAG_YOUXI,
        TAG_ZHANDUI,
        TAG_LIUYAN,
        TAG_XIHUAN,
        TAG_GERENRONGYU,
        TAG_BISAIJILU,
        
        TAG_SHOUYE_BTN,
        TAG_ZHAOPIAN_BTN,
        TAG_YOUXI_BTN,
        TAG_ZHANDUI_BTN,
        TAG_LIUYAN_BTN
    };
    
    UserInfo();
    ~UserInfo();
    
    virtual bool init();
    CREATE_FUNC(UserInfo);
    
    void initUI();
    void resetBtnState();
    
    void ShouyeClick(Ref* pSender);
    void ZhaopianClick(Ref* pSender);
    void YouxiClick(Ref* pSender);
    void ZhanduiClick(Ref* pSender);
    
    void LiuyanClick(Ref* pSender);
    void BackClick(Ref* pSender);
    void ShowXihuan(bool isShow);
    void ShowGame(int idex);
    void respFans(const cocos2d::network::WebSocket::Data& data);
    
    void respHotLiuyan(const cocos2d::network::WebSocket::Data& data);
    void respLiuyan(const cocos2d::network::WebSocket::Data& data);
    
    void resSeasonRank(const cocos2d::network::WebSocket::Data& data);
    void resGameRecode(const cocos2d::network::WebSocket::Data& data);
    void resHeadImg(int count);
    void resPhoto(std::vector<std::string> arr);
    void setHeadIcon();
private:
    PC_TAG m_currentTag;
    std::vector<TestAtt> fanses;
};

// 个人资料
class FirstPage : public Layer
{
public:
    enum
    {
        TAG_NONE,
        TAG_XIHUANBTN,
        TAG_LUYINBTN,
        TAG_DIQUBTN,
        TAG_TOUXIANGBTN,
        TAG_HEADCHOSE,
        TAG_HEADICON
    };
    FirstPage();
    ~FirstPage();
    
    virtual bool init();
    CREATE_FUNC(FirstPage);
    
    void ChangeHead(Ref* pSender);
    
    void HeadClick(cocos2d::Ref *pSender);   //头像
    void LuyinClick(cocos2d::Ref *pSender);   //录音
    
    void XihuanClick(cocos2d::Ref *pSender);   //喜欢
    
    void DiquClick(cocos2d::Ref *pSender);   //选择地区
    
    void SetBtnToTouch();
    void InitFensi(std::vector<TestAtt> info);
    void SenMSG(float ft);
    void resHeadImg(int count);
    void setHeadIcon();
};

// 设置
class HeadIconChose : public CPZLayer
{
public:
    enum PC_TAG
    {
        TAG_NONE,
        TAG_FindFriend,
        TAG_Fujinderen,
        TAG_SHEZHI,
        TAG_ZHUCE,
        TAG_XUANZENAN,
        TAG_XUANZENV,
    };
    HeadIconChose();
    ~HeadIconChose();
    
    virtual bool init();
    CREATE_FUNC(HeadIconChose);
    
    void resetBtnState();
    void InitShezhiUI();
    void InitZhuceUI();
    
    void YouxiShezhi(Ref* pSender);
    void Yonghuxinxi(Ref* pSender);
    void Back(Ref* pSender);
    void SenMSG(float ft);
    virtual bool onTouchBegan(Touch* pTouch,Event* pEvent);
    void SetParentTag(int tag){mParent = tag;}
    void resHeadImg(int count);
    void reshHead();
private:
    PC_TAG m_currentTag;
    int mParent;
};

// 普通头像
class NormalHeadIcon : public Layer, public TableViewDataSource, public TableViewDelegate
{
public:

    NormalHeadIcon();
    ~NormalHeadIcon();
    
    virtual bool init();
    CREATE_FUNC(NormalHeadIcon);
    
    virtual void tableCellTouched(TableView* table, TableViewCell* cell);
    virtual TableViewCell* tableCellAtIndex(TableView* table, ssize_t idex);
    virtual Size cellSizeForTable(TableView* table);
    virtual ssize_t numberOfCellsInTableView(TableView* table);
    
    virtual void scrollViewDidScroll(ScrollView* view){}
    virtual void scrollViewDidZoom(ScrollView* view){}
    
    void createTableViewCell(Node* cell, TableView* table, int idex);
    void rushHead();
    
private:
    
};

// 照片头像
class PhotoHeadIcon : public Layer, public TableViewDataSource, public TableViewDelegate
{
public:
    
    PhotoHeadIcon();
    ~PhotoHeadIcon();
    
    virtual bool init();
    CREATE_FUNC(PhotoHeadIcon);
    void InitTabelView(int count);
    virtual void tableCellTouched(TableView* table, TableViewCell* cell);
    virtual TableViewCell* tableCellAtIndex(TableView* table, ssize_t idex);
    virtual Size cellSizeForTable(TableView* table);
    virtual ssize_t numberOfCellsInTableView(TableView* table);
    
    virtual void scrollViewDidScroll(ScrollView* view){}
    virtual void scrollViewDidZoom(ScrollView* view){}
    
    void createTableViewCell(Node* cell, TableView* table, int idex);
    
    void rushHead();
private:
    int mPhotoNum;
};

// 荣誉头环
class HeadRing : public Layer, public TableViewDataSource, public TableViewDelegate
{
public:
    
    HeadRing();
    ~HeadRing();
    
    virtual bool init();
    CREATE_FUNC(HeadRing);
    
    virtual void tableCellTouched(TableView* table, TableViewCell* cell);
    virtual TableViewCell* tableCellAtIndex(TableView* table, ssize_t idex);
    virtual Size cellSizeForTable(TableView* table);
    virtual ssize_t numberOfCellsInTableView(TableView* table);
    
    virtual void scrollViewDidScroll(ScrollView* view){}
    virtual void scrollViewDidZoom(ScrollView* view){}
    
    void createTableViewCell(Node* cell, TableView* table, int idex);
    
    
private:
    
};

// 选择地区
class HeadRingInfo : public CPZLayer
{
public:
    HeadRingInfo();
    ~HeadRingInfo();
    
    virtual bool init();
    CREATE_FUNC(HeadRingInfo);
    
    virtual bool onTouchBegan(Touch* pTouch,Event* pEvent);
    virtual void onTouchEnded(Touch* pTouch,Event* pEvent);
    void InitItemInfo(item itemInfo);
    
    void UseClick(Ref* pSender);
    void XiexiaClick(Ref* pSender);
private:
    item mCurItem;
    bool isTouchIn;
};
// 选择地区
class XuanzeDiqu : public CPZLayer, public TableViewDataSource, public TableViewDelegate
{
public:
    XuanzeDiqu();
    ~XuanzeDiqu();
    
    virtual bool init();
    CREATE_FUNC(XuanzeDiqu);
    
    virtual void tableCellTouched(TableView* table, TableViewCell* cell);
    virtual TableViewCell* tableCellAtIndex(TableView* table, ssize_t idex);
    virtual Size cellSizeForTable(TableView* table);
    virtual ssize_t numberOfCellsInTableView(TableView* table);
    
    virtual void scrollViewDidScroll(ScrollView* view){}
    virtual void scrollViewDidZoom(ScrollView* view){}
    
    virtual bool onTouchBegan(Touch* pTouch,Event* pEvent);
    virtual void onTouchEnded(Touch* pTouch,Event* pEvent);
    
protected:
    Size getTableSize();
    void createTableViewCell(Node* cell, TableView* table, int idex);
    
private:
    std::map<int,std::string> hInfo;
    bool isTouchIn;
};
// 喜欢
class XiHuan : public Layer
{
public:
    XiHuan();
    ~XiHuan();
    
    virtual bool init();
    CREATE_FUNC(XiHuan);
    
    void XihuanClick(cocos2d::Ref *pSender);   //喜欢
    
    void InitInfo(std::vector<TestAtt> info);
    
    //void SetXihuan(std::vector<xihuanInfo> info){m_xihuaninfo = info;}
    //std::vector<xihuanInfo> m_xihuaninfo;
};

// 照片
class ZhaoPian : public Layer, public TableViewDataSource, public TableViewDelegate
{
public:
    ZhaoPian();
    ~ZhaoPian();
    
    virtual bool init();
    CREATE_FUNC(ZhaoPian);
    
    virtual void tableCellTouched(TableView* table, TableViewCell* cell);
    virtual TableViewCell* tableCellAtIndex(TableView* table, ssize_t idex);
    virtual Size cellSizeForTable(TableView* table);
    virtual ssize_t numberOfCellsInTableView(TableView* table);
    
    virtual void scrollViewDidScroll(ScrollView* view){}
    virtual void scrollViewDidZoom(ScrollView* view){}
    
    void InitTabelView(std::vector<std::string> arr);
    void SenMSG(float ft);
private:
    int m_spHeadNum;
    bool m_isShowAdd;
    std::vector<std::string> mPotoArr;
};

// 照片
class ZhaoPianView : public Layer, public TableViewDataSource, public TableViewDelegate
{
public:
    ZhaoPianView();
    ~ZhaoPianView();
    
    virtual bool init();
    CREATE_FUNC(ZhaoPianView);
    
    virtual void tableCellTouched(TableView* table, TableViewCell* cell);
    virtual TableViewCell* tableCellAtIndex(TableView* table, ssize_t idex);
    virtual Size cellSizeForTable(TableView* table);
    virtual ssize_t numberOfCellsInTableView(TableView* table);
    
    virtual void scrollViewDidScroll(ScrollView* view){}
    virtual void scrollViewDidZoom(ScrollView* view){}
    
    void InitTabelView(std::string arr,int mCount);
    
private:
    std::string mIcon;
};

// 游戏数据
class GameInfo : public Layer
{
public:
    enum
    {
        TAG_NONE,
        TAG_GERENRONGYUBTN,
        TAG_BISAIJILUBTN,
        TAG_HEADCHOSE,
        TAG_HEADBTN,
        TAG_HEADICON
    };
    GameInfo();
    ~GameInfo();
    
    virtual bool init();
    CREATE_FUNC(GameInfo);
    
    void GerenClick(cocos2d::Ref *pSender);
    void BisaiClick(cocos2d::Ref *pSender);
    void HeadClick(cocos2d::Ref *pSender);   //头像
    void SetBtnToTouch();
    void resHeadImg(int count);
    void setHeadIcon();
private:
    int m_spHeadNum;
};

// 个人荣誉
class GerenRongYu : public Layer
{
public:
    GerenRongYu();
    ~GerenRongYu();
    
    virtual bool init();
    CREATE_FUNC(GerenRongYu);
    void InitRongyu(std::vector<season_rank> arr);
    void ShowUI(float fx,season_rank info);
    void GameClick(cocos2d::Ref *pSender);
    void BisaiClick(cocos2d::Ref *pSender);
    void SenMSG(float ft);
private:
    int m_spHeadNum;
};

// 比赛
class BisaiJilu : public Layer, public TableViewDataSource, public TableViewDelegate
{
public:
    BisaiJilu();
    ~BisaiJilu();
    
    virtual bool init();
    CREATE_FUNC(BisaiJilu);
    
    virtual void tableCellTouched(TableView* table, TableViewCell* cell);
    virtual TableViewCell* tableCellAtIndex(TableView* table, ssize_t idex);
    virtual Size cellSizeForTable(TableView* table);
    virtual ssize_t numberOfCellsInTableView(TableView* table);
    
    virtual void scrollViewDidScroll(ScrollView* view){}
    virtual void scrollViewDidZoom(ScrollView* view){}
    
    void GameClick(cocos2d::Ref *pSender);
    void GerenClick(cocos2d::Ref *pSender);
    void SenMSG(float ft);
    void InitBisai(std::vector<bisaiInfo> arr);
protected:
    Size getTableSize();
    void createTableViewCell(Node* cell, TableView* table, int idex);
    
private:
    //TableView* tableView;
    std::vector<bisaiInfo>  infos;
};


// 个人荣誉
class ZhanDui : public Layer
{
public:
    ZhanDui();
    ~ZhanDui();
    
    virtual bool init();
    CREATE_FUNC(ZhanDui);
private:
    int m_spHeadNum;
};


// 留言
class LiuYan : public Layer, public TableViewDataSource, public TableViewDelegate, public ui::EditBoxDelegate
{
public:
    LiuYan();
    ~LiuYan();
    
    virtual bool init();
    CREATE_FUNC(LiuYan);
    
    virtual void tableCellTouched(TableView* table, TableViewCell* cell);
    virtual TableViewCell* tableCellAtIndex(TableView* table, ssize_t idex);
    //virtual Size cellSizeForTable(TableView* table);
    virtual Size tableCellSizeForIndex(TableView *table, unsigned int idx);
    virtual ssize_t numberOfCellsInTableView(TableView* table);
    
    virtual void scrollViewDidScroll(ScrollView* view){}
    virtual void scrollViewDidZoom(ScrollView* view){}
    
    void FasongClick(cocos2d::Ref *pSender);
    void ShuaxinClick(cocos2d::Ref *pSender);
    virtual void editBoxReturn(cocos2d::ui::EditBox* editBox);
    
    void InitHotLiuyan(std::vector<LiuyanInfo> hotArr);
    void InitLiuyan(std::vector<LiuyanInfo> hotArr);
    
    void SenMSG(float ft);
    
    void HotZanClick(cocos2d::Ref *pSender);
    void HotJubaoClick(cocos2d::Ref *pSender);
    void ZanClick(cocos2d::Ref *pSender);
    void JubaoClick(cocos2d::Ref *pSender);
protected:
    Size getTableSize();
    void createTableViewCell(Node* cell, TableView* table, int idex);
    
private:
    //TableView* tableView;
    std::vector<LiuyanInfo>  infos;
    std::vector<LiuyanInfo>  hotInfo;
    int m_curpage;
};

#endif /* PersonCenterLayer_h */
