//C++ includes
#include <iostream>
//RAT includes
#include <RAT/DS/Root.hh>
#include <RAT/DS/EV.hh>
//SFML includes
#include <SFML/Graphics.hpp>
//Viewer includes
#include <Viewer/CrateView.hh>
#include <Viewer/ConfigurationTable.hh>
#include <Viewer/EventData.hh>
#include <Viewer/ColourPalette.hh>
#include <Viewer/TimeAxis.hh>
#include <Viewer/MapArea.hh>

using namespace Viewer;
using namespace Viewer::Frames;
using namespace std;

const double kLocalSize = 1.0;

void CrateView::Initialise() {
  fProjectArea = sf::Rect<double>(0.1,0.0,0.8,0.9);
  fMapArea = fGUIManager.NewGUI<GUIs::MapArea>( fProjectArea );
  fInfoText.SetBoundingRect( sf::Rect<double>( 0.0, 0.9, 1.0, 0.1 ) );
  fInfoText.SetColor( ColourPalette::gPalette->GetPrimaryColour( eBlack ) );
}

void CrateView::Render2d(RWWrapper& windowApp){

  Rect projection;
  projection.SetFromLocalRect(fProjectArea,fFrameRect);
  fImage.Clear(projection);
  sf::Vector2<double> mapPosition = fMapArea->GetPosition();
  Double_t crateWidth = 0.09;
  Double_t crateHeight = 0.42;
  Double_t hitWidth = crateWidth/18;
  Double_t hitHeight = crateHeight/32;

  //set up the positions of all the crates
  //they are 0.08 wide by 0.4 high
  Double_t xPos,yPos;
  for (Int_t row=0;row<2;row++){
    yPos = hitHeight+(row*(crateHeight+hitHeight));
    for (Int_t column=0;column<10;column++){
      xPos = hitWidth+(column*(crateWidth+hitWidth));
      fImage.DrawHollowSquare(sf::Vector2<double>(xPos,yPos),sf::Vector2<double>(crateWidth,crateHeight),ColourPalette::gPalette->GetPrimaryColour(eGrey));
    }
  }
  
  EventData& events = EventData::GetInstance();
  RAT::DS::EV* rEV = events.GetCurrentEV();
  RAT::DS::PMTProperties* rPMTList = events.GetRun()->GetPMTProp();
  stringstream infoText;
  //printf("finished with empty pmts\n");
  for(int ipmt=0;ipmt<rEV->GetPMTCalCount();ipmt++){
    double pmtHitTime = rEV->GetPMTCal(ipmt)->GetTime();
    int ccc = rEV->GetPMTCal(ipmt)->GetID();
    int crate = int(ccc/512);
    int card = int((ccc-(512*crate))/32);
    int channel = ccc-(crate*512)-(card*32);
    
    double pmtX = hitWidth+(crate%10)*(crateWidth+hitWidth)+card*hitWidth;
    double pmtY = int(crate/10)*(crateHeight+hitHeight)+(crateHeight-channel*hitHeight+0.005);
    //if (crate==9){
    //printf("Crate: %i Card: %i Channel: %i\n",crate,card,channel);  
    //printf("pmtX: %0.4f pmtY: %0.4f\n",pmtX,pmtY);
      fImage.DrawSquare(sf::Vector2<double>(pmtX,pmtY),sf::Vector2<double>(hitHeight,hitWidth),ColourPalette::gPalette->GetColour(TimeAxis::ScaleTime(pmtHitTime)));
      const double distToMouse2 = pow(pmtX-mapPosition.x,2)+pow(pmtY-mapPosition.y,2);
      //if(distToMouse2 < kLocalSize * kLocalSize )
	//infoText << rEV->GetPMTCal(ipmt)->GetID() << " Time: " << rEV->GetPMTCal(ipmt)->GetTime() << " Charge: " << rEV->GetPMTCal(ipmt)->GetCharge() << endl;
      //}
  }
  fInfoText.SetString(infoText.str());
  windowApp.Draw(fInfoText);
  windowApp.Draw(&fImage);

}

void CrateView::Render3d(){
}

void CrateView::EventLoop(){
  while(!fEvents.empty()){
    fEvents.pop();
  }
}

void CrateView::SaveConfiguration(ConfigurationTable& configTable){
  // I think nothing goes in here...
}

