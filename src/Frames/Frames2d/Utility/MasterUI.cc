#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>

#include <vector>
#include <string>
using namespace std;

#include <Viewer/MasterUI.hh>
#include <Viewer/NewFrameButton.hh>
#include <Viewer/FrameFactory.hh>
#include <Viewer/FrameManager.hh>
#include <Viewer/UIEvent.hh>
using namespace Viewer;
using namespace Frames;

MasterUI::MasterUI( FrameManager* manager )
  : fFrameManager( manager )
{
  fCurrentState = eDown;
  fFrameInterest = Frame::eUtil;
  
  fUtilButton = fGUIManager.NewGUI<GUIs::NewFrameButton>( sf::Rect<double>( 0.05, 0.5, 0.1, 0.5 ) );
  fUtilButton->SetTitle( "Utility" );
  f2dButton = fGUIManager.NewGUI<GUIs::NewFrameButton>( sf::Rect<double>( 0.45, 0.5, 0.1, 0.5 ) );
  f2dButton->SetTitle( "2D Frames" );
  f3dButton = fGUIManager.NewGUI<GUIs::NewFrameButton>( sf::Rect<double>( 0.85, 0.5, 0.1, 0.5 ) );
  f3dButton->SetTitle( "3D Frames" );

  FrameFactory frameFactory;
  std::vector<string> frameNames = frameFactory.GetNames();
  for( vector<string>::iterator iTer = frameNames.begin(); iTer != frameNames.end(); iTer++ )
    {
      sf::Rect<double> tempPos( 0.0, 0.0, 0.5, 1.0 );
      GUIs::NewFrameButton* button = fGUIManager.NewGUI<GUIs::NewFrameButton>( tempPos );
      EFrameType type = frameFactory.fTypeMap[*iTer];
      button->SetTitle( *iTer );
      button->SetHidden( true );
      switch( type )
	{
	case Frame::eUtil:
	  fUtilButtons.push_back( button );
	  break;
	case Frame::e2d:
	  f2dButtons.push_back( button );
	  break;
	case Frame::e3d:
	  f3dButtons.push_back( button );
	  break;
	}
      fFrameNameMap[ button->GetGuiID() ] = *iTer;
    }
}

void 
MasterUI::NewEvent( UIEvent& event )
{
  // New Mother rect, thus new UIEvent
  UIEvent uiEvent( event, fFrameRect );
  if( fCurrentState == eUp && event.Type == sf::Event::LostFocus )
    {
      fClock.Reset();
      fCurrentState = eFalling;
    }
  GUIReturn retEvent = fGUIManager.NewEvent( uiEvent );
  if( retEvent.IsNULL() == false )
    fEvents.push( retEvent );
}

void 
MasterUI::EventLoop()
{
  while( !fEvents.empty() )
    {
      GUIReturn event = fEvents.front();
      int guiID = event.fguiID;
      if( event.IsNULL() )
	{
	  fEvents.pop();
	  continue;
	}
      if( guiID == 0 ) //Utility button
	{
	  fCurrentState = eRising;
	  fFrameInterest = Frame::eUtil;
	  fClock.Reset();
	  HideAllButtons();
	}
      else if( guiID == 1 ) //2d button
	{
	  fCurrentState = eRising;
	  fFrameInterest = Frame::e2d;
	  fClock.Reset();
	  HideAllButtons();
	}
      else if( guiID == 2 ) //3d button
	{
	  fCurrentState = eRising;
	  fFrameInterest = Frame::e3d;
	  fClock.Reset();
	  HideAllButtons();
	}
      else
	fFrameManager->NewFrame( fFrameNameMap[guiID] );
      fEvents.pop();
    }
  // Now reposition buttons etc..
  if( fCurrentState == eDown ) // Just Hide buttons and correctly place base buttons
    {
      HideAllButtons();
      fUtilButton->SetRect( sf::Rect<double>( 0.05, 0.5, 0.1, 0.5 ) );
      f2dButton->SetRect( sf::Rect<double>( 0.45, 0.5, 0.1, 0.5 ) );
      f3dButton->SetRect( sf::Rect<double>( 0.85, 0.5, 0.1, 0.5 ) );
    }
  else if( fCurrentState != eUp )
    MoveButtons();
}

void
MasterUI::HideAllButtons()
{
  for( vector<GUIs::NewFrameButton*>::iterator iTer = fUtilButtons.begin(); iTer != fUtilButtons.end(); iTer++ )
    (*iTer)->SetHidden( true );
  for( vector<GUIs::NewFrameButton*>::iterator iTer = f2dButtons.begin(); iTer != f2dButtons.end(); iTer++ )
    (*iTer)->SetHidden( true );
  for( vector<GUIs::NewFrameButton*>::iterator iTer = f3dButtons.begin(); iTer != f3dButtons.end(); iTer++ )
    (*iTer)->SetHidden( true );
}

void
MasterUI::MoveButtons()
{
  double height = 0.0;
  if( fCurrentState == eRising )
    {
      height = 1.0 - 0.5 * fClock.GetElapsedTime() / 1000.0;
      if( height < 0.5 )
	{
	  height = 0.5;
	  fCurrentState = eUp;
	}
    }
  else
    {
      height = 0.5 + 0.5 * fClock.GetElapsedTime() / 1000.0;
      if( height > 1.0 )
	{
	  height = 1.0;
	  fCurrentState = eDown;
	}
    }
  PositionButtons( height );
}

void
MasterUI::PositionButtons( const double height )
{
  const double mainHeight = height - 0.5; // Height of main buttons
  fUtilButton->SetRect( sf::Rect<double>( 0.05, mainHeight, 0.1, 0.5 ) );
  f2dButton->SetRect( sf::Rect<double>( 0.45, mainHeight, 0.1, 0.5 ) );
  f3dButton->SetRect( sf::Rect<double>( 0.85, mainHeight, 0.1, 0.5 ) );
  double buttonCount = 0.0;
  double buttonWidth = 0.0;
  switch( fFrameInterest )
    {
    case eUtil:
      buttonWidth = 0.9 / static_cast<double>( fUtilButtons.size() );
      for( vector<GUIs::NewFrameButton*>::iterator iTer = fUtilButtons.begin(); iTer != fUtilButtons.end(); iTer++ )
	{
	  (*iTer)->SetRect( sf::Rect<double>( 0.05 + buttonCount * buttonWidth, height, buttonWidth, 0.5 ) );
	  (*iTer)->SetHidden( false );
	  buttonCount += 1.0;
	}
      break;
    case e2d:
      buttonWidth = 0.9 / static_cast<double>( f2dButtons.size() );
      for( vector<GUIs::NewFrameButton*>::iterator iTer = f2dButtons.begin(); iTer != f2dButtons.end(); iTer++ )
	{
	  (*iTer)->SetRect( sf::Rect<double>( 0.05 + buttonCount * buttonWidth, height, buttonWidth, 0.5 ) );
	  (*iTer)->SetHidden( false );
	  buttonCount += 1.0;
	}
      break;
    case e3d:
           buttonWidth = 0.9 / static_cast<double>( f3dButtons.size() );
      for( vector<GUIs::NewFrameButton*>::iterator iTer = f3dButtons.begin(); iTer != f3dButtons.end(); iTer++ )
	{
	  (*iTer)->SetRect( sf::Rect<double>( 0.05 + buttonCount * buttonWidth, height, buttonWidth, 0.5 ) );
	  (*iTer)->SetHidden( false );
	  buttonCount += 1.0;
	}
      break;
    }
}
