/********************************************************************
	created:	2013/09/27
	filename: 	D:\evad11engine\DX11Tutorial\DX11Tutorial\UILib\FrontLable.h
	file ext:	h
	author:		wubaoqing
	
	purpose:	
*********************************************************************/


#ifndef FRONTLABLE_H_
#define FRONTLABLE_H_

#include <string>
#include "UiObject.h"
#include "Render/D3DIndexBuffer.h"
#include "Render/D3DVertexBuffer.h"

BEGINUINAMESPACE
class FrontLable : public EVAUI::UIObject
{

public:
	FrontLable(std::string& lable,const Vector2& postion = Vector2(0.0f,0.0), Vector4& color = Vector4(1.0,1.0,1.0,1.0));

	bool buildFront( std::string &lable, const Vector2 &postion );
	~FrontLable();
public:

	void	draw(Matrix4x4 world);

	void	update(float det);

	void	setString(std::string& lable);

private:

	D3DIndexBuffer*	m_pIndexBuffer;

	D3DVertexBuffer* m_pVertexBuffer;

	std::string		m_strMsg;

	Vector2			m_position;

};

ENDUINAMESPACE

#endif//FRONTLABLE_H_