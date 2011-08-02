#include <SFML/Graphics/Rect.hpp>
#include <Viewer/UIEvent.hh>
#include <Viewer/CheckBoxLabel.hh>
#include <Viewer/EnumCheckBoxes.hh>

namespace Viewer {
namespace GUIs {

EnumCheckBoxes::EnumCheckBoxes( sf::Rect<double>& rect, unsigned int guiID )
    : GUI ( rect, guiID )
{
    fState = 0;
}

void EnumCheckBoxes::SetLabels( std::vector< std::string >& labels )
{
    double shift = fRect.Height / labels.size();
    sf::Rect< double > rect = sf::Rect< double >( fRect.Left, fRect.Top, fRect.Width, fRect.Height / labels.size() );
    for( int i = 0; i < labels.size(); i++ )
    {
        GUIs::CheckBoxLabel* checkBoxLabel = new CheckBoxLabel( rect, -1 );
        checkBoxLabel->SetLabel( labels.at( i ) );
        fCheckBoxes.push_back( checkBoxLabel );
        rect.Top += shift;
    }
}

void EnumCheckBoxes::Render( RWWrapper& windowApp )
{
    for( int i = 0; i < fCheckBoxes.size(); i++ )
    {
        bool state = false;
        if( fState == i ) state = true;
        fCheckBoxes.at( i )->SetState( state );
        fCheckBoxes.at( i )->Render( windowApp );
    }
}

GUIReturn EnumCheckBoxes::NewEvent( UIEvent& event )
{
    GUIReturn retEvent; // Default NULL event
    switch( event.Type )
    {
        case sf::Event::MouseMoved:
            fCurrentPos = event.GetLocalCoord();
            break;
        case sf::Event::MouseButtonReleased:
            for( int i = 0; i < fCheckBoxes.size(); i++ )
            {
                if( fCheckBoxes.at( i )->ContainsPoint( fCurrentPos ) )
                    fState = i;
            }
            break;
    }
    return retEvent;
}

}; // namespace GUIs
}; // namespace Viewer

