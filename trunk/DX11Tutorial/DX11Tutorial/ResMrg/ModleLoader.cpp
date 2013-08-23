#include "ModleLoader.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <D3DX10math.h>
#include "framework/SystemClass.h"
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

bool ModleLoader::loaderModel( WCHAR* _modlefile, D3DVertexBuffer** vbuffer, D3DIndexBuffer** ibuffer )
{
	std::ifstream file(_modlefile);     //open the model file
	if(!file.is_open())
	{
		SystemClass::Instance().WarningDialog(_modlefile,L"No find File!");
		return false;
	}
	std::vector<D3DXVECTOR3*> vPosition;
	std::vector<D3DXVECTOR3*> vNormal;
	std::vector<D3DXVECTOR2*> vVU;
	//std::vector<D3DXVECTOR3>
	char buf[256];  //temp buffer for each line
	std::vector<std::string*> coord;
	
	int verNum = 0;
	int IndNum = 0;
	int faceNum = 0;

	while(!file.eof())
	{
		file.getline(buf,256);    //while we are not in the end of the file, read everything as a string to the coord vector
		coord.push_back(new std::string(buf));
	}
	
	for(unsigned int lineIndex = 0; lineIndex < coord.size(); lineIndex++) //and then go through all line and decide what kind of line it is
	{
		std::string line = *coord[lineIndex];

		if(line[0] == '#')
			continue; // this is # continue
		else if(line[0] == 'v' && line[1] == ' ') //v this is vertex
		{
			float tmpx,tmpy,tmpz;
			sscanf(line.c_str(),"v %f %f %f",&tmpx,&tmpy,&tmpz);       //read the 3 floats, which makes up the vertex
			//vertex.push_back(new coordinate(tmpx,tmpy,tmpz));
		}

		else if(line[0] == 'v' && line[1] == 't')//vt is texturecood
		{

		}
		else if(line[0] =='v' && line[1] == 'n')//vn normal
		{

		}
		else if(line[0] == 'f')
		{

		}

	}
	return true;

}