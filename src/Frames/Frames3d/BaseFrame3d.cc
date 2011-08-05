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
	delete fModuleManager;
	fModuleManager = NULL;
}

void BaseFrame3d::Initialise()
{
	fModuleManager = CreateModuleManager();
}

void BaseFrame3d::LoadConfiguration( ConfigurationTable& configTable )
{
	fModuleManager->LoadModuleConfigurations( configTable );
}

void BaseFrame3d::SaveConfiguration( ConfigurationTable& configTable )
{
	fModuleManager->SaveModuleConfigurations( configTable );
}

void BaseFrame3d::EventLoop()
{
	while( fEvents.empty() == false )
		fEvents.pop();

	LateInitialise();
	fModuleManager->EventLoop();
}

void BaseFrame3d::Render2d( RWWrapper& windowApp )
{
	fModuleManager->Render2d( windowApp );
}

void BaseFrame3d::Render3d()
{
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

