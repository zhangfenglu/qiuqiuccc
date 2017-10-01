//
//  MainScene.h
//  qiuFight
//
//  Created by ��Ծ�� on 16/2/24.
//
//

#ifndef MainScene_h
#define MainScene_h

#include "Global.h"

#pragma once
#include "cocos2d.h"
USING_NS_CC;
#include "WebSocketLayer.h"

class MainScene : public Layer
{
public:
	enum tagDif
	{
		TAG_NONE,
		TAG_LAYER_LOGIN,
		TAG_LAYER_PERSON,
		TAG_LAYER_RELATION,
		TAG_LAYER_RANKING,
		TAG_LAYER_SHOPSYM,
		TAG_LAYER_DIAMOND,
		TAG_LAYER_SHOP,
		TAG_LAYER_SCENE,
		TAG_LAYER_TUANDUI,
		//TAG_LAYER_SOCKET,
		TAG_LAYER_GRID,
		TAG_LAYER_JOY,
		TAG_LAYER_USERINFO,
		TAG_GAME_END,
		TAG_GAME_COLOR_BG,
		TAG_MAX
	};
	MainScene();
	~MainScene();
	virtual bool init();
	CREATE_FUNC(MainScene);
	void initJson();

	//static CCScene* scene();

	void initBackLayer();

	virtual void onTouchesBegan(const std::vector<Touch*>& touches, Event* pEvent);
	virtual void onTouchesMoved(const std::vector<Touch*>& touches, Event* pEvent);
	virtual void onTouchesEnded(const std::vector<Touch*>& touches, Event* pEvent);

	virtual void update(float ft);
	//void updateFrame(float ft);

	void enterGame(const char* nick, int key);

	void setWinSize(const cocos2d::network::WebSocket::Data &data);
	void addSelfNode(const cocos2d::network::WebSocket::Data &data);
	void updateNodes(const cocos2d::network::WebSocket::Data &data);
	// ����ս��������
	void updateRankeInFight(const cocos2d::network::WebSocket::Data &data);
	// ս������
	void GameOverState(const cocos2d::network::WebSocket::Data &data);
	// ��������
	void UpdateFightLife(const cocos2d::network::WebSocket::Data& data);
	// ����
	void SetDeath(const cocos2d::network::WebSocket::Data& data);


	void updateMainState(cocos2d::Point mainPos);

	void notifyEject();
	void notifySplite();

	void endSplit(float dt);

	void deleteMainNode(uint32_t nodeid);
	cocos2d::Point calculateBorder(cocos2d::Point pos, uint32_t size);

	void updateSceneSize(float siz);

	int getMainNodesSize();
	int getMainNodesMass();
	float getCameraScale();

	void CheckLayer(tagDif tag);
	void BackToLoginLayer(tagDif tag);

	bool OpenWebSocket(const char* ipAddress, const char* port);
	void UpdateScaleByMainNodes();
	void CloseFight();
	// ֱ�Ӹ��³ߴ�
	void UpdateScaleImmediately(float diff);
	bool IsNeedToUpdateScale();
	void CloseWebNet();

	// c->s
	void loginGame(); //���������
	void reqDuanXianChongLian();//��������
	void reqZuDui();//�������
	void reqQuXiaoZuDui();//ȡ�����
	void reqServerList();
	void reqServerList1(float f);
	void reqServerKey(int netID, int modeID, int ticket_count); // mode 0,1
	void reqShopList();
	void reqBuyItem(int itemID);
	void reqUseItem(int itemID);
	void reqUnequipItem(int itemType);
	void reqUpHero();
	void reqSetFocus(int type, int set, int roleID);
	void reqRole(int roleID);
	void reqFans(int type, int rang1, int rang2, int roleid);
	void reqRanks(int type, int subtype);
	void reqGmInfo(const char* a, int id = 0, int count = 0);
	void reqHotMsg(int roleID);
	void reqGetMsg(int roleID, int rang1, int rang2);
	void reqSendMsg(int roleID, std::string content);
	void reqLikeMsg(int roleID, int msgID, int set); // set 1��like�� 0��ȡ��like
	void reqFriendList(int type);
	void reqAddFriend(int roleID, std::string name); // ��ѡһ
	void reqResponseAdd(int flag, int roleID); // flag 1 ok, 0 cancel
	void reqSeasonRank(int roleID);
	void reqGameRecord(int roleID);
	void reqSendPhoto(int slot, std::string dataStr);
	void reqGetPhoto(int roleID);
	void reqSetName(std::string name, std::string passwd, int sex);
	void reqSetSex(int sex);
	void reqSetDesc(std::string desc);
	void reqSetGeo(int province);
	void reqSetIcon(int icon, std::string data);
	void reqGetTickets();
	void reqIcons(std::vector<int> iconList);
	void reqExitFight();
	void reqSign();
	void reqAward();

