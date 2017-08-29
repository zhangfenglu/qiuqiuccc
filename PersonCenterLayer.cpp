//
//  PersonCenterLayer.cpp
//  qiuFight
//
//  Created by 张跃东 on 16/4/1.
//
//

#include "PersonCenterLayer.h"
//#include "InputLabel.h"
#include "MainScene.h"

#define CHILD_OFFSET_X      50
#define CHILD_OFFSET_Y      100
#define MAIN_TABLEVIEW_ACTIVE   -120


//////////////////////////////////////////////////////
// base
//////////////////////////////////////////////////////
PersonCenterBase::PersonCenterBase()
{
    
}

PersonCenterBase::~PersonCenterBase()
{
    
}

bool PersonCenterBase::init()
{
    if(!Layer::init())
        return false;
    
    initUI();
    
    return true;
}

void PersonCenterBase::initUI()
{
    Sprite* back = Sprite::create("center_back.png");
    back->setPosition(Vec2(winSize.width * 0.5f, winSize.height * 0.5f));
    back->setScale(0.6f);
    addChild(back);
    
    ziliao = Button::createBtnWithSpriteFrameName("gerenziliao-01.png", false);
    ziliao->setPosition(Vec2(200, winSize.height - 50));
    ziliao->setScale(0.6f);
    ziliao->setOnClickCallback(callfuncO_selector(PersonCenterBase::ZiliaoClick), this);
    ziliao->setPressIcon("gerenziliao-02.png", false);
    ziliao->setPressIconShow(true);
    addChild(ziliao, 1);
    
    xinxi = Button::createBtnWithSpriteFrameName("yonghuxinxi-01.png", false);
    xinxi->setPosition(Vec2(400, winSize.height - 50));
    xinxi->setScale(0.6f);
    xinxi->setOnClickCallback(callfuncO_selector(PersonCenterBase::XinxiClick), this);
    xinxi->setPressIcon("yonghuxinxi-02.png", false);
    addChild(xinxi, 1);
    
    rongyu = Button::createBtnWithSpriteFrameName("gerenrongyu-01.png", false);
    rongyu->setPosition(Vec2(600, winSize.height - 50));
    rongyu->setScale(0.6f);
    rongyu->setOnClickCallback(callfuncO_selector(PersonCenterBase::RongyuClick), this);
    rongyu->setPressIcon("gerenrongyu-02.png", false);
    addChild(rongyu, 1);
    
    bisai = Button::createBtnWithSpriteFrameName("bisaijilu-01.png", false);
    bisai->setPosition(Vec2(800, winSize.height - 50));
    bisai->setScale(0.6f);
    bisai->setOnClickCallback(callfuncO_selector(PersonCenterBase::BisaiClick), this);
    bisai->setPressIcon("bisaijilu-02.png", false);
    addChild(bisai, 1);
    
    Button* set = Button::createBtnWithSpriteFrameName("set_btn.png", false);
    set->setPosition(Vec2(winSize.width - 200, 50));
    set->setScale(0.6f);
    set->setOnClickCallback(callfuncO_selector(PersonCenterBase::SetClick), this);
    addChild(set, 1);
    
    Button* backBtn = Button::createBtnWithSpriteFrameName("back_btn.png", false);
    backBtn->setPosition(Vec2(winSize.width - 100, 50));
    backBtn->setScale(0.6f);
    backBtn->setOnClickCallback(callfuncO_selector(PersonCenterBase::BackClick), this);
    addChild(backBtn, 1);
    
    m_currentTag = TAG_NONE;
    
    ZiliaoClick(ziliao);
}

void PersonCenterBase::resetBtnState()
{
    ziliao->setPressIconShow(false);
    xinxi->setPressIconShow(false);
    rongyu->setPressIconShow(false);
    bisai->setPressIconShow(false);
    
    if(getChildByTag(TAG_ZILIAO))
    {
        removeChildByTag(TAG_ZILIAO);
    }
    else if(getChildByTag(TAG_XINXI))
    {
        removeChildByTag(TAG_XINXI);
    }
    else if(getChildByTag(TAG_BISAI))
    {
        removeChildByTag(TAG_BISAI);
    }
    else if(getChildByTag(TAG_RONGYU))
    {
        removeChildByTag(TAG_RONGYU);
    }
}

