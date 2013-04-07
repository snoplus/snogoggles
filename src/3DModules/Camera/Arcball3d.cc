#include <TVector3.h>

#include <cmath>

#include <Viewer/Arcball3d.hh>
#include <Viewer/PersistLabel.hh>
#include <Viewer/Button.hh>
#include <Viewer/GUIEvent.hh>
#include <Viewer/ConfigurationTable.hh>
#include <Viewer/Rotation.hh>
#include <Viewer/DragArea.hh>
using namespace Viewer;

const double kMaxZoom = 1.5;
const double kMinZoom = 0.1;
const double kRadius = 8500.0; /// < PSUP radius, thing camera looks at
const double kCameraOffset = 4.5; /// < How far in units of kRadius
const double kSpinSpeed = 0.5; /// < Default rotation speed, radians/second

void 
Arcball3d::EventLoop()
{
  while( !fEvents.empty() )
    {
      switch( fEvents.front().fguiID )
        {
        case 0: // Drag area mouse move or release
          {
            GUIs::DragArea* dragArea = dynamic_cast<GUIs::DragArea*>( fGUIManager.GetGUI( 0 ) );
            if( dragArea->GetPressed() == true && fDragRotate == false ) // Start of drag rotation
              {
                fDragStartPos = Rect::GetOpenGLCoords( dragArea->GetStartPos() );
                fDragEndPos = Rect::GetOpenGLCoords( dragArea->GetEndPos() );
                fDragRotate = true;
              }
            else if( dragArea->GetPressed() == true ) // Normal dragging
              {
                fDragEndPos = Rect::GetOpenGLCoords( dragArea->GetEndPos() ); // Switch to openGL Coords
                fDragRotate = true;
              }
            else
              fDragRotate = false;
          }
          break;
        case 1: // Reset
          Reset();
          break;
        case 2: // Flip
          fCamera = -fCamera;
           break;
        case 3: // Rotate
          fRotate = ( dynamic_cast<GUIs::PersistLabel*>( fGUIManager.GetGUI( 3 ) )->GetState() );
          break;
        }
      fEvents.pop();
    }
  if( fRotate )
    {
      Rotation zRotation( TVector3( 0.0, 0.0 ,1.0 ), kSpinSpeed * fClock.getElapsedTime().asSeconds() ); // Rotate about the z axis
      Rotate( zRotation );
    }
  fClock.restart();
}

void 
Arcball3d::SaveConfiguration( ConfigurationTable* configTable )
{
  configTable->SetI( "Rotate", fRotate );
}

void 
Arcball3d::PreInitialise( const ConfigurationTable* configTable )
{
  sf::Rect<double> size( 0.0, 0.0, 1.0, 0.95 );
  fGUIManager.NewGUI<GUIs::DragArea>( size );

  size.left = 0.0; size.top = 0.96; size.width = 0.05; size.height = 0.05;
  GUIs::Button* resetButton = dynamic_cast<GUIs::Button*>( fGUIManager.NewGUI<GUIs::Button>( size ) );
  resetButton->Initialise( 24 );
  size.left = 0.1;
  GUIs::Button* flipButton = dynamic_cast<GUIs::Button*>( fGUIManager.NewGUI<GUIs::Button>( size ) );
  flipButton->Initialise( 24 );
  size.left = 0.2; size.width = 0.8;
  GUIs::PersistLabel* rotate = dynamic_cast<GUIs::PersistLabel*>( fGUIManager.NewGUI<GUIs::PersistLabel>( size ) );
  rotate->Initialise( 14, "Rotate" );
  if( configTable != NULL )
    fRotate = static_cast<bool>( configTable->GetI( "Rotate" ) );
  rotate->SetState( fRotate );
  Reset(); // Reset/Initialise the camera
}

void 
Arcball3d::SetGLCamera()
{
  // First setup the projection (zoom, fov)
  sf::Rect<double> rect = fRect->GetRect( Rect::eGL );
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective( 45.f * fZoom, rect.width / rect.height, ( kCameraOffset - 1.1 ) * kRadius, ( kCameraOffset + 1.1 ) * kRadius );
  glViewport( static_cast<GLint>( rect.left ), 
              static_cast<GLint>( rect.top ), 
              static_cast<GLsizei>( rect.width ), 
              static_cast<GLsizei>( rect.height ) );
  /// Next the modelview (camera view)
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt( fCamera.X(), fCamera.Y(), fCamera.Z(),
             fEye.X(), fEye.Y(), fEye.Z(),
             fUp.X(), fUp.Y(), fUp.Z() );
  if( fDragRotate ) 
    DragRotate(); // Must calculate here after the camera has been setup (allows correct mouse to space conversion)
}

void
Arcball3d::Reset()
{
  fCamera.SetXYZ( kCameraOffset * kRadius, 0.0, 0.0 );
  fEye.SetXYZ( 0.0, 0.0, 0.0 );
  fUp.SetXYZ( 0.0, 0.0, 1.0 );
  fZoom = ( kMaxZoom + kMinZoom ) / 2.0;
}

void
Arcball3d::Rotate( Rotation& rotation )
{
  rotation.Rotate( fCamera );
  rotation.Rotate( fUp );
}

TVector3
PointToAxis( TVector3 x0, 
             TVector3 x1 )
{
  TVector3 l = (x1 - x0).Unit();
  double disc = (l * x0)*(l * x0) - (l*l)*(x0*x0 - kRadius*kRadius);

  if( disc > 0 ) 
    {
      double d = -(l * x0) - sqrt( disc );
      TVector3 x = (d * l) + x0;
      return x;
    }
  else
    return TVector3();
}

void
Arcball3d::DragRotate()
{
  GLint viewport[4];
  glGetIntegerv( GL_VIEWPORT, viewport );
  GLdouble modelMatrix[16];
  glGetDoublev( GL_MODELVIEW_MATRIX, modelMatrix );
  GLdouble projectionMatrix[16];
  glGetDoublev( GL_PROJECTION_MATRIX, projectionMatrix );

  GLdouble startFront[3], startBack[3], endFront[3], endBack[3];
  gluUnProject( fDragStartPos.x, fDragStartPos.y, 0, modelMatrix, projectionMatrix, viewport, &startFront[0], &startFront[1], &startFront[2] );
  gluUnProject( fDragStartPos.x, fDragStartPos.y, 1, modelMatrix, projectionMatrix, viewport, &startBack[0], &startBack[1], &startBack[2] );
  gluUnProject( fDragEndPos.x, fDragEndPos.y, 0, modelMatrix, projectionMatrix, viewport, &endFront[0], &endFront[1], &endFront[2] );
  gluUnProject( fDragEndPos.x, fDragEndPos.y, 1, modelMatrix, projectionMatrix, viewport, &endBack[0], &endBack[1], &endBack[2] );

  TVector3 startAxis = PointToAxis( TVector3( startFront[0], startFront[1], startFront[2] ), 
                                    TVector3( startBack[0], startBack[1], startBack[2] ) );
  TVector3 endAxis = PointToAxis( TVector3( endFront[0], endFront[1], endFront[2] ), 
                                  TVector3( endBack[0], endBack[1], endBack[2] ) );
  if( startAxis.Mag2() > 0.0 && endAxis.Mag2() > 0.0 )
    {
      TVector3 axis = endAxis.Cross( startAxis ).Unit();
      Rotation rotation( Rotation( axis, endAxis.Angle( startAxis ) ) );
      rotation.GLRotate();
      Rotate( rotation );
      fDragStartPos = fDragEndPos;
    }
}

