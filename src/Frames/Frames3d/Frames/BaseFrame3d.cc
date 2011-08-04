#include <iostream>

#include <Viewer/ModuleManager3d.hh>
#include <Viewer/BaseFrame3d.hh>

namespace Viewer {
namespace Frames {

BaseFrame3d::BaseFrame3d()
{
	fInitialised = false;
}

BaseFrame3d::~BaseFrame3d()
{

}

void BaseFrame3d::Initialise()
{
	std::cout << "in initialise()\n";
	fModuleManager = CreateModuleManager();
}

void BaseFrame3d::LoadConfiguration( ConfigurationTable& configTable )
{
	std::cout << "in load configuration\n";
	fModuleManager->LoadModuleConfigurations( configTable );
}

void BaseFrame3d::SaveConfiguration( ConfigurationTable& configTable )
{
	std::cout << "in save configuration\n";
	fModuleManager->SaveModuleConfigurations( configTable );
}

void BaseFrame3d::EventLoop()
{
	std::cout << "in event loop\n";
	LateInitialise();
	fModuleManager->EventLoop();
}

void BaseFrame3d::Render2d( RWWrapper& windowApp )
{
	fModuleManager->Render2d( windowApp );
}

void BaseFrame3d::Render3d()
{
	std::cout << "in render3d\n";
	fViewportRect.SetFromLocalRect( GetViewportArea(), fFrameRect );
	fModuleManager->Render3d( fViewportRect );
}

void BaseFrame3d::LateInitialise()
{
	if( fInitialised == false )
	{
		fModuleManager->LateInitialise();
		CreateGUIObjects();
		fInitialised = true;
	}
}

}; // namespace Frames
}; // namespce Viewer