void PersonCenterBase::XinxiClick(cocos2d::Ref *pSender)
{
    if(TAG_XINXI == m_currentTag)
        return;
    
    resetBtnState();
    m_currentTag = TAG_XINXI;
    xinxi->setPressIconShow(true);
    
    PersonXinxi* xinxi = PersonXinxi::create();
    xinxi->setPosition(Vec2(CHILD_OFFSET_X, CHILD_OFFSET_Y));
    addChild(xinxi, 10, TAG_XINXI);
    
}

void PersonCenterBase::ZiliaoClick(cocos2d::Ref *pSender)
{
    if(TAG_ZILIAO == m_currentTag)
        return;
    
    resetBtnState();
    m_currentTag = TAG_ZILIAO;
    ziliao->setPressIconShow(true);
    
    PersonInfo* info = PersonInfo::create();
    info->setPosition(Vec2(CHILD_OFFSET_X, CHILD_OFFSET_Y));
    addChild(info, 10, TAG_ZILIAO);
}

void PersonCenterBase::RongyuClick(cocos2d::Ref *pSender)
{
    if(TAG_RONGYU == m_currentTag)
        return;
    
    resetBtnState();
    m_currentTag = TAG_RONGYU;
    rongyu->setPressIconShow(true);
    
    PersonRongyu* rongyu = PersonRongyu::create();
    rongyu->setPosition(Vec2(CHILD_OFFSET_X, CHILD_OFFSET_Y));
    addChild(rongyu, 10, TAG_RONGYU);
}

void PersonCenterBase::BisaiClick(cocos2d::Ref *pSender)
{
    if(TAG_BISAI == m_currentTag)
        return;
    
    resetBtnState();
    m_currentTag = TAG_BISAI;
    bisai->setPressIconShow(true);
    
    PersonCenterLayer* layer = PersonCenterLayer::create();
    layer->setPosition(Vec2(CHILD_OFFSET_X, CHILD_OFFSET_Y));
    addChild(layer, 10, TAG_BISAI);
}

void PersonCenterBase::SetClick(cocos2d::Ref *pSender)
{
    
}

void PersonCenterBase::BackClick(cocos2d::Ref *pSender)
{
    MainScene* main = dynamic_cast<MainScene*>(getParent());
    main->BackToLoginLayer(MainScene::TAG_LAYER_PERSON);
}

////////////////////////////////////////////////////////////////////
// 个人资料
////////////////////////////////////////////////////////////////////
PersonInfo::PersonInfo()
{
    
}

PersonInfo::~PersonInfo()
{
    
}

