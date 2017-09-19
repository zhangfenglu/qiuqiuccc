//
//  Common.h
//  qiuFight
//
//  Created by 张跃东 on 16/3/3.
//
//

#ifndef Common_h
#define Common_h

#pragma once

#include "cocos2d.h"
#include "cocos-ext.h"


USING_NS_CC;
USING_NS_CC_EXT;

#define  INITIAL_SPEED          10       //初始速度
#define  ATTENUATION_SPEED      0.01     //衰减速度
#define  MINIMUM_SPEED          1       //最小速度

#define R_LENGTH                60      //内圈圆的半径

#define MINIMUM_SIZE            32      //最小时候体积

#define MAXIMUM_PICTURE_NUM     40       //图片的最大数量

#define MINMUN_PLAYER_SCALE_OR  0.05    //player初始化时候的缩放比

#define PLAYER_PIX_SIZE         300 * 2
#define CI_PIX_SIZE             155 * 2
#define FOOD_PIX_SIZE           18 * 2

#define MASS_FORM_SIZE_PERCENT  0.01

#define DISTANCE_PER_CIRCLE     2000    // 球与球之间的距离来进行缩放

//质量和相机比例的关系
#define MASS_PERCENT_1          100
#define MASS_PERCENT_2          500
#define MASS_PERCENT_3          1500
#define MASS_PERCENT_4          5000
#define MASS_PERCENT_5          10000
#define MASS_PERCENT_6          22500
//比例
#define MAIN_CAMERA_SCALE_1     0.9
#define MAIN_CAMERA_SCALE_2     0.8
#define MAIN_CAMERA_SCALE_3     0.7
#define MAIN_CAMERA_SCALE_4     0.6
#define MAIN_CAMERA_SCALE_5     0.5
#define MAIN_CAMERA_SCALE_6     0.4

//相机变化 公式曲线类型 ：y=ax^k+b
#define K_VALUE                 -0.04
#define A_VALUE                 2.47667
#define B_VALUE                 -1.25875


struct iconInfo
{
    int			id ;
    std::string name;
};

struct itemInfo
{
    int			id;
    std::string name;
    std::string resName;
    int			index;
    int         mNum;
};

struct eatInfo
{
    uint32_t eatID;
    uint32_t eatedID;
};


struct AwardInfo
{
	AwardInfo()
	{
		title = "";
		xiaohao = "";
		allawards = "";
	}
	std::string title;
	std::string xiaohao;
	std::string allawards;
};

struct nodeInfo
{
	std::string name;
    uint32_t nodeID;
    int32_t posx;
    int32_t posy;
    int32_t heroid;
    int32_t heroleve;
    int32_t guanghuan;
    int32_t baozi;
    int32_t canying;
    int32_t huahuan;
	int16_t size;
	uint16_t indx;
	uint16_t mass;
	uint8_t name_len;
	uint8_t r;
	uint8_t g;
	uint8_t b;
	uint8_t spike;
	uint8_t isPlayer;
};

//张锋露 新增加的登陆后的账号玩家信息
struct player_info
{
	player_info()
	{
		playerid = "";
		pid = 0;
		playername = "";
		sex = 0;
		age = 0;
		playerdes = NULL;
		headid = "";
	}
	std::string        playerid;
	uint32_t           pid;
	std::string        playername;
	uint32_t           sex;
	uint32_t           age;
	uint32_t           playerdes;
	std::string        headid;
};

struct timeyuanzheng_cangku_info
{
	timeyuanzheng_cangku_info()
	{
		diamonds = 0;
		juan1 = 0;
		juan2 = 0;
		juan3 = 0;
		juan4 = 0;
		juan5 = 0;
		juan6 = 0;
	}
	uint32_t           diamonds;
	uint32_t           juan1;
	uint32_t           juan2;
	uint32_t           juan3;
	uint32_t           juan4;
	uint32_t           juan5;
	uint32_t           juan6;
};

