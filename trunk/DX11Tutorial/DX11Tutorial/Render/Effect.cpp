#include "Effect.h"
#include "tinyxml.h"
#include "FrameWork/SystemClass.h"
#include "ShaderCBuffer.h"
#include <iostream>
using namespace std;
Effect::Effect(void)
{
}

Effect::~Effect(void)
{
}

bool Effect::load( const char* filename )
{
	bool result = false;
	TiXmlDocument* pdoc = new TiXmlDocument();

	if(NULL != pdoc)
	{
		result = pdoc->LoadFile(filename);
	}

	if(!result)
	{
		SAFE_DELETE(pdoc);
		SystemClass::Instance().WarningDialog((WCHAR*)filename,L"open failed!");
		return false;
	}

	TiXmlElement* root = pdoc->RootElement();
	
	TiXmlNode* vsNode = root->IterateChildren("VSShader",NULL);
	TiXmlNode* psNode = root->IterateChildren("PSShader",NULL);

	//analyze Vshader
	const char* vscodestr = vsNode->Value();
	TiXmlNode* vscode = vsNode->IterateChildren("ShaderCode", NULL)->IterateChildren(NULL);
	if(NULL != vscode)
	{
		/*TiXmlElement* vsele = vsNode->ToElement();*/
		vscodestr = vscode->Value();
	}
	//cbuffer;
	TiXmlNode* vscbuffercode = vsNode->IterateChildren("CBuffer", NULL);
	do 
	{
		if(vscbuffercode)
		{
			std::string tmp = vscbuffercode->IterateChildren(NULL)->Value();
			if(!tmp.empty()) 
				m_vsCbufferkey.push_back(tmp);
			vscbuffercode = vsNode->IterateChildren("CBuffer", vscbuffercode);
		}
	
	} while (vscbuffercode);
	//vs input type

	TiXmlNode* vsinputnode = vsNode->IterateChildren("InputType", NULL);

	TiXmlNode* vsInputElementNode = vsinputnode->IterateChildren("Element", NULL);
	
	do 
	{
		if(vsInputElementNode)
		{
			TiXmlElement* vsinputElementEle = vsInputElementNode->ToElement();
			const char* namevalue = vsinputElementEle->Attribute("name");
			const char* typevalue = vsinputElementEle->Attribute("value");
			
			INPUT_TYPE tmp;
			tmp.name = namevalue;
			tmp.value = InputValue2DxValue(typevalue);
			m_input.push_back(tmp);
			vsInputElementNode = vsinputnode->IterateChildren("Element", vsInputElementNode);
		}
		
	} while (vsInputElementNode);


	const char* pscodestr = psNode->Value();
	TiXmlNode* pscode = psNode->IterateChildren("ShaderCode", NULL)->IterateChildren(NULL);
	if(NULL != pscode)
	{
		pscodestr = pscode->Value();
	}
	
	//cbuffer;
	TiXmlNode* pscbuffercode = psNode->IterateChildren("CBuffer", NULL);
	do 
	{
		if(pscbuffercode)
		{
			std::string tmp = pscbuffercode->IterateChildren(NULL)->Value();
			if(!tmp.empty()) 
				m_psCbufferkey.push_back(tmp);
			pscbuffercode = psNode->IterateChildren("CBuffer", pscbuffercode);
		}
		
	} while (pscbuffercode);
	//texture
	TiXmlNode* psTexturecode = psNode->IterateChildren("Texture", NULL);
	do 
	{
		if(psTexturecode)
		{
			std::string tmp = psTexturecode->IterateChildren(NULL)->Value();

			m_VTexture[tmp] = NULL;
			psTexturecode = psNode->IterateChildren("Texture", psTexturecode);
		}

	} while (psTexturecode);


	//complier shader

	HRESULT hresult;
	ID3D10Blob* errorMessage;
	ID3D10Blob* vertexShaderBuffer;
	ID3D10Blob* pixelShaderBuffer;
	

	// Initialize the pointers this function will use to null.
	errorMessage = 0;
	vertexShaderBuffer = 0;
	pixelShaderBuffer = 0;
	// Compile the vertex shader code.

	hresult = D3DX11CompileFromMemory(vscodestr, strlen(vscodestr),NULL,NULL,NULL,"main", "vs_5_0",D3D10_SHADER_ENABLE_STRICTNESS,0,NULL, &vertexShaderBuffer,&errorMessage, NULL);

	if(FAILED(hresult))
	{
		// If the shader failed to compile it should have writen something to the error message.
		if(errorMessage)
		{
			OutErrorMsg(errorMessage,(WCHAR*) filename);
		}
		// If there was nothing in the error message then it simply could not find the shader file itself.
		else
		{
			SystemClass::Instance().WarningDialog((WCHAR*)filename, L"Missing Shader File");
		}

		return false;
	}
	
	hresult = D3DX11CompileFromMemory(pscodestr, strlen(pscodestr),NULL,NULL,NULL,"main", "ps_5_0",D3D10_SHADER_ENABLE_STRICTNESS,0,NULL, &pixelShaderBuffer,&errorMessage, NULL);
	
	if(FAILED(hresult))
	{
		// If the shader failed to compile it should have writen something to the error message.
		if(errorMessage)
		{
			OutErrorMsg(errorMessage,(WCHAR*) filename);
		}
		// If there was nothing in the error message then it simply could not find the shader file itself.
		else
		{
			SystemClass::Instance().WarningDialog((WCHAR*)filename, L"Missing Shader File");
		}

		return false;
	}

	
	ID3D11Device* device = SystemClass::Instance().renderModul()->GetDevice();
	// Create the vertex shader from the buffer.
	hresult = device->CreateVertexShader(vertexShaderBuffer->GetBufferPointer(), vertexShaderBuffer->GetBufferSize(), NULL, &m_vertexShader);
	if(FAILED(result))
	{
		return false;
	}

	// Create the pixel shader from the buffer.
	hresult = device->CreatePixelShader(pixelShaderBuffer->GetBufferPointer(), pixelShaderBuffer->GetBufferSize(), NULL, &m_pixelShader);
	if(FAILED(hresult))
	{
		return false;
	}
	
	D3D11_INPUT_ELEMENT_DESC* inputdesc = new D3D11_INPUT_ELEMENT_DESC[m_input.size()];
	for(unsigned int index = 0; index < m_input.size(); index++)
	{
		inputdesc[index].SemanticName = m_input[index].name.c_str();
		inputdesc[index].SemanticIndex = 0;
		inputdesc[index].Format = m_input[index].value;
		inputdesc[index].InputSlot = 0;
		if(index == 0)
		{
			inputdesc[index].AlignedByteOffset = 0;
		}
		else
		{
			inputdesc[index].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
		}
		
		inputdesc[index].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		inputdesc[index].InstanceDataStepRate = 0;
	}

	hresult = device->CreateInputLayout(inputdesc, m_input.size(), vertexShaderBuffer->GetBufferPointer(), 
		vertexShaderBuffer->GetBufferSize(), &m_layout);

	SAFE_DELETE(inputdesc);
	D3D11_BUFFER_DESC BufferDesc;
	//cbuffer
	for(unsigned int index = 0; index < m_vsCbufferkey.size(); index++)
	{
		ShaderCBuffer* buffer = CBufferManager::Instance().get(m_vsCbufferkey[index]);
		

		BufferDesc.ByteWidth = buffer->size();
		BufferDesc.Usage = D3D11_USAGE_DYNAMIC;
		BufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		BufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		BufferDesc.MiscFlags = 0;
		BufferDesc.StructureByteStride = 0;
		ID3D11Buffer* tmp;
		hresult = device->CreateBuffer(&BufferDesc, NULL, &tmp);
		if(FAILED(hresult))
		{
			return false;
		}
		else
		{
			m_vscbufer.push_back(tmp);
		}
	}

	for(unsigned int index = 0; index < m_psCbufferkey.size(); index++)
	{
		ShaderCBuffer* buffer = CBufferManager::Instance().get(m_vsCbufferkey[index]);

		BufferDesc.Usage = D3D11_USAGE_DYNAMIC;
		BufferDesc.ByteWidth = buffer->size();
		BufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		BufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		BufferDesc.MiscFlags = 0;
		BufferDesc.StructureByteStride = 0;
		ID3D11Buffer* tmp;
		hresult = device->CreateBuffer(&BufferDesc, NULL, &tmp);
		if(FAILED(hresult))
		{
			return false;
		}
		else
		{
			m_pscbufer.push_back(tmp);
		}
	}

	//last release the doc
	SAFE_DELETE(pdoc);

	return true;
}

