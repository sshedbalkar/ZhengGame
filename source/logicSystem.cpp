#include "logicSystem.h"
#include "utility.h"
#include "logicComposition.h"
#include "gameLogic.h"
#include "allLogics.h"

#include "composition.h"

#define REGISTER_LOGIC(type)	LogicComposition::AddLogicSerializer(#type,new LogicSerializerType<type>());

LogicSystem* LOGICSYS = NULL;

//=======================================
LogicSystem::LogicSystem() : System( ST_LogicSystem )
{
}
//=======================================
LogicSystem::~LogicSystem()
{
	LogicComposition::DeleteSerializers();
}
//=======================================
void LogicSystem::Free()
{
	logic_compositions.clear();
}
//=======================================
void LogicSystem::Initialize()
{
	REGISTER_LOGIC( HeroInputHandling );
	REGISTER_LOGIC( HeroAnimations );
	REGISTER_LOGIC( HeroStateMachine );
	
	REGISTER_LOGIC( WaterAutoGeneration );
	REGISTER_LOGIC( PlatformAutoGeneration );
	REGISTER_LOGIC( Platform1AutoGeneration );
	REGISTER_LOGIC( GlobalInputHandling );
	REGISTER_LOGIC( SwordAttackInputHandling );

	REGISTER_LOGIC( Level0StateMachine );

	REGISTER_LOGIC( SwordStateMachine );
	REGISTER_LOGIC( TrapFallingBouldersStateMachine );
	REGISTER_LOGIC( BoulderStateMachine );
	REGISTER_LOGIC( GhostStateMachine );
	REGISTER_LOGIC( BackgroundStateMachine );

	REGISTER_LOGIC( SnapFromTerrain );
	REGISTER_LOGIC( BounceTwiceAndSelfDestruct );
	REGISTER_LOGIC( BringDamage );

	REGISTER_LOGIC( ShowDialogs );
	REGISTER_LOGIC( TitleScreen );
	LOGICSYS = this;
}
//=======================================
void LogicSystem::Update( int dt )
{
	LogicList::iterator it = logic_compositions.begin();
	while( it != logic_compositions.end() )
	{
		if ( !(*it)->GetOwner()->Exists() )
		{
//			utility::Delete( *it );
			it = logic_compositions.erase(it);
		}
		else
		{
			(*it)->Execute( dt );
			++it;
		}
	}
}
//=======================================
void LogicSystem::AddLogicComposition( LogicComposition* logic_obj )
{
	logic_compositions.push_back( logic_obj );
}
//=======================================
void LogicSystem::ProcessMessage( const Message* msg, LogicType type, Composition* obj )
{
	if ( obj )
	{
		LogicComposition* logic = static_cast<LogicComposition*>(obj->GetComponent(CT_LogicComposition));
		if ( logic ) logic->ProceedMessage( msg, type );
	}
	else
	{
		LogicList::iterator it;
		for ( it = logic_compositions.begin(); it != logic_compositions.end(); ++it )
		{
			(*it)->ProceedMessage( msg, type );
		}
	}
}
