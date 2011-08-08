//C++ includes
#include <iostream>
//RAT includes
#include <RAT/DS/Root.hh>
#include <RAT/DS/EV.hh>
//SFML includes
#include <SFML/Graphics.hpp>
//Viewer includes
#include <Viewer/ChargeHist.hh>
#include <Viewer/ConfigurationTable.hh>
#include <Viewer/EventData.hh>
#include <Viewer/ColourPalette.hh>

using namespace Viewer;
using namespace Viewer::Frames;
using namespace std;

void ChargeHist::Initialise()
{
   vertLine = Shape::Line(0.1,0.0,0.1,0.9,0.01f,ColourPalette::gPalette->GetPrimaryColour(eGrey));
  vertLine.SetBoundingRect(sf::Rect<double>(0.0,0.0,1.0,1.0));
  horizLine = Shape::Line(0.1,0.9,1.0,0.9,0.01f,ColourPalette::gPalette->GetPrimaryColour(eGrey));
  horizLine.SetBoundingRect(sf::Rect<double>(0.0,0.0,1.0,1.0));
  horizMarker1 = Shape::Line(0.325,0.87,0.325,0.91,0.007f,ColourPalette::gPalette->GetPrimaryColour(eGrey));
  horizMarker1.SetBoundingRect(sf::Rect<double>(0.0,0.0,1.0,1.0));
  horizMarker2 = Shape::Line(0.55,0.87,0.55,0.91,0.007f,ColourPalette::gPalette->GetPrimaryColour(eGrey));
  horizMarker2.SetBoundingRect(sf::Rect<double>(0.0,0.0,1.0,1.0));
  horizMarker3 = Shape::Line(0.775,0.87,0.775,0.91,0.007f,ColourPalette::gPalette->GetPrimaryColour(eGrey));
  horizMarker3.SetBoundingRect(sf::Rect<double>(0.0,0.0,1.0,1.0));
  horizMarker4 = Shape::Line(1.0,0.87,1.0,0.91,0.007f,ColourPalette::gPalette->GetPrimaryColour(eGrey));
  horizMarker4.SetBoundingRect(sf::Rect<double>(0.0,0.0,1.0,1.0)); 
  horizLabel1 = Text("100");
  horizLabel1.SetColor(ColourPalette::gPalette->GetPrimaryColour(eGrey));
  horizLabel1.SetBoundingRect(sf::Rect<double>(0.275,0.90,0.1,0.08));
  horizLabel2 = Text("200");
  horizLabel2.SetColor(ColourPalette::gPalette->GetPrimaryColour(eGrey));
  horizLabel2.SetBoundingRect(sf::Rect<double>(0.495,0.90,0.1,0.08));
  horizLabel3 = Text("300");
  horizLabel3.SetColor(ColourPalette::gPalette->GetPrimaryColour(eGrey));
  horizLabel3.SetBoundingRect(sf::Rect<double>(0.720,0.90,0.1,0.08));
  horizLabel4 = Text("400");
  horizLabel4.SetColor(ColourPalette::gPalette->GetPrimaryColour(eGrey));
  horizLabel4.SetBoundingRect(sf::Rect<double>(0.940,0.90,0.1,0.08));
  //vertMarker1 = Shape::Line(0.05,0.675,0.1,0.675,0.007f,ColourPalette::gPalette->GetPrimaryColour(eGrey));
  //vertMarker1.SetBoundingRect(0.0,0.0,1.0,1.0);
  vertLabel1.SetColor(ColourPalette::gPalette->GetPrimaryColour(eGrey));
  vertLabel1.SetBoundingRect(sf::Rect<double>(0.02,0.675,0.05,0.08));
  vertLabel2.SetColor(ColourPalette::gPalette->GetPrimaryColour(eGrey));
  vertLabel2.SetBoundingRect(sf::Rect<double>(0.02,0.450,0.05,0.08));
  vertLabel3.SetColor(ColourPalette::gPalette->GetPrimaryColour(eGrey));
  vertLabel3.SetBoundingRect(sf::Rect<double>(0.02,0.225,0.05,0.08));
  vertLabel4.SetColor(ColourPalette::gPalette->GetPrimaryColour(eGrey));
  vertLabel4.SetBoundingRect(sf::Rect<double>(0.02,0.0,0.05,0.08));
  }

