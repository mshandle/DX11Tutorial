#include "Effect.h"
#include "tinyxml.h"
#include "SystemClass.h"
#include "ShaderCBuffer.h"
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
		SystemClass::Instance().WarningDialog((WCHAR*)filename,L"Not find");

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
	/*ShaderCBuffer* tmp = CBufferManager::Instance().get("WorldViewProject");
	
	WorldViewProject::WorldViewProjectData* data = new WorldViewProject::WorldViewProjectData();;
	int size = tmp->size();
	tmp->InitBuffer((void**)&data);*/

	printf("hello");
	return true;
}

bool Effect::commit()
{

}