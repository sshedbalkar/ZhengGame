#pragma once

#include "message.h"


//====================================
class Body;

class MessageCollision : public Message
{
public:
	MessageCollision() : Message( MSG_COLLISION ) {}

	float colliding_x;
	float colliding_y;
	Body* colliding_body;
};
//====================================
class MessageSwitchAnimation : public Message
{
public:
	enum AnimationType
	{
		Stand,
		Run,

		AnimationNum
	};
	MessageSwitchAnimation() : Message(MSG_SWITCH_ANIMATION) { }

	AnimationType animation;
};
//====================================
class MessagePostAttacking : public Message
{
public:
	MessagePostAttacking() : Message( MSG_POST_ATTACKING ) {};
};
//====================================
class MessageTakeHit : public Message
{
public:
	MessageTakeHit() : Message( MSG_TAKE_HIT ) {};

	int damage;
};
//====================================
class MessageDestruct : public Message
{
public:
	MessageDestruct() : Message( MSG_DESTRUCT ) {};
};
//====================================
class MessageAnimationEnd : public Message
{
public:
	MessageAnimationEnd() : Message( MSG_ANIMATION_END ) {};
};
//====================================
class MessageActivate : public Message
{
public:
	MessageActivate() : Message( MSG_ACTIVATE ) {};
};