void ChargeHist::Render2d(RWWrapper& windowApp){
  //get all the axis-related drawing out of the way
  //except for the vertical axis labels
 
  windowApp.Draw(horizMarker1);
  windowApp.Draw(horizMarker2);
  windowApp.Draw(horizMarker3);
  windowApp.Draw(horizMarker4);
  windowApp.Draw(horizLabel1);
  windowApp.Draw(horizLabel2);
  windowApp.Draw(horizLabel3);
  windowApp.Draw(horizLabel4);
  //set the number of bars in the histogram
  //to a maximum of 400
  double numBars = 100.0;
  //maximum charge from a PMT is 400
  double divisor = 400.0/numBars;

  double barWidth = 0.9/numBars;
  EventData& events = EventData::GetInstance();
  RAT::DS::EV* rEV = events.GetCurrentEV();
  RAT::DS::PMTProperties* rPMTList = events.GetRun()->GetPMTProp();
  for (int i=0;i<static_cast<int>(numBars);i++) pmtCharges[i]=0;
  for(int ipmt=0;ipmt<rEV->GetPMTCalCount();ipmt++){
    int tempCharge = static_cast<int>(rEV->GetPMTCal(ipmt)->GetCharge()/divisor);
    if (tempCharge<400) pmtCharges[tempCharge]++;
  }
  int maxHeight=0;
  for (int iBar=0;iBar<numBars;iBar++) if(pmtCharges[iBar]>maxHeight) maxHeight=pmtCharges[iBar];

  double barHeight=0.9/static_cast<double>(maxHeight);
  //now the vertical axis labels can be created and drawn
  stringstream vertLabelA,vertLabelB;
  stringstream vertLabelC,vertLabelD;
  if (maxHeight<=4){
    string singleLabel;
    vertLabelD << static_cast<int>(maxHeight);
    vertLabel4.SetString(vertLabelD.str().c_str());
    windowApp.Draw(vertLabel4);
  }
  else if (maxHeight>40){
    vertLabelA << static_cast<int>(maxHeight/4);
    vertLabel1.SetString(vertLabelA.str().c_str());
    vertLabelB << static_cast<int>(2*maxHeight/4);
    vertLabel2.SetString(vertLabelB.str().c_str());
    vertLabelC << static_cast<int>(3*maxHeight/4);
    vertLabel3.SetString(vertLabelC.str().c_str());
    vertLabelD << static_cast<int>(maxHeight);
    vertLabel4.SetString(vertLabelD.str().c_str());
    windowApp.Draw(vertLabel1);
    windowApp.Draw(vertLabel2);
    windowApp.Draw(vertLabel3);
    windowApp.Draw(vertLabel4);
  }
  histBar = Shape::Rectangle(0.0,0.0,barWidth,1.0,ColourPalette::gPalette->GetPrimaryColour(eGrey));
  //create the individual bars of the histogram
  for (int i=0;i<numBars;i++){
    if (pmtCharges[i]>0){
      histBar.SetPosition(0.1+(i*barWidth),0.9-(pmtCharges[i]*barHeight));
      histBar.SetWidth(1.0);
      histBar.SetHeight(pmtCharges[i]*barHeight);
      windowApp.Draw(histBar);
    }
  }
  windowApp.Draw(vertLine);
  windowApp.Draw(horizLine);
}

void ChargeHist::Render3d(){
}

void ChargeHist::EventLoop(){
  while(!fEvents.empty()){
    fEvents.pop();
  }
}

void ChargeHist::SaveConfiguration(ConfigurationTable& configTable){
  // I think nothing goes in here...
}

