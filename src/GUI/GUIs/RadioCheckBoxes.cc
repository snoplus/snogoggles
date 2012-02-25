#include <SFML/Graphics/Rect.hpp>

using namespace std;

#include <Viewer/RadioCheckBoxes.hh>
#include <Viewer/CheckBoxLabel.hh>
#include <Viewer/RWWrapper.hh>
#include <Viewer/Event.hh>
using namespace Viewer;
using namespace Viewer::GUIs;

RadioCheckBoxes::~RadioCheckBoxes()
{
  for( unsigned int iCheckBox = 0; iCheckBox < fRadioCheckBoxes.size(); iCheckBox++ )
    delete fRadioCheckBoxes[iCheckBox];
  fRadioCheckBoxes.clear();
}

void 
RadioCheckBoxes::Initialise( const vector<string>& labels,
			     const int cols )
{
  sf::Rect<double> size;
  size.Left = 0.0;
  size.Width = 1.0 / (double)cols;
  double height = 1.0 / (double) labels.size();
  size.Height = height;
  int numPerCol = labels.size() / cols;
  for( unsigned int iLabel = 0; iLabel < labels.size(); iLabel++ )
    {
      size.Top = ( iLabel % numPerCol ) * height;
      size.Left = ( iLabel / numPerCol ) * size.Width;
      fRadioCheckBoxes.push_back( new CheckBoxLabel( RectPtr( fRect->NewDaughter( size, Rect::eLocal ) ), iLabel ) );
      fRadioCheckBoxes[iLabel]->SetLabel( labels[iLabel] );
    }
  fRadioCheckBoxes[0]->SetState( true );
}

void 
RadioCheckBoxes::Render( RWWrapper& renderApp )
{
  for( unsigned int iCheckBox = 0; iCheckBox < fRadioCheckBoxes.size(); iCheckBox++ )
    fRadioCheckBoxes[iCheckBox]->Render( renderApp );
}

GUIEvent 
RadioCheckBoxes::NewEvent( const Event& event )
{
  GUIEvent retEvent; // Defaul NULL
  // Broadcast lost focus events to all, otherwise find which to broadcast to
  if( event.Type == sf::Event::LostFocus )
    for( unsigned int iCheckBox = 0; iCheckBox < fRadioCheckBoxes.size(); iCheckBox++ )
      fRadioCheckBoxes[iCheckBox]->NewEvent( event );
  else if( event.Type == sf::Event::MouseButtonReleased )
    {
      for( unsigned int iCheckBox = 0; iCheckBox < fRadioCheckBoxes.size(); iCheckBox++ )
	{
	  // Change the state of the clicked box and turn off any others that are on
	  if( fRadioCheckBoxes[iCheckBox]->ContainsPoint( event.GetPos() ) )
	    fRadioCheckBoxes[iCheckBox]->NewEvent( event );
	  else if( fRadioCheckBoxes[iCheckBox]->GetState() )
	    fRadioCheckBoxes[iCheckBox]->NewEvent( event );
	}
      retEvent = GUIEvent( fID, fGlobalID );
    }
  else
      for( unsigned int iCheckBox = 0; iCheckBox < fRadioCheckBoxes.size(); iCheckBox++ )
	if( fRadioCheckBoxes[iCheckBox]->ContainsPoint( event.GetPos() ) )
	    fRadioCheckBoxes[iCheckBox]->NewEvent( event );
  // Make sure one is one
  if( GetState() == 0 )
    fRadioCheckBoxes[0]->SetState( true );
  return retEvent;
}

unsigned int
RadioCheckBoxes::GetState() const
{
  unsigned int state = 0;
  for( unsigned int iCheckBox = 0; iCheckBox < fRadioCheckBoxes.size(); iCheckBox++ )
    if( fRadioCheckBoxes[iCheckBox]->GetState() )
      state = iCheckBox;
  return state;
}
