#pragma once


#include "system.h"
#include "componentcreator.h"
#include <map>
#include <list>

class Composition;
class Archetype;

class Factory : public System
{
public:
	Factory();
	virtual ~Factory();
	
	virtual void Initialize();
	virtual void Update( int dt );
	virtual void Free();

	static void WindowSerialize( const std::string& filename, int& width, int& height, std::string& title );
	void GameSerialize( const std::string& filename );
	void LevelSerializeAndInitialize( const std::string& level_name );
	void BuildArchetypes( Json::Value& root );
	void BuildSprites( Json::Value& root );
	Composition* NewObject( const std::string& name, 
							float x = 0.0f, float y = 0.0f, float z = 0.0f,
							float w = 1.0f, float h = 1.0f );

	Composition* GetHeroHandle() { return hero; }

private:
	typedef std::map< std::string, Archetype*> ArchetypeMapType;
	typedef std::map< std::string, ComponentCreator*> ComponentCreatorMapType;

	Composition* hero;
	std::list<Composition*> objects;
	ArchetypeMapType archetypes;
	ComponentCreatorMapType component_creator_map;
	std::map<std::string, std::string> level_paths;

	void AssetsSerialize( const std::string& filename );
	void AddComponentCreator( const std::string type, ComponentCreator* creator );

	Archetype* ArchetypeFromFile( std::string& filename );
};

extern Factory* FACTORY;
