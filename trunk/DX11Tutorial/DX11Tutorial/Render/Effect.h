
#pragma once
#include <string>
#include <vector>
#include <map>
#include <d3d11.h>
#include <d3dx10math.h>
#include <d3dx11async.h>
#include <fstream>
class Effect
{
public:
	struct INPUT_TYPE
	{
		std::string name;

		DXGI_FORMAT value;
	};

	typedef std::map<std::string, ID3D11ShaderResourceView*> TEXTURECONTAIN;
public:
	Effect(void);
	~Effect(void);

public:
	bool load(const char* filename);
	
	bool commit();

	bool setTexture(std::string key_, ID3D11ShaderResourceView* text_);

	static DXGI_FORMAT InputValue2DxValue(const char* value);

	std::vector<std::string>& CbuferMap();
private:

	void OutErrorMsg(ID3D10Blob*, WCHAR*);
private:
	std::vector<std::string> m_vsCbufferkey;
	std::vector<std::string> m_psCbufferkey;

	std::vector<INPUT_TYPE> m_input;

	ID3D11VertexShader* m_vertexShader;
	ID3D11PixelShader* m_pixelShader;
	ID3D11InputLayout* m_layout;
	std::vector<ID3D11Buffer*> m_vscbufer;
	std::vector<ID3D11Buffer*> m_pscbufer;

	std::map<std::string, ID3D11ShaderResourceView*> m_VTexture;
};
