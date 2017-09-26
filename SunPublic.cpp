#include "SunPublic.h"
#include "MainScene.h"

SunPublic::~SunPublic()
{

}

SunPublic::SunPublic()
{

}

static SunPublic* p = nullptr;
SunPublic* SunPublic::getInstance()
{
	if (p == nullptr) {
		p = new SunPublic();
	}

	return p;
}

void SunPublic::returnMainScene(cocos2d::Node* node)
{
	((MainScene*)node)->BackToLoginLayer(MainScene::TAG_LAYER_LOGIN);
}
