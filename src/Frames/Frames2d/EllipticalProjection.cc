//C++ includes
#include <iostream>
//RAT includes
#include <RAT/DS/Root.hh>
#include <RAT/DS/EV.hh>
//SFML includes
#include <SFML/Graphics.hpp>
//Viewer includes
#include <Viewer/EllipticalProjection.hh>
#include <Viewer/ConfigurationTable.hh>
#include <Viewer/EventData.hh>
#include <Viewer/ColourPalette.hh>

using namespace Viewer;
using namespace Viewer::Frames;
using namespace std;

const double kPSUPRadius = 8500.0;

void EllipticalProjection::Initialise(){

  fFilledPMT = sf::Shape::Circle(0.0,0.0,0.5,sf::Color(255,255,255));
  //fFilledPMT.SetBoundingRect( sf::Rect<double>( 0.0, 0.0, 137.0 * 0.5 / kPSUPRadius * fProjectArea.Width, 137.0 * 0.5 / kPSUPRadius * fProjectArea.Height ) );
  fFilledPMT.EnableFill(true);

  fOpenPMT= sf::Shape::Circle(0.0,0.0,0.5,sf::Color(255,255,255),0.5,sf::Color(255,255,255));
  //fOpenPMT.SetBoundingRect( sf::Rect<double>( 0.0, 0.0, 100.0 * 0.5 / kPSUPRadius * fProjectArea.Width, 100.0 * 0.5 / kPSUPRadius * fProjectArea.Height ) );
  fOpenPMT.EnableFill(false);
  fOpenPMT.EnableOutline(true);
  fOpenPMT.SetOutlineThickness(0.5);
}

void EllipticalProjection::SaveConfiguration( ConfigurationTable& configTable ){

}

void EllipticalProjection::EventLoop(){
  while(!fEvents.empty()){
    fEvents.pop();
  }
}

sf::Vector2<double> EllipticalProjection::Projection(TVector3 pmtPos){
  double pi = 3.141592653589793;
  pmtPos = pmtPos.Unit();
  //printf("PMT Coords: (%0.3f,%0.3f,%0.3f)\n",pmtPos.Mag(),pmtPos.Theta(),pmtPos.Phi());
  //solve for newTheta using
  //2*newTheta + sin(2*newTheta) = Pi*sin(phi)
  //printf("Theta: %0.4f\n",pmtPos.Theta());
  //pmtPos.RotateZ(TMath::Pi()/2);
  double newTheta = pmtPos.Phi();
  int loop_ct=0;
  //if (fabs(newTheta)<(3.14/2.0) || fabs(newTheta)>(3.142/2.0)){
    double target = pi*sin(pmtPos.Phi());
    double ans = 1e9;
    while (fabs(target-ans)>1e-2){
      newTheta -= (2.0*newTheta+sin(2.0*newTheta)-pi*sin(pmtPos.Phi()))/(2.0+2.0*cos(2.0*newTheta));
      ans = 2.0*newTheta + sin(2.0*newTheta);
      //printf("newTheta: %0.2f  ans: %0.2f  target: %0.2f loop: %i\n",newTheta,ans,target,loop_ct);
      loop_ct++;
      if (loop_ct>1e4) break;
      //}
  }
  //if (newTheta>TMath::Pi()/2) printf("Found one here!\n");
  double newX,newY;
  /*
  if (pmtPos.Theta()>pi/2.0) newX = 0.5+0.16*(((2.0*sqrt(2.0))/pi)*pmtPos.Theta()*TMath::Cos(newTheta));
  else newX = 0.5-0.16*(((2.0*sqrt(2.0))/pi)*pmtPos.Theta()*TMath::Cos(newTheta));
  */
  double resizeFactor = 0.16;
  newX = 0.5+resizeFactor*(((2.0*sqrt(2.0))/pi)*pmtPos.Theta()*TMath::Cos(newTheta));
  //  if (pmtPos.Phi()<(-1.0*pi/2.0) || pmtPos.Phi()>(pi/2.0)) newX+=pi/2.0;
  if (pmtPos.Phi()<(-1.0*pi/2.0) || pmtPos.Phi()>(pi/2.0))  newX = 0.5+resizeFactor*(((2.0*sqrt(2.0))/pi)*pmtPos.Theta()*TMath::Cos(newTheta));
  else  newX = 0.5-resizeFactor*(((2.0*sqrt(2.0))/pi)*pmtPos.Theta()*TMath::Cos(newTheta));
  newY = 0.5+resizeFactor*(sqrt(2.0)*TMath::Sin(newTheta));
  sf::Vector2<double> transformPos(newX,newY);
  //printf("Returned position (%0.2f,%0.2f)\n",newX,newY);
  return transformPos;
}

void EllipticalProjection::Render2d( RWWrapper& windowApp ){
 
  EventData& events = EventData::GetInstance();
  RAT::DS::EV* rEV = events.GetCurrentEV();
  RAT::DS::PMTProperties* rPMTList = events.GetRun()->GetPMTProp();
  //printf("There are %i PMTs\n",rPMTList->GetCorrPMTsNumber());
  for( int ipmt=0;ipmt<rPMTList->GetCorrPMTsNumber();ipmt++){
    //printf("Trying to transform PMT %i\n",ipmt);
    const sf::Vector2<double> projPos = Projection(rPMTList->GetPos(ipmt));
    fOpenPMT.SetPosition(projPos);
    //fOpenPMT.SetColor(ColourPalette::gPalette->GetPrimaryColour(eGrey));
    fOpenPMT.SetColor(sf::Color(220,220,220,255));
    windowApp.Draw(fOpenPMT);
  }
  for(int ipmt=0;ipmt<rEV->GetPMTCalCount();ipmt++){
    const sf::Vector2<double> projPos = Projection(rEV->GetPMTCal(ipmt)->GetPos(rPMTList));
    fFilledPMT.SetPosition(projPos);
    double pmtHitTime = rEV->GetPMTCal(ipmt)->GetTime();
    if(pmtHitTime<250.0)
      fFilledPMT.SetColor(ColourPalette::gPalette->GetPrimaryColour(eWhite));
    else
      fFilledPMT.SetColor(ColourPalette::gPalette->GetColour((500.0-pmtHitTime)/250.0));
    windowApp.Draw(fFilledPMT);
  }
}
