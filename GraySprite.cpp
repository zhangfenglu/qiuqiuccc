#include "GraySprite.h"
#include "Global.h"


GraySprite* GraySprite::create( const char* pszFileName ){
	//CCINFO("%d",1);
	GraySprite* graySprite = new GraySprite;
	if (graySprite && graySprite->initWithFile(pszFileName)){
		graySprite->autorelease();
		return graySprite;
	}else{
		CC_SAFE_RELEASE(graySprite);
		return NULL;
	}
}

GraySprite* GraySprite::createWithSpriteFrameName(const char *pszSpriteFrameName)
{
	SpriteFrame *pFrame = SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(pszSpriteFrameName);

#if COCOS2D_DEBUG > 0
	char msg[256] = {0};
	sprintf(msg, "Invalid spriteFrameName: %s", pszSpriteFrameName);
	CCAssert(pFrame != NULL, msg);
#endif

	GraySprite *pobSprite = new GraySprite();
	if (pFrame && pobSprite && pobSprite->initWithSpriteFrame(pFrame))
	{
		pobSprite->autorelease();
		return pobSprite;
	}
	CC_SAFE_DELETE(pobSprite);
	return NULL;
}

GraySprite* GraySprite::createWithTexture(Texture2D *pTexture){
	//CCINFO("%d",1);
	GraySprite* graySprite = new GraySprite;
	if (graySprite && graySprite->initWithTexture(pTexture)){
		graySprite->autorelease();
		return graySprite;
	}else{
		CC_SAFE_RELEASE(graySprite);
		return NULL;
	}
}


bool GraySprite::initWithTexture(Texture2D *pTexture)
{
	CCAssert(pTexture != NULL, "Invalid texture for sprite");

    Rect rect = Rect::ZERO;
	rect.size = pTexture->getContentSize();

	return initWithTexture(pTexture, rect);
}



bool GraySprite::initWithTexture(Texture2D* pTexture, const Rect& tRect ){
		//CCINFO("%d",1);
	do{
		CC_BREAK_IF(!Sprite::initWithTexture(pTexture, tRect));

		GLchar* pszFragSource =
			"#ifdef GL_ES \n \
			precision mediump float; \n \
			#endif \n \
			uniform sampler2D u_texture; \n \
			varying vec2 v_texCoord; \n \
			varying vec4 v_fragmentColor; \n \
			void main(void) \n \
			{ \n \
			// Convert to greyscale using NTSC weightings \n \
			vec4 col = texture2D(u_texture, v_texCoord); \n \
			float grey = dot(col.rgb, vec3(0.299, 0.587, 0.114)); \n \
			gl_FragColor = vec4(grey, grey, grey, col.a); \n \
			}";

		CCGLProgram* pProgram = new CCGLProgram();
		pProgram->initWithVertexShaderByteArray(ccPositionTextureColor_vert, pszFragSource);
		this->setShaderProgram(pProgram);
		pProgram->release();
		CHECK_GL_ERROR_DEBUG();

		this->getShaderProgram()->addAttribute(/*kCCAttributeNamePosition*/GLProgram::ATTRIBUTE_NAME_POSITION, kCCVertexAttrib_Position);
		this->getShaderProgram()->addAttribute(/*kCCAttributeNameColor*/GLProgram::ATTRIBUTE_NAME_COLOR, kCCVertexAttrib_Color);
		this->getShaderProgram()->addAttribute(/*kCCAttributeNameTexCoord*/GLProgram::ATTRIBUTE_NAME_TEX_COORD, kCCVertexAttrib_TexCoords);
		CHECK_GL_ERROR_DEBUG();

		this->getShaderProgram()->link();
		CHECK_GL_ERROR_DEBUG();

		this->getShaderProgram()->updateUniforms();
		CHECK_GL_ERROR_DEBUG();

		return true;
	} while (0);
	return false;
}

void GraySprite::draw(Renderer *renderer, const Mat4& transform, uint32_t flags){
	//	CCINFO("%d",1);
	GL::enableVertexAttribs(GL::VERTEX_ATTRIB_FLAG_POS_COLOR_TEX );
	GL::blendFunc( _blendFunc.src, _blendFunc.dst );

	this->getShaderProgram()->use();
	//this->getShaderProgram()->setUniformForModelViewProjectionMatrix();
	this->getShaderProgram()->setUniformsForBuiltins();
    GL::bindTexture2D( this->getTexture()->getName() );

#define kQuadSize sizeof(_quad.bl)
	long offset = (long)(&_quad);

	// vertex
	int diff = offsetof( ccV3F_C4B_T2F, vertices);
	glVertexAttribPointer(kCCVertexAttrib_Position, 3, GL_FLOAT, GL_FALSE, kQuadSize, (void*) (offset + diff));

	// texCoods
	diff = offsetof( ccV3F_C4B_T2F, texCoords);
	glVertexAttribPointer(kCCVertexAttrib_TexCoords, 2, GL_FLOAT, GL_FALSE, kQuadSize, (void*)(offset + diff));

	// color
	diff = offsetof( ccV3F_C4B_T2F, colors);
	glVertexAttribPointer(kCCVertexAttrib_Color, 4, GL_UNSIGNED_BYTE, GL_TRUE, kQuadSize, (void*)(offset + diff));
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	CC_INCREMENT_GL_DRAWS(1);
}