	//��ʾս������ ���н�����Ϣ
	void showFightOverPaiHangInfo();
	//��ʾս������ ��λ���н�����Ϣ
	void showFightOverDuanWeiInfo();

	//static  UM_BattleResult _rep;
	std::vector<paihangplayerInfo> paihangInfos;

	struct myFuncton
	{
		bool operator()(const paihangplayerInfo &n1, const paihangplayerInfo &n2)
		{
			return n1.rank < n2.rank;
		}
	};

	// common
	void reqSendUIMsg(uint16_t type, std::string str);

	// s->c
	void setPlayerInfo(const cocos2d::network::WebSocket::Data &data);
	//��ȡ��������������
	void respDuanXianChongLian(const cocos2d::network::WebSocket::Data &data);
	//��ȡ���������Э�鴦��
	void respZuDui(const cocos2d::network::WebSocket::Data &data);
	//��ȡ������ȡ�����Э�鴦��
	void respQuXiaoZuDui(const cocos2d::network::WebSocket::Data &data);
	//��ȡ������ս��׼��Э��
	void respZhanDouZhunBei(const cocos2d::network::WebSocket::Data &data);
	void respSyncRole(const cocos2d::network::WebSocket::Data &data);
	void respServerList(const cocos2d::network::WebSocket::Data& data);
	void respServerKey(const cocos2d::network::WebSocket::Data& data);
	void respErrors(const cocos2d::network::WebSocket::Data& data);
	void respShopList(const cocos2d::network::WebSocket::Data& data);
	void respHeroUp(const cocos2d::network::WebSocket::Data& data);
	void respEquipUpdate(const cocos2d::network::WebSocket::Data& data);
	void respItemUpdate(const cocos2d::network::WebSocket::Data& data);
	void respRoleInfo(const cocos2d::network::WebSocket::Data& data);
	void respFans(const cocos2d::network::WebSocket::Data& data);
	void respRanks(const cocos2d::network::WebSocket::Data& data);
	void respFightLikes(const cocos2d::network::WebSocket::Data& data);
	void respHotMsg(const cocos2d::network::WebSocket::Data& data);
	void respMsgList(const cocos2d::network::WebSocket::Data& data);
	void respFriendList(const cocos2d::network::WebSocket::Data& data);
	void respAddFriend(const cocos2d::network::WebSocket::Data& data);    // ��Ӻ���
	void respAddInvite(const cocos2d::network::WebSocket::Data& data); // �������
	void respDelInvite(const cocos2d::network::WebSocket::Data& data); // ɾ������
	void respSeasonRank(const cocos2d::network::WebSocket::Data& data);
	void respGameRecord(const cocos2d::network::WebSocket::Data& data);
	void respPhotos(const cocos2d::network::WebSocket::Data& data);
	void respIcons(const cocos2d::network::WebSocket::Data& data);
	void respAwardList(const cocos2d::network::WebSocket::Data& data);    //���½����б�

	void reqReLogin();

	// ս�������߼�
	void reLogin(float ft);
	
	//�ϲ�������--0924--ע������� start======================================================================
	//׼��ս������ʱ
	void readyFightDaoJiShi();
	//����ս��׼������ʱ
	void delteReadyFightDaoJiShi();
	//���� ����
	void hideXingXing1();
	void hideXingXing2();
	void hideXingXing3();
	void hideXingXing4();
	void hideXingXing5();
	void hideXingXing6();
	void hideXingXing7();
	//�ϲ�������--0924--ע������� end======================================================================
	
	void reOpenSocket();
	void reConnectFightServer(float ft);
	void reSetNetKey(int netID, int netKey);
	void confirmReConnectFighting();
	void cancelReConnectFighting();
	// end

