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
  Frame::Initialise();
	fModuleManager = CreateModuleManager();
}

void BaseFrame3d::LoadConfiguration( const ConfigurationTable* configTable )
{
	fModuleManager->LoadModuleConfigurations( configTable );
}

void BaseFrame3d::SaveConfiguration( ConfigurationTable* configTable )
{
	fModuleManager->SaveModuleConfigurations( configTable );
}

void BaseFrame3d::EventLoop()
{
	while( fEvents.empty() == false )
		fEvents.pop();

	LateInitialise(); // This is very prone to cause segfaults, must it work this way?
	fModuleManager->EventLoop();
}

void BaseFrame3d::Render2d( RWWrapper& renderApp, const RenderState& renderState )
{
	fModuleManager->Render2d( renderApp, renderState );
}

void BaseFrame3d::Render3d( RWWrapper& renderApp, const RenderState& renderState )
{
	fModuleManager->Render3d( fRect, renderState );
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

