//
//  LoginScene.h
//  qiuFight
//
//  Created by 张跃东 on 16/3/4.
//
//

#ifndef LoginScene_h
#define LoginScene_h

#include "cocos2d.h"
#include "cocos-ext.h"
#include "network/WebSocket.h"

#include "DropDownListLayer.h"

#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "network/HttpClient.h"


using namespace cocostudio::timeline;
USING_NS_CC;
USING_NS_CC_EXT;

class LoginLayer : public Layer, public ui::EditBoxDelegate
{
public:
	enum
	{
		TAG_SHENGCUN,
		TAG_QIANDAO,
		TAG_FUWUQILAB
	};
	LoginLayer(){}
	~LoginLayer(){}

	virtual bool init();
	CREATE_FUNC(LoginLayer);

	void initUI();
	void initUI1();

	void NextScene(Ref* pSender);
	void ResetName(Ref* pSender);
	void ShowGM(Ref* pSender);
	void ShowQiandao(Ref* pSender);
	void PersonCenter(Ref* pSender);   // 个人中心
	void RelationClick(Ref* pSender);  // 关系
	void RankClick(Ref* pSender);      // 排行
	void MagicClick(Ref* pSender);     // 魔法屋
	void HelpClick(Ref* pSender);      // 帮助
	void FriendClick(Ref* pSender);    // 找朋友
	void TeamClick(Ref* pSender);      // 团队模式
	void LiveClick(Ref* pSender);      // 生产模式
	void ShezhiClick(Ref* pSender);    // 设置
	void HeadClick(cocos2d::Ref *pSender);   //头像

	void JingJiChangClick(Ref* pSender); //竞技场
	void ShengYiClick(Ref* pSender);//圣衣

	virtual void editBoxReturn(cocos2d::extension::EditBox* editBox);

	void RespMagicClick();

	void delayEnter(float ft);
	void InitHeadInfo();
	void initLogin(float ft);

	void updateNetInfos();
	void setNetKey(int key);
	void SetNameOK();

	void relogin();
	void rushmenpiao();
	void rushqiandao();

	netInfo getNetInfo();


private:
	//DropDownListLayer* dropLayer ;
	bool m_isLogin;
	int net_key;
};

//////
class GMScene : public Layer, public ui::EditBoxDelegate
{
public:

	GMScene(){}
	~GMScene(){}

	virtual bool init();
	CREATE_FUNC(GMScene);


	virtual void editBoxReturn(cocos2d::extension::EditBox* editBox);
	void Back(Ref* pSender);
	void ok(Ref* pSender);
private:

};
// 生存模式
class ShengCun : public CPZLayer
{
public:
	enum PC_TAG
	{
		TAG_NONE,
		TAG_Life,
		TAG_MenpiaoXiaohao,
		TAG_BtnJian,
		TAG_BtnJia,
		TAG_Xin1,
		TAG_Xin2,
		TAG_Xin3,
		TAG_MENPIAOLAB,
	};
	ShengCun();
	~ShengCun();

	virtual bool init();
	CREATE_FUNC(ShengCun);

	virtual bool onTouchBegan(Touch* pTouch, Event* pEvent);
	virtual void onTouchEnded(Touch* pTouch, Event* pEvent);

	void AddLife(Ref* pSender);      // 加生命
	void SubLife(Ref* pSender);      // 减生命
	void AddMenPiao(Ref* pSender);
	void StartGame(Ref* pSender);
	void rushmenpiao();


	void delayEnter(float ft);
private:
	bool isTouchIn;

	int  menpiaoNum;
	int  menpiaoxiaohao;
	int  lifeNum;
};

// 生存模式
class LingRuchangQuan : public CPZLayer
{
public:
	enum PC_TAG
	{
		TAG_NONE,
		TAG_Ruchangquan,
		TAG_Jinbi,
		TAG_MENPIAOLAB,
		TAG_MONEYLAB,
		TAG_LINQUCISHU
	};
	LingRuchangQuan();
	~LingRuchangQuan();

	virtual bool init();
	CREATE_FUNC(LingRuchangQuan);

	void BackClick(Ref* pSender);
	void FreeLing(Ref* pSender);
	void GouMai(Ref* pSender);
	void rushmenpiao();
private:
	bool isTouchIn;

	int  menpiaoNum;
	int  money;
};

// 找朋友
class FindFriend : public CPZLayer, public ui::EditBoxDelegate
{
public:
	enum PC_TAG
	{
		TAG_NONE,
		TAG_FindFriend,
		TAG_Fujinderen,
		TAG_PYLayer,
		TAG_FuJinLayer
	};
	FindFriend();
	~FindFriend();

	virtual bool init();
	CREATE_FUNC(FindFriend);

	void Saoyisao(Ref* pSender);
	void Leida(Ref* pSender);
	void Yaoyiyao(Ref* pSender);

	void Back(Ref* pSender);

	void Zhaopengyou(Ref* pSender);
	void Fujinderen(Ref* pSender);

	void InitZhaoPYUI();
	void resetBtnState();

	virtual void editBoxReturn(cocos2d::extension::EditBox* editBox);
private:
	PC_TAG m_currentTag;
};

// 设置
class SheZhi : public CPZLayer, public ui::EditBoxDelegate
{
public:
	enum PC_TAG
	{
		TAG_NONE,
		TAG_FindFriend,
		TAG_Fujinderen,
		TAG_SHEZHI,
		TAG_ZHUCE,
		TAG_USERSHEZHI,
		TAG_XUANZENAN,
		TAG_XUANZENV
	};
	SheZhi();
	~SheZhi();

	virtual bool init();
	CREATE_FUNC(SheZhi);

	void resetBtnState();
	void InitShezhiUI();
	void InitZhuceUI();
	void InitUserShezhi();
	void YouxiShezhi(Ref* pSender);
	void Yonghuxinxi(Ref* pSender);
	void Yinyue(Ref* pSender);
	void Yinxiao(Ref* pSender);
	void tuanzhanyaoqing(Ref* pSender);
	void tuqiushezhi(Ref* pSender);

	virtual void editBoxReturn(cocos2d::extension::EditBox* editBox);

	void xuanzenan(Ref* pSender);
	void xuanzenv(Ref* pSender);
	void Back(Ref* pSender);
	void baocunBtn(Ref* pSender);

	void SetNameOK();
private:
	PC_TAG m_currentTag;
	int  mUserSex;
};

// 签到
class Qiandao : public CPZLayer
{
public:
	enum PC_TAG
	{
		TAG_NONE,
		TAG_QIANDAOBTN,
		TAG_INFOLAYER
	};
	Qiandao();
	~Qiandao();

	virtual bool init();
	CREATE_FUNC(Qiandao);
	void InitInfo();
	void QiandaoClick(Ref* pSender);
	void Back(Ref* pSender);
	void UpdateSignInfos();
	void RushInfo();
private:
	std::vector<QianDao> mInfo;
};
#endif /* LoginScene_h */
