#include <SFML/Graphics.hpp>

#include <sstream>
#include <string>
using namespace std;

#include <Viewer/ColourPicker.hh>
#include <Viewer/CheckBoxLabel.hh>
#include <Viewer/ColourPaletteFactory.hh>
#include <Viewer/GUIColourPaletteFactory.hh>
#include <Viewer/ColourPalette.hh>
#include <Viewer/GUIColourPalette.hh>
#include <Viewer/ViewerWindow.hh>
#include <Viewer/GUIImageManager.hh>
using namespace Viewer;
using namespace Frames;

void 
ColourPicker::Initialise()
{
  fColourNames = ViewerWindow::gColourPaletteFactory.GetNames();
  const double height = 0.5 / ( (double)fColourNames.size() );
  for( vector<string>::iterator iTer = fColourNames.begin(); iTer != fColourNames.end(); iTer++ )
    {
      double offset = iTer - fColourNames.begin();
      sf::Rect<double> pos( 0.0, height * offset, 0.5, height );
      GUIs::CheckBoxLabel* checkBox = fGUIManager.NewGUI<GUIs::CheckBoxLabel>( pos );
      checkBox->SetLabel( *iTer );
      fColourBoxes.push_back( checkBox );
      if( ColourPalette::gPalette->GetName() == *iTer )
	checkBox->SetState( true );
    }
  // Now GUI Colours
  fGUIColourNames = ViewerWindow::gGUIColourPaletteFactory.GetNames();
  for( vector<string>::iterator iTer = fGUIColourNames.begin(); iTer != fGUIColourNames.end(); iTer++ )
    {
      double offset = iTer - fGUIColourNames.begin();
      sf::Rect<double> pos( 0.5, height * offset, 0.5, height );
      GUIs::CheckBoxLabel* checkBox = fGUIManager.NewGUI<GUIs::CheckBoxLabel>( pos );
      checkBox->SetLabel( *iTer );
      fGUIColourBoxes.push_back( checkBox );
      if( GUIColourPalette::gPalette->GetName() == *iTer )
	checkBox->SetState( true );
    }
}

void 
ColourPicker::EventLoop()
{
  while( !fEvents.empty() )
    {
      int guiID = fEvents.front().fguiID;
      if( guiID < fColourBoxes.size() )
	{
	  NewColourPalette( guiID );
	}
      else
	{
	  guiID -= fColourBoxes.size();
	  NewGUIColourPalette( guiID );
	}
      fEvents.pop();
    }
}
void 
ColourPicker::Render2d( RWWrapper& windowApp )
{

}

void
ColourPicker::NewColourPalette( int paletteID )
{
  ColourPalette::gPalette = ViewerWindow::gColourPaletteFactory.New( fColourNames[paletteID] );  
  for( std::vector<GUIs::CheckBoxLabel*>::iterator iTer = fColourBoxes.begin(); iTer != fColourBoxes.end(); iTer++ )
    (*iTer)->SetState( false );
  fColourBoxes[paletteID]->SetState( true );
}

void
ColourPicker::NewGUIColourPalette( int paletteID )
{
  GUIColourPalette::gPalette = ViewerWindow::gGUIColourPaletteFactory.New( fGUIColourNames[paletteID] );
  for( std::vector<GUIs::CheckBoxLabel*>::iterator iTer = fGUIColourBoxes.begin(); iTer != fGUIColourBoxes.end(); iTer++ )
    (*iTer)->SetState( false );
  fGUIColourBoxes[paletteID]->SetState( true );
  GUIImageManager& guiIM = GUIImageManager::GetInstance();
  guiIM.ChangeColourScheme( GUIColourPalette::gPalette );
}
