//
//  RelationShipLayer.cpp
//  qiuFight
//
//  Created by ÕÅÔ¾¶« on 16/4/8.
//
//

#include "RelationShipLayer.h"
#include "MainScene.h"

#define CHILD_OFFSET_X      100
#define CHILD_OFFSET_Y      50
#define MAIN_TABLLEVIEW_ACTIVE      -120


#include "msg_client.pb.h"
#include "struct.pb.h"
#include "ExchangeInfo.h"
#include "msg_error.pb.h"
#include "CurCularNode.h"
#include "GameVoice.h"

/////////////////////////////////////////////////////
///base
/////////////////////////////////////////////////////
RelationShipBase::RelationShipBase()
{
    m_currentTag    = TAG_NONE;
    m_attention     = NULL;
    m_friend        = NULL;
    m_enemy         = NULL;
    m_black         = NULL;
}

RelationShipBase::~RelationShipBase()
{
    m_currentTag    = TAG_NONE;
    m_attention     = NULL;
    m_friend        = NULL;
    m_enemy         = NULL;
    m_black         = NULL;
}

bool RelationShipBase::init()
{
    if(!Layer::init())
        return false;
    
    initUI();
    
    return true;
}

void RelationShipBase::initUI()
{
    Sprite* back = Sprite::create("center_back.png");
    back->setPosition(Vec2(winSize.width * 0.5f, winSize.height * 0.5f));
    back->setScale(0.6f);
    addChild(back);
    
    m_attention = Button::createBtnWithSpriteFrameName("guanzhu-02.png", false);
    m_attention->setPosition(Vec2(190, winSize.height - 80));
    m_attention->setScale(0.6f);
    m_attention->setOnClickCallback(callfuncO_selector(RelationShipBase::AttentionClick), this);
    m_attention->setPressIcon("guanzhu-01.png", false);
    m_attention->setPressIconShow(true);
    addChild(m_attention, 1);
    
    m_friend = Button::createBtnWithSpriteFrameName("fensi-02.png", false);
    m_friend->setPosition(Vec2(440, winSize.height - 80));
    m_friend->setScale(0.6f);
    m_friend->setOnClickCallback(callfuncO_selector(RelationShipBase::FriendClick), this);
    m_friend->setPressIcon("fensi-01.png", false);
    addChild(m_friend, 1);
    
    m_enemy = Button::createBtnWithSpriteFrameName("duishou-02.png", false);
    m_enemy->setPosition(Vec2(690, winSize.height - 80));
    m_enemy->setScale(0.6f);
    m_enemy->setOnClickCallback(callfuncO_selector(RelationShipBase::EnemyClick), this);
    m_enemy->setPressIcon("duishou-01.png", false);
    addChild(m_enemy, 1);
    
    m_black = Button::createBtnWithSpriteFrameName("heimigndan-02.png", false);
    m_black->setPosition(Vec2(940, winSize.height - 80));
    m_black->setScale(0.6f);
    m_black->setOnClickCallback(callfuncO_selector(RelationShipBase::BlackClick), this);
    m_black->setPressIcon("heimingdan-01.png", false);
    addChild(m_black, 1);
    
    Button* backBtn = Button::createBtnWithSpriteFrameName("fanhui-01.png", false);
    backBtn->setPosition(Vec2(winSize.width - 80, 50));
    backBtn->setScale(0.6f);
    backBtn->setOnClickCallback(callfuncO_selector(RelationShipBase::BackClick), this);
    addChild(backBtn, 1);
    
    m_currentTag = TAG_NONE;
    scheduleOnce(schedule_selector(RelationShipBase::SenMSG), 0.01f);
}
void RelationShipBase::SenMSG(float ft)
{
    AttentionClick(nullptr);
}
void RelationShipBase::resetBtnState()
{
    m_attention->setPressIconShow(false);
    m_friend->setPressIconShow(false);
    m_enemy->setPressIconShow(false);
    m_black->setPressIconShow(false);
    
    if(getChildByTag(TAG_ATTENTION))
    {
        removeChildByTag(TAG_ATTENTION);
    }
    else if(getChildByTag(TAG_FRIEND))
    {
        removeChildByTag(TAG_FRIEND);
    }
    else if(getChildByTag(TAG_ENEMY))
    {
        removeChildByTag(TAG_ENEMY);
    }
    else if(getChildByTag(TAG_BLACK))
    {
        removeChildByTag(TAG_BLACK);
    }
}

