#pragma once

#include "system.h"
#include "gameLogic.h"
#include <list>

class Composition;
class LogicComposition;

class LogicSystem : public System
{
public:
	LogicSystem();
	virtual ~LogicSystem();

	virtual void Initialize();
	virtual void Update( int dt );
	virtual void Free();

	void AddLogicComposition( LogicComposition* logic_obj );
	void ProcessMessage( const Message* msg, LogicType type, Composition* obj = NULL );

	typedef std::list<LogicComposition*> LogicList;
private:
	LogicList logic_compositions;
};

extern LogicSystem* LOGICSYS;