#pragma once

#include <iostream>

namespace utility
{
	static void ErrorIf( bool condition, const char* message = 0 )	
	{
		if ( condition )
		{
			if ( message ) printf("%s\n", message );
			exit(0);
		}
	}

	template < typename type >
	void Release( type& obj )
	{
		if ( obj ) (obj)->Release();
		obj = NULL;
	}

	template < typename type >
	void Delete( type& obj )
	{
		if ( obj ) delete obj;
		obj = NULL;
	}
}
