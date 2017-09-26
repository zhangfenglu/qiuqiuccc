//
//  FoodSprite.cpp
//  qiuFight
//
//  Created by 张跃东 on 16/3/2.
//1
//

#include "FoodSprite.h"
#include "Common.h"
#include "GridLayer.h"
#include "Resources.h"

#define IMAGE_PRE "color_"
#define BACK_IMG_FILE_PRE  "Big_color_"
#define FRONT_IMG_FILE_PRE  "hero_"
#define DURATION_TIMES  3
#define NANME_SIZE  30

FoodSprite::FoodSprite()
{
    m_spriteID = 0;
    m_isImageHead = false;
    m_times = DURATION_TIMES + 1;
    m_isFood = true;
    heroID = 0;
    mBaozi = 0;
    mGuanghuan = 0;
    mCanying = 0;
    this->scheduleUpdate();
}

FoodSprite::~FoodSprite()
{
    
}
bool FoodSprite::init()
{
    if(!Node::init())
        return false;
    
    return true;
}
void FoodSprite::createWithRGB(uint16_t index, bool isFood,int baozi,std::string icon,std::string name)
{
    int idx = index % MAXIMUM_PICTURE_NUM;
    setImageIndex(idx, isFood);
    char temp[32]={0};
    if(isFood)
    {
        sprintf(temp, "%s%d.png", IMAGE_PRE, idx%8);
        Sprite* image = Sprite::create(temp);
        //image->setAnchorPoint(Vec2(0, 0));
        addChild(image, 1, 14);
    }
    else if(name == "")
    {
		// 如果狍子有皮肤
        if(baozi)
        {
			auto node = CSLoader::createNode(icon);
			auto action = CSLoader::createTimeline(icon);
			if (action)
			{
				action->gotoFrameAndPlay(0, true);
				node->runAction(action);
			}
			addChild(node, 1, 14);
        }else{
            sprintf(temp, "%s%d.png", BACK_IMG_FILE_PRE, 12);
            Sprite* image = Sprite::create(temp);
            //image->setAnchorPoint(Vec2(0, 0));
            addChild(image, 1, 14);
            //CCLOG("tuqiu:%s",temp);
        }
    }else{
        sprintf(temp, "%s%d.png", BACK_IMG_FILE_PRE, index);
        Sprite* image = Sprite::create(temp);
        //image->setAnchorPoint(Vec2(0, 0));
        addChild(image, 1, 14);
        //CCLOG("tuqiu:%s",temp);
    }
    /*
    if (sprite && sprite->initWithFile(temp))
    {
        sprite->setImageIndex(idx, isFood);
        sprite->autorelease();
        return sprite;
    }
     */
}

void FoodSprite::setUpdateInfo(uint32_t nodeId, cocos2d::Point oldPos, cocos2d::Point destPos)
{
    m_spriteID = nodeId;
    m_destPos = destPos;
    m_oldPos = oldPos;
    
    m_diff = ccpSub(destPos, oldPos) / DURATION_TIMES;
    m_times = 1;
}

void FoodSprite::update(float ft)
{
    if(m_times > DURATION_TIMES)
        return;
    
    Point pos;
    if(m_times == DURATION_TIMES)
    {
        pos = m_destPos;
    }
    else
    {
        pos = ccpAdd(m_oldPos, m_diff * m_times);
    }
    
    GridLayer* grid = dynamic_cast<GridLayer*>(getParent());
    grid->updateOtherPos(m_spriteID, pos);
    
    m_times++;
}

void FoodSprite::setImageHead(bool flag)
{
    m_isImageHead = flag;
}

bool FoodSprite::getImageHead()
{
    return m_isImageHead;
}

void FoodSprite::setImageIndex(int index, bool isFood)
{
    m_imageIndex = index;
    m_isFood = isFood;
}

int FoodSprite::getImageIndex()
{
    return m_imageIndex;
}

void FoodSprite::addPlayerImage(int hero,int guanghuan,int baozi,int canying,std::string icon)
{
    //char temp[32];
    //sprintf(temp, "%s%d.png", FRONT_IMG_FILE_PRE, m_imageIndex);
    //Sprite* image = Sprite::create(temp);
    //image->setAnchorPoint(Vec2(0,0));
    //addChild(image, 2, 11);
    
    // 暂时主调
    heroID = hero;
    mGuanghuan = guanghuan;
    mBaozi = baozi;
    mCanying = canying;
    bool isShowIcon = false;
    if (heroID)
    {
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
		auto node = CSLoader::createNode(icon);
		auto action = CSLoader::createTimeline(icon);
		if (action)
		{
			action->gotoFrameAndPlay(0, true);
			node->runAction(action);
		}
		addChild(node, 2, 15);

		getChildByTag(14)->setVisible(false);
    }
    
    if (isShowIcon == false) {
        m_isImageHead = false;
    }
}

void FoodSprite::removePlayerImage()
{
    removeChildByTag(11);
    removeChildByTag(12);
    removeChildByTag(13);
    removeChildByTag(15);
    
    getChildByTag(14)->setVisible(true);
}

void FoodSprite::setName(const char* name)
{
    std::string nameColor = name;
    NameColor color = Global::getInstance()->GetNameColor(nameColor);
    std::string icon = Global::getInstance()->ComPlayerName(nameColor);
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
    int nameLen = (int)strlen(name);
    int nameSize = 0;
    if (nameLen) {
        nameSize = 600/nameLen;
    }
    CCLabelTTF* namelb = CCLabelTTF::create(nameColor.c_str(), "STXingkai.ttf", nameSize);
    namelb->setColor(Color3B(color.colorR, color.colorG, color.colorB));
    //namelb->setPosition(Vec2(size.width * 0.5f, size.height * 0.5f));
    //namelb->setAnchorPoint(Vec2(0,-2));
	addChild(namelb, 3, 38396);
}


void FoodSprite::setScale(float scale)
{
	auto sp = this->getChildByTag(14);
	if (sp)
	{
		sp->setScale(scale);
	}
	updateNameSize();
}

void FoodSprite::updateNameSize()
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
		float s = 100 * scale;
		if (s < NANME_SIZE)
		{
			s = NANME_SIZE;
		}
		namelb->setFontSize(s);
		namelb->setPositionY((314 / 2 + 50)* scale);

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