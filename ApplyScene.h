#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "network/HttpClient.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
USING_NS_CC;
using namespace cocos2d::ui;
using namespace cocostudio::timeline;

struct SunTime {
	int year;		// 年
	int month;		// 月
	int day;		// 日
	int week;		// 周数
	int hour;		// 小时
	int minute;		// 分
	int second;		// 秒
};

// 玩家数据
struct PlayerData
{
	std::string playerId;	// 玩家id
	std::string timeStr;	// 时间
	int monthcard;			// 月卡等级
	int yearcard;			// 年卡等级
	int diamonds;			// 钻石
	int goldcoins;			// 金币
	int likenumber;			// 喜欢值
	int week;				// 周数
	int grade;				// 等级
	SunTime time;			// 时间
};

class ApplyScene : public cocos2d::Layer
{
public:
    virtual bool init();

    // implement the "static create()" method manually
    CREATE_FUNC(ApplyScene);

	//************************************
	// Method:    applyReturn		处理报名返回
	// FullName:  ApplyScene::applyReturn
	// Access:    public 
	// Returns:   void
	// Qualifier:
	// Parameter: std::string data	网络数据
	//************************************
	void applyReturn(std::string data);
private:
	// msg
	//************************************
	// Method:    _initPlayerInfoMsg	玩家用户数据
	// FullName:  HelloWorld::_initPlayerInfoMsg
	// Access:    private 
	// Returns:   void
	// Qualifier:
	// Parameter: std::string data		网络数据
	//************************************
	void _initPlayerInfoMsg(std::string data);

	//************************************	
	// Method:    _initGroupMsg			获取对应的圣杯数据
	// FullName:  HelloWorld::_initGroupMsg	
	// Access:    private 
	// Returns:   void
	// Qualifier:
	// Parameter: std::string data		网络数据
	//************************************
	void _initGroupMsg(std::string data);

	//************************************
	// Method:    _checkLeftButton		点击圣杯按钮
	// FullName:  HelloWorld::_checkLeftButton
	// Access:    private 
	// Returns:   void
	// Qualifier:
	// Parameter: int tag
	//************************************
	void _checkLeftButton(int tag);
private:

	Node* _mainNode;					// 主节点
	ActionTimeline* _rightMoveAction;	// 动画

	Node* _rightNode;					// 右边节点
	Button* _leftCheckBox;				// 左边按钮
	Button* _rightCheckBox;				// 右边按钮
	ImageView* _leftImage;				// 左边图片
	ImageView* _RightImage;				// 右边图片
	Button* _smallGrail[5];				// 小圣杯数组
	Button* _bigGrail;					// 大圣杯

	Text* _textTime;					// 时间
	Text* _ruleText;					// 规则
	Text* _title;						// 标题

	ImageView* _prograssBg[3];			// 进度条背景
	LoadingBar* _bar[3];				// 进度条

	ImageView* _titleImage;				// 圣杯图片

	Text* _diamondText;					// 钻石数量
	Text* _numberText;					// 消耗数量
	ImageView* _icon;					// 消耗图片
	Button* _applyBtn;					// 开始按钮
	Text* _applyText;					// 开始提示
	bool _useType;						// 使用类型
	int _useConsumeType;				// 消耗类型

	PlayerData _playerData;				// 玩家数据
	ValueMap _stringData;				// 本地数据

	int _checkIndex;					// 圣杯编号
	int _week;							// 使用圣杯的周数
	int _useGold;						// 使用的金币数
	int _useDiamond;					// 使用的钻石数
	int _gouldId;						// 房间号

	Node* _nodeAction;					// 动作节点
private:

	//************************************
	// Method:    _initLeftUI			初始化左边ui
	// FullName:  HelloWorld::_initLeftUI
	// Access:    private 
	// Returns:   void
	// Qualifier:
	//************************************
	void _initLeftUI();				
	
	//************************************
	// Method:    _initRightUI			初始化右边ui
	// FullName:  HelloWorld::_initRightUI
	// Access:    private 
	// Returns:   void
	// Qualifier:
	//************************************
	void _initRightUI();

	//************************************
	// Method:    _initRightData		初始化右边数据
	// FullName:  HelloWorld::_initRightData
	// Access:    private 
	// Returns:   void
	// Qualifier:
	// Parameter: bool enroll			是否加入
	// Parameter: int playerNumber		玩家人数
	// Parameter: std::string openTime	开启时间
	// Parameter: int week				周数
	// Parameter:  SunTime time			系统时间
	//************************************
	void _initRightData(bool enroll, int playerNumber, std::string openTime, int week, SunTime time);

	//************************************
	// Method:    _openGrailByState		开启圣杯状态
	// FullName:  HelloWorld::_openGrailByState
	// Access:    private 
	// Returns:   void
	// Qualifier:
	// Parameter: bool state			true 为小圣杯，false 为大圣杯
	//************************************
	void _openGrailByState(bool state);

	//************************************
	// Method:    _openAllGrail			开启所有圣杯
	// FullName:  HelloWorld::_openAllGrail
	// Access:    private 
	// Returns:   void
	// Qualifier:
	//************************************
	void _openAllGrail();

	//************************************
	// Method:    _changeStrTimeToNumber转化字符时间为数字
	// FullName:  ApplyScene::changeStrTimeToNumber
	// Access:    private 
	// Returns:   SunTime
	// Qualifier:
	// Parameter: string timeStr		时间字符串
	//************************************
	SunTime _changeStrTimeToNumber(std::string timeStr);

	//************************************
	// Method:    _openBtnAction		开启按钮动画
	// FullName:  ApplyScene::_openBtnAction
	// Access:    private 
	// Returns:   Node*					动作节点
	// Qualifier:
	// Parameter: bool state true 为大按钮 false 为小按钮
	//************************************
	Node* _openBtnAction(bool state);

};



#endif // __HELLOWORLD_SCENE_H__
