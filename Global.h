#ifndef _GLOBAL_H_
#define _GLOBAL_H_
#pragma once

#include "Singleton.h"
#include "cocos2d.h"
#include "cocos-ext.h"
#include "spine/Json.h"

USING_NS_CC;
USING_NS_CC_EXT;
#define PormBoxTag  1000

#include "Button.h"
//#include "RichLabel.h"
#include "msgStru.h"
#include "struct.pb.h"
using namespace com::suyin::proto;


#include "Common.h"
//客户端测试算法控制宏
//#define EditEXE

#define PRI _pri(this)

#define winSize Director::getInstance()->getWinSize()

//int monthArray[22] = {0,1,2,3,4,5,6,8,10,12,15,18,21,24,30,36,42,48,54,60,66,72};

inline int _pri(Node* _this)
{
    int pri = -128 - _this->getLocalZOrder();
    Node* node = _this;
    while(node)
    {
        node=node->getParent();
        if (dynamic_cast<Layer*>(node)) {
            pri -= node->getLocalZOrder();
        }
    }
    return pri;
}



class Global : public Singleton<Global>
{
public:
	Global(void);
	~Global(void);	
	const char * getString(const char* en);
    
    
    // 2016-03-05
    void SetGridSize(cocos2d::Size size)
    {
        gridSize = size;
    }
    
    cocos2d::Size GetGridSize()
    {
        return gridSize;
    }

    void SetGridPos(cocos2d::Point pos)
    {
        gridPos = pos;
    }
    
    cocos2d::Point GetGridPos()
    {
        return gridPos;
    }

	void SetRoomId(uint32_t roomid)
	{
		roomId = roomid;
	}

	uint32_t GetRoomId()
	{
		return roomId;
	}
    
    void SetMainNodeID(uint32_t nodeid)
    {
        mainID = nodeid;
    }
    
    uint32_t GetMainNodeID()
    {
        return mainID;
    }
    
    void SetMainPos(cocos2d::Point pos)
    {
        mainPos = pos;
    }
    
    cocos2d::Point GetMainPos()
    {
        return mainPos;
    }
    
    void SetCenterPos(cocos2d::Point pos)
    {
        centerPos = pos;
    }
    
    cocos2d::Point GetCenterPos()
    {
        return centerPos;
    }
    
    void SetMainPicIndex(int idx)
    {
        mainPicIndex = idx;
    }
    
    int GetMainPicIndex()
    {
        return mainPicIndex;
    }
    
    void setMainNodeInfo(nodeInfo info)
    {
        mainNodeInfo = info;
    }
    
    nodeInfo getMainNodeInfo()
    {
        return  mainNodeInfo;
    }

    static std::string getDataPath(std::string fileName)
    {
        std::string path = FileUtils::getInstance()->getWritablePath();
        path.append(fileName);
        return path;
    }
    
    void addMianNode(uint32_t nodeid);
    void deleteMainNode(uint32_t nodeid);
    void clearMainNodes();
    bool IsMainNode(uint32_t nodeid);
    int getMainNodeNum();
    std::vector<uint32_t> getMainNodes();
    
    void setJsonImageHead(int ft);
    int getJsonImageHead();
    void setJsonUpCameraSize(int upCamera);
    int getJsonUpCameraSize();
    void setJsonUpCameraScale(float ft);
    float getJsonUpCameraScale();
    
    void setConnectState(bool flag);
    bool getConnectState();
    int  getRand(int maxCount);
    
    std::vector<netInfo> getNetInfos();
    void addNetInfos(netInfo info);
    
    void PlayBackMusci(const char* music);
    void StopBackMusci();
    void PlayEffect(const char* music);
    
    void SetUserInfo(user_info info){m_UserInfo=info;}
    user_info GetUserInfo(){return m_UserInfo;}

	//张锋露
	void SetplayerDengLuInfo(player_info info){ m_PlayerDengLuInfo = info; }
	player_info GetPlayerDengLuInfo(){ return m_PlayerDengLuInfo; }
	//张锋露
	void SetAccountInfo(account_info info){ m_AccountInfo = info; }
	account_info GetAccountInfo(){ return m_AccountInfo; }
	//倒计时
	void SetZuDuiDaoJiShiInfo(zuduidaojishi_info info){ m_ZuDuiDaoJiShi = info; }
	zuduidaojishi_info GetZuDuiDaoJiShiInfo(){ return m_ZuDuiDaoJiShi; }

