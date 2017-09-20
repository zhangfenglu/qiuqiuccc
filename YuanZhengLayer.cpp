#include "YuanZhengLayer.h"
#include "SimpleTools.h"
#include "RotateMenu.h"
#include "Global.h"


bool YuanZhengLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	//initCangKuObj();
	
	
	return true;
}

void YuanZhengLayer::menuItem1Callback(cocos2d::Ref* pSender)
{
	log("btn1");
	star_level = 1;
	showZuDuiBox(1);
}

void YuanZhengLayer::menuItem2Callback(cocos2d::Ref* pSender)
{
	log("btn2");
	star_level = 2;
	showZuDuiBox(2);
}

void YuanZhengLayer::menuItem3Callback(cocos2d::Ref* pSender)
{
	log("btn3");
	star_level = 3;
	showZuDuiBox(3);
}

void YuanZhengLayer::menuItem4Callback(cocos2d::Ref* pSender)
{
	log("btn4");
	star_level = 4;
	showZuDuiBox(4);
}

void YuanZhengLayer::menuItem5Callback(cocos2d::Ref* pSender)
{
	log("btn5");
	star_level = 5;
	showZuDuiBox(5);
}

void YuanZhengLayer::menuItem6Callback(cocos2d::Ref* pSender)
{
	log("btn6");
	star_level = 6;
	showZuDuiBox(6);
}


void YuanZhengLayer::showZuDuiBox(int tag)
{
	std::string titleStr = awards[tag].title;
	titleStr = "TimeYuanZhengLayer\\xiaohao\\title\\" + titleStr + ".png";
	auto title = (cocos2d::ui::ImageView*)seekNodeByName(rootNode, "title");
	title->loadTexture(titleStr.c_str());

	auto xiaohaoTitle = (cocos2d::ui::Text*)seekNodeByName(rootNode, "xiaohaoTitle");
	std::string xiaohaoTitleStr = awards[tag].xiaohaoTitle;
	xiaohaoTitle->setText(xiaohaoTitleStr.c_str());

	std::string zuanshiStr = awards[tag].zuanshi;
	zuanshiStr = "TimeYuanZhengLayer\\xiaohao\\killzuanshi\\" + zuanshiStr;
	auto zuanshi = (cocos2d::ui::ImageView*)seekNodeByName(rootNode, "zuanshi");
	zuanshi->loadTexture(zuanshiStr.c_str());

	std::string xiaohaoNumStr = awards[tag].xiaohaoNum;
	auto xiaohaoNum = (cocos2d::ui::Text*)seekNodeByName(rootNode, "xiaohaoNum");
	xiaohaoNumStr = "X" + xiaohaoNumStr;
	xiaohaoNum->setText(xiaohaoNumStr.c_str());

	std::string allawardsBgStr = awards[tag].allawardsBg;
	std::string allawardsTypeStr = awards[tag].allawardsType;
	std::string allawardsTitleStr = awards[tag].allawardsTitle;
	std::string allawardsStr = awards[tag].allawards;
	std::string allawardsNumStr = awards[tag].allawardsNum;
	std::string allawardsNameStr = awards[tag].allawardsName;
	std::vector<std::string> allawardsBgArrays = Global::getInstance()->split(allawardsBgStr, "|");

	auto scrollView = (cocos2d::ui::ScrollView*)seekNodeByName(rootNode, "ScrollView");
	auto Image_award = (cocos2d::ui::ImageView*)seekNodeByName(rootNode, "Image_award");
	Image_award->setVisible(false);
	//scrollView->removeAllChildren();

	for (int i = 0; i < allawardsBgStr.size(); i++)
	{
		auto cloneImage = (cocos2d::ui::ImageView*)Image_award->clone();
		//cocos2d::ui::ImageView* cloneImage = cocos2d::ui::ImageView::create();
		scrollView->addChild(cloneImage);

		std::string clonePath = "TimeYuanZhengLayer\\xiaohao\\reward\\" + allawardsBgStr.at(i);
		cloneImage->loadTexture(clonePath.c_str());
		cloneImage->setPosition(ccp(Image_award_poiX + Image_award_width * i, Image_award_poiY));

		auto allawardsType = (cocos2d::ui::ImageView*)cloneImage->getChildByName("allawardsType");
		std::string allawardsTypeStr1 = "TimeYuanZhengLayer\\xiaohao\\reward\\" + allawardsTypeStr.at(i);
		allawardsType->loadTexture(allawardsTypeStr1.c_str());

		auto allawardsTitle = (cocos2d::ui::Text*)allawardsType->getChildByName("allawardsTitle");
		std::string allawardsTitleStr1 = "" + allawardsTitleStr.at(i);
		if (allawardsTitleStr1 == "null")
		{
			allawardsTitle->setText("");
		}
		else
		{
			allawardsTitle->setText(allawardsTitleStr1.c_str());
		}

		auto allawards = (cocos2d::ui::ImageView*)cloneImage->getChildByName("allawards");
		std::string allawardsStr1 = "TimeYuanZhengLayer\\xiaohao\\reward\\" + allawardsStr.at(i);
		allawards->loadTexture(allawardsStr1.c_str());

		auto allawardsNum = (cocos2d::ui::Text*)cloneImage->getChildByName("allawardsNum");
		std::string allawardsNumStr1 = "" + allawardsNumStr.at(i);
		allawardsNum->setText(allawardsNumStr1.c_str());

		auto allawardsName = (cocos2d::ui::Text*)cloneImage->getChildByName("allawardsNam");
		std::string allawardsNameStr1 = "" + allawardsNameStr.at(i);
		allawardsName->setText(allawardsNameStr1.c_str());


	}
	baomingBox->setVisible(true);
}

