//
//  ShopLayer.cpp
//  qiuFight
//
//  Created by 张跃东 on 16/4/10.
//
//

#include "ShopLayer.h"
#include "MainScene.h"
#include "RichLabel.h"

#include "Resources.h"

#include "msg_client.pb.h"
#include "msg_error.pb.h"
#include "GameVoice.h"

#define CHILD_OFFSET_X      20
#define CHILD_OFFSET_Y      50

///////////////////////////////////////////////////////////////////////////
///base
///////////////////////////////////////////////////////////////////

ShopLayerBase::ShopLayerBase()
{
    
}

ShopLayerBase::~ShopLayerBase()
{
    
}

bool ShopLayerBase::init()
{
    if(!Layer::init())
        return false;
    
    initUI();
    
    return true;
}

void ShopLayerBase::initUI()
{
    Sprite* back = Sprite::create("center_back.png");
    back->setPosition(Vec2(winSize.width * 0.5f, winSize.height * 0.5f));
    back->setScale(0.6f);
    addChild(back);
    
    waiguanBtn = Button::createBtnWithSpriteFrameName("biaoti-waiguan-01.png", false);
    waiguanBtn->setPosition(Vec2(70, winSize.height - 50));
    waiguanBtn->setScale(0.6f);
    waiguanBtn->setOnClickCallback(callfuncO_selector(ShopLayerBase::WaiGuanClick), this);
    waiguanBtn->setPressIcon("biaoti-waiguan-02.png", false);
    waiguanBtn->setPressIconShow(true);
    addChild(waiguanBtn, 1);
    
    heroBtn = Button::createBtnWithSpriteFrameName("biaoti-yingxiong-01.png", false);
    heroBtn->setPosition(Vec2(190, winSize.height - 50));
    heroBtn->setScale(0.6f);
    heroBtn->setOnClickCallback(callfuncO_selector(ShopLayerBase::HeroClick), this);
    heroBtn->setPressIcon("biaoti-yingxiong-02.png", false);
    addChild(heroBtn, 1);
    
    jinheBtn = Button::createBtnWithSpriteFrameName("biaoti-jinhe-01.png", false);
    jinheBtn->setPosition(Vec2(310, winSize.height - 50));
    jinheBtn->setScale(0.6f);
    jinheBtn->setOnClickCallback(callfuncO_selector(ShopLayerBase::JinheClick), this);
    jinheBtn->setPressIcon("biaoti-jinhe-02.png", false);
    addChild(jinheBtn, 1);
    
    hdbbBtn = Button::createBtnWithSpriteFrameName("biaoti-huoquyuanbao-01.png", false);
    hdbbBtn->setPosition(Vec2(460, winSize.height - 50));
    hdbbBtn->setScale(0.6f);
    hdbbBtn->setOnClickCallback(callfuncO_selector(ShopLayerBase::HdbsClick), this);
    hdbbBtn->setPressIcon("biaoti-huoquyuanbao-02.png", false);
    addChild(hdbbBtn, 1);
    
    Button* backBtn = Button::createBtnWithSpriteFrameName("rankingback.png", false);
    backBtn->setPosition(Vec2(winSize.width - 110, 40));
    backBtn->setScale(0.6f);
    backBtn->setOnClickCallback(callfuncO_selector(ShopLayerBase::BackClick), this);
    addChild(backBtn, 1);
    
    Sprite* copper = Sprite::create("shop_copper.png");
    copper->setPosition(Vec2(winSize.width - 500, winSize.height - 50));
    copper->setScale(0.6f);
    addChild(copper, 1);
    
    Sprite* copperLb = Sprite::create("biaoti-tongqian-01.png");
    copperLb->setPosition(Vec2(winSize.width - 450, winSize.height - 50));
    copperLb->setScale(0.6f);
    addChild(copperLb, 1);
    
    Sprite* copperLbb = Sprite::create("money_labe_back.png");
    copperLbb->setPosition(Vec2(winSize.width - 360, winSize.height - 50));
    copperLbb->setScale(0.6f);
    addChild(copperLbb, 1);
    
    user_info user = Global::getInstance()->GetUserInfo();
    char temp[64] = {0};
    sprintf(temp, "%d",user.copper);
    CCLabelTTF* colb = CCLabelTTF::create(temp, "STXingkai.ttf", 29);
    colb->setColor(Color3B(255, 255, 255));
    colb->setAnchorPoint(Vec2(0,0));
    colb->setPosition(Vec2(winSize.width - 400, winSize.height - 65));
    addChild(colb, 1,TAG_TONGQIAN_LAB);
    
    Sprite* yuanbao = Sprite::create("shop_yuanbao.png");
    yuanbao->setPosition(Vec2(winSize.width - 250, winSize.height - 50));
    yuanbao->setScale(0.6f);
    addChild(yuanbao, 1);
    
    Sprite* yuanbaoLb = Sprite::create("biaoti-yuanbao-01.png");
    yuanbaoLb->setPosition(Vec2(winSize.width - 200, winSize.height - 50));
    yuanbaoLb->setScale(0.6f);
    addChild(yuanbaoLb, 1);
    
    Sprite* yuanbaoLbb = Sprite::create("money_labe_back.png");
    yuanbaoLbb->setPosition(Vec2(winSize.width - 110, winSize.height - 50));
    yuanbaoLbb->setScale(0.6f);
    addChild(yuanbaoLbb, 1);
    
    sprintf(temp, "%d",user.gold);
    CCLabelTTF* yblb = CCLabelTTF::create(temp, "STXingkai.ttf", 29);
    yblb->setColor(Color3B(255, 255, 255));
    yblb->setAnchorPoint(Vec2(0,0));
    yblb->setPosition(Vec2(winSize.width - 160, winSize.height - 65));
    addChild(yblb, 1,TAG_YUANBAO_LAB);
    
    m_shopTag = TAG_NONE;
    
    WaiGuanClick(waiguanBtn);
}

void ShopLayerBase::RushLab()
{
    user_info user = Global::getInstance()->GetUserInfo();
    char temp[64] = {0};
    sprintf(temp, "%d",user.copper);
    
    CCLabelTTF* lab = (CCLabelTTF*)getChildByTag(TAG_TONGQIAN_LAB);
    lab->setString(temp);
    
    sprintf(temp, "%d",user.gold);
    lab = (CCLabelTTF*)getChildByTag(TAG_YUANBAO_LAB);
    lab->setString(temp);
    
    ShopLayerWaiguan* layer = (ShopLayerWaiguan*)getChildByTag(TAG_WAIGUAN);
    if (layer) {
        layer->rushTabel();
    }
    
    ShopLayerJinhe* jinhe = (ShopLayerJinhe*)getChildByTag(TAG_JINHE);
    if(jinhe)
    {
        jinhe->rushLab();
    }
}
void ShopLayerBase::resetBtnState()
{
    waiguanBtn->setPressIconShow(false);
    heroBtn->setPressIconShow(false);
    jinheBtn->setPressIconShow(false);
    hdbbBtn->setPressIconShow(false);
    
    if(getChildByTag(TAG_WAIGUAN))
    {
        removeChildByTag(TAG_WAIGUAN);
    }
    else if(getChildByTag(TAG_HERO))
    {
        removeChildByTag(TAG_HERO);
    }
    else if(getChildByTag(TAG_JINHE))
    {
        removeChildByTag(TAG_JINHE);
    }
    else if(getChildByTag(TAG_HDBS))
    {
        removeChildByTag(TAG_HDBS);
    }
}

void ShopLayerBase::WaiGuanClick(cocos2d::Ref *pSender)
{
	GameVoice::getInstance()->playClickBtnVoive();
    if(TAG_WAIGUAN == m_shopTag)
        return;
    
    resetBtnState();
    m_shopTag = TAG_WAIGUAN;
    waiguanBtn->setPressIconShow(true);
    
    ShopLayerWaiguan* waiguan = ShopLayerWaiguan::create();
    waiguan->setPosition(Vec2(CHILD_OFFSET_X, CHILD_OFFSET_Y));
    addChild(waiguan, 10, TAG_WAIGUAN);
}

void ShopLayerBase::HeroClick(cocos2d::Ref *pSender)
{
	GameVoice::getInstance()->playClickBtnVoive();
    if(TAG_HERO == m_shopTag)
        return;
    
    resetBtnState();
    m_shopTag = TAG_HERO;
    heroBtn->setPressIconShow(true);
    
    ShopLayerHero* hero = ShopLayerHero::create();
    hero->setPosition(Vec2(CHILD_OFFSET_X, CHILD_OFFSET_Y));
    addChild(hero, 10, TAG_HERO);
}

void ShopLayerBase::JinheClick(cocos2d::Ref *pSender)
{
	GameVoice::getInstance()->playClickBtnVoive();
    if(TAG_JINHE == m_shopTag)
        return;
    
    resetBtnState();
    m_shopTag = TAG_JINHE;
    jinheBtn->setPressIconShow(true);
    
    ShopLayerJinhe* jinhe = ShopLayerJinhe::create();
    jinhe->setPosition(Vec2(CHILD_OFFSET_Y, CHILD_OFFSET_X));
    addChild(jinhe, 10, TAG_JINHE);
}