	//燃烧远征组队 对应的消耗及其奖励信息
	void SetAwardInfo(AwardInfo info){ m_AwardInfo = info; }
	AwardInfo GetAwardInfo(){ return m_AwardInfo; }

	//以 某个符号标记 分割字符串数组
	std::vector<std::string> split(std::string str, std::string pattern)
	{
		std::string::size_type pos;
		std::vector<std::string> result;
		str += pattern;//扩展字符串以方便操作
		int size = str.size();

		for (int i = 0; i < size; i++)
		{
			pos = str.find(pattern, i);
			if (pos < size)
			{
				std::string s = str.substr(i, pos - i);
				result.push_back(s);
				i = pos + pattern.size() - 1;
			}
		}
		return result;

	}

    void EquipUpdate(int type,int iteID);
    void HeroLeveUp(int heroID,int heroLeve);
    
    void SetplayerInfo(user_info info){m_PlayerInfo=info;}
    user_info GetPlayerInfo(){return m_PlayerInfo;}
    
    std::string ComPlayerName(std::string mName);
    
    void SetShopItems(std::vector<shop_item> items);
    std::vector<shop_item> GetShopItems();
    void AddItemForBag(int mId,user_bag info);
    user_bag GetBagItem(int mID);
    std::map<int,user_bag> GetBagMap(){return mUserBag;}
    
    void ShowPromBox(const char* msg);
    void ShowPromMoveBox(std::vector<item> vec);
    
    NameColor GetNameColor(std::string& name);
    int GetFightType(){return mCurFightType;}
    void SetFightType(int fight){mCurFightType = fight;}
    std::vector<QianDaoUse> GetQiandao(){return mQianDaoInfo;}
    void SetQiandao(std::vector<QianDaoUse> info){mQianDaoInfo = info;}
private:
    void addInfoInDoc(rapidjson::Document& writedoc,Json* root,rapidjson::Document::AllocatorType& allocator);
    void pareObject(rapidjson::Value& object,Json* root,rapidjson::Document::AllocatorType& allocator);
    void pareArray(rapidjson::Value& array,Json* root,rapidjson::Document::AllocatorType& allocator);
    
    
	__Dictionary *mStringDict;
    
    cocos2d::Size gridSize;
    cocos2d::Point gridPos;
	uint32_t roomId;;
    uint32_t  mainID;
    cocos2d::Point mainPos;
    cocos2d::Point centerPos;
    nodeInfo  mainNodeInfo;
    int  mainPicIndex;
    std::vector<uint32_t> m_mainIDs;
    
    int  m_imageHeadSize;
    int  m_perUpCamera;
    float  m_perUpCameraScale;
    
    bool m_isConnecting;
    
    std::vector<netInfo> m_nets;
    user_info m_UserInfo;
    
    user_info m_PlayerInfo;
	player_info m_PlayerDengLuInfo;
	zuduidaojishi_info m_ZuDuiDaoJiShi;
	AwardInfo m_AwardInfo;
	account_info m_AccountInfo;
    std::vector<nameMap> mComName;
    std::vector<shop_item>  shopItems;
    std::map<int,user_bag>  mUserBag;
    std::vector<NameColor> mNameColor;
    std::vector<QianDaoUse> mQianDaoInfo;
    int mCurFightType;
};

class CPZLayer : public Layer{
public:
    CPZLayer(void){}
    ~CPZLayer(void){}
    CREATE_FUNC(CPZLayer);
    virtual bool init();
    virtual void registerWithTouchDispatcherEx();
    virtual bool onTouchBegan(Touch* pTouch,Event* pEvent);
};

Json* ReadJson(const char* path);

class CCPromBox : public CPZLayer
{
public:
    enum tag
    {
        tag_menu,
    };
    CCPromBox();
    ~CCPromBox();
    virtual bool init();
    CREATE_FUNC(CCPromBox);
    void SetTypeAndValue(const char* msg);
    virtual bool onTouchBegan(Touch* pTouch,Event* pEvent);
    virtual void onTouchEnded(Touch* pTouch,Event* pEvent);
private:
    bool isTouchIn;
};

class CCPromMoveBox : public CPZLayer
{
public:
    enum tag
    {
        tag_menu,
    };
    CCPromMoveBox();
    ~CCPromMoveBox();
    virtual bool init();
    CREATE_FUNC(CCPromMoveBox);
    void SetTypeAndValue(std::vector<item> vec);
    virtual bool onTouchBegan(Touch* pTouch,Event* pEvent);
    virtual void onTouchEnded(Touch* pTouch,Event* pEvent);
private:
    bool isTouchIn;
};
#endif
