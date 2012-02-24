#include <Viewer/ModuleManager3d.hh>
#include <Viewer/BaseFrame3d.hh>

namespace Viewer {
namespace Frames {

BaseFrame3d::BaseFrame3d(
			 RectPtr rect )
  : Frame( rect )
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

void BaseFrame3d::Render2d( RWWrapper& renderApp, const RenderState& renderState )
{
	fModuleManager->Render2d( renderApp );
}

void BaseFrame3d::Render3d( RWWrapper& renderApp, const RenderState& renderState )
{
	fModuleManager->Render3d( fRect );
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

