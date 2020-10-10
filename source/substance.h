#pragma once

#include "component.h"
#include "transform.h"
#include "Utility3D.h"
#include "math.h"
#include <vector>

class Sprite;

class Substance : public Component
{
public:
	Substance( );
	virtual ~Substance();

	void SetParameters( float o_x, float o_y, float o_z, 
						float scale_x, float scale_y, float orientation,
						const std::string& sprite_name,
						float r = 0.0f, float g = 0.0f, float b = 0.0f );
	void SetParameters( float o_x, float o_y, float o_z, 
						float scale_x, float scale_y, float orientation,
						Sprite* sprite_name,
						float r = 0.0f, float g = 0.0f, float b = 0.0f );
	void SetParameters( float o_x, float o_y, float o_z, 
						float scale_x, float scale_y, float orientation,
						const std::string& alpha, const std::string& texture,
						float r = 0.0f, float g = 0.0f, float b = 0.0f );

	virtual void Serialize( Json::Value& root );
	virtual void Initialize();
	virtual Component* Clone();

	void ChangeSpriteTo( const std::string& sprite_id );
	void ChangeSpriteTo( Sprite* sprite );
	void IncreaseSize( float w, float h )
	{
		m_transform.width += w; m_transform.height += h;
	}

	void AnimateAndDraw( unsigned int dt, Matrix4x4& mat_higher_level );
	void GetWorldMatrix( Matrix4x4& mat_world );

	static bool Compare( Substance* a, Substance* b );

	Substance* GetSubstanceByID( const std::string& id );
	
	bool visible;

	void AddSubSubstance( Substance* sub );
	Transform* world_transform;
private:
	std::string id;
	std::vector<Substance*> sub_substances;
	Sprite* sprite;
	Transform m_transform;
	Vector4 overwrite_color;
	bool color_overwrite;
	unsigned int elapsed_time;

};