void ShopLayerBase::HdbsClick(cocos2d::Ref *pSender)
{
	GameVoice::getInstance()->playClickBtnVoive();
    if(TAG_HDBS == m_shopTag)
        return;
    
    resetBtnState();
    m_shopTag = TAG_HDBS;
    hdbbBtn->setPressIconShow(true);
    
    ShopLayerHuoqu* huoqu = ShopLayerHuoqu::create();
    huoqu->setPosition(Vec2(CHILD_OFFSET_X, CHILD_OFFSET_Y));
    addChild(huoqu, 10, TAG_HDBS);
}

void ShopLayerBase::BackClick(cocos2d::Ref *pSender)
{
	GameVoice::getInstance()->playClickBtnVoive();
    MainScene* main = dynamic_cast<MainScene*>(getParent());
    main->BackToLoginLayer(MainScene::TAG_LAYER_SHOP);
}

//////////////////////////////////////////////////////////
///外观
//////////////////////////////////////////////////////////
ShopLayerWaiguan::ShopLayerWaiguan()
{
    guanghuans.clear();
    baozis.clear();
    canyins.clear();
    
    std::vector<shop_item> shopItem = Global::getInstance()->GetShopItems();
    
    for (int i = 0; i<shopItem.size(); i++) {
        shop_item ite = shopItem[i];
        int id = ite.tpltid();
        
        ChildItem info = Resource::sharedResource()->GetShopItem(id);
        
        if (info.m_itemType == 2) {
            guanghuans.push_back(info);
        }
        if (info.m_itemType == 3) {
            baozis.push_back(info);
        }
        if (info.m_itemType == 1) {
            canyins.push_back(info);
        }
    }
}

ShopLayerWaiguan::~ShopLayerWaiguan()
{
    guanghuans.clear();
    baozis.clear();
    canyins.clear();
}

bool ShopLayerWaiguan::init()
{
    if(!Layer::init())
        return false;
    
    childSize = Size(1036, 520);
    
//    LayerColor* color = LayerColor::create(Color4B(255, 0, 0, 100), 1036, 520);
//    color->setPosition(Vec2(0,0));
//    addChild(color,0);
    
    guanhuan = Button::createBtnWithSpriteFrameName("guanghuan-02.png", false);
    guanhuan->setPosition(Vec2(50, childSize.height - 40));
    guanhuan->setScale(0.6f);
    guanhuan->setOnClickCallback(callfuncO_selector(ShopLayerWaiguan::GuangHuanClick), this);
    guanhuan->setPressIcon("guanghuan-01.png", false);
    guanhuan->setPressIconShow(true);
    addChild(guanhuan, 1);
    
    baozi = Button::createBtnWithSpriteFrameName("paozi-02.png", false);
    baozi->setPosition(Vec2(150, childSize.height - 40));
    baozi->setScale(0.6f);
    baozi->setOnClickCallback(callfuncO_selector(ShopLayerWaiguan::BaoziClick), this);
    baozi->setPressIcon("paozi-01.png", false);
    addChild(baozi, 1);
    /*
    canyin = Button::createBtnWithSpriteFrameName("canying-12.png", false);
    canyin->setPosition(Vec2(250, childSize.height - 40));
    canyin->setScale(0.6f);
    canyin->setOnClickCallback(callfuncO_selector(ShopLayerWaiguan::CanyinClick), this);
    canyin->setPressIcon("canying-11.png", false);
    addChild(canyin, 1);
    */
    GuangHuanClick(guanhuan);
    
    tableView = NULL;
    
    return true;
}
void ShopLayerWaiguan::rushTabel()
{
    ((TableView*)getChildByTag(111))->reloadData();
}
Size ShopLayerWaiguan::getTableSize()
{
    return Size(winSize.width - 2*CHILD_OFFSET_X, winSize.height - 2 * CHILD_OFFSET_Y - 40);
}

void ShopLayerWaiguan::tableCellTouched(cocos2d::extension::TableView *table, cocos2d::extension::TableViewCell *cell)
{
    BuyItemLayer* layer = BuyItemLayer::create();
    layer->setPosition(Vec2(-20,-50));
    addChild(layer,2);
    
    ChildItem item ;
    if (m_tag == guanghuan_tag) {
        item= guanghuans[cell->getIdx()];
    }
    
    if (m_tag == baozi_tag) {
        item= baozis[cell->getIdx()];
    }
    
    if (m_tag == canyin_tag) {
        item= canyins[cell->getIdx()];
    }
    
    
    layer->InitItem(item, m_tag);
}

TableViewCell* ShopLayerWaiguan::tableCellAtIndex(cocos2d::extension::TableView *table, ssize_t idex)
{
    TableViewCell* cell = table->dequeueCell();
    if(!cell)
    {
        cell = new TableViewCell();
        cell->autorelease();
        
        Node* cellNode = Node::create();
        cellNode->setPosition(Vec2(3 * CHILD_OFFSET_X, winSize.height * 0.5f - CHILD_OFFSET_Y));
        
//        Sprite* time_di = Sprite::create("time_dikuang.png");
//        time_di->setScale(0.6f);
//        time_di->setPosition(Vec2(CHILD_OFFSET_X, winSize.height * 0.5f - CHILD_OFFSET_Y));
//        cell->addChild(time_di, 1);
        
        createTableViewCell(cellNode, table, idex);
        cellNode->setTag(100);
        cell->addChild(cellNode, 20);
    }
    else
    {
        Node* cellNode = (Node*)cell->getChildByTag(100);
        cellNode->removeAllChildrenWithCleanup(true);
        createTableViewCell(cellNode, table, idex);
    }
    return cell;
}