void YuanZhengLayer::initZuDuiAwardInfo()
{
	Json* root = ReadJson("jingjichang.json");

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


							Json* title = Json_getItem(jsonChild, "title");
							//CCLog("<<<<<<%s", title->valuestring);
							Json * xiaohaoTitle = Json_getItem(jsonChild, "xiaohaoTitle");
							Json * zuanshi = Json_getItem(jsonChild, "zuanshi");
							Json * xiaohaoNum = Json_getItem(jsonChild, "xiaohaoNum");

							Json* allawardsBg = Json_getItem(jsonChild, "allawardsBg");
							Json* allawards = Json_getItem(jsonChild, "allawards");
							Json* allawardsType = Json_getItem(jsonChild, "allawardsType");
							Json* allawardsTitle = Json_getItem(jsonChild, "allawardsTitle");
							Json* allawardsNum = Json_getItem(jsonChild, "allawardsNum");
							Json* allawardsName = Json_getItem(jsonChild, "allawardsName");
							AwardInfo info;
							info.title = title->valueString;
							info.xiaohaoTitle = xiaohaoTitle->valueString;
							info.zuanshi = zuanshi->valueString;
							info.xiaohaoNum = xiaohaoNum->valueString;

							info.allawardsBg = allawardsBg->valueString;
							info.allawards = allawards->valueString;
							info.allawardsType = allawardsType->valueString;
							info.allawardsTitle = allawardsTitle->valueString;
							info.allawardsNum = allawardsNum->valueString;
							info.allawardsName = allawardsName->valueString;
							awards[i] = info;
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

	for (int i = 0; i < sizeof(awards) / sizeof(awards[0]); i++)
	{
		std::string title = awards[i].title;
		log("<<<<<<%s", title.c_str());
	}
}

