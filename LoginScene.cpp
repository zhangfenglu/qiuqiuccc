//
//  LoginScene.cpp
//  qiuFight
//
//  Created by 张跃东 on 16/3/4.
//
//

#include "LoginScene.h"
#include "Global.h"
//#include "InputLabel.h"
#include "MainScene.h"
#include "Common.h"
#include <ctime>
#include "CEditBox.h"

#include "SceneLayer.h"

#include "ExchangeInfo.h"
#include "Resources.h"
#include "CurCularNode.h"
#include "SimpleTools.h"
#include "HttpGetImg.h"
#include "TimeYuanZhengLayer.h"
#include "YuanZhengLayer.h"
//#include "DaTingLayer.h"
using namespace cocos2d::network;

bool LoginLayer::init()
{
	if (!Layer::init())
		return false;
	rootNode = CSLoader::createNode("DaTingLayer.csb");
	addChild(rootNode);
	rootGameSettingNode = nullptr;
	//初始化登陆数据
	initDengLuData();
	//initUI();
	initUI1();

	//获取事件分发器
	auto dispatcher = Director::getInstance()->getEventDispatcher();

	//创建单点触摸监听器 EventListenerTouchOneByOne
	auto touchListener = EventListenerTouchOneByOne::create();
	//单点触摸响应事件绑定
	touchListener->onTouchBegan = CC_CALLBACK_2(LoginLayer::onTouchBegan, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(LoginLayer::onTouchMoved, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(LoginLayer::onTouchEnded, this);
	touchListener->onTouchCancelled = CC_CALLBACK_2(LoginLayer::onTouchCancelled, this);
	touchListener->setSwallowTouches(true);

	//在事件分发器中，添加触摸监听器，事件响应委托给 this 处理
	dispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
	return true;
}

void LoginLayer::initUI1()
{
	auto  zuduidengdaiBg = (cocos2d::ui::ImageView*)seekNodeByName(rootNode, "zuduidengdaiBg");
	zuduidengdaiBg->setVisible(false);
	CEditBoxTool* edbox = CEditBoxTool::Create(Size(300, 80), Scale9Sprite::create("input.png"));
	edbox->setPosition(Vec2(winSize.width * 0.5f, winSize.height * 0.67));
	//edbox->setFont("STXingkai.ttf", 29.0f);
	edbox->setFontColor(Color3B(0, 0, 0));
	edbox->setFontColor(Color3B::GREEN);
	//edbox->setMaxLength(20);
	edbox->setInputMode(EditBox::InputMode::ANY);
	edbox->setDelegate(this);
	addChild(edbox, 3, 101);

	std::string name = CCUserDefault::sharedUserDefault()->getStringForKey("UserName", "");
	if (strcmp(name.c_str(), "") != 0) {
		edbox->setText(Global::getInstance()->getString(name.c_str()));
	}
	else{
		int nIdex = Global::getInstance()->getRand(10);
		char randName[126] = { 0 };
		sprintf(randName, "name_%d", nIdex);
		edbox->setText(Global::getInstance()->getString(randName));
		CCUserDefault::sharedUserDefault()->setStringForKey("UserName", name.c_str());
	}

	//随机生成名字
	cocos2d::ui::Button* resetName = (cocos2d::ui::Button*)seekNodeByName(rootNode, "btnRandom");
	resetName->addTouchEventListener([=](Ref*, cocos2d::ui::Widget::TouchEventType type)
	{
		if (type == cocos2d::ui::Widget::TouchEventType::ENDED)
		{
			ResetName(NULL);
		}
	});

	//游戏开始
	cocos2d::ui::Button* loginBtn = (cocos2d::ui::Button*)seekNodeByName(rootNode, "btnStatGame");
	loginBtn->addTouchEventListener([=](Ref*, cocos2d::ui::Widget::TouchEventType type)
	{
		if (type == cocos2d::ui::Widget::TouchEventType::ENDED)
		{
			NextScene(NULL);
		}
	});
	//addChild(loginBtn, 2);

	//Button* teamBtn = Button::createBtnWithSpriteFrameName("teammode.png", false);
	//teamBtn->setPosition(Vec2(winSize.width * 0.5f + 430, winSize.height * 0.5f - 120));
	//teamBtn->setScale(0.45f);
	//teamBtn->setOnClickCallback(callfuncO_selector(LoginLayer::TeamClick), this);
	//addChild(teamBtn, 2);

	//团队

	//生存模式
	/*Button* liveBtn = Button::createBtnWithSpriteFrameName("live_mode.png", false);
	liveBtn->setPosition(Vec2(winSize.width * 0.5f + 320, winSize.height * 0.5f - 120));
	liveBtn->setScale(0.45f);
	liveBtn->setOnClickCallback(callfuncO_selector(LoginLayer::LiveClick), this);
	addChild(liveBtn, 2);
	liveBtn->setVisible(false);*/

	//个人中心
	Button* personBtn = Button::createBtnWithSpriteFrameName("personcenter.png", false);
	personBtn->setPosition(Vec2(270, 60));
	personBtn->setScale(0.55f);
	personBtn->setOnClickCallback(callfuncO_selector(LoginLayer::PersonCenter), this);
	addChild(personBtn, 2);
	//personBtn->setVisible(false);


	//关系
	cocos2d::ui::Button* relationBtn = (cocos2d::ui::Button*)seekNodeByName(rootNode, "btnGuanXi");
	relationBtn->addTouchEventListener([=](Ref*, cocos2d::ui::Widget::TouchEventType type)
	{
		if (type == cocos2d::ui::Widget::TouchEventType::ENDED)
		{
			RelationClick(NULL);
		}
	});


	//排行榜
	cocos2d::ui::Button* rankBtn = (cocos2d::ui::Button*)seekNodeByName(rootNode, "btnPaiHangBang");
	//rankBtn->setOnClickCallback(callfuncO_selector(LoginLayer::RankClick), this);
	rankBtn->addTouchEventListener([=](Ref*, cocos2d::ui::Widget::TouchEventType type)
	{
		if (type == cocos2d::ui::Widget::TouchEventType::ENDED)
		{
			RankClick(NULL);
		}
	});

	//商店
	Button* magicBtn = Button::createBtnWithSpriteFrameName("magichouse.png", false);
	magicBtn->setPosition(Vec2(900, 60));
	magicBtn->setScale(0.55f);
	magicBtn->setOnClickCallback(callfuncO_selector(LoginLayer::MagicClick), this);
	addChild(magicBtn, 2);
	magicBtn->setVisible(false);
	/*
	Button* helpBtn = Button::createBtnWithSpriteFrameName("help.png", false);
	helpBtn->setPosition(Vec2(winSize.width - 50, winSize.height - 50));
	helpBtn->setScale(0.6f);
	helpBtn->setOnClickCallback(callfuncO_selector(LoginLayer::HelpClick), this);
	addChild(helpBtn, 2);
	*/


	//找朋友
	cocos2d::ui::Button* friendBtn = (cocos2d::ui::Button*)seekNodeByName(rootNode, "btnFindFriend");
	friendBtn->addTouchEventListener([=](Ref*, cocos2d::ui::Widget::TouchEventType type)
	{
		if (type == cocos2d::ui::Widget::TouchEventType::ENDED)
		{
			FriendClick(NULL);
		}
	});

	//游戏设置
	cocos2d::ui::Button* setBtn = (cocos2d::ui::Button*)seekNodeByName(rootNode, "btnSet");
	setBtn->addTouchEventListener([=](Ref*, cocos2d::ui::Widget::TouchEventType type)
	{
		if (type == cocos2d::ui::Widget::TouchEventType::ENDED)
		{
			ShezhiClick(NULL);
		}
	});

	//一排按钮群
	auto btnOpen = (cocos2d::ui::Button*)seekNodeByName(rootNode, "btnOpen");
	btnOpen->addTouchEventListener([=](Ref*, cocos2d::ui::Widget::TouchEventType type)
	{
		if (type == cocos2d::ui::Widget::TouchEventType::ENDED)
		{
			//btnOpen->setVisible(false);
			auto bg = (cocos2d::ui::ImageView*)seekNodeByName(rootNode, "bg");
			float x = bg->getPositionX();
			float y = bg->getPositionY();
			float x1 = x - bg->getContentSize().width;

			auto moveTo = MoveTo::create(0.2, Vec2(x1, y));
			//bg->runAction(Sequence::create(moveTo，NULL));
			bg->runAction(moveTo);

			auto btnClose = (cocos2d::ui::Button*)seekNodeByName(rootNode, "btnClose");
			btnClose->addTouchEventListener([=](Ref*, cocos2d::ui::Widget::TouchEventType type)
			{
				if (type == cocos2d::ui::Widget::TouchEventType::ENDED)
				{
					auto moveBack = MoveTo::create(0.2, Vec2(x, y));
					bg->runAction(moveBack);
				}
			});

		}
	});


	m_isLogin = false;

	user_info info = Global::getInstance()->GetUserInfo();
	if (info.roleID)
	{
		InitHeadInfo();
		updateNetInfos();//获取服务器
	}
	else{
		scheduleOnce(schedule_selector(LoginLayer::initLogin), 0.15f);
	}

	//CCParticleSystemQuad* effect = CCParticleSystemQuad::create("ddd.plist");
	//effect->setPosition(Vec2(winSize.width/2+30, winSize.height/2-60));
	//addChild(effect,50);

	//    friendBtn = Button::createBtnWithSpriteFrameName("login-qiandao.png", false);
	//    friendBtn->setPosition(Vec2(winSize.width - 50, winSize.height - 250));
	//    friendBtn->setScale(0.6f);
	//    friendBtn->setOnClickCallback(callfuncO_selector(LoginLayer::ShowQiandao), this);
	//    addChild(friendBtn, 2);

	//friendBtn = Button::createBtnWithSpriteFrameName("set_btn.png", false);
	//friendBtn->setPosition(Vec2(winSize.width - 50, winSize.height - 350));
	//friendBtn->setScale(0.3f);
	//friendBtn->setOnClickCallback(callfuncO_selector(LoginLayer::ShowGM), this);
	//addChild(friendBtn, 2);

	//竞技场
	auto btnJingJiChang = (cocos2d::ui::Button*)seekNodeByName(rootNode, "btnJingJiChang");
	btnJingJiChang->addTouchEventListener([=](Ref*, cocos2d::ui::Widget::TouchEventType type)
	{
		if (type == cocos2d::ui::Widget::TouchEventType::ENDED)
		{
			JingJiChangClick(NULL);
		}
	});

	//圣衣
	auto btnShengYi = (cocos2d::ui::Button*)seekNodeByName(rootNode, "btnShengYi");
	btnShengYi->addTouchEventListener([=](Ref*, cocos2d::ui::Widget::TouchEventType type)
	{
		if (type == cocos2d::ui::Widget::TouchEventType::ENDED)
		{
			ShengYiClick(NULL);
		}
	});




	//获取活动图片资源
	auto rootNode1 = CSLoader::createNode("ActiveLayer.csb");
	addChild(rootNode1,100000);

	auto ScrollView_1 = (cocos2d::ui::ImageView*)seekNodeByName(rootNode1, "ScrollView_1");
	auto closeBtn = (cocos2d::ui::Button*)seekNodeByName(rootNode1, "btnOk");
	closeBtn->addTouchEventListener([=](Ref*, cocos2d::ui::Widget::TouchEventType type)
	{
		if (type == cocos2d::ui::Widget::TouchEventType::ENDED)
		{
			rootNode1->setVisible(false);
		}
	});

	std::string url = "http://47.93.50.101:8080/QQWar/Qqwar/activity";
	
	requestFroGet(url, [=](HttpClient *sender, HttpResponse *response)
	{
		if (response == nullptr || !response->isSucceed())
		{
			CCLOG("responese is null");
			CCLOG("responese not succeed");

			return;
		}

		vector<char> *buffer = response->getResponseData();

		std::string responseStr = std::string(buffer->begin(), buffer->end());
		CCLOG("%s", responseStr.c_str());

		Json* root = Json_create(responseStr.c_str());
		Json* result = Json_getItem(root, "resultCode");
		Json * resultObj = Json_getItem(root, "resultObj");

		if (result->type == Json_Number)
		{
			if (result->valueInt == 1)
			{
				log("*******************************picPath success");

				Json * id = Json_getItem(resultObj->child, "id");

				if (id && id->valueInt == 1)
				{
					Json * url1 = Json_getItem(resultObj->child, "url");
					std::string u = url1->valueString;
					std::string picUrl = "http://" + u;
			
					HttpGetImg::GetHttpImg(picUrl, [=](Texture2D * texture)
					{
						if (texture)
						{
							auto tupian = Sprite::createWithTexture(texture);
							tupian->setAnchorPoint(Point(0,0));
							if (ScrollView_1)
							{
								ScrollView_1->addChild(tupian);
							}
						}	
					}
					);




				}
				else
				{

				}

				
			}
			else
			{
				log("*******************************picPath error");
			}
		}
		else
		{
			log("*******************************picPath error");
		}







		

	}, "GetImgPath");


	
	
}


void LoginLayer::rushqiandao()
{
	Qiandao* qiandao = (Qiandao*)getChildByTag(TAG_QIANDAO);
	if (qiandao)
	{
		qiandao->UpdateSignInfos();
		qiandao->InitInfo();
	}
}
void LoginLayer::ShowQiandao(Ref* pSender)
{
	Qiandao* qiandao = Qiandao::create();
	addChild(qiandao, 10, TAG_QIANDAO);
}
void LoginLayer::ShowGM(Ref* pSender)
{
	GMScene* GMS = GMScene::create();
	addChild(GMS, 200);

	/*
	std::vector<item> arr;
	for (int i = 0; i<5; i++) {
	item ite;
	ite.itemName = "测试名字";
	ite.maxCount = i+2;
	arr.push_back(ite);
	}
	Global::getInstance()->ShowPromMoveBox(arr);
	*/
}
void LoginLayer::ResetName(Ref* pSender)
{
	int nIdex = Global::getInstance()->getRand(10);
	char randName[126] = { 0 };
	sprintf(randName, "name_%d", nIdex);
	CEditBoxTool* edbox = (CEditBoxTool*)getChildByTag(101);
	edbox->setText(Global::getInstance()->getString(randName));
	CCUserDefault::sharedUserDefault()->setStringForKey("UserName", Global::getInstance()->getString(randName));
}
void LoginLayer::updateNetInfos()
{
	// 获得服务器列表
	std::vector<netInfo> nets = Global::getInstance()->getNetInfos();

	if (nets.size() == 0)
	{
		return;
		//        CCLabelTTF* netname = CCLabelTTF::create(nets[0].m_netName.c_str(), "STXingkai.ttf", 29);
		//        netname->setColor(Color3B(0, 0, 0));
		//        netname->setAnchorPoint(Vec2(0,0));
		//        netname->setPosition(Vec2(winSize.width * 0.5f - 60, winSize.height * 0.5f - 20));
		//        addChild(netname, 10);
	}
	else
	{
		removeChildByTag(TAG_FUWUQILAB, true);
		CCLabelTTF* netname = CCLabelTTF::create(nets[0].m_netName.c_str(), "STXingkai.ttf", 29);
		netname->setColor(Color3B(0, 0, 0));

		// 制作下拉
		//Size size = Size(200, 30);
		//dropLayer = DropDownListLayer::create(netname, size);

		//for(int i = 0; i < nets.size(); i++)
		//{
		// CCLabelTTF* netname = CCLabelTTF::create(nets[i].m_netName.c_str(), "STXingkai.ttf", 29);
		//dropLayer->addLabel(netname);
		//}

		netname->setPosition(Vec2(winSize.width * 0.5f + 5, winSize.height * 0.5f + 90));
		addChild(netname, 10, TAG_FUWUQILAB);
		netname->setVisible(false);

	}
}

void LoginLayer::relogin()
{
	scheduleOnce(schedule_selector(LoginLayer::initLogin), 0.5f);
}

void LoginLayer::initLogin(float ft)
{
	MainScene* main = dynamic_cast<MainScene*>(getParent());
	main->loginGame();
	main->reqDuanXianChongLian();
}
void LoginLayer::InitHeadInfo()
{
	if (getChildByTag(30))
	{
		removeChildByTag(30, true);
	}
	Layer* pyLyaer = Layer::create();
	addChild(pyLyaer, 2, 30);

	user_info info = Global::getInstance()->GetUserInfo();
	duanweiInfo duan = Resource::sharedResource()->GetDuanweiInfo(info.duanwei);

	Button* headbg = Button::createBtnWithSpriteFrameName("touxiang002.png", false);
	headbg->setPosition(Vec2(60, winSize.height - 70));
	headbg->setScale(0.33f);
	headbg->setOnClickCallback(callfuncO_selector(LoginLayer::HeadClick), this);
	pyLyaer->addChild(headbg, 2);

	std::string path;
	if (info.icon>100) {
		char temp[32];
		sprintf(temp, "hero_%d.png", info.icon);
		path = temp;
	}
	else{
		char spName[64] = { 0 };
		sprintf(spName, "headImage%d.jpg", info.icon);

		path = Global::getInstance()->getDataPath(spName);
	}

	Sprite* head = Sprite::create(path.c_str());
	if (head)
	{
		CirCularNode* headCir = CirCularNode::create(45, head);
		head->setScale(0.3f);
		headCir->setPosition(Vec2(60, winSize.height - 70));
		pyLyaer->addChild(headCir, 2);
	}
	else{
		MainScene* scene = (MainScene*)getParent();
		scene->reqGetPhoto(Global::getInstance()->GetUserInfo().roleID);
	}

	//log("name:%s",info.roleName.c_str());
	CCLabelTTF* useName = CCLabelTTF::create(info.roleName.c_str(), "STXingkai.ttf", 30);
	useName->setColor(Color3B(0, 0, 0));
	useName->setAnchorPoint(Vec2(0.0f, 0.5f));
	useName->setPosition(Vec2(120, winSize.height - 50));
	pyLyaer->addChild(useName, 2);

	Sprite* levBg = Sprite::create(duan.icon.c_str());
	levBg->setScale(0.25f);
	levBg->setPosition(Vec2(130, winSize.height - 80));
	pyLyaer->addChild(levBg, 2);

	CCLabelTTF* levName = CCLabelTTF::create(duan.name.c_str(), "STXingkai.ttf", 30);
	levName->setColor(Color3B(0, 0, 0));
	levName->setAnchorPoint(Vec2(0.0f, 0.5f));
	levName->setPosition(Vec2(145, winSize.height - 80));
	pyLyaer->addChild(levName, 2);

	if (info.stars > 3) {
		char starLab[32] = { 0 };
		sprintf(starLab, "%d", info.stars);
		levName = CCLabelTTF::create(starLab, "STXingkai.ttf", 30);
		levName->setColor(Color3B(0, 0, 0));
		levName->setAnchorPoint(Vec2(0.0f, 0.5f));
		levName->setPosition(Vec2(225, winSize.height - 80));
		pyLyaer->addChild(levName, 2);

		Sprite* xing = Sprite::create("hecheng-xx-02.png");
		xing->setScale(0.6f);
		xing->setPosition(Vec2(265, winSize.height - 80));
		pyLyaer->addChild(xing, 2);
	}
	else{
		for (int i = 0; i<3; i++)
		{
			if (info.stars > i) {
				Sprite* xing = Sprite::create("hecheng-xx-02.png");
				xing->setScale(0.6f);
				xing->setPosition(Vec2(225 + i * 25, winSize.height - 80));
				pyLyaer->addChild(xing, 2);
			}
			else{
				Sprite* xing = Sprite::create("hecheng-xx-01.png");
				xing->setScale(0.6f);
				xing->setPosition(Vec2(225 + i * 25, winSize.height - 80));
				pyLyaer->addChild(xing, 2);
			}
		}
	}
	if (!info.province) {
		int proID = ExchangeInfo::getLocationProvince();
		MainScene* scene = (MainScene*)getParent();
		if (scene)
			scene->reqSetGeo(proID);
	}
	//    updateNetInfos();
}
void LoginLayer::NextScene(cocos2d::Ref *pSender)
{
	if (m_isLogin == true)
		return;

	bool isConnect = false;
	//DropDownListLayer* dropLayer = dynamic_cast<DropDownListLayer*>(getChildByTag(121));
	//int selectIdx = dropLayer->getSelectedIndex();
	std::vector<netInfo> nets = Global::getInstance()->getNetInfos();
	MainScene* main = dynamic_cast<MainScene*>(getParent());
	if (main)
	{
		isConnect = main->OpenWebSocket(nets[0].m_netUrl.c_str(), nets[0].m_netPort.c_str());
	}

	if (!isConnect)
		return;

	m_isLogin = true;
	schedule(schedule_selector(LoginLayer::delayEnter), 1.0f);
}

void LoginLayer::setNetKey(int key)
{
	CEditBoxTool* input = dynamic_cast<CEditBoxTool*>(getChildByTag(101));
	std::string nick = input->getText();
	if (nick == "" || nick.size() == 0)
	{
		input->setText(CCUserDefault::sharedUserDefault()->getStringForKey("UserName").c_str());
		nick = input->getText();
	}

	//srand(time(0)) ;
	//int index = rand()%MAXIMUM_PICTURE_NUM;
	int index = Global::getInstance()->getRand(MAXIMUM_PICTURE_NUM);
	Global::getInstance()->SetMainPicIndex(index);
	MainScene* main = dynamic_cast<MainScene*>(getParent());
	main->enterGame(nick.c_str(), key);

	CCUserDefault::sharedUserDefault()->setStringForKey("UserName", nick.c_str());
}

void LoginLayer::delayEnter(float ft)
{
	if (!Global::getInstance()->getConnectState())
		return;

	m_isLogin = false;
	unschedule(schedule_selector(LoginLayer::delayEnter));

	MainScene* main = dynamic_cast<MainScene*>(getParent());
	//DropDownListLayer* dropLayer = dynamic_cast<DropDownListLayer*>(getChildByTag(121));
	//int selectIdx = dropLayer->getSelectedIndex();
	std::vector<netInfo> nets = Global::getInstance()->getNetInfos();
	// 获取战斗服务器秘钥
	main->reqServerKey(nets[0].m_netID, 0, 0);
	Global::getInstance()->SetFightType(0);
}

netInfo LoginLayer::getNetInfo()
{
	//DropDownListLayer* dropLayer = dynamic_cast<DropDownListLayer*>(getChildByTag(121));
	//int selectIdx = dropLayer->getSelectedIndex();
	std::vector<netInfo> nets = Global::getInstance()->getNetInfos();
	// 获取战斗服务器秘钥
	return nets[0];
}

void LoginLayer::PersonCenter(cocos2d::Ref *pSender)
{
	/*user_info user = Global::getInstance()->GetUserInfo();
	Global::getInstance()->SetplayerInfo(user);*/

	MainScene* main = dynamic_cast<MainScene*>(getParent());
	//main->CheckLayer(MainScene::TAG_LAYER_USERINFO);
	main->reqQuXiaoZuDui();
}

void LoginLayer::RelationClick(cocos2d::Ref *pSender)
{
	MainScene* main = dynamic_cast<MainScene*>(getParent());
	main->CheckLayer(MainScene::TAG_LAYER_RELATION);
}

void LoginLayer::RankClick(cocos2d::Ref *pSender)
{
	MainScene* main = dynamic_cast<MainScene*>(getParent());
	main->CheckLayer(MainScene::TAG_LAYER_RANKING);
}

void LoginLayer::MagicClick(cocos2d::Ref *pSender)
{
	//    MainScene* main = dynamic_cast<MainScene*>(getParent());
	//    main->CheckLayer(MainScene::TAG_LAYER_SHOP);
	//MainScene* main = dynamic_cast<MainScene*>(getParent());
	//main->reqShopList();
	//main->reqZuDui();

	/*auto timeYuanZhengLayer = TimeYuanZhengLayer::create();
	addChild(timeYuanZhengLayer,100000);*/

	/*auto YuanZhengLayer = YuanZhengLayer::create();
	addChild(YuanZhengLayer, 100000);*/
}

void LoginLayer::HelpClick(cocos2d::Ref *pSender)
{

}
void LoginLayer::HeadClick(cocos2d::Ref *pSender)
{
	user_info user = Global::getInstance()->GetUserInfo();
	Global::getInstance()->SetplayerInfo(user);

	MainScene* main = dynamic_cast<MainScene*>(getParent());
	main->CheckLayer(MainScene::TAG_LAYER_USERINFO);
}
void LoginLayer::FriendClick(cocos2d::Ref *pSender)
{
	FindFriend* layer = FindFriend::create();
	addChild(layer, 10);
}
void LoginLayer::ShezhiClick(Ref* pSender)
{
	/*SheZhi* layer = SheZhi::create();

	addChild(layer, 10, 131);*/

	account_info info = Global::getInstance()->GetAccountInfo();

	rootGameSettingNode = CSLoader::createNode("GameSetting.csb");
	setCanTouchOtherLayer(rootGameSettingNode, false, [=](Touch * touch, Event * event){
		if (rootGameSettingNode)
		{
			auto setBox = (cocos2d::ui::ImageView*)seekNodeByName(rootGameSettingNode, "setBox");
			if (!setBox->getBoundingBox().containsPoint(touch->getLocation()))
			{
				rootGameSettingNode->removeFromParent();
				rootGameSettingNode = nullptr;
			}
		}
		return true;
	});
	auto close1 = (cocos2d::ui::Button*)seekNodeByName(rootGameSettingNode, "close1");
	close1->addTouchEventListener([=](Ref*, cocos2d::ui::Widget::TouchEventType type)
	{
		if (type == cocos2d::ui::Widget::TouchEventType::ENDED)
		{
			rootGameSettingNode->removeFromParent();
			rootGameSettingNode = nullptr;
		}
	});

	//账号绑定界面
	auto btnBangDing = (cocos2d::ui::Button*)seekNodeByName(rootGameSettingNode, "btnBangDing");
	auto btnYiBangDing = (cocos2d::ui::Button*)seekNodeByName(rootGameSettingNode, "btnYiBangDing");
	auto zhanghaobangding = (cocos2d::ui::ImageView*)seekNodeByName(rootGameSettingNode, "zhanghaobangding");

	//账号显示
	auto zhanghao = (cocos2d::ui::Text*)seekNodeByName(rootGameSettingNode, "zhanghao");
	zhanghao->setText(info.accout);

	if (info.isbinded != 0)
	{
		btnBangDing->setVisible(false);
		btnBangDing->setTouchEnabled(false);
		btnYiBangDing->setVisible(true);
	}
	else
	{
		btnYiBangDing->setVisible(false);
		btnBangDing->setVisible(true);
		btnBangDing->setTouchEnabled(true);
	}

	//绑定账号输入框
	CEditBoxTool* zhanghaoedbox = CEditBoxTool::Create(Size(300, 80), Scale9Sprite::create("input.png"));
	CEditBoxTool* mimaedbox = CEditBoxTool::Create(Size(300, 80), Scale9Sprite::create("input.png"));
	CEditBoxTool* mima1edbox = CEditBoxTool::Create(Size(300, 80), Scale9Sprite::create("input.png"));

	zhanghaoedbox->setPosition(Vec2(365, 440));
	zhanghaoedbox->setInputMode(EditBox::InputMode::ANY);
	zhanghaoedbox->setDelegate(this);
	zhanghaoedbox->setFontSize(28);
	zhanghaoedbox->setFontColor(Color3B::BLACK);
	zhanghaobangding->addChild(zhanghaoedbox, 3, 101);

	zhanghaoedbox->setPlaceHolder(Global::getInstance()->getString("please input new account"));

	mimaedbox->setPosition(Vec2(365, 320));
	mimaedbox->setInputMode(EditBox::InputMode::ANY);
	mimaedbox->setDelegate(this);
	mimaedbox->setFontSize(28);
	mimaedbox->setFontColor(Color3B::BLACK);
	zhanghaobangding->addChild(mimaedbox, 3, 101);

	mimaedbox->setPlaceHolder(Global::getInstance()->getString("please input password"));
	mima1edbox->setPosition(Vec2(365, 200));
	mima1edbox->setInputMode(EditBox::InputMode::ANY);
	mima1edbox->setDelegate(this);
	mima1edbox->setFontSize(28);
	mima1edbox->setFontColor(Color3B::BLACK);
	zhanghaobangding->addChild(mima1edbox, 3, 101);
	mima1edbox->setPlaceHolder(Global::getInstance()->getString("please input password again"));


	btnBangDing->addTouchEventListener([=](Ref*, cocos2d::ui::Widget::TouchEventType type)
	{
		if (type == cocos2d::ui::Widget::TouchEventType::ENDED)
		{
			//账号绑定界面显示
			zhanghaobangding->setVisible(true);
		}
	});

	auto close2 = (cocos2d::ui::Button*)seekNodeByName(rootGameSettingNode, "close2");
	close2->addTouchEventListener([=](Ref*, cocos2d::ui::Widget::TouchEventType type)
	{
		if (type == cocos2d::ui::Widget::TouchEventType::ENDED)
		{
			zhanghaobangding->setVisible(false);
		}
	});

	auto btntijiao = (cocos2d::ui::Button*)seekNodeByName(rootGameSettingNode, "btntijiao");
	btntijiao->addTouchEventListener([=](Ref*, cocos2d::ui::Widget::TouchEventType type)
	{
		if (type == cocos2d::ui::Widget::TouchEventType::ENDED)
		{
			log("zhanghao===%s  mima===%s mima ==== %s,", zhanghaoedbox->getText(), mimaedbox->getText(), mima1edbox->getText());
			if (zhanghaoedbox->getText() != "" &&  strcmp(mimaedbox->getText(), mima1edbox->getText()) == 0 && mimaedbox->getText() != "")
			{
				log("submit bangding zhanghao xinxi");

				std::string zhanghao1 = zhanghaoedbox->getText();
				std::string data = "playerid=" + info.playerid + "&account=" + zhanghao1 + "&password=" + mimaedbox->getText();
				
				std::string url = "http://47.93.50.101:8080/QQWar/Qqwar/bindaccount";
				
				requestForPost(url, data.c_str(), [=](HttpClient *sender, HttpResponse *response)
				{
					if (response == nullptr || !response->isSucceed())
					{
						CCLOG("responese is null");
						CCLOG("responese not succeed");

						return;
					}

					vector<char> *buffer = response->getResponseData();

					std::string responseStr = std::string(buffer->begin(), buffer->end());
					CCLOG("%s", responseStr.c_str());

					Json* root = Json_create(responseStr.c_str());
					Json* result = Json_getItem(root, "resultCode");
					Json * resultObj = Json_getItem(root, "resultObj");

					if (result->type == Json_Number)
					{
						if (result->valueInt == 1)
						{
							log("*******************************bangding success");

							Json * gmlevel = Json_getItem(resultObj, "gmlevel");
							Json * id = Json_getItem(resultObj, "id");
							Json* playerid = Json_getItem(resultObj, "playerid");
							Json* isbinded = Json_getItem(resultObj, "isbinded");
							Json* isforbidden = Json_getItem(resultObj, "isforbidden");
							Json* macip = Json_getItem(resultObj, "macip");
							Json* mail = Json_getItem(resultObj, "mail");
							Json* accout = Json_getItem(resultObj, "accout");
							Json* password = Json_getItem(resultObj, "password");

							account_info info;
							info.accout = accout->valueString;
							info.gmlevel = gmlevel->valueInt;
							info.id = id->valueInt;
							info.password = password->valueString;
							info.playerid = playerid->valueString;
							info.isforbidden = isforbidden->valueInt;
							info.isbinded = isbinded->valueInt;
							info.macip = macip->valueString;
							if (mail->valueString != NULL)
								info.mail = mail->valueString;

							Global::getInstance()->SetAccountInfo(info);
							UserDefault::getInstance()->setStringForKey("accout", accout->valueString);
							UserDefault::getInstance()->setStringForKey("password", password->valueString);

							zhanghao->setText(info.accout);
							zhanghaobangding->setVisible(false);
							btnBangDing->setVisible(false);
							btnBangDing->setTouchEnabled(false);
							btnYiBangDing->setVisible(true);
						}
						else
						{
							log("*******************************bangding error");
						}
					}
					else
					{
						log("*******************************bangding error");
					}



				}, "bangdingzhanghao");

			}
		}
	});


	//切换账号
	auto btnChange = (cocos2d::ui::Button*)seekNodeByName(rootGameSettingNode, "btnChange");
	auto qiehuanzhanghao = (cocos2d::ui::ImageView*)seekNodeByName(rootGameSettingNode, "qiehuanzhanghao");
	btnChange->addTouchEventListener([=](Ref*, cocos2d::ui::Widget::TouchEventType type)
	{
		if (type == cocos2d::ui::Widget::TouchEventType::ENDED)
		{
			qiehuanzhanghao->setVisible(true);
		}
	});

	auto close3 = (cocos2d::ui::Button*)seekNodeByName(rootGameSettingNode, "close3");
	close3->addTouchEventListener([=](Ref*, cocos2d::ui::Widget::TouchEventType type)
	{
		if (type == cocos2d::ui::Widget::TouchEventType::ENDED)
		{
			qiehuanzhanghao->setVisible(false);
		}
	});

	//切换账号 上的弹窗 输入框
	CEditBoxTool* qiehuanzhanghaoedbox = CEditBoxTool::Create(Size(300, 80), Scale9Sprite::create("input.png"));
	CEditBoxTool* qiehuanmimaedbox = CEditBoxTool::Create(Size(300, 80), Scale9Sprite::create("input.png"));

	qiehuanzhanghaoedbox->setPosition(Vec2(330, 365));
	qiehuanzhanghaoedbox->setInputMode(EditBox::InputMode::ANY);
	qiehuanzhanghaoedbox->setDelegate(this);
	qiehuanzhanghaoedbox->setFontSize(28);
	qiehuanzhanghaoedbox->setFontColor(Color3B::BLACK);
	qiehuanzhanghao->addChild(qiehuanzhanghaoedbox, 3, 101);
	qiehuanzhanghaoedbox->setPlaceHolder(Global::getInstance()->getString("please input account"));

	qiehuanmimaedbox->setPosition(Vec2(330, 260));
	qiehuanmimaedbox->setInputMode(EditBox::InputMode::ANY);
	qiehuanmimaedbox->setDelegate(this);
	qiehuanmimaedbox->setFontSize(28);
	qiehuanmimaedbox->setFontColor(Color3B::BLACK);
	qiehuanzhanghao->addChild(qiehuanmimaedbox, 3, 101);
	qiehuanmimaedbox->setPlaceHolder(Global::getInstance()->getString("please input password"));

	auto btnLogin = (cocos2d::ui::Button*)seekNodeByName(rootGameSettingNode, "btnLogin");
	btnLogin->addTouchEventListener([=](Ref*, cocos2d::ui::Widget::TouchEventType type)
	{
		if (type == cocos2d::ui::Widget::TouchEventType::ENDED)
		{
			log("qiehuanzhanghao dengluyouxi xinxi");
			std::string zhanghao = qiehuanzhanghaoedbox->getText();
			std::string data = "account=" + zhanghao + "&password=" + qiehuanmimaedbox->getText();

			std::string url = "47.93.50.101:8080/QQWar/Qqwar/relogin";

			requestForPost(url, data.c_str(), [=](HttpClient *sender, HttpResponse *response)
			{
				if (response == nullptr || !response->isSucceed())
				{
					CCLOG("responese is null");
					CCLOG("responese not succeed");

					return;
				}

				vector<char> *buffer = response->getResponseData();

				std::string responseStr = std::string(buffer->begin(), buffer->end());
				CCLOG("%s", responseStr.c_str());

				Json* root = Json_create(responseStr.c_str());
				Json* result = Json_getItem(root, "resultCode");
				Json * resultObj = Json_getItem(root, "resultObj");

				/*if (result->type == Json_Number)
				{
				if (result->valueInt == 1)
				{
				log("*******************************qiehuanzhanghao success");

				Json * gmlevel = Json_getItem(resultObj, "gmlevel");
				Json * id = Json_getItem(resultObj, "id");
				Json* playerid = Json_getItem(resultObj, "playerid");
				Json* isbinded = Json_getItem(resultObj, "isbinded");
				Json* isforbidden = Json_getItem(resultObj, "isforbidden");
				Json* macip = Json_getItem(resultObj, "macip");
				Json* mail = Json_getItem(resultObj, "mail");
				Json* accout = Json_getItem(resultObj, "accout");
				Json* password = Json_getItem(resultObj, "password");

				account_info info;
				info.accout = accout->valueString;
				info.gmlevel = gmlevel->valueInt;
				info.id = id->valueInt;
				info.password = password->valueString;
				info.playerid = playerid->valueString;
				info.isforbidden = isforbidden->valueInt;
				info.isbinded = isbinded->valueInt;
				info.macip = macip->valueString;
				if (mail->valueString != NULL)
				info.mail = mail->valueString;

				Global::getInstance()->SetAccountInfo(info);
				UserDefault::getInstance()->setStringForKey("accout", accout->valueString);
				UserDefault::getInstance()->setStringForKey("password", password->valueString);

				}
				else
				{
				log("*******************************qiehuanzhanghao error");
				}
				}
				else
				{
				log("*******************************qiehuanzhanghao error");
				}*/



			}, "qieHuanZhangHao");







		}
	});

	auto btnForget = (cocos2d::ui::Button*)seekNodeByName(rootGameSettingNode, "btnForget");

	auto zhaohuimima = (cocos2d::ui::ImageView*)seekNodeByName(rootGameSettingNode, "zhaohuimima");
	btnForget->addTouchEventListener([=](Ref*, cocos2d::ui::Widget::TouchEventType type)
	{
		if (type == cocos2d::ui::Widget::TouchEventType::ENDED)
		{
			zhaohuimima->setVisible(true);
		}
	});

	//忘记密码 找回密码
	auto close5 = (cocos2d::ui::Button*)seekNodeByName(rootGameSettingNode, "close5");
	close5->addTouchEventListener([=](Ref*, cocos2d::ui::Widget::TouchEventType type)
	{
		if (type == cocos2d::ui::Widget::TouchEventType::ENDED)
		{
			zhaohuimima->setVisible(false);
		}
	});

	//忘记用户或密码 上的弹窗 输入框
	CEditBoxTool* zhaohuimimaEmailedbox = CEditBoxTool::Create(Size(300, 80), Scale9Sprite::create("input.png"));
	CEditBoxTool* zhaohuimimaYanZhengMaedbox = CEditBoxTool::Create(Size(300, 80), Scale9Sprite::create("input.png"));
	CEditBoxTool* zhaohuimimaNewPasswordedbox = CEditBoxTool::Create(Size(300, 80), Scale9Sprite::create("input.png"));

	zhaohuimimaEmailedbox->setPosition(Vec2(360, 470));
	zhaohuimimaEmailedbox->setInputMode(EditBox::InputMode::ANY);
	zhaohuimimaEmailedbox->setDelegate(this);
	zhaohuimimaEmailedbox->setFontSize(28);
	zhaohuimimaEmailedbox->setFontColor(Color3B::BLACK);
	zhaohuimima->addChild(zhaohuimimaEmailedbox, 3, 101);
	zhaohuimimaEmailedbox->setPlaceHolder(Global::getInstance()->getString("please input email"));

	zhaohuimimaYanZhengMaedbox->setPosition(Vec2(360, 340));
	zhaohuimimaYanZhengMaedbox->setInputMode(EditBox::InputMode::ANY);
	zhaohuimimaYanZhengMaedbox->setDelegate(this);
	zhaohuimimaYanZhengMaedbox->setFontSize(28);
	zhaohuimimaYanZhengMaedbox->setFontColor(Color3B::BLACK);
	zhaohuimima->addChild(zhaohuimimaYanZhengMaedbox, 3, 101);
	zhaohuimimaYanZhengMaedbox->setPlaceHolder(Global::getInstance()->getString("please input yanzhengma"));

	zhaohuimimaNewPasswordedbox->setPosition(Vec2(360, 230));
	zhaohuimimaNewPasswordedbox->setInputMode(EditBox::InputMode::ANY);
	zhaohuimimaNewPasswordedbox->setDelegate(this);
	zhaohuimimaNewPasswordedbox->setFontSize(28);
	zhaohuimimaNewPasswordedbox->setFontColor(Color3B::BLACK);
	zhaohuimima->addChild(zhaohuimimaNewPasswordedbox, 3, 101);
	zhaohuimimaNewPasswordedbox->setPlaceHolder(Global::getInstance()->getString("please input new password"));


	auto btnyanzhengma1 = (cocos2d::ui::Button*)seekNodeByName(rootGameSettingNode, "btnyanzhengma1");
	btnyanzhengma1->addTouchEventListener([=](Ref*, cocos2d::ui::Widget::TouchEventType type)
	{
		if (type == cocos2d::ui::Widget::TouchEventType::ENDED)
		{
			log("wangjiyonghu huo mima huoqu yanzhengma");
			//获取验证码
			std::string emailInput = zhaohuimimaEmailedbox->getText();
			std::string data = "";
			if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
			{
				data = "mail=" + emailInput + "@qq.com";
			}else
				data = "mail=" + emailInput;

			std::string url = "http://47.93.50.101:8080/QQWar/Qqwar/vaildcode";
			requestForPost(url, data.c_str(), [=](HttpClient *sender, HttpResponse *response)
			{
				if (response == nullptr || !response->isSucceed())
				{
					CCLOG("responese is null");
					CCLOG("responese not succeed");

					return;
				}

				vector<char> *buffer = response->getResponseData();

				std::string responseStr = std::string(buffer->begin(), buffer->end());
				CCLOG("%s", responseStr.c_str());

				/*Json* root = Json_create(responseStr.c_str());
				Json* result = Json_getItem(root, "resultCode");
				Json * resultObj = Json_getItem(root, "resultObj");

				if (result->type == Json_Number)
				{
				if (result->valueInt == 1)
				{
				log("*******************************bangdingyouxiang success");

				}
				else
				{
				log("*******************************bangding error");
				}
				}
				else
				{
				log("*******************************bangding error");
				}*/



			}, "getYanZhengMa1");
		}
	});

	auto btntijiao0 = (cocos2d::ui::Button*)seekNodeByName(rootGameSettingNode, "btntijiao0");
	btntijiao0->addTouchEventListener([=](Ref*, cocos2d::ui::Widget::TouchEventType type)
	{
		if (type == cocos2d::ui::Widget::TouchEventType::ENDED)
		{
			log("zhaohuimima tijiao xinxi");
			std::string emailInput = zhaohuimimaEmailedbox->getText();
			std::string data = "";
			if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
			{
				data = "&mail=" + emailInput + "qq.com" + "&password=" + zhaohuimimaNewPasswordedbox->getText() + "&code=" + zhaohuimimaYanZhengMaedbox->getText();
			}else
				data = "&mail=" + emailInput + "&password=" + zhaohuimimaNewPasswordedbox->getText() + "&code=" + zhaohuimimaYanZhengMaedbox->getText();
			//yanZhengMaedbox->getText();

			std::string url = "http://47.93.50.101:8080/QQWar/Qqwar/forgetpwd";

			requestForPost(url, data.c_str(), [=](HttpClient *sender, HttpResponse *response)
			{
				if (response == nullptr || !response->isSucceed())
				{
					CCLOG("responese is null");
					CCLOG("responese not succeed");

					return;
				}

				vector<char> *buffer = response->getResponseData();

				std::string responseStr = std::string(buffer->begin(), buffer->end());
				CCLOG("%s", responseStr.c_str());

				/*Json* root = Json_create(responseStr.c_str());
				Json* result = Json_getItem(root, "resultCode");
				Json * resultObj = Json_getItem(root, "resultObj");

				if (result->type == Json_Number)
				{
				if (result->valueInt == 1)
				{
				log("*******************************sheZhiXinMiMa success");

				Json * gmlevel = Json_getItem(resultObj, "gmlevel");
				Json * id = Json_getItem(resultObj, "id");
				Json* playerid = Json_getItem(resultObj, "playerid");
				Json* isbinded = Json_getItem(resultObj, "isbinded");
				Json* isforbidden = Json_getItem(resultObj, "isforbidden");
				Json* macip = Json_getItem(resultObj, "macip");
				Json* mail = Json_getItem(resultObj, "mail");
				Json* accout = Json_getItem(resultObj, "accout");
				Json* password = Json_getItem(resultObj, "password");

				account_info info;
				info.accout = accout->valueString;
				info.gmlevel = gmlevel->valueInt;
				info.id = id->valueInt;
				info.password = password->valueString;
				info.playerid = playerid->valueString;
				info.isforbidden = isforbidden->valueInt;
				info.isbinded = isbinded->valueInt;
				info.macip = macip->valueString;
				if (mail->valueString != NULL)
				info.mail = mail->valueString;

				Global::getInstance()->SetAccountInfo(info);
				UserDefault::getInstance()->setStringForKey("accout", accout->valueString);
				UserDefault::getInstance()->setStringForKey("password", password->valueString);

				}
				else
				{
				log("*******************************shezhiXinMiMa error");
				}
				}
				else
				{
				log("*******************************sheZhiXinMiMa error");
				}*/



			}, "xinMiMa");


		}
	});

	//绑定邮箱
	auto bangdingyouxiang = (cocos2d::ui::ImageView*)seekNodeByName(rootGameSettingNode, "bangdingyouxiang");
	auto btnBangYouXiang = (cocos2d::ui::Button*)seekNodeByName(rootGameSettingNode, "btnBangYouXiang");
	auto btnyanzhengma = (cocos2d::ui::Button*)seekNodeByName(rootGameSettingNode, "btnyanzhengma");



	btnBangYouXiang->addTouchEventListener([=](Ref*, cocos2d::ui::Widget::TouchEventType type)
	{
		if (type == cocos2d::ui::Widget::TouchEventType::ENDED)
		{
			bangdingyouxiang->setVisible(true);
		}
	});

	//绑定邮箱输入框
	CEditBoxTool* inputMiMadbox = CEditBoxTool::Create(Size(300, 80), Scale9Sprite::create("input.png"));
	CEditBoxTool* emaildbox = CEditBoxTool::Create(Size(300, 80), Scale9Sprite::create("input.png"));
	CEditBoxTool* yanZhengMaedbox = CEditBoxTool::Create(Size(300, 80), Scale9Sprite::create("input.png"));


	inputMiMadbox->setPlaceHolder(Global::getInstance()->getString("please input password"));
	inputMiMadbox->setPosition(Vec2(365, 470));
	inputMiMadbox->setInputMode(EditBox::InputMode::ANY);
	inputMiMadbox->setDelegate(this);
	inputMiMadbox->setFontSize(28);
	inputMiMadbox->setFontColor(Color3B::BLACK);
	bangdingyouxiang->addChild(inputMiMadbox, 3, 101);
	inputMiMadbox->setPlaceHolder(Global::getInstance()->getString("please input password"));

	emaildbox->setPlaceHolder(Global::getInstance()->getString("please input password"));
	emaildbox->setPosition(Vec2(365, 350));
	emaildbox->setInputMode(EditBox::InputMode::ANY);
	emaildbox->setDelegate(this);
	emaildbox->setFontSize(28);
	emaildbox->setFontColor(Color3B::BLACK);
	
	bangdingyouxiang->addChild(emaildbox, 3, 101);
	emaildbox->setPlaceHolder(Global::getInstance()->getString("please input password"));

	yanZhengMaedbox->setPlaceHolder(Global::getInstance()->getString("please input password"));
	yanZhengMaedbox->setPosition(Vec2(365, 220));
	yanZhengMaedbox->setInputMode(EditBox::InputMode::EMAIL_ADDRESS);
	yanZhengMaedbox->setDelegate(this);
	yanZhengMaedbox->setFontSize(28);
	yanZhengMaedbox->setFontColor(Color3B::BLACK);
	bangdingyouxiang->addChild(yanZhengMaedbox, 3, 101);
	yanZhengMaedbox->setPlaceHolder(Global::getInstance()->getString("input password"));

	btnyanzhengma->addTouchEventListener([=](Ref*, cocos2d::ui::Widget::TouchEventType type)
	{
		if (type == cocos2d::ui::Widget::TouchEventType::ENDED)
		{
			//获取验证码
			std::string data = "";
			if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
			{
				data = "playerid=" + info.playerid + "&mail=" + emaildbox->getText() + "@qq.com";
			}else
				 data = "playerid=" + info.playerid + "&mail=" + emaildbox->getText();

			std::string url = "http://47.93.50.101:8080/QQWar/Qqwar/vaildcode";
			requestForPost(url, data.c_str(), [=](HttpClient *sender, HttpResponse *response)
			{
				if (response == nullptr || !response->isSucceed())
				{
					CCLOG("responese is null");
					CCLOG("responese not succeed");

					return;
				}

				vector<char> *buffer = response->getResponseData();

				std::string responseStr = std::string(buffer->begin(), buffer->end());
				CCLOG("%s", responseStr.c_str());

				/*Json* root = Json_create(responseStr.c_str());
				Json* result = Json_getItem(root, "resultCode");
				Json * resultObj = Json_getItem(root, "resultObj");

				if (result->type == Json_Number)
				{
				if (result->valueInt == 1)
				{
				log("*******************************bangdingyouxiang success");

				}
				else
				{
				log("*******************************bangding error");
				}
				}
				else
				{
				log("*******************************bangding error");
				}*/



			}, "getYanZhengMa");
		}
	});



	auto close4 = (cocos2d::ui::Button*)seekNodeByName(rootGameSettingNode, "close4");
	close4->addTouchEventListener([=](Ref*, cocos2d::ui::Widget::TouchEventType type)
	{
		if (type == cocos2d::ui::Widget::TouchEventType::ENDED)
		{
			bangdingyouxiang->setVisible(false);
		}
	});

	auto btntijiao1 = (cocos2d::ui::Button*)seekNodeByName(rootGameSettingNode, "btntijiao1");
	btntijiao1->addTouchEventListener([=](Ref*, cocos2d::ui::Widget::TouchEventType type)
	{
		if (type == cocos2d::ui::Widget::TouchEventType::ENDED)
		{
			log("bangdingyouxiang tijiao xinxi");
			std::string data = "";
			if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
			{
				data = "playerid=" + info.playerid + "&mail=" + emaildbox->getText() + "qq.com" + "&password=" + inputMiMadbox->getText() + "&code=" + yanZhengMaedbox->getText();
			}else
				data = "playerid=" + info.playerid + "&mail=" + emaildbox->getText() + "&password=" + inputMiMadbox->getText() + "&code=" + yanZhengMaedbox->getText();
				//yanZhengMaedbox->getText();

			std::string url = "http://47.93.50.101:8080/QQWar/Qqwar/bindmail";

			requestForPost(url, data.c_str(), [=](HttpClient *sender, HttpResponse *response)
			{
				if (response == nullptr || !response->isSucceed())
				{
					CCLOG("responese is null");
					CCLOG("responese not succeed");

					return;
				}

				vector<char> *buffer = response->getResponseData();

				std::string responseStr = std::string(buffer->begin(), buffer->end());
				CCLOG("%s", responseStr.c_str());

				Json* root = Json_create(responseStr.c_str());
				Json* result = Json_getItem(root, "resultCode");
				Json * resultObj = Json_getItem(root, "resultObj");

				if (result->type == Json_Number)
				{
					if (result->valueInt == 1)
					{
						log("*******************************bangdingyouxiang success");

						Json * gmlevel = Json_getItem(resultObj, "gmlevel");
						Json * id = Json_getItem(resultObj, "id");
						Json* playerid = Json_getItem(resultObj, "playerid");
						Json* isbinded = Json_getItem(resultObj, "isbinded");
						Json* isforbidden = Json_getItem(resultObj, "isforbidden");
						Json* macip = Json_getItem(resultObj, "macip");
						Json* mail = Json_getItem(resultObj, "mail");
						Json* accout = Json_getItem(resultObj, "accout");
						Json* password = Json_getItem(resultObj, "password");

						account_info info;
						info.accout = accout->valueString;
						info.gmlevel = gmlevel->valueInt;
						info.id = id->valueInt;
						info.password = password->valueString;
						info.playerid = playerid->valueString;
						info.isforbidden = isforbidden->valueInt;
						info.isbinded = isbinded->valueInt;
						info.macip = macip->valueString;
						if (mail->valueString != NULL)
							info.mail = mail->valueString;

						Global::getInstance()->SetAccountInfo(info);
						UserDefault::getInstance()->setStringForKey("accout", accout->valueString);
						UserDefault::getInstance()->setStringForKey("password", password->valueString);

					}
					else
					{
						log("*******************************bangding error");
					}
				}
				else
				{
					log("*******************************bangding error");
				}



			}, "BangDingYouXiang");

		}
	});

	addChild(rootGameSettingNode,10000);

}
void LoginLayer::TeamClick(cocos2d::Ref *pSender)
{
	MainScene* main = dynamic_cast<MainScene*>(getParent());
	main->CheckLayer(MainScene::TAG_LAYER_TUANDUI);
}
void LoginLayer::SetNameOK()
{
	SheZhi* layer = (SheZhi*)getChildByTag(131);
	layer->SetNameOK();
}
void LoginLayer::LiveClick(cocos2d::Ref *pSender)
{
	ShengCun* layer = ShengCun::create();
	addChild(layer, 10, TAG_SHENGCUN);
	//Global::getInstance()->ShowPromBox("测试看看这个德行不");
}

void LoginLayer::editBoxReturn(cocos2d::extension::EditBox *editBox)
{

}

void LoginLayer::RespMagicClick()
{

}
void LoginLayer::rushmenpiao()
{
	ShengCun* layer = (ShengCun*)getChildByTag(TAG_SHENGCUN);
	if (layer) {
		layer->rushmenpiao();
	}
}

void LoginLayer::JingJiChangClick(Ref* pSender)
{
	log("===================================jingjichang");
	auto YuanZhengLayer = YuanZhengLayer::create();
	addChild(YuanZhengLayer, 100000);
}

void LoginLayer::ShengYiClick(Ref* pSender)
{
	log("===================================shengyi");
	auto timeYuanZhengLayer = TimeYuanZhengLayer::create();
	addChild(timeYuanZhengLayer, 100000);
}

bool LoginLayer::onTouchBegan(Touch *touch, Event *unused_event)
{
	if (rootGameSettingNode)
	{
		auto setBox = (cocos2d::ui::ImageView*)seekNodeByName(rootGameSettingNode, "setBox");
		if (!setBox->getBoundingBox().containsPoint(touch->getLocation()))
		{
			rootGameSettingNode->removeFromParent();
			rootGameSettingNode = nullptr;
		}
	}
	return true;
}

void LoginLayer::onTouchEnded(Touch *touch, Event *unused_event)
{
	if (rootGameSettingNode)
	{
		auto setBox = (cocos2d::ui::ImageView*)seekNodeByName(rootGameSettingNode, "setBox");
		if (!setBox->getBoundingBox().containsPoint(touch->getLocation()))
		{
			rootGameSettingNode->removeFromParent();
			rootGameSettingNode = nullptr;
		}

	}
}

void LoginLayer::initDengLuData()
{
	std::string UserAcc = ExchangeInfo::getIdentifier();
	std::string zhanghao = UserDefault::getInstance()->getStringForKey("accout");
	std::string mima = UserDefault::getInstance()->getStringForKey("password");
	if (zhanghao != "" && mima != "")
	{
		log("*******************************zhanghao: %s mima:  %s", zhanghao.c_str(), mima.c_str());
	}


	std::string data = "account=" + zhanghao + "&password=" + mima + "&macip=" + UserAcc;
	if (zhanghao == "" && mima == "")
	{
		data = "account=null&password=null&macip=" + UserAcc;
	}
	std::string url = "http://47.93.50.101:8080/QQWar/Qqwar/validateUserLogin";

	requestForPost(url, data.c_str(), [=](HttpClient *sender, HttpResponse *response)
	{
		if (response == nullptr || !response->isSucceed())
		{
			CCLOG("responese is null");
			CCLOG("responese not succeed");

			return;
		}

		vector<char> *buffer = response->getResponseData();

		std::string responseStr = std::string(buffer->begin(), buffer->end());
		CCLOG("%s", responseStr.c_str());

		Json* root = Json_create(responseStr.c_str());
		Json* result = Json_getItem(root, "resultCode");

		if (result->type == Json_Number)
		{
			if (result->valueInt == 1)
			{
				log("user: %s", UserAcc.c_str());

				Json* resultObj = Json_getItem(root, "resultObj");
				Json* account = Json_getItem(resultObj, "account");
				Json* accout = Json_getItem(account, "accout");
				Json* password = Json_getItem(account, "password");
				Json* player = Json_getItem(resultObj, "player");
				if (account->child != NULL)
				{
					if (accout->valueString != "" && password->valueString != "")
					{
						UserDefault::getInstance()->setStringForKey("accout", accout->valueString);
						UserDefault::getInstance()->setStringForKey("password", password->valueString);
						Json * gmlevel = Json_getItem(account, "gmlevel");
						Json * id = Json_getItem(account, "id");
						Json* playerid = Json_getItem(account, "playerid");
						Json* isbinded = Json_getItem(account, "isbinded");
						Json* isforbidden = Json_getItem(account, "isforbidden");
						Json* macip = Json_getItem(account, "macip");
						Json* mail = Json_getItem(account, "mail");

						account_info info;
						info.accout = accout->valueString;
						info.gmlevel = gmlevel->valueInt;
						info.id = id->valueInt;
						info.password = password->valueString;
						info.playerid = playerid->valueString;
						info.isforbidden = isforbidden->valueInt;
						info.isbinded = isbinded->valueInt;
						info.macip = macip->valueString;
						if (mail->valueString != NULL)
							info.mail = mail->valueString;

						Global::getInstance()->SetAccountInfo(info);


						head_info headInfo;
						Json* monthcard = Json_getItem(player, "monthcard");
						Json* yearcard = Json_getItem(player, "yearcard");
						Json* headid = Json_getItem(player, "headid");
						Json* grade = Json_getItem(player, "grade");
						Json* playername = Json_getItem(player, "playername");

						headInfo.monthcard = monthcard->valueInt;
						headInfo.yearcard = yearcard->valueInt;
						headInfo.grade = grade->valueString;
						headInfo.headid = headid->valueString;
						headInfo.playername = playername->valueString;
						Global::getInstance()->SetHeadInfo(headInfo);


						auto biankuangAll = (cocos2d::ui::ImageView*)seekNodeByName(rootNode, "biankuangAll");
						auto biankuangAllnian = (cocos2d::ui::ImageView*)seekNodeByName(biankuangAll, "nian");
						auto biankuangAllyue = (cocos2d::ui::ImageView*)seekNodeByName(biankuangAll, "yue");
						auto biankuangNian = (cocos2d::ui::ImageView*)seekNodeByName(rootNode, "biankuangNian");
						auto biankuangNianNian = (cocos2d::ui::ImageView*)seekNodeByName(biankuangNian, "nian");
						auto biankuangYue = (cocos2d::ui::ImageView*)seekNodeByName(rootNode, "biankuangYue");
						auto biankuangYueYue = (cocos2d::ui::ImageView*)seekNodeByName(biankuangYue, "yue");

						auto playerName = (cocos2d::ui::Text*)seekNodeByName(rootNode, "playerName");
						auto head = (cocos2d::ui::ImageView*)seekNodeByName(rootNode, "head");

						if (headInfo.monthcard == 0 && headInfo.yearcard == 0)
						{
							biankuangAll->setVisible(false);
							biankuangNian->setVisible(false);
							biankuangYue->setVisible(false);
						}
						else if (headInfo.monthcard > 0 && headInfo.yearcard > 0)
						{
							biankuangAll->setVisible(true);
							biankuangNian->setVisible(false);
							biankuangYue->setVisible(false);
							std::ostringstream nianFlag;
							nianFlag.clear();
							nianFlag << "DaTingLayer\\touxiang\\nian" << headInfo.yearcard << ".png";
							biankuangAllnian->loadTexture(nianFlag.str());
							std::ostringstream yueFlag;
							yueFlag.clear();
							yueFlag << "DaTingLayer\\touxiang\\yue" << headInfo.monthcard << ".png";
							biankuangAllyue->loadTexture(yueFlag.str());
						}
						else if (headInfo.monthcard > 0)
						{
							biankuangAll->setVisible(false);
							biankuangNian->setVisible(false);
							biankuangYue->setVisible(true);
							std::ostringstream yueFlag;
							yueFlag.clear();
							yueFlag << "DaTingLayer\\touxiang\\yue" << headInfo.monthcard << ".png";
							biankuangYueYue->loadTexture(yueFlag.str());
						}
						else if (headInfo.yearcard > 0)
						{
							biankuangAll->setVisible(false);
							biankuangNian->setVisible(true);
							biankuangYue->setVisible(false);
							std::ostringstream nianFlag;
							nianFlag.clear();
							nianFlag << "DaTingLayer\\touxiang\\nian" << headInfo.yearcard << ".png";
							biankuangNianNian->loadTexture(nianFlag.str());
						}

						playerName->setText(headInfo.playername.c_str());

						std::string headImgPath = "Head\\" + headInfo.headid;
						head->loadTexture(headImgPath.c_str());

						//根据网络请求过来的段位接口 初始化头像信息
						getDuanWeiInfoByIndex(atoi(headInfo.grade.c_str()));






					}
				}

				// ui login
				/*UM_Login req;
				req.set_acc(UserAcc.c_str());
				req.set_passwd(UserPass.c_str());
				std::string str = req.SerializeAsString();

				reqSendUIMsg(IDUM_Login, str);*/

			}
			else
			{
				log("*******************************login error: %s", UserAcc.c_str());
			}
		}
		else
		{
			log("*******************************login error: %s ", UserAcc.c_str());
		}



	}, "Login");
}

void LoginLayer::initWaitBox()
{
	auto  zuduidengdaiBg = (cocos2d::ui::ImageView*)seekNodeByName(rootNode, "zuduidengdaiBg");
	zuduidengdaiBg->setZOrder(100000);
	zuduidengdaiBg->setVisible(true);
	waitBoxVec2 = zuduidengdaiBg->getPosition();
	//auto moveTo = MoveBy::create(0.2, Vec2(waitBoxVec2.x, waitBoxVec2.y - zuduidengdaiBg->getContentSize().height * 2));
	auto moveTo = MoveBy::create(0.2, Vec2(648, 650));
	//zuduidengdaiBg->runAction(moveTo);
	auto moveToBack = moveTo->reverse();
	auto titleImg = (cocos2d::ui::ImageView*)seekNodeByName(rootNode, "titleImg");
	std::string  titleStr = "" + Global::getInstance()->GetWaitTimeBoxTitleStr();
	log("=================%s",titleStr.c_str());
	titleImg->loadTexture(titleStr);
	this->schedule(schedule_selector(LoginLayer::timeUpdate), 1);

	auto btnZuduiClose = (cocos2d::ui::Button*)seekNodeByName(rootNode, "btnZuduiClose");
	btnZuduiClose->addTouchEventListener([=](Ref*, cocos2d::ui::Widget::TouchEventType type)
	{
		if (type == cocos2d::ui::Widget::TouchEventType::ENDED)
		{
			//zuduidengdaiBg->runAction(moveToBack);
			zuduidengdaiBg->setVisible(false);
			this->unschedule(schedule_selector(LoginLayer::timeUpdate));
			upFenTime = 0;
			upMiaoTime = 0;
		}
	});
}

void LoginLayer::timeUpdate(float dt)
{
	upMiaoTime++;
	auto startTime = (cocos2d::ui::Text*)seekNodeByName(rootNode, "startTime");

	if (upMiaoTime >= 60)
	{
		upMiaoTime = 0;
		upFenTime++;
	}
	
	std::ostringstream tt;
	std::ostringstream t1;
	std::ostringstream s1;
	std::ostringstream s2;
	std::ostringstream s3;


	if (upMiaoTime < 10 && upFenTime == 0 )
	{
		tt << "00:0" << upMiaoTime;
		startTime->setText(tt.str());
	}
	else if (upMiaoTime < 60 && upFenTime == 0)
	{
		t1 << "00:" << upMiaoTime;
		startTime->setText(t1.str());
	}
	else if (upMiaoTime < 10 && upFenTime < 10)
	{
		s1 << "0" << upFenTime << ":0" + upMiaoTime;
		startTime->setText(s1.str());
	}
	else if (upMiaoTime < 60 && upFenTime < 10)
	{
		s2 << upFenTime << ":0" + upMiaoTime;
		startTime->setText(s2.str());
	}
	else if (upMiaoTime < 60 && upFenTime < 60)
	{
		s3 << upFenTime << ":" + upMiaoTime;
		startTime->setText(s3.str());
	}
	
}

void LoginLayer::hideWaitBox()
{
	auto  zuduidengdaiBg = (cocos2d::ui::ImageView*)seekNodeByName(rootNode, "zuduidengdaiBg");
	zuduidengdaiBg->setVisible(false);
	this->unschedule(schedule_selector(LoginLayer::timeUpdate));
	upFenTime = 0;
	upMiaoTime = 0;
}

void LoginLayer::getDuanWeiInfoByIndex(int index)
{
	Json* root = ReadJson("duanwei.json");

	Json* jsonChild = root->child;
	int i = -1;
	while (jsonChild)
	{
		i++;
		switch (jsonChild->type)
		{
		case Json_NULL:
			break;
		case Json_Number:
			break;
		case Json_Object:
		{

							if ((index - 1) == i)
							{
								Json* duanweiName = Json_getItem(jsonChild, "duanweiName");
								//CCLog("<<<<<<%s", title->valuestring);
								Json *duanweiDesc = Json_getItem(jsonChild, "duanweiDesc");
								Json * duanweiIcon = Json_getItem(jsonChild, "duanweiIcon");
								Json* xingliang = Json_getItem(jsonChild, "xingliang");
								Json* xingan = Json_getItem(jsonChild, "xingan");
								Json* xingnum1 = Json_getItem(jsonChild, "xingnum");
								log("段位描述==========================%s", duanweiDesc->valueString);
								log("段位名称==========================%s", duanweiName->valueString);
								log("段位图标==========================%s", duanweiIcon->valueString);
								log("亮星==========================%d", xingliang->valueInt);
								log("暗星==========================%d", xingan->valueInt);
								log("星数量==========================%d", xingnum1->valueInt);
								
								auto duanwei = (cocos2d::ui::ImageView*)seekNodeByName(rootNode, "duanwei");
								auto duanweiNameText = (cocos2d::ui::Text*)seekNodeByName(rootNode, "duanweiName");
								std::string duanName = duanweiName->valueString;
								duanweiNameText->setText(duanName);
								std::string iconStr = duanweiIcon->valueString;
								std::string iconPath = "DaTingLayer\\touxiang\\" + iconStr;
								duanwei->loadTexture(iconPath.c_str());
								auto xing1 = (cocos2d::ui::ImageView*)seekNodeByName(rootNode, "xing1");
								auto xing2 = (cocos2d::ui::ImageView*)seekNodeByName(rootNode, "xing2");
								auto xing3 = (cocos2d::ui::ImageView*)seekNodeByName(rootNode, "xing3");
								auto xing4 = (cocos2d::ui::ImageView*)seekNodeByName(rootNode, "xing4");
								auto xing5 = (cocos2d::ui::ImageView*)seekNodeByName(rootNode, "xing5");
								auto xing6 = (cocos2d::ui::ImageView*)seekNodeByName(rootNode, "xing6");
								auto xing7 = (cocos2d::ui::ImageView*)seekNodeByName(rootNode, "xing7");


								if (index-1 <= 3) //小于3个段位
								{
									xing1->setVisible(true);
									xing2->setVisible(true);
									xing3->setVisible(true);
									switch (xingan->valueInt)
									{
									case 1:
									{
											  xing3->loadTexture("DaTingLayer\\touxiang\\anxing.png");
									}
										break;
									case 2:
									{
											  xing2->loadTexture("DaTingLayer\\touxiang\\anxing.png");
											  xing3->loadTexture("DaTingLayer\\touxiang\\anxing.png");
									}
										break;
									case 3:
									{
											  xing1->loadTexture("DaTingLayer\\touxiang\\anxing.png");
											  xing2->loadTexture("DaTingLayer\\touxiang\\anxing.png");
											  xing3->loadTexture("DaTingLayer\\touxiang\\anxing.png");
									}
										break;
									default:
										break;
									}
								}
								else if (index-1 <= 38)
								{
									xing1->setVisible(true);
									xing2->setVisible(true);
									xing3->setVisible(true);
									xing4->setVisible(true);
									xing5->setVisible(true);

									switch (xingan->valueInt)
									{
									case 1:
									{
											  xing5->loadTexture("DaTingLayer\\touxiang\\anxing.png");
									}
										break;
									case 2:
									{
											  xing4->loadTexture("DaTingLayer\\touxiang\\anxing.png");
											  xing5->loadTexture("DaTingLayer\\touxiang\\anxing.png");
									}
										break;
									case 3:
									{
											  xing3->loadTexture("DaTingLayer\\touxiang\\anxing.png");
											  xing4->loadTexture("DaTingLayer\\touxiang\\anxing.png");
											  xing5->loadTexture("DaTingLayer\\touxiang\\anxing.png");
									}
										break;
									case 4:
									{
											  xing2->loadTexture("DaTingLayer\\touxiang\\anxing.png");
											  xing3->loadTexture("DaTingLayer\\touxiang\\anxing.png");
											  xing4->loadTexture("DaTingLayer\\touxiang\\anxing.png");
											  xing5->loadTexture("DaTingLayer\\touxiang\\anxing.png");
									}
										break;
									case 5:
									{
											  xing1->loadTexture("DaTingLayer\\touxiang\\anxing.png");
											  xing2->loadTexture("DaTingLayer\\touxiang\\anxing.png");
											  xing3->loadTexture("DaTingLayer\\touxiang\\anxing.png");
											  xing4->loadTexture("DaTingLayer\\touxiang\\anxing.png");
											  xing5->loadTexture("DaTingLayer\\touxiang\\anxing.png");
									}
										break;
									default:
										break;
									}
								}
								else
								{
									xing1->setVisible(true);
									xing2->setVisible(true);
									xing3->setVisible(true);
									xing4->setVisible(true);
									xing5->setVisible(true);
									xing6->setVisible(true);
									xing7->setVisible(true);

									switch (xingan->valueInt)
									{
									case 1:
									{
											  xing7->loadTexture("DaTingLayer\\touxiang\\anxing.png");
									}
										break;
									case 2:
									{
											  xing6->loadTexture("DaTingLayer\\touxiang\\anxing.png");
											  xing7->loadTexture("DaTingLayer\\touxiang\\anxing.png");
									}
										break;
									case 3:
									{
											  xing5->loadTexture("DaTingLayer\\touxiang\\anxing.png");
											  xing6->loadTexture("DaTingLayer\\touxiang\\anxing.png");
											  xing7->loadTexture("DaTingLayer\\touxiang\\anxing.png");
									}
										break;
									case 4:
									{
											  xing4->loadTexture("DaTingLayer\\touxiang\\anxing.png");
											  xing5->loadTexture("DaTingLayer\\touxiang\\anxing.png");
											  xing6->loadTexture("DaTingLayer\\touxiang\\anxing.png");
											  xing7->loadTexture("DaTingLayer\\touxiang\\anxing.png");
									}
										break;
									case 5:
									{
											  xing3->loadTexture("DaTingLayer\\touxiang\\anxing.png");
											  xing4->loadTexture("DaTingLayer\\touxiang\\anxing.png");
											  xing5->loadTexture("DaTingLayer\\touxiang\\anxing.png");
											  xing6->loadTexture("DaTingLayer\\touxiang\\anxing.png");
											  xing7->loadTexture("DaTingLayer\\touxiang\\anxing.png");
									}
										break;
									case 6:
									{
											  xing2->loadTexture("DaTingLayer\\touxiang\\anxing.png");
											  xing3->loadTexture("DaTingLayer\\touxiang\\anxing.png");
											  xing4->loadTexture("DaTingLayer\\touxiang\\anxing.png");
											  xing5->loadTexture("DaTingLayer\\touxiang\\anxing.png");
											  xing6->loadTexture("DaTingLayer\\touxiang\\anxing.png");
											  xing7->loadTexture("DaTingLayer\\touxiang\\anxing.png");
									}
										break;
									case 7:
									{
											  xing1->loadTexture("DaTingLayer\\touxiang\\anxing.png");
											  xing2->loadTexture("DaTingLayer\\touxiang\\anxing.png");
											  xing3->loadTexture("DaTingLayer\\touxiang\\anxing.png");
											  xing4->loadTexture("DaTingLayer\\touxiang\\anxing.png");
											  xing5->loadTexture("DaTingLayer\\touxiang\\anxing.png");
											  xing6->loadTexture("DaTingLayer\\touxiang\\anxing.png");
											  xing7->loadTexture("DaTingLayer\\touxiang\\anxing.png");
									}
									default:
										break;
									}
								}

								if (xingan->valueInt == 0)
								{
									xing1->setVisible(false);
									xing2->setVisible(false);
									xing3->setVisible(false);
									xing4->setVisible(false);
									xing5->setVisible(false);
									xing6->setVisible(false);
									xing7->setVisible(false);
									switch (xingliang->valueInt)
									{
									case 1:
									{
											  xing1->setVisible(true);
									}
										break;
									case 2:
									{
											  xing1->setVisible(true);
											  xing2->setVisible(true);
									}
										break;
									case 3:
									{
											  xing1->setVisible(true);
											  xing2->setVisible(true);
											  xing3->setVisible(true);
											
									}
										break;
									case 4:
									{
											  xing1->setVisible(true);
											  xing2->setVisible(true);
											  xing3->setVisible(true);  
											  xing4->setVisible(true);
											
									}
										break;
									case 5:
									{
											  xing1->setVisible(true);
											  xing2->setVisible(true);
											  xing3->setVisible(true);
											  xing4->setVisible(true);
											  xing5->setVisible(true);
											
									}
										break;
									case 6:
									{
											  xing1->setVisible(true);
											  xing2->setVisible(true);
											  xing3->setVisible(true);
											  xing4->setVisible(true);
											  xing5->setVisible(true);
											  xing6->setVisible(true);
									}
										break;
									case 7:
									{
											  xing1->setVisible(true);
											  xing2->setVisible(true);
											  xing3->setVisible(true);
											  xing4->setVisible(true);
											  xing5->setVisible(true);
											  xing6->setVisible(true);
											  xing7->setVisible(true);
									}
										break;
									default:
										break;
									}
								}

								auto xingNum = (cocos2d::ui::Text*)seekNodeByName(rootNode, "xingNum");
								xingNum->setText("" + xingnum1->valueInt);
								if (xingnum1->valueInt == 0)
									xingNum->setVisible(false);

								auto headButton = (cocos2d::ui::ImageView*)seekNodeByName(rootNode, "headButton");

								headButton->addTouchEventListener([=](Ref*, cocos2d::ui::Widget::TouchEventType type)
								{
									if (type == cocos2d::ui::Widget::TouchEventType::ENDED)
									{
										log("headButton clike=================");
									}
								});


							}					
		}
			break;
		case Json_String:
			log("<<<<<<%s", jsonChild->valueString);

			break;
		case Json_True:
			break;
		case Json_Array:
			break;
		default:
			break;
		}

		jsonChild = jsonChild->next;
	}
}

////////////////////////////////////////////////////////////////////
// 生存模式开始界面
////////////////////////////////////////////////////////////////////
ShengCun::ShengCun()
{
	isTouchIn = false;
	menpiaoNum = Global::getInstance()->GetBagItem(1001).count;
	lifeNum = 3;
	menpiaoxiaohao = 1;
}
ShengCun::~ShengCun()
{

}

bool ShengCun::init()
{
	if (!CPZLayer::init())
		return false;

	LayerColor* layer = LayerColor::create(Color4B(0, 0, 0, 80));
	addChild(layer);

	Sprite* back = Sprite::create("beijing-01.png");
	back->setPosition(Vec2(winSize.width * 0.5f, winSize.height * 0.5f));
	back->setScaleX(0.6f);
	back->setScaleY(0.8f);
	addChild(back, 0, 101);


	back = Sprite::create("xuanxiangkuang.png");
	back->setPosition(Vec2(winSize.width * 0.5f, winSize.height * 0.5f + 240));
	back->setScale(0.6f);
	addChild(back);

	back = Sprite::create("chushishengming-01.png");
	back->setPosition(Vec2(winSize.width * 0.5f - 370, winSize.height * 0.5f + 240));
	back->setScale(0.6f);
	addChild(back);

	Button* headbg = Button::createBtnWithSpriteFrameName("jian-01.png", false);
	headbg->setPosition(Vec2(winSize.width * 0.5f - 260, winSize.height * 0.5f + 240));
	headbg->setScale(0.6f);
	headbg->setOnClickCallback(callfuncO_selector(ShengCun::SubLife), this);
	addChild(headbg, 2, TAG_BtnJian);

	headbg->setVisible(false);

	back = Sprite::create("tiaowendikuang-01.png");
	back->setPosition(Vec2(winSize.width * 0.5f - 160, winSize.height * 0.5f + 240));
	back->setScale(0.6f);
	addChild(back);

	headbg = Button::createBtnWithSpriteFrameName("jia-01.png", false);
	headbg->setPosition(Vec2(winSize.width * 0.5f - 60, winSize.height * 0.5f + 240));
	headbg->setScale(0.6f);
	headbg->setOnClickCallback(callfuncO_selector(ShengCun::AddLife), this);
	addChild(headbg, 2, TAG_BtnJia);


	back = Sprite::create("ruchangjuan.png");
	back->setPosition(Vec2(winSize.width * 0.5f + 100, winSize.height * 0.5f + 240));
	back->setScale(0.15f);
	addChild(back);

	back = Sprite::create("ruchangquan-01.png");
	back->setPosition(Vec2(winSize.width * 0.5f + 210, winSize.height * 0.5f + 240));
	back->setScale(0.6f);
	addChild(back);

	back = Sprite::create("tiaowendikuang-01.png");
	back->setPosition(Vec2(winSize.width * 0.5f + 350, winSize.height * 0.5f + 240));
	back->setScale(0.6f);
	addChild(back);

	headbg = Button::createBtnWithSpriteFrameName("jia-01.png", false);
	headbg->setPosition(Vec2(winSize.width * 0.5f + 450, winSize.height * 0.5f + 240));
	headbg->setScale(0.6f);
	headbg->setOnClickCallback(callfuncO_selector(ShengCun::AddMenPiao), this);
	addChild(headbg, 2);

	char menpiao[16] = { 0 };
	sprintf(menpiao, "%d", menpiaoNum);

	CCLabelTTF* useName = CCLabelTTF::create(menpiao, "STXingkai.ttf", 30);
	useName->setPosition(Vec2(winSize.width * 0.5f + 350, winSize.height * 0.5f + 240));
	addChild(useName, 2, TAG_MENPIAOLAB);


	int i = 0;
	back = Sprite::create("hongxin-01.png");
	back->setPosition(Vec2(winSize.width * 0.5f - 200 + i * 40, winSize.height * 0.5f + 240));
	back->setScale(0.6f);
	addChild(back, 0, TAG_Xin1);

	i++;
	back = Sprite::create("hongxin-01.png");
	back->setPosition(Vec2(winSize.width * 0.5f - 200 + i * 40, winSize.height * 0.5f + 240));
	back->setScale(0.6f);
	addChild(back, 0, TAG_Xin2);

	i++;
	back = Sprite::create("hongxin-01.png");
	back->setPosition(Vec2(winSize.width * 0.5f - 200 + i * 40, winSize.height * 0.5f + 240));
	back->setScale(0.6f);
	addChild(back, 0, TAG_Xin3);

	sprintf(menpiao, "%d", lifeNum);
	useName = CCLabelTTF::create(menpiao, "STXingkai.ttf", 30);
	useName->setPosition(Vec2(winSize.width * 0.5f - 160, winSize.height * 0.5f + 240));
	addChild(useName, 2, TAG_Life);

	useName->setVisible(false);


	back = Sprite::create("shengcunmoshi-02.png");
	back->setPosition(Vec2(winSize.width * 0.5f, winSize.height * 0.5f + 90));
	back->setScale(0.6f);
	addChild(back);

	back = Sprite::create("shengcunmoshi-01.png");
	back->setPosition(Vec2(winSize.width * 0.5f, winSize.height * 0.5f - 60));
	back->setScale(0.6f);
	addChild(back);

	useName = CCLabelTTF::create(Global::getInstance()->getString("109"), "STXingkai.ttf", 25);
	useName->setPosition(Vec2(winSize.width * 0.5f - 60, winSize.height * 0.5f - 120));
	useName->setColor(Color3B(0, 0, 0));
	addChild(useName, 2);

	back = Sprite::create("ruchangjuan.png");
	back->setPosition(Vec2(winSize.width * 0.5f + 90, winSize.height * 0.5f - 120));
	back->setScale(0.1f);
	addChild(back);

	sprintf(menpiao, "%d", menpiaoxiaohao);
	useName = CCLabelTTF::create(menpiao, "STXingkai.ttf", 25);
	useName->setAnchorPoint(Vec2(0.0f, 0.5f));
	useName->setPosition(Vec2(winSize.width * 0.5f + 130, winSize.height * 0.5f - 120));
	useName->setColor(Color3B(0, 0, 0));
	addChild(useName, 2, TAG_MenpiaoXiaohao);

	headbg = Button::createBtnWithSpriteFrameName("kaishibisai-01.png", false);
	headbg->setPosition(Vec2(winSize.width * 0.5f, winSize.height * 0.5f - 200));
	headbg->setScale(0.6f);
	headbg->setPressIcon("kaishibisai-02.png", false);
	headbg->setOnClickCallback(callfuncO_selector(ShengCun::StartGame), this);
	addChild(headbg, 2);
	return true;
}
void ShengCun::rushmenpiao()
{
	menpiaoNum = Global::getInstance()->GetBagItem(1001).count;

	char menpiao[16] = { 0 };
	sprintf(menpiao, "%d", menpiaoNum);

	CCLabelTTF* useName = (CCLabelTTF*)getChildByTag(TAG_MENPIAOLAB);
	useName->setString(menpiao);

	LingRuchangQuan* layer = (LingRuchangQuan*)getParent()->getChildByTag(10);
	if (layer)
		layer->rushmenpiao();
}
void ShengCun::StartGame(Ref* pSender)
{
	if (menpiaoNum <= 0)
	{
		Global::getInstance()->ShowPromBox(Global::getInstance()->getString("110"));
		return;
	}

	if (menpiaoxiaohao <= 0)
	{
		Global::getInstance()->ShowPromBox(Global::getInstance()->getString("111"));
	}
	else
	{
		LoginLayer* login = dynamic_cast<LoginLayer*>(getParent());
		if (login)
		{
			bool isConnect = false;
			netInfo netID = login->getNetInfo();
			MainScene* main = dynamic_cast<MainScene*>(login->getParent());
			if (main)
			{
				isConnect = main->OpenWebSocket(netID.m_netUrl.c_str(), netID.m_netPort.c_str());
			}

			if (!isConnect)
				return;

			schedule(schedule_selector(ShengCun::delayEnter), 0.1f);
		}
	}
}
void ShengCun::delayEnter(float ft)
{
	if (!Global::getInstance()->getConnectState())
		return;

	unschedule(schedule_selector(ShengCun::delayEnter));


	LoginLayer* login = dynamic_cast<LoginLayer*>(getParent());
	netInfo netID = login->getNetInfo();
	MainScene* main = dynamic_cast<MainScene*>(login->getParent());
	// 获取战斗服务器秘钥
	main->reqServerKey(netID.m_netID, 1, menpiaoxiaohao);
	Global::getInstance()->SetFightType(1);
}
void ShengCun::AddLife(Ref* pSender)
{
	if (menpiaoxiaohao >= 10)
		return;
	menpiaoxiaohao++;
	lifeNum = menpiaoxiaohao / 3 * 10 + menpiaoxiaohao % 3 * 3;

	char menpiao[16] = { 0 };
	if (menpiaoxiaohao > 1) {
		sprintf(menpiao, "%d", lifeNum);

		CCLabelTTF* lab = (CCLabelTTF*)(getChildByTag(TAG_Life));
		lab->setVisible(true);
		lab->setString(menpiao);

		getChildByTag(TAG_BtnJian)->setVisible(true);
		getChildByTag(TAG_BtnJia)->setVisible(true);

		getChildByTag(TAG_Xin2)->setVisible(false);
		getChildByTag(TAG_Xin3)->setVisible(false);

		sprintf(menpiao, "%d", menpiaoxiaohao);
		lab = (CCLabelTTF*)(getChildByTag(TAG_MenpiaoXiaohao));
		lab->setString(menpiao);
	}

	if (menpiaoxiaohao >= 10)
	{
		getChildByTag(TAG_BtnJia)->setVisible(false);
	}

}
void ShengCun::SubLife(Ref* pSender)
{
	if (menpiaoxiaohao <= 1)
		return;
	menpiaoxiaohao--;
	lifeNum = menpiaoxiaohao / 3 * 10 + menpiaoxiaohao % 3 * 3;

	char menpiao[16] = { 0 };
	if (menpiaoxiaohao > 0) {
		sprintf(menpiao, "%d", lifeNum);

		CCLabelTTF* lab = (CCLabelTTF*)(getChildByTag(TAG_Life));
		lab->setVisible(true);
		lab->setString(menpiao);

		getChildByTag(TAG_BtnJian)->setVisible(true);
		getChildByTag(TAG_BtnJia)->setVisible(true);

		getChildByTag(TAG_Xin2)->setVisible(false);
		getChildByTag(TAG_Xin3)->setVisible(false);

		sprintf(menpiao, "%d", menpiaoxiaohao);
		lab = (CCLabelTTF*)(getChildByTag(TAG_MenpiaoXiaohao));
		lab->setString(menpiao);
	}

	if (menpiaoxiaohao <= 1)
	{
		getChildByTag(TAG_BtnJian)->setVisible(false);

		getChildByTag(TAG_Xin2)->setVisible(true);
		getChildByTag(TAG_Xin3)->setVisible(true);

		getChildByTag(TAG_Life)->setVisible(false);
	}
}
void ShengCun::AddMenPiao(Ref* pSender)
{
	LingRuchangQuan* layer = LingRuchangQuan::create();
	getParent()->addChild(layer, 50, 10);
}
bool ShengCun::onTouchBegan(Touch* pTouch, Event* pEvent)
{
	//Touch* pTouch = (Touch*)pTouches->anyObject();
	Node* node = getChildByTag(101);
	Point pt = node->convertToNodeSpace(Director::getInstance()->convertToGL(pTouch->getLocationInView()));
	Rect rt = Rect(0, 0, node->getContentSize().width, node->getContentSize().height);

	isTouchIn = rt.containsPoint(pt);

	return true;
}
void ShengCun::onTouchEnded(Touch* pTouch, Event* pEvent)
{
	if (isTouchIn)
		return;
	//Touch* pTouch = (Touch*)pTouches->anyObject();
	Node* node = getChildByTag(101);
	Point pt = node->convertToNodeSpace(Director::getInstance()->convertToGL(pTouch->getLocationInView()));
	Rect rt = Rect(0, 0, node->getContentSize().width, node->getContentSize().height);
	if (rt.containsPoint(pt) == false)
	{
		getParent()->removeChild(this);
	}
}

////////////////////////////////////////////////////////////////////
// 领取入场券界面
////////////////////////////////////////////////////////////////////
LingRuchangQuan::LingRuchangQuan()
{
	user_bag bag = Global::getInstance()->GetBagItem(1001);
	user_info info = Global::getInstance()->GetUserInfo();
	menpiaoNum = bag.count;
	money = info.gold;
}
LingRuchangQuan::~LingRuchangQuan()
{

}

bool LingRuchangQuan::init()
{
	if (!CPZLayer::init())
		return false;

	user_info info = Global::getInstance()->GetUserInfo();

	Sprite* back = Sprite::create("center_back.png");
	back->setPosition(Vec2(winSize.width * 0.5f, winSize.height * 0.5f));
	back->setScale(0.6f);
	addChild(back);

	CCLabelTTF* useName = CCLabelTTF::create(Global::getInstance()->getString("112"), "STXingkai.ttf", 45);
	useName->setPosition(Vec2(winSize.width * 0.5f - 430, winSize.height * 0.5f + 280));
	useName->setColor(Color3B(0, 0, 0));
	addChild(useName, 2);

	Button* backBtn = Button::createBtnWithSpriteFrameName("rankingback.png", false);
	backBtn->setPosition(Vec2(winSize.width - 110, 40));
	backBtn->setScale(0.6f);
	backBtn->setOnClickCallback(callfuncO_selector(LingRuchangQuan::BackClick), this);
	addChild(backBtn, 1);

	back = Sprite::create("ruchangjuan.png");
	back->setPosition(Vec2(winSize.width * 0.5f - 60, winSize.height * 0.5f + 280));
	back->setScale(0.15f);
	addChild(back);

	back = Sprite::create("xinxingdikuang-01.png");
	back->setPosition(Vec2(winSize.width * 0.5f + 470, winSize.height * 0.5f + 280));
	back->setScale(0.6f);
	addChild(back);

	useName = CCLabelTTF::create(Global::getInstance()->getString("113"), "STXingkai.ttf", 30);
	useName->setPosition(Vec2(winSize.width * 0.5f + 360, winSize.height * 0.5f + 280));
	useName->setColor(Color3B(0, 0, 0));
	addChild(useName, 2);

	back = Sprite::create("shop_yuanbao.png");
	back->setPosition(Vec2(winSize.width * 0.5f + 280, winSize.height * 0.5f + 280));
	back->setScale(0.6f);
	addChild(back);

	back = Sprite::create("xinxingdikuang-01.png");
	back->setPosition(Vec2(winSize.width * 0.5f + 180, winSize.height * 0.5f + 280));
	back->setScale(0.6f);
	addChild(back);

	useName = CCLabelTTF::create(Global::getInstance()->getString("114"), "STXingkai.ttf", 30);
	useName->setPosition(Vec2(winSize.width * 0.5f + 50, winSize.height * 0.5f + 280));
	useName->setColor(Color3B(0, 0, 0));
	addChild(useName, 2);

	for (int i = 0; i<2; i++) {
		back = Sprite::create("item_base.png");
		back->setPosition(Vec2(winSize.width * 0.5f - 180 + i * 360, winSize.height * 0.5f));
		back->setScale(0.6f);
		addChild(back);

		back = Sprite::create("ruchangquanbeijing-01.png");
		back->setPosition(Vec2(winSize.width * 0.5f - 180 + i * 360, winSize.height * 0.5f + 60));
		back->setScale(0.6f);
		addChild(back);

		back = Sprite::create("ruchangjuan.png");
		back->setPosition(Vec2(winSize.width * 0.5f - 180 + i * 355, winSize.height * 0.5f + 60));
		back->setScale(0.15f);
		back->setRotation(45);
		addChild(back);

		char tem[32] = { 0 };
		sprintf(tem, Global::getInstance()->getString("115"), i + 1);
		useName = CCLabelTTF::create(tem, "STXingkai.ttf", 35);
		useName->setPosition(Vec2(winSize.width * 0.5f - 180 + i * 360, winSize.height * 0.5f - 60));
		useName->setColor(Color3B(0, 0, 0));
		addChild(useName, 2);

		if (i == 0)
		{
			sprintf(tem, Global::getInstance()->getString("116"), info.freeTicket);
			useName = CCLabelTTF::create(tem, "STXingkai.ttf", 30);
			useName->setPosition(Vec2(winSize.width * 0.5f - 180 + i * 360, winSize.height * 0.5f - 100));
			useName->setColor(Color3B(0, 0, 0));
			addChild(useName, 2, TAG_LINQUCISHU);
		}
	}

	back = Sprite::create("ruchangjuan.png");
	back->setPosition(Vec2(winSize.width * 0.5f + 190, winSize.height * 0.5f + 60));
	back->setScale(0.15f);
	back->setRotation(70);
	addChild(back);

	backBtn = Button::createBtnWithSpriteFrameName("xinxingdikuang-01.png", false);
	backBtn->setPosition(Vec2(winSize.width * 0.5f - 180, winSize.height * 0.5f - 150));
	backBtn->setScale(0.7f);
	backBtn->setOnClickCallback(callfuncO_selector(LingRuchangQuan::FreeLing), this);
	addChild(backBtn, 1);

	useName = CCLabelTTF::create(Global::getInstance()->getString("117"), "STXingkai.ttf", 45);
	//useName->setPosition(Vec2(winSize.width * 0.5f-180 + i*360, winSize.height * 0.5f-100));
	//useName->setColor(Color3B(0, 0, 0));
	backBtn->addChild(useName, 2);

	backBtn = Button::createBtnWithSpriteFrameName("xinxingdikuang-01.png", false);
	backBtn->setPosition(Vec2(winSize.width * 0.5f + 180, winSize.height * 0.5f - 150));
	backBtn->setScale(0.7f);
	backBtn->setOnClickCallback(callfuncO_selector(LingRuchangQuan::GouMai), this);
	addChild(backBtn, 1);

	useName = CCLabelTTF::create("10", "STXingkai.ttf", 45);
	useName->setPosition(Vec2(-30, 0));
	//useName->setColor(Color3B(0, 0, 0));
	backBtn->addChild(useName, 2);

	back = Sprite::create("shop_yuanbao.png");
	back->setPosition(Vec2(50, 0));
	back->setScale(0.7f);
	backBtn->addChild(back);

	char ton[16] = { 0 };
	sprintf(ton, "%d", menpiaoNum);
	useName = CCLabelTTF::create(ton, "STXingkai.ttf", 30);
	useName->setPosition(Vec2(winSize.width * 0.5f + 180, winSize.height * 0.5f + 280));
	useName->setColor(Color3B(0, 0, 0));
	addChild(useName, 2, TAG_MENPIAOLAB);

	sprintf(ton, "%d", money);
	useName = CCLabelTTF::create(ton, "STXingkai.ttf", 30);
	useName->setPosition(Vec2(winSize.width * 0.5f + 470, winSize.height * 0.5f + 280));
	useName->setColor(Color3B(0, 0, 0));
	addChild(useName, 2, TAG_MONEYLAB);
	return true;
}
void LingRuchangQuan::rushmenpiao()
{
	user_bag bag = Global::getInstance()->GetBagItem(1001);
	user_info info = Global::getInstance()->GetUserInfo();
	menpiaoNum = bag.count;
	money = info.gold;

	char ton[64] = { 0 };
	sprintf(ton, "%d", menpiaoNum);
	CCLabelTTF* useName = (CCLabelTTF*)getChildByTag(TAG_MENPIAOLAB);
	useName->setString(ton);

	sprintf(ton, "%d", money);
	useName = (CCLabelTTF*)getChildByTag(TAG_MONEYLAB);
	useName->setString(ton);

	sprintf(ton, "今日可兑换：%d/1", info.freeTicket);
	useName = (CCLabelTTF*)getChildByTag(TAG_LINQUCISHU);
	useName->setString(ton);

}
void LingRuchangQuan::FreeLing(Ref* pSender)
{
	MainScene* scene = (MainScene*)getParent()->getParent();
	scene->reqGetTickets();
}
void LingRuchangQuan::GouMai(Ref* pSender)
{
	MainScene* scene = (MainScene*)getParent()->getParent();
	scene->reqBuyItem(1001);
}
void LingRuchangQuan::BackClick(Ref* pSender)
{
	getParent()->removeChild(this, true);
}


/////////////////////////////
FindFriend::FindFriend()
{

}
FindFriend::~FindFriend()
{

}

bool FindFriend::init()
{
	if (!CPZLayer::init())
		return false;

	LayerColor* layer = LayerColor::create(Color4B(0, 0, 0, 80));
	addChild(layer);

	Sprite* back = Sprite::create("dimianbeijing-01.png");
	back->setPosition(Vec2(winSize.width * 0.5f, winSize.height * 0.5f));
	back->setScale(0.6f);
	addChild(back);

	Button* backBtn = Button::createBtnWithSpriteFrameName("fangjianshezhi-guanbi-01.png", false);
	backBtn->setPosition(Vec2(winSize.width - 90, winSize.height - 70));
	backBtn->setScale(0.6f);
	backBtn->setOnClickCallback(callfuncO_selector(FindFriend::Back), this);
	addChild(backBtn, 1);

	Button* zhaopy = Button::createBtnWithSpriteFrameName("zhaopengyou-02.png", false);
	zhaopy->setPosition(Vec2(160, winSize.height - 70));
	zhaopy->setScale(0.6f);
	zhaopy->setOnClickCallback(callfuncO_selector(FindFriend::Zhaopengyou), this);
	zhaopy->setPressIcon("zhaopengyou-01.png", false);
	zhaopy->setPressIconShow(true);
	addChild(zhaopy, 1, TAG_FindFriend);
	/*
	Button* fujinderen = Button::createBtnWithSpriteFrameName("fujinderen-02.png", false);
	fujinderen->setPosition(Vec2(330, winSize.height - 70));
	fujinderen->setScale(0.6f);
	fujinderen->setOnClickCallback(callfuncO_selector(FindFriend::Fujinderen), this);
	fujinderen->setPressIcon("fujinderen-01.png", false);
	fujinderen->setPressIconShow(false);
	addChild(fujinderen, 1,TAG_Fujinderen);
	*/
	back = Sprite::create("fenxian-01.png");
	back->setPosition(Vec2(winSize.width * 0.5f, winSize.height - 100));
	back->setScale(0.6f);
	addChild(back);

	m_currentTag = TAG_NONE;

	Zhaopengyou(zhaopy);

	return true;
}
void FindFriend::InitZhaoPYUI()
{
	Layer* pyLayer = Layer::create();
	addChild(pyLayer, 5, TAG_PYLayer);


	Sprite* inputbg = Sprite::create("shurukuang-01.png");
	inputbg->setScale(0.6f);
	inputbg->setPosition(Vec2(winSize.width * 0.5f - 200, winSize.height - 170));
	pyLayer->addChild(inputbg, 2);

	CEditBoxTool* edbox = CEditBoxTool::Create(Size(400, 80), Scale9Sprite::create("input.png"));
	edbox->setPosition(Vec2(winSize.width * 0.5f - 200, winSize.height - 170));
	edbox->setFont("STXingkai.ttf", 29.0f);
	//edbox->setFontColor(Color3B(0, 0, 0));
	//edbox->setMaxLength(20);
	edbox->setInputMode(EditBox::InputMode::ANY);
	edbox->setDelegate(this);
	pyLayer->addChild(edbox, 3, 101);

	edbox->setPlaceHolder(Global::getInstance()->getString("118"));

	Button* zhaopy = Button::createBtnWithSpriteFrameName("saoyisao-01.png", false);
	zhaopy->setPosition(Vec2(winSize.width * 0.5f - 200, winSize.height - 300));
	zhaopy->setScale(0.6f);
	zhaopy->setOnClickCallback(callfuncO_selector(FindFriend::Saoyisao), this);
	pyLayer->addChild(zhaopy);
	/*
	zhaopy = Button::createBtnWithSpriteFrameName("leidajiahaoyou-01.png", false);
	zhaopy->setPosition(Vec2(360, winSize.height - 410));
	zhaopy->setScale(0.6f);
	zhaopy->setOnClickCallback(callfuncO_selector(FindFriend::Leida), this);
	pyLayer->addChild(zhaopy);

	zhaopy = Button::createBtnWithSpriteFrameName("yaoyiyao-01.png", false);
	zhaopy->setPosition(Vec2(360, winSize.height - 520));
	zhaopy->setScale(0.6f);
	zhaopy->setOnClickCallback(callfuncO_selector(FindFriend::Yaoyiyao), this);
	pyLayer->addChild(zhaopy);
	*/
	user_info info = Global::getInstance()->GetUserInfo();
	std::string headPath;
	char temp[32];
	if (info.icon > 100)
	{
		sprintf(temp, "hero_%d.png", info.icon);
		headPath = temp;
	}
	else{
		sprintf(temp, "headImage_%d.jpg", info.icon);
		headPath = Global::getInstance()->getDataPath(temp);
	}

	char idstr[32] = { 0 };

	sprintf(idstr, "%d", info.roleID);
	ExchangeInfo::CreateQRFImage(idstr, headPath.c_str(), 360);


	std::string path = Global::getInstance()->getDataPath("/qrf/qrf.png");

	Sprite* back = Sprite::create(path.c_str());
	back->setPosition(Vec2(winSize.width * 0.5f + 280, winSize.height * 0.5f));
	//back->setScale(0.6f);
	pyLayer->addChild(back);

	CCLabelTTF* useName = CCLabelTTF::create(Global::getInstance()->getString("119"), "STXingkai.ttf", 28);
	useName->setPosition(Vec2(winSize.width * 0.5f + 280, winSize.height * 0.5f - 230));
	useName->setColor(Color3B(0, 0, 0));
	pyLayer->addChild(useName, 2);
}

void FindFriend::resetBtnState()
{
	//((Button*)getChildByTag(TAG_Fujinderen))->setPressIconShow(false);
	((Button*)getChildByTag(TAG_FindFriend))->setPressIconShow(false);

	//removeChildByTag(m_currentTag);
}
void FindFriend::Zhaopengyou(Ref* pSender)
{
	if (TAG_FindFriend == m_currentTag)
		return;

	resetBtnState();
	m_currentTag = TAG_FindFriend;
	Button* shouye = (Button*)pSender;
	shouye->setPressIconShow(true);

	InitZhaoPYUI();
}
void FindFriend::Fujinderen(Ref* pSender)
{
	if (TAG_Fujinderen == m_currentTag)
		return;

	resetBtnState();
	m_currentTag = TAG_Fujinderen;
	Button* shouye = (Button*)pSender;
	shouye->setPressIconShow(true);

	removeChildByTag(TAG_PYLayer, true);
}
void FindFriend::editBoxReturn(cocos2d::extension::EditBox* editBox)
{

}
void FindFriend::Back(Ref* pSender)
{
	getParent()->removeChild(this, true);
}
void FindFriend::Saoyisao(Ref* pSender)
{
	ExchangeInfo::OpenScan();
}
void FindFriend::Leida(Ref* pSender)
{

}
void FindFriend::Yaoyiyao(Ref* pSender)
{

}




SheZhi::SheZhi()
{
	mUserSex = Global::getInstance()->GetUserInfo().sex;
}
SheZhi::~SheZhi()
{

}

bool SheZhi::init()
{
	if (!CPZLayer::init())
		return false;

	LayerColor* layer = LayerColor::create(Color4B(0, 0, 0, 80));
	addChild(layer);

	Sprite* back = Sprite::create("dimianbeijing-01.png");
	back->setPosition(Vec2(winSize.width * 0.5f, winSize.height * 0.5f));
	back->setScale(0.6f);
	addChild(back);

	Button* backBtn = Button::createBtnWithSpriteFrameName("fangjianshezhi-guanbi-01.png", false);
	backBtn->setPosition(Vec2(winSize.width - 90, winSize.height - 70));
	backBtn->setScale(0.6f);
	backBtn->setOnClickCallback(callfuncO_selector(SheZhi::Back), this);
	addChild(backBtn, 1);

	Button* zhaopy = Button::createBtnWithSpriteFrameName("youxishezhi-01.png", false);
	zhaopy->setPosition(Vec2(180, winSize.height - 70));
	zhaopy->setScale(0.6f);
	zhaopy->setOnClickCallback(callfuncO_selector(SheZhi::YouxiShezhi), this);
	zhaopy->setPressIcon("youxishezhi-02.png", false);
	zhaopy->setPressIconShow(true);
	addChild(zhaopy, 1, TAG_FindFriend);

	Button* yonghu = Button::createBtnWithSpriteFrameName("yonghuxinxi-01.png", false);
	yonghu->setPosition(Vec2(360, winSize.height - 70));
	yonghu->setScale(0.6f);
	yonghu->setOnClickCallback(callfuncO_selector(SheZhi::Yonghuxinxi), this);
	yonghu->setPressIcon("yonghuxinxi-02.png", false);
	//zhaopy->setPressIconShow(true);
	addChild(yonghu, 1, TAG_Fujinderen);

	back = Sprite::create("xiantiao-01.png");
	back->setPosition(Vec2(winSize.width * 0.5f, winSize.height - 110));
	back->setScaleX(1.8f);
	addChild(back);



	m_currentTag = TAG_NONE;

	YouxiShezhi(zhaopy);
	return true;
}
void SheZhi::InitShezhiUI()
{
	Layer* pyLayer = Layer::create();
	addChild(pyLayer, 5, TAG_SHEZHI);

	CCLabelTTF* useName = CCLabelTTF::create(Global::getInstance()->getString("120"), "STXingkai.ttf", 35);
	useName->setPosition(Vec2(210, winSize.height - 160));
	useName->setColor(Color3B(0, 0, 0));
	pyLayer->addChild(useName, 2);

	Button* zhaopy = Button::createBtnWithSpriteFrameName("xuanze_btn_1.png", false);
	zhaopy->setPosition(Vec2(350, winSize.height - 160));
	zhaopy->setScale(0.6f);
	zhaopy->setOnClickCallback(callfuncO_selector(SheZhi::Yinyue), this);
	zhaopy->setPressIcon("xuanze_btn_2.png", false);
	pyLayer->addChild(zhaopy, 2);

	if (CCUserDefault::sharedUserDefault()->getIntegerForKey("Syinyue", 0) == 1)
		zhaopy->setPressIconShow(true);

	useName = CCLabelTTF::create(Global::getInstance()->getString("121"), "STXingkai.ttf", 35);
	useName->setPosition(Vec2(460, winSize.height - 160));
	useName->setColor(Color3B(0, 0, 0));
	pyLayer->addChild(useName, 2);

	zhaopy = Button::createBtnWithSpriteFrameName("xuanze_btn_1.png", false);
	zhaopy->setPosition(Vec2(750, winSize.height - 160));
	zhaopy->setScale(0.6f);
	zhaopy->setOnClickCallback(callfuncO_selector(SheZhi::Yinxiao), this);
	zhaopy->setPressIcon("xuanze_btn_2.png", false);
	pyLayer->addChild(zhaopy, 2);

	if (CCUserDefault::sharedUserDefault()->getIntegerForKey("Syinxiao", 0) == 1)
		zhaopy->setPressIconShow(true);

	useName = CCLabelTTF::create(Global::getInstance()->getString("122"), "STXingkai.ttf", 35);
	useName->setPosition(Vec2(860, winSize.height - 160));
	useName->setColor(Color3B(0, 0, 0));
	pyLayer->addChild(useName, 2);

	Sprite* back = Sprite::create("xiantiao-01.png");
	back->setPosition(Vec2(winSize.width * 0.5f, winSize.height - 210));
	back->setScaleX(1.8f);
	pyLayer->addChild(back);

	useName = CCLabelTTF::create(Global::getInstance()->getString("123"), "STXingkai.ttf", 35);
	useName->setPosition(Vec2(210, winSize.height - 260));
	useName->setColor(Color3B(0, 0, 0));
	pyLayer->addChild(useName, 2);

	zhaopy = Button::createBtnWithSpriteFrameName("xuanze_btn_1.png", false);
	zhaopy->setPosition(Vec2(350, winSize.height - 260));
	zhaopy->setScale(0.6f);
	zhaopy->setOnClickCallback(callfuncO_selector(SheZhi::tuqiushezhi), this);
	zhaopy->setPressIcon("xuanze_btn_2.png", false);
	pyLayer->addChild(zhaopy, 2);

	if (CCUserDefault::sharedUserDefault()->getIntegerForKey("Stuqiu", 0) == 1)
		zhaopy->setPressIconShow(true);

	useName = CCLabelTTF::create(Global::getInstance()->getString("124"), "STXingkai.ttf", 35);
	useName->setPosition(Vec2(580, winSize.height - 260));
	useName->setColor(Color3B(0, 0, 0));
	pyLayer->addChild(useName, 2);

	back = Sprite::create("xiantiao-01.png");
	back->setPosition(Vec2(winSize.width * 0.5f, winSize.height - 310));
	back->setScaleX(1.8f);
	pyLayer->addChild(back);
}
void SheZhi::InitZhuceUI()
{
	Layer* pyLayer = Layer::create();
	addChild(pyLayer, 5, TAG_ZHUCE);

	CCLabelTTF* useName = CCLabelTTF::create(Global::getInstance()->getString("125"), "STXingkai.ttf", 35);
	useName->setPosition(Vec2(210, winSize.height - 160));
	useName->setColor(Color3B(0, 0, 0));
	pyLayer->addChild(useName, 2);

	Sprite* inputbg = Sprite::create("yonhu_shuru_bg.png");
	inputbg->setScale(0.6f);
	inputbg->setPosition(Vec2(460, winSize.height - 160));
	pyLayer->addChild(inputbg, 2);

	CEditBoxTool* edbox = CEditBoxTool::Create(Size(330, 80), Scale9Sprite::create("input.png"));
	edbox->setPosition(Vec2(460, winSize.height - 160));
	edbox->setFont("STXingkai.ttf", 29.0f);
	//edbox->setFontColor(Color3B(0, 0, 0));
	edbox->setMaxLength(20);
	edbox->setInputMode(EditBox::InputMode::ANY);
	edbox->setDelegate(this);
	pyLayer->addChild(edbox, 3, 101);

	Sprite* back = Sprite::create("xiantiao-01.png");
	back->setPosition(Vec2(winSize.width * 0.5f, winSize.height - 210));
	back->setScaleX(1.8f);
	addChild(back);

	useName = CCLabelTTF::create(Global::getInstance()->getString("126"), "STXingkai.ttf", 35);
	useName->setPosition(Vec2(210, winSize.height - 260));
	useName->setColor(Color3B(0, 0, 0));
	pyLayer->addChild(useName, 2);

	inputbg = Sprite::create("yonhu_shuru_bg.png");
	inputbg->setScale(0.6f);
	inputbg->setPosition(Vec2(460, winSize.height - 260));
	pyLayer->addChild(inputbg, 2);

	edbox = CEditBoxTool::Create(Size(330, 80), Scale9Sprite::create("input.png"));
	edbox->setPosition(Vec2(460, winSize.height - 260));
	edbox->setFont("STXingkai.ttf", 29.0f);
	//edbox->setFontColor(Color3B(0, 0, 0));
	edbox->setMaxLength(20);
	edbox->setInputMode(EditBox::InputMode::ANY);
	edbox->setDelegate(this);
	pyLayer->addChild(edbox, 3, 102);

	back = Sprite::create("xiantiao-01.png");
	back->setPosition(Vec2(winSize.width * 0.5f, winSize.height - 310));
	back->setScaleX(1.8f);
	addChild(back);

	useName = CCLabelTTF::create(Global::getInstance()->getString("127"), "STXingkai.ttf", 35);
	useName->setPosition(Vec2(210, winSize.height - 360));
	useName->setColor(Color3B(0, 0, 0));
	pyLayer->addChild(useName, 2);

	inputbg = Sprite::create("yonhu_shuru_bg.png");
	inputbg->setScale(0.6f);
	inputbg->setPosition(Vec2(460, winSize.height - 360));
	pyLayer->addChild(inputbg, 2);

	edbox = CEditBoxTool::Create(Size(330, 80), Scale9Sprite::create("input.png"));
	edbox->setPosition(Vec2(460, winSize.height - 360));
	edbox->setFont("STXingkai.ttf", 29.0f);
	//edbox->setFontColor(Color3B(0, 0, 0));
	edbox->setMaxLength(20);
	edbox->setInputMode(EditBox::InputMode::ANY);
	edbox->setDelegate(this);
	pyLayer->addChild(edbox, 3, 103);

	back = Sprite::create("xiantiao-01.png");
	back->setPosition(Vec2(winSize.width * 0.5f, winSize.height - 410));
	back->setScaleX(1.8f);
	addChild(back);

	useName = CCLabelTTF::create(Global::getInstance()->getString("128"), "STXingkai.ttf", 35);
	useName->setPosition(Vec2(210, winSize.height - 460));
	useName->setColor(Color3B(0, 0, 0));
	pyLayer->addChild(useName, 2);

	Button* zhaopy = Button::createBtnWithSpriteFrameName("xuanze_btn_1.png", false);
	zhaopy->setPosition(Vec2(320, winSize.height - 460));
	zhaopy->setScale(0.6f);
	zhaopy->setOnClickCallback(callfuncO_selector(SheZhi::xuanzenan), this);
	zhaopy->setPressIcon("xuanze_btn_2.png", false);
	pyLayer->addChild(zhaopy, 2, TAG_XUANZENAN);

	if (mUserSex == 0) {
		zhaopy->setPressIconShow(true);
	}

	useName = CCLabelTTF::create(Global::getInstance()->getString("129"), "STXingkai.ttf", 35);
	useName->setPosition(Vec2(380, winSize.height - 460));
	useName->setColor(Color3B(0, 0, 0));
	pyLayer->addChild(useName, 2);

	zhaopy = Button::createBtnWithSpriteFrameName("xuanze_btn_1.png", false);
	zhaopy->setPosition(Vec2(510, winSize.height - 460));
	zhaopy->setScale(0.6f);
	zhaopy->setOnClickCallback(callfuncO_selector(SheZhi::xuanzenv), this);
	zhaopy->setPressIcon("xuanze_btn_2.png", false);
	pyLayer->addChild(zhaopy, 2, TAG_XUANZENV);

	if (mUserSex == 1) {
		zhaopy->setPressIconShow(true);
	}

	useName = CCLabelTTF::create(Global::getInstance()->getString("130"), "STXingkai.ttf", 35);
	useName->setPosition(Vec2(560, winSize.height - 460));
	useName->setColor(Color3B(0, 0, 0));
	pyLayer->addChild(useName, 2);

	back = Sprite::create("xiantiao-01.png");
	back->setPosition(Vec2(winSize.width * 0.5f, winSize.height - 510));
	back->setScaleX(1.8f);
	addChild(back);

	zhaopy = Button::createBtnWithSpriteFrameName("baocunziliao-01.png", false);
	zhaopy->setPosition(Vec2(winSize.width*0.5f, winSize.height - 560));
	zhaopy->setScale(0.6f);
	zhaopy->setOnClickCallback(callfuncO_selector(SheZhi::baocunBtn), this);
	//zhaopy->setPressIcon("xuanze_btn_2.png", false);
	pyLayer->addChild(zhaopy);
}

void SheZhi::InitUserShezhi()
{
	Layer* pyLayer = Layer::create();
	addChild(pyLayer, 5, TAG_USERSHEZHI);

	CCLabelTTF* useName = CCLabelTTF::create(Global::getInstance()->getString("125"), "STXingkai.ttf", 35);
	useName->setPosition(Vec2(210, winSize.height - 160));
	useName->setColor(Color3B(0, 0, 0));
	pyLayer->addChild(useName, 2);

	std::string acc = CCUserDefault::sharedUserDefault()->getStringForKey("UserAcc", "");
	int len = (int)acc.length();
	for (int i = 3; i<len; i++) {
		acc.replace(i, 1, "*");
	}

	useName = CCLabelTTF::create(acc.c_str(), "STXingkai.ttf", 35);
	useName->setPosition(Vec2(310, winSize.height - 160));
	useName->setAnchorPoint(Vec2(0.0f, 0.5f));
	useName->setColor(Color3B(0, 0, 0));
	pyLayer->addChild(useName, 2);

	Sprite* back = Sprite::create("xiantiao-01.png");
	back->setPosition(Vec2(winSize.width * 0.5f, winSize.height - 210));
	back->setScaleX(1.8f);
	addChild(back);

	useName = CCLabelTTF::create(Global::getInstance()->getString("131"), "STXingkai.ttf", 35);
	useName->setPosition(Vec2(210, winSize.height - 260));
	useName->setColor(Color3B(0, 0, 0));
	pyLayer->addChild(useName, 2);

	char sexLab[64] = { 0 };
	if (mUserSex == 0) {
		sprintf(sexLab, Global::getInstance()->getString("129"));
	}
	else{
		sprintf(sexLab, Global::getInstance()->getString("130"));
	}
	useName = CCLabelTTF::create(sexLab, "STXingkai.ttf", 35);
	useName->setPosition(Vec2(310, winSize.height - 260));
	useName->setAnchorPoint(Vec2(0.0f, 0.5f));
	useName->setColor(Color3B(0, 0, 0));
	pyLayer->addChild(useName, 2);

	back = Sprite::create("xiantiao-01.png");
	back->setPosition(Vec2(winSize.width * 0.5f, winSize.height - 310));
	back->setScaleX(1.8f);
	addChild(back);

	useName = CCLabelTTF::create(Global::getInstance()->getString("132"), "STXingkai.ttf", 35);
	useName->setPosition(Vec2(210, winSize.height - 360));
	useName->setColor(Color3B(0, 0, 0));
	pyLayer->addChild(useName, 2);

	user_info use = Global::getInstance()->GetUserInfo();
	std::map<int, std::string> hInfo = ExchangeInfo::getProvinces();
	useName = CCLabelTTF::create(hInfo[use.province].c_str(), "STXingkai.ttf", 35);
	useName->setPosition(Vec2(310, winSize.height - 360));
	useName->setAnchorPoint(Vec2(0.0f, 0.5f));
	useName->setColor(Color3B(0, 0, 0));
	pyLayer->addChild(useName, 2);

	back = Sprite::create("xiantiao-01.png");
	back->setPosition(Vec2(winSize.width * 0.5f, winSize.height - 410));
	back->setScaleX(1.8f);
	addChild(back);
}
void SheZhi::editBoxReturn(cocos2d::extension::EditBox* editBox)
{

}
void SheZhi::baocunBtn(Ref* pSender)
{
	CEditBoxTool* input = dynamic_cast<CEditBoxTool*>(getChildByTag(TAG_ZHUCE)->getChildByTag(101));
	std::string nick = input->getText();

	if (nick.length() == 0)
	{
		Global::getInstance()->ShowPromBox(Global::getInstance()->getString("133"));
		return;
	}
	else if (nick.length() < 8){
		Global::getInstance()->ShowPromBox(Global::getInstance()->getString("134"));
		return;
	}
	else if (!ExchangeInfo::regexStr(nick.c_str(), "^[A-Za-z0-9_]+$"))
	{
		Global::getInstance()->ShowPromBox(Global::getInstance()->getString("135"));
		return;
	}
	CEditBoxTool* pass1 = dynamic_cast<CEditBoxTool*>(getChildByTag(TAG_ZHUCE)->getChildByTag(102));
	std::string passw1 = pass1->getText();
	if (passw1.length() == 0)
	{
		Global::getInstance()->ShowPromBox(Global::getInstance()->getString("136"));
		return;
	}
	else if (passw1.length() < 8){
		Global::getInstance()->ShowPromBox(Global::getInstance()->getString("137"));
		return;
	}
	else if (!ExchangeInfo::regexStr(passw1.c_str(), "^[A-Za-z0-9_]+$"))
	{
		Global::getInstance()->ShowPromBox(Global::getInstance()->getString("138"));
		return;
	}
	CEditBoxTool* pass2 = dynamic_cast<CEditBoxTool*>(getChildByTag(TAG_ZHUCE)->getChildByTag(103));
	std::string passw2 = pass2->getText();
	if (passw1 != passw2) {
		Global::getInstance()->ShowPromBox(Global::getInstance()->getString("139"));
		return;
	}

	MainScene* scene = (MainScene*)(getParent()->getParent());
	scene->reqSetName(nick, passw1, mUserSex);
}
void SheZhi::SetNameOK()
{
	CEditBoxTool* input = dynamic_cast<CEditBoxTool*>(getChildByTag(TAG_ZHUCE)->getChildByTag(101));
	std::string nick = input->getText();

	CEditBoxTool* pass1 = dynamic_cast<CEditBoxTool*>(getChildByTag(TAG_ZHUCE)->getChildByTag(102));
	std::string passw1 = pass1->getText();

	CCUserDefault::sharedUserDefault()->setStringForKey("UserAcc", nick.c_str());
	CCUserDefault::sharedUserDefault()->setStringForKey("UserPass", passw1.c_str());

	Global::getInstance()->ShowPromBox(Global::getInstance()->getString("140"));
	removeChildByTag(TAG_ZHUCE, true);
	m_currentTag = TAG_ZHUCE;
	InitUserShezhi();
}
void SheZhi::Back(Ref* pSender)
{
	getParent()->removeChild(this, true);
}
void SheZhi::xuanzenan(Ref* pSender)
{
	Button* btn = (Button*)pSender;
	btn->setPressIconShow(true);
	mUserSex = 0;
	Button* nvBtn = (Button*)getChildByTag(TAG_ZHUCE)->getChildByTag(TAG_XUANZENV);
	nvBtn->setPressIconShow(false);
}
void SheZhi::xuanzenv(Ref* pSender)
{
	Button* btn = (Button*)pSender;
	btn->setPressIconShow(true);
	mUserSex = 1;
	Button* nvBtn = (Button*)getChildByTag(TAG_ZHUCE)->getChildByTag(TAG_XUANZENAN);
	nvBtn->setPressIconShow(false);
}
void SheZhi::resetBtnState()
{
	((Button*)getChildByTag(TAG_Fujinderen))->setPressIconShow(false);
	((Button*)getChildByTag(TAG_FindFriend))->setPressIconShow(false);

	removeChildByTag(m_currentTag);
}
void SheZhi::YouxiShezhi(Ref* pSender)
{
	if (TAG_SHEZHI == m_currentTag)
		return;

	resetBtnState();
	m_currentTag = TAG_SHEZHI;
	Button* shouye = (Button*)pSender;
	shouye->setPressIconShow(true);

	InitShezhiUI();
}
void SheZhi::Yonghuxinxi(Ref* pSender)
{
	if (TAG_ZHUCE == m_currentTag)
		return;

	if (TAG_USERSHEZHI == m_currentTag)
		return;

	resetBtnState();
	Button* shouye = (Button*)pSender;
	shouye->setPressIconShow(true);

	//removeChildByTag(TAG_PYLayer, true);
	std::string acc = CCUserDefault::sharedUserDefault()->getStringForKey("UserAcc", "");
	if (acc.length() <= 0) {
		m_currentTag = TAG_ZHUCE;
		InitZhuceUI();
	}
	else{
		m_currentTag = TAG_USERSHEZHI;
		InitUserShezhi();
	}
}
void SheZhi::Yinyue(Ref* pSender)
{
	Button* btn = (Button*)pSender;
	if (btn->getPressIconShow())
	{
		btn->setPressIconShow(true);
		CCUserDefault::sharedUserDefault()->setIntegerForKey("Syinyue", 1);
		Global::getInstance()->PlayBackMusci("yinyue.mp3");
	}
	else
	{
		btn->setPressIconShow(false);
		CCUserDefault::sharedUserDefault()->setIntegerForKey("Syinyue", 2);
		Global::getInstance()->StopBackMusci();
	}
}
void SheZhi::Yinxiao(Ref* pSender)
{
	Button* btn = (Button*)pSender;
	if (btn->getPressIconShow())
	{
		btn->setPressIconShow(true);
		CCUserDefault::sharedUserDefault()->setIntegerForKey("Syinxiao", 1);
	}
	else
	{
		btn->setPressIconShow(false);
		CCUserDefault::sharedUserDefault()->setIntegerForKey("Syinxiao", 2);
	}
}
void SheZhi::tuanzhanyaoqing(Ref* pSender)
{
	Button* btn = (Button*)pSender;
	if (btn->getPressIconShow())
	{
		btn->setPressIconShow(true);
		CCUserDefault::sharedUserDefault()->setIntegerForKey("Stuanzhanyaoqing", 1);
	}
	else
	{
		btn->setPressIconShow(false);
		CCUserDefault::sharedUserDefault()->setIntegerForKey("Stuanzhanyaoqing", 2);
	}
}
void SheZhi::tuqiushezhi(Ref* pSender)
{
	Button* btn = (Button*)pSender;
	if (btn->getPressIconShow())
	{
		btn->setPressIconShow(true);
		CCUserDefault::sharedUserDefault()->setIntegerForKey("Stuqiu", 1);
	}
	else
	{
		btn->setPressIconShow(false);
		CCUserDefault::sharedUserDefault()->setIntegerForKey("Stuqiu", 2);
	}
}


bool GMScene::init()
{
	if (!Layer::init()) {
		return false;
	}

	LayerColor* layer = LayerColor::create(Color4B(0, 0, 0, 160), winSize.width, 80);
	addChild(layer);

	CEditBoxTool* edbox = CEditBoxTool::Create(Size(winSize.width - 300, 80), Scale9Sprite::create("input.png"));
	edbox->setPosition(Vec2(winSize.width * 0.5f - 100, 40));
	edbox->setFont("STXingkai.ttf", 29.0f);
	edbox->setFontColor(Color3B(255, 255, 255));
	//edbox->setMaxLength(20);
	edbox->setInputMode(EditBox::InputMode::ANY);
	edbox->setDelegate(this);
	addChild(edbox, 3, 101);

	Button* friendBtn = Button::createBtnWithSpriteFrameName("fangjianshezhi-guanbi-01.png", false);
	friendBtn->setPosition(Vec2(winSize.width - 50, 40));
	friendBtn->setScale(0.6f);
	friendBtn->setOnClickCallback(callfuncO_selector(GMScene::Back), this);
	addChild(friendBtn, 2);

	friendBtn = Button::createBtnWithSpriteFrameName("fangjianshezhi-guanbi-01.png", false);
	friendBtn->setPosition(Vec2(winSize.width - 100, 40));
	friendBtn->setScale(0.6f);
	friendBtn->setOnClickCallback(callfuncO_selector(GMScene::Back), this);
	addChild(friendBtn, 2);
	return true;
}
void GMScene::Back(Ref* pSender)
{
	getParent()->removeChild(this, true);
}

void GMScene::ok(Ref* pSender)
{
	CEditBoxTool* edbox = (CEditBoxTool*)getChildByTag(101);
	std::string msg = edbox->getText();

	MainScene* layer = (MainScene*)getParent()->getParent();
	layer->reqGmInfo(msg.c_str());
}
void GMScene::editBoxReturn(cocos2d::extension::EditBox* editBox)
{
	std::string msg = editBox->getText();

	MainScene* layer = (MainScene*)getParent()->getParent();
	layer->reqGmInfo(msg.c_str());
}

///////////////////////
Qiandao::Qiandao()
{
	mInfo.clear();
	//    for (int i=0; i<31; i++) {
	//        QianDao mInf;
	//        if(i == 4)
	//        {
	//            mInf.isQiandao = 1;
	//        }else{
	//            mInf.isQiandao = 0;
	//        }
	//        
	//        if (i == 10) {
	//            mInf.mItemId = 701;
	//        }else if (i == 11) {
	//            mInf.mItemId = 702;
	//        }else
	//            mInf.mItemId = i+1;
	//        
	//        mInfo.push_back(mInf);
	//    }
}
Qiandao::~Qiandao()
{

}

bool Qiandao::init()
{
	if (!CPZLayer::init()) {
		return false;
	}
	LayerColor* layer = LayerColor::create(Color4B(0, 0, 0, 160));
	addChild(layer);

	Sprite* back = Sprite::create("qiandao-bg.png");
	back->setScale(0.6f);
	back->setPosition(Vec2(winSize.width / 2, winSize.height / 2));
	addChild(back);

	back = Sprite::create("qiandao-titl.png");
	back->setScale(0.6f);
	back->setPosition(Vec2(winSize.width / 2, winSize.height / 2 + 225));
	addChild(back);

	Button* backBtn = Button::createBtnWithSpriteFrameName("fangjianshezhi-guanbi-01.png", false);
	backBtn->setPosition(Vec2(winSize.width / 2 + 420, winSize.height / 2 + 230));
	backBtn->setScale(0.6f);
	backBtn->setOnClickCallback(callfuncO_selector(Qiandao::Back), this);
	addChild(backBtn, 1);

	UpdateSignInfos();

	InitInfo();
	return true;
}
void Qiandao::Back(Ref* pSender)
{
	getParent()->removeChild(this, true);
}
void Qiandao::QiandaoClick(Ref* pSender)
{
	MainScene* layer = (MainScene*)getParent()->getParent();
	layer->reqSign();
}
void Qiandao::RushInfo()
{
	//struct cc_timeval now;
	//CCTime::gettimeofdayCocos2d(&now, NULL);
	struct timeval now;
	gettimeofday(&now, NULL);

	struct tm *tme;
	time_t timep = now.tv_sec;
	tme = localtime(&timep);
	int day = tme->tm_mday;

	mInfo[day - 1].isQiandao = true;

	InitInfo();
}
void Qiandao::InitInfo()
{
	removeChildByTag(TAG_INFOLAYER, true);

	Layer* layer = Layer::create();
	addChild(layer, 0, TAG_INFOLAYER);

	//struct cc_timeval now;
	//CCTime::gettimeofdayCocos2d(&now, NULL);
	struct timeval now;
	gettimeofday(&now, NULL);

	struct tm *tme;
	time_t timep = now.tv_sec;
	tme = localtime(&timep);
	int day = tme->tm_mday;

	Button* backBtn = Button::createBtnWithSpriteFrameName("qiandao-bt1.png", false);
	backBtn->setPosition(Vec2(winSize.width / 2, winSize.height / 2 - 210));
	backBtn->setScale(0.6f);
	backBtn->setOnClickCallback(callfuncO_selector(Qiandao::QiandaoClick), this);
	backBtn->setPressIcon("qiandao-bt2.png", false);
	layer->addChild(backBtn, 1, TAG_QIANDAOBTN);

	if (mInfo[day - 1].isQiandao) {
		backBtn->setPressIconShow(true);
		backBtn->setIsCanTouch(false);
	}
	char labStr[128] = { 0 };
	for (int i = 0; i<mInfo.size(); i++) {
		sprintf(labStr, "%d", i + 1);
		CCLabelTTF* leb = CCLabelTTF::create(labStr, "STXingkai.ttf", 30);
		leb->setPosition(Vec2(winSize.width / 2 - 410.5 + i % 7 * 122.5, winSize.height / 2 + 160 - i / 7 * 64.5));
		leb->setColor(Color3B(0, 0, 0));
		layer->addChild(leb);

		if (mInfo[i].mItemId == 701) {
			Sprite* bg = Sprite::create("xiangzi1.png");
			bg->setScale(0.1f);
			bg->setPosition(Vec2(winSize.width / 2 - 122.5 * 3 + i % 7 * 122.5, winSize.height / 2 + 150 - i / 7 * 64.5));
			layer->addChild(bg);
		}
		else if (mInfo[i].mItemId == 901) {
			Sprite* bg = Sprite::create("shop_yuanbao.png");
			bg->setScale(0.4f);
			bg->setPosition(Vec2(winSize.width / 2 - 122.5 * 3 + i % 7 * 122.5, winSize.height / 2 + 150 - i / 7 * 64.5));
			layer->addChild(bg);
		}
		else{
			//item ite = Resource::sharedResource()->getItemForID(mInfo[i].mItemId);

			//Sprite* bg = Sprite::create(ite.itemIcon.c_str());
			//bg->setScale(0.2f);
			//bg->setPosition(Vec2(winSize.width/2-122.5*3+i%7*122.5,winSize.height/2+150-i/7*64.5));
			//layer->addChild(bg);
		}

		if (mInfo[i].isQiandao) {
			Sprite* bg = Sprite::create("qiandao-d2.png");
			bg->setScale(0.6f);
			bg->setPosition(Vec2(winSize.width / 2 - 122.5 * 3 + i % 7 * 122.5, winSize.height / 2 + 150 - i / 7 * 64.5));
			layer->addChild(bg);

			bg = Sprite::create("qiandao-d3.png");
			bg->setScale(0.6f);
			bg->setPosition(Vec2(winSize.width / 2 - 122.5 * 3 + i % 7 * 122.5, winSize.height / 2 + 150 - i / 7 * 64.5));
			layer->addChild(bg);

			if (i == day - 1)
			{
				CCLabelTTF* leb = CCLabelTTF::create(Global::getInstance()->getString("141"), "STXingkai.ttf", 20);
				leb->setPosition(Vec2(winSize.width / 2 - 332.5 + i % 7 * 122.5, winSize.height / 2 + 135 - i / 7 * 64.5));
				leb->setColor(Color3B(0, 0, 0));
				layer->addChild(leb);
			}
		}
		else if (i == day - 1)
		{
			Sprite* bg = Sprite::create("qiandao-d2.png");
			bg->setScale(0.6f);
			bg->setPosition(Vec2(winSize.width / 2 - 122.5 * 3 + i % 7 * 122.5, winSize.height / 2 + 150 - i / 7 * 64.5));
			layer->addChild(bg);

			CCLabelTTF* leb = CCLabelTTF::create(Global::getInstance()->getString("141"), "STXingkai.ttf", 20);
			leb->setPosition(Vec2(winSize.width / 2 - 332.5 + i % 7 * 122.5, winSize.height / 2 + 135 - i / 7 * 64.5));
			leb->setColor(Color3B(0, 0, 0));
			layer->addChild(leb);
		}
		else{
			Sprite* bg = Sprite::create("qiandao-d1.png");
			bg->setScale(0.6f);
			bg->setPosition(Vec2(winSize.width / 2 - 122.5 * 3 + i % 7 * 122.5, winSize.height / 2 + 150 - i / 7 * 64.5));
			layer->addChild(bg);
		}

	}
}

void Qiandao::UpdateSignInfos()
{
	mInfo.clear();

	user_info uInfo = Global::getInstance()->GetUserInfo();

	time_t now;
	time(&now);
	struct tm* nowBlk;
	nowBlk = localtime(&now);
	int nowMon = nowBlk->tm_mon;
	int year = nowBlk->tm_year + 1900;

	int monthDay[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) {
		monthDay[1]++;
	}
	//log("year:%d   mon:%d",year,nowMon);
	std::vector<QianDaoUse> mQinfo = Global::getInstance()->GetQiandao();

	int signTag = uInfo.signTags;

	for (int i = 0; i < monthDay[nowMon]; i++)
	{
		int radix = 1 << i;
		QianDao mInf;
		int index = radix & signTag;
		if (index > 0)
			mInf.isQiandao = 1;
		else
			mInf.isQiandao = 0;
		//radix <<= 1;
		mInf.mItemId = 0;
		for (int j = 0; j<mQinfo.size(); j++) {
			if (mQinfo[j].mDay == i + 1) {
				if (mQinfo[j].mType == 1) {
					mInf.mItemId = 701;
				}
				else{
					mInf.mItemId = 901;
				}

				// log("Qian:%d",mQinfo[j].mType);
			}
		}
		mInfo.push_back(mInf);
	}
}
