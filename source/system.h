#pragma once

enum SystemType
{
	ST_Factory,
	ST_Graphics,
	ST_Physics,
	ST_LogicSystem,
	ST_Input,

	ST_Num
};

class System
{
public:
	System( SystemType _type ) { type = _type; }
	virtual ~System() {};

	virtual void Initialize() = 0;
	virtual void Update( int dt ) = 0;
	virtual void Free() = 0;


	SystemType GetType() { return type; }
protected:
	SystemType type;
};