////////////////////////////////////////////////////////////////////////
/// \class Viewer::GUIs::Arcball
///
/// \brief   Provides arcball rotation functionality
///
/// \author  Olivia Wasalski <wasalski@berkeley.ca>
///                          <oliviawasalski@gmail.com>
///
/// REVISION HISTORY:\n
///     05/22/12 : Olivia Wasalski - First Revision, New File. \n
///
/// \detail  As brief
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_GUIs_Arcball__
#define __Viewer_GUIs_Arcball__

#include <TVector3.h>
#include <SFML/OpenGL.hpp>
#include <Viewer/Rotation.hh>
#include <Viewer/GUI.hh>

namespace Viewer {  
namespace GUIs {

class Arcball : public GUI {

public:
    Arcball( RectPtr rect, unsigned int guiID ) : GUI( rect, guiID ) {}
    void Initialise( double radius );
    GUIEvent NewEvent( const Event& event );
    Rotation Update( GLint* viewport, GLdouble* modelview_matrix, GLdouble* projection_matrix );
    void Render( RWWrapper& renderApp ) {}
    bool GetState() { return fPressed; }
    
protected:
    void UnProject( GLint* viewport, GLdouble* modelview_matrix, GLdouble* projection_matrix, GLdouble winZ, GLdouble* output );

    bool fPressed;
    bool fPreviousPressed;

    double fRadius;
    sf::Vector2<double> fWindowPos;
    TVector3 fStartVector;

    bool fUpdateRotation;
    Rotation fPreviousRotation;

};

} // ::GUIs

} // ::Viewer

#endif
