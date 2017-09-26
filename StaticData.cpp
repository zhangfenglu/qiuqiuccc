
#include "StaticData.h"

static StaticData *s_JsonUtils = nullptr;

StaticData::StaticData()
{
	_playerId = nullptr;
	_bXiHuan = false;
}

StaticData::~StaticData()
{

}

StaticData* StaticData::getInstance()
{
	if (!s_JsonUtils)
	{
		s_JsonUtils = new (std::nothrow) StaticData;
		CCASSERT(s_JsonUtils, "FATAL: Not enough memory");
		s_JsonUtils->init();
	}

	return s_JsonUtils;

}

void StaticData::init()
{
	
}

void StaticData::setPlayId(const char* id)
{
	_playerId = id;
}

const char* StaticData::getPlayerId()
{
	return _playerId;
}

void StaticData::setLove(bool b)
{
	_bXiHuan = b;
}

bool StaticData::getLove()
{
	return _bXiHuan;
}