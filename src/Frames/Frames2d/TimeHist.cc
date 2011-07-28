//C++ includes
#include <iostream>
//RAT includes
#include <RAT/DS/Root.hh>
#include <RAT/DS/EV.hh>
//SFML includes
#include <SFML/Graphics.hpp>
//Viewer includes
#include <Viewer/TimeHist.hh>
#include <Viewer/ConfigurationTable.hh>
#include <Viewer/EventData.hh>
#include <Viewer/ColourPalette.hh>

using namespace Viewer;
using namespace Viewer::Frames;
using namespace std;

void TimeHist::Initialise()
{
   vertLine = Shape::Line(0.1,0.0,0.1,0.9,0.01f,ColourPalette::gPalette->GetPrimaryColour(eBlack));
  vertLine.SetBoundingRect(sf::Rect<double>(0.0,0.0,1.0,1.0));
  horizLine = Shape::Line(0.1,0.9,1.0,0.9,0.01f,ColourPalette::gPalette->GetPrimaryColour(eBlack));
  horizLine.SetBoundingRect(sf::Rect<double>(0.0,0.0,1.0,1.0));
  horizMarker1 = Shape::Line(0.325,0.87,0.325,0.91,0.007f,ColourPalette::gPalette->GetPrimaryColour(eBlack));
  horizMarker1.SetBoundingRect(sf::Rect<double>(0.0,0.0,1.0,1.0));
  horizMarker2 = Shape::Line(0.55,0.87,0.55,0.91,0.007f,ColourPalette::gPalette->GetPrimaryColour(eBlack));
  horizMarker2.SetBoundingRect(sf::Rect<double>(0.0,0.0,1.0,1.0));
  horizMarker3 = Shape::Line(0.775,0.87,0.775,0.91,0.007f,ColourPalette::gPalette->GetPrimaryColour(eBlack));
  horizMarker3.SetBoundingRect(sf::Rect<double>(0.0,0.0,1.0,1.0));
  horizMarker4 = Shape::Line(1.0,0.87,1.0,0.91,0.007f,ColourPalette::gPalette->GetPrimaryColour(eBlack));
  horizMarker4.SetBoundingRect(sf::Rect<double>(0.0,0.0,1.0,1.0)); 
  horizLabel1 = Text("200");
  horizLabel1.SetColor(ColourPalette::gPalette->GetPrimaryColour(eBlack));
  horizLabel1.SetBoundingRect(sf::Rect<double>(0.275,0.90,0.1,0.08));
  horizLabel2 = Text("300");
  horizLabel2.SetColor(ColourPalette::gPalette->GetPrimaryColour(eBlack));
  horizLabel2.SetBoundingRect(sf::Rect<double>(0.495,0.90,0.1,0.08));
  horizLabel3 = Text("400");
  horizLabel3.SetColor(ColourPalette::gPalette->GetPrimaryColour(eBlack));
  horizLabel3.SetBoundingRect(sf::Rect<double>(0.720,0.90,0.1,0.08));
  horizLabel4 = Text("500");
  horizLabel4.SetColor(ColourPalette::gPalette->GetPrimaryColour(eBlack));
  horizLabel4.SetBoundingRect(sf::Rect<double>(0.940,0.90,0.1,0.08));
  vertLabel1.SetColor(ColourPalette::gPalette->GetPrimaryColour(eBlack));
  vertLabel1.SetBoundingRect(sf::Rect<double>(0.02,0.675,0.05,0.08));
  vertLabel2.SetColor(ColourPalette::gPalette->GetPrimaryColour(eBlack));
  vertLabel2.SetBoundingRect(sf::Rect<double>(0.02,0.450,0.05,0.08));
  vertLabel3.SetColor(ColourPalette::gPalette->GetPrimaryColour(eBlack));
  vertLabel3.SetBoundingRect(sf::Rect<double>(0.02,0.225,0.05,0.08));
  vertLabel4.SetColor(ColourPalette::gPalette->GetPrimaryColour(eBlack));
  vertLabel4.SetBoundingRect(sf::Rect<double>(0.02,0.0,0.05,0.08));
  }

void TimeHist::Render2d(RWWrapper& windowApp){
  //get all the axis-related drawing out of the way
  //except for the vertical axis labels
  windowApp.Draw(vertLine);
  windowApp.Draw(horizLine);
  windowApp.Draw(horizMarker1);
  windowApp.Draw(horizMarker2);
  windowApp.Draw(horizMarker3);
  windowApp.Draw(horizMarker4);
  windowApp.Draw(horizLabel1);
  windowApp.Draw(horizLabel2);
  windowApp.Draw(horizLabel3);
  windowApp.Draw(horizLabel4);
  //set the number of bars up to a maximum of 400
  double numBars = 100.0;
  double barWidth = 0.8/numBars;
  double divisor = 400.0/numBars;
  EventData& events = EventData::GetInstance();
  RAT::DS::EV* rEV = events.GetCurrentEV();
  RAT::DS::PMTProperties* rPMTList = events.GetRun()->GetPMTProp();
  for (int i=0;i<static_cast<int>(numBars);i++) pmtTimes[i]=0;
  for(int ipmt=0;ipmt<rEV->GetPMTCalCount();ipmt++){
    int tempTime = static_cast<int>(rEV->GetPMTCal(ipmt)->GetTime());
    if (tempTime>=100 && tempTime<500) pmtTimes[static_cast<int>(((tempTime)-100)/divisor)]++;
  }
  int maxHeight=0;
  for (int iBar=0;iBar<numBars;iBar++) if(pmtTimes[iBar]>maxHeight) maxHeight=pmtTimes[iBar];
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
    if (pmtTimes[i]!=0){
      histBar.SetBoundingRect(sf::Rect<double>(barWidth,pmtTimes[i]*barHeight,(i+1)*barWidth,0.9));
      histBar.SetPosition(0.1+(i*barWidth),0.9-(pmtTimes[i]*barHeight));
      histBar.SetWidth(1.0);
      histBar.SetHeight(pmtTimes[i]*barHeight);
      histBar.SetColor(ColourPalette::gPalette->GetColour((100.0+static_cast<double>(i)*divisor)/500.0));
      windowApp.Draw(histBar);
    }
  }
}

void TimeHist::Render3d(){
}

void TimeHist::EventLoop(){
  while(!fEvents.empty()){
    fEvents.pop();
  }
}

void TimeHist::SaveConfiguration(ConfigurationTable& configTable){
  // I think nothing goes in here...
}