void ShopLayerWaiguan::createTableViewCell(cocos2d::Node *cell, cocos2d::extension::TableView *table, int idex)
{
    Sprite* time_di = Sprite::create("time_dikuang.png");
    time_di->setScale(0.55f);
    time_di->setPosition(Vec2(80, 140));
    cell->addChild(time_di, 1);

    Sprite* item_di = Sprite::create("item_base.png");
    item_di->setScale(0.55f);
    item_di->setPosition(Vec2(80, -65));
    cell->addChild(item_di, 1);
    

    
    if(m_tag == guanghuan_tag)
    {
        ChildItem item = guanghuans[idex];
        
        Sprite* money_di = Sprite::create("money_back.png");
        money_di->setScale(0.55f);
        money_di->setPosition(Vec2(80, -195));
        cell->addChild(money_di, 1);
        
        user_bag bagIte = Global::getInstance()->GetBagItem(item.m_id);
        user_info user = Global::getInstance()->GetUserInfo();
        std::map<int, int> equip = user.mEquip;
        std::map<int,int>::iterator iter = equip.begin();
        for (; iter!=equip.end(); iter++) {
            if (iter->first == item.m_itemType) {
                break;
            }
        }
        if (iter!=equip.end() && iter->second == item.m_id) {
            CCLabelTTF* sysj = CCLabelTTF::create(Global::getInstance()->getString("56"), "STXingkai.ttf", 29);
            sysj->setColor(Color3B(255, 255, 255));
            sysj->setPosition(Vec2(80, -195));
            cell->addChild(sysj, 1);
            
        }else if(bagIte.count)
        {
            CCLabelTTF* sysj = CCLabelTTF::create(Global::getInstance()->getString("57"), "STXingkai.ttf", 29);
            sysj->setColor(Color3B(255, 255, 255));
            sysj->setPosition(Vec2(80, -195));
            cell->addChild(sysj, 1);
        }else{
        
            if(item.m_costType == 2)
            {
                Sprite* yuanbao = Sprite::create("shop_yuanbao.png");
                yuanbao->setScale(0.55f);
                yuanbao->setPosition(Vec2(110, -195));
                cell->addChild(yuanbao, 2);
            }
            
            if(item.m_costType == 1)
            {
                Sprite* yuanbao = Sprite::create("shop_copper.png");
                yuanbao->setScale(0.55f);
                yuanbao->setPosition(Vec2(110, -195));
                cell->addChild(yuanbao, 2);
            }
            
            CCLabelTTF* money = CCLabelTTF::create(item.m_money.c_str(), "STXingkai.ttf", 29);
            money->setColor(Color3B(255, 255, 255));
            money->setPosition(Vec2(50, -195));
            cell->addChild(money, 2);
        }
        
        char temp[32];
        sprintf(temp, Global::getInstance()->getString("58"), item.m_duration.c_str());
        
        CCLabelTTF* sysj = CCLabelTTF::create(temp, "STXingkai.ttf", 29);
        sysj->setColor(Color3B(0, 0, 0));
        sysj->setPosition(Vec2(80, 140));
        cell->addChild(sysj, 1);
        
        //CCLOG("itebG:%s",item.m_iconBG.c_str());
        Sprite* icon_bg = Sprite::create(item.m_iconBG.c_str());
        icon_bg->setScale(0.76f);
        icon_bg->setPosition(Vec2(80,20));
        cell->addChild(icon_bg, 2);
        
        Sprite* icon = Sprite::create(item.m_icon.c_str());
        icon->setScale(0.6f);
        icon->setPosition(Vec2(80, 20));
        cell->addChild(icon, 2);
        
        CCLabelTTF* name = CCLabelTTF::create(item.m_name.c_str(), "STXingkai.ttf", 43);
        name->setColor(Color3B(0, 0, 0));
        name->setPosition(Vec2(80, -110));
        cell->addChild(name, 2);
        
    }
    else if(m_tag == baozi_tag)
    {
        ChildItem item = baozis[idex];
        
        Sprite* money_di = Sprite::create("money_back.png");
        money_di->setScale(0.55f);
        money_di->setPosition(Vec2(80, -195));
        cell->addChild(money_di, 1);
        
        user_bag bagIte = Global::getInstance()->GetBagItem(item.m_id);
        user_info user = Global::getInstance()->GetUserInfo();
        std::map<int, int> equip = user.mEquip;
        std::map<int,int>::iterator iter = equip.begin();
        for (; iter!=equip.end(); iter++) {
            if (iter->first == item.m_itemType) {
                break;
            }
        }
        if (iter!=equip.end() && iter->second == item.m_id) {
            CCLabelTTF* sysj = CCLabelTTF::create(Global::getInstance()->getString("56"), "STXingkai.ttf", 29);
            sysj->setColor(Color3B(255, 255, 255));
            sysj->setPosition(Vec2(80, -195));
            cell->addChild(sysj, 1);
            
        }else if(bagIte.count)
        {
            CCLabelTTF* sysj = CCLabelTTF::create(Global::getInstance()->getString("57"), "STXingkai.ttf", 29);
            sysj->setColor(Color3B(255, 255, 255));
            sysj->setPosition(Vec2(80, -195));
            cell->addChild(sysj, 1);
        }else{
            
            if(item.m_costType == 2)
            {
                Sprite* yuanbao = Sprite::create("shop_yuanbao.png");
                yuanbao->setScale(0.55f);
                yuanbao->setPosition(Vec2(110, -195));
                cell->addChild(yuanbao, 2);
            }
            
            if(item.m_costType == 1)
            {
                Sprite* yuanbao = Sprite::create("shop_copper.png");
                yuanbao->setScale(0.55f);
                yuanbao->setPosition(Vec2(110, -195));
                cell->addChild(yuanbao, 2);
            }
            
            CCLabelTTF* money = CCLabelTTF::create(item.m_money.c_str(), "STXingkai.ttf", 29);
            money->setColor(Color3B(255, 255, 255));
            money->setPosition(Vec2(50, -195));
            cell->addChild(money, 2);
        }
        
        char temp[32];
        sprintf(temp, Global::getInstance()->getString("58"), item.m_duration.c_str());
        
        CCLabelTTF* sysj = CCLabelTTF::create(temp, "STXingkai.ttf", 29);
        sysj->setColor(Color3B(0, 0, 0));
        sysj->setPosition(Vec2(80, 140));
        cell->addChild(sysj, 1);
        
        Sprite* iconbg = Sprite::create("yushi-bg.png");
        iconbg->setScale(0.3f);
        iconbg->setPosition(Vec2(80, 20));
        cell->addChild(iconbg, 2);
        
        Sprite* icon = Sprite::create(item.m_icon.c_str());
        icon->setScale(0.3f);
        icon->setPosition(Vec2(80, 20));
        cell->addChild(icon, 2);
        
        CCLabelTTF* name = CCLabelTTF::create(item.m_name.c_str(), "STXingkai.ttf", 43);
        name->setColor(Color3B(0, 0, 0));
        name->setPosition(Vec2(80, -110));
        cell->addChild(name, 2);
        
    }
    else if(m_tag == canyin_tag)
    {
        ChildItem item = canyins[idex];
        
        Sprite* money_di = Sprite::create("money_back.png");
        money_di->setScale(0.55f);
        money_di->setPosition(Vec2(80, -195));
        cell->addChild(money_di, 1);
        
        user_bag bagIte = Global::getInstance()->GetBagItem(item.m_id);
        user_info user = Global::getInstance()->GetUserInfo();
        std::map<int, int> equip = user.mEquip;
        std::map<int,int>::iterator iter = equip.begin();
        for (; iter!=equip.end(); iter++) {
            if (iter->first == item.m_itemType) {
                break;
            }
        }
        if (iter!=equip.end() && iter->second == item.m_id) {
            CCLabelTTF* sysj = CCLabelTTF::create(Global::getInstance()->getString("56"), "STXingkai.ttf", 29);
            sysj->setColor(Color3B(255, 255, 255));
            sysj->setPosition(Vec2(80, -195));
            cell->addChild(sysj, 1);
            
        }else if(bagIte.count)
        {
            CCLabelTTF* sysj = CCLabelTTF::create(Global::getInstance()->getString("57"), "STXingkai.ttf", 29);
            sysj->setColor(Color3B(255, 255, 255));
            sysj->setPosition(Vec2(80, -195));
            cell->addChild(sysj, 1);
        }else{
            
            if(item.m_costType == 2)
            {
                Sprite* yuanbao = Sprite::create("shop_yuanbao.png");
                yuanbao->setScale(0.55f);
                yuanbao->setPosition(Vec2(110, -195));
                cell->addChild(yuanbao, 2);
            }
            
            if(item.m_costType == 1)
            {
                Sprite* yuanbao = Sprite::create("shop_copper.png");
                yuanbao->setScale(0.55f);
                yuanbao->setPosition(Vec2(110, -195));
                cell->addChild(yuanbao, 2);
            }
            
            CCLabelTTF* money = CCLabelTTF::create(item.m_money.c_str(), "STXingkai.ttf", 29);
            money->setColor(Color3B(255, 255, 255));
            money->setPosition(Vec2(50, -195));
            cell->addChild(money, 2);
        }
        
        char temp[32];
        sprintf(temp, Global::getInstance()->getString("58"), item.m_duration.c_str());
        
        CCLabelTTF* sysj = CCLabelTTF::create(temp, "STXingkai.ttf", 29);
        sysj->setColor(Color3B(0, 0, 0));
        sysj->setPosition(Vec2(80, 140));
        cell->addChild(sysj, 1);
        
        Sprite* icon = Sprite::create(item.m_icon.c_str());
        icon->setScale(0.6f);
        icon->setPosition(Vec2(80, 20));
        cell->addChild(icon, 2);
        
        CCLabelTTF* name = CCLabelTTF::create(item.m_name.c_str(), "STXingkai.ttf", 43);
        name->setColor(Color3B(0, 0, 0));
        name->setPosition(Vec2(80, -110));
        cell->addChild(name, 2);
        
    }
}

Size ShopLayerWaiguan::cellSizeForTable(cocos2d::extension::TableView *table)
{
    Size tableSize = getTableSize();
    return Size(tableSize.width / 4, tableSize.height);
}

ssize_t ShopLayerWaiguan::numberOfCellsInTableView(cocos2d::extension::TableView *table)
{
    if (m_tag == guanghuan_tag) {
        return (int)guanghuans.size();
    }
    
    if (m_tag == baozi_tag) {
        return (int)baozis.size();
    }
    
    if (m_tag == canyin_tag) {
        return (int)canyins.size();
    }
    
    return 0;
}

void ShopLayerWaiguan::scrollViewDidScroll(cocos2d::extension::ScrollView *view)
{
    
}

void ShopLayerWaiguan::scrollViewDidZoom(cocos2d::extension::ScrollView *view)
{
    
}


void ShopLayerWaiguan::GuangHuanClick(cocos2d::Ref *pSender)
{
	GameVoice::getInstance()->playClickBtnVoive();
    m_tag = guanghuan_tag;
    
    if(getChildByTag(111))
    {
        removeChildByTag(111);
        tableView =NULL;
    }
    
    resetBtnState();
    guanhuan->setPressIconShow(true);
    
    tableView = TableView::create(this, getTableSize());
    //tableView->setTouchPriority(MAIN_TABLEVIEW_ACTIVE);
    tableView->setDirection(ScrollView::Direction::HORIZONTAL);
    //tableView->setPosition(Vec2(winSize.width * 0.5f - CHILD_OFFSET_X, winSize.height * 0.5f - CHILD_OFFSET_Y));
    tableView->setPosition(Vec2(0,0));
    tableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
    tableView->setDelegate(this);
    addChild(tableView, 2, 111);
    tableView->reloadData();
}

void ShopLayerWaiguan::BaoziClick(cocos2d::Ref* pSender)
{
	GameVoice::getInstance()->playClickBtnVoive();
    m_tag = baozi_tag;
    
    if(getChildByTag(111))
    {
        removeChildByTag(111);
        tableView =NULL;
    }
    
    resetBtnState();
    baozi->setPressIconShow(true);
    
    tableView = TableView::create(this, getTableSize());
    //tableView->setTouchPriority(MAIN_TABLEVIEW_ACTIVE);
    tableView->setDirection(ScrollView::Direction::HORIZONTAL);
    //tableView->setPosition(Vec2(winSize.width * 0.5f - CHILD_OFFSET_X, winSize.height * 0.5f - CHILD_OFFSET_Y));
    tableView->setPosition(Vec2(0,0));
    tableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
    tableView->setDelegate(this);
    addChild(tableView, 2, 111);
    tableView->reloadData();
}