void RelationShipBase::AttentionClick(cocos2d::Ref *pSender)
{
	if (pSender) GameVoice::getInstance()->playClickBtnVoive();
    if(TAG_ATTENTION == m_currentTag)
        return;
    
    resetBtnState();
    m_currentTag = TAG_ATTENTION;
    m_attention->setPressIconShow(true);
    
    RelationShipAttention* attention = RelationShipAttention::create();
    attention->setPosition(Vec2(CHILD_OFFSET_X, CHILD_OFFSET_Y));
    addChild(attention, 10, TAG_ATTENTION);
    
    //user_info usef = Global::getInstance()->GetUserInfo();
    ((MainScene*)getParent())->reqFriendList(1);
}

void RelationShipBase::FriendClick(cocos2d::Ref *pSender)
{
	GameVoice::getInstance()->playClickBtnVoive();
    if(TAG_FRIEND == m_currentTag)
        return;
    
    resetBtnState();
    m_currentTag = TAG_FRIEND;
    m_friend->setPressIconShow(true);
    
    RelationShipAttention* attention = RelationShipAttention::create();
    attention->setPosition(Vec2(CHILD_OFFSET_X, CHILD_OFFSET_Y));
    addChild(attention, 10, TAG_FRIEND);
    
    user_info usef = Global::getInstance()->GetUserInfo();
    ((MainScene*)getParent())->reqFans(2, 0, 20,usef.roleID);
}

void RelationShipBase::EnemyClick(cocos2d::Ref *pSender)
{
	GameVoice::getInstance()->playClickBtnVoive();
    if(TAG_ENEMY == m_currentTag)
        return;
    
    resetBtnState();
    m_currentTag = TAG_ENEMY;
    m_enemy->setPressIconShow(true);
    
    RelationShipAttention* attention = RelationShipAttention::create();
    attention->setPosition(Vec2(CHILD_OFFSET_X, CHILD_OFFSET_Y));
    addChild(attention, 10, TAG_ENEMY);
    
    ((MainScene*)getParent())->reqFriendList(4);
}

void RelationShipBase::BlackClick(cocos2d::Ref *pSender)
{
	GameVoice::getInstance()->playClickBtnVoive();
    if(TAG_BLACK == m_currentTag)
        return;
    
    resetBtnState();
    m_currentTag = TAG_BLACK;
    m_black->setPressIconShow(true);
    
    RelationShipAttention* attention = RelationShipAttention::create();
    attention->setPosition(Vec2(CHILD_OFFSET_X, CHILD_OFFSET_Y));
    addChild(attention, 10, TAG_BLACK);
    
    ((MainScene*)getParent())->reqFriendList(3);
}

void RelationShipBase::PrePageClick(cocos2d::Ref *pSender)
{
    
}

void RelationShipBase::NextPageClick(cocos2d::Ref *pSender)
{
    
}

void RelationShipBase::BackClick(cocos2d::Ref *pSender)
{
	GameVoice::getInstance()->playClickBtnVoive();
    MainScene* main = dynamic_cast<MainScene*>(getParent());
    main->BackToLoginLayer(MainScene::TAG_LAYER_RELATION);
}

