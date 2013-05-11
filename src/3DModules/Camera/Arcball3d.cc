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
            if( dragArea->IsLeftPressed() && fDragRotate == false ) // Start of drag rotation
              {
                fDragStartPos = Rect::GetOpenGLCoords( dragArea->GetStartPos() );
                fDragEndPos = Rect::GetOpenGLCoords( dragArea->GetEndPos() );
		fDragRotate = true;
              }
            else if( dragArea->IsLeftPressed() ) // Normal dragging
              {
                fDragEndPos = Rect::GetOpenGLCoords( dragArea->GetEndPos() ); // Switch to openGL Coords
                fDragRotate = true;
              }
            else
              fDragRotate = false;
	    if( dragArea->IsRightPressed() )
	      {
		fZoom -= ( dragArea->GetEndPos().y - dragArea->GetStartPos().y ) / 1000.0;
		if( fZoom < kMinZoom ) fZoom = kMinZoom;
		if( fZoom > kMaxZoom ) fZoom = kMaxZoom;
	      }
          }
          break;
        case 1: // Rotate
          fRotate = ( dynamic_cast<GUIs::PersistLabel*>( fGUIManager.GetGUI( 1 ) )->GetState() );
          break;
        case 2: // Zoom in
          fZoom -= 0.1;
          if( fZoom < kMinZoom ) fZoom = kMinZoom;
          break;
        case 3: // Zoom out
          fZoom += 0.1;
          if( fZoom > kMaxZoom ) fZoom = kMaxZoom;
          break;
        case 4: // Reset
          Reset();
          break;
        case 5: // Right
          {
            Rotation rotation( TVector3( 0.0, 0.0, 1.0 ), kSpinSpeed );
            Rotate( rotation );
          }
          break;
        case 6: // down
          {
            Rotation rotation( TVector3( 1.0, 0.0, 0.0 ), -kSpinSpeed );
            Rotate( rotation );
          }
          break;
        case 7: // left 
          {
            Rotation rotation( TVector3( 0.0, 0.0, 1.0 ), -kSpinSpeed );
            Rotate( rotation );
          }
          break;
        case 8: // up
          {
            Rotation rotation( TVector3( 1.0, 0.0, 0.0 ), kSpinSpeed );
            Rotate( rotation );
          }
          break;
        case 9: // Flip
          fCamera = -fCamera;
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
  size.left = 0.5; size.top = 0.95; size.width = 0.5; size.height = 0.05;
  GUIs::PersistLabel* rotate = dynamic_cast<GUIs::PersistLabel*>( fGUIManager.NewGUI<GUIs::PersistLabel>( size ) );
  rotate->Initialise( 16, "Rotate" );
  if( configTable != NULL )
    fRotate = static_cast<bool>( configTable->GetI( "Rotate" ) );
  rotate->SetState( fRotate );
  // Now the other buttons
  size.left = 0.0; size.top = 0.95; size.width = 0.05; size.height = 0.05;
  for( int iButton = 0; iButton < 8; iButton++ )
    {
      GUIs::Button* button = dynamic_cast<GUIs::Button*>( fGUIManager.NewGUI<GUIs::Button>( size ) );
      button->Initialise( 20 + iButton );
      size.left += 0.05;
    }
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

