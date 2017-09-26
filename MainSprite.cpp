//
//  MainSprite.cpp
//  qiuFight
//
//  Created by 张跃东 on 16/2/29.
//
//

#include "MainSprite.h"
#include "Global.h"
#include "GridLayer.h"
#include "Resources.h"
#include "MainScene.h"

#include "UI/CocosGUI.h"
#include "editor-support/cocostudio/CocoStudio.h"

#define BACK_IMG_FILE_PRE  "Big_color_"
#define FRONT_IMG_FILE_PRE  "hero_"
#define DURATION_TIMES  6
#define NANME_SIZE  30

MainSprite::MainSprite()
{
    
	m_isImageHead = false;
	m_sp_scale = 1;
	m_times = DURATION_TIMES + 1;
	heroID = 0;
	mBaozi = 0;
	mGuanghuan = 0;
	mCanying = 0;
}

void MainSprite::reset()
{
	m_isImageHead = false;
	m_sp_scale = 1;
	m_times = DURATION_TIMES + 1;
	heroID = 0;
	mBaozi = 0;
	mGuanghuan = 0;
	mCanying = 0;
	m_sprID = 0;
}
MainSprite::~MainSprite()
{
    
}
bool MainSprite::init()
{
    if(!Node::init())
        return false;
    
	this->scheduleUpdate();
    int index = Global::getInstance()->GetMainPicIndex();
	
	
	
	//合并代码用--0924--注册与组队 start======================================================================
	if (index > 40)
	{
		index = Global::getInstance()->getRand(MAXIMUM_PICTURE_NUM);
	}
	//合并代码用--0924--注册与组队 end======================================================================
	
    
    char temp[32];
    sprintf(temp, "%s%d.png", BACK_IMG_FILE_PRE, index);
    //sprintf(temp, "%s%d.png", FRONT_IMG_FILE_PRE, index);
    //MainSprite* sprite = new MainSprite();
    //if(sprite && sprite->initWithFile(temp))
        //if(sprite)
    //{
    Sprite* image = Sprite::create(temp);
    //image->setAnchorPoint(Vec2(0, 0));
    addChild(image, 1, 14);
    //}
  
    
    return true;
}
/*
MainSprite* MainSprite::createWithIDX()
{
    int index = Global::getInstance()->GetMainPicIndex();
    
    char temp[32];
    sprintf(temp, "%s%d.png", BACK_IMG_FILE_PRE, index);
    MainSprite* sprite = new MainSprite();
    //if(sprite && sprite->initWithFile(temp))
    //if(sprite)
    {
        //Sprite* image = Sprite::create(temp);
        //image->setAnchorPoint(Vec2(0, 0));
        //sprite->addChild(image, 2, 14);
        
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return NULL;
}
*/
void MainSprite::setUpdateInfo(uint32_t nodeId, cocos2d::Point oldPos, cocos2d::Point destPos)
{
    m_sprID = nodeId;
    m_oldPos = oldPos;
    m_destPos = destPos;
    m_diff = ccpSub(destPos, oldPos) / DURATION_TIMES;
    m_times = 1;
}

void MainSprite::resetState()
{
    m_times = DURATION_TIMES + 1;
}

void MainSprite::update(float ft)
{
    //log("float update duration is:%f", ft);
    if(m_times > DURATION_TIMES)
    {
        return;
    }
    
    Point pos ;
    MainScene* scene = (MainScene*)getParent()->getParent();
    
    if( m_times == DURATION_TIMES )
    {
        pos = m_destPos;
    }
    else
    {
        pos = ccpAdd(m_oldPos, m_diff * m_times);
    }
    GridLayer* grid = dynamic_cast<GridLayer*>(getParent());
    grid->updateMainPos(m_sprID, pos);
    
    //log("pos:(%f,%f)",pos.x,pos.y);
    
    m_times++;
    
}

void MainSprite::setPlayerUpdate(uint32_t nodeId, cocos2d::Point destPos)
{
    m_sprID = nodeId;
    m_destPos = destPos;
    
    CCDelayTime * delayAction = CCDelayTime::create(0.02f);
    CCCallFunc * callFunc = CCCallFunc::create(this, callfunc_selector(MainSprite::updateMainPos));
    this->runAction(Sequence::createWithTwoActions(delayAction, callFunc));
}

void MainSprite::updateMainPos()
{
    GridLayer* grid = dynamic_cast<GridLayer*>(getParent());
    grid->updateMainPos(m_sprID, m_destPos);
}

