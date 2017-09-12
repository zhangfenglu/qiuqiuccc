//
//  MainScene.cpp
//  qiuFight
//
//  Created by 张跃东 on 16/2/24.
//
//////
//http://blog.sina.com.cn/s/blog_693de6100102vtjk.html
////

#include "MainScene.h"
#include "WebSocketLayer.h"
#include "SceneLayer.h"
#include "GridLayer.h"
#include "Common.h"
#include "LoginScene.h"
#include "Global.h"
#include "PersonCenterLayer.h"
#include "RelationShipLayer.h"
#include "RankingLayer.h"
#include "ShopLayer.h"
#include "UserInfo.h"
#include "msg_client.pb.h"
#include "struct.pb.h"
#include "ExchangeInfo.h"
#include "msg_error.pb.h"
#include "Resources.h"
#include "CurCularNode.h"
#include "RichLabel.h"
#include "TuanDui.h"

#include "SimpleTools.h"
using namespace cocos2d::network;

#define UPDATE_CAMERA_DURATION      0.4
#define NEED_TO_PER_CAMERA          0.08
#define NEED_TO_PER_CAMERA_TIMES    3

/*
CCScene* MainScene::scene()
{
CCScene* pScene = CCScene::create();

return pScene;
}
*/

MainScene::MainScene()
{

}
MainScene::~MainScene()
{

}
bool MainScene::init()
{
	if (!Layer::init())
		return false;

	auto listener = EventListenerTouchAllAtOnce::create();
	listener->onTouchesBegan = CC_CALLBACK_2(MainScene::onTouchesBegan, this);
	listener->onTouchesMoved = CC_CALLBACK_2(MainScene::onTouchesMoved, this);
	listener->onTouchesEnded = CC_CALLBACK_2(MainScene::onTouchesEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	LoginLayer* login = LoginLayer::create();
	addChild(login, 2, TAG_LAYER_LOGIN);
	//setTouchEnabled(true);

	//    SceneLayer* scene = SceneLayer::create();
	//    addChild(scene, 2, TAG_LAYER_SCENE);

	//    this->scheduleUpdate();

	m_diff = Vec2(0, 0);
	////m_isFirstEnter = false;
	m_isSplit = false;
	m_isUpdateScale = false;
	m_initialSpeed = 0;
	m_attenuationSpeed = 0;
	m_scale = 1;
	m_tempScale = 1;
	m_CurrTag = TAG_LAYER_LOGIN;
	m_isFistGetItem = true;
	m_grid_off_pos = Vec2(winSize.width * 0.5f, winSize.height * 0.5f);
	initJson();


	//ZhanDouEnd* gameEnd = ZhanDouEnd::create();
	//addChild(gameEnd, 2, TAG_GAME_END);
	this->scheduleOnce(schedule_selector(MainScene::reqServerList1), 0.1f);
	return true;
}

bool MainScene::OpenWebSocket(const char *ipAddress, const char *port)
{
	CCScene* pScene = dynamic_cast<CCScene*>(getParent());
	if (pScene)
	{
		m_ipAddress = ipAddress;
		m_ipPort = port;
		WebSocketLayer* socket = dynamic_cast<WebSocketLayer*>(pScene->getChildByTag(1));
		if (socket)
			return socket->openWebSocket(ipAddress, port);
	}
	return false;
}

void MainScene::CheckLayer(MainScene::tagDif tag)
{
	if (tag == TAG_LAYER_PERSON)
	{
		removeChildByTag(TAG_LAYER_LOGIN);

		PersonCenterBase* person = PersonCenterBase::create();
		addChild(person, 3, TAG_LAYER_PERSON);

		m_CurrTag = TAG_LAYER_PERSON;
	}
	else if (tag == TAG_LAYER_RELATION)
	{
		removeChildByTag(TAG_LAYER_LOGIN);

		RelationShipBase* relation = RelationShipBase::create();
		addChild(relation, 3, TAG_LAYER_RELATION);

		m_CurrTag = TAG_LAYER_RELATION;
	}
	else if (tag == TAG_LAYER_RANKING)
	{
		removeChildByTag(TAG_LAYER_LOGIN);

		RankingLayerBase* rank = RankingLayerBase::create();
		addChild(rank, 3, TAG_LAYER_RANKING);

		m_CurrTag = TAG_LAYER_RANKING;
	}
	else if (tag == TAG_LAYER_SHOP)
	{
		removeChildByTag(TAG_LAYER_LOGIN);

		ShopLayerBase* shop = ShopLayerBase::create();
		addChild(shop, 3, TAG_LAYER_SHOP);

		m_CurrTag = TAG_LAYER_SHOP;
	}
	else if (tag == TAG_LAYER_USERINFO)
	{
		if (m_CurrTag == TAG_LAYER_LOGIN)
			removeChildByTag(TAG_LAYER_LOGIN);
		else{
			Node* node = getChildByTag(m_CurrTag);
			node->setScale(0.0f);
		}

		UserInfo* userInfo = UserInfo::create();
		addChild(userInfo, 50, TAG_LAYER_USERINFO);

	}
	else if (tag == TAG_LAYER_TUANDUI)
	{
		removeChildByTag(TAG_LAYER_LOGIN);

		TuanDui* relation = TuanDui::create();
		addChild(relation, 3, TAG_LAYER_TUANDUI);

		m_CurrTag = TAG_LAYER_TUANDUI;
	}
}

void MainScene::BackToLoginLayer(MainScene::tagDif tag)
{
	auto node = this->getChildByTag(tag);
	if (node)
	{
		node->retain();
		node->autorelease();
	}


	removeChildByTag(tag);
	Global::getInstance()->clearMainNodes();
	this->unscheduleUpdate();
	if (tag == TAG_LAYER_USERINFO && m_CurrTag != TAG_LAYER_LOGIN) {
		getChildByTag(m_CurrTag)->setScale(1.0f);
	}
	else{
		LoginLayer* login = LoginLayer::create();
		addChild(login, 2, TAG_LAYER_LOGIN);
		m_CurrTag = TAG_LAYER_LOGIN;
	}
}

void MainScene::CloseWebNet()
{
	this->unscheduleUpdate();
	WebSocketLayer* socket = dynamic_cast<WebSocketLayer*>(getParent()->getChildByTag(1));
	socket->closeNet();
}
void MainScene::initJson()
{
	Json* root = ReadJson("SetInfo.json");

	Json* inispeed = Json_getItem(root, "initial_speed");
	if (inispeed->type == Json_Number)
	{
		m_initialSpeed = inispeed->valueFloat;
	}

	Json* attenuation = Json_getItem(root, "attenuation_speed");
	if (attenuation->type == Json_Number)
	{
		m_attenuationSpeed = attenuation->valueFloat;
	}

	Json* sceneScale = Json_getItem(root, "split_scene_size");
	if (sceneScale->type == Json_Number)
	{
		m_sceneScale = sceneScale->valueFloat;
	}

	Json* changeText = Json_getItem(root, "change_text_size");
	if (changeText->type == Json_Number)
	{
		Global::getInstance()->setJsonImageHead(changeText->valueInt);
	}

	Json* upCameraPer = Json_getItem(root, "player_size_up_camera");
	if (upCameraPer->type == Json_Number)
	{
		Global::getInstance()->setJsonUpCameraSize(upCameraPer->valueInt);
	}

	Json* upCameraScale = Json_getItem(root, "camera_up_scale_diff");
	if (upCameraScale->type == Json_Number)
	{
		Global::getInstance()->setJsonUpCameraScale(upCameraScale->valueFloat);
	}

	Json* upCameraMinScale = Json_getItem(root, "camera_up_min_scale");
	if (upCameraMinScale->type == Json_Number)
	{
		m_minScale = upCameraMinScale->valueFloat;
	}
}

void MainScene::onTouchesBegan(const std::vector<Touch*>&pTouch, cocos2d::Event *pEvent)
{
	Touch* touch = pTouch[0];// (Touch*)pTouch->anyObject();

	Point pos = touch->getLocation();
	SceneLayer* layer = dynamic_cast<SceneLayer*>(getChildByTag(TAG_LAYER_SCENE));
	if (layer)
	{
		layer->setVisible(true);

		//    GridLayer* grid = dynamic_cast<GridLayer*>(getChildByTag(TAG_LAYER_GRID));
		//    grid->resetMainState();

		layer->setJoystickPos(pos);

		m_isFirstEnter = true;
	}
}

void MainScene::onTouchesMoved(const std::vector<Touch*>& pTouch, cocos2d::Event *pEvent)
{
	if (m_isUpdateScale)
		return;

	Touch* touch = pTouch[0];// (Touch*)pTouch->anyObject();
	Point diff = touch->getDelta();
	diff = Vec2((int)diff.x, (int)diff.y);

	// 滑杆移动
	SceneLayer* scene = dynamic_cast<SceneLayer*>(getChildByTag(TAG_LAYER_SCENE));
	if (scene)
	{
		Vec2 touchPos = touch->getLocation();
		scene->updateJoystickPos(touchPos);

		Point tempDiff = scene->GetJoyDiff();

		if (tempDiff.getLength() < 10)
		{
			m_diff = Vec2::ZERO;
		}
		else
		{
			//m_diff = tempDiff / R_LENGTH ;
			m_diff = tempDiff / tempDiff.getLength();
		}
	}
}

void MainScene::onTouchesEnded(const std::vector<Touch*>& pTouch, cocos2d::Event *pEvent)
{
	// 现在希望不拖动也能移动
	//    m_diff = Vec2(0,0);

	SceneLayer* layer = dynamic_cast<SceneLayer*>(getChildByTag(TAG_LAYER_SCENE));
	if (layer)
	{
		Point tempDiff = layer->GetJoyDiff();

		if (tempDiff.getLength() < 10)
		{
			m_diff = Vec2::ZERO;
		}
		else
		{
			//m_diff = tempDiff / R_LENGTH ;
			m_diff = tempDiff / tempDiff.getLength();
		}

		layer->moveEndJoystick();
	}
}
#ifdef EditEXE
void MainScene::UpdataWeight(int weight)
{
	SceneLayer* layer = dynamic_cast<SceneLayer*>(getChildByTag(TAG_LAYER_SCENE));
	if (!layer) {
		return;
	}
	layer->updateWeightLabel(weight);
}
#endif
void MainScene::update(float ft)
{
	// 设置体积的label
	SceneLayer* layer = dynamic_cast<SceneLayer*>(getChildByTag(TAG_LAYER_SCENE));
	if (!layer) {
		return;
	}
#ifndef EditEXE
	layer->updateWeightLabel(getMainNodesMass());
#endif
	if (!m_isFirstEnter)
		return;

	// 获得体积
	//int size = getMainNodesSize();

	GridLayer* grid = dynamic_cast<GridLayer*>(getChildByTag(TAG_LAYER_GRID));
	if (grid)
	{
		UpdateScaleImmediately(grid->getMainNodeDiff());
	}
#ifndef EditEXE
	//float speed = m_initialSpeed - (size - MINIMUM_SIZE) * m_attenuationSpeed;
	//if(speed < MINIMUM_SPEED)
	//speed = MINIMUM_SPEED;
	float speed = grid->getMainNodeDiff() + 500;
	Point diff = m_diff * speed * m_scale;

	// 判断边界, 现在服务器做，暂时注掉
	//diff = calculateBorder(diff, size);
	diff = Vec2((int)diff.x, (int)diff.y);

	//log("diff x is:%f, y is:%f", diff.x, diff.y);

	// 客户端先模拟移动
	//    GridLayer* layer = dynamic_cast<GridLayer*>(getChildByTag(TAG_LAYER_GRID));
	//    Point currentPos = layer->getPosition();
	//    Point destPos = ccpSub(currentPos, diff);
	//    layer->setPosition( destPos);
	//    Global::getInstance()->SetGridPos(destPos);

	// 通知服务器移动
	// 4-16 zyd修改球中心点
	Point mainOldPos = Global::getInstance()->GetMainPos();
	//    GridLayer* grid = dynamic_cast<GridLayer*>(getChildByTag(TAG_LAYER_GRID));
	//    Point mainOldPos = grid->getMainNodesCenterPos();
	Point mainDest = ccpAdd(mainOldPos, diff / m_scale);
	//log("old pos x is:%f, old pos y is:%f", mainOldPos.x, mainOldPos.y);
	struct sMoveTo msg;
	msg.msgid = 16;
	msg.target_x = (uint32_t)mainDest.x;
	msg.target_y = (uint32_t)mainDest.y;
	msg.dir_x = (uint32_t)(m_diff.x * 100);
	msg.dir_y = (uint32_t)(m_diff.y * 100);
	//    Global::getInstance()->SetMainPos(mainDest);
	//    layer->setMainNodePos(mainDest);

	WebSocketLayer* socket = dynamic_cast<WebSocketLayer*>(getParent()->getChildByTag(1));
	socket->onSendMsg((char*)&msg, sizeof(struct sMoveTo));
	//log("main:(x = %f , y = %f)", mainDest.x, mainDest.y);
	//m_diff = m_diff / (speed * m_scale);

#endif
}

Point MainScene::calculateBorder(cocos2d::Point pos, uint32_t size)
{
	Point diff = pos;
	Point MainPos = Global::getInstance()->GetMainPos();
	Point wantPos = ccpAdd(MainPos, pos);
	Size gridSize = Global::getInstance()->GetGridSize();
	if (wantPos.x - size <= 0)
	{
		diff.x = 0;
	}
	if (wantPos.y - size <= 0)
	{
		diff.y = 0;
	}
	if (wantPos.x + size >= gridSize.width)
	{
		diff.x = 0;
	}
	if (wantPos.y + size >= gridSize.height)
	{
		diff.y = 0;
	}

	return diff;
}

void MainScene::enterGame(const char *nick, int key)
{
	removeChildByTag(TAG_LAYER_LOGIN);

	//user_info info = Global::getInstance()->GetUserInfo();
	

	account_info info = Global::getInstance()->GetAccountInfo();
	std::string userID1 = info.playerid;
	uint32_t userID = atoi(userID1.c_str());
	//uint32_t userID = 100223;
	//uint32_t userID = info.roleID;

	uint8_t msgid = 255;
	uint32_t protocol = 0;
	uint8_t index = Global::getInstance()->GetMainPicIndex();
	uint8_t len = strlen(nick);
	uint32_t roomId = Global::getInstance()->GetRoomId();
	int headSize = 0;
	char msg[sizeof(EnterBoard)+255];
	int msgsize = sizeof(EnterBoard)+len;
	memcpy(msg, &msgid, sizeof(uint8_t));
	headSize += sizeof(uint8_t);
	memcpy(msg + headSize, &protocol, sizeof(uint32_t));
	headSize += sizeof(uint32_t);
	memcpy(msg + headSize, &index, sizeof(uint8_t));
	headSize += sizeof(uint8_t);
	memcpy(msg + headSize, &userID, sizeof(uint32_t));
	//memcpy(msg + headSize, &userID, sizeof(std::string));
	headSize += sizeof(uint32_t);
	//headSize += sizeof(std::string);
	memcpy(msg + headSize, &key, sizeof(uint32_t));
	headSize += sizeof(uint32_t);
	memcpy(msg + headSize, &roomId, sizeof(uint32_t));
	headSize += sizeof(uint32_t);
	memcpy(msg + headSize, &len, sizeof(uint8_t));
	headSize += sizeof(uint8_t);
	memcpy(msg + headSize, nick, len);


	WebSocketLayer* socket = dynamic_cast<WebSocketLayer*>(getParent()->getChildByTag(1));
	socket->onSendMsg(msg, msgsize);
}

void MainScene::setWinSize(const cocos2d::network::WebSocket::Data &data)
{
	//设置SceneLayer
	setTouchEnabled(true);

	SceneLayer* scene = dynamic_cast<SceneLayer*>(getChildByTag(TAG_LAYER_SCENE));
	if (scene == NULL)
	{
		scene = SceneLayer::create();
		addChild(scene, 2, TAG_LAYER_SCENE);
	}

	this->scheduleUpdate();
	//schedule(schedule_selector(MainScene::updateFrame), 0.05);
	//end

	uint32_t m_left, m_top, m_right, m_bottom, m_leftTime;
	uint8_t m_life;

	int headSize = sizeof(uint8_t);

	memcpy(&m_left, data.bytes + headSize, sizeof(uint32_t));
	headSize += sizeof(uint32_t);
	memcpy(&m_top, data.bytes + headSize, sizeof(uint32_t));
	headSize += sizeof(uint32_t);
	memcpy(&m_right, data.bytes + headSize, sizeof(uint32_t));
	headSize += sizeof(uint32_t);
	memcpy(&m_bottom, data.bytes + headSize, sizeof(uint32_t));
	headSize += sizeof(uint32_t);
	memcpy(&m_leftTime, data.bytes + headSize, sizeof(uint32_t));
	headSize += sizeof(uint32_t);
	memcpy(&m_life, data.bytes + headSize, sizeof(uint8_t));
	headSize += sizeof(uint8_t);

	scene->ViewLife(m_life);

	Point pos = ccpAdd(Vec2(m_left, m_top), m_grid_off_pos);
	Size size = Size(m_right - m_left, m_bottom - m_top);
	Global::getInstance()->SetGridPos(pos);
	Global::getInstance()->SetGridSize(size);

	GridLayer* grid = dynamic_cast<GridLayer*>(getChildByTag(TAG_LAYER_GRID));
	if (grid == NULL)
	{
		LayerColor* color = LayerColor::create(Color4B(237, 242, 221, 255));
		//color->setPosition(Vec2(-1000,-1000));
		addChild(color, 0, TAG_GAME_COLOR_BG);

		GridLayer* grid = GridLayer::create();
		grid->setPosition(pos);
		addChild(grid, 1, TAG_LAYER_GRID);
		//log("grid posx:%f, posy: %f, width is: %f, height is: %f, left_time is:%d", grid->getPositionX(), grid->getPositionY(), size.width, size.height, m_leftTime);
	}
	else if (grid != NULL && m_isFighting)
	{
		grid->removeOtherChild();
	}

	if (scene)
	{
		int duration = m_leftTime / 1000;
		scene->setDuration(duration);
	}
}

void MainScene::addSelfNode(const cocos2d::network::WebSocket::Data &data)
{
	uint32_t nodeid;
	int headSize = sizeof(uint8_t);
	memcpy(&nodeid, data.bytes + headSize, sizeof(uint32_t));
	headSize += sizeof(uint32_t);

	//    if(Global::getInstance()->getMainNodeNum() == 0)
	//        m_isFirstEnter = true;
	//    log("main id is:%d", nodeid);
	Global::getInstance()->SetMainNodeID(nodeid);  //设置主节点的id
	Global::getInstance()->addMianNode(nodeid);


}

void MainScene::UpdateScaleByMainNodes()
{
	if (Global::getInstance()->getMainNodeNum() >= 2)
	{
		//log("scene scale is:%f, minScale is:%f", m_sceneScale, m_minScale);
		//        if(m_sceneScale < m_minScale)
		{
			updateSceneSize(m_sceneScale);
		}
	}
}

void MainScene::updateNodes(const cocos2d::network::WebSocket::Data &data)
{
	GridLayer* grid = dynamic_cast<GridLayer*>(getChildByTag(TAG_LAYER_GRID));
	if (grid)
	{
		grid->updateNodes(data);
	}
}

void MainScene::updateMainState(Point mainPos)
{
	//    SceneLayer* scen = dynamic_cast<SceneLayer*>(getChildByTag(TAG_LAYER_SCENE));
	//    scen->updateMainInfo(info);

	//    if(!m_isJoyMove && m_isFirstEnter)
	{
		GridLayer* grid = dynamic_cast<GridLayer*>(getChildByTag(TAG_LAYER_GRID));
		if (grid != NULL)
		{
			Point currentPos = grid->getPosition();
			Point mainOldPos = Global::getInstance()->GetMainPos();
			Point mainRelaPos = ccpSub(mainPos, mainOldPos);
			Point destPos = ccpSub(currentPos, mainRelaPos * m_scale); // 有缩放的过程
			Global::getInstance()->SetMainPos(mainPos);
			Global::getInstance()->SetGridPos(destPos);
			grid->setPosition(destPos);
			//log("return posx is:%f, posy is:%f", destPos.x, destPos.y);

			UpdateScaleImmediately(grid->getMainNodeDiff());

			//grid->upCenter(mainPos);
		}
	}
}

void MainScene::notifyEject()
{
	EjectMass msg;
	msg.msgid = 21;

	WebSocketLayer* socket = dynamic_cast<WebSocketLayer*>(getParent()->getChildByTag(1));
	socket->onSendMsg((char*)&msg, sizeof(EjectMass));
}

void MainScene::notifySplite()
{
	if (m_isUpdateScale)
		return;

	SplitCell msg;
	msg.msgid = 17;

	WebSocketLayer* socket = dynamic_cast<WebSocketLayer*>(getParent()->getChildByTag(1));
	socket->onSendMsg((char*)&msg, sizeof(SplitCell));

	m_isSplit = true;

	scheduleOnce(schedule_selector(MainScene::endSplit), 0.5);
}

void MainScene::endSplit(float dt)
{
	m_isSplit = false;
}

int MainScene::getMainNodesSize()
{
	std::vector<uint32_t> mainIDS = Global::getInstance()->getMainNodes();
	int num = (int)mainIDS.size();

	int size = 32;
	if (num == 1)
	{
		GridLayer* grid = dynamic_cast<GridLayer*>(getChildByTag(TAG_LAYER_GRID));
		std::vector<uint32_t>::iterator it = mainIDS.begin();
		//for (; it != mainIDS.end(); ++it) {
		uint32_t mainID = *it;
		size = grid->getMainNodeSize(mainID);
		//}
	}
	//log("the main node size is:%d", size);
	return size;
}

int MainScene::getMainNodesMass()
{
	std::vector<uint32_t> mainIDS = Global::getInstance()->getMainNodes();
	int size = 0;
	int mass = 0;
	GridLayer* grid = dynamic_cast<GridLayer*>(getChildByTag(TAG_LAYER_GRID));
	std::vector<uint32_t>::iterator it = mainIDS.begin();
	for (; it != mainIDS.end(); ++it) {
		uint32_t mainID = *it;
		size = grid->getMainMass(mainID);
		mass += size;
	}
	return mass;
}

float MainScene::getCameraScale()
{
	//int mass = 0;
#ifdef EditEXE
	//GridLayer* grid = dynamic_cast<GridLayer*>(getChildByTag(TAG_LAYER_GRID));
	//if(grid)
	//mass = grid->getMass();

	int mainSize = getMainNodesSize() * 2;

	float power = 0.5;
	float value = powf(mainSize, power);
	float nSize = 14.75282 * value - 54.02254;
	float scale = nSize / ((float)mainSize);
#else
	//mass = getMainNodesMass();
	//float power = K_VALUE;
	//float value = powf(mass, power);
	//float scale = A_VALUE * value + B_VALUE;

	int mainSize = getMainNodesSize() * 2;
	if (mainSize == 0)
	{
		return 0;
	}
	float power = 0.5;
	float value = powf(mainSize, power);
	float nSize = 14.75282 * value - 54.02254;
	float scale = nSize / ((float)mainSize);
#endif

	return scale;
}

void MainScene::deleteMainNode(uint32_t nodeid)
{
	Global::getInstance()->deleteMainNode(nodeid);

	if (Global::getInstance()->getMainNodeNum() == 0)
	{
		this->unscheduleUpdate();
		//SceneLayer* layer = dynamic_cast<SceneLayer*>(getChildByTag(TAG_LAYER_SCENE));
		//layer->addEndUI("");

		//log("游戏结束！！！");
	}
}

void MainScene::updateSceneSize(float siz)
{
	m_scale = siz;
	GridLayer* grid = dynamic_cast<GridLayer*>(getChildByTag(TAG_LAYER_GRID));
	//    Point mainPos = Global::getInstance()->GetMainPos();
	Point mainPos = grid->getMainNodesCenterPos();
	Point dest = ccpSub(m_grid_off_pos * siz, mainPos * siz);
	//log("dest x is::%f, dest y is:%f", dest.x, dest.y);


	m_isUpdateScale = true;
	scheduleOnce(schedule_selector(MainScene::resetUpdateCamera), UPDATE_CAMERA_DURATION);

	CCAction* seq = CCSpawn::create(CCMoveTo::create(UPDATE_CAMERA_DURATION, dest), CCScaleTo::create(UPDATE_CAMERA_DURATION, siz), NULL);
	grid->runAction(seq);

}
// test
/*
void MainScene::updateSceneSize(float siz)
{
GridLayer* grid = dynamic_cast<GridLayer*>(getChildByTag(TAG_LAYER_GRID));
Point mainPos = Global::getInstance()->GetMainPos();
//    grid->ignoreAnchorPointForPosition(false);
//    Size gridSize = Global::getInstance()->GetGridSize();
//    Point anchor = Vec2(mainPos.x / gridSize.width, mainPos.y / gridSize.height);
//    grid->setAnchorPoint(anchor);
grid->setPosition(ccpSub(m_grid_off_pos, mainPos * siz));
grid->setScale( siz );
//安全地设置锚点，用于锚点改变后node对象即便设置了scale缩放，其位置也不发生变化
//    float diffX = anchor.x * gridSize.width  * (grid->getScaleX() - 0.95);
//    float diffY = anchor.y * gridSize.height * (grid->getScaleY() - 0.95);
//
//    grid->setAnchorPoint(anchor);
//
//    grid->setPositionX(grid->getPosition().x + diffX);
//    grid->setPositionY(grid->getPosition().y + diffY);



//    SceneLayer* scene = dynamic_cast<SceneLayer*>(getChildByTag(TAG_LAYER_SCENE));
//    scene->updateSceneScale(siz);
}*/

//void MainScene::updateCameraScale(float ft)
//{
//    if(m_scale == m_sceneScale)
//        return;
//    int size = getMainNodesSize();
//    
//    m_tempScale = getCameraScale();
//    if(m_tempScale == m_scale)
//        return;
//    
//    if(m_tempScale == m_minScale)
//        return;
//    
//    if(m_tempScale < m_minScale)
//        m_tempScale = m_minScale;
//    
//    log("main nodes size is:%d", size);
//    updateSceneSize(m_tempScale);
//    
//}

void MainScene::resetUpdateCamera(float ft)
{
	m_isUpdateScale = false;
}

void MainScene::UpdateScaleImmediately(float diff)
{
	m_scale = getCameraScale();
	float len = diff;

	float power = 0.35;
	float value = powf(len, power);
	float nSize = 43.95517 * value - 124.43993;
	float siz = nSize / len;
	//float siz = (DISTANCE_PER_CIRCLE - len)/DISTANCE_PER_CIRCLE;

	float size = 0.0f;
	if (m_scale < siz)
		size = m_scale;
	else
		size = siz;

	//m_tempScale = size;

	GridLayer* grid = dynamic_cast<GridLayer*>(getChildByTag(TAG_LAYER_GRID));
	float oldSize = grid->getScale();
	//size = oldSize;
	Point oldPos = grid->getPosition();
	Point mainPos = grid->getMainNodesCenterPos();
	Point dest = ccpSub(m_grid_off_pos * size, mainPos * size);
	float sizeDiff = size - oldSize;
	if ((sizeDiff < 0 && sizeDiff < -NEED_TO_PER_CAMERA) || (sizeDiff > 0 && sizeDiff > NEED_TO_PER_CAMERA))
	{
		Point diffPos = ccpSub(dest, oldPos) / NEED_TO_PER_CAMERA_TIMES;
		float diff = sizeDiff / NEED_TO_PER_CAMERA_TIMES;
		//log("diff size is:%f, diff posx is:%f, diff posy is:%f", diff, diffPos.x, diffPos.y);
		for (int i = 1; i <= NEED_TO_PER_CAMERA_TIMES; i++)
		{
			Point midPos = oldPos + diffPos * i;
			float midDiff = oldSize + diff * i;
			grid->setScale(midDiff);
			grid->setPosition(midPos);
		}
	}
	else
	{
		grid->setScale(size);
		grid->setPosition(dest);
	}

	//log("scale:%f",size);
}

bool MainScene::IsNeedToUpdateScale()
{
	return false;
}

void MainScene::updateRankeInFight(const cocos2d::network::WebSocket::Data &data)
{
	int headSize = sizeof(uint8_t);

	uint16_t count;
	memcpy(&count, data.bytes + headSize, sizeof(uint16_t));
	headSize += sizeof(uint16_t);
	std::vector<fight_rank> ranks;
	for (int i = 0; i < count; i++)
	{
		fight_rank rank;
		uint32_t roleID;
		uint8_t len;
		memcpy(&roleID, data.bytes + headSize, sizeof(uint32_t));
		headSize += sizeof(uint32_t);
		memcpy(&len, data.bytes + headSize, sizeof(uint8_t));
		headSize += sizeof(uint8_t);
		rank.rankID = roleID;
		if (len > 0)
		{
			//char temp[len + 1];
			char* temp = new char[len + 1];
			memcpy(temp, data.bytes + headSize, len);
			temp[len] = '\0';
			headSize += len;
			rank.name = temp;
			delete[] temp;
		}
		ranks.push_back(rank);
	}

	SceneLayer* layer = dynamic_cast<SceneLayer*>(getChildByTag(TAG_LAYER_SCENE));
	if (layer) {
		layer->updateFightRanking(ranks);
	}
}

void MainScene::GameOverState(const cocos2d::network::WebSocket::Data &data)
{
	int headSize = sizeof(uint8_t);

	uint16_t count;
	memcpy(&count, data.bytes + headSize, sizeof(uint16_t));
	//log("over state count is:%d", count);
	headSize += sizeof(uint16_t);
	std::vector<EndGame1> ranks;
	std::vector<Relation2Me1> relations;

	std::vector<int> idList;

	for (int i = 0; i < count; i++)
	{
		int rank, roleID, sex, province, city, mass, eat, copper, exp, icon;
		uint8_t recommend, len, roleNameLen;
		std::string name, roleName;

		memcpy(&rank, data.bytes + headSize, sizeof(uint32_t));
		headSize += sizeof(uint32_t);
		memcpy(&roleID, data.bytes + headSize, sizeof(uint32_t));
		headSize += sizeof(uint32_t);
		memcpy(&sex, data.bytes + headSize, sizeof(uint32_t));
		headSize += sizeof(uint32_t);
		memcpy(&province, data.bytes + headSize, sizeof(uint32_t));
		headSize += sizeof(uint32_t);
		memcpy(&city, data.bytes + headSize, sizeof(uint32_t));
		headSize += sizeof(uint32_t);
		memcpy(&mass, data.bytes + headSize, sizeof(uint32_t));
		headSize += sizeof(uint32_t);
		memcpy(&eat, data.bytes + headSize, sizeof(uint32_t));
		headSize += sizeof(uint32_t);
		memcpy(&copper, data.bytes + headSize, sizeof(uint32_t));
		headSize += sizeof(uint32_t);
		memcpy(&exp, data.bytes + headSize, sizeof(uint32_t));
		headSize += sizeof(uint32_t);
		memcpy(&icon, data.bytes + headSize, sizeof(uint32_t));
		headSize += sizeof(uint32_t);
		memcpy(&recommend, data.bytes + headSize, sizeof(uint8_t));
		headSize += sizeof(uint8_t);
		memcpy(&len, data.bytes + headSize, sizeof(uint8_t));
		headSize += sizeof(uint8_t);

		if (icon < 101)
		{
			idList.push_back(roleID);
		}

		if (len > 0)
		{
			char* temp = new char[len + 1];
			//char temp[len + 1];
			memcpy(temp, data.bytes + headSize, len);
			temp[len] = '\0';
			headSize += len;
			name = temp;
			delete[] temp;
		}

		memcpy(&roleNameLen, data.bytes + headSize, sizeof(uint8_t));
		headSize += sizeof(uint8_t);
		if (roleNameLen > 0)
		{
			char* temp = new char[roleNameLen + 1];
			//char temp[roleNameLen + 1];
			memcpy(temp, data.bytes + headSize, roleNameLen);
			temp[roleNameLen] = '\0';
			headSize += roleNameLen;
			roleName = temp;
			delete[] temp;
		}
		else
			roleName = "";


		if (rank > 0)
		{
			EndGame1 info;
			info.rank = rank;
			info.roleid = roleID;
			info.sex = sex;
			info.province = province;
			info.city = city;
			info.mass = mass;
			info.eat = eat;
			info.copper = copper;
			info.exp = exp;
			info.icon = icon;
			info.name = name;
			info.roleName = roleName;

			ranks.push_back(info);
		}

		if (recommend > 0)
		{
			Relation2Me1 info;
			info.roleid = roleID;
			info.sex = sex;
			info.province = province;
			info.city = city;
			info.mass = mass;
			info.eat = eat;
			info.copper = copper;
			info.exp = exp;
			info.icon = icon;
			info.name = name;
			info.roleName = roleName;
			info.recommend = recommend;

			relations.push_back(info);
		}
	}

	if (getChildByTag(TAG_GAME_END) && (ZhanDouEnd*)getChildByTag(TAG_GAME_END))
	{
		ZhanDouEnd* end = dynamic_cast<ZhanDouEnd*>(getChildByTag(TAG_GAME_END));
		end->setInfos(ranks, relations);
		if (idList.size() > 0)
			reqIcons(idList);
	}
	else
	{
		removeChildByTag(TAG_LAYER_SCENE, true);
		ZhanDouEnd* gameEnd = ZhanDouEnd::create();
		addChild(gameEnd, 2, TAG_GAME_END);
		gameEnd->setInfos(ranks, relations);

		Global::getInstance()->clearMainNodes();
		removeChildByTag(TAG_GAME_COLOR_BG, true);
		removeChildByTag(TAG_LAYER_GRID, true);
		//CloseWebNet();
	}
}
void MainScene::CloseFight()
{
	BackToLoginLayer(TAG_LAYER_SCENE);
	Global::getInstance()->clearMainNodes();
	removeChildByTag(TAG_GAME_COLOR_BG, true);
	removeChildByTag(TAG_LAYER_GRID, true);
}
void MainScene::UpdateFightLife(const cocos2d::network::WebSocket::Data &data)
{
	int headSize = sizeof(uint8_t);

	uint8_t lifeCount;
	memcpy(&lifeCount, data.bytes + headSize, sizeof(uint8_t));
	headSize += sizeof(uint8_t);

	SceneLayer* layer = (SceneLayer*)getChildByTag(TAG_LAYER_SCENE);
	if (layer)
		layer->ViewLife(lifeCount);
}

void MainScene::SetDeath(const cocos2d::network::WebSocket::Data &data)
{
	int headSize = sizeof(uint8_t);

	uint8_t duration;
	memcpy(&duration, data.bytes + headSize, sizeof(uint8_t));
	headSize += sizeof(uint8_t);

	int tempLen = data.len - sizeof(uint8_t)+1;

	char* temp = new char[tempLen + 1];
	memset(temp, 0, tempLen + 1);
	//char temp[tempLen];
	memcpy(temp, data.bytes + headSize, tempLen);
	temp[tempLen] = '\0';

	char temp1[128];
	sprintf(temp1, Global::getInstance()->getString("77"), temp);
	delete[] temp;

	SceneLayer* layer = dynamic_cast<SceneLayer*>(getChildByTag(TAG_LAYER_SCENE));
	layer->addEndUI(temp1, duration);
}




// UI协议相关

// c->s
void MainScene::loginGame()
{
	std::string UserAcc = CCUserDefault::sharedUserDefault()->getStringForKey("UserAcc", "");
	std::string UserPass = CCUserDefault::sharedUserDefault()->getStringForKey("UserPass", "");

	if (UserAcc.length() <= 0 || UserPass.length() <= 0) {
		UserAcc = ExchangeInfo::getIdentifier();
		UserPass = "";
	}
	// ui login
	UM_Login req;
	account_info info;
	info = Global::getInstance()->GetAccountInfo();
	/*req.set_acc(UserAcc.c_str());
	req.set_passwd(UserPass.c_str());*/
	req.set_acc(info.macip);
	req.set_passwd(info.password);
	std::string str = req.SerializeAsString();

	reqSendUIMsg(IDUM_Login, str);
}

void MainScene::reqServerList()
{
	WebSocketLayer* socket = dynamic_cast<WebSocketLayer*>(getParent()->getChildByTag(1));

	UM_ReqServerList req;
	uint16_t header = IDUM_ReqServerList;
	int headUISize = sizeof(uint16_t);
	char msgUI[2];
	memcpy(msgUI, &header, headUISize);

	socket->onSendUIMsg(msgUI, headUISize);
}

void MainScene::reqServerKey(int netID, int modeID, int ticket_count)
{
	UM_ReqLoginFight req;
	req.set_serverid(netID);
	req.set_mode(modeID);
	req.set_ticket_count(ticket_count);

	std::string str = req.SerializeAsString();
	log("================================%s", str.c_str());

	reqSendUIMsg(IDUM_ReqLoginFight, str);
}

void MainScene::reqShopList()
{
	WebSocketLayer* socket = dynamic_cast<WebSocketLayer*>(getParent()->getChildByTag(1));
	UM_ReqShop req;

	uint16_t header = IDUM_ReqShop;
	int headUISize = sizeof(uint16_t);
	char msgUI[2];
	memcpy(msgUI, &header, headUISize);

	socket->onSendUIMsg(msgUI, headUISize);
}

void MainScene::reqBuyItem(int itemID)
{
	UM_BuyItem req;

	req.set_id(itemID);
	std::string str = req.SerializeAsString();

	reqSendUIMsg(IDUM_BuyItem, str);
}

void MainScene::reqUseItem(int itemID)
{
	UM_UseItem req;

	req.set_id(itemID);
	std::string str = req.SerializeAsString();

	reqSendUIMsg(IDUM_UseItem, str);
}

void MainScene::reqUnequipItem(int itemType)
{
	UM_UnequipItem req;

	req.set_itemtype(itemType);
	std::string str = req.SerializeAsString();

	reqSendUIMsg(IDUM_UnequipItem, str);
}


void MainScene::reqUpHero()
{
	WebSocketLayer* socket = dynamic_cast<WebSocketLayer*>(getParent()->getChildByTag(1));

	UM_HeroLevelup req;

	uint16_t header = IDUM_HeroLevelup;
	int headUISize = sizeof(uint16_t);
	char msgUI[2];
	memcpy(msgUI, &header, headUISize);

	socket->onSendUIMsg(msgUI, headUISize);
}

void MainScene::reqSetFocus(int type, int set, int roleID)
{
	UM_SetFocus req;

	req.set_type(type);
	req.set_set(set);
	req.set_roleid(roleID);
	//log("type is:%d, set is:%d, the roleID is:%d", type, set, roleID);
	std::string str = req.SerializeAsString();

	reqSendUIMsg(IDUM_SetFocus, str);

}

void MainScene::reqRole(int roleID)
{
	UM_ReqRole req;

	req.set_roleid(roleID);
	std::string str = req.SerializeAsString();

	reqSendUIMsg(IDUM_ReqRole, str);
}

void MainScene::reqFans(int type, int rang1, int rang2, int roleid)
{
	UM_ReqFans req;

	req.set_type(type);
	req.set_range1(rang1);
	req.set_range2(rang2);
	req.set_roleid(roleid);
	std::string str = req.SerializeAsString();

	reqSendUIMsg(IDUM_ReqFans, str);
}

void MainScene::reqRanks(int type, int subtype)
{
	UM_ReqRanks req;
	req.set_type(type);
	req.set_subtype(subtype);
	std::string str = req.SerializeAsString();

	reqSendUIMsg(IDUM_ReqRanks, str);
}

void MainScene::reqGmInfo(const char *a, int id, int count)
{
	/*
	char temp[32];
	if(count > 0)
	{
	sprintf(temp, "%s %d %d", a, id, count);
	}
	else
	{
	sprintf(temp, "%s %d", a, id);
	}
	*/
	//std::string GMStr(temp);
	std::string GMStr = a;

	//log(GMStr.c_str());
	UM_Gm req;
	req.set_command(GMStr);
	std::string str = req.SerializeAsString();

	reqSendUIMsg(IDUM_Gm, str);
}

void MainScene::reqHotMsg(int roleID)
{
	UM_GetTopMsg req;
	req.set_roleid(roleID);
	std::string str = req.SerializeAsString();

	reqSendUIMsg(IDUM_GetTopMsg, str);
}

void MainScene::reqGetMsg(int roleID, int rang1, int rang2)
{
	UM_GetMsg req;

	req.set_roleid(roleID);
	req.set_range1(rang1);
	req.set_range2(rang2);
	std::string str = req.SerializeAsString();

	reqSendUIMsg(IDUM_GetMsg, str);
}

void MainScene::reqSendMsg(int roleID, std::string content)
{
	UM_SendMsg req;

	req.set_roleid(roleID);
	req.set_content(content);
	std::string str = req.SerializeAsString();

	reqSendUIMsg(IDUM_SendMsg, str);
}

void MainScene::reqLikeMsg(int roleID, int msgID, int set)
{
	UM_LikeMsg req;

	req.set_roleid(roleID);
	req.set_msgid(msgID);
	req.set_set(set);
	std::string str = req.SerializeAsString();

	reqSendUIMsg(IDUM_LikeMsg, str);
}

void MainScene::reqFriendList(int type)
{
	UM_GetFriend req;
	req.set_type(type);

	std::string str = req.SerializeAsString();

	reqSendUIMsg(IDUM_GetFriend, str);
}

void MainScene::reqAddFriend(int roleID, std::string name)
{
	UM_InviteFriend req;
	if (roleID > 0)
	{
		req.set_roleid(roleID);
	}
	else
	{
		req.set_name(name);
	}
	std::string str = req.SerializeAsString();

	reqSendUIMsg(IDUM_InviteFriend, str);
}

void MainScene::reqResponseAdd(int flag, int roleID)
{
	UM_ResponseInvite req;

	req.set_ok(flag);
	req.set_roleid(roleID);
	std::string str = req.SerializeAsString();

	reqSendUIMsg(IDUM_ResponseInvite, str);

}

void MainScene::reqSeasonRank(int roleID)
{
	UM_ReqSeasonRank req;
	req.set_roleid(roleID);
	std::string str = req.SerializeAsString();

	reqSendUIMsg(IDUM_ReqSeasonRank, str);
}

void MainScene::reqGameRecord(int roleID)
{
	UM_ReqGameRecord req;
	req.set_roleid(roleID);
	std::string str = req.SerializeAsString();

	reqSendUIMsg(IDUM_ReqGameRecord, str);
}

void MainScene::reqSetName(std::string name, std::string passwd, int sex)
{
	UM_SetName req;
	req.set_name(name);
	req.set_passwd(passwd);
	req.set_sex(sex);
	std::string str = req.SerializeAsString();

	reqSendUIMsg(IDUM_SetName, str);
}

void MainScene::reqSetSex(int sex)
{
	UM_SetSex req;
	req.set_sex(sex);
	std::string str = req.SerializeAsString();

	reqSendUIMsg(IDUM_SetSex, str);
}

void MainScene::reqSetDesc(std::string desc)
{
	UM_SetDesc req;
	req.set_desc(desc);
	std::string str = req.SerializeAsString();

	reqSendUIMsg(IDUM_SetDesc, str);
}

void MainScene::reqSetGeo(int province)
{
	UM_SetGeo req;
	req.set_province(province);
	std::string str = req.SerializeAsString();

	reqSendUIMsg(IDUM_SetGeo, str);
}

void MainScene::reqSendPhoto(int slot, std::string dataStr)
{
	log("picdatalen:%d", dataStr.length());
	UM_SetPhoto req;

	photo_data *data = new photo_data;
	data->set_slot(slot);
	data->set_data(dataStr);

	req.set_allocated_data(data);
	std::string str = req.SerializeAsString();

	reqSendUIMsg(IDUM_SetPhoto, str);
}

void MainScene::reqGetPhoto(int roleID)
{
	UM_ReqPhotos req;

	req.set_roleid(roleID);
	std::string str = req.SerializeAsString();

	reqSendUIMsg(IDUM_ReqPhotos, str);

}

void MainScene::reqSetIcon(int icon, std::string data)
{
	UM_SetIcon req;

	req.set_icon(icon);
	if (!data.empty())
		req.set_data(data);

	std::string str = req.SerializeAsString();

	reqSendUIMsg(IDUM_SetIcon, str);
}

void MainScene::reqGetTickets()
{
	WebSocketLayer* socket = dynamic_cast<WebSocketLayer*>(getParent()->getChildByTag(1));

	uint16_t header = IDUM_GetTicket;
	int headUISize = sizeof(uint16_t);
	char msgUI[2];
	memcpy(msgUI, &header, headUISize);

	socket->onSendUIMsg(msgUI, headUISize);
}

void MainScene::reqIcons(std::vector<int> iconList)
{
	UM_ReqIcons req;

	std::vector<int>::iterator it = iconList.begin();
	for (; it != iconList.end(); ++it)
	{
		int icon = *it;
		req.add_list(icon);

	}
	std::string str = req.SerializeAsString();

	reqSendUIMsg(IDUM_ReqIcons, str);

}

void MainScene::reqExitFight()
{
	WebSocketLayer* socket = dynamic_cast<WebSocketLayer*>(getParent()->getChildByTag(1));

	uint16_t header = IDUM_ExitFight;
	int headUISize = sizeof(uint16_t);
	char msgUI[2];
	memcpy(msgUI, &header, headUISize);

	socket->onSendUIMsg(msgUI, headUISize);
}

void MainScene::reqSign()
{
	WebSocketLayer* socket = dynamic_cast<WebSocketLayer*>(getParent()->getChildByTag(1));

	uint16_t header = IDUM_Sign;
	int headUISize = sizeof(uint16_t);
	char msgUI[2];
	memcpy(msgUI, &header, headUISize);

	socket->onSendUIMsg(msgUI, headUISize);
}

void MainScene::reqAward()
{
	WebSocketLayer* socket = dynamic_cast<WebSocketLayer*>(getParent()->getChildByTag(1));

	uint16_t header = IDUM_Award;
	int headUISize = sizeof(uint16_t);
	char msgUI[2];
	memcpy(msgUI, &header, headUISize);

	socket->onSendUIMsg(msgUI, headUISize);
}


// Common
void MainScene::reqSendUIMsg(uint16_t type, std::string str)
{
	WebSocketLayer* socket = dynamic_cast<WebSocketLayer*>(getParent()->getChildByTag(1));

	uint16_t header = type;
	int headSize = sizeof(uint16_t);

	char* msgUI = new char[headSize + str.length()];

	//char msgUI[headSize + str.length()];
	memcpy(msgUI, &header, headSize);
	memcpy(msgUI + headSize, str.c_str(), str.length());
	headSize += str.length();

	socket->onSendUIMsg(msgUI, headSize);

	delete[] msgUI;
}





// s->c
void MainScene::setPlayerInfo(const cocos2d::network::WebSocket::Data &data)
{
	// 此对象释放有问题  改为静态对象 只创建一次
	static UM_EnterGame resp;
	bool re = resp.ParseFromArray(data.bytes + 2, data.len - 2);
	if (re)
	{
		const role_info& userInfo = resp.info();
		user_info info;
		info.roleID = userInfo.roleid();
		info.roleName = userInfo.name();
		info.createTime = userInfo.create_time();
		info.icon = userInfo.icon();
		info.sex = userInfo.sex();
		info.level = userInfo.level();
		info.copper = userInfo.copper();
		info.gold = userInfo.gold();
		info.duanwei = userInfo.duanwei();
		info.stars = userInfo.star();
		info.mvpCount = userInfo.mvp_cnt();
		info.chapionCount = userInfo.champion_cnt();
		info.eatPlayerCount = userInfo.eat1_cnt();
		info.eatCount = userInfo.eat2_cnt();
		info.maxMass = userInfo.max_mass();
		info.province = userInfo.province();
		info.city = userInfo.city();
		info.describe = userInfo.describe();
		info.heroid = userInfo.heroid();
		info.herolevel = userInfo.herolevel();
		info.exp = userInfo.exp();
		info.freeTicket = userInfo.free_ticket();
		info.fefreshTime = userInfo.refresh_time();
		info.isSign = userInfo.sign();
		info.lastSignTime = userInfo.last_sign_time();
		info.signTags = userInfo.sign_tags();
		info.awardRefreshTime = userInfo.award_refresh_time();


		std::vector<bool> gots;
		int gotSize = userInfo.award_gots_size();
		log("gotSize:%d", gotSize);
		for (int i = 0; i < gotSize; i++)
		{
			bool flag = userInfo.award_gots(i);
			gots.push_back(flag);
		}
		info.awardGots = gots;

		int num = userInfo.equips_size();
		for (int i = 0; i<num; i++) {
			int tpID = userInfo.equips(i).tpltid();
			item ite = Resource::sharedResource()->getItemForID(tpID);
			info.mEquip[ite.itemType] = tpID;
			//CCLOG("equip:%d",tpID);
		}

		if (info.roleName == "")
		{
			char temp[128] = { 0 };
			sprintf(temp, "S%d", info.roleID);
			info.roleName = temp;
		}

		Global::getInstance()->SetUserInfo(info);

		m_isFighting = resp.fighting();


		// 战斗服重连
		if (m_isFighting)
		{
			//reOpenSocket();

			ReqOpenFight* layer = ReqOpenFight::create();
			addChild(layer, 100);
		}
		else
		{
			// 获取服务器列表
			reqServerList();

			LoginLayer* layer = (LoginLayer*)getChildByTag(TAG_LAYER_LOGIN);
			if (layer) {
				layer->InitHeadInfo();
			}
		}
	}
}

void MainScene::respSyncRole(const cocos2d::network::WebSocket::Data &data)
{
	UM_SyncRole resp;
	bool re = resp.ParseFromArray(data.bytes + 2, data.len - 2);
	if (re)
	{
		const role_info& userInfo = resp.info();
		user_info info;
		info.roleID = userInfo.roleid();
		info.roleName = userInfo.name();
		info.createTime = userInfo.create_time();
		info.icon = userInfo.icon();
		info.sex = userInfo.sex();
		info.level = userInfo.level();
		info.copper = userInfo.copper();
		info.gold = userInfo.gold();
		info.duanwei = userInfo.duanwei();
		info.stars = userInfo.star();
		info.mvpCount = userInfo.mvp_cnt();
		info.chapionCount = userInfo.champion_cnt();
		info.eatPlayerCount = userInfo.eat1_cnt();
		info.eatCount = userInfo.eat2_cnt();
		info.maxMass = userInfo.max_mass();
		info.province = userInfo.province();
		info.city = userInfo.city();
		info.describe = userInfo.describe();
		info.heroid = userInfo.heroid();
		info.herolevel = userInfo.herolevel();
		info.exp = userInfo.exp();
		info.freeTicket = userInfo.free_ticket();
		info.fefreshTime = userInfo.refresh_time();
		info.isSign = userInfo.sign();
		info.lastSignTime = userInfo.last_sign_time();
		info.signTags = userInfo.sign_tags();
		info.awardRefreshTime = userInfo.award_refresh_time();

		std::vector<bool> gots;
		int gotSize = userInfo.award_gots_size();

		log("gotSize:%d", gotSize);
		for (int i = 0; i < gotSize; i++)
		{
			bool flag = userInfo.award_gots(i);
			gots.push_back(flag);
		}
		info.awardGots = gots;

		int num = userInfo.equips_size();
		for (int i = 0; i<num; i++) {
			int tpID = userInfo.equips(i).tpltid();
			item ite = Resource::sharedResource()->getItemForID(tpID);
			info.mEquip[ite.itemType] = tpID;
			//CCLOG("equip:%d",tpID);
		}

		if (info.roleName == "")
		{
			char temp[128] = { 0 };
			sprintf(temp, "S%d", info.roleID);
			info.roleName = temp;
		}

		Global::getInstance()->SetUserInfo(info);
	}
}

void MainScene::respServerList(const cocos2d::network::WebSocket::Data &data)
{
	UM_ServerList resp;
	bool re = resp.ParseFromArray(data.bytes + 2, data.len - 2);
	if (re)
	{
		int num = resp.list_size();
		//log("list number is:%d", num);
		for (int i = 0; i < num; i++)
		{
			server_info info = resp.list(i);
			netInfo net_info;
			net_info.m_netID = info.serverid();
			net_info.m_netUrl = info.serverip();
			char temp[16];
			sprintf(temp, "%d", info.serverport());
			net_info.m_netPort = temp;
			net_info.m_netName = info.servername();

			Global::getInstance()->addNetInfos(net_info);
		}

		/*if (m_isFighting)
		{
			reqServerKey(0, 0, 0);
		}
		else
		{
			LoginLayer* login = dynamic_cast<LoginLayer*>(getChildByTag(TAG_LAYER_LOGIN));
			if (login)
				login->updateNetInfos();
		}*/
	}
}

void MainScene::respServerKey(const cocos2d::network::WebSocket::Data &data)
{
	UM_LoginFightKey resp;
	bool re = resp.ParseFromArray(data.bytes + 2, data.len - 2);
	if (re)
	{
		int netID = resp.serverid();
		int netKey = resp.key();
		int roomId = resp.roomid();
		Global::getInstance()->SetRoomId(roomId);

		if (m_isFighting)
		{
			reSetNetKey(netID, netKey);
		}
		else
		{
			LoginLayer* login = dynamic_cast<LoginLayer*>(getChildByTag(TAG_LAYER_LOGIN));
			if (login)
				login->setNetKey(netKey);
		}
	}
}

void MainScene::respErrors(const cocos2d::network::WebSocket::Data &data)
{
	UM_Response resp;
	bool re = resp.ParseFromArray(data.bytes + 2, data.len - 2);
	if (re)
	{
		uint32_t msgID = resp.msgid();
		SERR err = (SERR)resp.err();
		switch (err) {
		case SERR_OK:
			//log("response id is:%d. err message is:%s", msgID, "正常");
			if (msgID == IDUM_SetName) {
				LoginLayer* layer = (LoginLayer*)getChildByTag(TAG_LAYER_LOGIN);
				if (layer) {
					layer->SetNameOK();
				}
			}

			if (msgID == IDUM_SetGeo)
			{
				//Global::getInstance()->ShowPromBox("修改成功");
			}

			if (msgID == IDUM_BuyItem)
			{

				Global::getInstance()->ShowPromBox(Global::getInstance()->getString("78"));
				ShopLayerBase* layer = (ShopLayerBase*)getChildByTag(TAG_LAYER_SHOP);
				if (layer) {
					layer->RushLab();
				}

				LoginLayer* layer1 = (LoginLayer*)getChildByTag(TAG_LAYER_LOGIN);
				if (layer1)
					layer1->rushmenpiao();
			}

			if (msgID == IDUM_UseItem) {
				Node* jinhe = getChildByTag(TAG_LAYER_SHOP)->getChildByTag(3);
				if (!jinhe) {
					Global::getInstance()->ShowPromBox(Global::getInstance()->getString("79"));
				}

				ShopLayerBase* layer = (ShopLayerBase*)getChildByTag(TAG_LAYER_SHOP);
				if (layer) {
					layer->RushLab();
				}
			}

			if (msgID == IDUM_SetFocus)
			{
				Global::getInstance()->ShowPromBox(Global::getInstance()->getString("80"));
				ZhanDouEnd* layer = (ZhanDouEnd*)getChildByTag(TAG_GAME_END);
				if (layer)
				{
					layer->ResSetFans();
				}
			}

			if (msgID == IDUM_SetIcon) {
				user_info us = Global::getInstance()->GetUserInfo();
				user_info pl = Global::getInstance()->GetPlayerInfo();
				if (us.roleID == pl.roleID) {
					Global::getInstance()->SetplayerInfo(us);
				}
				UserInfo* user = (UserInfo*)getChildByTag(TAG_LAYER_USERINFO);
				user->setHeadIcon();
			}

			if (msgID == IDUM_GetTicket) {
				Global::getInstance()->ShowPromBox(Global::getInstance()->getString("81"));
				LoginLayer* layer = (LoginLayer*)getChildByTag(TAG_LAYER_LOGIN);
				if (layer)
					layer->rushmenpiao();
			}

			if (msgID == IDUM_SetPhoto) {
				Global::getInstance()->ShowPromBox(Global::getInstance()->getString("82"));
				user_info user = Global::getInstance()->GetPlayerInfo();
				reqGetPhoto(user.roleID);
			}

			if (msgID == IDUM_Gm)
			{
				//Global::getInstance()->ShowPromBox("GM 更新");
			}

			if (msgID == IDUM_ExitFight) {
				BackToLoginLayer(TAG_LAYER_SCENE);
				//removeChildByTag(TAG_LAYER_SCENE,true);
				Global::getInstance()->clearMainNodes();
				removeChildByTag(TAG_GAME_COLOR_BG, true);
				removeChildByTag(TAG_LAYER_GRID, true);
				CloseWebNet();
			}

			if (msgID == IDUM_Sign)
			{
				Global::getInstance()->ShowPromBox(Global::getInstance()->getString("83"));

				user_info uInfo = Global::getInstance()->GetUserInfo();

				struct timeval now;
				//CCTime::gettimeofdayCocos2d(&now, NULL);
				gettimeofday(&now, NULL);

				struct tm *tme;
				time_t timep = now.tv_sec;
				tme = localtime(&timep);
				int day = tme->tm_mday;
				std::vector<QianDaoUse> mQdo = Global::getInstance()->GetQiandao();
				for (int i = 0; i<mQdo.size(); i++) {
					if (day == mQdo[i].mDay) {
						reqAward();
						break;
					}
				}

				LoginLayer* layer = (LoginLayer*)getChildByTag(TAG_LAYER_LOGIN);
				if (layer)
					layer->rushqiandao();
			}
			if (msgID == IDUM_Award)
			{
				LoginLayer* layer = (LoginLayer*)getChildByTag(TAG_LAYER_LOGIN);
				if (layer)
					layer->rushqiandao();
			}
			break;

		case SERR_Exception:
			log("error id is:%d. err message is:%s", msgID, "服务器异常");
			break;

		case SERR_Msg:
			log("error id is:%d. err message is:%s", msgID, "error msg");
			break;

		case SERR_Notplt:
			log("error id is:%d. err message is:%s", msgID, "no data template");
			break;

		case SERR_Illegal:
			log("error id is:%d. err message is:%s", msgID, "非法的");
			break;

		case SERR_Arg:
			log("error id is:%d. err message is:%s", msgID, "参数错误");
			break;

		case SERR_State:
			log("error id is:%d. err message is:%s", msgID, "状态错误");
			break;

		case SERR_Remote:
			log("error id is:%d. err message is:%s", msgID, "远端异常");
			break;

		case SERR_Nocopper:
			log("error id is:%d. err message is:%s", msgID, "铜币不足");
			break;

		case SERR_Nogold:
			log("error id is:%d. err message is:%s", msgID, "元宝不足");
			break;

		case SERR_Noticket:
			log("error id is:%d. err message is:%s", msgID, "入场券不足");
			break;

		case SERR_Nomat:
			log("error id is:%d. err message is:%s", msgID, "材料不足");
			break;

		case SERR_Norole:
			log("error id is:%d. err message is:%s", msgID, "没有指定的角色");
			break;

		case SERR_Notfriend:
			log("error id is:%d. err message is:%s", msgID, "不是好友");
			break;

		case SERR_Friendyet:
			log("error id is:%d. err message is:%s", msgID, "已经是好友");
			break;

		case SERR_HasInvite:
			log("error id is:%d. err message is:%s", msgID, "已经邀请");
			break;

		case SERR_Blackyet:
			log("error id is:%d. err message is:%s", msgID, "已经拉黑");
			break;

		case SERR_FightGone:
		{
							   Global::getInstance()->ShowPromBox(Global::getInstance()->getString("84"));
		}
			break;

		case SERR_ReenterFight:
		{
								  Global::getInstance()->ShowPromBox(Global::getInstance()->getString("85"));
		}
			break;

		case SERR_ExitFight:
		{
							   Global::getInstance()->ShowPromBox(Global::getInstance()->getString("86"));
		}
			break;

		default:
			break;
		}
	}
}

void MainScene::respShopList(const cocos2d::network::WebSocket::Data &data)
{
	UM_Shop resp;
	bool re = resp.ParseFromArray(data.bytes + 2, data.len - 2);
	if (re)
	{
		std::vector<shop_item> items;
		int num = resp.list_size();
		log("list number is:%d", num);
		for (int i = 0; i < num; i++)
		{
			shop_item item = resp.list(i);
			log("shop item id is:%d", item.tpltid());
			items.push_back(item);
		}
		Global::getInstance()->SetShopItems(items);
		this->CheckLayer(MainScene::TAG_LAYER_SHOP);
	}
}

void MainScene::respHeroUp(const cocos2d::network::WebSocket::Data &data)
{
	UM_Hero resp;
	bool re = resp.ParseFromArray(data.bytes + 2, data.len - 2);
	if (re)
	{
		int heroid = resp.heroid();
		int herolevel = resp.herolevel();

		Global::getInstance()->HeroLeveUp(heroid, herolevel);
	}
}

void MainScene::respEquipUpdate(const cocos2d::network::WebSocket::Data &data)
{
	UM_EquipUpdate resp;
	bool re = resp.ParseFromArray(data.bytes + 2, data.len - 2);
	if (re)
	{
		int equipType = resp.itemtype();
		int equipID = resp.id();

		Global::getInstance()->EquipUpdate(equipType, equipID);
	}
}

// item buy or use
void MainScene::respItemUpdate(const cocos2d::network::WebSocket::Data &data)
{
	for (int i = 2; i < data.len; i++) {
		//        printf("%d,", (uint8_t)data.bytes[i]);
	}
	UM_ItemUpdate resp;
	bool re = resp.ParseFromArray(data.bytes + 2, data.len - 2);
	if (re)
	{
		int num = resp.list_size();

		int type = resp.type();

		std::vector<item> arrUP;

		for (int i = 0; i < num; i++)
		{
			item_info info = resp.list(i);

			user_bag bag;
			bag.mId = info.tpltid();
			bag.count = info.stack();

			item ite = Resource::sharedResource()->getItemForID(bag.mId);
			user_bag bagI = Global::getInstance()->GetBagItem(bag.mId);

			ite.maxCount = bag.count - bagI.count;

			if (ite.maxCount > 0 && bag.mId == 701) {
				ite.itemName = Global::getInstance()->getString("87");
				arrUP.push_back(ite);
			}
			else if (ite.maxCount > 0 && bag.mId == 702){
				ite.itemName = Global::getInstance()->getString("88");
				arrUP.push_back(ite);
			}
			else if (ite.maxCount > 0 && bag.mId == 1001){
				ite.itemName = Global::getInstance()->getString("89");
				arrUP.push_back(ite);
			}
			else if (ite.maxCount > 0 && ite.itemID){
				arrUP.push_back(ite);
			}

			Global::getInstance()->AddItemForBag(bag.mId, bag);
		}
		if (m_isFistGetItem == false) {
			if (type == 1)
			{
				Global::getInstance()->ShowPromMoveBox(arrUP);
			}
		}
		else{
			m_isFistGetItem = false;
		}
	}
}

void MainScene::respRoleInfo(const cocos2d::network::WebSocket::Data &data)
{
	UM_RoleInfo resp;
	bool re = resp.ParseFromArray(data.bytes + 2, data.len - 2);
	if (re)
	{
		role_info userInfo = resp.info();
		user_info info;
		info.roleID = userInfo.roleid();
		info.roleName = userInfo.name();
		info.createTime = userInfo.create_time();
		info.icon = userInfo.icon();
		info.sex = userInfo.sex();
		info.level = userInfo.level();
		info.copper = userInfo.copper();
		info.gold = userInfo.gold();
		info.duanwei = userInfo.duanwei();
		info.stars = userInfo.star();
		info.mvpCount = userInfo.mvp_cnt();
		info.chapionCount = userInfo.champion_cnt();
		info.eatPlayerCount = userInfo.eat1_cnt();
		info.eatCount = userInfo.eat2_cnt();
		info.maxMass = userInfo.max_mass();
		info.province = userInfo.province();
		info.city = userInfo.city();
		info.describe = userInfo.describe();
		info.heroid = userInfo.heroid();
		info.herolevel = userInfo.herolevel();
		info.exp = userInfo.exp();

		info.freeTicket = userInfo.free_ticket();
		info.fefreshTime = userInfo.refresh_time();
		//log("user id:%d, name is:%s, sex is:%d, createTime is:%d, level is:%d", info.roleID, info.roleName.c_str(), info.sex, info.createTime, info.level);

		//log("duanwei is :%d, stars is:%d", info.duanwei, info.stars);
		if (info.roleName == "")
		{
			char temp[128] = { 0 };
			sprintf(temp, "S%d", info.roleID);
			info.roleName = temp;
		}
		Global::getInstance()->SetplayerInfo(info);

		//gm
		//    reqGmInfo("duanwei", 7);
		ZhanDouEnd* layer = (ZhanDouEnd*)getChildByTag(TAG_GAME_END);
		if (layer) {
			layer->ShowUserLowInfo();
		}
		else{
			CheckLayer(TAG_LAYER_USERINFO);
		}
	}
}

void MainScene::respFans(const cocos2d::network::WebSocket::Data &data)
{
	RelationShipBase* layer = (RelationShipBase*)getChildByTag(TAG_LAYER_RELATION);
	if (layer)
		layer->respFans(data);

	UserInfo* ulayer = (UserInfo*)getChildByTag(TAG_LAYER_USERINFO);
	if (ulayer)
		ulayer->respFans(data);
}

void MainScene::respRanks(const cocos2d::network::WebSocket::Data &data)
{
	RankingLayerBase* layer = (RankingLayerBase*)getChildByTag(TAG_LAYER_RANKING);
	if (layer)
		layer->respRanks(data);
}

void MainScene::respFightLikes(const cocos2d::network::WebSocket::Data &data)
{
	UM_FightLikes resp;
	bool re = resp.ParseFromArray(data.bytes + 2, data.len - 2);
	std::vector<EndGame2> infos;
	if (re)
	{
		int attenSize = resp.attentions_size();
		int likeSize = resp.likes_size();
		if (attenSize == likeSize)
		{
			for (int i = 0; i < attenSize; ++i)
			{
				EndGame2 info;
				info.roleID = resp.roles(i);
				info.isLike = resp.likes(i);
				info.isAttention = resp.attentions(i);

				infos.push_back(info);
			}
		}
	}

	if (getChildByTag(TAG_GAME_END) && (ZhanDouEnd*)getChildByTag(TAG_GAME_END))
	{
		ZhanDouEnd* end = dynamic_cast<ZhanDouEnd*>(getChildByTag(TAG_GAME_END));
		end->setLikes(infos);
	}
	else
	{
		removeChildByTag(TAG_LAYER_SCENE, true);
		ZhanDouEnd* gameEnd = ZhanDouEnd::create();
		addChild(gameEnd, 2, TAG_GAME_END);
		gameEnd->setLikes(infos);

		Global::getInstance()->clearMainNodes();
		removeChildByTag(TAG_GAME_COLOR_BG, true);
		removeChildByTag(TAG_LAYER_GRID, true);
	}

}

void MainScene::respHotMsg(const cocos2d::network::WebSocket::Data &data)
{
	UserInfo* ulayer = (UserInfo*)getChildByTag(TAG_LAYER_USERINFO);
	if (ulayer)
		ulayer->respHotLiuyan(data);
}

void MainScene::respMsgList(const cocos2d::network::WebSocket::Data &data)
{
	UserInfo* ulayer = (UserInfo*)getChildByTag(TAG_LAYER_USERINFO);
	if (ulayer)
		ulayer->respLiuyan(data);
}

void MainScene::respFriendList(const cocos2d::network::WebSocket::Data &data)
{
	if (data.len <= 2)
		return;

	RelationShipBase* layer = (RelationShipBase*)getChildByTag(TAG_LAYER_RELATION);
	if (layer)
		layer->respFriends(data);
}

void MainScene::respAddFriend(const cocos2d::network::WebSocket::Data &data)
{
	UM_AddFriend resp;
	bool re = resp.ParseFromArray(data.bytes + 2, data.len - 2);
	if (re)
	{
		int type = resp.type();
		if (type == 2) {
			friend_info info = resp.info();

			//reqResponseAdd(1, info.roleid());
			std::string name = info.name();
			char tem[128] = { 0 };
			sprintf(tem, Global::getInstance()->getString("90"), name.c_str());
			Global::getInstance()->ShowPromBox(tem);
			//log("addFriend : OK");
			ZhanDouEnd* layer = (ZhanDouEnd*)getChildByTag(TAG_GAME_END);
			if (layer)
			{
				layer->ResAddFriend();
			}
		}
	}
}

void MainScene::respAddInvite(const cocos2d::network::WebSocket::Data &data)
{
	UM_AddInvite resp;
	bool re = resp.ParseFromArray(data.bytes + 2, data.len - 2);
	if (re)
	{
		int type = resp.type();
		if (type == 2) {
			friend_info info = resp.info();

			//reqResponseAdd(1, info.roleid());

			AddFriend* fff = AddFriend::create();
			addChild(fff, 100);

			fff->InitFriend(info);
		}
	}
}

// 提示用户被拒绝
void MainScene::respDelInvite(const cocos2d::network::WebSocket::Data &data)
{
	UM_DelInvite resp;
	bool re = resp.ParseFromArray(data.bytes + 2, data.len - 2);
	if (re)
	{
		int type = resp.type();
		if (type == 2) {
			friend_info info = resp.info();
			std::string name = info.name();
			char tem[128] = { 0 };
			sprintf(tem, Global::getInstance()->getString("91"), name.c_str());
			Global::getInstance()->ShowPromBox(tem);
		}
	}
}

void MainScene::respSeasonRank(const cocos2d::network::WebSocket::Data &data)
{
	UserInfo* ulayer = (UserInfo*)getChildByTag(TAG_LAYER_USERINFO);
	if (ulayer)
		ulayer->resSeasonRank(data);

}

void MainScene::respGameRecord(const cocos2d::network::WebSocket::Data &data)
{
	UserInfo* ulayer = (UserInfo*)getChildByTag(TAG_LAYER_USERINFO);
	if (ulayer)
		ulayer->resGameRecode(data);
}

void MainScene::respPhotos(const cocos2d::network::WebSocket::Data &data)
{
	for (int i = 2; i < data.len; i++) {
		//        printf("%d,", (uint8_t)data.bytes[i]);
	}
	if (data.len < 2)
		return;
	UM_Photos resp;
	bool re = resp.ParseFromArray(data.bytes + 2, data.len - 2);
	if (re)
	{
		int count = resp.list_size();
		std::vector<std::string> mArr;
		for (int i = 0; i<count; i++) {
			mArr.push_back(resp.list(i).data());
		}
		UserInfo* ulayer = (UserInfo*)getChildByTag(TAG_LAYER_USERINFO);
		if (ulayer)
		{
			ulayer->resHeadImg(count);
			ulayer->resPhoto(mArr);
		}

		LoginLayer* llayer = (LoginLayer*)getChildByTag(TAG_LAYER_LOGIN);
		if (llayer)
		{
			for (int i = 0; i<count; i++) {
				char spname[64];
				sprintf(spname, "/headImage%d.jpg", i + 1);

				ExchangeInfo::SaveImag(mArr[i].c_str(), spname);
			}

			llayer->InitHeadInfo();
		}
	}
}

void MainScene::respIcons(const cocos2d::network::WebSocket::Data &data)
{
	UM_Icons resp;
	bool re = resp.ParseFromArray(data.bytes + 2, data.len - 2);
	if (re)
	{
		int count = resp.list_size();
		std::vector<icon_data> arr;
		arr.clear();
		for (int i = 0; i < count; i++)
		{
			icon_data icon = resp.list(i);
			arr.push_back(icon);
		}

		switch (m_CurrTag) {
		case TAG_LAYER_RANKING:
		{
								  RankingLayerBase* layer = (RankingLayerBase*)getChildByTag(TAG_LAYER_RANKING);
								  if (layer)
									  layer->respRankIcons(arr);
		}
			break;

		case TAG_LAYER_RELATION:
		{
								   RelationShipBase* Ship = (RelationShipBase*)getChildByTag(TAG_LAYER_RELATION);
								   if (Ship) {
									   Ship->resIcon(arr);
								   }
		}

		case TAG_GAME_END:
		{
							 ZhanDouEnd* layer = (ZhanDouEnd*)getChildByTag(TAG_GAME_END);
							 if (layer) {
								 layer->resIcon(arr);
							 }
		}

		default:
			break;
		}

	}
}

void MainScene::respAwardList(const cocos2d::network::WebSocket::Data &data)
{
	UM_AwardList resp;
	bool re = resp.ParseFromArray(data.bytes + 2, data.len - 2);
	if (re)
	{
		std::vector<QianDaoUse> mQinfo;
		mQinfo.clear();

		int count = resp.list_size();
		//log("签到:%d",count);
		for (int i = 0; i < count; i++)
		{
			award_info info = resp.list(i);
			QianDaoUse use;
			use.mType = info.type();
			use.mDay = info.day();
			mQinfo.push_back(use);
		}

		Global::getInstance()->SetQiandao(mQinfo);
	}
}




////end

// 网络断开重连
void MainScene::confirmReConnectFighting()
{
	if (Global::getInstance()->getNetInfos().size() > 0)
		reqServerKey(0, 0, 0);
	else
	{
		reqServerList();
	}
}

void MainScene::cancelReConnectFighting()
{
	m_isFighting = false;
	// 获取服务器列表
	reqServerList();

	LoginLayer* layer = (LoginLayer*)getChildByTag(TAG_LAYER_LOGIN);
	if (layer) {
		layer->InitHeadInfo();
	}
}

void MainScene::reqReLogin()
{
	LoginLayer* login = dynamic_cast<LoginLayer*>(getChildByTag(TAG_LAYER_LOGIN));
	if (login)
		login->relogin();
	else
	{
		scheduleOnce(schedule_selector(MainScene::reLogin), 0.5f);
	}
}

void MainScene::reLogin(float ft)
{
	loginGame();
}

void MainScene::reOpenSocket()
{
	//    bool isConnect = OpenWebSocket(m_ipAddress.c_str(), m_ipPort.c_str());
	//    if(!isConnect)
	//        return;
	//    
	//    schedule(schedule_selector(MainScene::reConnectFightServer), 0.1f);
}

void MainScene::reConnectFightServer(float ft)
{
	/*if (!Global::getInstance()->getConnectState())
		return;*/

	unschedule(schedule_selector(MainScene::reConnectFightServer));

	//reqServerKey(0, 0, 0);
	std::string nick = CCUserDefault::sharedUserDefault()->getStringForKey("UserName");
	enterGame(nick.c_str(), m_netKey);
}

void MainScene::reSetNetKey(int netID, int netKey)
{
	std::vector<netInfo> infos = Global::getInstance()->getNetInfos();
	if (infos.size() == 0)
		return;

	std::vector<netInfo>::iterator it = infos.begin();
	for (; it != infos.end(); ++it)
	{
		netInfo info = *it;
		if (info.m_netID == netID)
		{
			bool isConnect = OpenWebSocket(info.m_netUrl.c_str(), info.m_netPort.c_str());
			if (!isConnect)
				return;
			m_netKey = netKey;

			schedule(schedule_selector(MainScene::reConnectFightServer), 0.1f);
		}
	}




	//    std::string nick = CCUserDefault::sharedUserDefault()->getStringForKey("UserName");
	//    enterGame(nick.c_str(), netKey);
}

// 复活
void MainScene::reRebirth()
{
	ReqRebirth msg;
	msg.msgid = 22;

	WebSocketLayer* socket = dynamic_cast<WebSocketLayer*>(getParent()->getChildByTag(1));
	socket->onSendMsg((char*)&msg, sizeof(ReqRebirth));

}

void MainScene::respDuanXianChongLian(const cocos2d::network::WebSocket::Data &data)
{
	static UM_Reconnect resp;
	bool re = resp.ParseFromArray(data.bytes + 2, data.len - 2);
	if (re)
	{
		ReqOpenFight* layer = ReqOpenFight::create();
		addChild(layer, 100);
	}
}

void MainScene::reqDuanXianChongLian()
{
	static UM_ReqReconncet req;
	// ui login
	account_info info;
	info = Global::getInstance()->GetAccountInfo();
	req.set_playerid(info.playerid);
	std::string str = req.SerializeAsString();

	reqSendUIMsg(IDUM_ReqReconnect, str);
}

void MainScene::reqZuDui()
{
	static UM_ReqTeamFight req;
	account_info info;
	info = Global::getInstance()->GetAccountInfo();
	
	req.set_playerid(info.playerid);
	req.set_serverid(0);
	req.set_mode(10);
	req.set_ticket_count(1);
	std::string str = req.SerializeAsString();

	reqSendUIMsg(IDUM_ReqTeamFight, str);
}

void MainScene::respZuDui(const cocos2d::network::WebSocket::Data &data)
{
	static UM_TeamFight resp;
	log("shen qing zudui dengdai zhong ");
	bool re = resp.ParseFromArray(data.bytes + 2, data.len - 2);
	if (re)
	{
		log("zudui chenggong");
		/*ReqOpenFight* layer = ReqOpenFight::create();
		addChild(layer, 100);*/
	}
	else
	{
		log("zudui shibai");
	}
}

void MainScene::respQuXiaoZuDui(const cocos2d::network::WebSocket::Data &data)
{
	static UM_CancelFight resp;
	log("qu xiao zudui zhong");
	bool re = resp.ParseFromArray(data.bytes + 2, data.len - 2);
	if (re)
	{
		log("qu xiao zudui chenggong");
		/*ReqOpenFight* layer = ReqOpenFight::create();
		addChild(layer, 100);*/
	}
	else
	{
		log("qu xiao zudui shibai");
	}
}

void MainScene::reqQuXiaoZuDui()
{
	static UM_ReqCancelFight req;
	account_info info;
	info = Global::getInstance()->GetAccountInfo();
	req.set_playerid(info.playerid);
	std::string str = req.SerializeAsString();
	reqSendUIMsg(IDUM_ReqCancelFight, str);
}

void MainScene::respZhanDouZhunBei(const cocos2d::network::WebSocket::Data &data)
{
	static UM_ReadyFight resp;
	bool re = resp.ParseFromArray(data.bytes + 2, data.len - 2);
	if (re)
	{
		log("zhandou zhunbei");
		//战斗准备倒计时 时间
		uint32_t time = resp.time();
		/*ReqOpenFight* layer = ReqOpenFight::create();
		addChild(layer, 100);*/
	}
	else
	{
		log("not zhandou zhunbei");
	}
}

void MainScene::reqServerList1(float f)
{
	WebSocketLayer* socket = dynamic_cast<WebSocketLayer*>(getParent()->getChildByTag(1));

	UM_ReqServerList req;
	uint16_t header = IDUM_ReqServerList;
	int headUISize = sizeof(uint16_t);
	char msgUI[2];
	memcpy(msgUI, &header, headUISize);

	socket->onSendUIMsg(msgUI, headUISize);
}

void MainScene::readyFightDaoJiShi()
{
	 daojishiNode = CSLoader::createNode("daojishi10s.csb");
	addChild(daojishiNode,100000);
	Size size = Director::getInstance()->getWinSize();
	daojishiNode->setPosition(size.width / 2, size.height / 2);

	ActionTimeline* action = CSLoader::createTimeline("daojishi10s.csb");
	daojishiNode->runAction(action);
	//从第0帧开始，并且只播放一次  
	action->gotoFrameAndPlay(0, false);
	//获取动画持续时间  
	float duration = action->getDuration();
	//获取结束帧，经测试是你动画添加帧的最后位置  
	float lastFrame = action->getEndFrame();
	//捕获事件帧  
	//action->setFrameEventCallFunc(CC_CALLBACK_1(SplashScene::onFrameEvent, this));
	//捕获到最后一帧的回调事件，比如你总共是60帧的动画，那么60就是最后帧，每次循环到60都会触发一次  
	action->setLastFrameCallFunc(CC_CALLBACK_0(MainScene::delteReadyFightDaoJiShi, this));

}

void MainScene::delteReadyFightDaoJiShi()
{
	daojishiNode->removeFromParent();
	daojishiNode = nullptr;
}

/////////////////
//战斗结束
/////////////////
ZhanDouEnd::ZhanDouEnd()
{
	mRankVec.clear();
	mTouchDex = 0;
	mCurTouch = 1;
}
ZhanDouEnd::~ZhanDouEnd()
{
	mRankVec.clear();
}

bool ZhanDouEnd::init()
{
	if (!Layer::init())
		return false;

	Sprite* back = Sprite::create("center_back.png");
	back->setPosition(Vec2(winSize.width * 0.5f, winSize.height * 0.5f));
	back->setScale(0.6f);
	addChild(back);


	Sprite* dikuang = Sprite::create("zhaopian-03.png");
	dikuang->setScale(0.77f);
	dikuang->setPosition(Vec2(winSize.width * 0.5f, winSize.height * 0.5f + 280));
	addChild(dikuang);

	dikuang = Sprite::create("benlunjieshu-01.png");
	dikuang->setScale(0.6f);
	dikuang->setPosition(Vec2(winSize.width * 0.5f, winSize.height * 0.5f + 280));
	addChild(dikuang);

	Button* lef = Button::createBtnWithSpriteFrameName("jiesuan-btn-2.png", false);
	lef->setPosition(Vec2(winSize.width*0.5f - 275, winSize.height * 0.5f + 210));
	lef->setScale(0.6f);
	lef->setPressIcon("jiesuan-btn-3.png", false);
	lef->setOnClickCallback(callfuncO_selector(ZhanDouEnd::clickLeft), this);
	addChild(lef, 0, TAG_LEFT_BTN);
	lef->setPressIconShow(true);

	lef = Button::createBtnWithSpriteFrameName("jiesuan-btn-4.png", false);
	lef->setPosition(Vec2(winSize.width*0.5f + 270, winSize.height * 0.5f + 210));
	lef->setScale(0.6f);
	lef->setPressIcon("jiesuan-btn-1.png", false);
	lef->setOnClickCallback(callfuncO_selector(ZhanDouEnd::clickRight), this);
	addChild(lef, 0, TAG_RIGHT_BTN);


	lef = Button::createBtnWithSpriteFrameName("fanhuidating-02.png", false);
	lef->setPosition(Vec2(winSize.width*0.5f, 60));
	lef->setPressIcon("fanhuidating-01.png", false);
	lef->setScale(0.6f);
	lef->setOnClickCallback(callfuncO_selector(ZhanDouEnd::ReturnBegan), this);
	addChild(lef);

	infoFlag = false;
	likeFlag = false;

	return true;
}

void ZhanDouEnd::setInfos(std::vector<EndGame1> infos, std::vector<Relation2Me1> relas)
{
	if (mRankVec.size() == 0 && likeFlag == false)
	{
		std::vector<EndGame1>::iterator it = infos.begin();
		for (; it != infos.end(); ++it)
		{
			EndGame info;
			EndGame1 info1 = *it;
			info.rank = info1.rank;
			info.roleid = info1.roleid;
			info.sex = info1.sex;
			info.province = info1.province;
			info.city = info1.city;
			info.mass = info1.mass;
			info.eat = info1.eat;
			info.copper = info1.copper;
			info.exp = info1.exp;
			info.icon = info1.icon;
			info.name = info1.name;
			info.roleName = info1.roleName;

			mRankVec.push_back(info);
		}

		std::vector<Relation2Me1>::iterator iter = relas.begin();
		for (; iter != relas.end(); ++iter)
		{
			Relation2Me rela;
			Relation2Me1 rela1 = *iter;
			rela.roleid = rela1.roleid;
			rela.sex = rela1.sex;
			rela.province = rela1.province;
			rela.city = rela1.city;
			rela.mass = rela1.mass;
			rela.eat = rela1.eat;
			rela.copper = rela1.copper;
			rela.exp = rela1.exp;
			rela.icon = rela1.icon;
			rela.recommend = rela1.recommend;
			rela.name = rela1.name;
			rela.roleName = rela1.roleName;

			mRelaVec.push_back(rela);
		}

		infoFlag = true;
	}
	else if (mRankVec.size() == 0 && likeFlag == true)
	{
		int vSize = infos.size();
		for (int i = 0; i < vSize; i++)
		{
			EndGame info;
			EndGame1 info1 = infos[i];
			info.rank = info1.rank;
			info.roleid = info1.roleid;
			info.sex = info1.sex;
			info.province = info1.province;
			info.city = info1.city;
			info.mass = info1.mass;
			info.eat = info1.eat;
			info.copper = info1.copper;
			info.exp = info1.exp;
			info.icon = info1.icon;
			info.name = info1.name;
			info.roleName = info1.roleName;
			EndGame2 end = getEndGame2ById(info.roleid, mEndVec);
			info.isAttention = end.isAttention;
			info.isLike = end.isLike;

			mRankVec.push_back(info);
		}

		int rSize = relas.size();
		for (int j = 0; j < rSize; j++)
		{
			Relation2Me rela;
			Relation2Me1 rela1 = relas[j];

			rela.roleid = rela1.roleid;
			rela.sex = rela1.sex;
			rela.province = rela1.province;
			rela.city = rela1.city;
			rela.mass = rela1.mass;
			rela.eat = rela1.eat;
			rela.copper = rela1.copper;
			rela.exp = rela1.exp;
			rela.icon = rela1.icon;
			rela.recommend = rela1.recommend;
			rela.name = rela1.name;
			rela.roleName = rela1.roleName;
			EndGame2 end = getEndGame2ById(rela.roleid, mEndVec);
			rela.isAttention = end.isAttention;
			rela.isLike = end.isLike;

			mRelaVec.push_back(rela);

		}

		infoFlag = true;
	}
	//    else if(mRankVec.size() > 0 && likeFlag == true)
	//    {
	//        int vSize = mRankVec.size();
	//        for(int i = 0; i < vSize; i++)
	//        {
	//            if(i < infos.size())
	//            {
	//                EndGame1 info = getEndGame1ById(mRankVec[i].roleid, infos);
	//                mRankVec[i].rank = info.rank;
	//                mRankVec[i].roleid = info.roleid;
	//                mRankVec[i].sex = info.sex;
	//                mRankVec[i].province = info.province;
	//                mRankVec[i].city = info.city;
	//                mRankVec[i].mass = info.mass;
	//                mRankVec[i].eat = info.eat;
	//                mRankVec[i].copper = info.copper;
	//                mRankVec[i].exp = info.exp;
	//                mRankVec[i].name = info.name;
	//            }
	//        }
	//        
	//        int rSize = mRelaVec.size();
	//        for(int j = 0; j < rSize; j++)
	//        {
	//            if( j < relas.size())
	//            {
	//                Relation2Me1 info = getRela1ById(mRelaVec[j].roleid, relas);
	//                mRelaVec[j].roleid = info.roleid;
	//                mRelaVec[j].sex = info.sex;
	//                mRelaVec[j].province = info.province;
	//                mRelaVec[j].city = info.city;
	//                mRelaVec[j].mass = info.mass;
	//                mRelaVec[j].eat = info.eat;
	//                mRelaVec[j].copper = info.copper;
	//                mRelaVec[j].exp = info.exp;
	//                mRelaVec[j].recommend = info.recommend;
	//                mRelaVec[j].name = info.name;
	//
	//            }
	//        }
	//        infoFlag = true;
	//    }

	if (likeFlag && infoFlag)
	{
		InitRank();
	}
}

EndGame1 ZhanDouEnd::getEndGame1ById(int roleID, std::vector<EndGame1> infos)
{
	EndGame1 temp;
	std::vector<EndGame1>::iterator it = infos.begin();
	for (; it != infos.end(); ++it)
	{
		EndGame1 info = *it;
		if (roleID == info.roleid)
		{
			temp = info;
			return info;
		}
	}
	return temp;
}

Relation2Me1 ZhanDouEnd::getRela1ById(int roleID, std::vector<Relation2Me1> infos)
{
	Relation2Me1 temp;
	std::vector<Relation2Me1>::iterator it = infos.begin();
	for (; it != infos.end(); ++it)
	{
		Relation2Me1 info = *it;
		if (roleID == info.roleid)
		{
			temp = info;
			return info;
		}
	}
	return temp;
}

void ZhanDouEnd::setLikes(std::vector<EndGame2> infos)
{
	if (mRankVec.size() == 0 && infoFlag == false)
	{
		// old
		//        std::vector<EndGame2>::iterator it = infos.begin();
		//        for(; it != infos.end(); ++it)
		//        {
		//            EndGame info;
		//            Relation2Me rela;
		//            
		//            EndGame2 info2 = *it;
		//            
		//            info.roleid = info2.roleID;
		//            info.isAttention = info2.isAttention;
		//            info.isLike = info2.isLike;
		//            
		//            rela.roleid = info2.roleID;
		//            rela.isAttention = info2.isAttention;
		//            rela.isLike = info2.isLike;
		//            
		//            mRankVec.push_back(info);
		//            mRelaVec.push_back(rela);
		//        }

		mEndVec.clear();
		mEndVec = infos;

		likeFlag = true;
	}
	else if (mRankVec.size() > 0 && infoFlag == true)
	{
		int vSize = mRankVec.size();
		for (int i = 0; i < vSize; ++i)
		{
			if (i < vSize)
			{
				EndGame2 info = getEndGame2ById(mRankVec[i].roleid, infos);
				mRankVec[i].isAttention = info.isAttention;
				mRankVec[i].isLike = info.isLike;
			}
		}

		int rSize = mRelaVec.size();
		for (int j = 0; j < rSize; ++j)
		{
			if (j < rSize)
			{
				EndGame2 info = getEndGame2ById(mRelaVec[j].roleid, infos);
				mRelaVec[j].isAttention = info.isAttention;
				mRelaVec[j].isLike = info.isLike;
			}
		}
		likeFlag = true;
	}

	if (likeFlag && infoFlag)
	{
		InitRank();
	}
}

EndGame2 ZhanDouEnd::getEndGame2ById(int roleID, std::vector<EndGame2> infos)
{
	EndGame2 temp;
	std::vector<EndGame2>::iterator it = infos.begin();
	for (; it != infos.end(); ++it)
	{
		EndGame2 info = *it;
		if (roleID == info.roleID)
		{
			temp = info;
			return info;
		}
	}
	return temp;
}

void ZhanDouEnd::resIcon(std::vector<icon_data> arr)
{
	std::vector<EndGame>::iterator it = mRankVec.begin();
	for (; it != mRankVec.end(); ++it)
	{
		if ((*it).icon < 101)
		{
			(*it).iconStr = getIconString((*it).roleid, arr);
		}
	}

	std::vector<Relation2Me>::iterator ier = mRelaVec.begin();
	for (; ier != mRelaVec.end(); ++ier)
	{
		if ((*ier).icon < 101)
		{
			(*ier).iconStr = getIconString((*it).roleid, arr);
		}
	}
}

std::string ZhanDouEnd::getIconString(int roleID, std::vector<icon_data>datas)
{
	std::vector<icon_data>::iterator it = datas.begin();
	for (; it != datas.end(); ++it)
	{
		icon_data data = *it;
		if (data.roleid() == roleID)
		{
			return data.data();
		}
	}

	return "";
}

void ZhanDouEnd::InitRank()
{
	removeChildByTag(TAG_LEFT_LAYER, true);

	Layer* layer = Layer::create();
	addChild(layer, 0, TAG_LEFT_LAYER);
	if (mCurTouch == 1) {

		CCLabelTTF* lab = CCLabelTTF::create(Global::getInstance()->getString("92"), "STXingkai.ttf", 25);
		lab->setPosition(Vec2(winSize.width*0.5f - 500, winSize.height * 0.5f + 150));
		lab->setColor(Color3B(0, 0, 0));
		layer->addChild(lab);
	}
	CCLabelTTF* lab = CCLabelTTF::create(Global::getInstance()->getString("93"), "STXingkai.ttf", 25);
	lab->setPosition(Vec2(winSize.width*0.5f - 320, winSize.height * 0.5f + 150));
	lab->setColor(Color3B(0, 0, 0));
	layer->addChild(lab);

	lab = CCLabelTTF::create(Global::getInstance()->getString("94"), "STXingkai.ttf", 25);
	lab->setPosition(Vec2(winSize.width*0.5f - 130, winSize.height * 0.5f + 150));
	lab->setColor(Color3B(0, 0, 0));
	layer->addChild(lab);
	if (mCurTouch == 1) {
		lab = CCLabelTTF::create(Global::getInstance()->getString("95"), "STXingkai.ttf", 25);
		lab->setPosition(Vec2(winSize.width*0.5f + 30, winSize.height * 0.5f + 150));
		lab->setColor(Color3B(0, 0, 0));
		layer->addChild(lab);

		lab = CCLabelTTF::create(Global::getInstance()->getString("96"), "STXingkai.ttf", 25);
		lab->setPosition(Vec2(winSize.width*0.5f + 140, winSize.height * 0.5f + 150));
		lab->setColor(Color3B(0, 0, 0));
		layer->addChild(lab);

		lab = CCLabelTTF::create(Global::getInstance()->getString("97"), "STXingkai.ttf", 25);
		lab->setPosition(Vec2(winSize.width*0.5f + 250, winSize.height * 0.5f + 150));
		lab->setColor(Color3B(0, 0, 0));
		layer->addChild(lab);
		//if (mCurTouch == 1) {
		Sprite* dikuang = Sprite::create("zhaopian-03.png");
		dikuang->setScale(0.77f);
		dikuang->setPosition(Vec2(winSize.width * 0.5f, 160));
		layer->addChild(dikuang);

		int idx = (int)mRankVec.size() - 1;
		EndGame info = mRankVec[idx];

		char labStr[64] = { 0 };
		sprintf(labStr, "%d", info.rank);

		lab = CCLabelTTF::create(labStr, "STXingkai.ttf", 30);
		lab->setPosition(Vec2(70, 160));
		lab->setColor(Color3B(0, 0, 0));
		layer->addChild(lab, 1);

		//table_bg = Sprite::create("touxiang002.png");
		//table_bg->setScale(0.2f);
		//table_bg->setPosition(Vec2(160,35));
		//cell->addChild(table_bg,1);

		char temp[64];
		sprintf(temp, "hero_101.png");

		Sprite* head = Sprite::create(temp);
		head->setScale(0.23f);
		head->setPosition(Vec2(160, 160));
		layer->addChild(head, 2);

		NameColor color = Global::getInstance()->GetNameColor(info.name);
		lab = CCLabelTTF::create(info.name.c_str(), "STXingkai.ttf", 25);
		lab->setPosition(Vec2(200, 160 + 16));
		lab->setAnchorPoint(Vec2(0.0f, 0.5f));
		lab->setColor(Color3B(color.colorR, color.colorG, color.colorB));
		layer->addChild(lab, 1);

		if (info.roleName == "") {
			sprintf(temp, "S%d", info.roleid);
			info.roleName = temp;
		}
		lab = CCLabelTTF::create(info.roleName.c_str(), "STXingkai.ttf", 25);
		lab->setPosition(Vec2(200, 160 - 15));
		lab->setAnchorPoint(Vec2(0.0f, 0.5f));
		lab->setColor(Color3B(0, 0, 0));
		layer->addChild(lab, 1);

		std::map<int, std::string> hInfo = ExchangeInfo::getProvinces();
		lab = CCLabelTTF::create(hInfo[info.province].c_str(), "STXingkai.ttf", 30);
		lab->setPosition(Vec2(450, 160));
		lab->setColor(Color3B(0, 0, 0));
		layer->addChild(lab, 1);

		unsigned long long eMass = 0.000173415299158326*(pow(info.mass, 5)) - 7.34152991583261;

		if (eMass < 10000) {
			sprintf(temp, Global::getInstance()->getString("10"), eMass);
		}
		else if (eMass < 1000000)
		{
			unsigned long long tMa = eMass / 100;
			sprintf(temp, Global::getInstance()->getString("11"), tMa);
		}
		else if (eMass < 1000000000)
		{
			unsigned long long tMa = eMass / 100000;
			sprintf(temp, Global::getInstance()->getString("12"), tMa);
		}
		else if (eMass < 1000000000000)
		{
			unsigned long long tMa = eMass / 100000000;
			sprintf(temp, Global::getInstance()->getString("13"), tMa);
		}
		else if (eMass < 1000000000000000)
		{
			unsigned long long tMa = eMass / 100000000000;
			sprintf(temp, Global::getInstance()->getString("14"), tMa);
		}
		else if (eMass < 1000000000000000000)
		{
			unsigned long long tMa = eMass / 100000000000000;
			sprintf(temp, Global::getInstance()->getString("15"), tMa);
		}
		else{
			unsigned long long tMa = eMass / 100000000000000000;
			sprintf(temp, Global::getInstance()->getString("16"), tMa);
		}

		lab = CCLabelTTF::create(temp, "STXingkai.ttf", 30);
		lab->setPosition(Vec2(600, 160));
		lab->setColor(Color3B(0, 0, 0));
		layer->addChild(lab, 1);

		sprintf(labStr, "%d", info.eat);
		lab = CCLabelTTF::create(labStr, "STXingkai.ttf", 30);
		lab->setPosition(Vec2(700, 160));
		lab->setColor(Color3B(0, 0, 0));
		layer->addChild(lab, 1);

		sprintf(labStr, "%d", info.copper);
		lab = CCLabelTTF::create(labStr, "STXingkai.ttf", 30);
		lab->setPosition(Vec2(800, 160));
		lab->setColor(Color3B(0, 0, 0));
		layer->addChild(lab, 1);
	}
	else if (mCurTouch == 2)
	{
		lab = CCLabelTTF::create(Global::getInstance()->getString("98"), "STXingkai.ttf", 25);
		lab->setPosition(Vec2(winSize.width*0.5f + 140, winSize.height * 0.5f + 150));
		lab->setColor(Color3B(0, 0, 0));
		layer->addChild(lab);
	}


	if (getChildByTag(101)) {
		((TableView*)getChildByTag(101))->reloadData();
	}
	else{
		TableView* tableView = TableView::create(this, getTableSize());
		//tableView->setTouchPriority(MAIN_TABLEVIEW_ACTIVE);
		tableView->setDirection(ScrollView::Direction::VERTICAL);
		//tableView->setPosition(Vec2(winSize.width * 0.5f - CHILD_OFFSET_X, winSize.height * 0.5f - CHILD_OFFSET_Y));
		tableView->setPosition(Vec2(0, 200));
		tableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
		tableView->setDelegate(this);
		addChild(tableView, 50, 101);
		tableView->reloadData();
	}
}
void ZhanDouEnd::ReturnBegan(Ref* pSender)
{
	((MainScene*)getParent())->BackToLoginLayer(MainScene::TAG_GAME_END);
}
void ZhanDouEnd::resetBtnState()
{
	((Button*)getChildByTag(TAG_LEFT_BTN))->setPressIconShow(false);
	((Button*)getChildByTag(TAG_RIGHT_BTN))->setPressIconShow(false);
}
void ZhanDouEnd::clickLeft(Ref* pSender)
{
	resetBtnState();
	Button* shouye = (Button*)pSender;
	shouye->setPressIconShow(true);
	mCurTouch = 1;
	InitRank();
}
void ZhanDouEnd::clickRight(Ref* pSender)
{
	resetBtnState();
	Button* shouye = (Button*)pSender;
	shouye->setPressIconShow(true);

	mCurTouch = 2;
	InitRank();
}
void ZhanDouEnd::tableCellTouched(TableView* table, TableViewCell* cell)
{
	mTouchDex = cell->getIdx();
}
TableViewCell* ZhanDouEnd::tableCellAtIndex(TableView* table, ssize_t idex)
{
	TableViewCell* cell = table->dequeueCell();
	if (!cell) {
		cell = new TableViewCell();
		cell->autorelease();
	}
	else{
		cell->removeAllChildrenWithCleanup(true);
	}
	createTableViewCell(cell, table, idex);
	return cell;
}
Size ZhanDouEnd::cellSizeForTable(TableView* table)
{
	return Size(winSize.width, 70);
}
ssize_t ZhanDouEnd::numberOfCellsInTableView(TableView* table)
{
	if (mCurTouch == 1) {
		return (int)mRankVec.size() - 1;
	}
	else if (mCurTouch == 2){
		return (int)mRelaVec.size();
		//return 0;
	}

	return 0;
}

Size ZhanDouEnd::getTableSize()
{
	return Size(winSize.width, 250);
}
void ZhanDouEnd::createTableViewCell(Node* cell, TableView* table, int idex)
{
	if (mCurTouch == 1) {
		EndGame info = mRankVec[idex];

		Sprite* table_bg = Sprite::create("xuanxiangkuang.png");
		table_bg->setScale(0.65f);
		table_bg->setPosition(Vec2(winSize.width / 2, 35));
		cell->addChild(table_bg, 1);

		char labStr[64] = { 0 };
		sprintf(labStr, "%d", info.rank);

		CCLabelTTF* lab = CCLabelTTF::create(labStr, "STXingkai.ttf", 30);
		lab->setPosition(Vec2(70, 35));
		lab->setColor(Color3B(0, 0, 0));
		cell->addChild(lab, 1);

		//table_bg = Sprite::create("touxiang002.png");
		//table_bg->setScale(0.2f);
		//table_bg->setPosition(Vec2(160,35));
		//cell->addChild(table_bg,1);

		char temp1[32];
		Sprite* icon;
		CirCularNode* iconCir;
		if (info.icon < 101)
		{
			Texture2D* tex = ExchangeInfo::GetTextureForData(info.iconStr.c_str());
			icon = Sprite::createWithTexture(tex);
			icon->setScale(0.75f);
			iconCir = CirCularNode::create(25, icon);
		}
		else
		{
			sprintf(temp1, "hero_%d.png", info.icon);
			icon = Sprite::create(temp1);
			icon->setScale(0.23f);
			iconCir = CirCularNode::create(25, icon);
		}

		iconCir->setPosition(Vec2(160, 35));
		cell->addChild(iconCir, 1);

		NameColor color = Global::getInstance()->GetNameColor(info.name);
		lab = CCLabelTTF::create(info.name.c_str(), "STXingkai.ttf", 25);
		lab->setPosition(Vec2(200, 51));
		lab->setAnchorPoint(Vec2(0.0f, 0.5f));
		lab->setColor(Color3B(color.colorR, color.colorG, color.colorB));
		cell->addChild(lab, 1);

		if (info.roleName == "")
		{
			sprintf(temp1, "S%d", info.roleid);
			info.roleName = temp1;
		}
		lab = CCLabelTTF::create(info.roleName.c_str(), "STXingkai.ttf", 25);
		lab->setPosition(Vec2(200, 20));
		lab->setAnchorPoint(Vec2(0.0f, 0.5f));
		lab->setColor(Color3B(0, 0, 0));
		cell->addChild(lab, 1);

		std::map<int, std::string> hInfo = ExchangeInfo::getProvinces();

		lab = CCLabelTTF::create(hInfo[info.province].c_str(), "STXingkai.ttf", 30);
		lab->setPosition(Vec2(450, 35));
		lab->setColor(Color3B(0, 0, 0));
		cell->addChild(lab, 1);

		char temp[64];

		unsigned long long eMass = 0.000173415299158326*(pow(info.mass, 5)) - 7.34152991583261;

		if (eMass < 10000) {
			sprintf(temp, Global::getInstance()->getString("10"), eMass);
		}
		else if (eMass < 1000000)
		{
			unsigned long long tMa = eMass / 100;
			sprintf(temp, Global::getInstance()->getString("11"), tMa);
		}
		else if (eMass < 1000000000)
		{
			unsigned long long tMa = eMass / 100000;
			sprintf(temp, Global::getInstance()->getString("12"), tMa);
		}
		else if (eMass < 1000000000000)
		{
			unsigned long long tMa = eMass / 100000000;
			sprintf(temp, Global::getInstance()->getString("13"), tMa);
		}
		else if (eMass < 1000000000000000)
		{
			unsigned long long tMa = eMass / 100000000000;
			sprintf(temp, Global::getInstance()->getString("14"), tMa);
		}
		else if (eMass < 1000000000000000000)
		{
			unsigned long long tMa = eMass / 100000000000000;
			sprintf(temp, Global::getInstance()->getString("15"), tMa);
		}
		else{
			unsigned long long tMa = eMass / 100000000000000000;
			sprintf(temp, Global::getInstance()->getString("16"), tMa);
		}

		//sprintf(labStr, "%d克",info.mass);
		lab = CCLabelTTF::create(temp, "STXingkai.ttf", 30);
		lab->setPosition(Vec2(600, 35));
		lab->setColor(Color3B(0, 0, 0));
		cell->addChild(lab, 1);

		sprintf(labStr, "%d", info.eat);
		lab = CCLabelTTF::create(labStr, "STXingkai.ttf", 30);
		lab->setPosition(Vec2(700, 35));
		lab->setColor(Color3B(0, 0, 0));
		cell->addChild(lab, 1);

		sprintf(labStr, "%d", info.copper);
		lab = CCLabelTTF::create(labStr, "STXingkai.ttf", 30);
		lab->setPosition(Vec2(800, 35));
		lab->setColor(Color3B(0, 0, 0));
		cell->addChild(lab, 1);

		if (info.isLike)
		{

		}
		else{
			Button* lef = Button::createBtnWithSpriteFrameName("hongxin-01.png", false);
			lef->setPosition(Vec2(950, 35));
			//lef->setPressIcon("fanhuidating-01.png", false);
			lef->setScale(0.6f);
			lef->setOnClickCallback(callfuncO_selector(ZhanDouEnd::clickXihuan), this);
			cell->addChild(lef, 0, 1);
		}

		if (info.isAttention)
		{
			Button* lef = Button::createBtnWithSpriteFrameName("guanzhubtn.png", false);
			lef->setPosition(Vec2(1050, 35));
			//lef->setPressIcon("fanhuidating-01.png", false);
			lef->setScale(0.8f);
			lef->setOnClickCallback(callfuncO_selector(ZhanDouEnd::clickGuanzhu), this);
			cell->addChild(lef);

			lab = CCLabelTTF::create(Global::getInstance()->getString("99"), "STXingkai.ttf", 30);
			lab->setColor(Color3B(0, 0, 0));
			lef->addChild(lab, 1);
		}
		else{
			Button* lef = Button::createBtnWithSpriteFrameName("guanzhubtn.png", false);
			lef->setPosition(Vec2(1050, 35));
			//lef->setPressIcon("fanhuidating-01.png", false);
			lef->setScale(0.8f);
			lef->setOnClickCallback(callfuncO_selector(ZhanDouEnd::clickGuanzhu), this);
			cell->addChild(lef);

			lab = CCLabelTTF::create(Global::getInstance()->getString("100"), "STXingkai.ttf", 30);
			lab->setColor(Color3B(0, 0, 0));
			lef->addChild(lab, 1);
		}
	}
	else{
		Relation2Me info = mRelaVec[idex];

		Sprite* table_bg = Sprite::create("xuanxiangkuang.png");
		table_bg->setScale(0.65f);
		table_bg->setPosition(Vec2(winSize.width / 2, 35));
		cell->addChild(table_bg, 1);

		//table_bg = Sprite::create("touxiang002.png");
		//table_bg->setScale(0.2f);
		//table_bg->setPosition(Vec2(160,35));
		//cell->addChild(table_bg,1);

		char temp1[32];
		Sprite* icon;
		CirCularNode* iconCir;
		if (info.icon < 101)
		{
			Texture2D* tex = ExchangeInfo::GetTextureForData(info.iconStr.c_str());
			icon = Sprite::createWithTexture(tex);
			icon->setScale(0.75f);
			iconCir = CirCularNode::create(25, icon);
		}
		else
		{
			sprintf(temp1, "hero_%d.png", info.icon);
			icon = Sprite::create(temp1);
			icon->setScale(0.23f);
			iconCir = CirCularNode::create(25, icon);
		}

		iconCir->setPosition(Vec2(160, 35));
		cell->addChild(iconCir, 1);

		NameColor color = Global::getInstance()->GetNameColor(info.name);
		CCLabelTTF* lab = CCLabelTTF::create(info.name.c_str(), "STXingkai.ttf", 25);
		lab->setPosition(Vec2(200, 51));
		lab->setAnchorPoint(Vec2(0.0f, 0.5f));
		lab->setColor(Color3B(color.colorR, color.colorG, color.colorB));
		cell->addChild(lab, 1);

		if (info.roleName == "")
		{
			sprintf(temp1, "S%d", info.roleid);
			info.roleName = temp1;
		}
		lab = CCLabelTTF::create(info.roleName.c_str(), "STXingkai.ttf", 25);
		lab->setPosition(Vec2(200, 20));
		lab->setAnchorPoint(Vec2(0.0f, 0.5f));
		lab->setColor(Color3B(0, 0, 0));
		cell->addChild(lab, 1);

		std::map<int, std::string> hInfo = ExchangeInfo::getProvinces();
		lab = CCLabelTTF::create(hInfo[info.province].c_str(), "STXingkai.ttf", 30);
		lab->setPosition(Vec2(450, 35));
		lab->setColor(Color3B(0, 0, 0));
		cell->addChild(lab, 1);

		std::string strlb = "";
		///recommend  :1 = 果脯之恩  2 = 天赐良缘 3 ＝ 技艺切磋  4 ＝ 生死之敌
		if (info.recommend == 1) {
			strlb = Global::getInstance()->getString("101");
		}
		else if (info.recommend == 2)
		{
			strlb = Global::getInstance()->getString("102");
		}
		else if (info.recommend == 3)
		{
			strlb = Global::getInstance()->getString("103");
		}
		else if (info.recommend == 4)
		{
			strlb = Global::getInstance()->getString("104");
		}
		lab = CCLabelTTF::create(strlb.c_str(), "STXingkai.ttf", 30);
		lab->setPosition(Vec2(700, 35));
		lab->setColor(Color3B(0, 0, 0));
		cell->addChild(lab, 1);

		if (info.isLike)
		{

		}
		else{
			Button* lef = Button::createBtnWithSpriteFrameName("hongxin-01.png", false);
			lef->setPosition(Vec2(950, 35));
			//lef->setPressIcon("fanhuidating-01.png", false);
			lef->setScale(0.6f);
			lef->setOnClickCallback(callfuncO_selector(ZhanDouEnd::clickXihuan), this);
			cell->addChild(lef, 0, 1);
		}

		if (info.isAttention)
		{
			Button* lef = Button::createBtnWithSpriteFrameName("guanzhubtn.png", false);
			lef->setPosition(Vec2(1050, 35));
			//lef->setPressIcon("fanhuidating-01.png", false);
			lef->setScale(0.8f);
			lef->setOnClickCallback(callfuncO_selector(ZhanDouEnd::clickGuanzhu), this);
			cell->addChild(lef);

			lab = CCLabelTTF::create(Global::getInstance()->getString("99"), "STXingkai.ttf", 30);
			lab->setColor(Color3B(0, 0, 0));
			lef->addChild(lab, 1);
		}
		else{
			Button* lef = Button::createBtnWithSpriteFrameName("guanzhubtn.png", false);
			lef->setPosition(Vec2(1050, 35));
			//lef->setPressIcon("fanhuidating-01.png", false);
			lef->setScale(0.8f);
			lef->setOnClickCallback(callfuncO_selector(ZhanDouEnd::clickGuanzhu), this);
			cell->addChild(lef);

			lab = CCLabelTTF::create(Global::getInstance()->getString("100"), "STXingkai.ttf", 30);
			lab->setColor(Color3B(0, 0, 0));
			lef->addChild(lab, 1);
		}
	}
}
void ZhanDouEnd::clickGuanzhu(Ref* pSender)
{
	Button* btn = (Button*)pSender;
	TableViewCell* cell = (TableViewCell*)btn->getParent();
	int idex = cell->getIdx();
	mTouchDex = idex;
	EndGame info = mRankVec[idex];
	MainScene* scene = (MainScene*)getParent();
	int attn = 1;
	if (info.isAttention) {
		attn = 0;
	}
	scene->reqAddFriend(info.roleid, "");
}
void ZhanDouEnd::clickXihuan(Ref* pSender)
{
	Button* btn = (Button*)pSender;
	TableViewCell* cell = (TableViewCell*)btn->getParent();
	int idex = cell->getIdx();
	mTouchDex = idex;
	EndGame info = mRankVec[idex];
	MainScene* scene = (MainScene*)getParent();
	scene->reqSetFocus(2, 1, info.roleid);
}
void ZhanDouEnd::ShowUserLowInfo()
{
	UserLow* layer = UserLow::create();
	addChild(layer, 20, TAG_LOW_LAYER);

	layer->InitLike(mRankVec[mTouchDex]);
}
void ZhanDouEnd::ResSetFans()
{
	mRankVec[mTouchDex].isLike = true;
	((TableView*)getChildByTag(101))->reloadData();

	UserLow* layer = (UserLow*)getChildByTag(TAG_LOW_LAYER);
	if (layer)
	{
		layer->ResSetFans();
	}
}
void ZhanDouEnd::ResAddFriend()
{
	mRankVec[mTouchDex].isAttention = true;
	((TableView*)getChildByTag(101))->reloadData();

	UserLow* layer = (UserLow*)getChildByTag(TAG_LOW_LAYER);
	if (layer)
	{
		layer->ResAddFrieng();
	}
}
//////////////////////////////
AddFriend::AddFriend()
{

}
AddFriend::~AddFriend()
{

}

bool AddFriend::init()
{
	if (!Layer::init()) {
		return false;
	}

	Sprite* bg = Sprite::create("yaoqing_bg_2.png");
	bg->setPosition(Vec2(winSize.width - 202 * 0.6f + 10, 200));
	bg->setScale(0.6f);
	addChild(bg);

	CCLabelTTF* lab = CCLabelTTF::create(Global::getInstance()->getString("105"), "STXingkai.ttf", 25);
	lab->setPosition(Vec2(winSize.width - 202 * 0.6f + 10, 200));
	addChild(lab, 1);

	bg = Sprite::create("yaoqing_bg_1.png");
	bg->setPosition(Vec2(winSize.width - 202 * 0.6f, 150));
	bg->setScale(0.6f);
	addChild(bg);

	Button* lef = Button::createBtnWithSpriteFrameName("yaoqing_btn.png", false);
	lef->setPosition(Vec2(winSize.width - 202 * 0.6f - 92 * 0.6f + 10, 95));
	//lef->setPressIcon("fanhuidating-01.png", false);
	lef->setScale(0.6f);
	lef->setOnClickCallback(callfuncO_selector(AddFriend::clickOK), this);
	addChild(lef);

	bg = Sprite::create("xuanze-01.png");
	bg->setPosition(Vec2(winSize.width - 202 * 0.6f - 92 * 0.6f + 10, 95));
	bg->setScale(0.6f);
	addChild(bg);

	lef = Button::createBtnWithSpriteFrameName("yaoqing_btn.png", false);
	lef->setPosition(Vec2(winSize.width - 202 * 0.6f + 92 * 0.6f + 10, 95));
	//lef->setPressIcon("fanhuidating-01.png", false);
	lef->setScale(0.6f);
	lef->setOnClickCallback(callfuncO_selector(AddFriend::clickCancel), this);
	addChild(lef);

	bg = Sprite::create("xuanze-02.png");
	bg->setPosition(Vec2(winSize.width - 202 * 0.6f + 92 * 0.6f + 10, 95));
	bg->setScale(0.6f);
	addChild(bg);

	return true;
}

void AddFriend::clickOK(Ref* pSender)
{
	MainScene* scene = (MainScene*)getParent();
	scene->reqResponseAdd(1, m_friend.roleid());

	scene->removeChild(this, true);
}
void AddFriend::clickCancel(Ref* pSender)
{
	MainScene* scene = (MainScene*)getParent();
	scene->reqResponseAdd(0, m_friend.roleid());

	scene->removeChild(this, true);
}
void AddFriend::InitFriend(friend_info info)
{
	m_friend = info;
	char temp[32];
	sprintf(temp, "hero_%d.png", m_friend.icon());
	Sprite* head = Sprite::create(temp);
	head->setScale(0.2f);
	head->setPosition(Vec2(winSize.width - 202 * 0.6f - 80, 150));
	addChild(head, 2);

	CCLabelTTF* useName = CCLabelTTF::create(m_friend.name().c_str(), "STXingkai.ttf", 30);
	useName->setAnchorPoint(Vec2(0.0f, 0.5f));
	useName->setPosition(Vec2(winSize.width - 202 * 0.6f - 45, 150));
	addChild(useName, 2);

	/*
	Sprite* levBg = Sprite::create(duan.icon.c_str());
	levBg->setScale(0.25f);
	levBg->setPosition(Vec2(130, winSize.height - 80));
	addChild(levBg, 2);

	CCLabelTTF* levName = CCLabelTTF::create(duan.name.c_str(), "STXingkai.ttf", 30);
	levName->setColor(Color3B(0, 0, 0));
	levName->setAnchorPoint(Vec2(0.0f,0.5f));
	levName->setPosition(Vec2(145, winSize.height - 80));
	addChild(levName, 2);

	if (info.stars > 3) {
	char starLab[32] = {0};
	sprintf(starLab, "%d",info.stars);
	levName = CCLabelTTF::create(starLab, "STXingkai.ttf", 30);
	levName->setColor(Color3B(0, 0, 0));
	levName->setAnchorPoint(Vec2(0.0f,0.5f));
	levName->setPosition(Vec2(225, winSize.height - 80));
	addChild(levName, 2);

	Sprite* xing = Sprite::create("hecheng-xx-02.png");
	xing->setScale(0.6f);
	xing->setPosition(Vec2(265, winSize.height - 80));
	addChild(xing, 2);
	}else{
	for(int i = 0;i<3;i++)
	{
	if (info.stars > i) {
	Sprite* xing = Sprite::create("hecheng-xx-02.png");
	xing->setScale(0.6f);
	xing->setPosition(Vec2(225+i*25, winSize.height - 80));
	addChild(xing, 2);
	}else{
	Sprite* xing = Sprite::create("hecheng-xx-01.png");
	xing->setScale(0.6f);
	xing->setPosition(Vec2(225+i*25, winSize.height - 80));
	addChild(xing, 2);
	}
	}
	}
	*/
}


/////////
//用户简单信息
//////


UserLow::UserLow()
{
	isTouchIn = false;
}
UserLow::~UserLow()
{

}

bool UserLow::init()
{
	if (!CPZLayer::init()) {
		return false;
	}

	//user_info info = Global::getInstance()->GetPlayerInfo();
	user_info info = Global::getInstance()->GetUserInfo();
	duanweiInfo duan = Resource::sharedResource()->GetDuanweiInfo(info.duanwei);

	LayerColor* layer = LayerColor::create(Color4B(0, 0, 0, 80));
	addChild(layer);

	Sprite* spBg = Sprite::create("user_low_bg.png");
	spBg->setPosition(Vec2(winSize.width / 2, winSize.height / 2));
	spBg->setScale(0.6f);
	addChild(spBg, 0, 101);

	spBg = Sprite::create("low_line.png");
	spBg->setPosition(Vec2(winSize.width / 2, winSize.height / 2 + 200));
	spBg->setScale(0.6f);
	addChild(spBg);


	CCLabelTTF* lab = CCLabelTTF::create(Global::getInstance()->getString("31"), "STXingkai.ttf", 28);
	lab->setColor(Color3B(0, 0, 0));
	lab->setAnchorPoint(Vec2(0.0f, 0.5f));
	lab->setPosition(Vec2(winSize.width * 0.5f - 110, winSize.height * 0.5f + 230));
	addChild(lab, 2);


	Sprite* youxi = Sprite::create(duan.icon.c_str());
	youxi->setPosition(Vec2(winSize.width * 0.5f - 25, winSize.height * 0.5f + 230));
	youxi->setScale(0.25f);
	addChild(youxi);

	lab = CCLabelTTF::create(duan.name.c_str(), "STXingkai.ttf", 28);
	lab->setColor(Color3B(0, 0, 0));
	lab->setAnchorPoint(Vec2(0.0f, 0.5f));
	lab->setPosition(Vec2(winSize.width * 0.5f - 10, winSize.height * 0.5f + 230));
	addChild(lab, 2);

	if (info.stars > 3) {
		char starLab[32] = { 0 };
		sprintf(starLab, "%d", info.stars);
		lab = CCLabelTTF::create(starLab, "STXingkai.ttf", 30);
		lab->setColor(Color3B(0, 0, 0));
		lab->setAnchorPoint(Vec2(0.0f, 0.5f));
		lab->setPosition(Vec2(winSize.width * 0.5f + 60, winSize.height * 0.5f + 230));
		addChild(lab, 2);

		Sprite* xing = Sprite::create("hecheng-xx-02.png");
		xing->setScale(0.6f);
		xing->setPosition(Vec2(winSize.width * 0.5f + 100, winSize.height * 0.5f + 230));
		addChild(xing, 2);
	}
	else{
		for (int i = 0; i<3; i++)
		{
			if (info.stars > i) {
				Sprite* xing = Sprite::create("hecheng-xx-02.png");
				xing->setScale(0.6f);
				xing->setPosition(Vec2(winSize.width * 0.5f + 60 + i * 30, winSize.height * 0.5f + 230));
				addChild(xing, 2);
			}
			else{
				Sprite* xing = Sprite::create("hecheng-xx-01.png");
				xing->setScale(0.6f);
				xing->setPosition(Vec2(winSize.width * 0.5f + 60 + i * 30, winSize.height * 0.5f + 230));
				addChild(xing, 2);
			}
		}
	}


	Button* headbg = NULL;

	headbg = Button::createBtnWithSpriteFrameName("touxiang002.png", false);
	headbg->setPosition(Vec2(winSize.width * 0.5f, winSize.height * 0.5f + 90));
	headbg->setScale(0.55f);
	headbg->setOnClickCallback(callfuncO_selector(GameInfo::HeadClick), this);
	headbg->setPressIcon("touxiang002.png", false);
	addChild(headbg, 2);

	char temp[32];
	sprintf(temp, "hero_%d.png", info.icon);

	Sprite* head = Sprite::create(temp);
	head->setScale(0.5f);
	head->setPosition(Vec2(winSize.width * 0.5f, winSize.height * 0.5f + 90));
	addChild(head, 2);

	lab = CCLabelTTF::create(info.roleName.c_str(), "STXingkai.ttf", 35);
	lab->setColor(Color3B(0, 0, 0));
	lab->setPosition(Vec2(winSize.width * 0.5f, winSize.height * 0.5f - 20));
	addChild(lab, 2);

	std::map<int, std::string> hInfo = ExchangeInfo::getProvinces();
	lab = CCLabelTTF::create(hInfo[info.province].c_str(), "STXingkai.ttf", 35);
	lab->setPosition(Vec2(winSize.width * 0.5f, winSize.height*0.5f - 100));
	lab->setColor(Color3B(0, 0, 0));
	addChild(lab, 2);

	spBg = Sprite::create("low_line.png");
	spBg->setPosition(Vec2(winSize.width / 2, winSize.height / 2 - 150));
	spBg->setScale(0.6f);
	addChild(spBg);

	EndGame ninfo;
	ninfo.isLike = false;
	ninfo.isAttention = false;
	InitLike(ninfo);
	return true;
}
void UserLow::InitLike(EndGame info)
{
	mTouchInfo = info;

	Button* lef = Button::createBtnWithSpriteFrameName("low_zan.png", false);
	lef->setPosition(Vec2(winSize.width * 0.5f + 70, winSize.height*0.5f - 200));
	lef->setPressIcon("low_yizan.png", false);
	lef->setScale(0.6f);
	lef->setOnClickCallback(callfuncO_selector(UserLow::clickXihuan), this);
	addChild(lef, 0, TAG_RIGHT_BTN);

	if (info.isLike)
	{
		lef->setPressIconShow(true);
		lef->setIsCanTouch(false);
	}

	lef = Button::createBtnWithSpriteFrameName("low_guanzhu.png", false);
	lef->setPosition(Vec2(winSize.width * 0.5f - 70, winSize.height*0.5f - 200));
	lef->setPressIcon("low_yiguanzhu.png", false);
	lef->setScale(0.6f);
	lef->setOnClickCallback(callfuncO_selector(UserLow::clickGuanzhu), this);
	addChild(lef, 0, TAG_LEFT_BTN);

	if (info.isAttention)
	{
		lef->setPressIconShow(true);
		lef->setIsCanTouch(false);
	}
}

void UserLow::clickXihuan(Ref* pSender)
{
	MainScene* scene = (MainScene*)getParent()->getParent();
	scene->reqSetFocus(2, 1, mTouchInfo.roleid);
}
void UserLow::ResSetFans()
{
	Button* btn = (Button*)getChildByTag(TAG_RIGHT_BTN);
	btn->setPressIconShow(true);
	btn->setIsCanTouch(false);
}
void UserLow::clickGuanzhu(Ref* pSender)
{
	MainScene* scene = (MainScene*)getParent()->getParent();
	scene->reqAddFriend(mTouchInfo.roleid, "");
}
void UserLow::ResAddFrieng()
{
	Button* btn = (Button*)getChildByTag(TAG_LEFT_BTN);
	btn->setPressIconShow(true);
	btn->setIsCanTouch(false);
}
bool UserLow::onTouchBegan(Touch* pTouch, Event* pEvent)
{
	//Touch* pTouch = (Touch*)pTouches->anyObject();
	Node* node = getChildByTag(101);
	Point pt = node->convertToNodeSpace(Director::getInstance()->convertToGL(pTouch->getLocationInView()));
	Rect rt = Rect(0, 0, node->getContentSize().width*0.6f, node->getContentSize().height*0.6f);

	isTouchIn = rt.containsPoint(pt);
	if (isTouchIn)
		return false;
	else
		return true;
	//return true;
}
void UserLow::onTouchEnded(Touch* pTouch, Event* pEvent)
{
	if (isTouchIn)
		return;
	//Touch* pTouch = (Touch*)pTouches->anyObject();
	Node* node = getChildByTag(101);
	Point pt = node->convertToNodeSpace(Director::getInstance()->convertToGL(pTouch->getLocationInView()));
	Rect rt = Rect(0, 0, node->getContentSize().width*0.6f, node->getContentSize().height*0.6f);
	if (rt.containsPoint(pt) == false)
	{
		getParent()->removeChild(this);
	}
}



ReqOpenFight::ReqOpenFight()
{

}
ReqOpenFight::~ReqOpenFight()
{

}

bool ReqOpenFight::init()
{
	if (!CPZLayer::init())
		return false;

	LayerColor* layer = LayerColor::create(Color4B(0, 0, 0, 80));
	addChild(layer);

	Sprite* back = Sprite::create("bag-1.png");
	back->setPosition(Vec2(winSize.width * 0.5f, winSize.height * 0.5f));
	//back->setScaleX(0.3f);
	back->setScale(0.4f);
	addChild(back, 0, 101);

	CCLabelTTF* lab = CCLabelTTF::create(Global::getInstance()->getString("106"), "STXingkai.ttf", 35);
	lab->setColor(Color3B(0, 0, 0));
	lab->setPosition(Vec2(winSize.width * 0.5f, winSize.height * 0.5f + 100));
	addChild(lab, 2);


	lab = CCLabelTTF::create(Global::getInstance()->getString("107"), "STXingkai.ttf", 30);
	lab->setColor(Color3B(0, 0, 0));
	lab->setPosition(Vec2(winSize.width * 0.5f, winSize.height * 0.5f + 50));
	addChild(lab, 2);

	lab = CCLabelTTF::create(Global::getInstance()->getString("108"), "STXingkai.ttf", 30);
	lab->setColor(Color3B(0, 0, 0));
	lab->setPosition(Vec2(winSize.width * 0.5f, winSize.height * 0.5f + 10));
	addChild(lab, 2);

	Button* headbg = Button::createBtnWithSpriteFrameName("huifubisai-01.png", false);
	headbg->setPosition(Vec2(winSize.width * 0.5f, winSize.height * 0.5f - 70));
	headbg->setScale(0.5f);
	headbg->setOnClickCallback(callfuncO_selector(ReqOpenFight::clickOK), this);
	headbg->setPressIcon("huifubisai-02.png", false);
	addChild(headbg, 2);
	return true;
}

void ReqOpenFight::clickOK(Ref* pSender)
{
	MainScene* scene = (MainScene*)getParent();
	scene->confirmReConnectFighting();


	this->retain();
	this->autorelease();// 延迟到下一帧去释放
	scene->removeChild(this);
}

bool ReqOpenFight::onTouchBegan(Touch* pTouch, Event* pEvent)
{
	//Touch* pTouch = (Touch*)pTouches->anyObject();
	Node* node = getChildByTag(101);
	Point pt = node->convertToNodeSpace(Director::getInstance()->convertToGL(pTouch->getLocationInView()));
	Rect rt = Rect(0, 0, node->getContentSize().width*0.3f, node->getContentSize().height*0.4f);

	isTouchIn = rt.containsPoint(pt);

	return true;
}
void ReqOpenFight::onTouchEnded(Touch* pTouch, Event* pEvent)
{
	if (isTouchIn)
		return;
	//Touch* pTouch = (Touch*)pTouches->anyObject();
	Node* node = getChildByTag(101);
	Point pt = node->convertToNodeSpace(Director::getInstance()->convertToGL(pTouch->getLocationInView()));
	Rect rt = Rect(0, 0, node->getContentSize().width*0.3f, node->getContentSize().height*0.4f);
	if (rt.containsPoint(pt) == false)
	{
		MainScene* scene = dynamic_cast<MainScene*>(getParent());
		scene->cancelReConnectFighting();
		scene->CloseFight();
		scene->removeChild(this);

	}
}