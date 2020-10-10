#include "LogicComposition.h"
#include "utility.h"
#include "gameLogic.h"
#include "allLogics.h"
#include "logicSystem.h"
#include "composition.h"

std::map< std::string, LogicSerializer*> LogicComposition::serializer_map;
//==========================================
LogicComposition::LogicComposition() : Component( CT_LogicComposition )
{
}
//==========================================
LogicComposition::~LogicComposition()
{
	for ( unsigned int i = 0; i < logics.size(); ++i )
	{
		utility::Delete( logics[i]);
	}
	if ( owner ) owner->RemoveReference();
}
//==========================================
void LogicComposition::Serialize( Json::Value& root )
{
//	printf("%i\n", serializer_map.size() );
	for ( unsigned int i = 0; i < root.size(); ++i )
	{
	//serializer_map;
		GameLogic* logic = serializer_map[root[i].asString()]->Create();
		logics.push_back( logic );
	}
}
//==========================================
void LogicComposition::Initialize()
{
	for ( unsigned int i = 0; i < logics.size(); ++i )
	{
		logics[i]->Initialize( owner );
	}

	LOGICSYS->AddLogicComposition( this );
	owner->AddReference();
}
//==========================================
void LogicComposition::Execute( int dt )
{
	for ( unsigned int i = 0; i < logics.size(); ++i )
		logics[i]->Execute( dt );
}
//==========================================
Component* LogicComposition::Clone()
{	
	LogicComposition* new_logic_composition = new LogicComposition;
	for ( unsigned int i = 0; i < logics.size(); ++i )
	{
		GameLogic* new_logic = logics[i]->Clone();
		new_logic_composition->logics.push_back( new_logic );
	}
	return new_logic_composition;
}
//==========================================
void LogicComposition::AddLogicSerializer( std::string name, LogicSerializer* serializer )
{
	serializer_map[name] = serializer;
}
//==========================================
void LogicComposition::DeleteSerializers()
{
	std::map<std::string, LogicSerializer*>::iterator it;
	for ( it = serializer_map.begin(); it != serializer_map.end(); ++it )
		utility::Delete( it->second );
}
//==========================================
void LogicComposition::ProceedMessage( const Message* msg, LogicType type )
{
	for ( unsigned int i = 0; i < logics.size(); ++i )
	{
		if ( type == LT_All || logics[i]->logic_type == type ) logics[i]->ProceedMessage( msg );
	}
}
