#ifndef _CEDIT_BOX_H_
#define _CEDIT_BOX_H_
#pragma once

#include "Global.h"

class CInputText : public Layer, public IMEDelegate
{
public:
	enum EidtType
	{
		EIDT_NORMEL,
		EIDT_PASSWORD,
		EIDI_NUM
	};
	CInputText();
	~CInputText();
	virtual void onClickTrackNode(bool bClicked) = 0;

	virtual void registerWithTouchDispatcherEx();
	virtual void keyboardWillShow(IMEKeyboardNotificationInfo& info);
	virtual void keyboardDidHide(IMEKeyboardNotificationInfo& info);
	virtual bool onTouchBegan(Touch *pTouch, Event *pEvent);
	virtual void onTouchEnded(Touch *pTouch, Event *pEvent);
	std::string getEditString();
	std::string getSpaceName(){return mSpaceName;}
	void setEditString(const char* str){mResult = str;}
	void SetMaxNum(int num){mMaxNum = num;}
    void SetMaxFontNum(int num){mMaxFontNum = num;}
	void SetBoxSize(Size  zi);
	void SetEidtType(EidtType tp){mType = tp;}
	bool GetSelect(){return m_IsSelect;}
    void setOnClickCallback(SEL_CallFuncO cb, Ref * obj){ mClickCallback = cb; clickObj = obj;}
protected:
	Node * m_pTrackNode;
	Point  m_beginPos;
	Point  m_endPos;
	EidtType  mType;
	std::string  mSpaceName;
	std::string  mFontName;
	float   mFontSize;
	std::string  mResult;
	int  mMaxNum;
	int  mMaxFontNum;               //最大显示的字符数
	bool  m_IsSelect;
	Sprite *mCursor;
	float  m_MoveFloat;
    SEL_CallFuncO mClickCallback;
    Ref *clickObj;
};

class CEditBox : public CInputText, public TextFieldDelegate
{
public:
	CEditBox();
	~CEditBox();
	virtual void onClickTrackNode(bool bClicked);
	static  CEditBox*  CreateBox(Point pos, Rect rt=Rect(40,0,10,84),const char* str="function/func_input_1.png",EidtType type = EIDT_NORMEL,bool isChinese = false,const char* fontName ="w7.ttf",float fontSize = 30.0f);
	bool InitBox(Point pos,Rect rt,const char* str,bool isChinese,const char* fontName,float fontSize,EidtType type);

	virtual bool onTextFieldAttachWithIME(TextFieldTTF * pSender);
	virtual bool onTextFieldDetachWithIME(TextFieldTTF * pSender);
	virtual bool onTextFieldInsertText(TextFieldTTF * pSender, const char * text, int nLen);
	virtual bool onTextFieldDeleteBackward(TextFieldTTF * pSender, const char * delText, int nLen);
	virtual bool onDraw(TextFieldTTF * pSender);
	//virtual void setPosition(const Point &position){setPosition(position);}
	void  setFontColor(const cocos2d::Color3B &color3b){ ((TextFieldTTF*)m_pTrackNode)->setColor(color3b);}
    void setFontSize(float size){
        //auto ttfConfig = ((TextFieldTTF*)m_pTrackNode)->getTTFConfig();
        //ttfConfig.fontSize = size;
        //((TextFieldTTF*)m_pTrackNode)->setTTFConfigInternal(ttfConfig);
    }
	void  changeText(float fd);
	void  reRunActiorn();
private:
	std::string oldstr;
	int  mTimeCount;
	bool  isPutInChinese;
	float  stringLen;

};

class CEditBoxTool : public ui::EditBox
{
public:
    static CEditBoxTool* Create(const Size& size, ui::Scale9Sprite* pNormal9SpriteBg, ui::Scale9Sprite* pPressed9SpriteBg = NULL, ui::Scale9Sprite* pDisabled9SpriteBg = NULL)
    {
        CEditBoxTool* pRet = new CEditBoxTool();
        
        if (pRet != NULL && pRet->initWithSizeAndBackgroundSprite(size, pNormal9SpriteBg))
        {
            if (pPressed9SpriteBg != NULL)
            {
                //pRet->setBackgroundSpriteForState(pPressed9SpriteBg, ControlButton::State::HIGH_LIGHTED);
                pRet->setBright(true);
            }
            
            if (pDisabled9SpriteBg != NULL)
            {
                //pRet->setBackgroundSpriteForState(pDisabled9SpriteBg, ControlButton::State::DISABLED);
                pRet->setBright(false);
            }
            pRet->autorelease();
        }
        else
        {
            CC_SAFE_DELETE(pRet);
        }
        
        return pRet;
    }
    virtual void registerWithTouchDispatcherEx()
    {
        //TouchDispatcher::getInstance()->addTargetedDelegate(this,PRI,true);
        //Director::getInstance()->getTouchDispatcher()->addTargetedDelegate(this, PRI, true);
    }
};
#endif