void ShopLayerWaiguan::CanyinClick(cocos2d::Ref *pSender)
{
    m_tag = canyin_tag;
    
    if(getChildByTag(111))
    {
        removeChildByTag(111);
        tableView =NULL;
    }
    
    resetBtnState();
    canyin->setPressIconShow(true);
    
    tableView = TableView::create(this, getTableSize());
    //tableView->setTouchPriority(MAIN_TABLEVIEW_ACTIVE);
    tableView->setDirection(ScrollView::Direction::HORIZONTAL);
    //tableView->setPosition(Vec2(winSize.width * 0.5f - CHILD_OFFSET_X, winSize.height * 0.5f - CHILD_OFFSET_Y));
    tableView->setPosition(Vec2(0,0));
    tableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
    tableView->setDelegate(this);
    addChild(tableView, 2, 111);
    tableView->reloadData();
}

void ShopLayerWaiguan::resetBtnState()
{
    guanhuan->setPressIconShow(false);
    baozi->setPressIconShow(false);
    //canyin->setPressIconShow(false);
}
////////////////////////////////////////////////////
///购买界面
////////////////////////////////////////////////////
BuyItemLayer::BuyItemLayer()
{
    isTouchIn = false;
}
BuyItemLayer::~BuyItemLayer()
{
    
}

bool BuyItemLayer::init()
{
    if(!CPZLayer::init())
        return false;
    
    LayerColor* layer = LayerColor::create(Color4B(0, 0, 0, 50));
    addChild(layer);
    
    Sprite* back = Sprite::create("item_base.png");
    back->setPosition(Vec2(winSize.width * 0.5f, winSize.height * 0.5f));
    back->setScale(0.9f);
    addChild(back,0,1);
    
    Sprite* time_di = Sprite::create("time_dikuang.png");
    time_di->setScale(0.85f);
    time_di->setPosition(Vec2(winSize.width * 0.5f, winSize.height * 0.5f+260));
    addChild(time_di, 1);
    
    time_di = Sprite::create("item-buy-bg-1.png");
    time_di->setScale(0.6f);
    time_di->setPosition(Vec2(winSize.width * 0.5f, winSize.height * 0.5f+90));
    addChild(time_di, 1);
    
    Sprite* yuanbao = Sprite::create("shop_yuanbao.png");
    yuanbao->setScale(0.6f);
    yuanbao->setPosition(Vec2(winSize.width * 0.5f+40, winSize.height * 0.5f-130));
    addChild(yuanbao, 2);
    
    return true;
}

void BuyItemLayer::BuyClick(Ref* pSender)
{
	GameVoice::getInstance()->playClickBtnVoive();
    MainScene* main = dynamic_cast<MainScene*>(getParent()->getParent()->getParent());
    main->reqBuyItem(mItem.m_id);
    
    getParent()->removeChild(this, true);
}
void BuyItemLayer::UseClick(Ref* pSender)
{
	GameVoice::getInstance()->playClickBtnVoive();
    MainScene* main = dynamic_cast<MainScene*>(getParent()->getParent()->getParent());
    main->reqUseItem(mItem.m_id);
    
    getParent()->removeChild(this, true);
}
void BuyItemLayer::XiexiaClick(Ref* pSender)
{
	GameVoice::getInstance()->playClickBtnVoive();
    MainScene* main = dynamic_cast<MainScene*>(getParent()->getParent()->getParent());
    main->reqUnequipItem(mItem.m_itemType);
    
    getParent()->removeChild(this, true);
}
void BuyItemLayer::InitItem(ChildItem ite,int itemType)
{
    mItem = ite;
    
    //log("buy:%d",ite.m_id);
    char temp[32];
    sprintf(temp, Global::getInstance()->getString("58"), ite.m_duration.c_str());
    
    CCLabelTTF* sysj = CCLabelTTF::create(temp, "STXingkai.ttf", 35);
    sysj->setColor(Color3B(0, 0, 0));
    sysj->setPosition(Vec2(winSize.width * 0.5f, winSize.height * 0.5f+260));
    addChild(sysj, 1);
    if(itemType == 0)
    {
        Sprite* icon_bg = Sprite::create(ite.m_iconBG.c_str());
        icon_bg->setScale(0.76f);
        icon_bg->setPosition(Vec2(winSize.width * 0.5f, winSize.height * 0.5f+90));
        addChild(icon_bg, 2);
    }
    
    Sprite* icon = Sprite::create(ite.m_icon.c_str());
    icon->setScale(0.6f);
    icon->setPosition(Vec2(winSize.width * 0.5f, winSize.height * 0.5f+90));
    addChild(icon, 2);
    
    if(itemType == 0)
    {
        icon->runAction(
            RepeatForever::create(
            Sequence::create(
            RotateBy::create(0.1f, 5.0f),NULL)));
    }
    
    CCLabelTTF* name = CCLabelTTF::create(ite.m_name.c_str(), "STXingkai.ttf", 43);
    name->setColor(Color3B(0, 0, 0));
    name->setPosition(Vec2(winSize.width * 0.5f, winSize.height * 0.5f-70));
    addChild(name, 2);
    
    CCLabelTTF* money = CCLabelTTF::create(ite.m_money.c_str(), "STXingkai.ttf", 29);
    money->setColor(Color3B(0, 0, 0));
    money->setPosition(Vec2(winSize.width * 0.5f-40, winSize.height * 0.5f-130));
    addChild(money, 2);
    
    user_bag bagIte = Global::getInstance()->GetBagItem(ite.m_id);
    //log("iteCount:%d",bagIte.count);
    
    user_info user = Global::getInstance()->GetUserInfo();
    std::map<int, int> equip = user.mEquip;
    std::map<int,int>::iterator iter = equip.begin();
    for (; iter!=equip.end(); iter++) {
        if (iter->first == ite.m_itemType) {
            break;
        }
    }
    if (iter!=equip.end()) {
        if(iter->second)
        {
            if (iter->second == ite.m_id) {
                Button* guanhuan = Button::createBtnWithSpriteFrameName("xiexia-01.png", false);
                guanhuan->setPosition(Vec2(winSize.width * 0.5f, winSize.height * 0.5f-220));
                guanhuan->setScale(0.6f);
                guanhuan->setOnClickCallback(callfuncO_selector(BuyItemLayer::XiexiaClick), this);
                guanhuan->setPressIcon("xiexia-02.png", false);
                addChild(guanhuan, 1);
            }else if(bagIte.count){
                Button* guanhuan = Button::createBtnWithSpriteFrameName("zhuangbei_01.png", false);
                guanhuan->setPosition(Vec2(winSize.width * 0.5f, winSize.height * 0.5f-220));
                guanhuan->setScale(0.6f);
                guanhuan->setOnClickCallback(callfuncO_selector(BuyItemLayer::UseClick), this);
                guanhuan->setPressIcon("zhuangbei_02.png", false);
                addChild(guanhuan, 1);
            }else{
                Button* guanhuan = Button::createBtnWithSpriteFrameName("duihuan-01.png", false);
                guanhuan->setPosition(Vec2(winSize.width * 0.5f, winSize.height * 0.5f-220));
                guanhuan->setScale(0.6f);
                guanhuan->setOnClickCallback(callfuncO_selector(BuyItemLayer::BuyClick), this);
                guanhuan->setPressIcon("duihuan-02.png", false);
                addChild(guanhuan, 1);
            }
        }else if(bagIte.count){
            Button* guanhuan = Button::createBtnWithSpriteFrameName("zhuangbei_01.png", false);
            guanhuan->setPosition(Vec2(winSize.width * 0.5f, winSize.height * 0.5f-220));
            guanhuan->setScale(0.6f);
            guanhuan->setOnClickCallback(callfuncO_selector(BuyItemLayer::UseClick), this);
            guanhuan->setPressIcon("zhuangbei_02.png", false);
            addChild(guanhuan, 1);
        }else{
            Button* guanhuan = Button::createBtnWithSpriteFrameName("duihuan-01.png", false);
            guanhuan->setPosition(Vec2(winSize.width * 0.5f, winSize.height * 0.5f-220));
            guanhuan->setScale(0.6f);
            guanhuan->setOnClickCallback(callfuncO_selector(BuyItemLayer::BuyClick), this);
            guanhuan->setPressIcon("duihuan-02.png", false);
            addChild(guanhuan, 1);
        }
    }else if(bagIte.count) {
        Button* guanhuan = Button::createBtnWithSpriteFrameName("zhuangbei_01.png", false);
        guanhuan->setPosition(Vec2(winSize.width * 0.5f, winSize.height * 0.5f-220));
        guanhuan->setScale(0.6f);
        guanhuan->setOnClickCallback(callfuncO_selector(BuyItemLayer::UseClick), this);
        guanhuan->setPressIcon("zhuangbei_02.png", false);
        addChild(guanhuan, 1);
    }else{
        Button* guanhuan = Button::createBtnWithSpriteFrameName("duihuan-01.png", false);
        guanhuan->setPosition(Vec2(winSize.width * 0.5f, winSize.height * 0.5f-220));
        guanhuan->setScale(0.6f);
        guanhuan->setOnClickCallback(callfuncO_selector(BuyItemLayer::BuyClick), this);
        guanhuan->setPressIcon("duihuan-02.png", false);
        addChild(guanhuan, 1);
    }
}