void MainSprite::setIamgeHead(bool flag)
{
    m_isImageHead = flag;
}

bool MainSprite::getIamgeHead()
{
    return m_isImageHead;
}

void MainSprite::addPlayerImage(int hero,int guanghuan,int baozi,int canying)
{
    heroID = hero;
    mGuanghuan = guanghuan;
    mBaozi = baozi;
    mCanying = canying;
    //int index = Global::getInstance()->GetMainPicIndex();
    
    //char temp[32];
    //sprintf(temp, "%s%d.png", FRONT_IMG_FILE_PRE, index);
    //Sprite* image = Sprite::create(temp);
    //if(image)
    //{
        //image->setAnchorPoint(Vec2(0, 0));
        //addChild(image, 2, 11);
    //}
    //else
    //{
        //m_isImageHead = false;
    //}
    bool isShowIcon = false;
    //Shenshou++;
    if (heroID) {
        isShowIcon = true;
		nameMap ite = Resource::sharedResource()->getPiFuForID(heroID);
		auto node = CSLoader::createNode(ite.icon);
		auto action = CSLoader::createTimeline(ite.icon);
		if (action)
		{
			action->gotoFrameAndPlay(0, true);
			node->runAction(action);
		}
		addChild(node, 2, 11);

		getChildByTag(14)->setVisible(false);
    }
    
    if (mGuanghuan)
    {
        isShowIcon = true;

		item ite = Resource::sharedResource()->getItemForID(mGuanghuan);
		auto node = CSLoader::createNode(ite.itemIcon);
		auto action = CSLoader::createTimeline(ite.itemIcon);
		if (action)
		{
			action->gotoFrameAndPlay(0, true);
			node->runAction(action);
		}
		addChild(node, 2, 15);

		getChildByTag(14)->setVisible(false);
    }
    
    if(isShowIcon == false)
    {
        m_isImageHead = false;
    }
}

void MainSprite::removePlayerImage()
{
    removeChildByTag(11);
    removeChildByTag(12);
    removeChildByTag(13);
    removeChildByTag(15);
    getChildByTag(14)->setVisible(true);
}

void MainSprite::setName(std::string name)
{
    NameColor color = Global::getInstance()->GetNameColor(name);
    std::string icon = Global::getInstance()->ComPlayerName(name);
	if (icon.size() > 0) {
        removeChildByTag(14, true);

		auto node = CSLoader::createNode(icon);
		auto action = CSLoader::createTimeline(icon);
		if (action)
		{
			action->gotoFrameAndPlay(0, true);
			node->runAction(action);
		}
		addChild(node, 1, 14);
    }
    //Size size = getContentSize();

    /*int nameSize = 130;
    if (nameLen) {
        nameSize = 600/nameLen;
    }*/
    
    //CCLOG("name:%s",name.c_str());
	CCLabelTTF* namelb = CCLabelTTF::create(name, "STXingkai.ttf", NANME_SIZE);
    namelb->setColor(Color3B(color.colorR, color.colorG, color.colorB));
    //namelb->setAnchorPoint(Vec2(0,-2));
    addChild(namelb, 5, 38396);
    
	updateNameSize();
}

void MainSprite::setSpSize(float size)
{
    m_sp_scale = size;
}

float MainSprite::getSpSize()
{
    return m_sp_scale;
}

void MainSprite::setOriginPos(cocos2d::Point pos)
{
    
}

void MainSprite::setSize(cocos2d::Size size)
{
    
}

void MainSprite::updatePos(cocos2d::Point pos)
{
    
}


void MainSprite::setScale(float scale)
{
	auto sp = this->getChildByTag(14);
	sp->setScale(scale);

	updateNameSize();
}

void MainSprite::updateNameSize()
{
	float scale = 1;
	auto node = this->getChildByTag(14);
	while (node)
	{
		float s = node->getScale();
		scale = scale * s;
		node = node->getParent();
	}
	

	auto namelb = (CCLabelTTF*)this->getChildByTag(38396);
	if (namelb)
	{
		float s = 100 *  scale;
		if (s < NANME_SIZE)
		{
			s = NANME_SIZE;
		}
		namelb->setFontSize(s);
		if (heroID)
		{
			namelb->setPositionY((314 / 2 + 50)* scale);
		}
		else
		{
			namelb->setPositionY(0);
		}
		
	}
}