//张锋露 账号
struct account_info
{
	account_info()
	{
		id = 0;
		playerid = "";
		password = "";
		isforbidden = 0;
		isbinded = 0;
		gmlevel = 0;
		mail = "";
		macip = "";
		accout = "";
	}
	uint32_t           id;
	std::string        playerid;
	std::string        password;
	uint32_t           isforbidden;
	uint32_t           isbinded;
	uint32_t           gmlevel;
	std::string        mail;
	std::string        macip;
	std::string        accout;
};

//倒计时
struct zuduidaojishi_info
{
	zuduidaojishi_info()
	{
		xing1time = 0;
		xing2time = 0;
		xing3time = 0;
		xing4time = 0;
		xing5time = 0;
		xing6time = 0;
	}

	uint32_t           xing1time;
	uint32_t           xing2time;
	uint32_t           xing3time;
	uint32_t           xing4time;
	uint32_t           xing5time;
	uint32_t           xing6time;
};

struct user_info {
    user_info()
    {
        roleID = 0;
        roleName = "";
        createTime = 0;
        icon = 0;
        sex = 0;
        level = 0;
        copper = 0;
        gold = 0;
        duanwei = 0;
        stars = 0;
        mvpCount = 0;
        chapionCount = 0;
        eatPlayerCount = 0;
        eatCount = 0;
        maxMass = 0;
        province = 0;
        city = 0;
        describe = "";
        heroid = 0;
        herolevel = 0;
        exp = 0;
        mEquip.clear();
        freeTicket = 0;
        fefreshTime = 0;
        isSign = false;
        lastSignTime = 0;
        signTags = 0;
        awardRefreshTime = 0;
        awardGots.clear();
        
    }
    uint32_t        roleID;
    std::string     roleName;
    uint32_t        createTime;
    uint32_t        icon;
    uint32_t        sex;
    uint32_t        level;
    uint32_t        copper;
    uint32_t        gold;
    uint32_t        duanwei;
    uint32_t        stars;
    uint32_t        mvpCount;
    uint32_t        chapionCount;
    uint32_t        eatPlayerCount;
    uint32_t        eatCount;
    uint32_t        maxMass;
    uint32_t        province;
    uint32_t        city;
    std::string     describe;
    uint32_t        heroid;
    uint32_t        herolevel;
    uint32_t        exp;
    std::map<int,int> mEquip;
    uint32_t        freeTicket;
    uint32_t        fefreshTime;
    bool            isSign;
    uint32_t        lastSignTime;
    uint32_t        signTags;
    uint32_t        awardRefreshTime;
    std::vector<bool>            awardGots;
};

struct shop_item_info
{
    uint32_t        tpltid;
    uint32_t        pos;
    uint32_t        stack;
    uint32_t        createTime;
};

struct bisaiInfo
{
    int             m_id;
    int             m_Icon;
    std::string     m_nickName;
    std::string     m_lastTime;
    std::string     m_rank;
    std::string     m_weight;
    std::string     m_number;
    std::string     m_duration;
    std::string     m_copper;
};

struct netInfo
{
    int             m_netID;
    std::string     m_netUrl;
    std::string     m_netPort;
    std::string     m_netName;
};

struct xihuanInfo
{
    int             m_xihuannum;
    std::string     m_headstr;
    std::string     m_name;
};

struct LiuyanInfo
{
    int m_icon;
    int likeCount;
    int roleid;
    int liuyanID;
    int isLike;
    std::string     m_name;
    std::string     m_neirong;
};

struct item
{
    item()
    {
        itemID = 0;
        itemType = 0;
        maxCount = 0;
        itemName = "";
        itemIcon = "";
        itemTips = "";
    }
    
    int             itemID;
    int             itemType;
    int             maxCount;
    std::string     itemName;
    std::string     itemIcon;
    std::string     itemTips;
};

