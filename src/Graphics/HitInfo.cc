#include <RAT/DS/PMTCal.hh>

#include <SFML/Graphics/Rect.hpp>

#include <string>
using namespace std;

#include <Viewer/Colour.hh>
#include <Viewer/ColourPalette.hh>
#include <Viewer/HitInfo.hh>
#include <Viewer/RWWrapper.hh>
#include <Viewer/GUIColourPalette.hh>
#include <Viewer/Text.hh>
using namespace Viewer;

void 
HitInfo::AddPMT( RAT::DS::PMTCal* rPMTCal )
{
  fInfoStream << "PMT: " << rPMTCal->GetID() << endl;
  fInfoStream << "Time: " << rPMTCal->GetTime() << "ns" << endl;
  fInfoStream << "Charge: " << rPMTCal->GetCharge() << "??" << endl << endl;
}

void 
HitInfo::Render( RWWrapper& windowApp )
{
  Text infoText;
  infoText.SetString( fInfoStream.str() );
  infoText.SetColor( GUIColourPalette::gPalette->GetTextColour( eBase ) );
  infoText.SetBoundingRect( fRect );
  windowApp.Draw( infoText );
  fInfoStream.str("");
}
