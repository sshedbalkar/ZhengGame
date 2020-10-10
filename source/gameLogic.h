#pragma once

#include "allComponents.h"

enum LogicType
{
	LT_NotReactingToMessage,
	LT_StateMachine,
	LT_Controller,
	LT_Animations,
	LT_CollisionHandling,
	
	LT_Num,
	LT_All
};


class GameLogic;
class Composition;
class Message;


class LogicSerializer
{
public:
	virtual GameLogic* Create() = 0;
};

template< class Type >
class LogicSerializerType : public LogicSerializer
{
public:
	virtual GameLogic* Create() { return new Type; }
};






class GameLogic
{
public:
	GameLogic( ) { }
	virtual ~GameLogic() { }

	virtual void Execute( int dt ) = 0;
	virtual void Initialize( Composition* owner ) = 0;
	
	virtual void ProceedMessage( const Message* msg ) = 0;

	virtual GameLogic* Clone() = 0;

	LogicType logic_type;
protected:
};
