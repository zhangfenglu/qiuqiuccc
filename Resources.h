
#pragma once

#define MAX_REWARD_ITEM 5
#define MAX_TASK_FINISH 2
#define MAX_SKILL_MONSTER 10

#include <list>
#include <map>
#include <vector>

#include "SqliteDataProvider.h"
#include "cocos2d.h"
 
#include "Global.h"

//#include "RoleDataManager.h"
//#include "ActiveLevel.h"


#define GUIDE_PLAYER_BATTLE_TASK_ID		1300
#define GUIDE_PLAYER_BATTLE_MAP_ID		2001
#define MAX_EQUIP_STAR_ITEM_NUM			4
#define MAX_RELA_ATTR 10

template <typename T>
struct string_to: public std::unary_function<std::string, T>
{
    T
    operator()(const std::string& s) const
    {
        std::istringstream is(s);
        T value;
        is >> value;
        return value;
    }
};
//typedef std::map<int,SAIStateInfoEntry> AIStateMap;
/**
 * The high level interface to the database. Through the storage you can access
 * all characters, guilds, worlds states, transactions, etc.
 */
class Resource
{
public:
    ~Resource();
	
    static Resource * sharedResource();

    void open();
    void close();
    
    void writeDb();
   
    item getItemForID(int itemId);
	nameMap getPiFuForID(int pifuId);
    void GetComName(std::vector<nameMap> &vec);
	
    ChildItem GetShopItem(int itemID);
    
    void GetComposeItem(std::vector<itemInfo>& arr);

	void GetDuanweiItem(std::vector<duanweiInfo>& arr);
    duanweiInfo GetDuanweiInfo(int mID);
    
    void GetNameColorList(std::vector<NameColor>& arr);

	void getDiamondInfoAndroid(std::vector<DiamondInfo>& arr);
	void getDiamondInfoIos(std::vector<DiamondInfo>& arr);

	void getItemInfos(std::vector<ItemInfo>& arr);
	void getGoodsInfos(std::vector<GoodsInfo>& arr);


public:
	ValueMap stringData;				// 本地数据
private:
        
    Resource();
    Resource(const Resource &rhs);
    Resource &operator=(const Resource &rhs);

    SqLiteDataProvider *mDb; /**< the data provider */
    //
    //AIStateMap mAIStateMap;

};


