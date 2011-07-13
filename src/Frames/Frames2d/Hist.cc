
#include <SFML/Graphics.hpp>
#include <Viewer/Hist.hh>
#include <Viewer/ImageManager.hh>
#include <Viewer/ConfigurationTable.hh>
#include <Viewer/ExitButton.hh>
using namespace Viewer;
using namespace Frames;

void Hist::Initialise()
{
  fHistBox = sf::Shape::Rectangle(0.0,0.0,0.5,0.5,sf::Color::Black,1.0f,sf::Color::Black);
  //fHistBox.SetBoundingRect(0.0,0.0,1.0,1.0);
  sf::Rect<double> button( 0.8, 0.1, 0.2, 0.1 );
  fGUIManager.NewGUI<GUIs::ExitButton>(button);
  fMessage = Text( "WTF?" );
  fMessage.SetBoundingRect( sf::Rect<double>( 0.5, 0.0, 0.5, 0.5 ) );
  fMessage.SetColor( sf::Color( 0, 0, 0 ) );
}

void Hist::Initialise(ConfigurationTable& configTable) 
{
  Initialise();
}

void Hist::Render2d(RWWrapper& windowApp){
  windowApp.Draw(fHistBox);
  windowApp.Draw(fMessage);
}

void Hist::Render3d(){
}

void Hist::EventLoop(){
  while(!fEvents.empty()){
    fEvents.pop();
  }
}

void Hist::SaveConfiguration(ConfigurationTable& configTable){
  // I think nothing goes in here...
}