bool PersonInfo::init()
{
    if(!Layer::init())
        return false;
    
    Sprite* iconBack = Sprite::create("touxiang002.png");
    iconBack->setPosition(Vec2(winSize.width * 0.5f - 350, winSize.height * 0.5f + 20));
    iconBack->setScale(0.6f);
    addChild(iconBack);
    
    //Sprite* icon = Sprite::create("morentouxiang01.png");
    //icon->setPosition(Vec2(winSize.width * 0.5f - 350, winSize.height * 0.5f + 20));
    //icon->setScale(0.6f);
    //addChild(icon, 1);
    
    Button* changeHead = Button::createBtnWithSpriteFrameName("set_head_lb.png", false);
    changeHead->setPosition(Vec2(winSize.width * 0.5f - 350, winSize.height * 0.5f - 80));
    changeHead->setOnClickCallback(callfuncO_selector(PersonInfo::ChangeHead), this);
    changeHead->setScale(0.6f);
    addChild(changeHead, 1);
    
    Sprite* male = Sprite::create("male.png");
    male->setPosition(Vec2(winSize.width * 0.5f - 450, winSize.height * 0.5f - 150));
    male->setScale(0.6f);
    addChild(male, 1);
    
    CCLabelTTF* name = CCLabelTTF::create("B0B69845026", "STXingkai.ttf", 36);
    name->setColor(Color3B(1, 1, 1));
    name->setAnchorPoint(Vec2(0,0));
    name->setPosition(Vec2(winSize.width * 0.5f - 430, winSize.height * 0.5f - 170));
    addChild(name, 1);
    
    Sprite* disBack = Sprite::create("dis_frame.png");
    disBack->setPosition(Vec2(winSize.width * 0.5f - 340, winSize.height * 0.5f - 220));
    disBack->setScale(0.6f);
    addChild(disBack, 1);
    
    Sprite* guoqi = Sprite::create("guoqi-001.png");
    Size disSize = disBack->getContentSize();
    guoqi->setPosition(Vec2(disSize.width * 0.5f, disSize.height * 0.5f));
    //guoqi->setScale(0.6f);
    disBack->addChild(guoqi, 1);
    
    Sprite* conBack = Sprite::create("dis_frame.png");
    conBack->setPosition(Vec2(winSize.width * 0.5f - 340, winSize.height * 0.5f - 290));
    conBack->setScale(0.6f);
    addChild(conBack, 1);
    
    CCLabelTTF* content = CCLabelTTF::create("这家伙很懒，什么都没有留下", "STXingkai.ttf", 36);
    content->setColor(Color3B(1, 1, 1));
    //content->setAnchorPoint(Vec2(0,0));
    content->setPosition(Vec2(disSize.width * 0.5f, disSize.height * 0.5f));
    conBack->addChild(content, 1);
    
    // splite
    Sprite* splite = Sprite::create("splite.png");
    splite->setPosition(Vec2(winSize.width * 0.5f - CHILD_OFFSET_X, winSize.height * 0.5f - CHILD_OFFSET_Y));
    splite->setScale(0.6f);
    addChild(splite, 1);
    
    //右侧
    Sprite* dengjiTitle = Sprite::create("jinhuadengji01.png");
    dengjiTitle->setPosition(Vec2(winSize.width * 0.5f + 80, winSize.height * 0.5f + 80));
    dengjiTitle->setScale(0.6f);
    addChild(dengjiTitle, 1);
    
    //铜钱
    Sprite* copperlb = Sprite::create("tongqian001.png");
    copperlb->setPosition(Vec2(winSize.width * 0.5f + 55, winSize.height * 0.5f + 35));
    copperlb->setScale(0.6f);
    addChild(copperlb, 1);
    
    CCLabelTTF* copLabel = CCLabelTTF::create("2", "STXingkai.ttf", 29);
    copLabel->setColor(Color3B(1, 1, 1));
    copLabel->setPosition(Vec2(winSize.width * 0.5f + 130, winSize.height * 0.5f + 35));
    addChild(copLabel, 1);
    
    Sprite* copIcon = Sprite::create("copper.png");
    copIcon->setPosition(Vec2(winSize.width * 0.5f + 180, winSize.height * 0.5f + 35));
    copIcon->setScale(0.6f);
    addChild(copIcon, 1);
    
    //段位
    Sprite* duanweilb = Sprite::create("duanwei001.png");
    duanweilb->setPosition(Vec2(winSize.width * 0.5f + 55, winSize.height * 0.5f - 10));
    duanweilb->setScale(0.6f);
    addChild(duanweilb, 1);
    
    //此处先写死
    Sprite* dwIcon = Sprite::create("001duanwei.png");
    dwIcon->setPosition(Vec2(winSize.width * 0.5f + 115, winSize.height * 0.5f - 10));
    dwIcon->setScale(0.6f);
    addChild(dwIcon, 1);
    
    Sprite* dwtext = Sprite::create("001duanwei02.png");
    dwtext->setPosition(Vec2(winSize.width * 0.5f + 155, winSize.height * 0.5f -10));
    dwtext->setScale(0.6f);
    addChild(dwtext, 1);
    
    
    // mvp数
    Sprite* mvplb = Sprite::create("zongMVPshu001.png");
    mvplb->setPosition(Vec2(winSize.width * 0.5f + 80, winSize.height * 0.5f - 55));
    mvplb->setScale(0.6f);
    addChild(mvplb, 1);
    
    Sprite* mvpIcon = Sprite::create("mvp.png");
    mvpIcon->setPosition(Vec2(winSize.width * 0.5f + 160, winSize.height * 0.5f - 55));
    mvpIcon->setScale(0.6f);
    addChild(mvpIcon, 1);
    
    CCLabelTTF* mvpLabel = CCLabelTTF::create("0", "STXingkai.ttf", 29);
    mvpLabel->setColor(Color3B(1, 1, 1));
    mvpLabel->setPosition(Vec2(winSize.width * 0.5f + 200, winSize.height * 0.5f - 55));
    addChild(mvpLabel, 1);
    
    
    // 总轮数
    Sprite* lunshulb = Sprite::create("zonglunshu001.png");
    lunshulb->setPosition(Vec2(winSize.width * 0.5f + 70, winSize.height * 0.5f - 95));
    lunshulb->setScale(0.6f);
    addChild(lunshulb, 1);
    
    CCLabelTTF* lunLabel = CCLabelTTF::create("1", "STXingkai.ttf", 29);
    lunLabel->setColor(Color3B(1, 1, 1));
    lunLabel->setPosition(Vec2(winSize.width * 0.5f + 140, winSize.height * 0.5f - 95));
    addChild(lunLabel, 1);
    
    // 总冠军数
    Sprite* winlb = Sprite::create("zongguanjunshu001.png");
    winlb->setPosition(Vec2(winSize.width * 0.5f + 80, winSize.height * 0.5f - 140));
    winlb->setScale(0.6f);
    addChild(winlb, 1);
    
    CCLabelTTF* winLabel = CCLabelTTF::create("1", "STXingkai.ttf", 29);
    winLabel->setColor(Color3B(1, 1, 1));
    winLabel->setPosition(Vec2(winSize.width * 0.5f + 150, winSize.height * 0.5f - 140));
    addChild(winLabel, 1);
    
    
    // 总吞噬人数
    Sprite* playerlb = Sprite::create("zongtunshirenshu001.png");
    playerlb->setPosition(Vec2(winSize.width * 0.5f + 90, winSize.height * 0.5f - 185));
    playerlb->setScale(0.6f);
    addChild(playerlb, 1);
    
    CCLabelTTF* playerLabel = CCLabelTTF::create("48", "STXingkai.ttf", 29);
    playerLabel->setColor(Color3B(1, 1, 1));
    playerLabel->setPosition(Vec2(winSize.width * 0.5f + 190, winSize.height * 0.5f - 185));
    addChild(playerLabel, 1);
    
    // 总吞噬数
    Sprite* eatlb = Sprite::create("zongtunshishu001.png");
    eatlb->setPosition(Vec2(winSize.width * 0.5f + 80, winSize.height * 0.5f - 225));
    eatlb->setScale(0.6f);
    addChild(eatlb, 1);
    
    CCLabelTTF* eatLabel = CCLabelTTF::create("48", "STXingkai.ttf", 29);
    eatLabel->setColor(Color3B(1, 1, 1));
    eatLabel->setPosition(Vec2(winSize.width * 0.5f + 170, winSize.height * 0.5f - 225));
    addChild(eatLabel, 1);
    
    // 最大体重
    Sprite* weightlb = Sprite::create("zuidatizhong.png");
    weightlb->setPosition(Vec2(winSize.width * 0.5f + 80, winSize.height * 0.5f - 270));
    weightlb->setScale(0.6f);
    addChild(weightlb, 1);
    
    CCLabelTTF* weightLabel = CCLabelTTF::create("50千克", "STXingkai.ttf", 29);
    weightLabel->setColor(Color3B(1, 1, 1));
    weightLabel->setPosition(Vec2(winSize.width * 0.5f + 200, winSize.height * 0.5f - 270));
    addChild(weightLabel, 1);
    
//    InputLabel* nick = InputLabel::createText("", PointMake(0, -3.0f), Size(400, 80));
//    nick->setPosition(Vec2(winSize.width * 0.5f - 350, winSize.height * 0.5 - 200));
//    nick->setFontSize(25.0f);
//    addChild(nick, 1, 101);
    
    
    
    return true;
}