bool BuyItemLayer::onTouchBegan(Touch* pTouch,Event* pEvent)
{
    //Touch* pTouch = (Touch*)pTouches->anyObject();
    Node* node = getChildByTag(1);
    Point pt = node->convertToNodeSpace(Director::getInstance()->convertToGL(pTouch->getLocationInView()));
    Rect rt = Rect(0, 0, node->getContentSize().width*0.9f, node->getContentSize().height*0.9f);
    
    isTouchIn = rt.containsPoint(pt);
    //if(isTouchIn)
        //return false;
    //else
        //return true;
    return true;
}
void BuyItemLayer::onTouchEnded(Touch* pTouch,Event* pEvent)
{
    if(isTouchIn)
        return;
    //Touch* pTouch = (Touch*)pTouches->anyObject();
    Node* node = getChildByTag(1);
    Point pt = node->convertToNodeSpace(Director::getInstance()->convertToGL(pTouch->getLocationInView()));
    Rect rt = Rect(0, 0, node->getContentSize().width*0.9f, node->getContentSize().height*0.9f);
    if(rt.containsPoint(pt) == false)
    {
        getParent()->removeChild(this);
    }
}
////////////////////////////////////////////////////
///英雄
////////////////////////////////////////////////////
ShopLayerHero::ShopLayerHero()
{
    
}

ShopLayerHero::~ShopLayerHero()
{
    
}

bool ShopLayerHero::init()
{
    if(!Layer::init())
        return false;
    
    childSize = Size(1036, 520);
    
    //Sprite* hero_di = Sprite::create("yingxiong-01.png");
    //hero_di->setScale(0.6f);
    //hero_di->setPosition(Vec2(childSize.width * 0.5f, childSize.height * 0.5f + 20));
    //addChild(hero_di, 1);
    
    Button* hecheng = Button::createBtnWithSpriteFrameName("hecheng_btn.png", false);
    hecheng->setPosition(Vec2(childSize.width * 0.5f, childSize.height * 0.5f - 250));
    hecheng->setScale(0.6f);
    hecheng->setOnClickCallback(callfuncO_selector(ShopLayerHero::HechengClick), this);
    addChild(hecheng, 1);
    
    hecheng = Button::createBtnWithSpriteFrameName("cailiao-bag-1.png", false);
    hecheng->setPosition(Vec2(childSize.width * 0.5f-450, childSize.height * 0.5f - 220));
    hecheng->setScale(0.6f);
    hecheng->setPressIcon("cailiao-bag-2.png", false);
    hecheng->setOnClickCallback(callfuncO_selector(ShopLayerHero::BagClick), this);
    addChild(hecheng, 1);
    
    /*
    hecheng = Button::createBtnWithSpriteFrameName("wenhao.png", false);
    hecheng->setPosition(Vec2(childSize.width + 10, childSize.height - 50));
    hecheng->setScale(0.6f);
    hecheng->setOnClickCallback(callfuncO_selector(ShopLayerHero::helpClick), this);
    addChild(hecheng, 1);
    
    
    hecheng = Button::createBtnWithSpriteFrameName("yulan-01.png", false);
    hecheng->setPosition(Vec2(childSize.width + 10, childSize.height * 0.5f + 100));
    hecheng->setScale(0.6f);
    hecheng->setOnClickCallback(callfuncO_selector(ShopLayerHero::helpClick), this);
    addChild(hecheng, 1);
    
    CCLabelTTF* name = CCLabelTTF::create("冲上云霄", "STXingkai.ttf", 40);
    name->setColor(Color3B(0, 0, 0));
    name->setPosition(Vec2(childSize.width - 150, childSize.height * 0.5f + 100));
    addChild(name, 1);
    
    Sprite* state_di = Sprite::create("hero_state.png");
    state_di->setScale(0.6f);
    state_di->setPosition(Vec2(childSize.width - 150, childSize.height * 0.5f + 50));
    addChild(state_di, 1);
    
    CCLabelTTF* statelb = CCLabelTTF::create("1级形态", "STXingkai.ttf", 29);
    statelb->setColor(Color3B(0, 0, 0));
    statelb->setPosition(Vec2(childSize.width - 150, childSize.height * 0.5f + 50));
    addChild(statelb, 2);
    
    CCLabelTTF* progresslb = CCLabelTTF::create("收集进度：20%", "STXingkai.ttf", 29);
    progresslb->setColor(Color3B(0, 0, 0));
    progresslb->setPosition(Vec2(childSize.width - 150, childSize.height * 0.5f));
    addChild(progresslb, 1);
    
    CCProgressTimer* progress = CCProgressTimer::create(Sprite::create("jindutiao-01.png"));
    progress->setType(kCCProgressTimerTypeBar);
    progress->setMidpoint(Vec2(0,0));
    progress->setBarChangeRate(Vec2(1, 0));
    progress->setPosition(Vec2(0, 0));
    progress->setAnchorPoint(Vec2(0,0));
    progress->setPercentage(20.0);
    
    Sprite *leftBg = Sprite::create("progress_base.png");
    leftBg->addChild(progress,1);
    leftBg->setScale(0.6f);
    addChild(leftBg);
    leftBg->setPosition(Vec2(childSize.width - 150, winSize.height * 0.5f - 80));
    */
    
    InitShenshou();
    return true;
}
void ShopLayerHero::helpClick(Ref* pSender)
{
    
}
void ShopLayerHero::LookClick(Ref* pSender)
{
    
}
void ShopLayerHero::InitShenshou()
{
    for (int i = 11; i<19; i++) {
        removeChildByTag(i, true);
    }
    int Shenshou = Global::getInstance()->GetUserInfo().heroid;
    int starNum = Global::getInstance()->GetUserInfo().herolevel;
    if(Shenshou == 0)
        Shenshou = 1;
    if (Shenshou)
    {
        char imagName[128] = {0};
        sprintf(imagName, "shenshou-%d-3.png",Shenshou);
        Sprite* image = Sprite::create(imagName);
        if(image)
        {
            //getChildByTag(14)->setVisible(false);
            
            //image->setAnchorPoint(Vec2(0.5f, 0.5f));
            image->setPosition(Vec2(childSize.width * 0.5f, childSize.height * 0.5f));
            addChild(image, 2, 11);
            
            
            image->runAction(
                             RepeatForever::create(
                                                     Sequence::create(
                                                                        RotateBy::create(0.1f, 5.0f),NULL)));
            
            sprintf(imagName, "shenshou-%d-2.png",Shenshou);
            Sprite* texiao = Sprite::create(imagName);
            //texiao->setAnchorPoint(Vec2(0.5f, 0.5f));
            texiao->setPosition(Vec2(childSize.width * 0.5f, childSize.height * 0.5f));
            addChild(texiao, 3, 12);
            
            texiao->runAction(
                              RepeatForever::create(
                                                      Sequence::create(
                                                                         RotateBy::create(0.1f, 5.0f),NULL)));
            
            sprintf(imagName, "shenshou-%d-1.png",Shenshou);
            Sprite* qlong = Sprite::create(imagName);
            //qlong->setAnchorPoint(Vec2(0, 0));
            qlong->setPosition(Vec2(childSize.width * 0.5f, childSize.height * 0.5f));
            addChild(qlong, 4, 13);
        }
    }
    
    int idx = 0;
    
    char starstr[64]  = {0};
    
    if (idx < starNum)
        sprintf(starstr, "hecheng-xx-02.png");
    else
        sprintf(starstr, "hecheng-xx-01.png");
    
    Sprite* back = Sprite::create(starstr);
    back->setPosition(Vec2(childSize.width * 0.5f-80, childSize.height * 0.5f+150));
    //back->setScale(0.6f);
    back->setRotation(-25);
    addChild(back,5,14);
    
    idx++;
    if (idx < starNum)
        sprintf(starstr, "hecheng-xx-02.png");
    else
        sprintf(starstr, "hecheng-xx-01.png");
    
    back = Sprite::create(starstr);
    back->setPosition(Vec2(childSize.width * 0.5f-42, childSize.height * 0.5f+147+20));
    //back->setScale(0.6f);
    back->setRotation(-17);
    addChild(back,5,15);
    
    idx++;
    if (idx < starNum)
        sprintf(starstr, "hecheng-xx-02.png");
    else
        sprintf(starstr, "hecheng-xx-01.png");
    back = Sprite::create(starstr);
    back->setPosition(Vec2(childSize.width * 0.5f, childSize.height * 0.5f+147+28));
    //back->setScale(0.6f);
    //back->setRotation(20);
    addChild(back,5,16);
    
    idx++;
    if (idx < starNum)
        sprintf(starstr, "hecheng-xx-02.png");
    else
        sprintf(starstr, "hecheng-xx-01.png");
    back = Sprite::create(starstr);
    back->setPosition(Vec2(childSize.width * 0.5f+42, childSize.height * 0.5f+147+20));
    //back->setScale(0.6f);
    back->setRotation(17);
    addChild(back,5,17);
    
    idx++;
    if (idx < starNum)
        sprintf(starstr, "hecheng-xx-02.png");
    else
        sprintf(starstr, "hecheng-xx-01.png");
    back = Sprite::create(starstr);
    back->setPosition(Vec2(childSize.width * 0.5f+80, childSize.height * 0.5f+150));
    //back->setScale(0.6f);
    back->setRotation(25);
    addChild(back,5,18);
}
void ShopLayerHero::BagClick(Ref* pSender)
{
	GameVoice::getInstance()->playClickBtnVoive();
    CaiLiaoBag* hecheng = CaiLiaoBag::create();
    hecheng->setPosition(Vec2(-20,-50));
    addChild(hecheng, 100);
}
void ShopLayerHero::HechengClick(cocos2d::Ref *pSender)
{
	GameVoice::getInstance()->playClickBtnVoive();
    HeCheng* hecheng = HeCheng::create();
    hecheng->setPosition(Vec2(-20,-50));
    addChild(hecheng, 15);
}
////////////////////////////////////////////////////////////////
/// 合成
////////////////////////////////////////////////////////////////
HeCheng::HeCheng()
{
    Resource::sharedResource()->GetComposeItem(hInfo);
    itemMax = (int)hInfo.size();
    user_info  user = Global::getInstance()->GetUserInfo();
    starNum = user.herolevel;
    
    for (int i = 0; i<itemMax; i++) {
        
        item ite = Resource::sharedResource()->getItemForID(hInfo[i].id);
        
        hInfo[i].name = ite.itemName;
        hInfo[i].resName = ite.itemIcon;
    }
}
HeCheng::~HeCheng()
{
    
}