void RelationShipBase::respFans(const cocos2d::network::WebSocket::Data& data)
{
    if(data.len <= 2)
        return;
    
    for (int i = 2; i < data.len; i++) {
        printf("%d,", (uint8_t)data.bytes[i]);
    }
    std::vector<int> icons;
    icons.clear();

    UM_Fans resp;
    bool re = resp.ParseFromArray(data.bytes + 2, data.len - 2);
    if(re)
    {
        //std::vector<rank_info> items;
        std::vector<TestAtt> fanses;
        int num = resp.list_size();
        //log("list number is:%d", num);
        for( int i = 0; i < num; i++)
        {
            TestAtt  rank;
            fans_info item = resp.list(i);
            //log("shop item id is:%d", item.roleid());
            //items.push_back(item);
            rank.m_id = item.roleid();
            rank.m_sex = item.sex();
            rank.m_name = item.name();
            rank.m_icon = item.icon();
            
            if(rank.m_icon < 101)
            {
                icons.push_back(rank.m_id);
            }
            rank.m_dest = Global::getInstance()->getString("2");
            rank.m_state = Global::getInstance()->getString("3");
            rank.m_times = Global::getInstance()->getString("4");
            fanses.push_back(rank);
        }
        
        if(icons.size() > 0)
        {
            ((RelationShipAttention*)getChildByTag(m_currentTag))->setLists(fanses);
            MainScene* main = dynamic_cast<MainScene*>(getParent());
            main->reqIcons(icons);
        }else{
            ((RelationShipAttention*)getChildByTag(m_currentTag))->initTableView(fanses);
        }
    }
}
void RelationShipBase::resIcon(std::vector<icon_data> icons)
{
    ((RelationShipAttention*)getChildByTag(m_currentTag))->updateLists(icons);
}
void RelationShipBase::respFriends(const cocos2d::network::WebSocket::Data &data)
{
    for (int i = 2; i < data.len; i++) {
        printf("%d,", (uint8_t)data.bytes[i]);
    }
    
    std::vector<int> icons;
    icons.clear();
    
    UM_Friends resp;
    bool re = resp.ParseFromArray(data.bytes + 2, data.len - 2);
    if(re)
    {
        std::vector<TestAtt> fanse;
        int num = resp.list_size();
        //log("friend number is:%d", num);
        for(int i = 0; i < num; i++)
        {
            TestAtt rank;
            friend_info finfo = resp.list(i);
            rank.m_id = finfo.roleid();
            rank.m_sex = finfo.sex();
            rank.m_name = finfo.name();
            rank.m_icon = finfo.icon();
            if(rank.m_icon < 101)
            {
                icons.push_back(rank.m_id);
            }
            rank.m_dest = Global::getInstance()->getString("2");
            rank.m_state = Global::getInstance()->getString("3");
            rank.m_times = Global::getInstance()->getString("4");
            fanse.push_back(rank);
        }
        
        if(icons.size() > 0)
        {
            ((RelationShipAttention*)getChildByTag(m_currentTag))->setLists(fanse);
            MainScene* main = dynamic_cast<MainScene*>(getParent());
            main->reqIcons(icons);
        }else{
            ((RelationShipAttention*)getChildByTag(m_currentTag))->initTableView(fanse);
        }
    }
}

////////////////////////////////////////////////////////////////////
//// ¹Ø×¢
////////////////////////////////////////////////////////////////////
RelationShipAttention::RelationShipAttention()
{
    m_atts.clear();
    m_tag = RelationShipBase::TAG_NONE;
}

RelationShipAttention::~RelationShipAttention()
{
    m_atts.clear();
    
    m_tag = RelationShipBase::TAG_NONE;
}

bool RelationShipAttention::init()
{
    if(!Layer::init())
        return false;
    
//    LayerColor* color = LayerColor::create(Color4B(0, 0, 0, 255), 936, 460);
//    color->setPosition(Vec2(0,0));
//    addChild(color,0);
    
    //scheduleOnce(schedule_selector(RelationShipAttention::initTableView), 0.1);
    
    return true;
}

void RelationShipAttention::initTableView(std::vector<TestAtt> fanses)
{
    m_atts = fanses;
    if (getChildByTag(101)) {
        ((TableView*)getChildByTag(101))->reloadData();
        return;
    }
    RelationShipBase* base = dynamic_cast<RelationShipBase*>(getParent());
    m_tag = base->GetCurrentTag();
    
    TableView* tableView = TableView::create(this, getTableSize());
    //tableView->setTouchPriority(MAIN_TABLEVIEW_ACTIVE);
    tableView->setDirection(ScrollView::Direction::VERTICAL);
    //tableView->setPosition(Vec2(winSize.width * 0.5f - CHILD_OFFSET_X, winSize.height * 0.5f - CHILD_OFFSET_Y));
    tableView->setPosition(Vec2(0,0));
    tableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
    tableView->setDelegate(this);
    addChild(tableView, 2, 101);
    tableView->reloadData();
}
void RelationShipAttention::updateLists(std::vector<icon_data> datas)
{
    std::vector<TestAtt>::iterator it = m_atts.begin();
    for(; it != m_atts.end(); ++it)
    {
        if((*it).m_icon < 101)
        {
            (*it).m_iconStr = getIconString((*it).m_id, datas);
        }
    }
    
    initTableView(m_atts);
}
std::string RelationShipAttention::getIconString(int roleID, std::vector<icon_data>datas)
{
    std::vector<icon_data>::iterator it = datas.begin();
    for(; it != datas.end(); ++it)
    {
        icon_data data = *it;
        if(data.roleid() == roleID)
        {
            return data.data();
        }
    }
    
    return "";
}
Size RelationShipAttention::getTableSize()
{
    return Size(winSize.width - 2 * CHILD_OFFSET_X, winSize.height - 2 * CHILD_OFFSET_Y - 80);
}

void RelationShipAttention::tableCellTouched(cocos2d::extension::TableView *table, cocos2d::extension::TableViewCell *cell)
{
    int idx = cell->getIdx();
    TestAtt info = m_atts[idx];
    
    ((MainScene*)getParent()->getParent())->reqRole(info.m_id);
}

