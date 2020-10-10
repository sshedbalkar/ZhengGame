#include "platformAutoGeneration.h"

#include "composition.h"
#include "substance.h"
#include "transform.h"

//==============================================
PlatformAutoGeneration::PlatformAutoGeneration()
{
	logic_type = LT_NotReactingToMessage;
}
//==============================================
PlatformAutoGeneration::~PlatformAutoGeneration()
{
}
//==============================================
void PlatformAutoGeneration::Initialize( Composition* _owner )
{
	Transform* transform = static_cast<Transform*>(_owner->GetComponent(CT_Transform ));
	if ( !transform ) return;

	Substance* substance = new Substance;
	substance->SetParameters( 0.0f,0.0f,0.0f,1.0f,1.0f,0.0f, "grass" );

	int w = static_cast<int>(transform->width);
	int h = static_cast<int>(transform->height);

	float unit_x = 1.0f / (float) w;
	float unit_y = 1.0f / (float) h;

	Substance* ground = new Substance;
	ground->SetParameters( 0.0f, 0.0f, 0.0f,
						   1.0f, 1.0f, 0.0f, "block",
						   0.8f, 0.75f, 0.3f );
	substance->AddSubSubstance( ground );

	for ( int x = w-1; x >= 0; --x )
	{
		Substance* grass = new Substance;
		grass->SetParameters( unit_x*( (float)x-float(w-1)/2.0f ), 
							  0.5f - unit_y/2.0f, 
							  0.0f, unit_x * 1.0001f, unit_y, 0.0f, "grass" );
		substance->AddSubSubstance( grass );
	}

	_owner->AddComponent( substance );
//	substance->Initialize();
}
//==============================================
void PlatformAutoGeneration::Execute( int dt )
{
}
//==============================================
void PlatformAutoGeneration::ProceedMessage( const Message* )
{
}
