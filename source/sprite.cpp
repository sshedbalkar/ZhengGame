#include "sprite.h"
#include "utility.h"
#include <fstream>
#include "graphics.h"


//=========================================
Sprite::Sprite( ) : Component( CT_Sprite )
{
}
//=========================================
Sprite::~Sprite()
{
}
//=========================================
void Sprite::Serialize( Json::Value& root )
{
	std::ifstream stream( root[1u].asString().c_str() );
	utility::ErrorIf( !stream, "failed loading sprite file.\n" );

	const std::string& name = root[0u].asString();
	Json::Reader reader;
	Json::Value sprite_root;
	utility::ErrorIf( !reader.parse( stream, sprite_root ), "failed parsing sprite file.\n" );

	loop = sprite_root["loop"].asUInt() == 0 ? false : true;
	time_per_frame = sprite_root["frametime"].asUInt();

	Json::Value& frames_root = sprite_root["frames"];
	for ( unsigned int i = 0; i < frames_root.size(); ++i )
	{
		Texture* alpha = GRAPHICS->GetAlphaTexture( frames_root[i]["alpha_texture"].asString() );
		Texture* tex = GRAPHICS->GetTexture( frames_root[i]["texture"].asString() );

		frameStruct frame = { alpha, tex };

		frames.push_back( frame );
	}

	stream.close();
	GRAPHICS->AddSprite( name, this );
}
//=========================================
bool Sprite::GetTextureByElapsedTime( unsigned int elapsed_time, Texture** alpha, Texture** tex )
{
	bool ret = true;
	unsigned int index = elapsed_time / time_per_frame;
	if ( loop ) index %= frames.size();
	else if ( index >= frames.size() ) 
	{
		index = frames.size() - 1; 
		ret = false; 
	}

	if ( alpha ) *alpha = frames[index].alpha;
	if ( tex ) *tex = frames[index].tex;
	return ret;
}
//=========================================
void Sprite::SetStaticSprite( const std::string& alpha_file, const std::string& texture_file )
{
	static int counter = 0;
	Texture* alpha = GRAPHICS->GetAlphaTexture( alpha_file );
	Texture* tex = GRAPHICS->GetTexture( texture_file );

	frameStruct frame = { alpha, tex };

	frames.push_back( frame );
	time_per_frame = 1000;
	loop = true;
	
	char name[15];
	sprintf_s( name, "nameless%i", counter );
	GRAPHICS->AddSprite( name, this );
	++counter;
}
//=========================================
void Sprite::Initialize()
{
}
//=========================================
Component* Sprite::Clone()
{
	return this; 
}
