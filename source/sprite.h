#pragma once

#include "component.h"
#include "Utility3D.h"
#include "math.h"

class Sprite : public Component
{
public:
	Sprite( );
	virtual ~Sprite();

	virtual void Serialize( Json::Value& root );
	virtual void Initialize();

	void SetStaticSprite( const std::string& alpha_file, const std::string& texture_file );

	bool GetTextureByElapsedTime( unsigned int elapsed_time, Texture** alpha_texture, Texture** texture );
	virtual Component* Clone();
private:
	struct frameStruct
	{
		Texture* alpha;
		Texture* tex;
	};
	bool loop;
	unsigned int time_per_frame;
	std::vector<frameStruct> frames;
};
