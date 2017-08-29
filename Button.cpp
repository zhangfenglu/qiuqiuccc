#include "Button.h"
#include "Global.h"

Button::~Button()
{
	if (isEffecttype)
	{
		
	}
}


Button* Button::createBtn(Node* baseNode,Node* upNode)
{	
	Button* btn = new Button;
	if (btn && btn->init(baseNode,upNode))
	{
		btn->autorelease();
		return btn;
	}
	CC_SAFE_DELETE(btn);
	return NULL;
}

Button* Button::createBtn(std::string iconStr)
{
	
	Button *btn = new Button;
	if (btn && btn->init(iconStr))
	{
		btn->autorelease();
		return btn;
	}
	CC_SAFE_DELETE(btn);
	return NULL;
}

Button* Button::createBtnWithSpriteFrameName(std::string iconStr,bool bPlist)
{
	
	Button *btn = new Button ;
	if (btn && btn->initWithFrameName(iconStr,bPlist))
	{
		btn->autorelease();
		return btn;
	}
	CC_SAFE_DELETE(btn);
	return NULL;
}


Button* Button::createBtnWith2SpriteFrameName(std::string baseStr,std::string upStr,bool bPlist)
{
	
	Button* btn = new Button;
	if (btn && btn->initWith2FrameName(baseStr,upStr, bPlist))
	{
		btn->autorelease();
		return btn;
	}
	CC_SAFE_DELETE(btn);
	return NULL;
}

Button* Button::createBtn(std::string baseStr,std::string upStr)
{
	
	Button* btn = new Button;
	if (btn && btn->init(baseStr,upStr))
	{
		btn->autorelease();
		return btn;
	}
	CC_SAFE_DELETE(btn);
	return NULL;
}

Button* Button::createOtherBtn(std::string baseName, std::string name1, std::string name2, std::string name3)
{

	return NULL;
}


Button* Button::createEffectBtn(const char* baseEffectXmls,const char* baseFirstFrameName,const char* baseAnimateName,const char* upEffectXmls,const char* upFirstFrameName,const char* upAnimateName,const char* upWords)
{
	
	Button* btn = new Button;
	if (btn && btn->init(baseEffectXmls,baseFirstFrameName,baseAnimateName,upEffectXmls,upFirstFrameName,upAnimateName,upWords))
	{
		btn->autorelease();
		return btn;
	}
	CC_SAFE_DELETE(btn);
	return NULL;
}

bool Button::init(Node* baseNode,Node* upNode)
{
	bool bRet = false;
	do 
	{
		m_HandlerPriority = 2048-42;
		bg = (Sprite*)baseNode;
		this->setContentSize(bg->getContentSize());
		bg->addChild(upNode,eUpNodeTag,eUpNodeTag);
		upNode->setPosition(Vec2(bg->getContentSize().width*0.5-upNode->getContentSize().width*0.5,bg->getContentSize().height*0.5 - upNode->getContentSize().height*0.5));
		//upNode->setPosition(Vec2(upNode->getContentSize().width*0.5,upNode->getContentSize().height*0.5));
		this->addChild(bg,eBaseNodeTag,eBaseNodeTag);



		bRet = true;
	} while (0);
	return bRet;
}


bool Button::init(const char* baseEffectXmls,const char* baseFirstFrameName,const char* baseAnimateName,const char* upEffectXmls,const char* upFirstFrameName,const char* upAnimateName,const char* upWords)
{
	bool bRet = false;
	do 
	{
		 mbaseEffectXmls = baseEffectXmls;
		 mupEffectXmls = upEffectXmls;
		 isEffecttype = true;
		m_HandlerPriority = 2048-42;
		mScale = 2.0f;
		bg = Sprite::createWithSpriteFrameName(baseFirstFrameName);
	
		bg->setScale(mScale);
		//this->setContentSize(Size(bg->getContentSize().width*mScale,bg->getContentSize().height*mScale));
		this->setContentSize(bg->getContentSize());
		this->addChild(bg,1,1);
	
		Sprite* upSp = Sprite::createWithSpriteFrameName(upFirstFrameName);
	
		upSp->setScale(mScale);
		this->addChild(upSp,2,2);
	
		
		Sprite* upSprite = Sprite::create(upWords);
		//upSprite->setPosition(Vec2(this->getContentSize().width/2,this->getContentSize().height/2));

		this->addChild(upSprite,3,3);
		upSprite->setPosition(Vec2(0,10.0f));

		bRet = true;
	} while (0);
	return bRet;
}

bool Button::init(std::string baseStr,std::string upStr)
{
	
	bool bRet = false;
	do 
	{	
		Sprite* upSprite;
	
		m_HandlerPriority = 2048-42;
		bg = Sprite::create(baseStr.c_str());


		this->setContentSize(bg->getContentSize());
		
		upSprite = Sprite::create(upStr.c_str());
		
		bg->addChild(upSprite);
		upSprite->setPosition(Vec2(bg->getContentSize().width/2,bg->getContentSize().height/2));
		this->addChild(bg);
		bRet = true;
	} while (0);
	return bRet;
}

