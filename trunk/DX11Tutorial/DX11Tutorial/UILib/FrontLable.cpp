#include "Base/EngineBase.h"
#include "FrontLable.h"
#include "Base/VertexFormat.h"
#include "UISystem.h"
#include "../FrameWork/SystemClass.h"

EVAUI::FrontLable::FrontLable( std::string& lable,const Vector2& postion,Vector4& color /*= Vector4(1.0,1.0,1.0,1.0)*/ )
{
	bool bResult = true;
	unsigned int nLenght = lable.size();
	m_strMsg = lable;
	XYZUV* vertices = NULL;
	unsigned long* indices = NULL;

	m_pIndexBuffer =new D3DIndexBuffer();
	indices = new unsigned long[nLenght * 6];
	for(unsigned int index = 0; index < nLenght *6; index++)
	{
		indices[index] = index;
	}
	if(m_pIndexBuffer->init(sizeof(unsigned long) * nLenght * 6, (void*)indices))
	{
		bResult = true;
		SAFE_DELETE(indices);
	}

	vertices = new XYZUV[nLenght * 6];
	m_pVertexBuffer = new D3DVertexBuffer();
	UISystem::instance().FontEngine()->BuildVertexArray((void*)vertices, lable.c_str(), postion.x, postion.y);
	if(m_pVertexBuffer->init(sizeof(XYZUV) * nLenght * 6, (void*)vertices, sizeof(XYZUV),D3D11_USAGE_DYNAMIC))
	{
		SAFE_DELETE(vertices);
		bResult = true;
	}

}

EVAUI::FrontLable::~FrontLable()
{

}

void EVAUI::FrontLable::draw( Matrix4x4 world )
{
	//return true;
	unsigned int offset;
	// Set vertex buffer stride and offset.
	offset = 0;
	ID3D11DeviceContext*  deviceContext = SystemClass::Instance().renderModul()->GetDeviceContext();
	// Set the vertex buffer to active in the input assembler so it can be rendered.
	ID3D11Buffer* vertexbuffer = m_pVertexBuffer->buffer();
	unsigned int stride_ = m_pVertexBuffer->stride();
	deviceContext->IASetVertexBuffers(0, 1, &vertexbuffer, &stride_, &offset);

	// Set the index buffer to active in the input assembler so it can be rendered.
	deviceContext->IASetIndexBuffer(m_pIndexBuffer->buffer(), DXGI_FORMAT_R32_UINT, 0);

	// Set the type of primitive that should be rendered from this vertex buffer, in this case triangles.
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	Effect* pXYZUV = UISystem::instance().EffectType(UIET_XYZUV);

	pXYZUV->setTexture("diffuse", UISystem::instance().FontEngine()->GetTexture());

	bool  result = pXYZUV->commit();

	deviceContext->DrawIndexed(6* m_strMsg.size(), 0, 0);
}

void EVAUI::FrontLable::update( float det )
{

	UIObject::update(det);
}