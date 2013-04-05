#include <iostream>

#include <Viewer/ModuleManager3d.hh>
#include <Viewer/BaseFrame3d.hh>

namespace Viewer {
namespace Frames {

BaseFrame3d::BaseFrame3d(
			 RectPtr rect )
  : Frame( rect )
{

}

BaseFrame3d::~BaseFrame3d()
{
	delete fModuleManager;
	fModuleManager = NULL;
}

void BaseFrame3d::PreInitialise( const ConfigurationTable* configTable )
{
  fModuleManager = CreateModuleManager();
  CreateGUIObjects();
  fModuleManager->PreInitialise( configTable );
}

void BaseFrame3d::PostInitialise( const ConfigurationTable* configTable )
{
  fModuleManager->PostInitialise( configTable );
}

void BaseFrame3d::SaveConfiguration( ConfigurationTable* configTable )
{
  fModuleManager->SaveConfiguration( configTable );
}

void BaseFrame3d::EventLoop()
{
  while( fEvents.empty() == false )
    fEvents.pop();
  
  fModuleManager->EventLoop();
}

void BaseFrame3d::ProcessData( const RenderState& renderState )
{
  fModuleManager->ProcessData( renderState );
}

void BaseFrame3d::Render2d( RWWrapper& renderApp, const RenderState& renderState )
{
  fModuleManager->Render2d( renderApp, renderState );
}
  
void BaseFrame3d::Render3d( RWWrapper& renderApp, const RenderState& renderState )
{
  fModuleManager->Render3d( fRect, renderState );
}

}; // namespace Frames
}; // namespce Viewer

