#pragma once

enum MessageID
{
	MSG_NONE,
	MSG_RESET,
	MSG_CONTROL_ENABLE,
	MSG_KEY_TRIGGERED,
	MSG_SWITCH_ANIMATION,
	MSG_ANIMATION_END,
	MSG_COLLISION,
	MSG_ACTIVATE,
	MSG_POST_ATTACKING,
	MSG_TAKE_HIT,
	MSG_DESTRUCT,
	MSG_NEXTLEVEL
	//MSG_
};

class Message
{
public:
	Message( MessageID _id ) : id( _id ) { }

	MessageID id;
};
//====================================
class MessageReset : public Message
{
public:
	MessageReset() : Message( MSG_RESET ) {}
};

