//C++ includes
#include <iostream>
//ROOT
#include <TMath.h>
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
const double kLocalSize = 137.0*0.3/kPSUPRadius;

void EllipticalProjection::Initialise(){

 fProjectArea = sf::Rect<double>(0.1,0.0,0.8,0.9);
 projFilled = false;
 
}

void EllipticalProjection::SaveConfiguration( ConfigurationTable& configTable ){

}

void EllipticalProjection::EventLoop(){
  while(!fEvents.empty()){
    fEvents.pop();
  }
}

void EllipticalProjection::FillPMTLocations(){

 EventData& tempEvents = EventData::GetInstance();
 RAT::DS::PMTProperties *pmtProps = tempEvents.GetRun()->GetPMTProp();
 projPosVec.resize(pmtProps->GetPMTCount());
 for(int ipmt=0;ipmt<pmtProps->GetPMTCount();ipmt++){
   //if (!pmtProps->GetIsInvalid(ipmt)){
   if (pmtProps->GetIsNormal(ipmt)){
       projPosVec[ipmt]=Projection(pmtProps->GetPos(ipmt));
   }
 }
 projFilled = true;
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
 
  Rect projection;
  projection.SetFromLocalRect(fProjectArea,fFrameRect);
  fImage.Clear(projection);

  if (!projFilled) FillPMTLocations();

  EventData& events = EventData::GetInstance();
  RAT::DS::EV* rEV = events.GetCurrentEV();
  RAT::DS::PMTProperties* rPMTList = events.GetRun()->GetPMTProp();
  for( int ipmt=0;ipmt<rPMTList->GetPMTCount();ipmt++){
    //const sf::Vector2<double> projPos = Projection(rPMTList->GetPos(ipmt));
    //printf("PMT %i has X position %0.2f\n",rEV->GetPMTCal(ipmt)->GetID(),(projPosVec.at(rEV->GetPMTCal(ipmt)->GetID())).x);
    fImage.DrawHollowSquare(projPosVec.at(ipmt),sf::Vector2<double>(kLocalSize,kLocalSize),ColourPalette::gPalette->GetPrimaryColour(eGrey));
  }
  for(int ipmt=0;ipmt<rEV->GetPMTCalCount();ipmt++){
    //const sf::Vector2<double> projPos = Projection(rPMTList->GetPos(rEV->GetPMTCal(ipmt)->GetID()));
    double pmtHitTime = rEV->GetPMTCal(ipmt)->GetTime();
    fImage.DrawSquare(projPosVec.at(rEV->GetPMTCal(ipmt)->GetID()),sf::Vector2<double>(kLocalSize,kLocalSize),ColourPalette::gPalette->GetColour((500.0-pmtHitTime)/250.0));
  }
  windowApp.Draw(fImage);
}
