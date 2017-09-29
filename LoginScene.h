//
//  LoginScene.h
//  qiuFight
//
//  Created by ��Ծ�� on 16/3/4.
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

	//��ʼ�� ��½����
	void initDengLuData();
	void initUI();
	void initUI1();
	
	
	//�ϲ�������--0924--ע������� start======================================================================
	void initWaitBox();
	void hideWaitBox();
	void timeUpdate(float dt);
	//�ϲ�������--0924--ע������� end======================================================================
	//ͨ����λ��ȡ ��λ���� ��λͼ��
	void getDuanWeiInfoByIndex(int index);
	//��������
	void showBaoMingXiangQing();

	//���ݾ���������Ҷ� aid �õ� ������������
	xiangQing_Info getXiangQingInfoByAid(int aid);

	//���� aid ��ȡ�� ������ ��������
	baomingYuanAndLuan_Info getBaoMingNumByAid(int aid);


	void NextScene(Ref* pSender); //��Ϸ��ʼ
	void ResetName(Ref* pSender);
	void ShowGM(Ref* pSender);
	void ShowQiandao(Ref* pSender);
	void PersonCenter(Ref* pSender);   // ��������
	void RelationClick(Ref* pSender);  // ��ϵ
	void RankClick(Ref* pSender);      // ����
	void MagicClick(Ref* pSender);     // ħ����
	void HelpClick(Ref* pSender);      // ����
	void FriendClick(Ref* pSender);    // ������
	void TeamClick(Ref* pSender);      // �Ŷ�ģʽ
	void TeamClickFriend(Ref* pSender); //�����������
	void LiveClick(Ref* pSender);      // ����ģʽ
	void ShezhiClick(Ref* pSender);    // ����
	void HeadClick(cocos2d::Ref *pSender);   //ͷ��

	void JingJiChangClick(Ref* pSender); //������
	void ShengYiClick(Ref* pSender);//ʥ��

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


	//���㴥���¼���Ӧ����
	bool onTouchBegan(Touch *touch, Event *unused_event);
	void onTouchMoved(Touch *touch, Event *unused_event)     { CCLOG("moved"); }
	void onTouchEnded(Touch *touch, Event *unused_event);
	void onTouchCancelled(Touch *touch, Event *unused_event) {}

private:
	std::vector<yuanZhengBaoMingXiangQing_Info> baomingXiangQingInfos; //Զ����������
	std::vector<daLuanDouXiangQing_Info> daluandouXiangQingInfos;//���Ҷ���������
	std::vector<baomingYuanAndLuan_Info> yuanAndLuanInfos;//���б��� ������Ϣ
	long long int backTime;

	Node* rootNode; //����                  //�ϲ�������--0924--ע������� start=========================
	Node* rootGameSettingNode;

	float tishiY;
	float tishiX;

	float rongqiX;
	float rongqiY;
	float rongqiWidth;

private:
	//DropDownListLayer* dropLayer ;
	bool m_isLogin;
	int net_key;
	
	//�ϲ�������--0924--ע������� start=================================================================		
	int upMiaoTime = 0;
	int upFenTime = 0;
	Vec2 waitBoxVec2;
	//�ϲ�������--0924--ע������� end==================================================================
	
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
// ����ģʽ
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

	void AddLife(Ref* pSender);      // ������
	void SubLife(Ref* pSender);      // ������
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

// ����ģʽ
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

// ������
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

// ����
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

// ǩ��
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
