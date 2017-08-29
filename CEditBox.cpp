#include "CEditBox.h"
#include "cocos-ext.h"
#include "Global.h"
USING_NS_CC_EXT;


static Rect getRect(Node * pNode)
{
	Rect rc;
	rc.origin = pNode->getPosition();
	rc.size = pNode->getContentSize();
	rc.origin.x -= rc.size.width / 2;
	rc.origin.y -= rc.size.height / 2;
	return rc;
}
CInputText::CInputText() : m_pTrackNode(0)
{
	setTouchEnabled(true);
	mType = EIDT_NORMEL;
	mSpaceName.clear();
	mFontName.clear();
	mFontSize = 0;
	mResult.clear();
	mMaxNum = 300;
	mMaxFontNum = 300;
	m_IsSelect = false;
	m_endPos = Vec2(0,0);
	mCursor = NULL;
	m_MoveFloat = 0.0f;
    clickObj = NULL;
}
CInputText::~CInputText()
{
	CC_SAFE_RELEASE_NULL(m_pTrackNode);
	CC_SAFE_RELEASE_NULL(mCursor);
}
void CInputText::registerWithTouchDispatcherEx()
{
    //TouchDispatcher::getInstance()->addTargetedDelegate(this,PRI,false);
	//Director* pDirector = Director::getInstance();
	//pDirector->getTouchDispatcher()->addTargetedDelegate(this, PRI, false);
}
std::string CInputText::getEditString()
{
	if (mResult == mSpaceName)
	{
		return "";
	}
	return mResult;
}
void CInputText::SetBoxSize(Size  zi)
{
	getChildByTag(3)->setContentSize(zi);
}
void CInputText::keyboardWillShow(IMEKeyboardNotificationInfo& info)
{
	CCLOG("TextInputTest:keyboardWillShowAt(origin:%f,%f, size:%f,%f)",
		info.end.origin.x, info.end.origin.y, info.end.size.width, info.end.size.height);

	if (! m_pTrackNode)
	{
		return;
	}
	Rect rectTracked = getRect(getChildByTag(3));
	//Rect rectTracked = getRect(m_pTrackNode);
	CCLOG("TextInputTest:trackingNodeAt(origin:%f,%f, size:%f,%f)",
		rectTracked.origin.x, rectTracked.origin.y, rectTracked.size.width, rectTracked.size.height);

	// if the keyboard area doesn't intersect with the tracking node area, nothing need to do.
	if (! rectTracked.intersectsRect(info.end))
	{
		return;
	}
	if (!rectTracked.containsPoint(m_endPos))
	{
		return;
	}
	// assume keyboard at the bottom of screen, calculate the vertical adjustment.
    float mY = info.end.getMaxY() - rectTracked.getMinY();
    m_MoveFloat += mY;
	CCLOG("TextInputTest:needAdjustVerticalPosition(%f)", m_MoveFloat);

	// move all the children node of KeyboardNotificationLayer
	Node* node = getParent();
	Point pos = node->getPosition();
	pos.y+=mY;
	node->setPosition(pos);
}
void CInputText::keyboardDidHide(IMEKeyboardNotificationInfo& info)
{
	if (! m_pTrackNode)
	{
		return;
	}
	TextFieldTTF * pTextField = (TextFieldTTF*)m_pTrackNode;
	pTextField->detachWithIME();
	m_IsSelect = false;
	if (mResult == "")
	{
		mResult = mSpaceName;
	}
	pTextField->removeChild(mCursor,true);
	Node* node = getParent();
	Point pos = node->getPosition();
	pos.y-=m_MoveFloat;
	node->setPosition(pos);
	m_MoveFloat = 0.0f;
    
    if (clickObj != NULL)
    {
        CCLOG("=========== CLICK  ==============");
        (clickObj->*mClickCallback)(this);
    }
}
bool CInputText::onTouchBegan(Touch *pTouch, Event *pEvent)
{
	CCLOG("++++++++++++++++++++++++++++++++++++++++++++");
	m_beginPos = pTouch->getLocation();    
	return true;
}
void CInputText::onTouchEnded(Touch *pTouch, Event *pEvent)
{
	if (! m_pTrackNode)
	{
		return;
	}

	Point endPos = pTouch->getLocation();    

	float delta = 10.0f;
	if (::abs(endPos.x - m_beginPos.x) > delta
		|| ::abs(endPos.y - m_beginPos.y) > delta)
	{
		// not click
		m_beginPos.x = m_beginPos.y = -1;
		return;
	}

	// decide the trackNode is clicked.
	Rect rect;
	//Point point = convertTouchToNodeSpaceAR(pTouch);
	m_endPos = convertTouchToNodeSpaceAR(pTouch);
	CCLOG("KeyboardNotificationLayer:clickedAt(%f,%f)", m_endPos.x, m_endPos.y);

	rect = getRect(getChildByTag(3));
	//rect = getRect(m_pTrackNode);
	CCLOG("KeyboardNotificationLayer:TrackNode at(origin:%f,%f, size:%f,%f)",
		rect.origin.x, rect.origin.y, rect.size.width, rect.size.height);

	this->onClickTrackNode(rect.containsPoint(m_endPos));
	CCLOG("----------------------------------");
}

