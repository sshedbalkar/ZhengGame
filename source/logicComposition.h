#pragma once

#include "component.h"
#include "gameLogic.h"

class LogicComposition : public Component
{
public:
	LogicComposition();
	virtual ~LogicComposition();

	virtual void Serialize( Json::Value& root );
	virtual void Initialize();
	virtual Component* Clone();
	void ProceedMessage( const Message* msg, LogicType type );

	void Execute( int dt );
	static void DeleteSerializers();
	static void AddLogicSerializer( std::string name, LogicSerializer* serializer );

private:
	std::vector< GameLogic* > logics;
	static std::map< std::string, LogicSerializer*> serializer_map;

	
};
