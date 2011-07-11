#include <Viewer/HitRenderer3d.hh>
#include <Viewer/OpenGLUtils.hh>

#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <TVector3.h>
#include <TMath.h>

namespace Viewer {
namespace Frames {

void HitRenderer3d::RenderSolidHit( const TVector3& pos )
{
    glPushMatrix();
    RotateToRenderHit( pos );
    RenderHexagonOnBallSolid( pos );
    glPopMatrix();
}

void HitRenderer3d::RenderHollowHit( const TVector3& pos )
{
    glPushMatrix();
    RotateToRenderHit( pos );
    RenderHexagonOnBallHollow( pos );
    glPopMatrix();
}

void HitRenderer3d::RotateToRenderHit( const TVector3& pos )
{
    TVector3 zAxis( 0, 0, 1 );
    OpenGLUtils::RotateGLMatrix( zAxis, pos.Unit() );
}

void HitRenderer3d::RenderHexagonOnBallSolid( const TVector3& pos )
{
    glBegin(GL_TRIANGLES);
    for (int i = 0; i <= NUM_VERTICES_IN_HEXAGON; i++)
    {
        float angle = 2 * TMath::Pi() * i / NUM_VERTICES_IN_HEXAGON;
        float nextAngle = 2 * TMath::Pi() * (i+1) / NUM_VERTICES_IN_HEXAGON;
        glVertex3f(RADIUS * sin(angle), RADIUS * cos(angle), pos.Mag());
        glVertex3f(RADIUS * sin(nextAngle), RADIUS * cos(nextAngle), pos.Mag());
        glVertex3f(0, 0, pos.Mag());
    }
    glEnd();

}

void HitRenderer3d::RenderHexagonOnBallHollow( const TVector3& pos )
{
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < NUM_VERTICES_IN_HEXAGON; i++)
    {
        float angle = 2* TMath::Pi() * i / NUM_VERTICES_IN_HEXAGON;
        glVertex3f(RADIUS * sin(angle), RADIUS * cos(angle), pos.Mag());
    }
    glEnd();

}

void HitRenderer3d::DrawPMT( const TVector3& pmtPos, const TVector3& pmtDir, bool fill )
{
  double yAngle = (-1.0)*atan2( pmtDir.x(), pmtDir.z() );
  double xAngle = atan2( pmtDir.y(), sqrt( pmtDir.x() * pmtDir.x() + pmtDir.z()
* pmtDir.z() ) );

  glPushMatrix();
  glTranslatef( pmtPos.x(), pmtPos.y(), pmtPos.z() );

  glRotatef( xAngle * 180 / TMath::Pi(), 1.0, 0.0, 0.0 );
  glRotatef( yAngle * 180 / TMath::Pi(), 0.0, 1.0, 0.0 );
  glRotatef( 30.0, 0.0, 0.0, 1.0 );

  if( fill == true )
    {
      glBegin(GL_TRIANGLES);
      for (int i = 0; i <= 6; i++)
        {
          float angle = 2 * TMath::Pi() * i / 6.0f;
          float nextAngle = 2 * TMath::Pi() * (i+1) / 6.0f;
          const float radius = 140.0;
          glVertex3f(radius * sin(angle), radius * cos(angle), 1);
          glVertex3f(radius * sin(nextAngle), radius * cos(nextAngle), 1);
          glVertex3f(0, 0, 1);
        }
    }
  else
    {
      glBegin(GL_LINE_LOOP);
      for (int i = 0; i < 6; i++)
        {
          float angle = 2* TMath::Pi() * i / 6.0f;
          const float radius = 140.0;
          glVertex3f( radius * sin(angle), radius * cos(angle), 1 );
        }
    }
  glEnd();
  glPopMatrix();
}

}; // namespace Frames
}; // namespace Viewer
