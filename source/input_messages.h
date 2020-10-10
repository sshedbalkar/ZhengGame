#pragma once

#include "message.h"

//====================================
class MessageKeyTriggered : public Message
{
public:
	MessageKeyTriggered() : Message( MSG_KEY_TRIGGERED ) {};

	unsigned int key;
};
//====================================
class MessageControlEnable : public Message
{
public:
	MessageControlEnable( bool _enable ) : Message( MSG_CONTROL_ENABLE ),
		enable( _enable )
	{ };

	bool enable;
};