bool Effect::commit()
{
	if(m_vsCbufferkey.size() != m_vscbufer.size())
		return false;

	HRESULT result;
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	ID3D11DeviceContext* deviceContext = SystemClass::Instance().renderModul()->GetDeviceContext();
	for(unsigned int index = 0; index < m_vscbufer.size(); index++)
	{
		// Lock the constant buffer so it can be written to.
		result = deviceContext->Map(m_vscbufer[index], 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);

		void*	dataPtr = (void*)mappedResource.pData;

		ShaderCBuffer* cbuffer =  CBufferManager::Instance().get(m_vsCbufferkey[index]);

		cbuffer->InitBuffer(&dataPtr);
		// Unlock the constant buffer.
		deviceContext->Unmap(m_vscbufer[index], 0);
		// Finaly set the constant buffer in the vertex shader with the updated values.
		deviceContext->VSSetConstantBuffers(index, 1, &m_vscbufer[index]);

	}

	for(unsigned int index = 0; index < m_pscbufer.size(); index++)
	{
		// Lock the constant buffer so it can be written to.
		result = deviceContext->Map(m_pscbufer[index], 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);

		void*	dataPtr = (void*)mappedResource.pData;

		ShaderCBuffer* cbuffer =  CBufferManager::Instance().get(m_psCbufferkey[index]);

		cbuffer->InitBuffer(&dataPtr);
		// Unlock the constant buffer.
		deviceContext->Unmap(m_pscbufer[index], 0);
		// Finaly set the constant buffer in the vertex shader with the updated values.
		deviceContext->PSSetConstantBuffers(index, 1, &m_pscbufer[index]);

	}


	// Set the vertex input layout.
	deviceContext->IASetInputLayout(m_layout);

	// Set the vertex and pixel shaders that will be used to render this triangle.
	deviceContext->VSSetShader(m_vertexShader, NULL, 0);
	deviceContext->PSSetShader(m_pixelShader, NULL, 0);

	int nSlot = 0;
	for(TEXTURECONTAIN::iterator it = m_VTexture.begin(); it!= m_VTexture.end(); it++)
	{
		ID3D11ShaderResourceView* pResourceView = it->second;
		deviceContext->PSSetShaderResources(nSlot,1, &pResourceView);
		nSlot++;
	}
	if(m_VTexture.size() != 0)
	{
		ID3D11SamplerState* pSampleState = 	SystemClass::Instance().renderModul()->GetDefaultSampleState();
		if(pSampleState != NULL)
		{
			deviceContext->PSSetSamplers(0,1,&pSampleState);
		}
	}
	return !FAILED(result);
}

