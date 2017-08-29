
#include "LabelStroke.h"


LabelStroke * LabelStroke::create(const char* string, const char* fontName, const int fontSize, int strokeSize, Color3B color)
{
	LabelStroke *label = new LabelStroke();
	if (label && label->init(string, fontName, fontSize, strokeSize, color))
	{
		label->autorelease();
		return label;
	}
	CC_SAFE_DELETE(label);
	return NULL;
}

bool LabelStroke::init(const char* string, const char* fontName, const int fontSize, int strokeSize, Color3B color)
{
	//mLabel = CCLabelTTF::create(string, fontName, fontSize);
	//if (mLabel)
	//{
	//	mLabel->setPosition(Vec2::ZERO);
	//	setContentSize(mLabel->getContentSize());

	//	CCRenderTexture * texture = createStroke(mLabel, strokeSize, color);
	//	addChild(texture, 1, 1);
	//	addChild(mLabel, 1, 2);

	//	return true;
	//}

	//return false;

	CCLabelTTF::initWithString(string, fontName, fontSize);
	//enableStroke(color, (float)strokeSize);
	enableShadow(Size(1.5f, -1.5f), 0.9f, 0.3f);
	
	return true;
}

LabelStroke * LabelStroke::create(const char* string, const char* fontName, const int fontSize, const Size& dimensions, 
							CCTextAlignment hAlignment, int strokeSize, Color3B color)
{
	LabelStroke *label = new LabelStroke();
	if (label && label->init(string, fontName, fontSize, dimensions, hAlignment, strokeSize, color))
	{
		label->autorelease();
		return label;
	}
	CC_SAFE_DELETE(label);
	return NULL;
}

bool LabelStroke::init(const char* string, const char* fontName, const int fontSize, const Size& dimensions, CCTextAlignment hAlignment, int strokeSize, Color3B color)
{
	//mLabel = CCLabelTTF::create(string, fontName, fontSize, dimensions, hAlignment);
	//if (mLabel)
	//{
	//	mLabel->setPosition(Vec2::ZERO);
	//	setContentSize(mLabel->getContentSize());

	//	CCRenderTexture * texture = createStroke(mLabel, strokeSize, color);
	//	addChild(texture, 1, 1);
	//	addChild(mLabel, 1, 2);

	//	return true;
	//}

	//return false;

	CCLabelTTF::initWithString(string, fontName, fontSize, dimensions, hAlignment);
	//enableStroke(color, (float)strokeSize);
	enableShadow(Size(1.5f, -1.5f), 0.9f, 0.3f);

	return true;
}

#if 0
CCRenderTexture* LabelStroke::createStroke(CCLabelTTF* label, float size ,Color3B cor)
{
	float x=label->getTexture()->getContentSize().width+size*2; 
	float y=label->getTexture()->getContentSize().height+size*2; 
	CCRenderTexture *rt=CCRenderTexture::create(x, y, kTexture2DPixelFormat_RGBA4444); 
	Point originalPos=label->getPosition(); 
	Color3B originalColor=label->getColor(); 
	label->setColor(cor); 
	ccBlendFunc originalBlend=label->getBlendFunc();
	ccBlendFunc blend={GL_SRC_ALPHA,GL_ONE};
	label->setBlendFunc(blend); 
	Point center=Vec2(x/2+size, y/2+size); 

	rt->begin(); 
	for (int i=0; i<360; i+=15) { 
		float _x=center.x+sin(CC_DEGREES_TO_RADIANS(i))*size; 
		float _y=center.y+cos(CC_DEGREES_TO_RADIANS(i))*size; 

		label->setPosition(Vec2(_x, _y)); 
		label->visit(); 

	} 
	rt->end(); 

	label->setPosition(originalPos); 
	label->setColor(originalColor); 
	label->setBlendFunc(originalBlend); 
	float rtX=originalPos.x-size; 
	float rtY=originalPos.y-size; 

	rt->setPosition(Vec2(rtX, rtY)); 
	//rt->getSprite();

	return rt;
}

const char * LabelStroke::getString()
{
	return mLabel->getString();
}
#endif

//GLubyte LabelStroke::getOpacity(void)
//{
//	CCRenderTexture * texture = (CCRenderTexture*) getChildByTag(1);
//	return texture->getSprite()->getOpacity();
//}
//
//void LabelStroke::setOpacity(GLubyte opacity)
//{
//	CCRenderTexture * texture = (CCRenderTexture*) getChildByTag(1);
//	texture->getSprite()->setOpacity(opacity);
//	mLabel->setOpacity(opacity);
//}
//
//const Color3B& LabelStroke::getColor(void)
//{
//	return m_sColor;
//}
//
//void LabelStroke::setColor(const Color3B& color3)
//{
//	m_sColor = color3;
//	mLabel->setColor(m_sColor);
//}
//
//void LabelStroke::setOpacityModifyRGB(bool bValue)
//{
//}
//
//bool LabelStroke::isOpacityModifyRGB(void)
//{
//	return true;
//}