void PersonInfo::ChangeHead(cocos2d::Ref *pSender)
{
    
}


////////////////////////////////////////////////////////
///PersonXinix
////////////////////////////////////////////////////////
PersonXinxi::PersonXinxi()
{
    
}

PersonXinxi::~PersonXinxi()
{
    
}

bool PersonXinxi::init()
{
    if(!Layer::init())
        return false;
    
    Sprite* iconBack = Sprite::create("touxiang002.png");
    iconBack->setPosition(Vec2(winSize.width * 0.5f - 350, winSize.height * 0.5f - 10));
    iconBack->setScale(0.6f);
    addChild(iconBack);
    
    //Sprite* icon = Sprite::create("morentouxiang01.png");
    //icon->setPosition(Vec2(winSize.width * 0.5f - 350, winSize.height * 0.5f - 10));
    //icon->setScale(0.6f);
    //addChild(icon, 1);
    
    Sprite* guoqi = Sprite::create("guoqi-001.png");
    guoqi->setPosition(Vec2(winSize.width * 0.5f - 350, winSize.height * 0.5f - 110));
    //guoqi->setScale(0.6f);
    addChild(guoqi, 1);
    
    Sprite* changeTitle = Sprite::create("qiehuanyonghu01.png");
    changeTitle->setPosition(Vec2(winSize.width * 0.5f - 430, winSize.height * 0.5f - 180));
    changeTitle->setScale(0.6f);
    addChild(changeTitle, 1);
    
    Sprite* changeFrame = Sprite::create("change_frame.png");
    changeFrame->setPosition(Vec2(winSize.width * 0.5f - 310, winSize.height * 0.5f - 250));
    changeFrame->setScale(0.6f);
    addChild(changeFrame, 1);
    
    CCLabelTTF* name = CCLabelTTF::create("B0B69845026", "STXingkai.ttf", 60);
    name->setColor(Color3B(255, 255, 255));
    Size size = changeFrame->getContentSize();
    name->setPosition(Vec2(size.width * 0.5f - 80, size.height * 0.5f));
    changeFrame->addChild(name, 1);
    
    Button* downBtn = Button::createBtnWithSpriteFrameName("change_down.png", false);
    downBtn->setPosition(Vec2(size.width * 0.5f + 190, size.height * 0.5f));
    downBtn->setOnClickCallback(callfuncO_selector(PersonXinxi::ChangePlayer), this);
    changeFrame->addChild(downBtn, 1);
    
    // splite
    Sprite* splite = Sprite::create("splite.png");
    splite->setPosition(Vec2(winSize.width * 0.5f - CHILD_OFFSET_X, winSize.height * 0.5f - CHILD_OFFSET_Y));
    splite->setScale(0.6f);
    addChild(splite, 1);
    
    // 右侧
    Sprite* registTitle = Sprite::create("zhucechengzhengshiyonghu001.png");
    registTitle->setPosition(Vec2(winSize.width * 0.5 + 200, winSize.height * 0.5f + 60));
    registTitle->setScale(0.6f);
    addChild(registTitle, 1);
    
    Sprite* registCont = Sprite::create("yonghuzhucexiangqing002.png");
    registCont->setPosition(Vec2(winSize.width * 0.5 + 200, winSize.height * 0.5f - 100));
    registCont->setScale(0.6f);
    addChild(registCont, 1);
    
    Button* registBtn = Button::createBtnWithSpriteFrameName("register_btn.png", false);
    registBtn->setPosition(Vec2(winSize.width * 0.5f + 200, winSize.height * 0.5f - 250));
    registBtn->setScale(0.6f);
    registBtn->setOnClickCallback(callfuncO_selector(PersonXinxi::RegisterClick), this);
    addChild(registBtn, 1);
    
    return true;
}

