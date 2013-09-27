#include "FrontTestSample.h"
#include "UILib/FrontLable.h"
#include "UILib/UISystem.h"

bool FrontTestSample::init()
{

	EVAUI::FrontLable* pLable = new EVAUI::FrontLable(std::string("Eva UI Font !"), EVAUI::UISystem::instance().TopLeft());

	EVAUI::UISystem::instance().Root()->addchild(pLable);
	return true;
}

void FrontTestSample::fini()
{

}

void FrontTestSample::update( float det )
{

}

bool FrontTestSample::render()
{
	return true;
}