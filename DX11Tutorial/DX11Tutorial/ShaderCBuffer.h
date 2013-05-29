
#pragma once
#include <d3d11.h>
#include <d3dx10math.h>
#include <d3dx11async.h>
#include <map>

class ShaderCBuffer
{

public:
	virtual int size() = 0;

	virtual bool InitBuffer(void** buffer)= 0;
};

class CBufferManager
{
	typedef std::map<std::string, ShaderCBuffer*> CBUFFERMAP;
private:
	CBufferManager();
	~CBufferManager();
public:

	static CBufferManager& Instance();

	ShaderCBuffer* get(const std::string key);

	void			insert(const std::string key, ShaderCBuffer* object);
private:

	void			InitConstanceMap();
private:
	CBUFFERMAP m_pBufferMap;
};

class WorldViewProject : public ShaderCBuffer
{
public:
	struct WorldViewProjectData
	{
		D3DXMATRIX world;
		D3DXMATRIX view;
		D3DXMATRIX project;
	};
public:
		WorldViewProject();
		~WorldViewProject();

public:
	virtual int size();

	virtual bool InitBuffer(void** buffer);
};