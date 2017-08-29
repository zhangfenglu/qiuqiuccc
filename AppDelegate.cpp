#include "AppDelegate.h"
//#include "MainScene.h"
#include "LogoLayer.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate()
{
}

void AppDelegate::initGLContextAttrs()
{
	// set OpenGL context attributes: red,green,blue,alpha,depth,stencil
	GLContextAttrs glContextAttrs = { 8, 8, 8, 8, 24, 8 };

	GLView::setGLContextAttrs(glContextAttrs);
}

bool AppDelegate::applicationDidFinishLaunching() {

	auto pDirector = Director::getInstance();
	auto glview = pDirector->getOpenGLView();
	if (!glview) {
		glview = GLViewImpl::create("Ball Battle");
		pDirector->setOpenGLView(glview);
	}

	pDirector->setOpenGLView(glview);

	// turn on display FPS
	pDirector->setDisplayStats(true);
	//pDirector->setDisplayStats(false);

	// set FPS. the default value is 1.0/60 if you don't call this
	pDirector->setAnimationInterval(1.0 / 60);

	glview->setFrameSize(1280, 720);
	pDirector->getOpenGLView()->setDesignResolutionSize(1280, 720, ResolutionPolicy::SHOW_ALL);

	//glview->setDesignResolutionSize(glview->getFrameSize().width, glview->getFrameSize().height, ResolutionPolicy::SHOW_ALL);
	//glview->setDesignResolutionSize(glview->getFrameSize().width, glview->getFrameSize().height, ResolutionPolicy::EXACT_FIT);

	cocos2d::FileUtils::getInstance()->addSearchPath("Resources");
	cocos2d::FileUtils::getInstance()->addSearchPath("fonts");
	cocos2d::FileUtils::getInstance()->addSearchPath("res");
	cocos2d::FileUtils::getInstance()->addSearchPath("endgame");
	cocos2d::FileUtils::getInstance()->addSearchPath("Food");
	cocos2d::FileUtils::getInstance()->addSearchPath("friend");
	cocos2d::FileUtils::getInstance()->addSearchPath("item");
	cocos2d::FileUtils::getInstance()->addSearchPath("Login");
	cocos2d::FileUtils::getInstance()->addSearchPath("music");
	cocos2d::FileUtils::getInstance()->addSearchPath("PersonCenter");
	cocos2d::FileUtils::getInstance()->addSearchPath("Player");
	cocos2d::FileUtils::getInstance()->addSearchPath("qiandao");
	cocos2d::FileUtils::getInstance()->addSearchPath("Ranking");
	cocos2d::FileUtils::getInstance()->addSearchPath("RelationShip");
	cocos2d::FileUtils::getInstance()->addSearchPath("shengcun");
	cocos2d::FileUtils::getInstance()->addSearchPath("shezhi");
	cocos2d::FileUtils::getInstance()->addSearchPath("Shop");
	cocos2d::FileUtils::getInstance()->addSearchPath("UserInfo");

	// create a scene. it's an autorelease object
	CCScene *pScene = CCScene::create();

	// WebSocketLayer* socket = WebSocketLayer::create();
	//pScene->addChild(socket, 0, 1);

	//MainScene* layer = MainScene::create();
	// pScene->addChild(layer, 2 , 0);

	LogoLayer* logoLayer = LogoLayer::create();
	pScene->addChild(logoLayer, 2, 0);

	// run
	pDirector->runWithScene(pScene);

	return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
	Director::getInstance()->stopAnimation();

	// if you use SimpleAudioEngine, it must be pause
	// SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
	Director::getInstance()->startAnimation();

	// if you use SimpleAudioEngine, it must resume here
	// SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