bool HeCheng::init()
{
    if(!CPZLayer::init())
        return false;
    
    Sprite* back = Sprite::create("center_back.png");
    back->setPosition(Vec2(winSize.width * 0.5f, winSize.height * 0.5f));
    back->setScale(0.6f);
    addChild(back);
    
    CCLabelTTF* statelb = CCLabelTTF::create(Global::getInstance()->getString("59"), "STXingkai.ttf", 45);
    statelb->setColor(Color3B(0, 0, 0));
    statelb->setPosition(Vec2(winSize.width * 0.5f, winSize.height * 0.5f + 280));
    addChild(statelb, 2);
    
    Button* backBtn = Button::createBtnWithSpriteFrameName("rankingback.png", false);
    backBtn->setPosition(Vec2(winSize.width - 110, 40));
    backBtn->setScale(0.6f);
    backBtn->setOnClickCallback(callfuncO_selector(HeCheng::BackClick), this);
    addChild(backBtn, 1);
    
    back = Sprite::create("shenshoubg.png");
    back->setPosition(Vec2(winSize.width * 0.5f, winSize.height * 0.5f));
    back->setScale(1.3f);
    addChild(back);
    
    Button* hecheng = Button::createBtnWithSpriteFrameName("hecheng_btn.png", false);
    hecheng->setPosition(Vec2(winSize.width * 0.5f, winSize.height * 0.5f - 250));
    hecheng->setScale(0.6f);
    hecheng->setOnClickCallback(callfuncO_selector(HeCheng::HechengClick), this);
    addChild(hecheng, 1);
    
    InitItem();
    return true;
}
void HeCheng::InitItem()
{
    if(itemMax == 2)
    {
        for (int i = 0; i<2; i++) {
            itemInfo info = hInfo[i];
            
            user_bag bagIte = Global::getInstance()->GetBagItem(info.id);
            
            Sprite* back = Sprite::create(info.resName.c_str());
            back->setPosition(Vec2(winSize.width * 0.5f-170 + i*340, winSize.height * 0.5f));
            back->setScale(0.6f);
            addChild(back);
            
            
            char tem[32] = {0};
            sprintf(tem, "%d/%d",bagIte.count,info.mNum);
            CCLabelTTF* statelb = CCLabelTTF::create(tem, "STXingkai.ttf", 20);
            statelb->setColor(Color3B(0, 0, 0));
            statelb->setPosition(Vec2(winSize.width * 0.5f-260 + i*520, winSize.height * 0.5f-40));
            addChild(statelb, 2);
        }
    }else if(itemMax == 3)
    {
        for (int i = 0; i<3; i++) {
            itemInfo info = hInfo[i];
            user_bag bagIte = Global::getInstance()->GetBagItem(info.id);
            
            Sprite* back = Sprite::create(info.resName.c_str());
            back->setPosition(Vec2(winSize.width * 0.5f-150 + i*150, winSize.height * 0.5f-90+i%2*260));
            back->setScale(0.6f);
            addChild(back);
            
            char tem[32] = {0};
            sprintf(tem, "%d/%d",bagIte.count,info.mNum);
            CCLabelTTF* statelb = CCLabelTTF::create(tem, "STXingkai.ttf", 20);
            statelb->setColor(Color3B(0, 0, 0));
            if(i != 1)
                statelb->setPosition(Vec2(winSize.width * 0.5f-230 + i*230, winSize.height * 0.5f-130+i%2*260));
            else
                statelb->setPosition(Vec2(winSize.width * 0.5f-163 + i*230, winSize.height * 0.5f-130+i%2*260));
            addChild(statelb, 2);
        }
    }else if(itemMax == 4)
    {
        for (int i = 0; i<4; i++) {
            itemInfo info = hInfo[i];
            user_bag bagIte = Global::getInstance()->GetBagItem(info.id);
            
            Sprite* back = Sprite::create(info.resName.c_str());
            back->setPosition(Vec2(winSize.width * 0.5f-150 + i%2*300, winSize.height * 0.5f-90+i/2*180));
            back->setScale(0.6f);
            addChild(back);
            
            char tem[32] = {0};
            sprintf(tem, "%d/%d",bagIte.count,info.mNum);
            CCLabelTTF* statelb = CCLabelTTF::create(tem, "STXingkai.ttf", 20);
            statelb->setColor(Color3B(0, 0, 0));
            statelb->setPosition(Vec2(winSize.width * 0.5f-230 + i%2*460, winSize.height * 0.5f-130+i/2*180));
            addChild(statelb, 2);
        }
    }
    
    int Shenshou = Global::getInstance()->GetUserInfo().heroid;
    if(Shenshou == 0)
        Shenshou = 1;
    if (Shenshou)
    {
        char imagName[128] = {0};
        sprintf(imagName, "shenshou-%d-3.png",Shenshou);
        Sprite* image = Sprite::create(imagName);
        if(image)
        {
            //getChildByTag(14)->setVisible(false);
            
            //image->setAnchorPoint(Vec2(0.5f, 0.5f));
            image->setPosition(Vec2(winSize.width * 0.5f, winSize.height * 0.5f));
            image->setScale(0.6f);
            addChild(image, 2, 11);
            
            
            image->runAction(
                             RepeatForever::create(
                                                     Sequence::create(
                                                                        RotateBy::create(0.1f, 5.0f),NULL)));
            
            sprintf(imagName, "shenshou-%d-2.png",Shenshou);
            Sprite* texiao = Sprite::create(imagName);
            //texiao->setAnchorPoint(Vec2(0.5f, 0.5f));
            texiao->setPosition(Vec2(winSize.width * 0.5f, winSize.height * 0.5f));
            texiao->setScale(0.6f);
            addChild(texiao, 3, 12);
            
            texiao->runAction(
                              RepeatForever::create(
                                                      Sequence::create(
                                                                         RotateBy::create(0.1f, 5.0f),NULL)));
            
            sprintf(imagName, "shenshou-%d-1.png",Shenshou);
            Sprite* qlong = Sprite::create(imagName);
            //qlong->setAnchorPoint(Vec2(0, 0));
            qlong->setPosition(Vec2(winSize.width * 0.5f, winSize.height * 0.5f));
            qlong->setScale(0.6f);
            addChild(qlong, 4, 13);
        }
    }
    
    int idx = 0;
    
    char starstr[64]  = {0};
        
    if (idx < starNum)
        sprintf(starstr, "hecheng-xx-02.png");
    else
        sprintf(starstr, "hecheng-xx-01.png");
        
    Sprite* back = Sprite::create(starstr);
    back->setPosition(Vec2(winSize.width * 0.5f-60, winSize.height * 0.5f+87));
    back->setScale(0.6f);
    back->setRotation(-30);
    addChild(back);
    
    idx++;
    if (idx < starNum)
        sprintf(starstr, "hecheng-xx-02.png");
    else
        sprintf(starstr, "hecheng-xx-01.png");
    
    back = Sprite::create(starstr);
    back->setPosition(Vec2(winSize.width * 0.5f-32, winSize.height * 0.5f+87+16));
    back->setScale(0.6f);
    back->setRotation(-20);
    addChild(back);
    
    idx++;
    if (idx < starNum)
        sprintf(starstr, "hecheng-xx-02.png");
    else
        sprintf(starstr, "hecheng-xx-01.png");
    back = Sprite::create(starstr);
    back->setPosition(Vec2(winSize.width * 0.5f, winSize.height * 0.5f+87+20));
    back->setScale(0.6f);
    //back->setRotation(20);
    addChild(back);
    
    idx++;
    if (idx < starNum)
        sprintf(starstr, "hecheng-xx-02.png");
    else
        sprintf(starstr, "hecheng-xx-01.png");
    back = Sprite::create(starstr);
    back->setPosition(Vec2(winSize.width * 0.5f+32, winSize.height * 0.5f+87+16));
    back->setScale(0.6f);
    back->setRotation(20);
    addChild(back);
    
    idx++;
    if (idx < starNum)
        sprintf(starstr, "hecheng-xx-02.png");
    else
        sprintf(starstr, "hecheng-xx-01.png");
    back = Sprite::create(starstr);
    back->setPosition(Vec2(winSize.width * 0.5f+60, winSize.height * 0.5f+87));
    back->setScale(0.6f);
    back->setRotation(30);
    addChild(back);
    
}
void HeCheng::BackClick(Ref* pSender)
{
	GameVoice::getInstance()->playClickBtnVoive();
    getParent()->removeChild(this,true);
}
void HeCheng::HechengClick(Ref* pSender)
{
	GameVoice::getInstance()->playClickBtnVoive();
    bool isCanHeCheng = true;
    for (int i = 0; i<itemMax; i++) {
        user_bag bagIte = Global::getInstance()->GetBagItem(hInfo[i].id);
        if(bagIte.count < hInfo[i].mNum)
        {
            isCanHeCheng = false;
            break;
        }
    }
    
    if (isCanHeCheng) {
        MainScene* scene =  (MainScene*)(getParent()->getParent()->getParent());
        scene->reqUpHero();
    }
}
////////////////////////////////////////////////////////////////
/// 材料包裹
////////////////////////////////////////////////////////////////
CaiLiaoBag::CaiLiaoBag()
{
    std::map<int,user_bag> bagMap = Global::getInstance()->GetBagMap();
    std::map<int,user_bag>::iterator iter = bagMap.begin();
    for (; iter!=bagMap.end(); iter++) {
        user_bag bagIte = iter->second;
        
        if (bagIte.count) {
            item ite = Resource::sharedResource()->getItemForID(bagIte.mId);
            
            //CCLOG("itemRES:%s",ite.itemIcon.c_str());
            if (ite.itemType == 4) {
                itemInfo info;
                info.id = bagIte.mId;
                info.name = ite.itemName;
                info.resName = ite.itemIcon;
                info.mNum = bagIte.count;
                
                hInfo.push_back(info);
            }
        }
    }
    isTouchIn = false;
}
CaiLiaoBag::~CaiLiaoBag()
{
    
}