bool Button::initOther(std::string baseName, std::string name1, std::string name2, std::string name3)
{

	return false;
}


bool Button::initWith2FrameName(std::string baseStr,std::string upStr,bool bPlist)
{
	m_HandlerPriority = 2048-42;
	bool bRet = false;
	do 
	{	
		Sprite* upSprite;
		if (bPlist)
		{
			bg = Sprite::createWithSpriteFrameName(baseStr.c_str());
		}
		else
		{
			bg = Sprite::create(baseStr.c_str());
		}

		this->setContentSize(bg->getContentSize());
		if (bPlist)
		{
			upSprite = Sprite::createWithSpriteFrameName(upStr.c_str());
		}
		else
		{
			upSprite = Sprite::create(upStr.c_str());
		}
		bg->addChild(upSprite);
		upSprite->setPosition(Vec2(bg->getContentSize().width/2,bg->getContentSize().height/2));
		this->addChild(bg);
		bRet = true;
	} while (0);
	return bRet;
}

bool Button::initWithFrameName(std::string iconStr,bool bPlist)
{
	bool bRet = false;
	do 
	{
		if(bPlist)
		{
			bg = Sprite::createWithSpriteFrameName(iconStr.c_str());
		}
		else
		{
			bg = Sprite::create(iconStr.c_str());
		}
		this->setContentSize(bg->getContentSize());
		this->addChild(bg,1,1);
		bRet = true;
	} while (0);
	return bRet;
}


bool Button::init(std::string iconStr)
{
	m_HandlerPriority = 2048-42;
	bool bRet = false;
	do 
	{
		if (strcmp(iconStr.c_str(),"") == 0)
		{
			bg = Sprite::create();
			bg->setContentSize(Size(200,120));
		}
		else
		{
			bg = Sprite::create(iconStr.c_str());
		}		
		this->setContentSize(bg->getContentSize());
		this->addChild(bg,1,1);
		bRet = true;
	} while (0);
	return bRet;
}

Button *Button::createBtn(std::string baseStr,std::string upStr,std::string moneyIcon,const char* numStr)
{
	Button* btn = new Button();
	if (btn && btn->init(baseStr,upStr,moneyIcon,numStr))
	{
		btn->autorelease();
		return btn;
	}
	CC_SAFE_DELETE(btn);
	return NULL;
}

bool Button::init(std::string baseStr,std::string upStr,std::string moneyIcon,const char* numStr)
{
	bool bRet = false;
	do 
	{	
		Sprite* upSprite;
		m_HandlerPriority = 2048-42;
		bg = Sprite::create(baseStr.c_str());
		this->setContentSize(bg->getContentSize());

		upSprite = Sprite::create(upStr.c_str());
		upSprite->setPosition(Vec2(bg->getContentSize().width/2.0f,bg->getContentSize().height*11/16.0f));
		bg->addChild(upSprite);

		Sprite *moneySprite = Sprite::create(moneyIcon.c_str());
		moneySprite->setPosition(Vec2(bg->getContentSize().width/5.0f,bg->getContentSize().height/4.0f));
		moneySprite->setScale(0.8f);
		bg->addChild(moneySprite);

		std::ostringstream oss;
		oss<<numStr;
		CCLabelBMFont *numLabel = CCLabelBMFont::create(oss.str().c_str(),
			"Graphics/Fonts/UI_yongbinghuashengchuancheng_num.fnt");
			numLabel->setPosition(Vec2(bg->getContentSize().width*2/5.0f,bg->getContentSize().height/4.0f));
		numLabel->setAnchorPoint(Vec2(0,0.5f));	
		bg->addChild(numLabel);
		this->addChild(bg);
		bRet = true;
	} while (0);
	return bRet;
}

//昆仑秘境专用按钮
Button *Button::createHomeBtn(std::string baseStr,std::string upStr,std::string wordIcon)
{
	Button* btn = new Button();
	if (btn && btn->init(baseStr,upStr,wordIcon))
	{
		btn->autorelease();
		return btn;
	}
	CC_SAFE_DELETE(btn);
	return NULL;
}

bool Button::init(std::string baseStr,std::string upStr,std::string wordIcon)
{
	bool bRet = false;
	do 
	{	
		Sprite* upSprite;
		m_HandlerPriority = 2048-1;
		bg = Sprite::create(baseStr.c_str());
		this->setContentSize(bg->getContentSize());

		upSprite = Sprite::create(upStr.c_str());
		upSprite->setPosition(Vec2(bg->getContentSize().width/2.0f,bg->getContentSize().height/2.0));
		bg->addChild(upSprite);

		Sprite *wordSprite = Sprite::create(wordIcon.c_str());
		wordSprite->setAnchorPoint(Vec2(0.5,0));
		wordSprite->setPosition(Vec2(bg->getContentSize().width/2,wordSprite->getContentSize().height));
		//moneySprite->setScale(0.8f);
		bg->addChild(wordSprite);

		this->addChild(bg);
		bRet = true;
	} while (0);
	return bRet;
}

void Button::setIsShow(bool isShow)
{
	this->setVisible(isShow);
	isCanTouch = isShow;
}


