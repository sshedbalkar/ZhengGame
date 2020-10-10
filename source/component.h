#pragma once

#include "../json/json.h"

class Composition;

enum ComponentType
{
	CT_Transform = 0,
	CT_Steering,
	CT_Sprite,
	CT_Substance,
	CT_Body,
	CT_Status,
	CT_Camera,
	CT_LogicComposition,
	CT_PhysicsComposition,
	CT_Dialogs,

	CT_Num
};

class Component
{
public:
	Component( ComponentType _type ) : type(_type), owner( NULL ),
									   reference_count(new int(0)) { };
	virtual ~Component() { delete reference_count; };

	virtual void Serialize( Json::Value& root ) = 0;
	virtual void Initialize() = 0;
	virtual Component* Clone() = 0;
	 
	void SetOwner( Composition* _owner ) { owner = _owner; }
	void Delete()
	{
		if ( reference_count > 0 ) --reference_count;
		if ( reference_count <= 0 ) delete this;
	}
	Composition* GetOwner() { return owner; }
	ComponentType GetType() { return type; }

protected:
	int* reference_count;
	Composition* owner;
	ComponentType type;
};