bool CaiLiaoBag::init()
{
    if(!CPZLayer::init())
        return false;
    
    LayerColor* layer = LayerColor::create(Color4B(0, 0, 0, 80));
    addChild(layer);
    
    Sprite* back = Sprite::create("bag-1.png");
    back->setPosition(Vec2(winSize.width * 0.5f, winSize.height * 0.5f));
    back->setScale(0.6f);
    addChild(back);
    
    
    TableView* tableView = TableView::create(this, getTableSize());
    //tableView->setTouchPriority(MAIN_TABLEVIEW_ACTIVE);
    tableView->setDirection(ScrollView::Direction::VERTICAL);
    //tableView->setPosition(Vec2(winSize.width * 0.5f - CHILD_OFFSET_X, winSize.height * 0.5f - CHILD_OFFSET_Y));
    tableView->setPosition(Vec2(winSize.width * 0.5f-350,winSize.height * 0.5f-200));
    tableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
    tableView->setDelegate(this);
    addChild(tableView, 50, 101);
    tableView->reloadData();
    
    return true;
}


void CaiLiaoBag::tableCellTouched(TableView* table, TableViewCell* cell)
{
    
}
TableViewCell* CaiLiaoBag::tableCellAtIndex(TableView* table, ssize_t idex)
{
    TableViewCell* cell = table->dequeueCell();
    if (!cell) {
        cell = new TableViewCell();
        cell->autorelease();
    }else{
        cell->removeAllChildrenWithCleanup(true);
    }
    createTableViewCell(cell, table, idex);
    return cell;
}
Size CaiLiaoBag::cellSizeForTable(TableView* table)
{
    return Size(700, 200);

}
ssize_t CaiLiaoBag::numberOfCellsInTableView(TableView* table)
{
    return (int)(hInfo.size()/4)+(hInfo.size()%4);
}

Size CaiLiaoBag::getTableSize()
{
    return Size(700, 400);
}
void CaiLiaoBag::createTableViewCell(Node* cell, TableView* table, int idex)
{
    for (int i = 0; i<4; i++) {
        if(idex*4+i >= hInfo.size())
            break;
        Sprite* table_bg = Sprite::create("bag-cell-bg.png");
        table_bg->setScale(0.6f);
        table_bg->setPosition(Vec2(175/2+i*175,120));
        cell->addChild(table_bg,1);
        
        itemInfo info = hInfo[idex*4+i];
        
        table_bg = Sprite::create(info.resName.c_str());
        table_bg->setScale(0.6f);
        table_bg->setPosition(Vec2(175/2+i*175,120));
        cell->addChild(table_bg,1);
        
        char lab[32] = {0};
        sprintf(lab, "%d/99",info.mNum);
        CCLabelTTF* statelb = CCLabelTTF::create(lab, "STXingkai.ttf", 30);
        statelb->setColor(Color3B(0, 0, 0));
        statelb->setPosition(Vec2(175/2+i*175,30));
        cell->addChild(statelb, 2);
    }
}

bool CaiLiaoBag::onTouchBegan(Touch* pTouch,Event* pEvent)
{
    //Touch* pTouch = (Touch*)pTouches->anyObject();
    Node* node = getChildByTag(101);
    Point pt = node->convertToNodeSpace(Director::getInstance()->convertToGL(pTouch->getLocationInView()));
    Rect rt = Rect(0, 0, 700, 400);
    
    isTouchIn = rt.containsPoint(pt);
    if(isTouchIn)
        return false;
    else
        return true;
}
void CaiLiaoBag::onTouchEnded(Touch* pTouch,Event* pEvent)
{
    if(isTouchIn)
        return;
    //Touch* pTouch = (Touch*)pTouches->anyObject();
    Node* node = getChildByTag(101);
    Point pt = node->convertToNodeSpace(Director::getInstance()->convertToGL(pTouch->getLocationInView()));
    Rect rt = Rect(0, 0, 700, 400);
    if(rt.containsPoint(pt) == false)
    {
        getParent()->removeChild(this);
    }
}

////////////////////////////////////////////////////////////////
/// 锦盒
////////////////////////////////////////////////////////////////
ShopLayerJinhe::ShopLayerJinhe()
{
    
}

ShopLayerJinhe::~ShopLayerJinhe()
{
    
}

