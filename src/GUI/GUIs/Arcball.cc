#include <iostream>
#include <math.h>
#include <TVector3.h>
#include <SFML/Window/Event.hpp>
#include <Viewer/Event.hh>
#include <Viewer/Arcball.hh>

namespace Viewer {
namespace GUIs {

GUIEvent Arcball::NewEvent( const Event& event )
{
    GUIEvent ret; // NULL event
    switch( event.type )
    {
        case sf::Event::MouseMoved:
        {
	        fWindowPos = event.GetPos();
	        ret = GUIEvent( fID, fGlobalID );
	        break;
        }
        case sf::Event::MouseButtonPressed:
            fPressed = true;
            break;
        case sf::Event::LostFocus:
            fWindowPos = sf::Vector2<double>( -1, -1 );
            fPressed = false;
            break;
        case sf::Event::MouseButtonReleased:
            fPressed = false;
            break;
        }
    return ret;
}

void Arcball::Initialise( double radius )
{
    fRadius = radius;
    fPressed = false;
    fPreviousPressed = false;
    fUpdateRotation = false;
}

Rotation Arcball::Update( GLint* viewport, GLdouble* modelview_matrix, GLdouble* projection_matrix )
{
    Rotation result;

    GLdouble frontPos[3];
    GLdouble backPos[3];

    UnProject( viewport, modelview_matrix, projection_matrix, 0, frontPos );
    UnProject( viewport, modelview_matrix, projection_matrix, 1, backPos );

    TVector3 x0( frontPos[0], frontPos[1], frontPos[2] );
    TVector3 x1( backPos[0], backPos[1], backPos[2] );
    TVector3 l = (x1 - x0).Unit();
    double disc = (l * x0)*(l * x0) - (l*l)*(x0*x0 - fRadius*fRadius);

    if( disc > 0 ) 
    {
        fUpdateRotation = true;

        double d = -(l * x0) - sqrt( disc );
        TVector3 x = (d * l) + x0;
        TVector3 axis = x.Cross( fStartVector ).Unit();

        if( fPressed && !fPreviousPressed )
            fStartVector = x;

        else if( fPreviousPressed )
            result = Rotation( axis, x.Angle(fStartVector) );
    }
    else if( fUpdateRotation )
    {
        result = fPreviousRotation;
        fPressed = false;
        fUpdateRotation = false;
    }

    fPreviousPressed = fPressed;
    fPreviousRotation = result;
    return result;
}

void Arcball::UnProject( GLint* viewport, GLdouble* modelview_matrix, GLdouble* projection_matrix, GLdouble winZ, GLdouble* output )
{
    sf::Vector2<double> mouse = Rect::GetOpenGLCoords( fWindowPos );

    gluUnProject(
        mouse.x, mouse.y, winZ,
        modelview_matrix, projection_matrix, viewport,
        &output[0], &output[1], &output[2] 
    );
}

}; // namespace GUIs
}; // namespace Viewer

