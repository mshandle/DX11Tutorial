#include "ModleLoader.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <D3DX10math.h>
#include "framework/SystemClass.h"
#include "../Base/VertexFormat.h"
ModleLoader::ModleLoader(void)
{
}

ModleLoader::~ModleLoader(void)
{
}

ModleLoader& ModleLoader::Instance()
{
	static ModleLoader instance;
	return instance;
}

Model* ModleLoader::loaderModel(const std::string& _modlefile)
{
	std::ifstream file(_modlefile);     //open the model file
	if(!file.is_open())
	{
		//SystemClass::Instance().WarningDialog(_modlefile.c_str(),L"No find File!");
		return false;
	}
	std::vector<D3DXVECTOR3> vPosition;
	std::vector<D3DXVECTOR3> vNormal;
	std::vector<D3DXVECTOR2> vVU;
	std::vector<FaceType>    vIndex;
	//std::vector<D3DXVECTOR3>
	char buf[256];  //temp buffer for each line
	std::vector<std::string> coord;

	int verNum = 0;
	int IndNum = 0;
	int faceNum = 0;

	while(!file.eof())
	{
		file.getline(buf,256);    //while we are not in the end of the file, read everything as a string to the coord vector
		coord.push_back(std::string(buf));
	}
	
	for(unsigned int lineIndex = 0; lineIndex < coord.size(); lineIndex++) //and then go through all line and decide what kind of line it is
	{
		std::string line = coord[lineIndex];
		
		if(line.empty()) continue;

		if(line[0] == '#')
			continue; // this is # continue
		else if(line[0] == 'v' && line[1] == ' ') //v this is vertex
		{
			float tmpx,tmpy,tmpz;
			sscanf(line.c_str(),"v %f %f %f",&tmpx,&tmpy,&tmpz);       //read the 3 floats, which makes up the vertex
			vPosition.push_back(D3DXVECTOR3(tmpx,tmpy,tmpz*-1.0));//translate left hand to right hand
			verNum++;
		}

		else if(line[0] == 'v' && line[1] == 't')//vt is texturecood
		{
			float fTmpU,fTmpV;
			sscanf(line.c_str(),"vt %f %f",&fTmpU,&fTmpV);
			vVU.push_back(D3DXVECTOR2(fTmpU,1.0 - fTmpV));//translate left hand to right hand
		}
		else if(line[0] =='v' && line[1] == 'n')//vn normal
		{
			float fTmpX,fTmpY,fTmpZ;
			sscanf(line.c_str(),"vn %f %f %f",&fTmpX,&fTmpY, &fTmpZ);
			vNormal.push_back(D3DXVECTOR3(fTmpX, fTmpY,fTmpZ*-1.0f));//translate left hand to right hand
		}
		else if(line[0] == 'f')
		{
			
			FaceType value_;
			//f 1/1 2/2 3/3
			//sscanf(line.c_str(),"f %d/%d %d/%d %d/%d", &value_.vIndex1,&value_.tIndex1, &value_.vIndex2, &value_.tIndex2, &value_.vIndex3, &value_.tIndex3);
			//f 1/1/1 2/2/2 3/3/3
			sscanf(line.c_str(),"f %d/%d/%d %d/%d/%d %d/%d/%d", &value_.vIndex1,&value_.tIndex1,&value_.nIndex1, &value_.vIndex2, &value_.tIndex2,&value_.nIndex2, &value_.vIndex3, &value_.tIndex3,&value_.nIndex3);
			
			vIndex.push_back(value_);
		}

	}

	XYZNUV* pVertBuff = new XYZNUV[vIndex.size() * 3];
	unsigned long* indices = new unsigned long[vIndex.size() * 3];

	for(unsigned int nIndex= 0; nIndex < vIndex.size(); nIndex++)
	{
		int VerBufferIndex = nIndex * 3;
		/****************************************************/
		int VPostionIndex = vIndex[nIndex].vIndex1 -1;
		if(VPostionIndex >= vPosition.size())
		{
			pVertBuff[VerBufferIndex].position = vPosition[VPostionIndex - 1];
		}
		else
		{
			pVertBuff[VerBufferIndex].position = vPosition[VPostionIndex];
		}
		
		if(vIndex[nIndex].nIndex1!= -1)
		{
			pVertBuff[VerBufferIndex].normal = vNormal[vIndex[nIndex].nIndex1 - 1];
		}
		int vtexIndex = vIndex[nIndex].tIndex1-1;
		if(VPostionIndex >= vVU.size())
		{
			pVertBuff[VerBufferIndex].uv = vVU[vtexIndex - 1];
		}
		else
		{
			pVertBuff[VerBufferIndex].uv = vVU[vtexIndex];
		}
		/****************************************************/

		VPostionIndex = vIndex[nIndex].vIndex2 -1;
		if(VPostionIndex >= vPosition.size())
		{
			pVertBuff[VerBufferIndex +1].position = vPosition[VPostionIndex - 1];
		}
		else
		{
			pVertBuff[VerBufferIndex + 1].position = vPosition[VPostionIndex];
		}

		if(vIndex[nIndex].nIndex2!= -1)
		{
			pVertBuff[VerBufferIndex].normal = vNormal[vIndex[nIndex].nIndex2 - 1];
		}

		vtexIndex = vIndex[nIndex].tIndex2-1;
		if(VPostionIndex >= vVU.size())
		{
			pVertBuff[VerBufferIndex+1].uv = vVU[vtexIndex - 1];
		}
		else
		{
			pVertBuff[VerBufferIndex+1].uv = vVU[vtexIndex];

		}
	
		/****************************************************/

		VPostionIndex = vIndex[nIndex].vIndex3 -1;
		if(VPostionIndex >= vPosition.size())
		{
			pVertBuff[VerBufferIndex +2].position = vPosition[VPostionIndex - 1];
		}
		else
		{
			pVertBuff[VerBufferIndex + 2].position = vPosition[VPostionIndex];
		}

		if(vIndex[nIndex].nIndex3!= -1)
		{
			pVertBuff[VerBufferIndex].normal = vNormal[vIndex[nIndex].nIndex3 - 1];
		}

		vtexIndex = vIndex[nIndex].tIndex3-1;
		if(VPostionIndex >= vVU.size())
		{
			pVertBuff[VerBufferIndex+2].uv = vVU[vtexIndex - 1];
		}
		else
		{
			pVertBuff[VerBufferIndex+2].uv = vVU[vtexIndex];

		}

	}

	for(unsigned int nIndex = 0; nIndex < vIndex.size() * 3; nIndex++)
	{
		indices[nIndex] = nIndex;
	}
	bool result = true;
	D3DVertexBuffer* m_vertexBuffer = new D3DVertexBuffer();
	if(m_vertexBuffer)
	{
		result =m_vertexBuffer->init(sizeof(XYZNUV) * (vIndex.size() * 3), (void*)pVertBuff,sizeof(XYZNUV));
		SAFE_DELETE(pVertBuff);
	}

	D3DIndexBuffer* m_indexBuffer = new D3DIndexBuffer();
	if(m_indexBuffer)
	{
		result = m_indexBuffer->init(sizeof(unsigned long) * (vIndex.size() * 3), (void*)indices);
		SAFE_DELETE(indices);
	}

	
	if(result)
	{
		Model* pModle = new Model(m_vertexBuffer, m_indexBuffer, vIndex.size());
		return pModle;
	}
	else
	{
		return NULL;
	}

}