struct nameMap
{
    int mID;
    std::string name;
    std::string icon;
};

struct NameColor
{
	int mID;
	int colorR;
	int colorG;
	int colorB;
};

// 战斗内排行
struct fight_rank
{
    int             rankID;
    std::string     name;
};

//战斗结算
struct EndGame
{
    EndGame()
    {
        rank = 0;
        roleid = 0;
        sex = 0;
        province = 0;
        city = 0;
        mass = 0;
        eat = 0;
        copper = 0;
        exp = 0;
        icon = 0;
        name = "";
        roleName = "";
        isAttention = false;
        isLike = false;
        iconStr = "";
    }
    int rank;
    int roleid;
    int sex;
    int province;
    int city;
    int mass;
    int eat;
    int copper;
    int exp;
    int icon;
    std::string name;
    std::string roleName;
    bool isAttention;
    bool isLike;
    std::string iconStr;
};

struct EndGame1
{
    EndGame1()
    {
        rank = 0;
        roleid = 0;
        sex = 0;
        province = 0;
        city = 0;
        mass = 0;
        eat = 0;
        copper = 0;
        exp = 0;
        icon = 0;
        name = "";
        roleName = "";
    }
    int rank;
    int roleid;
    int sex;
    int province;
    int city;
    int mass;
    int eat;
    int copper;
    int exp;
    int icon;
    std::string name;
    std::string roleName;
};

struct EndGame2
{
    EndGame2()
    {
        roleID = 0;
        isAttention = false;
        isLike = false;
    }
    int roleID;
    bool isAttention;
    bool isLike;
};

struct Relation2Me
{
    Relation2Me()
    {
        roleid = 0;
        sex = 0;
        province = 0;
        city = 0;
        mass = 0;
        eat = 0;
        copper = 0;
        exp = 0;
        icon = 0;
        recommend = 0;
        name = "";
        isAttention = false;
        isLike = false;
        iconStr = "";
        roleName = "";
    }
    int roleid;
    int sex;
    int province;
    int city;
    int mass;
    int eat;
    int copper;
    int exp;
    int icon;
    uint8_t recommend;
    std::string name;
    bool isAttention;
    bool isLike;
    std::string iconStr;
    std::string roleName;
};

struct Relation2Me1
{
    Relation2Me1()
    {
        roleid = 0;
        sex = 0;
        province = 0;
        city = 0;
        mass = 0;
        eat = 0;
        copper = 0;
        exp = 0;
        icon = 0;
        recommend = 0;
        name = "";
        roleName = "";
    }
    int roleid;
    int sex;
    int province;
    int city;
    int mass;
    int eat;
    int copper;
    int exp;
    int icon;
    uint8_t recommend;
    std::string name;
    std::string roleName;
};

struct ChildItem
{
    ChildItem()
    {
        m_id = 0;
        m_itemType = 0;
        m_costType = 0;
        m_duration = "";
        m_icon = "";
        m_iconBG = "";
        m_name = "";
        m_money = "";
    }
    int             m_id;
    int             m_itemType;
    int             m_costType;
    std::string     m_duration;
    std::string     m_icon;
    std::string     m_iconBG;
    std::string     m_name;
    std::string     m_money;
};

struct province_info
{
    int             m_id;
    std::string     m_name;
};
struct user_bag
{
    user_bag()
    {
        mId = 0;
        count = 0;
    }
    int mId;
    int count;
};

//测试
struct TestAtt
{
    int         m_id;
    int         m_sex;
    int         m_icon;
    std::string m_name;
    std::string m_dest;
    std::string m_state;
    std::string m_times;
    std::string m_iconStr;   //icon照片
};

struct duanweiInfo
{
    int mID;
    std::string name;
    std::string icon;
    int mStar;
};

struct QianDao
{
    int isQiandao;
    int mItemId;
};

struct QianDaoUse
{
    int mType;
    int mDay;
};
#endif /* Common_h */

