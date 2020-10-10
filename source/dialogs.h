#pragma once

#include "component.h"

#include <vector>

class Sprite;

class Dialogs : public Component
{
public:
	Dialogs();
	virtual ~Dialogs();

	virtual void Initialize();
	virtual void Serialize( Json::Value& root );

	virtual Component* Clone();
	
	struct DialogInfo
	{
		float x,y;
		Sprite* sprite;
	};

	typedef std::vector<DialogInfo> DialogList;
	DialogList dialogs;

	Sprite* popup;
	Sprite* shrink;

	float range_x;
	float range_y;

private:
};
