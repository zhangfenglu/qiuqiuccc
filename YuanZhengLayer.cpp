#include "YuanZhengLayer.h"
#include "SimpleTools.h"



bool YuanZhengLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	initPlayerBaoMingState();
	initCangKuObj();
	//initUI();
	
	return true;
}

void YuanZhengLayer::menuItem1Callback(cocos2d::Ref* pSender)
{
	log("btn1");
	star_level = 1;
	showZuDuiBox(star_level - 1);
}

void YuanZhengLayer::menuItem2Callback(cocos2d::Ref* pSender)
{
	log("btn2");
	star_level = 2;
	showZuDuiBox(star_level - 1);
}

void YuanZhengLayer::menuItem3Callback(cocos2d::Ref* pSender)
{
	log("btn3");
	star_level = 3;
	showZuDuiBox(star_level - 1);
}

void YuanZhengLayer::menuItem4Callback(cocos2d::Ref* pSender)
{
	log("btn4");
	star_level = 4;
	showZuDuiBox(star_level - 1);
}

void YuanZhengLayer::menuItem5Callback(cocos2d::Ref* pSender)
{
	log("btn5");
	star_level = 5;
	showZuDuiBox(star_level - 1);
}

void YuanZhengLayer::menuItem6Callback(cocos2d::Ref* pSender)
{
	log("btn6");
	star_level = 6;
	showZuDuiBox(star_level - 1);
}