void PersonXinxi::ChangePlayer(cocos2d::Ref *pSender)
{
    
}

void PersonXinxi::RegisterClick(cocos2d::Ref *pSender)
{
    
}

////////////////////////////////////////////////////////
/// personrongyu
////////////////////////////////////////////////////////
PersonRongyu::PersonRongyu()
{
    
}

PersonRongyu::~PersonRongyu()
{
    
}

bool PersonRongyu::init()
{
    if(!Layer::init())
        return false;
    
    Sprite* rongyu_base = Sprite::create("rongyu_base.png");
    rongyu_base->setPosition(Vec2(winSize.width * 0.5 - CHILD_OFFSET_X, winSize.height * 0.5f - CHILD_OFFSET_Y));
    rongyu_base->setScale(0.6f);
    addChild(rongyu_base, 1);
    
    CCLabelTTF* name = CCLabelTTF::create("第7赛季", "STXingkai.ttf", 36);
    name->setColor(Color3B(0, 0, 0));
    name->setPosition(Vec2(winSize.width * 0.5f - CHILD_OFFSET_X, winSize.height * 0.5f + 20));
    addChild(name, 1);
    
    Sprite* star = Sprite::create("xingxing1.png");
    star->setPosition(Vec2(winSize.width * 0.5 - CHILD_OFFSET_X, winSize.height * 0.5f - 20));
    //star->setScale(0.6f);
    addChild(star, 1);
    
    Sprite* icon = Sprite::create("001duanwei.png");
    icon->setPosition(Vec2(winSize.width * 0.5 - CHILD_OFFSET_X, winSize.height * 0.5f - 100));
    icon->setScale(3.0f);
    addChild(icon, 1);
    
    Sprite* qulity = Sprite::create("001duanwei02.png");
    qulity->setPosition(Vec2(winSize.width * 0.5f - CHILD_OFFSET_X, winSize.height * 0.5f - 220));
    qulity->setScale(1.2f);
    addChild(qulity, 1);
    
    CCLabelTTF* dengji = CCLabelTTF::create("未上榜", "STXingkai.ttf", 36);
    dengji->setColor(Color3B(0, 0, 0));
    dengji->setPosition(Vec2(winSize.width * 0.5f - CHILD_OFFSET_X, winSize.height * 0.5f - 255));
    addChild(dengji, 1);
    
    return true;
}