TableViewCell* RelationShipAttention::tableCellAtIndex(cocos2d::extension::TableView *table, ssize_t idex)
{
    TableViewCell* cell = table->dequeueCell();
    if(!cell)
    {
        cell = new TableViewCell();
        cell->autorelease();
        
        Node* cellNode = Node::create();
        //cellNode->setAnchorPoint(Vec2::ZERO);
        cellNode->setPosition(Vec2(winSize.width * 0.5f - CHILD_OFFSET_X, 0));
        
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

void RelationShipAttention::createTableViewCell(cocos2d::Node *cell, cocos2d::extension::TableView *table, int idex)
{
    int left = idex % 2;
    Sprite* table_bg = NULL;
    if(left == 0)
        table_bg = Sprite::create("dikuang-01.png");
    else
        table_bg = Sprite::create("dikuang-02.png");
    if(table)
    {
        table_bg->setScale(0.6f);
        table_bg->setPosition(Vec2(0,40));
        cell->addChild(table_bg,1);
        
        Size size = table_bg->getContentSize() * 0.6;
        
        TestAtt info = m_atts[idex];
        if (info.m_icon > 101) {
            char temp[32];
            sprintf(temp, "hero_%d.png", info.m_icon);
            Sprite* icon = Sprite::create(temp);
            CirCularNode* iconCir = CirCularNode::create(25, icon);
            iconCir->setPosition(Vec2(50 - size.width * 0.5f, 40));
            icon->setScale(0.2f);
            cell->addChild(iconCir, 1);
        }else{
            
            Texture2D* tex = ExchangeInfo::GetTextureForData(info.m_iconStr.c_str());
            
            Sprite* icon = Sprite::createWithTexture(tex);
            CirCularNode* iconCir = CirCularNode::create(25, icon);
            iconCir->setPosition(Vec2(50 - size.width * 0.5f, 40));
            icon->setScale(0.2f);
            cell->addChild(iconCir, 1);
        }
        
        
        Sprite* sex = Sprite::create("male.png");
        sex->setPosition(Vec2(100 - size.width * 0.5f, 40));
        sex->setScale(0.8f);
        cell->addChild(sex, 1);
        
        if (info.m_name == "") {
            char namlab[64] = {0};
            sprintf(namlab, "S%d",info.m_id);
            info.m_name = namlab;
        }
        CCLabelTTF* nick_name = CCLabelTTF::create(info.m_name.c_str(), "STXingkai.ttf", 29);
        nick_name->setColor(Color3B(255, 255, 255));
        nick_name->setAnchorPoint(Vec2(0,0));
        nick_name->setPosition(Vec2(120 - size.width * 0.5f, 20));
        cell->addChild(nick_name, 1);
        
        CCLabelTTF* duration = CCLabelTTF::create(info.m_state.c_str(), "STXingkai.ttf", 29);
        duration->setColor(Color3B(255, 255, 255));
        //duration->setAnchorPoint(Vec2(0,0));
        duration->setPosition(Vec2(800 - size.width * 0.5f, 40));
        cell->addChild(duration, 1);
        
        if(m_tag == RelationShipBase::TAG_ATTENTION || m_tag == RelationShipBase::TAG_FRIEND)
        {
            CCLabelTTF* rank = CCLabelTTF::create(info.m_dest.c_str(), "STXingkai.ttf", 29);
            rank->setColor(Color3B(255, 255, 255));
            rank->setAnchorPoint(Vec2(0,0));
            rank->setPosition(Vec2(400 - size.width * 0.5f, 20));
            cell->addChild(rank, 1);
        }
        else if(m_tag == RelationShipBase::TAG_ENEMY)
        {
            CCLabelTTF* rank = CCLabelTTF::create(info.m_times.c_str(), "STXingkai.ttf", 29);
            rank->setColor(Color3B(255, 255, 255));
            rank->setAnchorPoint(Vec2(0,0));
            rank->setPosition(Vec2(480 - size.width * 0.5f, 20));
            cell->addChild(rank, 1);
        }
        
        
    }
}

Size RelationShipAttention::cellSizeForTable(cocos2d::extension::TableView *table)
{
    Size tableSize = getTableSize();
    return Size(tableSize.width, tableSize.height / 7);
}

ssize_t RelationShipAttention::numberOfCellsInTableView(cocos2d::extension::TableView *table)
{
    return (int)m_atts.size();
}

void RelationShipAttention::scrollViewDidScroll(cocos2d::extension::ScrollView *view)
{
    
}

void RelationShipAttention::scrollViewDidZoom(cocos2d::extension::ScrollView *view)
{
    
}


