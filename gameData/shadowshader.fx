float4x4 WorldViewProj : WorldViewProjection;
float alpha = 1.0;
texture texture0;

sampler Sampler0
{
	Texture = texture0;
//	MipFilter = Linear;
//	MinFilter = Linear;
//	MagFilter = Linear;
	AddressU = Clamp;
	AddressV = Clamp;
};


struct VS_INPUT
{
    float3 position	: POSITION;
	float2 tex0 : TEXCOORD0;
};

struct VS_OUTPUT
{
	float4 screenposition : POSITION;
	float2 tex0  : TEXCOORD0;
};

VS_OUTPUT VertexShader0( VS_INPUT IN )
{
	VS_OUTPUT OUT;
	OUT.screenposition = mul( float4(IN.position, 1) , WorldViewProj);
	OUT.tex0 = IN.tex0;
	return OUT;
}

float4 PixelShader0( VS_OUTPUT IN ) : COLOR
{	
	float4 ret = tex2D( Sampler0 , IN.tex0 );
	ret.a = 0.8 * ( 1.0 - ret.r );
	ret.r = 0.0;
	ret.g = 0.0;
	ret.b = 0.0;
	return ret;
}

technique Technique0
{
	pass Pass0
	{
		Lighting = FALSE;
		AlphaBlendEnable = TRUE;
		SrcBlend = SrcAlpha;
		DestBlend = InvSrcAlpha;
		VertexShader = compile vs_2_0 VertexShader0();
		PixelShader  = compile ps_2_0 PixelShader0();
	}
}
