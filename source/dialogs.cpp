#include "dialogs.h"
#include "graphics.h"
#include "sprite.h"
#include <string>

//========================================
Dialogs::Dialogs() : Component( CT_Dialogs )
{
}
//========================================
Dialogs::~Dialogs()
{
}
//========================================
void Dialogs::Serialize( Json::Value& root )
{
	const std::string& str_popup = root["popup_sprite"].asString();
	popup = GRAPHICS->GetSprite( str_popup );
	const std::string& str_shrink = root["shrink_sprite"].asString();
	shrink = GRAPHICS->GetSprite( str_shrink );
	
	range_x = static_cast<float>(root["range_x"].asDouble());
	range_y = static_cast<float>(root["range_y"].asDouble());

	const std::string& alphafile = root["alpha"].asString();
	
	Json::Value& dialogs_root = root["dialogs"];

	for ( unsigned int i = 0; i < dialogs_root.size(); ++i )
	{
		DialogInfo info;
		Json::Value& node = dialogs_root[i];
		info.x = static_cast<float>(node["x"].asDouble());
		info.y = static_cast<float>(node["y"].asDouble());
		const std::string tex = node["texture"].asString();
		info.sprite = new Sprite;
		info.sprite->SetStaticSprite( alphafile, tex );

		dialogs.push_back(info);
	}
}
//========================================
void Dialogs::Initialize()
{
}
//========================================
Component* Dialogs::Clone()
{
	return this;
}