std::vector<std::string>& Effect::CbuferMap()
{
	return m_vsCbufferkey;
}

DXGI_FORMAT Effect::InputValue2DxValue( const char* value )
{
	std::string valuestr(value);
	if(valuestr=="FLOAT3")
	{
		return DXGI_FORMAT_R32G32B32_FLOAT;
	}
	else if(valuestr == "FLOAT4")
	{
		return DXGI_FORMAT_R32G32B32A32_FLOAT;
	}
	else if(valuestr == "FLOAT2")
	{
		return DXGI_FORMAT_R32G32_FLOAT;
	}

	return DXGI_FORMAT_UNKNOWN;
}

void Effect::OutErrorMsg( ID3D10Blob*  errorMessage, WCHAR* filename)
{
	char* compileErrors;
	unsigned long bufferSize, i;
	ofstream fout;


	// Get a pointer to the error message text buffer.
	compileErrors = (char*)(errorMessage->GetBufferPointer());

	// Get the length of the message.
	bufferSize = errorMessage->GetBufferSize();

	// Open a file to write the error message to.
	fout.open("shader-error.txt");

	// Write out the error message.
	for(i=0; i<bufferSize; i++)
	{
		fout << compileErrors[i];
	}

	// Close the file.
	fout.close();

	// Release the error message.
	errorMessage->Release();
	errorMessage = 0;

	// Pop a message up on the screen to notify the user to check the text file for compile errors.
	

	SystemClass::Instance().WarningDialog(filename, L"Error compiling shader.  Check shader-error.txt for message.");
}

bool Effect::setTexture( std::string key_, ID3D11ShaderResourceView* text_ )
{
	TEXTURECONTAIN::iterator it = m_VTexture.find(key_);
	if(it == m_VTexture.end()) return false;

	m_VTexture[key_] = text_;
	return true;
}