////////////////////////////////////////////////////////
// 记录
PersonCenterLayer::PersonCenterLayer()
{
    infos.clear();
    
    bisaiInfo info1;
    info1.m_id = 1;
    info1.m_nickName = "了不起的球球";
    info1.m_lastTime = "5天前";
    info1.m_rank = "37";
    info1.m_weight = "0毫克";
    info1.m_number = "0";
    info1.m_duration = "33秒";
    info1.m_copper = "0";
    infos.push_back(info1);
    
    bisaiInfo info2;
    info2.m_id = 2;
    info2.m_nickName = "武大也疯狂";
    info2.m_lastTime = "8天前";
    info2.m_rank = "17";
    info2.m_weight = "0毫克";
    info2.m_number = "89";
    info2.m_duration = "1分58秒";
    info2.m_copper = "0";
    infos.push_back(info2);
    
    bisaiInfo info3;
    info3.m_id = 3;
    info3.m_nickName = "阳光下的日子";
    info3.m_lastTime = "9天前";
    info3.m_rank = "56";
    info3.m_weight = "0毫克";
    info3.m_number = "45";
    info3.m_duration = "48秒";
    info3.m_copper = "0";
    infos.push_back(info3);
    
    bisaiInfo info4;
    info4.m_id = 4;
    info4.m_nickName = "飞行日记";
    info4.m_lastTime = "10天前";
    info4.m_rank = "28";
    info4.m_weight = "0毫克";
    info4.m_number = "5";
    info4.m_duration = "55秒";
    info4.m_copper = "4";
    infos.push_back(info4);
    
    bisaiInfo info5;
    info5.m_id = 5;
    info5.m_nickName = "批发初吻";
    info5.m_lastTime = "11天前";
    info5.m_rank = "30";
    info5.m_weight = "10毫克";
    info5.m_number = "10";
    info5.m_duration = "2分钟";
    info5.m_copper = "1";
    infos.push_back(info5);
}

