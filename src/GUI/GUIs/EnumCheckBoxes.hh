////////////////////////////////////////////////////////////////////////
/// \class Viewer::GUIs::EnumCheckBoxes
///
/// \brief   
///
/// \author  Olivia Wasalski <wasalski@triumf.ca>
///			     <oliviawasalski@gmail.com>
///
/// REVISION HISTORY:\n
///     30/07/11 : Olivia Wasalski - First Revision, new file. \n
///
/// \detail  As brief
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_GUIs_EnumCheckBoxes__
#define __Viewer_GUIs_EnumCheckBoxes__

#include <vector>
#include <string>
#include <SFML/System/Vector2.hpp>
#include <Viewer/GUI.hh>

namespace Viewer { 
namespace GUIs {
    class CheckBoxLabel;

class EnumCheckBoxes : public GUI {
public:
    EnumCheckBoxes( const sf::Rect<double>& rect, unsigned int guiID );
    virtual ~EnumCheckBoxes() { }
    virtual void SetLabels( std::vector< std::string >& labels );
    virtual void RenderT( sf::RenderWindow& windowApp ) { }
    virtual void Render( RWWrapper& windowApp );
    virtual GUIReturn NewEvent( Event& event );

    inline void SetState( int state );
    inline int GetState() const;
    template < typename T > inline T GetEnumState() const;

protected:
    int fState;
    std::vector< CheckBoxLabel* > fCheckBoxes;
    sf::Vector2< double > fCurrentPos;
};

////////////////////////////////////////////////////////////////////////
// Inline methods
////////////////////////////////////////////////////////////////////////
void EnumCheckBoxes::SetState( int state )
{
    fState = state;
}

int EnumCheckBoxes::GetState() const
{
    return fState;
}

template < typename T > T
EnumCheckBoxes::GetEnumState() const
{
    return static_cast< T >( fState );
}

} // ::GUIs
} // ::Viewer
#endif