void YuanZhengLayer::showZuDuiBox(int tag)
{

	if (baomingInfos.size() > 0)
	{
		
				switch (tag)
				{
				case 0://处于第一个竞技
				{
						   for (int i = 0; i < baomingInfos.size(); i++)
						   {
							   yuanzhengBaoMing_Info baomingStateInfo = baomingInfos.at(i);
							   switch (baomingStateInfo.aid)
							   {
							   case 1200101://第一个按钮
							   {
												auto baomingBox1 = (cocos2d::ui::Layout*)seekNodeByName(rootNode, "zuduiBox");
												auto btn_bao1 = (cocos2d::ui::Button*)seekNodeByName(baomingBox1, "btn_baoming1");
												btn_bao1->setVisible(false);
												auto btn_yibaoming1 = (cocos2d::ui::Button*)seekNodeByName(baomingBox1, "btn_yibaoming1");
												btn_yibaoming1->setVisible(true);
							   }
								   break;
							   case 1800101:
							   {
											   auto baomingBox2 = (cocos2d::ui::Layout*)seekNodeByName(rootNode, "zuduiBox");
											   auto btn_bao2 = (cocos2d::ui::Button*)seekNodeByName(baomingBox2, "btn_baoming2");
											   btn_bao2->setVisible(false);
											   auto btn_yibaoming2 = (cocos2d::ui::Button*)seekNodeByName(baomingBox2, "btn_yibaoming2");
											   btn_yibaoming2->setVisible(true);
							   }
								   break;
							   case 2000101:
							   {
											   auto baomingBox3 = (cocos2d::ui::Layout*)seekNodeByName(rootNode, "zuduiBox");
											   auto btn_bao3 = (cocos2d::ui::Button*)seekNodeByName(baomingBox3, "btn_baoming3");
											   btn_bao3->setVisible(false);
											   auto btn_yibaoming3 = (cocos2d::ui::Button*)seekNodeByName(baomingBox3, "btn_yibaoming3");
											   btn_yibaoming3->setVisible(true);
							   }
								   break;
							   case 2200101:
							   {
											   auto baomingBox4 = (cocos2d::ui::Layout*)seekNodeByName(rootNode, "zuduiBox");
											   auto btn_bao4 = (cocos2d::ui::Button*)seekNodeByName(baomingBox4, "btn_baoming4");
											   btn_bao4->setVisible(false);
											   auto btn_yibaoming4 = (cocos2d::ui::Button*)seekNodeByName(baomingBox4, "btn_yibaoming4");
											   btn_yibaoming4->setVisible(true);
							   }
								   break;
							   default:
								   break;
							   }
						   }
						  
				}
					break;
				case 1://第二个竞技场
				{
						   for (int i = 0; i < baomingInfos.size(); i++)
						   {
							   yuanzhengBaoMing_Info baomingStateInfo = baomingInfos.at(i);
							   switch (baomingStateInfo.aid)
							   {
							   case 1200102://第一个按钮
							   {
												auto baomingBox1 = (cocos2d::ui::Layout*)seekNodeByName(rootNode, "zuduiBox");
												auto btn_bao1 = (cocos2d::ui::Button*)seekNodeByName(baomingBox1, "btn_baoming1");
												btn_bao1->setVisible(false);
												auto btn_yibaoming1 = (cocos2d::ui::Button*)seekNodeByName(baomingBox1, "btn_yibaoming1");
												btn_yibaoming1->setVisible(true);
							   }
								   break;
							   case 1800102:
							   {
											   auto baomingBox2 = (cocos2d::ui::Layout*)seekNodeByName(rootNode, "zuduiBox");
											   auto btn_bao2 = (cocos2d::ui::Button*)seekNodeByName(baomingBox2, "btn_baoming2");
											   btn_bao2->setVisible(false);
											   auto btn_yibaoming2 = (cocos2d::ui::Button*)seekNodeByName(baomingBox2, "btn_yibaoming2");
											   btn_yibaoming2->setVisible(true);
							   }
								   break;
							   case 2000102:
							   {
											   auto baomingBox3 = (cocos2d::ui::Layout*)seekNodeByName(rootNode, "zuduiBox");
											   auto btn_bao3 = (cocos2d::ui::Button*)seekNodeByName(baomingBox3, "btn_baoming3");
											   btn_bao3->setVisible(false);
											   auto btn_yibaoming3 = (cocos2d::ui::Button*)seekNodeByName(baomingBox3, "btn_yibaoming3");
											   btn_yibaoming3->setVisible(true);
							   }
								   break;
							   case 2200102:
							   {
											   auto baomingBox4 = (cocos2d::ui::Layout*)seekNodeByName(rootNode, "zuduiBox");
											   auto btn_bao4 = (cocos2d::ui::Button*)seekNodeByName(baomingBox4, "btn_baoming4");
											   btn_bao4->setVisible(false);
											   auto btn_yibaoming4 = (cocos2d::ui::Button*)seekNodeByName(baomingBox4, "btn_yibaoming4");
											   btn_yibaoming4->setVisible(true);
							   }
								   break;
							   default:
								   break;
							   }
						   }
				}
					break;
				case 2://第三个竞技场
				{
						   for (int i = 0; i < baomingInfos.size(); i++)
						   {
							   yuanzhengBaoMing_Info baomingStateInfo = baomingInfos.at(i);
							   switch (baomingStateInfo.aid)
							   {
							   case 1200103://第一个按钮
							   {
												auto baomingBox1 = (cocos2d::ui::Layout*)seekNodeByName(rootNode, "zuduiBox");
												auto btn_bao1 = (cocos2d::ui::Button*)seekNodeByName(baomingBox1, "btn_baoming1");
												btn_bao1->setVisible(false);
												auto btn_yibaoming1 = (cocos2d::ui::Button*)seekNodeByName(baomingBox1, "btn_yibaoming1");
												btn_yibaoming1->setVisible(true);
							   }
								   break;
							   case 1800103:
							   {
											   auto baomingBox2 = (cocos2d::ui::Layout*)seekNodeByName(rootNode, "zuduiBox");
											   auto btn_bao2 = (cocos2d::ui::Button*)seekNodeByName(baomingBox2, "btn_baoming2");
											   btn_bao2->setVisible(false);
											   auto btn_yibaoming2 = (cocos2d::ui::Button*)seekNodeByName(baomingBox2, "btn_yibaoming2");
											   btn_yibaoming2->setVisible(true);
							   }
								   break;
							   case 2000103:
							   {
											   auto baomingBox3 = (cocos2d::ui::Layout*)seekNodeByName(rootNode, "zuduiBox");
											   auto btn_bao3 = (cocos2d::ui::Button*)seekNodeByName(baomingBox3, "btn_baoming3");
											   btn_bao3->setVisible(false);
											   auto btn_yibaoming3 = (cocos2d::ui::Button*)seekNodeByName(baomingBox3, "btn_yibaoming3");
											   btn_yibaoming3->setVisible(true);
							   }
								   break;
							   case 2200103:
							   {
											   auto baomingBox4 = (cocos2d::ui::Layout*)seekNodeByName(rootNode, "zuduiBox");
											   auto btn_bao4 = (cocos2d::ui::Button*)seekNodeByName(baomingBox4, "btn_baoming4");
											   btn_bao4->setVisible(false);
											   auto btn_yibaoming4 = (cocos2d::ui::Button*)seekNodeByName(baomingBox4, "btn_yibaoming4");
											   btn_yibaoming4->setVisible(true);
							   }
								   break;
							   default:
								   break;
							   }
						   }
						  
				}
					break;
				case 3://第四个竞技场
				{
						   for (int i = 0; i < baomingInfos.size(); i++)
						   {
							   yuanzhengBaoMing_Info baomingStateInfo = baomingInfos.at(i);
							   switch (baomingStateInfo.aid)
							   {
							   case 1200104://第一个按钮
							   {
												auto baomingBox1 = (cocos2d::ui::Layout*)seekNodeByName(rootNode, "zuduiBox");
												auto btn_bao1 = (cocos2d::ui::Button*)seekNodeByName(baomingBox1, "btn_baoming1");
												btn_bao1->setVisible(false);
												auto btn_yibaoming1 = (cocos2d::ui::Button*)seekNodeByName(baomingBox1, "btn_yibaoming1");
												btn_yibaoming1->setVisible(true);
							   }
								   break;
							   case 1800104:
							   {
											   auto baomingBox2 = (cocos2d::ui::Layout*)seekNodeByName(rootNode, "zuduiBox");
											   auto btn_bao2 = (cocos2d::ui::Button*)seekNodeByName(baomingBox2, "btn_baoming2");
											   btn_bao2->setVisible(false);
											   auto btn_yibaoming2 = (cocos2d::ui::Button*)seekNodeByName(baomingBox2, "btn_yibaoming2");
											   btn_yibaoming2->setVisible(true);
							   }
								   break;
							   case 2000104:
							   {
											   auto baomingBox3 = (cocos2d::ui::Layout*)seekNodeByName(rootNode, "zuduiBox");
											   auto btn_bao3 = (cocos2d::ui::Button*)seekNodeByName(baomingBox3, "btn_baoming3");
											   btn_bao3->setVisible(false);
											   auto btn_yibaoming3 = (cocos2d::ui::Button*)seekNodeByName(baomingBox3, "btn_yibaoming3");
											   btn_yibaoming3->setVisible(true);
							   }
								   break;
							   case 2200104:
							   {
											   auto baomingBox4 = (cocos2d::ui::Layout*)seekNodeByName(rootNode, "zuduiBox");
											   auto btn_bao4 = (cocos2d::ui::Button*)seekNodeByName(baomingBox4, "btn_baoming4");
											   btn_bao4->setVisible(false);
											   auto btn_yibaoming4 = (cocos2d::ui::Button*)seekNodeByName(baomingBox4, "btn_yibaoming4");
											   btn_yibaoming4->setVisible(true);
							   }
								   break;
							   default:
								   break;
							   }
						   }
						   
				}
					break;
				case 4://第五个竞技场
				{
						   for (int i = 0; i < baomingInfos.size(); i++)
						   {
							   yuanzhengBaoMing_Info baomingStateInfo = baomingInfos.at(i);
							   switch (baomingStateInfo.aid)
							   {
							   case 1200105://第一个按钮
							   {
												auto baomingBox1 = (cocos2d::ui::Layout*)seekNodeByName(rootNode, "zuduiBox");
												auto btn_bao1 = (cocos2d::ui::Button*)seekNodeByName(baomingBox1, "btn_baoming1");
												btn_bao1->setVisible(false);
												auto btn_yibaoming1 = (cocos2d::ui::Button*)seekNodeByName(baomingBox1, "btn_yibaoming1");
												btn_yibaoming1->setVisible(true);
							   }
								   break;
							   case 1800105:
							   {
											   auto baomingBox2 = (cocos2d::ui::Layout*)seekNodeByName(rootNode, "zuduiBox");
											   auto btn_bao2 = (cocos2d::ui::Button*)seekNodeByName(baomingBox2, "btn_baoming2");
											   btn_bao2->setVisible(false);
											   auto btn_yibaoming2 = (cocos2d::ui::Button*)seekNodeByName(baomingBox2, "btn_yibaoming2");
											   btn_yibaoming2->setVisible(true);
							   }
								   break;
							   case 2000105:
							   {
											   auto baomingBox3 = (cocos2d::ui::Layout*)seekNodeByName(rootNode, "zuduiBox");
											   auto btn_bao3 = (cocos2d::ui::Button*)seekNodeByName(baomingBox3, "btn_baoming3");
											   btn_bao3->setVisible(false);
											   auto btn_yibaoming3 = (cocos2d::ui::Button*)seekNodeByName(baomingBox3, "btn_yibaoming3");
											   btn_yibaoming3->setVisible(true);
							   }
								   break;
							   case 2200105:
							   {
											   auto baomingBox4 = (cocos2d::ui::Layout*)seekNodeByName(rootNode, "zuduiBox");
											   auto btn_bao4 = (cocos2d::ui::Button*)seekNodeByName(baomingBox4, "btn_baoming4");
											   btn_bao4->setVisible(false);
											   auto btn_yibaoming4 = (cocos2d::ui::Button*)seekNodeByName(baomingBox4, "btn_yibaoming4");
											   btn_yibaoming4->setVisible(true);
							   }
								   break;
							   default:
								   break;
							   }
						   }
						  
				}
					break;
				case 5://第六个竞技场
				{
						   for (int i = 0; i < baomingInfos.size(); i++)
						   {
							   yuanzhengBaoMing_Info baomingStateInfo = baomingInfos.at(i);
							   switch (baomingStateInfo.aid)
							   {
							   case 1200106://第一个按钮
							   {
												auto baomingBox1 = (cocos2d::ui::Layout*)seekNodeByName(rootNode, "zuduiBox");
												auto btn_bao1 = (cocos2d::ui::Button*)seekNodeByName(baomingBox1, "btn_baoming1");
												btn_bao1->setVisible(false);
												auto btn_yibaoming1 = (cocos2d::ui::Button*)seekNodeByName(baomingBox1, "btn_yibaoming1");
												btn_yibaoming1->setVisible(true);
							   }
								   break;
							   case 1800106:
							   {
											   auto baomingBox2 = (cocos2d::ui::Layout*)seekNodeByName(rootNode, "zuduiBox");
											   auto btn_bao2 = (cocos2d::ui::Button*)seekNodeByName(baomingBox2, "btn_baoming2");
											   btn_bao2->setVisible(false);
											   auto btn_yibaoming2 = (cocos2d::ui::Button*)seekNodeByName(baomingBox2, "btn_yibaoming2");
											   btn_yibaoming2->setVisible(true);
							   }
								   break;
							   case 2000106:
							   {
											   auto baomingBox3 = (cocos2d::ui::Layout*)seekNodeByName(rootNode, "zuduiBox");
											   auto btn_bao3 = (cocos2d::ui::Button*)seekNodeByName(baomingBox3, "btn_baoming3");
											   btn_bao3->setVisible(false);
											   auto btn_yibaoming3 = (cocos2d::ui::Button*)seekNodeByName(baomingBox3, "btn_yibaoming3");
											   btn_yibaoming3->setVisible(true);
							   }
								   break;
							   case 2200106:
							   {
											   auto baomingBox4 = (cocos2d::ui::Layout*)seekNodeByName(rootNode, "zuduiBox");
											   auto btn_bao4 = (cocos2d::ui::Button*)seekNodeByName(baomingBox4, "btn_baoming4");
											   btn_bao4->setVisible(false);
											   auto btn_yibaoming4 = (cocos2d::ui::Button*)seekNodeByName(baomingBox4, "btn_yibaoming4");
											   btn_yibaoming4->setVisible(true);
							   }
								   break;
							   default:
								   break;
							   }
						   }
						 
				}
					break;
				default:
					break;
				}

			
				
	}

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
	std::vector<std::string> allawardsTypeArrays = Global::getInstance()->split(allawardsTypeStr, "|");
	std::vector<std::string> allawardsTitleArrays = Global::getInstance()->split(allawardsTitleStr, "|");
	std::vector<std::string> allawardsArrays = Global::getInstance()->split(allawardsStr, "|");
	std::vector<std::string> allawardsNumArrays = Global::getInstance()->split(allawardsNumStr, "|");
	std::vector<std::string> allawardsNameArrays = Global::getInstance()->split(allawardsNameStr, "|");

	auto scrollView = (cocos2d::ui::ScrollView*)seekNodeByName(rootNode, "ScrollView");
	auto Image_award = (cocos2d::ui::ImageView*)seekNodeByName(rootNode, "Image_award");
	Image_award->setVisible(false);
	//scrollView->removeAllChildren();

	for (int i = 0; i < allawardsBgArrays.size(); i++)
	{
		auto cloneImage = (cocos2d::ui::ImageView*)Image_award->clone();
		cloneImage->setVisible(true);
		//cocos2d::ui::ImageView* cloneImage = cocos2d::ui::ImageView::create();
		scrollView->addChild(cloneImage);

		std::string clonePath = "TimeYuanZhengLayer\\xiaohao\\reward\\" + allawardsBgArrays.at(i);
		cloneImage->loadTexture(clonePath.c_str());
		cloneImage->setPosition(ccp(Image_award_poiX + Image_award_width * i, Image_award_poiY));

		auto allawardsType = (cocos2d::ui::ImageView*)cloneImage->getChildByName("allawardsType");
		std::string allawardsTypeStr1 = "TimeYuanZhengLayer\\xiaohao\\reward\\" + allawardsTypeArrays.at(i);
		allawardsType->loadTexture(allawardsTypeStr1.c_str());

		auto allawardsTitle = (cocos2d::ui::Text*)allawardsType->getChildByName("allawardsTitle");
		std::string allawardsTitleStr1 = "" + allawardsTitleArrays.at(i);
		if (allawardsTitleStr1 == "null")
		{
			allawardsTitle->setText("");
		}
		else
		{
			allawardsTitle->setText(allawardsTitleStr1.c_str());
		}

		auto allawards = (cocos2d::ui::ImageView*)cloneImage->getChildByName("allawards");
		std::string allawardsStr1 = "TimeYuanZhengLayer\\xiaohao\\reward\\" + allawardsArrays.at(i);
		allawards->loadTexture(allawardsStr1.c_str());

		auto allawardsNum = (cocos2d::ui::Text*)cloneImage->getChildByName("allawardsNum");
		std::string allawardsNumStr1 = "" + allawardsNumArrays.at(i);
		allawardsNum->setText(allawardsNumStr1.c_str());

		auto allawardsName = (cocos2d::ui::Text*)cloneImage->getChildByName("allawardsName");
		std::string allawardsNameStr1 = "" + allawardsNameArrays.at(i);
		allawardsName->setText(allawardsNameStr1.c_str());


	}



	//报名按钮 是否 可点击 是否制灰色 当仓库物品 无法满足消耗时候 制灰色 且不可点击
	timeyuanzheng_cangku_info cangKuInfo = Global::getInstance()->GetCangKuObj();
	//四个按钮
	auto bao1 = (cocos2d::ui::Button*)seekNodeByName(baomingBox, "btn_baoming1");
	auto bao2 = (cocos2d::ui::Button*)seekNodeByName(baomingBox, "btn_baoming2");
	auto bao3 = (cocos2d::ui::Button*)seekNodeByName(baomingBox, "btn_baoming3");
	auto bao4 = (cocos2d::ui::Button*)seekNodeByName(baomingBox, "btn_baoming4");

	auto btn_yibaoming1 = (cocos2d::ui::Button*)seekNodeByName(baomingBox, "btn_yibaoming1");
	auto btn_yibaoming2 = (cocos2d::ui::Button*)seekNodeByName(baomingBox, "btn_yibaoming2");
	auto btn_yibaoming3 = (cocos2d::ui::Button*)seekNodeByName(baomingBox, "btn_yibaoming3");
	auto btn_yibaoming4 = (cocos2d::ui::Button*)seekNodeByName(baomingBox, "btn_yibaoming4");
	switch (tag)
	{
	case 0://1星
	{
			   if (cangKuInfo.diamonds < atoi(awards[tag].xiaohaoNum.c_str()))
			   {
				   if (!btn_yibaoming1->isVisible())
						 bao1->setTouchEnabled(false);
				  // bao1->setColor(Color3B::GRAY);
				   if (!btn_yibaoming2->isVisible())
						 bao2->setTouchEnabled(false);
				  // bao2->setColor(Color3B::GRAY);
				   if (!btn_yibaoming3->isVisible())
						 bao3->setTouchEnabled(false);
				  // bao3->setColor(Color3B::GRAY);
				   if (!btn_yibaoming4->isVisible())
				   bao4->setTouchEnabled(false);
				  // bao4->setColor(Color3B::GRAY);

			   }
			   else
			   {
					 if (!btn_yibaoming1->isVisible())
						 bao1->setTouchEnabled(true);
					 // bao1->setColor(Color3B::WHITE);
					  if (!btn_yibaoming2->isVisible())
						 bao2->setTouchEnabled(true);
					  //bao2->setColor(Color3B::WHITE);
					  if (!btn_yibaoming3->isVisible())
						bao3->setTouchEnabled(true);
					 // bao3->setColor(Color3B::WHITE);
					  if (!btn_yibaoming4->isVisible())
						bao4->setTouchEnabled(true);
					  //bao4->setColor(Color3B::WHITE);
				   
			   }
	}
		break;
	case 1:
	{
			  if (cangKuInfo.juan2 < atoi(awards[tag].xiaohaoNum.c_str()))
			  {
				  if (!btn_yibaoming1->isVisible())
					  bao1->setTouchEnabled(false);
				  // bao1->setColor(Color3B::GRAY);
				  if (!btn_yibaoming2->isVisible())
					  bao2->setTouchEnabled(false);
				  // bao2->setColor(Color3B::GRAY);
				  if (!btn_yibaoming3->isVisible())
					  bao3->setTouchEnabled(false);
				  // bao3->setColor(Color3B::GRAY);
				  if (!btn_yibaoming4->isVisible())
					  bao4->setTouchEnabled(false);
				  // bao4->setColor(Color3B::GRAY);
			  }
			  else
			  {
				  if (!btn_yibaoming1->isVisible())
					  bao1->setTouchEnabled(true);
				  // bao1->setColor(Color3B::WHITE);
				  if (!btn_yibaoming2->isVisible())
					  bao2->setTouchEnabled(true);
				  //bao2->setColor(Color3B::WHITE);
				  if (!btn_yibaoming3->isVisible())
					  bao3->setTouchEnabled(true);
				  // bao3->setColor(Color3B::WHITE);
				  if (!btn_yibaoming4->isVisible())
					  bao4->setTouchEnabled(true);
				  //bao4->setColor(Color3B::WHITE);
			  }
	}
		break;
	case 2:
	{
			  if (cangKuInfo.juan3 < atoi(awards[tag].xiaohaoNum.c_str()))
			  {
				  if (!btn_yibaoming1->isVisible())
					  bao1->setTouchEnabled(false);
				  // bao1->setColor(Color3B::GRAY);
				  if (!btn_yibaoming2->isVisible())
					  bao2->setTouchEnabled(false);
				  // bao2->setColor(Color3B::GRAY);
				  if (!btn_yibaoming3->isVisible())
					  bao3->setTouchEnabled(false);
				  // bao3->setColor(Color3B::GRAY);
				  if (!btn_yibaoming4->isVisible())
					  bao4->setTouchEnabled(false);
				  // bao4->setColor(Color3B::GRAY);
			  }
			  else
			  {
				  if (!btn_yibaoming1->isVisible())
					  bao1->setTouchEnabled(true);
				  // bao1->setColor(Color3B::WHITE);
				  if (!btn_yibaoming2->isVisible())
					  bao2->setTouchEnabled(true);
				  //bao2->setColor(Color3B::WHITE);
				  if (!btn_yibaoming3->isVisible())
					  bao3->setTouchEnabled(true);
				  // bao3->setColor(Color3B::WHITE);
				  if (!btn_yibaoming4->isVisible())
					  bao4->setTouchEnabled(true);
				  //bao4->setColor(Color3B::WHITE);
			  }
	}
		break;
	case 3:
	{
			  if (cangKuInfo.juan4 < atoi(awards[tag].xiaohaoNum.c_str()))
			  {
				  if (!btn_yibaoming1->isVisible())
					  bao1->setTouchEnabled(false);
				  // bao1->setColor(Color3B::GRAY);
				  if (!btn_yibaoming2->isVisible())
					  bao2->setTouchEnabled(false);
				  // bao2->setColor(Color3B::GRAY);
				  if (!btn_yibaoming3->isVisible())
					  bao3->setTouchEnabled(false);
				  // bao3->setColor(Color3B::GRAY);
				  if (!btn_yibaoming4->isVisible())
					  bao4->setTouchEnabled(false);
				  // bao4->setColor(Color3B::GRAY);
			  }
			  else
			  {
				  if (!btn_yibaoming1->isVisible())
					  bao1->setTouchEnabled(true);
				  // bao1->setColor(Color3B::WHITE);
				  if (!btn_yibaoming2->isVisible())
					  bao2->setTouchEnabled(true);
				  //bao2->setColor(Color3B::WHITE);
				  if (!btn_yibaoming3->isVisible())
					  bao3->setTouchEnabled(true);
				  // bao3->setColor(Color3B::WHITE);
				  if (!btn_yibaoming4->isVisible())
					  bao4->setTouchEnabled(true);
				  //bao4->setColor(Color3B::WHITE);
			  }
	}
		break;
	case 4:
	{
			  if (cangKuInfo.juan5 < atoi(awards[tag].xiaohaoNum.c_str()))
			  {
				  if (!btn_yibaoming1->isVisible())
					  bao1->setTouchEnabled(false);
				  // bao1->setColor(Color3B::GRAY);
				  if (!btn_yibaoming2->isVisible())
					  bao2->setTouchEnabled(false);
				  // bao2->setColor(Color3B::GRAY);
				  if (!btn_yibaoming3->isVisible())
					  bao3->setTouchEnabled(false);
				  // bao3->setColor(Color3B::GRAY);
				  if (!btn_yibaoming4->isVisible())
					  bao4->setTouchEnabled(false);
				  // bao4->setColor(Color3B::GRAY);
			  }
			  else
			  {
				  if (!btn_yibaoming1->isVisible())
					  bao1->setTouchEnabled(true);
				  // bao1->setColor(Color3B::WHITE);
				  if (!btn_yibaoming2->isVisible())
					  bao2->setTouchEnabled(true);
				  //bao2->setColor(Color3B::WHITE);
				  if (!btn_yibaoming3->isVisible())
					  bao3->setTouchEnabled(true);
				  // bao3->setColor(Color3B::WHITE);
				  if (!btn_yibaoming4->isVisible())
					  bao4->setTouchEnabled(true);
				  //bao4->setColor(Color3B::WHITE);
			  }
	}
		break;
	case 5:
	{
			  if (cangKuInfo.juan6 < atoi(awards[tag].xiaohaoNum.c_str()))
			  {
				  if (!btn_yibaoming1->isVisible())
					  bao1->setTouchEnabled(false);
				  // bao1->setColor(Color3B::GRAY);
				  if (!btn_yibaoming2->isVisible())
					  bao2->setTouchEnabled(false);
				  // bao2->setColor(Color3B::GRAY);
				  if (!btn_yibaoming3->isVisible())
					  bao3->setTouchEnabled(false);
				  // bao3->setColor(Color3B::GRAY);
				  if (!btn_yibaoming4->isVisible())
					  bao4->setTouchEnabled(false);
				  // bao4->setColor(Color3B::GRAY);
			  }
			  else
			  {
				  if (!btn_yibaoming1->isVisible())
					  bao1->setTouchEnabled(true);
				  // bao1->setColor(Color3B::WHITE);
				  if (!btn_yibaoming2->isVisible())
					  bao2->setTouchEnabled(true);
				  //bao2->setColor(Color3B::WHITE);
				  if (!btn_yibaoming3->isVisible())
					  bao3->setTouchEnabled(true);
				  // bao3->setColor(Color3B::WHITE);
				  if (!btn_yibaoming4->isVisible())
					  bao4->setTouchEnabled(true);
				  //bao4->setColor(Color3B::WHITE);
			  }
	}
		break;

	default:
		break;
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
							Json * zuanshi = Json_getItem(jsonChild, "xiaohaoIcon");
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
		initUI();
	}, "getCangKu");
}