PersonCenterLayer::~PersonCenterLayer()
{
    
}

bool PersonCenterLayer::init()
{
    if(!Layer::init())
        return false;
    
    //LayerColor* color = LayerColor::create(Color4B(255, 0, 0, 100), 1036, 460);
//    LayerColor* color = LayerColor::create(Color4B(0, 0, 0, 255), 1036, 460);
//    color->setPosition(Vec2(0,0));
//    addChild(color,0);
    
    Sprite* title_base = Sprite::create("title_back.png");
    title_base->setPosition(Vec2(winSize.width * 0.5f - CHILD_OFFSET_X, winSize.height - 200 ));
    title_base->setScale(0.6f);
    addChild(title_base, 1);
    
    Sprite* title_nick = Sprite::create("title_nick.png");
    title_nick->setPosition(Vec2(180, winSize.height - 200));
    title_nick->setScale(0.6f);
    addChild(title_nick, 1);
    
    Sprite* title_rank = Sprite::create("rank_title.png");
    title_rank->setPosition(Vec2(330, winSize.height - 200));
    title_rank->setScale(0.6f);
    addChild(title_rank, 1);
    
    Sprite* title_weight = Sprite::create("title_weight.png");
    title_weight->setPosition(Vec2(450, winSize.height - 200));
    title_weight->setScale(0.6f);
    addChild(title_weight, 1);
    
    Sprite* title_num = Sprite::create("tunshirenshu-002.png");
    title_num->setPosition(Vec2(600, winSize.height - 200));
    title_num->setScale(0.6f);
    addChild(title_num, 1);
    
    Sprite* title_duration = Sprite::create("cunhuoshijian-002.png");
    title_duration->setPosition(Vec2(750, winSize.height - 200));
    title_duration->setScale(0.6f);
    addChild(title_duration, 1);
    
    Sprite* title_copper = Sprite::create("tongqian-002.png");
    title_copper->setPosition(Vec2(900, winSize.height - 200));
    title_copper->setScale(0.6f);
    addChild(title_copper, 1);
    
    TableView* tableView = TableView::create(this, getTableSize());
    //tableView->setTouchPriority(MAIN_TABLEVIEW_ACTIVE);
    tableView->setDirection(ScrollView::Direction::VERTICAL);
    //tableView->setPosition(Vec2(winSize.width * 0.5f - CHILD_OFFSET_X, winSize.height * 0.5f - CHILD_OFFSET_Y));
    tableView->setPosition(Vec2(-20,0));
    tableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
    tableView->setDelegate(this);
    addChild(tableView, 2, 101);
    tableView->reloadData();
    
    return true;
}

Size PersonCenterLayer::getTableSize()
{
    return Size(winSize.width - 2 * CHILD_OFFSET_X+40, winSize.height - 2 * CHILD_OFFSET_Y - 20);
}

void PersonCenterLayer::tableCellTouched(cocos2d::extension::TableView *table, cocos2d::extension::TableViewCell *cell)
{
    
}

TableViewCell* PersonCenterLayer::tableCellAtIndex(cocos2d::extension::TableView *table, ssize_t idex)
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

