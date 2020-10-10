#include "factory.h"
#include "utility.h"
#include "composition.h"
#include <fstream>
#include "core.h"
#include "graphics.h"

#include "allComponents.h"
#include "LogicComposition.h"
#include "physicsComposition.h"
#include "archetype.h"

//Register component macro
#define RegisterComponent(type) AddComponentCreator( #type, new ComponentCreatorType<type>( CT_##type ) );
#define Type(type) CT_##type;

Factory* FACTORY = NULL;
//==============================================
Factory::Factory() : System( ST_Factory )
{
}
//==============================================
Factory::~Factory()
{
	ComponentCreatorMapType::iterator it;
	it = component_creator_map.begin();
	for ( ; it != component_creator_map.end(); ++it )
		utility::Delete( it->second );

	ArchetypeMapType::iterator ait = archetypes.begin();
	int i  = 1;
	while ( ait != archetypes.end() )
	{
//		printf("%i\n", i++);
		utility::Delete( ait->second );
		++ait;
	}
	Free();
}
//==============================================
void Factory::Free()
{
	std::list<Composition*>::iterator it = objects.begin();
	while ( it != objects.end() )
	{
		utility::Delete( *it );
		++it;
	}
	objects.clear();
}
//==============================================
void Factory::Initialize()
{
	RegisterComponent(Transform);
	RegisterComponent(Sprite);
	RegisterComponent(Substance);
	RegisterComponent(Body);
	RegisterComponent(Steering);
	RegisterComponent(Status);
	RegisterComponent(Camera);
	RegisterComponent(LogicComposition);
	RegisterComponent(PhysicsComposition);
	RegisterComponent(Dialogs);

	FACTORY = this;
}
//==============================================
void Factory::WindowSerialize( const std::string& filename, int& width, int& height, std::string& title )
{
	Json::Value root;
	Json::Reader reader;

	std::ifstream stream(filename.c_str() );
	utility::ErrorIf( !stream, "error loading file\n" );
	bool successful = reader.parse( stream, root );
	utility::ErrorIf( !successful, "error while parsing\n");
	
	width = root.get("width", 200 ).asInt();
	height = root.get("height", 200 ).asInt();
	title = root["title"].asString();

	stream.close();
}
//==============================================
void Factory::GameSerialize( const std::string& filename )
{
	Json::Value root;
	Json::Reader reader;

	std::ifstream stream(filename.c_str() );
	utility::ErrorIf( !stream, "error loading file\n" );
	bool successful = reader.parse( stream, root );
	utility::ErrorIf( !successful, "error while parsing\n");
	
	AssetsSerialize( root["assets"].asString() );

	Json::Value& levels = root["levels"];
	for ( unsigned i = 0; i < levels.size(); ++i )
	{
		Json::Value& level_info = levels[i];
		level_paths[level_info[0u].asString()] = level_info[1u].asString();
	}
	//start at the first level in the level map
	CORE->SetNextLevel( "title" );
	stream.close();
}
//==============================================
void Factory::AssetsSerialize( const std::string& filename )
{
	std::ifstream stream( filename.c_str() );
	utility::ErrorIf( !stream, "error loading assets file.\n" );
	Json::Value root;
	Json::Reader reader;
	reader.parse( stream, root );
	
	BuildSprites( root["sprites"] );
	BuildArchetypes( root["archetypes"] );
	stream.close();
}
//==============================================
void Factory::LevelSerializeAndInitialize( const std::string& level_name )
{
	std::string filename = level_paths[level_name];
	std::ifstream stream( filename.c_str() );
	utility::ErrorIf( !stream, "cannot open level file\n" );

	Json::Value root;
	Json::Reader reader;
	utility::ErrorIf( !reader.parse( stream, root ), "parsing level file error\n" );
	
	float abstract_width = static_cast<float>(root.get("abstract_width", 40 ).asDouble());
	float abstract_height = static_cast<float>(root.get("abstract_height", 24 ).asDouble());
	Json::Value& color_root = root["background_color"];
	DWORD color = D3DCOLOR_XRGB( color_root[0u].asInt(), color_root[1u].asInt(), color_root[2u].asInt() );
	float offset_x = static_cast<float>(root.get("fake_shadow_offset_x", 0.0 ).asDouble());
	float offset_y = static_cast<float>(root.get("fake_shadow_offset_y", 0.0 ).asDouble());

	Json::Value objects_root = root["objects"];
	for ( unsigned int i = 0; i < objects_root.size(); ++i )
	{
		Json::Value inst_root = objects_root[i];
		std::string str = inst_root[0u].asString();
		Composition* obj = archetypes[str]->Instantiate();
		if ( str == "hero" ) hero = obj;
		float x = static_cast<float>(inst_root[1u].asDouble());
		float y = static_cast<float>(inst_root[2u].asDouble());
		float z = static_cast<float>(inst_root[3u].asDouble());
		float w = static_cast<float>(inst_root[4u].asDouble());
		float h = static_cast<float>(inst_root[5u].asDouble());
		Transform* transform = static_cast<Transform*>(obj->GetComponent(CT_Transform));

		if ( transform )
		{
			transform->position.x = x;
			transform->position.y = y;
			transform->position.z = z;
			transform->width = w;
			transform->height = h;
		}
		obj->Initialize();

		objects.push_back( obj );
	}
	stream.close();

	GRAPHICS->SetLevelGeometry( abstract_width, abstract_height, color, offset_x, offset_y );

}
//==============================================
void Factory::BuildArchetypes( Json::Value& root )
{
	for ( unsigned int i = 0; i < root.size(); ++i )
	{
		const std::string& name = root[i][0u].asString();
		Archetype* archetype = ArchetypeFromFile( root[i][1u].asString() );
		archetypes[name] = archetype;
	}
}
//=======build a single archetype from file====
Archetype* Factory::ArchetypeFromFile( std::string& filename )
{
	std::ifstream stream(filename.c_str() );
	utility::ErrorIf( !stream, filename.c_str() );

	Archetype* archetype = new Archetype();
	Json::Value root;
	Json::Reader reader;
	reader.parse( stream, root );
	const Json::Value::Members& component_names = root.getMemberNames();
	for( unsigned int i = 0; i < root.size(); ++i )
	{
		const std::string& component_type = component_names[i];
		ComponentCreator* creator = component_creator_map[component_type];
		utility::ErrorIf( !creator, "No matching component creator.\n" );
		Component* component = creator->Create( );
		component->Serialize( root[component_type] );
		archetype->AddComponent( component );
	}
	stream.close();

	return archetype;
}
//==============================================
void Factory::BuildSprites( Json::Value& root )
{
	for ( unsigned int i = 0; i < root.size(); ++i )
	{
		ComponentCreator* creator = component_creator_map["Sprite"];
		Component* sprite = creator->Create();
		sprite->Serialize( root[i] );

	}
}
//==============================================
void Factory::Update( int dt )
{
	std::list<Composition*>::iterator it = objects.begin();
	while( it != objects.end() )
	{
		if ( !(*it)->Referenced() )
		{
			utility::Delete( *it );
			it = objects.erase(it);
		}
		else ++it;
	}
}
//==============================================
void Factory::AddComponentCreator( const std::string type, ComponentCreator* creator )
{
	component_creator_map[type] = creator;
}
//==============================================
Composition* Factory::NewObject( const std::string& name, 
							float x, float y, float z,
							float w, float h )
{
	Composition* obj = archetypes[name]->Instantiate();

	Transform* transform = static_cast<Transform*>(obj->GetComponent(CT_Transform));

	if ( transform )
	{
		transform->position.x = x;
		transform->position.y = y;
		transform->position.z = z;
		transform->width = w;
		transform->height = h;
	}
	obj->Initialize();

	objects.push_back( obj );

	return obj;
}