void YuanZhengLayer::initCangKuObj()
{
	account_info info = Global::getInstance()->GetAccountInfo();
	std::string data = "id=" + info.playerid;

	std::string url = "http://47.93.50.101:8080/QQWar/expedition/exinfo";
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
		Json* diamonds = Json_getItem(root, "diamonds");
		Json* onestar = Json_getItem(root, "onestar");
		Json* twostar = Json_getItem(root, "twostar");
		Json* threestar = Json_getItem(root, "threestar");
		Json* fourstar = Json_getItem(root, "fourstar");
		Json* fivestar = Json_getItem(root, "fivestar");
		Json* sixstar = Json_getItem(root, "sixstar");

		timeyuanzheng_cangku_info cangku_info;
		if (twostar->valueInt != NULL)
		{
			cangku_info.juan2 = twostar->valueInt;
		}
		else
		{
			cangku_info.juan2 = 0;
		}

		if (threestar->valueInt != NULL)
		{
			cangku_info.juan3 = threestar->valueInt;
		}
		else
		{
			cangku_info.juan3 = 0;
		}

		if (fourstar->valueInt != NULL)
		{
			cangku_info.juan4 = fourstar->valueInt;
		}
		else
		{
			cangku_info.juan4 = 0;
		}

		if (fivestar->valueInt != NULL)
		{
			cangku_info.juan5 = fivestar->valueInt;
		}
		else
		{
			cangku_info.juan5 = 0;
		}

		if (sixstar->valueInt != NULL)
		{
			cangku_info.juan6 = sixstar->valueInt;
		}
		else
		{
			cangku_info.juan6 = 0;
		}
		
		if (diamonds->valueInt != NULL)
		{
			cangku_info.diamonds = diamonds->valueInt;
		}
		else
		{
			cangku_info.diamonds = 0;
		}
		Global::getInstance()->SetCangKuObj(cangku_info);
		//initUI();
	}, "getCangKu");
}

