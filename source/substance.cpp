#include "utility.h"
#include "substance.h"
#include "sprite.h"
#include "transform.h"
#include "graphics.h"
#include "composition.h"

#include "other_messages.h"
#include "core.h"

//=============================================
Substance::Substance( ) : Component( CT_Substance ) , color_overwrite(false)
{
}
//=============================================
Substance::~Substance()
{
	for ( unsigned int i = 0; i < sub_substances.size(); ++i )
		utility::Delete( sub_substances[i] );

	if ( owner ) owner->RemoveReference();
}
//=============================================
void Substance::Serialize( Json::Value& root )
{
	float x, y, z, width, height, orientation;
	id = root.get("id", "").asString();
	x = static_cast<float>(root.get("offset_x",0).asDouble());
	y = static_cast<float>(root.get("offset_y",0).asDouble());
	z = static_cast<float>(root.get("offset_z",0).asDouble());
	width = static_cast<float>(root.get("width",1).asDouble());
	height = static_cast<float>(root.get("height",1).asDouble());
	orientation = static_cast<float>(root["orientation"].asDouble());
	overwrite_color[0] = static_cast<float>(root.get("overwrite_r",0).asDouble());
	overwrite_color[1] = static_cast<float>(root.get("overwrite_g",0).asDouble());
	overwrite_color[2] = static_cast<float>(root.get("overwrite_b",0).asDouble());
	overwrite_color[3] = 1.0f;
	float f = overwrite_color[0] + overwrite_color[1] + overwrite_color[2];
	color_overwrite = f > 0.02f ? true : false;

	m_transform.position.x = x;
	m_transform.position.y = y;
	m_transform.position.z = z;
	m_transform.width = width;
	m_transform.height = height;
	m_transform.orientation = orientation;

	Json::Value& sp = root["sprite"];
	if ( !(!sp) )
	{
		const std::string& sprite_name = root["sprite"].asString();
		sprite = GRAPHICS->GetSprite( sprite_name );
		utility::ErrorIf( !sprite, "failed finding sprite.\n" );
	}
	else
	{
		Json::Value& tex = root["texture"];
		Json::Value& alpha = root["alpha"];
		utility::ErrorIf( (!tex)||(!alpha), "No texture/sprite assigned to the substance\n" );
		Sprite* _sp = new Sprite;
		_sp->SetStaticSprite( alpha.asString(), tex.asString() );
		sprite = _sp;
	}

	Json::Value& subs = root["sub_substances"];
	for ( unsigned int i = 0; i < subs.size(); ++i )
	{
		Substance* sub_substance = new Substance;
		sub_substance->Serialize( subs[i] );
		sub_substances.push_back( sub_substance );
	}
}
//=============================================
void Substance::Initialize()
{
	elapsed_time = 0;
	world_transform = static_cast<Transform*>(owner->GetComponent( CT_Transform ));
	GRAPHICS->AddSubstance( this );
	visible = true;

	owner->AddReference();
}
//=============================================
Component* Substance::Clone()
{
	Substance* new_substance = new Substance(*this);
	new_substance->sub_substances.clear();
	for ( unsigned int i = 0; i < sub_substances.size(); ++i )
	{
		Substance* sub = static_cast<Substance*>(sub_substances[i]->Clone());
		new_substance->sub_substances.push_back( sub );
	}
	return new_substance;
}
//=============================================
void Substance::AnimateAndDraw( unsigned int dt, Matrix4x4& mat_higher_level )
{
	elapsed_time += dt;
	Texture* texture;
	Texture* alpha;
	Vector4* color = NULL;

	if ( !sprite->GetTextureByElapsedTime( elapsed_time, &alpha, &texture ) )
	{
		MessageAnimationEnd msg;
		CORE->SendMessageToObj( &msg, owner, LT_StateMachine );
	};
	if ( color_overwrite ) color = &overwrite_color;
	Matrix4x4 mat_world;
	m_transform.BuildWorldMatrix( mat_world );
	MatrixMultiply( &mat_world, &mat_world, &mat_higher_level );

	GRAPHICS->DrawElement( mat_world, alpha, texture, color );

	for ( unsigned int i = 0; i < sub_substances.size(); ++i )
	{
		sub_substances[i]->AnimateAndDraw( dt, mat_world );
	}
}
//=============================================
void Substance::ChangeSpriteTo( const std::string& sprite_id )
{
	Sprite* changing_sprite = GRAPHICS->GetSprite( sprite_id );
	if ( changing_sprite ) 
	{
		if ( sprite != changing_sprite )
		{
			sprite = changing_sprite;
			elapsed_time = 0;
		}
	}
}
//=============================================
void Substance::ChangeSpriteTo( Sprite* _sprite )
{
	if ( sprite != _sprite )
	{
		sprite = _sprite;
		elapsed_time = 0;
	}
}
//=============================================
Substance* Substance::GetSubstanceByID( const std::string& _id )
{
	if ( id == _id ) return this;
	for ( unsigned int i = 0; i < sub_substances.size(); ++i )
	{
		Substance* t = sub_substances[i]->GetSubstanceByID(_id);
		if (  t != 0 )
			return t;
	}
	return NULL;
}
//=============================================
void Substance::GetWorldMatrix( Matrix4x4& mat_world )
{
	world_transform->BuildWorldMatrix( mat_world );
}
//=============================================
void Substance::SetParameters( float o_x, float o_y, float o_z, 
						float scale_x, float scale_y, float orientation,
						const std::string& sprite_name,
						float r, float g, float b)
{
	m_transform.position.x = o_x;
	m_transform.position.y = o_y;
	m_transform.position.z = o_z;
	m_transform.width = scale_x;
	m_transform.height = scale_y;
	m_transform.orientation = orientation;

	overwrite_color[0] = r;
	overwrite_color[1] = g;
	overwrite_color[2] = b;
	float f = r + g + b;
	color_overwrite = f > 0.02f ? true : false;

	sprite = GRAPHICS->GetSprite( sprite_name );
	utility::ErrorIf( !sprite, "failed finding sprite.\n" );

}
//=============================================
void Substance::SetParameters( float o_x, float o_y, float o_z, 
				float scale_x, float scale_y, float orientation,
				const std::string& alpha, const std::string& texture,
				float r, float g, float b )
{
	m_transform.position.x = o_x;
	m_transform.position.y = o_y;
	m_transform.position.z = o_z;
	m_transform.width = scale_x;
	m_transform.height = scale_y;
	m_transform.orientation = orientation;

	overwrite_color[0] = r;
	overwrite_color[1] = g;
	overwrite_color[2] = b;
	float f = r + g + b;
	color_overwrite = f > 0.02f ? true : false;

	sprite = new Sprite;
	sprite->SetStaticSprite( alpha, texture );
}
//=============================================
void Substance::SetParameters( float o_x, float o_y, float o_z, 
							float scale_x, float scale_y, float orientation,
							Sprite* _sprite,
							float r, float g, float b )
{
	m_transform.position.x = o_x;
	m_transform.position.y = o_y;
	m_transform.position.z = o_z;
	m_transform.width = scale_x;
	m_transform.height = scale_y;
	m_transform.orientation = orientation;

	overwrite_color[0] = r;
	overwrite_color[1] = g;
	overwrite_color[2] = b;
	float f = r + g + b;
	color_overwrite = f > 0.02f ? true : false;

	sprite = _sprite;
}

//=============================================
void Substance::AddSubSubstance( Substance* sub )
{
	sub_substances.push_back( sub );
}
//=============================================
bool Substance::Compare( Substance* a, Substance* b )
{
	if ( a->world_transform->position.z >=  b->world_transform->position.z  )
		return false;
	return true;
}