void YuanZhengLayer::initUI()
{
	star_level = 1;
	infos = Global::getInstance()->GetAccountInfo();

	rootNode = CSLoader::createNode("TimeYuanZhengLayer1.csb");

	addChild(rootNode);
	cocos2d::ui::Layout* rongqi = (cocos2d::ui::Layout*)seekNodeByName(rootNode, "Panel_xuanzhuan");
	Size visibleSize = rongqi->getContentSize();

	baomingBox = (cocos2d::ui::Layout*)seekNodeByName(rootNode, "zuduiBox");


	
	
	cocos2d::ui::Button* btn_bao1 = (cocos2d::ui::Button*)seekNodeByName(baomingBox, "btn_baoming1");
	btn_bao1->addTouchEventListener(CC_CALLBACK_0(YuanZhengLayer::baoming1Click, this));
	cocos2d::ui::Button* btn_bao2 = (cocos2d::ui::Button*)seekNodeByName(baomingBox, "btn_baoming2");
	btn_bao2->addTouchEventListener(CC_CALLBACK_0(YuanZhengLayer::baoming2Click, this));
	cocos2d::ui::Button* btn_bao3 = (cocos2d::ui::Button*)seekNodeByName(baomingBox, "btn_baoming3");
	btn_bao3->addTouchEventListener(CC_CALLBACK_0(YuanZhengLayer::baoming3Click, this));
	cocos2d::ui::Button* btn_bao4 = (cocos2d::ui::Button*)seekNodeByName(baomingBox, "btn_baoming4");
	btn_bao4->addTouchEventListener(CC_CALLBACK_0(YuanZhengLayer::baoming4Click, this));



	timeyuanzheng_cangku_info cangKuInfo = Global::getInstance()->GetCangKuObj();

	auto text_wukuanNum = (cocos2d::ui::Text*)seekNodeByName(rootNode, "text_wukuanNum");
	std::ostringstream w1;
	w1 << "X" << cangKuInfo.diamonds;
	text_wukuanNum->setText(w1.str().c_str());

	auto juan2 = (cocos2d::ui::ImageView*)seekNodeByName(rootNode, "juan2");
	auto text_juanNum2 = (cocos2d::ui::Text*)seekNodeByName(juan2, "text_juanNum");
	std::ostringstream w2;
	w2 << "X" << cangKuInfo.juan2;
	text_juanNum2->setText(w2.str().c_str());

	auto juan3 = (cocos2d::ui::ImageView*)seekNodeByName(rootNode, "juan3");
	auto text_juanNum3 = (cocos2d::ui::Text*)seekNodeByName(juan3, "text_juanNum");
	std::ostringstream w3;
	w3 << "X" << cangKuInfo.juan3;
	text_juanNum3->setText(w3.str().c_str());

	auto juan4 = (cocos2d::ui::ImageView*)seekNodeByName(rootNode, "juan4");
	auto text_juanNum4 = (cocos2d::ui::Text*)seekNodeByName(juan4, "text_juanNum");
	std::ostringstream w4;
	w4 << "X" << cangKuInfo.juan4;
	text_juanNum4->setText(w4.str().c_str());

	auto juan5 = (cocos2d::ui::ImageView*)seekNodeByName(rootNode, "juan5");
	auto text_juanNum5 = (cocos2d::ui::Text*)seekNodeByName(juan5, "text_juanNum");
	std::ostringstream w5;
	w5 << "X" << cangKuInfo.juan5;
	text_juanNum5->setText(w5.str().c_str());

	auto juan6 = (cocos2d::ui::ImageView*)seekNodeByName(rootNode, "juan6");
	auto text_juanNum6 = (cocos2d::ui::Text*)seekNodeByName(juan6, "text_juanNum");
	std::ostringstream w6;
	w6 << "X" << cangKuInfo.juan6;
	text_juanNum6->setText(w6.str().c_str());

	auto Image_award = (cocos2d::ui::ImageView*)seekNodeByName(rootNode, "Image_award");
	auto scrollView = (cocos2d::ui::ScrollView*)seekNodeByName(rootNode, "ScrollView");
	Image_award_width = Image_award->getSize().width;
	Image_award_poiX = Image_award->getPositionX();
	//Image_award_poiY = scrollView->getSize().height + Image_award->getSize().height * 2;
	Image_award_poiY = Image_award->getPositionY();


	auto btn1 = (cocos2d::ui::Button*)seekNodeByName(rootNode, "btn_huangjin1");
	auto btn2 = (cocos2d::ui::Button*)seekNodeByName(rootNode, "btn_huangjin2");
	auto btn3 = (cocos2d::ui::Button*)seekNodeByName(rootNode, "btn_huangjin3");
	auto btn4 = (cocos2d::ui::Button*)seekNodeByName(rootNode, "btn_huangjin4");
	auto btn5 = (cocos2d::ui::Button*)seekNodeByName(rootNode, "btn_huangjin5");
	auto btn6 = (cocos2d::ui::Button*)seekNodeByName(rootNode, "btn_huangjin6");
	copy1 = (cocos2d::ui::Button*)btn1->clone();
	copy2 = (cocos2d::ui::Button*)btn2->clone();
	copy3 = (cocos2d::ui::Button*)btn3->clone();
	copy4 = (cocos2d::ui::Button*)btn4->clone();
	copy5 = (cocos2d::ui::Button*)btn5->clone();
	copy6 = (cocos2d::ui::Button*)btn6->clone();

	copy1->setVisible(true);
	copy2->setVisible(true);
	copy3->setVisible(true);
	copy4->setVisible(true);
	copy5->setVisible(true);
	copy6->setVisible(true);




	MenuItemImage* item1 = MenuItemImage::create("TimeYuanZhengLayer/mianTime/bao1.png", "TimeYuanZhengLayer/mianTime/bao1.png", CC_CALLBACK_1(YuanZhengLayer::menuItem1Callback, this));
	MenuItemImage* item2 = MenuItemImage::create("TimeYuanZhengLayer/mianTime/bao2.png", "TimeYuanZhengLayer/mianTime/bao2.png", CC_CALLBACK_1(YuanZhengLayer::menuItem2Callback, this));
	MenuItemImage* item3 = MenuItemImage::create("TimeYuanZhengLayer/mianTime/bao3.png", "TimeYuanZhengLayer/mianTime/bao3.png", CC_CALLBACK_1(YuanZhengLayer::menuItem3Callback, this));
	MenuItemImage* item4 = MenuItemImage::create("TimeYuanZhengLayer/mianTime/bao4.png", "TimeYuanZhengLayer/mianTime/bao4.png", CC_CALLBACK_1(YuanZhengLayer::menuItem4Callback, this));
	MenuItemImage* item5 = MenuItemImage::create("TimeYuanZhengLayer/mianTime/bao5.png", "TimeYuanZhengLayer/mianTime/bao5.png", CC_CALLBACK_1(YuanZhengLayer::menuItem5Callback, this));
	MenuItemImage* item6 = MenuItemImage::create("TimeYuanZhengLayer/mianTime/bao6.png", "TimeYuanZhengLayer/mianTime/bao6.png", CC_CALLBACK_1(YuanZhengLayer::menuItem6Callback, this));

	copy1->setAnchorPoint(Vec2::ZERO);
	copy2->setAnchorPoint(Vec2::ZERO);
	copy3->setAnchorPoint(Vec2::ZERO);
	copy4->setAnchorPoint(Vec2::ZERO);
	copy5->setAnchorPoint(Vec2::ZERO);
	copy6->setAnchorPoint(Vec2::ZERO);
	copy1->setPosition(item1->getPosition());
	copy2->setPosition(item2->getPosition());
	copy3->setPosition(item3->getPosition());
	copy4->setPosition(item4->getPosition());
	copy5->setPosition(item5->getPosition());
	copy6->setPosition(item6->getPosition());

	item1->addChild(copy1);
	item2->addChild(copy2);
	item3->addChild(copy3);
	item4->addChild(copy4);
	item5->addChild(copy5);
	item6->addChild(copy6);


	RotateMenu *menu = RotateMenu::create();

	menu->addMenuItem(item1);
	menu->addMenuItem(item2);
	menu->addMenuItem(item3);
	item3->setName("shao");
	menu->addMenuItem(item4);

	menu->addMenuItem(item5);
	item5->setName("duo");
	menu->addMenuItem(item6);

	menu->setPosition(visibleSize / 2);
	rongqi->addChild(menu, 2);


	auto btnClose = (cocos2d::ui::Button*)seekNodeByName(rootNode, "btnClose");
	btnClose->addTouchEventListener([=](Ref*, cocos2d::ui::Widget::TouchEventType type)
	{
		if (type == cocos2d::ui::Widget::TouchEventType::ENDED)
		{
			this->removeFromParent();

		}
	});

	auto btnHelp = (cocos2d::ui::Button*)seekNodeByName(rootNode, "btnHelp");
	btnHelp->addTouchEventListener([=](Ref*, cocos2d::ui::Widget::TouchEventType type)
	{
		if (type == cocos2d::ui::Widget::TouchEventType::ENDED)
		{
			log("click    btnHelp");

		}
	});

	initZuDuiAwardInfo();
}

