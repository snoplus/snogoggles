#include <Viewer/Frame3d.hh>
#include <Viewer/Module3d.hh>
#include <Viewer/Camera3d.hh>
using namespace Viewer;

Module3dFactory Frame3d::fsModule3dFactory;

Frame3d::Frame3d( RectPtr rect )
  : Frame( rect )
{

}

Frame3d::~Frame3d()
{
  for( vector<Module3d*>::iterator iTer = fModules.begin(); iTer != fModules.end(); iTer++ )
    delete *iTer;
  delete fCamera;
}

void 
Frame3d::NewEvent( const Event& event )
{
  for( vector<Module3d*>::iterator iTer = fModules.begin(); iTer != fModules.end(); iTer++ )
    (*iTer)->NewEvent( event );
  fCamera->NewEvent( event );
}

void 
Frame3d::EventLoop()
{
  for( vector<Module3d*>::iterator iTer = fModules.begin(); iTer != fModules.end(); iTer++ )
    (*iTer)->EventLoop();
  fCamera->EventLoop();
}

void 
Frame3d::SaveConfiguration( ConfigurationTable* configTable )
{
  for( vector<Module3d*>::iterator iTer = fModules.begin(); iTer != fModules.end(); iTer++ )
    (*iTer)->SaveConfiguration( configTable ); 
  fCamera->SaveConfiguration( configTable );
}

void 
Frame3d::PreInitialise( const ConfigurationTable* configTable )
{
  for( vector<Module3d*>::iterator iTer = fModules.begin(); iTer != fModules.end(); iTer++ )
    (*iTer)->PreInitialise( configTable );
  fCamera->PreInitialise( configTable );
}

void 
Frame3d::PostInitialise( const ConfigurationTable* configTable )
{
  for( vector<Module3d*>::iterator iTer = fModules.begin(); iTer != fModules.end(); iTer++ )
    (*iTer)->PostInitialise( configTable );
  fCamera->PostInitialise( configTable );
}

void 
Frame3d::ProcessData( const RenderState& renderState )
{
  for( vector<Module3d*>::iterator iTer = fModules.begin(); iTer != fModules.end(); iTer++ )
    (*iTer)->ProcessData( renderState );
  fCamera->ProcessData( renderState );
}

void 
Frame3d::Render3d( RWWrapper& renderApp,
                   const RenderState& )
{
  fCamera->SetGLCamera();
  for( vector<Module3d*>::iterator iTer = fModules.begin(); iTer != fModules.end(); iTer++ )
    (*iTer)->Render3d();
  fCamera->Render3d();
}

void 
Frame3d::RenderGUI( RWWrapper& renderApp,
                    const RenderState& )
{
  for( vector<Module3d*>::iterator iTer = fModules.begin(); iTer != fModules.end(); iTer++ )
    (*iTer)->RenderGUI( renderApp );
  fCamera->RenderGUI( renderApp );
}

void 
Frame3d::SetCamera( const std::string& cameraName,
                    const sf::Rect<double>& cameraSize )
{
  RectPtr cameraRect = RectPtr( fRect->NewDaughter( cameraSize, Rect::eLocal ) );
  fCamera = dynamic_cast< Camera3d* >( fsModule3dFactory.New( cameraName, cameraRect ) );
}

void 
Frame3d::AddModule( const std::string& moduleName,
                    const sf::Rect<double>& guiSize )
{
  RectPtr rect = RectPtr( fRect->NewDaughter( guiSize, Rect::eLocal ) );
  fModules.push_back( fsModule3dFactory.New( moduleName, rect ) );
}
