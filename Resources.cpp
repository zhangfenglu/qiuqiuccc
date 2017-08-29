#pragma once
#include <cassert>
#include <time.h>
#include <string>

#include "Resources.h"
#include "DBException.h"
//定义随机数 by atom
#include<stdlib.h>
#include <map>
#define Random(x) (rand() % x)

using namespace std;

// defines the supported db version
//static const char *SUPPORTED_DB_VERSION = "1";

/*
 * MySQL specificities:
 *     - TINYINT is an integer (1 byte) type defined as an extension to
 *       the SQL standard.
 *     - all integer types can have an optional (non-standard) attribute
 *       UNSIGNED (http://dev.mysql.com/doc/mysql/en/numeric-types.html)
 *
 * SQLite3 specificities:
 *     - any column (but only one for each table) with the exact type of
 *       'INTEGER PRIMARY KEY' is taken as auto-increment.
 *     - the supported data types are: NULL, INTEGER, REAL, TEXT and BLOB
 *       (http://www.sqlite.org/datatype3.html)
 *     - the size of TEXT cannot be set, it is just ignored by the engine.
 *     - IMPORTANT: foreign key constraints are not yet supported
 *       (http://www.sqlite.org/omitted.html). Included in case of future
 *       support.
 *
 * Notes:
 *     - the SQL queries will take advantage of the most appropriate data
 *       types supported by a particular database engine in order to
 *       optimize the server database size.
 *
 * TODO: Fix problem with PostgreSQL null primary key's.
 */


static const char *ANTS_ITEMS_TBL_NAME =		"ants_item";
static const char *ANTS_HEAD =		"ants_headitem";
static const char *ANTS_SHOP = "ants_shop";
static const char *ANTS_COMPOSE = "ants_compose";
static const char *ANTS_DUANWEI = "ants_duanwei";
static const char *ANTS_COLOR = "ants_color";

static Resource * resource = NULL;

Resource * Resource::sharedResource()
{
	if (!resource)
		resource = new Resource();
	return resource;
}

/**
 * Constructor.
 */
Resource::Resource()
        : mDb(new SqLiteDataProvider())
{
}

/**
 * Destructor.
 */
Resource::~Resource()
{
    if (mDb->isConnected())
        close();

    delete mDb;
}

/**
 * Connect to the database and initialize it if necessary.
 */
void Resource::open()
{
    // Do nothing if already connected.
    if (mDb->isConnected())
        return;

    try {
        // open a connection to the database.
        mDb->connect();
#if 0
        // check database version here
		std::string dbversion = getDbVersion();
        if (dbversion.compare(SUPPORTED_DB_VERSION))
        {
            std::ostringstream errmsg;
            errmsg << "Database version is not supported. " <<
                "Needed version: '" << SUPPORTED_DB_VERSION <<
                "', current version: '" << dbversion << "'";
            throw errmsg.str(); 
        }
#endif
    }
    catch (const DbConnectionFailure& e) {
        std::ostringstream errmsg;
        errmsg << "(Resource::open #1) Unable to connect to the database: "
            << e.what();
        throw errmsg.str();
    }
}

/**
 * Disconnect from the database.
 */
void Resource::close()
{
    mDb->disconnect();
}


void Resource::writeDb()
{
    std::string path = FileUtils::getInstance()->getWritablePath();
    path.append("ants.db");
    ssize_t len = 0;
    unsigned char* buff = FileUtils::getInstance()->getFileData("ants.db", "rb", &len);
    
    FILE* write = fopen(path.c_str(),"wb");
    if(write)
    {
        fwrite(buff, 1, len, write);
        fclose(write);
    }
}

item Resource::getItemForID(int itemId)
{
    item  ite;

	try
	{
		std::ostringstream query;
		query << "SELECT *" << " FROM " << ANTS_ITEMS_TBL_NAME <<" WHERE itemID = "<< itemId <<";";

		const RecordSet &info = mDb->execSql(query.str());
		if (!info.isEmpty()) 
		{
            string_to<int> toInt;
			ite.itemID = toInt(info(0,"itemID"));
            ite.itemName = info(0,"itemName");
            ite.itemType = toInt(info(0,"itemType"));
            ite.maxCount = toInt(info(0,"maxCount"));
            ite.itemIcon = info(0,"itemIcon");
            ite.itemTips = info(0,"itemTips");
			
			return ite;
		}
	}
	catch (const DbSqlQueryExecFailure &e) 
	{
		std::ostringstream error;
		error << "(Resource::getItemForID) SQL query failure: " << e.what();
		CCLOGERROR(error.str().c_str());
	}

	return ite;
}
void Resource::GetComName(std::vector<nameMap> &vec)
{
    try
    {
        std::ostringstream query;
        query << "SELECT *" << " FROM " << ANTS_HEAD <<";";
        
        const RecordSet &info = mDb->execSql(query.str());
        if (!info.isEmpty())
        {
            string_to<int> toInt;
            
            unsigned int len = info.rows();
            for (int i = 0; i<len; i++) {
                nameMap vecInfo;
                vecInfo.mID = toInt(info(i,"id"));
                vecInfo.name = info(i,"name");
                vecInfo.icon = info(i,"icon");
                vec.push_back(vecInfo);
            }
        }
    }
    catch (const DbSqlQueryExecFailure &e)
    {
        std::ostringstream error;
        error << "(Resource::GetComName) SQL query failure: " << e.what();
        CCLOGERROR(error.str().c_str());
    }
}
void Resource::GetNameColorList(std::vector<NameColor>& arr)
{
    try
    {
        std::ostringstream query;
        query << "SELECT *" << " FROM " << ANTS_COLOR <<";";
        
        const RecordSet &info = mDb->execSql(query.str());
        if (!info.isEmpty())
        {
            string_to<int> toInt;
            
            unsigned int len = info.rows();
            for (int i = 0; i<len; i++) {
                NameColor vecInfo;
                vecInfo.mID = toInt(info(i,"id"));
                vecInfo.colorR = toInt(info(i,"colorR"));
                vecInfo.colorG = toInt(info(i,"colorG"));
                vecInfo.colorB = toInt(info(i,"colorB"));
                
                arr.push_back(vecInfo);
            }
        }
    }
    catch (const DbSqlQueryExecFailure &e)
    {
        std::ostringstream error;
        error << "(Resource::GetNameColorList) SQL query failure: " << e.what();
        CCLOGERROR(error.str().c_str());
    }
}