	void reRebirth();
	cocos2d::Point getMoveDiff(){ return m_diff; }


	//ͨ��id ս������ ���а� ����id�õ�����
	paihangAward getPaiHangAwardById(int id);
	std::vector<paihangAward> paihangAwards;

	//ͨ����λ grade ��ȡ ���а��λ��Ϣ
	duanweipaihang_info getPaiHangDuanWeiByGrade(int grade);

	bool nodeComparisonLess(Node* n1,Node*n2);
	//std::vector<UM_PlayerInfo> pInfos;

	void MutUpdate(float dt);

	Node* paiHangNode;


	(cocos2d::ui::ImageView*) liangxing1  ;
	(cocos2d::ui::ImageView*) liangxing2 ;
	(cocos2d::ui::ImageView*) liangxing3;
	(cocos2d::ui::ImageView*) liangxing4;
	(cocos2d::ui::ImageView*) liangxing5;
	(cocos2d::ui::ImageView*) liangxing6;
	(cocos2d::ui::ImageView*) liangxing7;
	(cocos2d::ui::ImageView*) anxing1;
	(cocos2d::ui::ImageView*)anxing2;
	(cocos2d::ui::ImageView*) anxing3;
	(cocos2d::ui::ImageView*)anxing4;
	(cocos2d::ui::ImageView*)anxing5 ;
	(cocos2d::ui::ImageView*)anxing6 ;
	(cocos2d::ui::ImageView*) anxing7;
	(cocos2d::ui::ImageView*) xing8bg ;
	(cocos2d::ui::Text*) xingNum;
	(cocos2d::ui::ImageView*) anxing1action;
	(cocos2d::ui::ImageView*) anxing2action ;
	(cocos2d::ui::ImageView*) anxing3action;
	(cocos2d::ui::ImageView*)anxing4action;
	(cocos2d::ui::ImageView*) anxing5action ;
	(cocos2d::ui::ImageView*)anxing6action ;
	(cocos2d::ui::ImageView*) anxing7action ;
	(cocos2d::ui::ImageView*) liangxing1action;
	(cocos2d::ui::ImageView*) liangxing2action;
	(cocos2d::ui::ImageView*) liangxing3action ;
	(cocos2d::ui::ImageView*) liangxing4action;
	(cocos2d::ui::ImageView*)liangxing5action ;
	(cocos2d::ui::ImageView*) liangxing6action;
	(cocos2d::ui::ImageView*) liangxing7action;






#ifdef EditEXE
	void UpdataWeight(int weight);
#endif
protected:
	void resetUpdateCamera(float ft);

private:
	Node* daojishiNode;        //�ϲ�������--0924--ע������� 
	cocos2d::Point m_diff;

	bool m_isFirstEnter;
	bool m_isSplit;

	float  m_initialSpeed;      // json����ĳ�ʼ�ٶ�
	float  m_attenuationSpeed;  // json˥���ٶ�
	float  m_sceneScale;        // json�������ű�

	float  m_scale;

	float  m_tempScale;
	float  m_minScale;          // json��С���ű�

	float listX;
	float listY;
	float listHeight;

	float jiangX;
	float jiangY;
	float jiangWidth;

	float tishiX;
	float tishiY;

	cocos2d::Point  m_grid_off_pos;

	bool m_isUpdateScale;
	tagDif  m_CurrTag;
	bool m_isFistGetItem;

	bool m_isFighting;          // �Ƿ���ս����
	std::string  m_ipAddress;   // ս������IP��ַ
	std::string  m_ipPort;      // ս�����Ķ˿�
	int m_netKey;               // ս��key

};


//

class ZhanDouEnd : public Layer, public TableViewDataSource, public TableViewDelegate
{
public:
	enum
	{
		TAG_NONE,
		TAG_LEFT_BTN,
		TAG_RIGHT_BTN,
		TAG_LOW_LAYER,
		TAG_LEFT_LAYER,
		TAG_RIGHT_LAYER
	};
	ZhanDouEnd();
	~ZhanDouEnd();

	virtual bool init();
	CREATE_FUNC(ZhanDouEnd);

	void InitRank();

