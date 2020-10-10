#include "WaterAutoGeneration.h"

#include "composition.h"
#include "substance.h"
#include "transform.h"

//==============================================
WaterAutoGeneration::WaterAutoGeneration()
{
	logic_type = LT_NotReactingToMessage;
}
//==============================================
WaterAutoGeneration::~WaterAutoGeneration()
{
}
//==============================================
void WaterAutoGeneration::Initialize( Composition* _owner )
{
	Transform* transform = static_cast<Transform*>(_owner->GetComponent(CT_Transform ));
	if ( !transform ) return;

	Substance* substance = new Substance;
	substance->SetParameters( 0.0f,0.0f,0.0f,1.0f,1.0f,0.0f, "blank" );

	int w = static_cast<int>(transform->width);
	int h = static_cast<int>(transform->height);

	float unit_x = 1.0f / (float) w;
	float unit_y = 1.0f / (float) h;

	
	Substance* water = new Substance;
	water->SetParameters( 0.0f, 0.5f, 0.0f,
						   1.0f, unit_y * 0.5f, 0.0f, "block",
						   1.0f, 1.0f, 1.0f );
	substance->AddSubSubstance( water );

	for ( int x = w-1; x >= 0; --x )
	{
		Substance* wave = new Substance;
		wave->SetParameters( unit_x*( (float)x-float(w-1)/2.0f ), 
							  0.5f + unit_y/2.0f, 
							  0.0f, unit_x * 1.0001f, unit_y, 0.0f, "wave" );
		substance->AddSubSubstance( wave );
	}

	water = new Substance;
	water->SetParameters( 0.0f, 0.0f, 0.0f,
						   1.0f, 1.0f, 0.0f, "block",
						   0.33f, 0.34f, 0.99f );
	substance->AddSubSubstance( water );


	_owner->AddComponent( substance );
//	substance->Initialize();
}
//==============================================
void WaterAutoGeneration::Execute( int dt )
{
}
//==============================================
void WaterAutoGeneration::ProceedMessage( const Message* )
{
}