ChildItem Resource::GetShopItem(int itemID)
{
    ChildItem vecInfo;
    try
    {
        std::ostringstream query;
        query << "SELECT *" << " FROM " << ANTS_SHOP <<" JOIN "<< ANTS_ITEMS_TBL_NAME <<" WHERE "<< ANTS_SHOP<<".id = "<<ANTS_ITEMS_TBL_NAME<<".itemID"<<" AND "<<ANTS_ITEMS_TBL_NAME<<".itemID = "<<itemID<<";";
        
        const RecordSet &info = mDb->execSql(query.str());
        if (!info.isEmpty())
        {
            
            
            string_to<int> toInt;
            
            int id = toInt(info(0,"id"));
            
            int coper = toInt(info(0,"copper"));
            int gold = toInt(info(0,"gold"));
            vecInfo.m_id = id;
            if (coper) {
                vecInfo.m_money = info(0,"copper");
                vecInfo.m_costType = 1;
            }else if(gold)
            {
                vecInfo.m_money = info(0,"gold");
                vecInfo.m_costType = 2;
            }

            vecInfo.m_duration = Global::getInstance()->getString("1");
            vecInfo.m_icon = info(0,"itemIcon");
            char tem[64] = {0};
            sprintf(tem, "guanhuan_qiuiqu_%s",vecInfo.m_icon.c_str());
            vecInfo.m_iconBG = tem;
            vecInfo.m_name = info(0,"itemName");
            vecInfo.m_itemType = toInt(info(0,"itemType"));
            return vecInfo;
            
        }
    }
    catch (const DbSqlQueryExecFailure &e)
    {
        std::ostringstream error;
        error << "(Resource::GetShopItem) SQL query failure: " << e.what();
        CCLOGERROR(error.str().c_str());
    }
    return vecInfo;
}

void Resource::GetComposeItem(std::vector<itemInfo>& arr)
{
    user_info user = Global::getInstance()->GetUserInfo();
    try
    {
        std::ostringstream query;
        query << "SELECT *" << " FROM " << ANTS_COMPOSE <<" WHERE id = "<< user.heroid+1 <<" AND level = "<< user.herolevel<<";";
        
        const RecordSet &info = mDb->execSql(query.str());
        if (!info.isEmpty())
        {
            
            itemInfo vecInfo;
            string_to<int> toInt;
            
            for (int i = 1; i < 5; i++) {
                char labStr[64] = {0};
                sprintf(labStr, "matid%d",i);
                vecInfo.id = toInt(info(0,labStr));
                sprintf(labStr, "matn%d",i);
                vecInfo.mNum = toInt(info(0,labStr));
                
                if (vecInfo.id) {
                    arr.push_back(vecInfo);
                }
            }
        }
    }
    catch (const DbSqlQueryExecFailure &e)
    {
        std::ostringstream error;
        error << "(Resource::GetShopItem) SQL query failure: " << e.what();
        CCLOGERROR(error.str().c_str());
    }
}

duanweiInfo Resource::GetDuanweiInfo(int mID)
{
    duanweiInfo vecInfo;
    try
    {
        std::ostringstream query;
        query << "SELECT *" << " FROM " << ANTS_DUANWEI <<" WHERE id = "<<mID<<";";
        
        const RecordSet &info = mDb->execSql(query.str());
        if (!info.isEmpty())
        {
            
            
            string_to<int> toInt;
            
            int id = toInt(info(0,"id"));
            //log("shopidx:%d",id);
            
            vecInfo.mID = id;
            vecInfo.name = info(0,"name");
            vecInfo.icon = info(0,"icon");
            vecInfo.mStar = toInt(info(0,"star"));
            return vecInfo;
            
        }
    }
    catch (const DbSqlQueryExecFailure &e)
    {
        std::ostringstream error;
        error << "(Resource::GetDuanweiInfo) SQL query failure: " << e.what();
        CCLOGERROR(error.str().c_str());
    }
    return vecInfo;
}
