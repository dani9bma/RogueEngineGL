Texture2D ObjTexture : register(t0);
SamplerState s_sampleParams
{
    Filter = MIN_MAG_MIP_LINEAR;
    AddressU = WRAP;
    AddressV = WRAP;
};

struct VS_OUTPUT
{
    float4 Pos : SV_POSITION;
    float2 TexCoord : TEXCOORD;
};

float4 main(VS_OUTPUT input) : SV_TARGET
{
    return ObjTexture.Sample(s_sampleParams, input.TexCoord);
}