	virtual void tableCellTouched(TableView* table, TableViewCell* cell);
	virtual TableViewCell* tableCellAtIndex(TableView* table, ssize_t idex);
	virtual cocos2d::Size cellSizeForTable(TableView* table);
	virtual ssize_t numberOfCellsInTableView(TableView* table);

	virtual void scrollViewDidScroll(ScrollView* view){}
	virtual void scrollViewDidZoom(ScrollView* view){}

	cocos2d::Size getTableSize();
	void createTableViewCell(Node* cell, TableView* table, int idex);

	void resetBtnState();
	void clickLeft(Ref* pSender);
	void clickRight(Ref* pSender);

	void ReturnBegan(Ref* pSender);

	void setInfos(std::vector<EndGame1> infos, std::vector<Relation2Me1> relas);
	void setLikes(std::vector<EndGame2> infos);

	void clickGuanzhu(Ref* pSender);
	void clickXihuan(Ref* pSender);

	void ShowUserLowInfo();
	void ResSetFans();
	void ResAddFriend();
	std::string getIconString(int roleID, std::vector<icon_data> datas);
	void resIcon(std::vector<icon_data> arr);
private:
	EndGame1 getEndGame1ById(int roleID, std::vector<EndGame1> infos);
	Relation2Me1 getRela1ById(int roleID, std::vector<Relation2Me1> infos);
	EndGame2 getEndGame2ById(int roleID, std::vector<EndGame2> infos);

	std::vector<EndGame> mRankVec;
	std::vector<Relation2Me> mRelaVec;
	std::vector<EndGame2> mEndVec;
	bool  infoFlag;
	bool  likeFlag;
	int   mTouchDex;
	int   mCurTouch;
};

//������ѽ���

class AddFriend : public Layer
{
public:
	AddFriend();
	~AddFriend();

	virtual bool init();
	CREATE_FUNC(AddFriend);

	void InitFriend(friend_info info);
	void clickOK(Ref* pSender);
	void clickCancel(Ref* pSender);
private:
	friend_info m_friend;
};


class UserLow : public CPZLayer
{
public:
	enum
	{
		TAG_NONE,
		TAG_LEFT_BTN,
		TAG_RIGHT_BTN
	};
	UserLow();
	~UserLow();

	virtual bool init();
	CREATE_FUNC(UserLow);

	virtual bool onTouchBegan(Touch* pTouch, Event* pEvent);
	virtual void onTouchEnded(Touch* pTouch, Event* pEvent);

	void InitLike(EndGame info);

	void clickXihuan(Ref* pSender);
	void clickGuanzhu(Ref* pSender);

	void ResSetFans();
	void ResAddFrieng();
private:
	bool isTouchIn;
	EndGame mTouchInfo;
};

class ReqOpenFight : public CPZLayer
{
public:
	enum
	{
		TAG_NONE,
		TAG_LEFT_BTN,
		TAG_RIGHT_BTN
	};
	ReqOpenFight();
	~ReqOpenFight();

	virtual bool init();
	CREATE_FUNC(ReqOpenFight);

	virtual bool onTouchBegan(Touch* pTouch, Event* pEvent);
	virtual void onTouchEnded(Touch* pTouch, Event* pEvent);

	void clickOK(Ref* pSender);

private:
	bool isTouchIn;
};

struct Goods_Infors
{
    Goods_Infors()
    {
        strName = "";
        strPath = "";
    }
    std::string  strName;
    std::string  strPath;
};
class GameOverLayer : public cocos2d::Layer
{
public:
    GameOverLayer();
    static  GameOverLayer* createGameOver(const BattleResault& stRsault);
    void    init(const BattleResault& stRsault);
    //CREATE_FUNC(GameOverLayer);
public:
    void setOverData(const BattleResault& stRsault);
private:
    void ReturnBegan(Ref* pSender);
    Goods_Infors  findGoodsInfor(int nID);
    bool getPropConfig(const std::string& strPath);
    void showRank(const BattleResault& stResault);
    void showGoodsList(const BattleResault& stResault);
    std::string  getResPath(const BattleResault& stResault);
protected:
    cocos2d::ui::Button*      m_textContineGame;
    Node*                    m_nodeParent;
    cocos2d::ui::ListView*      m_listGoods;
    cocos2d::ui::Widget*   m_defaulttItem;
    std::map<int, Goods_Infors> m_mapPropCfg;
};

#endif /* MainScene_h */