void YuanZhengLayer::initUI()
{
	star_level = 1;

	rootNode = CSLoader::createNode("YuanZhengLayer1.csb");

	addChild(rootNode);
	cocos2d::ui::Layout* rongqi = (cocos2d::ui::Layout*)seekNodeByName(rootNode, "Panel_xuanzhuan");
	Size visibleSize = rongqi->getContentSize();

	baomingBox = (cocos2d::ui::Layout*)seekNodeByName(rootNode, "zuduiBox");


	
	
	/*auto btn_bao1 = (cocos2d::ui::Button*)seekNodeByName(baomingBox, "btn_baoming1");
	btn_bao1->addTouchEventListener(CC_CALLBACK_0(YuanZhengLayer::baoming1Click, this));
	auto btn_bao2 = (cocos2d::ui::Button*)seekNodeByName(baomingBox, "btn_baoming2");
	btn_bao2->addTouchEventListener(CC_CALLBACK_0(YuanZhengLayer::baoming2Click, this));
	auto btn_bao3 = (cocos2d::ui::Button*)seekNodeByName(baomingBox, "btn_baoming3");
	btn_bao3->addTouchEventListener(CC_CALLBACK_0(YuanZhengLayer::baoming3Click, this));
	auto btn_bao4 = (cocos2d::ui::Button*)seekNodeByName(baomingBox, "btn_baoming4");
	btn_bao4->addTouchEventListener(CC_CALLBACK_0(YuanZhengLayer::baoming4Click, this));
	*/


	//timeyuanzheng_cangku_info cangKuInfo = Global::getInstance()->GetCangKuObj();

	//auto text_wukuanNum = (cocos2d::ui::Text*)seekNodeByName(rootNode, "text_wukuanNum");
	//std::ostringstream w1;
	//w1 << "X" << cangKuInfo.diamonds;
	//text_wukuanNum->setText(w1.str().c_str());

	//auto juan2 = (cocos2d::ui::ImageView*)seekNodeByName(rootNode, "juan2");
	//auto text_juanNum2 = (cocos2d::ui::Text*)seekNodeByName(juan2, "text_juanNum");
	//std::ostringstream w2;
	//w2 << "X" << cangKuInfo.juan2;
	//text_juanNum2->setText(w2.str().c_str());

	//auto juan3 = (cocos2d::ui::ImageView*)seekNodeByName(rootNode, "juan3");
	//auto text_juanNum3 = (cocos2d::ui::Text*)seekNodeByName(juan3, "text_juanNum");
	//std::ostringstream w3;
	//w3 << "X" << cangKuInfo.juan3;
	//text_juanNum3->setText(w3.str().c_str());

	//auto juan4 = (cocos2d::ui::ImageView*)seekNodeByName(rootNode, "juan4");
	//auto text_juanNum4 = (cocos2d::ui::Text*)seekNodeByName(juan4, "text_juanNum");
	//std::ostringstream w4;
	//w4 << "X" << cangKuInfo.juan4;
	//text_juanNum4->setText(w4.str().c_str());

	//auto juan5 = (cocos2d::ui::ImageView*)seekNodeByName(rootNode, "juan5");
	//auto text_juanNum5 = (cocos2d::ui::Text*)seekNodeByName(juan5, "text_juanNum");
	//std::ostringstream w5;
	//w5 << "X" << cangKuInfo.juan5;
	//text_juanNum5->setText(w5.str().c_str());

	//auto juan6 = (cocos2d::ui::ImageView*)seekNodeByName(rootNode, "juan6");
	//auto text_juanNum6 = (cocos2d::ui::Text*)seekNodeByName(juan6, "text_juanNum");
	//std::ostringstream w6;
	//w6 << "X" << cangKuInfo.juan6;
	//text_juanNum6->setText(w6.str().c_str());

	//auto Image_award = (cocos2d::ui::ImageView*)seekNodeByName(rootNode, "Image_award");
	//auto scrollView = (cocos2d::ui::ScrollView*)seekNodeByName(rootNode, "ScrollView");
	//Image_award_width = Image_award->getSize().width;
	//Image_award_poiX = Image_award->getPositionX();
	////Image_award_poiY = scrollView->getSize().height + Image_award->getSize().height * 2;
	//Image_award_poiY = Image_award->getPositionY();


	//auto btn1 = (cocos2d::ui::Button*)seekNodeByName(rootNode, "btn_huangjin1");
	//auto btn2 = (cocos2d::ui::Button*)seekNodeByName(rootNode, "btn_huangjin2");
	//auto btn3 = (cocos2d::ui::Button*)seekNodeByName(rootNode, "btn_huangjin3");
	//auto btn4 = (cocos2d::ui::Button*)seekNodeByName(rootNode, "btn_huangjin4");
	//auto btn5 = (cocos2d::ui::Button*)seekNodeByName(rootNode, "btn_huangjin5");
	//auto btn6 = (cocos2d::ui::Button*)seekNodeByName(rootNode, "btn_huangjin6");
	//copy1 = (cocos2d::ui::Button*)btn1->clone();
	//copy2 = (cocos2d::ui::Button*)btn2->clone();
	//copy3 = (cocos2d::ui::Button*)btn3->clone();
	//copy4 = (cocos2d::ui::Button*)btn4->clone();
	//copy5 = (cocos2d::ui::Button*)btn5->clone();
	//copy6 = (cocos2d::ui::Button*)btn6->clone();

	//copy1->setVisible(true);
	//copy2->setVisible(true);
	//copy3->setVisible(true);
	//copy4->setVisible(true);
	//copy5->setVisible(true);
	//copy6->setVisible(true);




	//auto item1 = MenuItemImage::create("TimeYuanZhengLayer/mianTime/bao1.png", "TimeYuanZhengLayer/mianTime/bao1.png", CC_CALLBACK_1(YuanZhengLayer::menuItem1Callback, this));
	//auto item2 = MenuItemImage::create("TimeYuanZhengLayer/mianTime/bao2.png", "TimeYuanZhengLayer/mianTime/bao2.png", CC_CALLBACK_1(YuanZhengLayer::menuItem2Callback, this));
	//auto item3 = MenuItemImage::create("TimeYuanZhengLayer/mianTime/bao3.png", "TimeYuanZhengLayer/mianTime/bao3.png", CC_CALLBACK_1(YuanZhengLayer::menuItem3Callback, this));
	//auto item4 = MenuItemImage::create("TimeYuanZhengLayer/mianTime/bao4.png", "TimeYuanZhengLayer/mianTime/bao4.png", CC_CALLBACK_1(YuanZhengLayer::menuItem4Callback, this));
	//auto item5 = MenuItemImage::create("TimeYuanZhengLayer/mianTime/bao5.png", "TimeYuanZhengLayer/mianTime/bao5.png", CC_CALLBACK_1(YuanZhengLayer::menuItem5Callback, this));
	//auto item6 = MenuItemImage::create("TimeYuanZhengLayer/mianTime/bao6.png", "TimeYuanZhengLayer/mianTime/bao6.png", CC_CALLBACK_1(YuanZhengLayer::menuItem6Callback, this));

	//copy1->setAnchorPoint(Vec2::ZERO);
	//copy2->setAnchorPoint(Vec2::ZERO);
	//copy3->setAnchorPoint(Vec2::ZERO);
	//copy4->setAnchorPoint(Vec2::ZERO);
	//copy5->setAnchorPoint(Vec2::ZERO);
	//copy6->setAnchorPoint(Vec2::ZERO);
	//copy1->setPosition(item1->getPosition());
	//copy2->setPosition(item2->getPosition());
	//copy3->setPosition(item3->getPosition());
	//copy4->setPosition(item4->getPosition());
	//copy5->setPosition(item5->getPosition());
	//copy6->setPosition(item6->getPosition());

	//item1->addChild(copy1);
	//item2->addChild(copy2);
	//item3->addChild(copy3);
	//item4->addChild(copy4);
	//item5->addChild(copy5);
	//item6->addChild(copy6);


	//RotateMenu *menu = RotateMenu::create();

	//menu->addMenuItem(item1);
	//menu->addMenuItem(item2);
	//menu->addMenuItem(item3);
	//item3->setName("shao");
	//menu->addMenuItem(item4);

	//menu->addMenuItem(item5);
	//item5->setName("duo");
	//menu->addMenuItem(item6);

	//menu->setPosition(visibleSize / 2);
	//rongqi->addChild(menu, 2);


	//auto btnClose = (cocos2d::ui::Button*)seekNodeByName(rootNode, "btnClose");
	//btnClose->addTouchEventListener([=](Ref*, cocos2d::ui::Widget::TouchEventType type)
	//{
	//	if (type == cocos2d::ui::Widget::TouchEventType::ENDED)
	//	{
	//		this->removeFromParent();

	//	}
	//});

	//auto btnHelp = (cocos2d::ui::Button*)seekNodeByName(rootNode, "btnHelp");
	//btnHelp->addTouchEventListener([=](Ref*, cocos2d::ui::Widget::TouchEventType type)
	//{
	//	if (type == cocos2d::ui::Widget::TouchEventType::ENDED)
	//	{
	//		log("click    btnHelp");

	//	}
	//});

	//initZuDuiAwardInfo();
}