//void Button::setOnClickCallback(SEL_CallFuncO cb, Ref * obj)


void Button::onEnter()
{
	Node::onEnter();
	//Director::getInstance()->getTouchDispatcher()->addTargetedDelegate(this,/*m_HandlerPriority*/PRI,true);
	
}
void Button::onExit()
{
	//Director::getInstance()->getTouchDispatcher()->removeDelegate(this);
	Node::onExit();
}

Rect Button::rect()
{
	Size sizeBg = bg->getContentSize();
	return Rect(-sizeBg.width/2,-sizeBg.height/2,sizeBg.width,sizeBg.height);
}

bool Button::containsTouchLocation(Touch* pTouch)
{
	return rect().containsPoint(convertTouchToNodeSpaceAR(pTouch));
}
void Button::setIsCanTouch(bool bl)
{
	isCanTouch = bl;
	if(!isCanTouch && pressbg)
	{
		bg->setVisible(false);
		pressbg->setVisible(true);
	}else if (pressbg)
	{
		bg->setVisible(true);
		pressbg->setVisible(false);
	}
}
void Button::TouchMoreTime(float ft)
{
    click(this);
}
bool  Button::onTouchBegan(Touch *pTouch, Event *pEvent)
{
	this->retain();
	this->autorelease();
	if (containsTouchLocation(pTouch))
	{
		if (!isCanTouch)
		{
			return false;
		}

		if(mIsSelect)
			return false;

		if(m_bIsSpecialEffect = false)
		{
		}
		if (mLockMode && mIsLock)
		{
			return false;
		}
		if (m_bPressChange)
		{
			bg->setVisible(false);
			pressbg->setVisible(true);
		}
		else
		{
			bg->setScale(1.1f*mScale);
		}
		
        if (mIsCanTouchMoreTime) {
            schedule(schedule_selector(Button::TouchMoreTime), 0.1f);
        }
        
		return true;
	}
	return false;
}

void Button::onTouchEnded(Touch *pTouch, Event *pEvent)
{
	this->retain();
	this->autorelease();

	if (containsTouchLocation(pTouch))
	{
		if (!isCanTouch)
		{
			return;
		}
		if (mLockMode)
		{
			lockState();
		}
		
		click(this);
		if (m_needPlayClickEffect)
		{
			Global::getInstance()->PlayEffect("touch.mp3");
		}
       
	}
	if (m_bPressChange)
	{
		bg->setVisible(true);
		pressbg->setVisible(false);
	}
	else
	{
		if(mIsBig)
		{
			bg->setScale(1.1f*mScale);
		}
		else
		{
			bg->setScale(1.0f*mScale);
		}
	}
    if (mIsCanTouchMoreTime) {
        unschedule(schedule_selector(Button::TouchMoreTime));
    }
}

void Button::SetSelect(bool flag)
{
	mIsSelect = flag;
	if(flag)
	{
		bg->setScale(1.1f*mScale);
		bg->setColor(Color3B(255, 255, 255));
	}
	else
	{
		bg->setScale(0.9f*mScale);
		bg->setColor(Color3B(25, 25, 25));
	}

}

void Button::click(Node *node)
{
	if (mClickCallback != NULL)
	{
		CCLOG("=========== CLICK  ==============");
		(clickObj->*mClickCallback)(this);
	}
}



void Button::loadLock(float dt)
{
	unLockState();
}

void Button::lockState()
{
	schedule(schedule_selector(Button::loadLock),mLockDt);
	log("------------------------------------------");
	mIsLock = true;
	loadSp = Sprite::create("New_Graphics/UI_New_liantianfasong_003.png");
	bg->addChild(loadSp,12,1002);
	loadSp->setOpacity(100.0f);
	loadSp->setScale(1.8f);
	loadSp->setPosition(Vec2(this->getContentSize().width*0.5,this->getContentSize().height*0.5));
	CCActionInterval*  action1 = RotateBy::create(0.1f,  -360.0f);
	loadSp->runAction(RepeatForever::create(action1));
	
}

void Button::unLockState()
{
	mIsLock = false;
	unschedule(schedule_selector(Button::loadLock));
	bg->removeChildByTag(1002,true);
}

void Button::setPressIcon(std::string iconStr,bool bPlist)
{
	if(bPlist)
	{
		pressbg = Sprite::createWithSpriteFrameName(iconStr.c_str());
	}
	else
	{
		pressbg = Sprite::create(iconStr.c_str());
	}
	addChild(pressbg,1,1);
	pressbg->setVisible(false);
	m_bPressChange =  true;
}

void Button::setPressEnable(bool b)
{
	isCanTouch = b;
	if(b)
	{
		bg->setVisible(true);
		pressbg->setVisible(false);
	}
	else
	{
		bg->setVisible(false);
		pressbg->setVisible(true);
	}
}

void Button::setPressIconShow(bool b)
{
	if(b)
	{
		m_bPressChange = false;
		bg->setVisible(false);
		pressbg->setVisible(true);
	}
	else
	{
		m_bPressChange = true;
		bg->setVisible(true);
		pressbg->setVisible(false);		
	}
}