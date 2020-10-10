#pragma once

#include <Windows.h>
#include "system.h"
#include "math.h"
#include <map>
#include <list>
#include <vector>
#include "../json/json.h"

#include "Utility3D.h"

struct IDirect3D9;
struct IDirect3DDevice9;

class Sprite;
class Substance;
class Camera;

class Graphics : public System
{
	Camera* camera;
	typedef std::map<std::string, Texture*> TextureMapType;
	typedef std::map<std::string, Sprite*> SpriteMapType;
	TextureMapType texture_map;
	TextureMapType alpha_texture_map;
	SpriteMapType sprite_map;
	std::list<Substance*> substances;

	IDirect3D9* pD3D;
	IDirect3DDevice9* pDevice;
	IDirect3DVertexBuffer9* pVB;

	Matrix4x4 mat_proj;
	Matrix4x4 mat_viewproj;

	HWND hwnd;
	int screen_width, screen_height;
	float abstract_width, abstract_height;
	DWORD bg_color;
	float shadow_offset_x, shadow_offset_y;
	
	ID3DXEffect* shader;
	ID3DXEffect* shader_shadow;
	ID3DXEffect* shader_debug;

	bool debug_drawing;

public:
	Graphics();
	virtual ~Graphics();

	virtual void Initialize();
	virtual void Update( int dt );
	virtual void Free();

	Texture* GetTexture( const std::string& name );
	Texture* GetAlphaTexture( const std::string& name );
	Sprite* GetSprite( const std::string& name );
	void AddSprite( const std::string& name, Sprite* sprite );
	void AddSubstance( Substance* substance );

	void SetWindowProperties(HWND _hwnd,int _width,int _height){hwnd=_hwnd;screen_width=_width;screen_height=_height;}

	void SetLevelGeometry( float _width, float _height, DWORD _color, float o_x, float o_y );
	void SetCamera( Camera* _camera ) { camera = _camera; }

	void DrawElement( Matrix4x4& mat_world, Texture* alpha, Texture* tex = 0, Vector4* color = 0 );
	void SortSprites();

	void ToggleDebugDrawing();

	struct VertexFormat
	{
		Vector3 position;
		float u, v;
	};

private:
	void SetupMatrices( );

	void LoadGeometry();
	void LoadEffect( const char* filename, ID3DXEffect** effect );

};

extern Graphics* GRAPHICS;
