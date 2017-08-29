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
//#include "DaTingLayer.h"

bool LoginLayer::init()
{
	if (!Layer::init())
		return false;

	//initUI();
	initUI1();


	return true;
}

void LoginLayer::initUI1()
{
	auto rootNode = CSLoader::createNode("DaTingLayer.csb");
	addChild(rootNode);

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
	Button* liveBtn = Button::createBtnWithSpriteFrameName("live_mode.png", false);
	liveBtn->setPosition(Vec2(winSize.width * 0.5f + 320, winSize.height * 0.5f - 120));
	liveBtn->setScale(0.45f);
	liveBtn->setOnClickCallback(callfuncO_selector(LoginLayer::LiveClick), this);
	addChild(liveBtn, 2);
	liveBtn->setVisible(false);

	//个人中心
	Button* personBtn = Button::createBtnWithSpriteFrameName("personcenter.png", false);
	personBtn->setPosition(Vec2(270, 60));
	personBtn->setScale(0.55f);
	personBtn->setOnClickCallback(callfuncO_selector(LoginLayer::PersonCenter), this);
	addChild(personBtn, 2);
	personBtn->setVisible(false);


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
	schedule(schedule_selector(LoginLayer::delayEnter), 0.1f);
}

void LoginLayer::setNetKey(int key)
{
	CEditBoxTool* input = dynamic_cast<CEditBoxTool*>(getChildByTag(101));
	std::string nick = input->getText();
	if (nick == "" || nick.size() == 0)
		return;

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
	user_info user = Global::getInstance()->GetUserInfo();
	Global::getInstance()->SetplayerInfo(user);

	MainScene* main = dynamic_cast<MainScene*>(getParent());
	main->CheckLayer(MainScene::TAG_LAYER_USERINFO);
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
	MainScene* main = dynamic_cast<MainScene*>(getParent());
	main->reqShopList();
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
	SheZhi* layer = SheZhi::create();
	addChild(layer, 10, 131);
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
}

void LoginLayer::ShengYiClick(Ref* pSender)
{
	log("===================================shengyi");
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
