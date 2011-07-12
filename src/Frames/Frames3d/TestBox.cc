#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

#include <Viewer/TestBox.hh>
#include <Viewer/GUIManager.hh>
#include <Viewer/DragArea.hh>
using namespace Viewer;
using namespace Viewer::Frames;

void 
TestBox::Initialise( ConfigurationTable& configTable )
{
  Frame::Initialise( configTable );
  sf::Rect<double> dragPos = sf::Rect<double>( 0.0, 0.0, 1.0, 1.0 );
  fRotate = 0.0;
  fDragArea = dynamic_cast<GUIs::DragArea*>( fGUIManager.NewGUI<GUIs::DragArea>( dragPos ) );
}

void 
TestBox::EventLoop()
{
  while( !fEvents.empty() )
    {
      if( fEvents.front().fguiID == 0 )
	fRotate = fDragArea->GetMoveDelta().x;
      fEvents.pop();
    }
}

void
TestBox::Render3d()
{
  // Remember Rect is defined as top left, viewport as bottom left
  fFrameRect.SetAsGLViewport();
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(90.f, 1.f, 1.f, 500.f);
  // Clear color and depth buffer
  //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  // NOTE: OpenGL buffers should NOT be cleared in frames!!!!!
  
  // Apply some transformations
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glTranslatef(0.f, 0.f, -200.f);
  glRotatef(fRotate, 1.f, 0.f, 0.f);
  //glRotatef(clock.GetElapsedTime() * 30, 0.f, 1.f, 0.f);
  //glRotatef(clock.GetElapsedTime() * 90, 0.f, 0.f, 1.f);
  
  // Draw a cube
  glBegin(GL_QUADS);
  
  glColor3f(1.f, 0.f, 0.f);
  glVertex3f(-50.f, -50.f, -50.f);
  glVertex3f(-50.f,  50.f, -50.f);
  glVertex3f( 50.f,  50.f, -50.f);
  glVertex3f( 50.f, -50.f, -50.f);
  
  glColor3f(1.f, 0.f, 0.f);
  glVertex3f(-50.f, -50.f, 50.f);
  glVertex3f(-50.f,  50.f, 50.f);
  glVertex3f( 50.f,  50.f, 50.f);
  glVertex3f( 50.f, -50.f, 50.f);
  
  glColor3f(0.f, 1.f, 0.f);
  glVertex3f(-50.f, -50.f, -50.f);
  glVertex3f(-50.f,  50.f, -50.f);
  glVertex3f(-50.f,  50.f,  50.f);
  glVertex3f(-50.f, -50.f,  50.f);
  
  glColor3f(0.f, 1.f, 0.f);
  glVertex3f(50.f, -50.f, -50.f);
  glVertex3f(50.f,  50.f, -50.f);
  glVertex3f(50.f,  50.f,  50.f);
  glVertex3f(50.f, -50.f,  50.f);
  
  glColor3f(0.f, 0.f, 1.f);
  glVertex3f(-50.f, -50.f,  50.f);
  glVertex3f(-50.f, -50.f, -50.f);
  glVertex3f( 50.f, -50.f, -50.f);
  glVertex3f( 50.f, -50.f,  50.f);
  
  glColor3f(0.f, 0.f, 1.f);
  glVertex3f(-50.f, 50.f,  50.f);
  glVertex3f(-50.f, 50.f, -50.f);
  glVertex3f( 50.f, 50.f, -50.f);
  glVertex3f( 50.f, 50.f,  50.f);
  
  glEnd();
}