void YuanZhengLayer::baoming1Click()
{
	account_info info = Global::getInstance()->GetAccountInfo();
	std::string aid = "";
	switch (star_level)
	{
	case 1:
		aid = "1200101";
		break;
	case 2:
		aid = "1200102";
		break;
	case 3:
		aid = "1200103";
		break;
	case 4:
		aid = "1200104";
		break;
	case 5:
		aid = "1200105";
		break;
	case 6:
		aid = "1200106";
		break;
	default:
		break;
	}
	std::string data = "id=" + info.playerid + "&aid=" + aid;

	std::string url = "http://47.93.50.101:8080/QQWar/expedition/enroll";
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
		Json * ok = Json_getItem(root, "ok");

		if (result->type == Json_Number /*&& ok->type == Json_True*/)
		{
			if (result->valueInt == 1)
			{
				log("***************************************baoming1 success");
				auto btn_bao1 = (cocos2d::ui::Button*)seekNodeByName(baomingBox, "btn_baoming1");
				btn_bao1->setVisible(false);
				auto btn_yibaoming1 = (cocos2d::ui::Button*)seekNodeByName(baomingBox, "btn_yibaoming1");
				btn_yibaoming1->setVisible(true);
			}
			else
			{
				log("***************************************baoming1 error");
			}
		}
		else
		{
			log("***************************************baoming1 error");
		}



	}, "getBaoMing1");
}

