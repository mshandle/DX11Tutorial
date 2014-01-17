////////////////////////////////////////////////////////////////////////////////
// Filename: d3dclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _D3DCLASS_H_
#define _D3DCLASS_H_


/////////////
// LINKING //
/////////////
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dx11.lib")
#pragma comment(lib, "d3dx10.lib")


//////////////
// INCLUDES //
//////////////

#include <dxgi.h>
#include <d3dcommon.h>
#include <d3d11.h>
#include "../math/IMath.h"

////////////////////////////////////////////////////////////////////////////////
// Class name: D3DClass
////////////////////////////////////////////////////////////////////////////////
class D3DClass
{
public:
	D3DClass();
	D3DClass(const D3DClass&);
	~D3DClass();

	bool Initialize(int, int, bool, HWND, bool, float, float);
	void Shutdown();
	
	void BeginScene(float, float, float, float);
	void EndScene();

	ID3D11Device* GetDevice();
	ID3D11DeviceContext* GetDeviceContext();

	Matrix4x4 GetProjectionMatrix();
	Matrix4x4& GetWorldMatrix();
	Matrix4x4 GetOrthoMatrix();

	float ViewWidth();

	float ViewHeight();

	void GetVideoCardInfo(char*, int&);

	ID3D11SamplerState* GetDefaultSampleState();

	void TurnOnDepth();

	void TurnOffDepth();
	

	void TurnOnAlphaBlend();

	void TurnOffAlphaBlend();

	void TurnOnLineFrame();

	void TurnOffLineFrame();

	ID3D11DepthStencilView*	GetDepthStencilView();

	void					setRenderToBackBuffer();

private:

	HRESULT InitDefualtSampleState();

private:
	bool m_vsync_enabled;
	int m_videoCardMemory;
	char m_videoCardDescription[128];
	IDXGISwapChain* m_swapChain;
	ID3D11Device* m_device;
	ID3D11DeviceContext* m_deviceContext;
	ID3D11RenderTargetView*		m_renderTargetView;
	ID3D11Texture2D*			m_depthStencilBuffer;
	ID3D11DepthStencilState*	m_depthStencilState;
	ID3D11DepthStencilState*	m_disableDepthStencilState;
	ID3D11DepthStencilView*		m_depthStencilView;
	ID3D11RasterizerState*		m_rasterState;
	ID3D11RasterizerState*		m_rasterLineFrameState;

	ID3D11SamplerState*			m_sampleState;

	//alpha Blend state
	ID3D11BlendState* m_alphaEnableBlendingState;
	
	ID3D11BlendState* m_alphaDisableBlendingState;


	Matrix4x4 m_projectionMatrix;
	Matrix4x4 m_worldMatrix;
	Matrix4x4 m_orthoMatrix;

	float	  m_fViewWidth;

	float	  m_fViewHeight;
};

#endif