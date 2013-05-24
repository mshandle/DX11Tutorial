#include "XMLTestSample.h"
#include "tinyxml.h"
#include "Effect.h"
XMLTestSample::XMLTestSample(void)
{
}

XMLTestSample::~XMLTestSample(void)
{
}

bool XMLTestSample::init()
{
	/*TiXmlDocument *pDoc = new TiXmlDocument();
	if (NULL==pDoc)  
	{  
		return false;  
	}  
	pDoc->LoadFile("../res/confige/confige.xml"); 

	const TiXmlElement* root = pDoc->RootElement();
	//const char* name = root->Value();
	const TiXmlNode* first =root->IterateChildren("Shader", NULL);
	const TiXmlNode* shaderIndex =NULL;
	std::string name;
	do
	{
		shaderIndex = first->IterateChildren(shaderIndex);
		if(NULL != shaderIndex)
		{
			name = shaderIndex->Value();
		}
	}while(NULL != shaderIndex);
	*/
	Effect* effect = new Effect();
	effect->load("../res/shader/staticModleShader.xml");
	return true;
}

void XMLTestSample::fini()
{

}

void XMLTestSample::update( float det )
{

}

bool XMLTestSample::render()
{
	return true;
}