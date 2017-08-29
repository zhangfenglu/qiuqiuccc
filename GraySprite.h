#ifndef __GRAY_SPRITE_H__
#define __GRAY_SPRITE_H__

#include "cocos2d.h"
USING_NS_CC;


class GraySprite : public Sprite
{
public:
	GraySprite(){}
	virtual ~GraySprite(){}
	static GraySprite* create(const char* pszFileName);
	static GraySprite* createWithSpriteFrameName(const char *pszSpriteFrameName);
	bool initWithTexture(Texture2D* pTexture, const Rect& tRect);
	bool initWithTexture(Texture2D *pTexture);
	static GraySprite* createWithTexture(Texture2D *pTexture);
	virtual void draw(Renderer *renderer, const Mat4& transform, uint32_t flags);

};


#endif

