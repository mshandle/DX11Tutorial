/*
* File color.vs for sample bufferandshader;
*/

cbuffer MatrixBuffer
{
	matrix worldMatrix;
	matrix viewMatrix;
	matrix projectionMatrix;
};

//Input Type and OutPutType

struct VertexInputType
{
	float4 position:POSITION;
	float4 color:COLOR;
};

struct PixelInputType
{
    float4 position : SV_POSITION;
    float4 color : COLOR;
};

PixelInputType ColorVertexShader(VertexInputType input)
{
	PixelInputType output;
	
	input.position.w = 1.0;//input position is float3
	
	output.position = mul(input.position, worldMatrix);//translate world
	
	output.position = mul(output.position, viewMatrix);//translate view
	
	output.position = mul(output.position, projectionMatrix);//translate projection
	
	output.color = input.color;

}