//////EDitBox//////
CEditBox::CEditBox()
{
	oldstr.clear();
	isPutInChinese = false;
	mTimeCount = 0;
	stringLen = 0.0f;
}
CEditBox::~CEditBox()
{
	
}
void CEditBox::onClickTrackNode(bool bClicked)
{
	TextFieldTTF * pTextField = (TextFieldTTF*)m_pTrackNode;

	if (bClicked)
	{
		// TextFieldTTFTest be clicked
		CCLOG("TextFieldTTFDefaultTest:TextFieldTTF attachWithIME");
		pTextField->attachWithIME();
		m_IsSelect = true;
		if (mResult == mSpaceName)
		{
			mResult = "";
		}
        /*
		if(pTextField->isEqual(mCursor->getParent()))
			return;
        */

		pTextField->addChild(mCursor);
		
		mCursor->stopAllActions();
		mCursor->runAction(
			RepeatForever::create(
			Sequence::create(
			CCFadeTo::create(0.2f, 0),
			CCFadeTo::create(0.2f, 255),
			CCDelayTime::create(0.1f),
			NULL)));
	}
	else
	{
		CCLOG("TextFieldTTFDefaultTest:TextFieldTTF detachWithIME");
		pTextField->detachWithIME();
		m_IsSelect = false;
		if (mResult == "")
		{
			mResult = mSpaceName;
		}

		pTextField->removeChild(mCursor,true);
        
        /*if (clickObj != NULL)
        {
            CCLOG("=========== CLICK  ==============");
            (clickObj->*mClickCallback)(this);
        }*/
	}
}
bool CEditBox::InitBox(Point pos,Rect rt,const char* str,bool isChinese,const char* fontName,float fontSize,EidtType type)
{
	isPutInChinese = isChinese;
	mType = type;
	mSpaceName = "";
	mFontName = fontName;
	mFontSize = fontSize;
	mTimeCount = 0;
	oldstr.clear();
	schedule( schedule_selector(CEditBox::changeText));

	Size s = Director::getInstance()->getWinSize();

	Scale9Sprite* mEditBack = Scale9Sprite::create(rt,str);
	mEditBack->setContentSize(Size(400,84));
    mEditBack->setPosition(pos);
	addChild(mEditBack,0,3);

	TextFieldTTF *pTextField = TextFieldTTF::textFieldWithPlaceHolder("",
		fontName,
		fontSize);

	if(!pTextField)
		return false;
	pTextField->retain();
	addChild(pTextField,0,1);
	pTextField->setDelegate(this);
    pTextField->setPosition(pos);
	mResult = mSpaceName;
	CCLabelTTF *mLable = CCLabelTTF::create("","w7.ttf",30);
	addChild(mLable,0,2);
	mLable->setPosition(Vec2(s.width/2,s.height/2+300));
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)    
//	// on android, TextFieldTTF cannot auto adjust its position when soft-keyboard pop up
//	// so we had to set a higher position to make it visable
//	pTextField->setPosition(Vec2(s.width / 2, s.height/2 + 50));
//#else 
//	pTextField->setPosition(Vec2(s.width / 2, s.height / 2));
//#endif

	m_pTrackNode = pTextField;

	mCursor = Sprite::create("enter_guangbiao.png");
	mCursor->retain();

	return true;
}
CEditBox*  CEditBox::CreateBox(Point pos,Rect rt,const char* str,EidtType type,bool isChinese,const char* fontName,float fontSize)
{
	CEditBox *box = new CEditBox;
	
	if(box && box->InitBox(pos,rt,str,isChinese,fontName,fontSize,type))
	{
		box->autorelease();
		return box;
	}
	 CC_SAFE_DELETE(box);
	return NULL;
}
bool CEditBox::onTextFieldAttachWithIME(TextFieldTTF * pSender)
{
	return false;
}
bool CEditBox::onTextFieldDetachWithIME(TextFieldTTF * pSender)
{
	return false;
}
bool CEditBox::onTextFieldInsertText(TextFieldTTF * pSender, const char * text, int nLen)
{
	//CReadString fp;
	// if insert enter, treat as default to detach with ime
	if ('\n' == *text)
	{
		return false;
	}
	// if the textfield's char count more than m_nCharLimit, doesn't insert text anymore.
	std::string aStr = mResult;
	int len = aStr.length();
    //mResult = a2u(aStr.c_str());

	if (len >= mMaxNum)
	{
		return true;
	}
	if (mType == EIDI_NUM)
	{
		if ((*text) <'0' || (*text)>'9')
		{
			return true;
		}
	}
	if (!isPutInChinese)
	{
		if(nLen>1)
		{
			//std::string str = a2u("ÇëÊäÈë×ÖÄ¸»òÊý×Ö");
			//std::string str = a2u(fp.FindStringSLK(905).c_str());
			//((CCLabelTTF*)getChildByTag(2))->setString(str.c_str());
			return true;
		}
	}
	if(isPutInChinese)
	{
		mResult.append(text);
	}else
	{
		mResult.push_back(*text);
	}
	return false;
}
bool CEditBox::onTextFieldDeleteBackward(TextFieldTTF * pSender, const char * delText, int nLen)
{
	mResult.resize(mResult.size()-nLen);
	return false;
}
bool CEditBox::onDraw(TextFieldTTF * pSender)
{
	std::string str;
	//int num = mResult.length();
	std::string aStr = mResult;
	int num = aStr.length();
	if(num>mMaxFontNum)
	{
		str.append(mResult.c_str()+(num-mMaxFontNum),mMaxFontNum);
		pSender->setString(str.c_str());
	}else
		pSender->setString(mResult.c_str());
		//((TextFieldTTF*)m_pTrackNode)->setString(mResult.c_str());

	if(mType == EIDT_PASSWORD && mResult != mSpaceName)
	{
		std::string str = pSender->getString();
		int temp = str.size();
		for (int i = 0;i<temp;i++)
		{
			str[i] = '*';
		}
		pSender->setString(str.c_str());
	}
	if(mCursor)
	{
		Size mSize = m_pTrackNode->getContentSize();
		mCursor->setPosition(Vec2(mSize.width+6,mSize.height/2));
	}
	return false;
}
void  CEditBox::changeText(float fd)
{
	if (getChildByTag(2))
	{
		mTimeCount++;
		if (mTimeCount >= 200)
		{
			mTimeCount = 0;	
			((CCLabelTTF*)getChildByTag(2))->setString("");
		}
	}
}
void  CEditBox::reRunActiorn()
{
	/*
     if(!getChildByTag(1)->getChildByTag(1)->isEqual(mCursor->getParent()))
		return;
     */
	mCursor->stopAllActions();
	mCursor->runAction(
		RepeatForever::create(
		Sequence::create(
		CCFadeTo::create(0.2f, 0),
		CCFadeTo::create(0.2f, 255),
		CCDelayTime::create(0.1f),
		NULL)));
}