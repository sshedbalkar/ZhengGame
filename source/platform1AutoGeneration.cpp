#include "platform1AutoGeneration.h"

#include "composition.h"
#include "substance.h"
#include "transform.h"

//==============================================
Platform1AutoGeneration::Platform1AutoGeneration()
{
	logic_type = LT_NotReactingToMessage;
}
//==============================================
Platform1AutoGeneration::~Platform1AutoGeneration()
{
}
//==============================================
void Platform1AutoGeneration::Initialize( Composition* _owner )
{
	Transform* transform = static_cast<Transform*>(_owner->GetComponent(CT_Transform ));
	if ( !transform ) return;

	Substance* substance = new Substance;
	substance->SetParameters( 0.0f,0.0f,0.0f,1.0f,1.0f,0.0f, "blank" );

	int w = static_cast<int>(transform->width);
	int h = static_cast<int>(transform->height);

	float unit_x = 1.0f / (float) w;
	float unit_y = 1.0f / (float) h;

	Substance* ground = new Substance;
	ground->SetParameters( 0.0f, 0.0f, 0.0f,
						   1.0f, 1.0f, 0.0f, "block",
						   0.73f, 0.33f, 0.83f );
	substance->AddSubSubstance( ground );

	for ( int x = w-1; x >= 0; --x )
	{
		Substance* grass = new Substance;
		grass->SetParameters( unit_x*( (float)x-float(w-1)/2.0f ), 
							  0.5f - unit_y/2.0f, 
							  0.0f, unit_x * 1.0001f, unit_y, 0.0f, "grass1" );
		substance->AddSubSubstance( grass );
	}

	_owner->AddComponent( substance );
//	substance->Initialize();
}
//==============================================
void Platform1AutoGeneration::Execute( int dt )
{
}
//==============================================
void Platform1AutoGeneration::ProceedMessage( const Message* )
{
}
