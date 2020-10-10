#pragma once

#include "component.h"
//#include "transform.h"

///Game Component Creator Interface.
///Used to create components in data driven method in the GameObjectFactory.
class ComponentCreator
{
public:
	ComponentCreator(ComponentType _type_id)
		:type_id(_type_id)
	{
	}

	ComponentType type_id;
	///Create the component
	virtual Component* Create( ) = 0;
};

///Templated helper class used to make concrete component creators.
template<typename type>
class ComponentCreatorType : public ComponentCreator
{
public:
	ComponentCreatorType(ComponentType _type_id)
		:ComponentCreator(_type_id)
	{
	}

	virtual Component* Create( )
	{
		return new type( );
	}
};
