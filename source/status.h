#pragma once

#include "component.h"

class Status : public Component
{
public:
	Status();
	~Status();

	virtual void Initialize();
	virtual void Serialize( Json::Value& root );

	virtual Component* Clone();
	
	int hp;
	int max_hp;
	int stamina;
	int max_stamina;
};