bool ShopLayerJinhe::init()
{
    if(!Layer::init())
        return false;
    
    childSize = Size(1036, 520);
    
    Sprite* xiangzibg = Sprite::create("lv1.png");
    xiangzibg->setScale(0.35f);
    xiangzibg->setPosition(Vec2(childSize.width * 0.5f - 200, childSize.height * 0.5f + 60));
    addChild(xiangzibg, 1);
    
    Sprite* xiangzi1 = Sprite::create("xiangzi1.png");
    xiangzi1->setScale(0.6f);
    xiangzi1->setPosition(Vec2(childSize.width * 0.5f - 200, childSize.height * 0.5f + 60));
    addChild(xiangzi1, 1);
    
    xiangzibg = Sprite::create("lv1.png");
    xiangzibg->setScale(0.35f);
    xiangzibg->setPosition(Vec2(childSize.width * 0.5f + 200, childSize.height * 0.5f + 60));
    addChild(xiangzibg, 1);
    
    Sprite* xiangzi2 = Sprite::create("xiangzi2.png");
    xiangzi2->setScale(0.6f);
    xiangzi2->setPosition(Vec2(childSize.width * 0.5f + 200, childSize.height * 0.5f + 60));
    addChild(xiangzi2, 1);
    
    user_bag bag = Global::getInstance()->GetBagItem(701);
    char temp[64] = {0};
    sprintf(temp, Global::getInstance()->getString("60"),bag.count);
    CCLabelTTF* title_time1 = CCLabelTTF::create(temp, "STXingkai.ttf", 29);
    title_time1->setColor(Color3B(0, 0, 0));
    title_time1->setPosition(Vec2(childSize.width * 0.5f - 200, childSize.height * 0.5f - 150));
    addChild(title_time1, 1,11);

    
    Button* backBtn = Button::createBtnWithSpriteFrameName("money_back.png", false);
    backBtn->setPosition(Vec2(childSize.width * 0.5f - 200, childSize.height * 0.5f - 210));
    backBtn->setScale(0.6f);
    backBtn->setOnClickCallback(callfuncO_selector(ShopLayerJinhe::OpenMuClick), this);
    addChild(backBtn, 1);
    
    CCLabelTTF* statelb = CCLabelTTF::create(Global::getInstance()->getString("61"), "STXingkai.ttf", 50);
    //statelb->setColor(Color3B(0, 0, 0));
    //statelb->setPosition(Vec2(175/2+i*175,30));
    backBtn->addChild(statelb, 2);
    
    bag = Global::getInstance()->GetBagItem(702);
    sprintf(temp, Global::getInstance()->getString("60"),bag.count);
    CCLabelTTF* title_time2 = CCLabelTTF::create(temp, "STXingkai.ttf", 29);
    title_time2->setColor(Color3B(0, 0, 0));
    title_time2->setPosition(Vec2(childSize.width * 0.5f + 200, childSize.height * 0.5f - 150));
    addChild(title_time2, 1,12);
    
    backBtn = Button::createBtnWithSpriteFrameName("money_back.png", false);
    backBtn->setPosition(Vec2(childSize.width * 0.5f + 200, childSize.height * 0.5f - 210));
    backBtn->setScale(0.6f);
    backBtn->setOnClickCallback(callfuncO_selector(ShopLayerJinhe::OpenHaoClick), this);
    addChild(backBtn, 1);
    
    statelb = CCLabelTTF::create(Global::getInstance()->getString("61"), "STXingkai.ttf", 50);
    backBtn->addChild(statelb, 2);
    return true;
}
void ShopLayerJinhe::rushLab()
{
    user_bag bag = Global::getInstance()->GetBagItem(701);
    char temp[64] = {0};
    sprintf(temp, Global::getInstance()->getString("60"),bag.count);
    
    CCLabelTTF* lab = (CCLabelTTF*)getChildByTag(11);
    lab->setString(temp);
    
    bag = Global::getInstance()->GetBagItem(702);
    sprintf(temp, Global::getInstance()->getString("60"),bag.count);
    lab = (CCLabelTTF*)getChildByTag(12);
    lab->setString(temp);
}
void ShopLayerJinhe::OpenMuClick(Ref* pSender)
{
	GameVoice::getInstance()->playClickBtnVoive();
    user_bag bag = Global::getInstance()->GetBagItem(701);
    if (bag.count <= 0) {
        Global::getInstance()->ShowPromBox(Global::getInstance()->getString("62"));
    }else{
        MainScene* scene =  (MainScene*)(getParent()->getParent());
        scene->reqUseItem(701);
    }
}
void ShopLayerJinhe::OpenHaoClick(Ref* pSender)
{
	GameVoice::getInstance()->playClickBtnVoive();
    user_bag bag = Global::getInstance()->GetBagItem(702);
    if (bag.count <= 0) {
        Global::getInstance()->ShowPromBox(Global::getInstance()->getString("62"));
    }else{
        MainScene* scene =  (MainScene*)(getParent()->getParent());
        scene->reqUseItem(702);
    }
}
//////////////////////////////////////////////////////////////////
/// 获取元宝
//////////////////////////////////////////////////////////////////
ShopLayerHuoqu::ShopLayerHuoqu()
{
    
}

ShopLayerHuoqu::~ShopLayerHuoqu()
{
    
}

bool ShopLayerHuoqu::init()
{
    if(!Layer::init())
        return false;
    
    childSize = Size(1036, 520);
    
    Sprite* help = Sprite::create("wenhao.png");
    help->setScale(0.6f);
    help->setPosition(Vec2(100, childSize.height - 100));
    addChild(help, 1);
    
    CCLabelTTF* helpLb = CCLabelTTF::create(Global::getInstance()->getString("63"), "STXingkai.ttf", 35);
    helpLb->setColor(Color3B(0, 0, 0));
    helpLb->setPosition(Vec2(250, childSize.height - 100));
    addChild(helpLb, 1);
    
    std::ostringstream ossAttr;
    std::string content1 = Global::getInstance()->getString("64");
    std::string content2 = Global::getInstance()->getString("65");
    std::string content3 = Global::getInstance()->getString("66");
    ossAttr<<"<t/><font><fontname>STXingkai</><fontsize>25</><color><value>00000060</>" << content1.c_str()  <<"</></>";
    ossAttr<<"<n/><font><fontname>STXingkai</><fontsize>25</><color><value>00000060</>" << content2.c_str() <<"</></>";
    ossAttr<<"<n/><font><fontname>STXingkai</><fontsize>25</><color><value>00000060</>" << content3.c_str() <<"</></>";
    
    RichLabel* helpCon = RichLabel::create(ossAttr.str().c_str(), "STXingkai.ttf", 29.0f, Size(400, 300),false,false);
    helpCon->setAnchorPoint(Vec2::ZERO);
	helpCon->setColor(/*ccBLACK*/cocos2d::Color3B::BLACK);
    helpCon->setPosition(Vec2(50, childSize.height - 400));
    addChild(helpCon, 1);
    
    CCLabelTTF* todaylb = CCLabelTTF::create(Global::getInstance()->getString("67"), "STXingkai.ttf", 29);
    todaylb->setColor(Color3B(0, 0, 0));
    todaylb->setPosition(Vec2(100, 130));
    addChild(todaylb, 1);
    
    CCLabelTTF* totlelb = CCLabelTTF::create(Global::getInstance()->getString("68"), "STXingkai.ttf", 29);
    totlelb->setColor(Color3B(0, 0, 0));
    totlelb->setPosition(Vec2(100, 90));
    addChild(totlelb, 1);
    
    Sprite* money_back1 = Sprite::create("huode_base.png");
    money_back1->setScale(0.5f);
    money_back1->setPosition(Vec2(230, 130));
    addChild(money_back1, 1);
    
    CCLabelTTF* todayget1 = CCLabelTTF::create("0", "STXingkai.ttf", 29);
    todayget1->setColor(Color3B(255, 255, 255));
    todayget1->setPosition(Vec2(230, 130));
    addChild(todayget1, 2);
    
    Sprite* money_back2 = Sprite::create("huode_base.png");
    money_back2->setScale(0.5f);
    money_back2->setPosition(Vec2(230, 90));
    addChild(money_back2, 1);
    
    CCLabelTTF* todayget2 = CCLabelTTF::create("0", "STXingkai.ttf", 29);
    todayget2->setColor(Color3B(255, 255, 255));
    todayget2->setPosition(Vec2(230, 90));
    addChild(todayget2, 2);
    
    Button* hecheng = Button::createBtnWithSpriteFrameName("lingqubtn.png", false);
    hecheng->setPosition(Vec2(400, 90));
    hecheng->setScale(0.6f);
    hecheng->setOnClickCallback(callfuncO_selector(ShopLayerHuoqu::LingquClick), this);
    addChild(hecheng, 1);
    
    // bottom
    Sprite* bottomLb = Sprite::create("wodezhuanshu-01.png");
    bottomLb->setScale(0.6f);
    bottomLb->setPosition(Vec2(200, 0));
    addChild(bottomLb, 1);
    
    Sprite* zhuanshuback = Sprite::create("zhuanshu_back.png");
    zhuanshuback->setScale(0.5f);
    zhuanshuback->setPosition(Vec2(childSize.width * 0.5f - 40, 0));
    addChild(zhuanshuback, 1);
    
    CCLabelTTF* url = CCLabelTTF::create("http://liaobuqi/qiuqiusanguo", "STXingkai.ttf", 29);
    url->setColor(Color3B(255, 255, 255));
    url->setPosition(Vec2(childSize.width * 0.5f - 40, 0));
    addChild(url, 2);
    
    Button* copyBtn = Button::createBtnWithSpriteFrameName("copyurlbtn.png", false);
    copyBtn->setPosition(Vec2(childSize.width - 240, 0));
    copyBtn->setScale(0.6f);
    copyBtn->setOnClickCallback(callfuncO_selector(ShopLayerHuoqu::copyClick), this);
    addChild(copyBtn, 1);
    
    //splite
    Sprite* splite = Sprite::create("shop_splite.png");
    splite->setScale(0.6f);
    splite->setPosition(Vec2(childSize.width * 0.5f, childSize.height * 0.5f));
    addChild(splite, 1);
    
    Sprite* wodezhuanshutitle = Sprite::create("wodezhuanshu-02.png");
    wodezhuanshutitle->setScale(0.6f);
    wodezhuanshutitle->setPosition(Vec2(childSize.width * 0.75f, childSize.height - 100));
    addChild(wodezhuanshutitle, 1);
    
    Sprite* wodezhuanshu = Sprite::create("erweima-01.png");
    wodezhuanshu->setScale(0.6f);
    wodezhuanshu->setPosition(Vec2(childSize.width * 0.75f, childSize.height * 0.5f + 20));
    addChild(wodezhuanshu, 1);
    
    Button* saveBtn = Button::createBtnWithSpriteFrameName("savephoto.png", false);
    saveBtn->setPosition(Vec2(childSize.width * 0.75f, 100));
    saveBtn->setScale(0.6f);
    saveBtn->setOnClickCallback(callfuncO_selector(ShopLayerHuoqu::saveClick), this);
    addChild(saveBtn, 1);
    
    return true;
}

void ShopLayerHuoqu::LingquClick(cocos2d::Ref *pSender)
{
	GameVoice::getInstance()->playClickBtnVoive();
}

void ShopLayerHuoqu::saveClick(cocos2d::Ref *pSender)
{
	GameVoice::getInstance()->playClickBtnVoive();
}

void ShopLayerHuoqu::copyClick(cocos2d::Ref *pSender)
{
	GameVoice::getInstance()->playClickBtnVoive();
}