void YuanZhengLayer::baoming2Click()
{
	account_info info = Global::getInstance()->GetAccountInfo();
	std::string aid = "";
	switch (star_level)
	{
	case 1:
		aid = "1800101";
		break;
	case 2:
		aid = "1800102";
		break;
	case 3:
		aid = "1800103";
		break;
	case 4:
		aid = "1800104";
		break;
	case 5:
		aid = "1800105";
		break;
	case 6:
		aid = "1800106";
		break;
	default:
		break;
	}
	std::string data = "id=" + info.playerid + "&aid=" + aid;

	std::string url = "http://47.93.50.101:8080/QQWar/expedition/enroll";
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
		Json * ok = Json_getItem(root, "ok");

		if (result->type == Json_Number && ok->type == Json_True)
		{
			if (result->valueInt == 1)
			{
				log("***************************************baoming2 success");
				auto btn_bao2 = (cocos2d::ui::Button*)seekNodeByName(baomingBox, "btn_baoming2");
				btn_bao2->setVisible(false);
				auto btn_yibaoming2 = (cocos2d::ui::Button*)seekNodeByName(baomingBox, "btn_yibaoming2");
				btn_yibaoming2->setVisible(true);
			}
			else
			{
				log("***************************************baoming2 error");
			}
		}
		else
		{
			log("***************************************baoming2 error");
		}



	}, "getBaoMing2");
}

void YuanZhengLayer::baoming3Click()
{
	account_info info = Global::getInstance()->GetAccountInfo();
	std::string aid = "";
	switch (star_level)
	{
	case 1:
		aid = "2000101";
		break;
	case 2:
		aid = "2000102";
		break;
	case 3:
		aid = "2000103";
		break;
	case 4:
		aid = "2000104";
		break;
	case 5:
		aid = "2000105";
		break;
	case 6:
		aid = "2000106";
		break;
	default:
		break;
	}
	std::string data = "id=" + info.playerid + "&aid=" + aid;

	std::string url = "http://47.93.50.101:8080/QQWar/expedition/enroll";
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
		Json * ok = Json_getItem(root, "ok");

		if (result->type == Json_Number && ok->type == Json_True)
		{
			if (result->valueInt == 1)
			{
				log("***************************************baoming3 success");
				auto btn_bao3 = (cocos2d::ui::Button*)seekNodeByName(baomingBox, "btn_baoming3");
				btn_bao3->setVisible(false);
				auto btn_yibaoming3 = (cocos2d::ui::Button*)seekNodeByName(baomingBox, "btn_yibaoming3");
				btn_yibaoming3->setVisible(true);
			}
			else
			{
				log("***************************************baoming3 error");
			}
		}
		else
		{
			log("***************************************baoming3 error");
		}



	}, "getBaoMing3");
}

void YuanZhengLayer::baoming4Click()
{
	account_info info = Global::getInstance()->GetAccountInfo();
	std::string aid = "";
	switch (star_level)
	{
	case 1:
		aid = "2200101";
		break;
	case 2:
		aid = "2200102";
		break;
	case 3:
		aid = "2200103";
		break;
	case 4:
		aid = "2200104";
		break;
	case 5:
		aid = "2200105";
		break;
	case 6:
		aid = "2200106";
		break;
	default:
		break;
	}
	std::string data = "id=" + info.playerid + "&aid=" + aid;

	std::string url = "http://47.93.50.101:8080/QQWar/expedition/enroll";
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
		Json * ok = Json_getItem(root, "ok");

		if (result->type == Json_Number && ok->type == Json_True)
		{
			if (result->valueInt == 1)
			{
				log("***************************************baoming4 success");
				auto btn_bao4 = (cocos2d::ui::Button*)seekNodeByName(baomingBox, "btn_baoming4");
				btn_bao4->setVisible(false);
				auto btn_yibaoming4 = (cocos2d::ui::Button*)seekNodeByName(baomingBox, "btn_yibaoming4");
				btn_yibaoming4->setVisible(true);
			}
			else
			{
				log("***************************************baoming4 error");
			}
		}
		else
		{
			log("***************************************baoming4 error");
		}



	}, "getBaoMing4");
}

