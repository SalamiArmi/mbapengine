Texture2D g_Texture;

sampler DiffuseSampler = sampler_state
{ 
    AddressU  = Wrap;
    AddressV  = Wrap;
	Texture = (g_Texture);
};

struct VS_OUTPUT
{
    float4 Pos : POSITION;
    float4 Dif : COLOR;
    float2 Tex : TEXCOORD;
};

VS_OUTPUT VS( float3 vPos : POSITION, float4 Dif : COLOR, float2 vTexCoord0 : TEXCOORD )
{
    VS_OUTPUT Output;

    Output.Pos = float4( vPos, 1.0f );
    Output.Dif = Dif;
    Output.Tex = vTexCoord0;

    return Output;
}

float4 PS( VS_OUTPUT In ) : SV_Target
{
	return tex2D( DiffuseSampler, In.Tex ) * In.Dif;
    //return g_Texture.Sample( DiffuseSampler, In.Tex ) * In.Dif;
}

float4 PSUntex( VS_OUTPUT In ) : SV_Target
{
    return In.Dif;
}

technique RenderUI
{
    pass P0
    {
		VertexShader = compile vs_3_0 VS();
		PixelShader  = compile ps_3_0 PS();
    }
}
technique RenderUIUntex
{
    pass P0
    {
        VertexShader = compile vs_3_0 VS();
        PixelShader  = compile ps_3_0 PSUntex();
    }
}