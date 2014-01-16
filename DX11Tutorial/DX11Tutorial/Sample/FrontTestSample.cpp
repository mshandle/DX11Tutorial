#include "FrontTestSample.h"
#include "UILib/FrontLable.h"
#include "UILib/UISystem.h"

bool FrontTestSample::init()
{

	/*pLable = new EVAUI::FrontLable(std::string("Eva UI Font !"), EVAUI::UISystem::instance().TopLeft());

	EVAUI::UISystem::instance().Root()->addchild(pLable);*/
	return true;
}

void FrontTestSample::fini()
{

}

void FrontTestSample::update( float det )
{
	/*static int Index = 0;

	char buffer[256];

	sprintf(buffer,"Eva UI Font ! %d", Index);
	pLable->setString(std::string(buffer));

	Index++;*/
}

bool FrontTestSample::render()
{
	return true;
}