void YuanZhengLayer::baoming1Click()
{
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
	std::string data = "id=" + infos.playerid + "&aid=" + aid;

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
				log("***************************************baoming1 success");
				auto baomingBox1 = (cocos2d::ui::Layout*)seekNodeByName(rootNode, "zuduiBox");
				auto btn_bao1 = (cocos2d::ui::Button*)seekNodeByName(baomingBox1, "btn_baoming1");
				btn_bao1->setVisible(false);
				auto btn_yibaoming1 = (cocos2d::ui::Button*)seekNodeByName(baomingBox1, "btn_yibaoming1");
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
	std::string data = "id=" + infos.playerid + "&aid=" + aid;

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
				auto baomingBox1 = (cocos2d::ui::Layout*)seekNodeByName(rootNode, "zuduiBox");
				auto btn_bao2 = (cocos2d::ui::Button*)seekNodeByName(baomingBox1, "btn_baoming2");
				btn_bao2->setVisible(false);
				auto btn_yibaoming2 = (cocos2d::ui::Button*)seekNodeByName(baomingBox1, "btn_yibaoming2");
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
	std::string data = "id=" + infos.playerid + "&aid=" + aid;

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
				auto baomingBox1 = (cocos2d::ui::Layout*)seekNodeByName(rootNode, "zuduiBox");
				auto btn_bao3 = (cocos2d::ui::Button*)seekNodeByName(baomingBox1, "btn_baoming3");
				btn_bao3->setVisible(false);
				auto btn_yibaoming3 = (cocos2d::ui::Button*)seekNodeByName(baomingBox1, "btn_yibaoming3");
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
	std::string data = "id=" + infos.playerid + "&aid=" + aid;

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
				auto baomingBox1 = (cocos2d::ui::Layout*)seekNodeByName(rootNode, "zuduiBox");
				auto btn_bao4 = (cocos2d::ui::Button*)seekNodeByName(baomingBox1, "btn_baoming4");
				btn_bao4->setVisible(false);
				auto btn_yibaoming4 = (cocos2d::ui::Button*)seekNodeByName(baomingBox1, "btn_yibaoming4");
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

void YuanZhengLayer::initPlayerBaoMingState()
{
	account_info info = Global::getInstance()->GetAccountInfo();
	std::string data = "playerid=" + info.playerid;
	std::string url = "http://47.93.50.101:8080/QQWar/expedition/getExpeditionByid";
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
		Json* resultObj = Json_getItem(root, "resultObj");
		Json * ok = Json_getItem(root, "ok");

		if (result->type == Json_Number && ok->type == Json_True)
		{
			if (result->valueInt == 1)
			{
				log("***************************************baomingState success");

				//保存 玩家远征 报名状态
				if (resultObj)
				{
						Json* child = resultObj->child;
						//if (child)
						{

							for (int i = 0; i < resultObj->size; i++)
							{
								//Json* child = resultObj->child;
								//if (child)
								{
									if (child == NULL)
										break;
									uint32_t aid = Json_getItem(child, "aid")->valueInt;
									uint32_t state = Json_getItem(child, "state")->valueInt;
									yuanzhengBaoMing_Info info;
									info.aid = aid;
									info.state = state;
									baomingInfos.push_back(info);
									child = child->next;
								}
								
							}
						}
				}
				
			}
			else
			{
				log("***************************************baomingState error");
			}
		}
		else
		{
			log("***************************************baomingState error");
		}



	}, "getBaoMingState");

}

