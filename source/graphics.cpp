
#include <iostream>
#include <d3d9.h>
#include <d3dx9.h>
#include "graphics.h"
#include "utility.h"
#include "sprite.h"////
#include "substance.h"
#include "camera.h"

#include "physics.h"
#include "body.h"
#include "transform.h"
#include "composition.h"

#define FVF		D3DFVF_XYZ|D3DFVF_TEX1


Graphics* GRAPHICS = NULL;
//===============================================
Graphics::Graphics() : System( ST_Graphics )
{
	pD3D = NULL;
	pDevice = NULL;
	shader = NULL;
	shader_shadow = NULL;
}
//===============================================
Graphics::~Graphics()
{
	
	utility::Release(shader);////
	utility::Release( shader_shadow );
	utility::Release( shader_debug );
	utility::Release(pVB);
	utility::Release(pD3D);
	utility::Release(pDevice);
	TextureMapType::iterator it;
	for ( it = texture_map.begin(); it != texture_map.end(); ++it )
		utility::Release( it->second );
	for ( it = alpha_texture_map.begin(); it != alpha_texture_map.end(); ++it )
		utility::Release( it->second );
	SpriteMapType::iterator it2;
	for ( it2 = sprite_map.begin(); it2 != sprite_map.end(); ++it2 )
		utility::Delete( it2->second );
}
//===============================================
void Graphics::Free()
{
	substances.clear();
}
//===============================================
void Graphics::Initialize()
{
	pD3D = Direct3DCreate9(D3D_SDK_VERSION);
		//return;////error handling here

	D3DPRESENT_PARAMETERS d3dpp; 
	ZeroMemory( &d3dpp, sizeof(d3dpp) );
	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;

	HRESULT hr = pD3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hwnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,&d3dpp, &pDevice );

	if ( FAILED(hr) ) 1;//printf("error\n"); ///error handling here

	pDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE );
	pDevice->SetRenderState( D3DRS_LIGHTING, FALSE );

	LoadGeometry();

	debug_drawing = false;

	LoadEffect( "gamedata\\debugshader.fx", &shader_debug );
	LoadEffect( "gamedata\\shader.fx", &shader );
	LoadEffect( "gamedata\\shadowshader.fx", &shader_shadow );

	GRAPHICS = this;
}
//===============================================
void Graphics::Update( int dt )
{
	SetupMatrices();

	pDevice->BeginScene();
	
	pDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE );
	pDevice->SetStreamSource( 0, pVB, 0, sizeof(VertexFormat) );
	pDevice->SetFVF( FVF );

	if( debug_drawing )
	{
		pDevice->Clear( 0, NULL, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(255,255,255), 1.0f, 0 );
		shader_debug->SetTechnique("Technique0");
		const Physics::BodyList& bodies = PHYSICS->GetBodyList();
		Physics::BodyList::const_iterator it;
		for ( it = bodies.begin(); it != bodies.end(); ++it )
		{
			shader_debug->Begin( 0, 0 );
			Texture* texture;
			shader_debug->BeginPass( 0 );

			Matrix4x4 mat;
			(*it)->transform->BuildWorldMatrix( mat );
			MatrixMultiply( &mat, &mat, &mat_viewproj );
			shader_debug->SetMatrix("WorldViewProj", &mat );
			switch( (*it)->shape )
			{
			case Body::Shape_Circle:
				texture = GetTexture("resources\\debug_circle.bmp");
				break;
			case Body::Shape_Rectangle:
				texture = GetTexture("resources\\debug_rectangle.bmp");
				break;
			}
			shader_debug->SetTexture( "texture0",  texture );
			pDevice->DrawPrimitive( D3DPT_TRIANGLESTRIP, 0, 2 );
			shader_debug->EndPass();
		
			pDevice->EndScene();
		}
	}
	else
	{
		pDevice->Clear( 0, NULL, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER, bg_color, 1.0f, 0 );
		shader->SetTechnique("Technique0");
		shader_shadow->SetTechnique( "Technique0" );
		shader_shadow->Begin( 0, 0 );
		shader->Begin( 0, 0 );
		std::list<Substance*>::iterator it = substances.begin();
		while ( it != substances.end() )
		{
			if ( !(*it)->GetOwner()->Exists() )
			{
//				utility::Delete( *it );
				it = substances.erase(it);
			}
			else
			{
				Matrix4x4 mat_world;
				(*it)->GetWorldMatrix( mat_world );
				
				float x,y;
				camera->GetViewingPosition( x, y );
				float w = abs(mat_world._11);
				float ox = mat_world._41;
//				if ( ox > 71.0f && ox < 73.0f )
//					printf( "%0.3f %0.3f %0.3f %0.3f \n",ox,w,x,abstract_width );
				if ( ox + w > x - abstract_width * 0.7f && ox - w < x + abstract_width * 0.7f )
				{
					(*it)->AnimateAndDraw( dt, mat_world );
				}
				++it;
			}
		
		}
	}
	
	//pDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE );
	//shader_debug->Begin( 0, 0 );
	//Texture* texture = GetTexture("resources\\debug_rectangle.bmp");
	//shader_debug->BeginPass( 0 );	
	//Matrix4x4 mat;
	//D3DXMatrixIdentity( &mat );
	//shader_debug->SetMatrix("WorldViewProj", &mat );
	//shader_debug->SetTexture( "texture0",  texture );
	//pDevice->DrawPrimitive( D3DPT_TRIANGLESTRIP, 0, 2 );
	//shader_debug->EndPass();

	pDevice->EndScene();
	pDevice->Present( 0,0,0,0);
}
//===============================================
void Graphics::DrawElement( Matrix4x4& mat_world, Texture* alpha, Texture* tex, Vector4* color )
{
		Matrix4x4 mat_offset, mat;
		MatrixMultiply( &mat, &mat_world, &mat_viewproj );


		shader_shadow->BeginPass( 0 );

		float ox, oy;
		ox = mat_world._43 * shadow_offset_x + shadow_offset_x;
		oy = mat_world._43 * shadow_offset_y + shadow_offset_y;

		MatrixTranslation( &mat_offset, ox, oy, 0.0f );
		mat_offset = mat_world* mat_offset;
		mat_offset *= mat_viewproj;
		shader_shadow->SetMatrix("WorldViewProj", &mat_offset );
		shader_shadow->SetTexture( "texture0",  alpha );
		pDevice->DrawPrimitive( D3DPT_TRIANGLESTRIP, 0, 2 );
		shader_shadow->EndPass();
		
		shader->BeginPass( 0 );
		
		shader->SetMatrix("WorldViewProj", &mat );
		shader->SetTexture( "alpha_texture",  alpha );
		shader->SetTexture( "texture0",  tex );
		if ( color ) shader->SetVector("color", color );
		else 
		{
			Vector4 white(1.0f,1.0f,1.0f,1.0f);
			shader->SetVector( "color", &white );
		}
		pDevice->DrawPrimitive( D3DPT_TRIANGLESTRIP, 0, 2 );
		shader->EndPass();
}
//===============================================
void Graphics::SetLevelGeometry( float _width, float _height, DWORD _color, float o_x, float o_y )
{
	abstract_width = _width;
	abstract_height = _height;

	shadow_offset_x = o_x;
	shadow_offset_y = o_y;

	bg_color = _color;

	D3DXMatrixPerspectiveLH( &mat_proj, abstract_width, abstract_height, 0.999f, 1000.0f );

}
//===============================================
void Graphics::SetupMatrices( )
{
	//////todo: get information from camera,etc. and set up mat_viewproj
	Matrix4x4 mat_view;
	float x = 0.0f, y = 0.0f;

	camera->GetViewingPosition( x, y );
	Vector3 eye( x, y, -1.0f );
	Vector3 target( x, y, 0.0f );
	Vector3 up( 0.0f, 1.0f, 0.0f );
	D3DXMatrixLookAtLH( &mat_view, &eye, &target, &up );

	//D3DXMatrixPerspectiveFovRH(&mat_viewproj, D3DXToRadian(90.0f), 4.0f/3.0f, 1.0f, 1000.0f);
	//D3DXMatrixOrthoLH( &mat_viewproj, abstract_width, abstract_height, 1.0f, 1000.0f );
	mat_viewproj = mat_view * mat_proj;
}
//===============================================
void Graphics::LoadEffect( const char* filename, ID3DXEffect** effect )
{
		HRESULT hr;
		LPD3DXBUFFER pBufferErrors = NULL;

		//Set up the shader flags
		#ifdef _DEBUG
			DWORD shaderFlags  = D3DXSHADER_DEBUG;
		#else
			DWORD shaderFlags  = D3DXSHADER_OPTIMIZATION_LEVEL3;//Max speed shaders
		#endif

		//Compile the shaders at load time. 
		hr = D3DXCreateEffectFromFile( pDevice, 
			filename,//The shader file to to load
			NULL, //Optional NULL-terminated array of preprocessor macro definitions
			NULL, //Not using include interface
			shaderFlags, //Shader Flags
			NULL, //No shader pool
			effect, 
			&pBufferErrors );

		if( FAILED(hr) )
		{
			printf("%s\n", pBufferErrors );
			exit(0);
		}
}
//===============================================
Texture* Graphics::GetTexture( const std::string& name )
{
	Texture* tex = texture_map[name];
	if ( tex ) return tex;
	else 
	{
		HRESULT hr = D3DXCreateTextureFromFile(pDevice, name.c_str(), &tex);
		utility::ErrorIf( FAILED(hr), "failed loading texture.\n" );
		texture_map[name] = tex;
		return tex;
	}
}//===============================================
Texture* Graphics::GetAlphaTexture( const std::string& name )
{
	Texture* tex = alpha_texture_map[name];
	if ( tex ) return tex;
	else 
	{
		HRESULT hr = D3DXCreateTextureFromFile(pDevice, name.c_str(), &tex);
		utility::ErrorIf( FAILED(hr), "failed loading texture.\n" );
		alpha_texture_map[name] = tex;
		return tex;
	}
}
//===============================================
Sprite* Graphics::GetSprite( const std::string& name )
{
	return sprite_map[name];
}
//===============================================
void Graphics::AddSprite( const std::string& name, Sprite* sprite )
{
	sprite_map[name] = sprite;
}
//===============================================
void Graphics::AddSubstance( Substance* substance )
{
	substances.push_back( substance );
	SortSprites();
}
//===============================================
void Graphics::LoadGeometry()
{
	//todo: load texture?
	//todo: create vertexbuffer, error handling

	if ( FAILED(pDevice->CreateVertexBuffer( sizeof( VertexFormat ) * 4, 0, FVF, 
								D3DPOOL_MANAGED, &pVB, NULL ) ) ) 1;

	VertexFormat* vertices;
	if ( FAILED(pVB->Lock( 0, 0, (void**)&vertices, 0 ) ) ) 1;	
	vertices[0].position = Vector3(-0.5f, -0.5f, 0.0f);
	vertices[0].u       = 0.0f;
	vertices[0].v       = 1.0f;
	vertices[1].position = Vector3(-0.5f, 0.5f, 0.0f);
	vertices[1].u       = 0.0f;
	vertices[1].v       = 0.0f;
	vertices[2].position = Vector3( 0.5f, -0.5f, 0.0f);
	vertices[2].u       = 1.0f;
	vertices[2].v       = 1.0f;
	vertices[3].position = Vector3( 0.5f, 0.5f, 0.0f);
	vertices[3].u       = 1.0f;
	vertices[3].v       = 0.0f;

	pVB->Unlock();
}
//===============================================
void Graphics::SortSprites()
{
	std::list<Substance*>::iterator it0, it1;
	for ( it0 = substances.begin(); it0 != substances.end(); ++it0 )
	{
		for ( it1 = it0; it1 != substances.end(); ++it1 )
		{
			if ( Substance::Compare( *it0, *it1 ) )
			{
				Substance* t = *it0;
				*it0 = *it1;
				*it1 = t;
			}
		}
	}

}
//==============================================
void Graphics::ToggleDebugDrawing()
{
	debug_drawing = !debug_drawing;
}