void PersonCenterLayer::createTableViewCell(cocos2d::Node *cell, cocos2d::extension::TableView *table, int idex)
{
    int left = idex % 2;
    Sprite* table_bg = NULL;
    if(left == 0)
        table_bg = Sprite::create("bisai_cell_back1.png");
    else
        table_bg = Sprite::create("bisai_cell_back2.png");
    if(table)
    {
        table_bg->setScale(0.6f);
        table_bg->setPosition(Vec2(20,40));
        cell->addChild(table_bg,1);
        
        Size size = table_bg->getContentSize() * 0.6;
        
        bisaiInfo info = infos[idex];
        
        //Sprite* icon = Sprite::create("morentouxiang01.png");
        //icon->setPosition(Vec2(70 - size.width * 0.5f+20, 40));
        //icon->setScale(0.4f);
        //cell->addChild(icon, 1);
        
        CCLabelTTF* nick_name = CCLabelTTF::create(info.m_nickName.c_str(), "STXingkai.ttf", 29);
        nick_name->setColor(Color3B(255, 255, 255));
        nick_name->setAnchorPoint(Vec2(0,0));
        nick_name->setPosition(Vec2(130 - size.width * 0.5f+20, 50));
        cell->addChild(nick_name, 1);
        
        CCLabelTTF* last_Time = CCLabelTTF::create(info.m_lastTime.c_str(), "STXingkai.ttf", 24);
        last_Time->setColor(Color3B(255, 255, 255));
        last_Time->setAnchorPoint(Vec2(0,0));
        last_Time->setPosition(Vec2(130 - size.width * 0.5f+20, 10));
        cell->addChild(last_Time, 1);
        
        CCLabelTTF* rank = CCLabelTTF::create(info.m_rank.c_str(), "STXingkai.ttf", 29);
        rank->setColor(Color3B(255, 255, 255));
        rank->setAnchorPoint(Vec2(0,0));
        rank->setPosition(Vec2(320 - size.width * 0.5f+20, 30));
        cell->addChild(rank, 1);
        
        CCLabelTTF* weight = CCLabelTTF::create(info.m_weight.c_str(), "STXingkai.ttf", 29);
        weight->setColor(Color3B(255, 255, 255));
        weight->setAnchorPoint(Vec2(0,0));
        weight->setPosition(Vec2(420 - size.width * 0.5f+20, 30));
        cell->addChild(weight, 1);
        
        CCLabelTTF* num = CCLabelTTF::create(info.m_number.c_str(), "STXingkai.ttf", 29);
        num->setColor(Color3B(255, 255, 255));
        num->setAnchorPoint(Vec2(0,0));
        num->setPosition(Vec2(90, 30));
        cell->addChild(num, 1);
        
        CCLabelTTF* duration = CCLabelTTF::create(info.m_duration.c_str(), "STXingkai.ttf", 29);
        duration->setColor(Color3B(255, 255, 255));
        duration->setAnchorPoint(Vec2(0,0));
        duration->setPosition(Vec2(220, 30));
        cell->addChild(duration, 1);
        
        CCLabelTTF* coppor = CCLabelTTF::create(info.m_copper.c_str(), "STXingkai.ttf", 29);
        coppor->setColor(Color3B(255, 255, 255));
        coppor->setAnchorPoint(Vec2(0,0));
        coppor->setPosition(Vec2(400, 30));
        cell->addChild(coppor, 1);
    }
}

Size PersonCenterLayer::cellSizeForTable(cocos2d::extension::TableView *table)
{
    Size tableSize = getTableSize();
    return Size(tableSize.width, tableSize.height / 5);
}

ssize_t PersonCenterLayer::numberOfCellsInTableView(cocos2d::extension::TableView *table)
{
    return infos.size();
}

void PersonCenterLayer::scrollViewDidScroll(cocos2d::extension::ScrollView *view)
{
    
}

void PersonCenterLayer::scrollViewDidZoom(cocos2d::extension::ScrollView *view)
{
    
}




