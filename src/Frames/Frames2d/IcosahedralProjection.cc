//C++ includes
#include <iostream>
//RAT includes
#include <RAT/DS/Root.hh>
#include <RAT/DS/EV.hh>
//SFML includes
#include <SFML/Graphics.hpp>
//Viewer includes
#include <Viewer/IcosahedralProjection.hh>
#include <Viewer/ConfigurationTable.hh>
#include <Viewer/EventData.hh>
#include <Viewer/ColourPalette.hh>

using namespace Viewer;
using namespace Viewer::Frames;
using namespace std;

//const double kLocalSize = 1.0;
const double kPSUPRadius = 8500.0;
const double kLocalSize = 137.0*0.3/kPSUPRadius;

void IcosahedralProjection::Initialise(){
  /*
  //set up shapes for the PMTs (use the convention of open and filled)
  fFilledPMT = sf::Shape::Circle(0,0,2.0,sf::Color(255,255,255));
  fFilledPMT.EnableFill(true);
  fOpenPMT = sf::Shape::Circle(0,0,2.0,sf::Color(255,255,255),0.5,sf::Color(255,255,255));
  fOpenPMT.EnableFill(true);
  fOpenPMT.EnableOutline(true);
  fOpenPMT.SetOutlineThickness(0.4);
  */

  fProjectArea = sf::Rect<double>(0.1,0.0,0.8,0.9);
  projFilled = false;

  //set up the geometry for the transformation
  //need to know the vertices
  double phi = (1.0+sqrt(5.0))/2.0;
  vertices_3d.push_back(TVector3(pow(phi,2), 0.0,pow(phi,3)).Unit());//Vertex 2->0
  vertices_3d.push_back(TVector3(-1.0*pow(phi,2), 0.0,pow(phi,3)).Unit());//Vertex 6->1
  vertices_3d.push_back(TVector3(0.0,pow(phi,3),pow(phi,2)).Unit());//Vertex 12->2
  vertices_3d.push_back(TVector3(0.0,-1.0*pow(phi,3),pow(phi,2)).Unit());//Vertex 17->3
  vertices_3d.push_back(TVector3(pow(phi,3),pow(phi,2),0.0).Unit());//Vertex 27->4
  vertices_3d.push_back(TVector3(-1.0*pow(phi,3),pow(phi,2),0.0).Unit());//Vertex 31->5
  vertices_3d.push_back(TVector3(-1.0*pow(phi,3),-1.0*pow(phi,2),0.0).Unit());//Vertex 33->6
  vertices_3d.push_back(TVector3(pow(phi,3),-1.0*pow(phi,2),0.0).Unit());//Vertex 37->7
  vertices_3d.push_back(TVector3(0.0,pow(phi,3),-1.0*pow(phi,2)).Unit());//Vertex 46->8
  vertices_3d.push_back(TVector3(0.0,-1.0*pow(phi,3),-1.0*pow(phi,2)).Unit());//Vertex 51->9
  vertices_3d.push_back(TVector3(pow(phi,2),0.0,-1.0*pow(phi,3)).Unit());//Vertex 54->10
  vertices_3d.push_back(TVector3(-1.0*pow(phi,2),0.0,-1.0*pow(phi,3)).Unit());//Vertex 58->11
  //Faces are made up of vertices as follows
  //{{2, 6,17},{2,12, 6},{2,17,37},{2,37,27},{2,27,12},{37,54,27}, {27, 54, 46}, {27, 46, 12}, {12, 46, 31}, {12, 31, 6}, { 6, 31, 33}, { 6, 33, 17}, {17, 33, 51}, {17, 51, 37}, {37, 51, 54}, {58, 54, 51}, {58, 46, 54}, {58, 31, 46}, {58, 33, 31}, {58, 51, 33}}
  //Need to know the centres of these faces
  vertex_centres.push_back((vertices_3d.at(0)+vertices_3d.at(1)+vertices_3d.at(3))*(1.0/3.0));//{2, 6,17}
  vertex_centres.push_back((vertices_3d.at(0)+vertices_3d.at(2)+vertices_3d.at(1))*(1.0/3.0));//{2,12, 6}
  vertex_centres.push_back((vertices_3d.at(0)+vertices_3d.at(3)+vertices_3d.at(7))*(1.0/3.0));//{2,17,37}
  vertex_centres.push_back((vertices_3d.at(0)+vertices_3d.at(7)+vertices_3d.at(4))*(1.0/3.0));//{2,37,27}
  vertex_centres.push_back((vertices_3d.at(0)+vertices_3d.at(4)+vertices_3d.at(2))*(1.0/3.0));//{2,27,12}
  vertex_centres.push_back((vertices_3d.at(7)+vertices_3d.at(10)+vertices_3d.at(4))*(1.0/3.0));//{37,54,27}
  vertex_centres.push_back((vertices_3d.at(4)+vertices_3d.at(10)+vertices_3d.at(8))*(1.0/3.0));//{27, 54, 46}
  vertex_centres.push_back((vertices_3d.at(4)+vertices_3d.at(8)+vertices_3d.at(2))*(1.0/3.0));//{27, 46, 12}
  vertex_centres.push_back((vertices_3d.at(2)+vertices_3d.at(8)+vertices_3d.at(5))*(1.0/3.0));//{12, 46, 31}
  vertex_centres.push_back((vertices_3d.at(2)+vertices_3d.at(5)+vertices_3d.at(1))*(1.0/3.0));//{12, 31, 6}
  vertex_centres.push_back((vertices_3d.at(1)+vertices_3d.at(5)+vertices_3d.at(6))*(1.0/3.0));//{6, 31, 33}
  vertex_centres.push_back((vertices_3d.at(1)+vertices_3d.at(6)+vertices_3d.at(3))*(1.0/3.0));//{6, 33, 17}
  vertex_centres.push_back((vertices_3d.at(3)+vertices_3d.at(6)+vertices_3d.at(9))*(1.0/3.0));//{17, 33, 51}
  vertex_centres.push_back((vertices_3d.at(3)+vertices_3d.at(9)+vertices_3d.at(7))*(1.0/3.0));//{17, 51, 37}
  vertex_centres.push_back((vertices_3d.at(7)+vertices_3d.at(9)+vertices_3d.at(10))*(1.0/3.0));//{37, 51, 54}
  vertex_centres.push_back((vertices_3d.at(11)+vertices_3d.at(10)+vertices_3d.at(9))*(1.0/3.0));//{58, 54, 51}
  vertex_centres.push_back((vertices_3d.at(11)+vertices_3d.at(8)+vertices_3d.at(10))*(1.0/3.0));//{58, 46, 54}
  vertex_centres.push_back((vertices_3d.at(11)+vertices_3d.at(5)+vertices_3d.at(8))*(1.0/3.0));//{58, 31, 46}
  vertex_centres.push_back((vertices_3d.at(11)+vertices_3d.at(6)+vertices_3d.at(5))*(1.0/3.0));//{58, 33, 31}
  vertex_centres.push_back((vertices_3d.at(11)+vertices_3d.at(9)+vertices_3d.at(6))*(1.0/3.0));//{58, 51, 33}
  //now need to know the 2d coordinates of the vertices
  //BEWARE!!! Because of "wrapping", there are more 2d vertices than 3d vertices
  //ALSO BEWARE!! These are in SFML coordinates in which (0,0) is the top left corner
  //x increases to the right, y increases *DOWN*.
  //There are 5.5 edge lengths across the x dimension (edge length = 2(phi^2))
  //There are 3 heights across the y dimension (height = sqrt(3)*phi^2)
  double edge_length = 2.0*pow(phi,2);
  double edge_height = sqrt(3)*pow(phi,2);
  double total_length = 5.5*edge_length;
  double total_height = 3.0*edge_height;
  vertices_2d.push_back(TVector2(edge_length/total_length,0.0));//2a
  vertices_2d.push_back(TVector2(2.0*edge_length/total_length,0.0));//2b
  vertices_2d.push_back(TVector2(3.0*edge_length/total_length,0.0));//2c
  vertices_2d.push_back(TVector2(4.0*edge_length/total_length,0.0));//2d
  vertices_2d.push_back(TVector2(5.0*edge_length/total_length,0.0));//2e
  vertices_2d.push_back(TVector2(0.5*edge_length/total_length,edge_height/total_height));//6a
  vertices_2d.push_back(TVector2(1.5*edge_length/total_length,edge_height/total_height));//17
  vertices_2d.push_back(TVector2(2.5*edge_length/total_length,edge_height/total_height));//37 
  vertices_2d.push_back(TVector2(3.5*edge_length/total_length,edge_height/total_height));//27
  vertices_2d.push_back(TVector2(4.5*edge_length/total_length,edge_height/total_height));//12
  vertices_2d.push_back(TVector2(5.5*edge_length/total_length,edge_height/total_height));//6b
  vertices_2d.push_back(TVector2(0.0,2.0*edge_height/total_height));//31a
  vertices_2d.push_back(TVector2(edge_length/total_length,2.0*edge_height/total_height));//33
  vertices_2d.push_back(TVector2(2.0*edge_length/total_length,2.0*edge_height/total_height));//51
  vertices_2d.push_back(TVector2(3.0*edge_length/total_length,2.0*edge_height/total_height));//54
  vertices_2d.push_back(TVector2(4.0*edge_length/total_length,2.0*edge_height/total_height));//46
  vertices_2d.push_back(TVector2(5.0*edge_length/total_length,2.0*edge_height/total_height));//31b
  vertices_2d.push_back(TVector2(0.5*edge_length/total_length,3.0*edge_height/total_height));//58a
  vertices_2d.push_back(TVector2(1.5*edge_length/total_length,3.0*edge_height/total_height));//58b
  vertices_2d.push_back(TVector2(2.5*edge_length/total_length,3.0*edge_height/total_height));//58c
  vertices_2d.push_back(TVector2(3.5*edge_length/total_length,3.0*edge_height/total_height));//58d
  vertices_2d.push_back(TVector2(4.5*edge_length/total_length,3.0*edge_height/total_height));//58e
}

void IcosahedralProjection::SaveConfiguration(ConfigurationTable& configTable){
  //empty, Phil's work takes care of this
}

void IcosahedralProjection::EventLoop(){
  //just the standard getting event loop
  while(!fEvents.empty() ){
    fEvents.pop();
  }
}

sf::Vector2<double> IcosahedralProjection::Projection(TVector3 pmtPos){
  //this needs some serious additional work for the Icosahedron
  //determine to which face centre this point is closest
  pmtPos.RotateY(3.72);
  std::map<double,int> dotProducts;
  for (UInt_t centreFaces=0;centreFaces<vertex_centres.size();centreFaces++){
    dotProducts.insert(std::pair<double,int>(vertex_centres.at(centreFaces).Dot(pmtPos),centreFaces));
  }
  int intersectFace = dotProducts.begin()->second;
  sf::Vector2<double> newPos;
  switch(intersectFace){
  case 0: newPos = Transform(0,1,3,0,5,6,pmtPos);break;
  case 1: newPos = Transform(0,2,1,4,9,10,pmtPos);break;
  case 2: newPos = Transform(0,3,7,1,6,7,pmtPos);break;
  case 3: newPos = Transform(0,7,4,2,7,8,pmtPos);break;
  case 4: newPos = Transform(0,4,2,3,8,9,pmtPos);break;
  case 5: newPos = Transform(7,10,4,7,14,8,pmtPos);break;
  case 6: newPos = Transform(4,10,8,8,14,15,pmtPos);break;
  case 7: newPos = Transform(4,8,2,8,15,9,pmtPos);break;
  case 8: newPos = Transform(2,8,5,9,15,16,pmtPos);break;
  case 9: newPos = Transform(2,5,1,9,16,10,pmtPos);break;
  case 10: newPos = Transform(1,5,6,5,11,12,pmtPos);break;
  case 11: newPos = Transform(1,6,3,5,12,6,pmtPos);break;
  case 12: newPos = Transform(3,6,9,6,12,13,pmtPos);break;
  case 13: newPos = Transform(3,9,7,6,13,7,pmtPos);break;
  case 14: newPos = Transform(7,9,10,7,13,14,pmtPos);break;
  case 15: newPos = Transform(11,10,9,19,14,13,pmtPos);break;
  case 16: newPos = Transform(11,8,10,20,15,14,pmtPos);break;
  case 17: newPos = Transform(11,5,8,21,16,15,pmtPos);break;
  case 18: newPos = Transform(11,6,5,17,12,11,pmtPos);break;
  case 19: newPos = Transform(11,9,6,18,13,12,pmtPos);break;
  }
  return newPos;
}

sf::Vector2<double> IcosahedralProjection::Transform(int vertex3d_1, int vertex3d_2, int vertex3d_3, int vertex2d_1, int vertex2d_2, int vertex2d_3, TVector3 pmtPos){
  //now need to multiply the PMT position vector by the matrix made up of
  //the vertices to get the barycentric coordinates of the point
  Double_t origMatrix[3][3], invMatrix[3][3];
  Double_t detOrigMatrix;
  //set up the original matrix
  origMatrix[0][0]=-1.0*pmtPos.X();
  origMatrix[1][0]=-1.0*pmtPos.Y();
  origMatrix[2][0]=-1.0*pmtPos.Z();
  origMatrix[0][1]=vertices_3d.at(vertex3d_2).X()-vertices_3d.at(vertex3d_1).X();
  origMatrix[1][1]=vertices_3d.at(vertex3d_2).Y()-vertices_3d.at(vertex3d_1).Y();
  origMatrix[2][1]=vertices_3d.at(vertex3d_2).Z()-vertices_3d.at(vertex3d_1).Z();
  origMatrix[0][2]=vertices_3d.at(vertex3d_3).X()-vertices_3d.at(vertex3d_1).X();
  origMatrix[1][2]=vertices_3d.at(vertex3d_3).Y()-vertices_3d.at(vertex3d_1).Y();
  origMatrix[2][2]=vertices_3d.at(vertex3d_3).Z()-vertices_3d.at(vertex3d_1).Z();
  //find the determinant
  detOrigMatrix = origMatrix[0][0]*(origMatrix[1][1]*origMatrix[2][2]-origMatrix[1][2]*origMatrix[2][1]) - origMatrix[0][1]*(origMatrix[1][0]*origMatrix[2][2]-origMatrix[1][2]*origMatrix[2][0]) + origMatrix[0][2]*(origMatrix[1][0]*origMatrix[2][1]-origMatrix[1][1]*origMatrix[2][0]);
  //invert the matrix
  invMatrix[0][0] = 1.0/detOrigMatrix*((origMatrix[1][1]*origMatrix[2][2])-(origMatrix[2][1]*origMatrix[1][2]));
 invMatrix[1][0] = 1.0/detOrigMatrix*((origMatrix[1][2]*origMatrix[2][0])-(origMatrix[2][2]*origMatrix[1][0]));
 invMatrix[2][0] = 1.0/detOrigMatrix*((origMatrix[1][0]*origMatrix[2][1])-(origMatrix[2][0]*origMatrix[1][1]));
  invMatrix[0][1] = 1.0/detOrigMatrix*((origMatrix[0][2]*origMatrix[2][1])-(origMatrix[2][2]*origMatrix[0][1]));
 invMatrix[1][1] = 1.0/detOrigMatrix*((origMatrix[0][0]*origMatrix[2][2])-(origMatrix[2][0]*origMatrix[0][2]));
 invMatrix[2][1] = 1.0/detOrigMatrix*((origMatrix[0][1]*origMatrix[2][0])-(origMatrix[2][1]*origMatrix[0][0]));
  invMatrix[0][2] = 1.0/detOrigMatrix*((origMatrix[0][1]*origMatrix[1][2])-(origMatrix[1][1]*origMatrix[0][2]));
 invMatrix[1][2] = 1.0/detOrigMatrix*((origMatrix[0][2]*origMatrix[1][0])-(origMatrix[1][2]*origMatrix[0][0]));
 invMatrix[2][2] = 1.0/detOrigMatrix*((origMatrix[0][0]*origMatrix[1][1])-(origMatrix[1][0]*origMatrix[0][1]));
 //using this we can get out the length of the PMT location vector to the intercept (l)
 //and the relative coordinates of the intercept using the lines:
 double t = (invMatrix[0][0]*(vertices_3d.at(vertex3d_1).X()) + invMatrix[0][1]*(vertices_3d.at(vertex3d_1).Y()) + invMatrix[0][2]*(vertices_3d.at(vertex3d_1).Z()));
 double u = -1.0*(invMatrix[1][0]*(vertices_3d.at(vertex3d_1).X()) + invMatrix[1][1]*(vertices_3d.at(vertex3d_1).Y()) + invMatrix[1][2]*(vertices_3d.at(vertex3d_1).Z()));
 double v = -1.0*(invMatrix[2][0]*(vertices_3d.at(vertex3d_1).X()) + invMatrix[2][1]*(vertices_3d.at(vertex3d_1).Y()) + invMatrix[2][2]*(vertices_3d.at(vertex3d_1).Z()));
 // if (u<0 || v<0) printf("********* Calculated t: %0.2f u: %0.2f, v:%0.2f\n",t,u,v);
 //Use these to find the 2d coordinates
 TVector2 new2d = vertices_2d.at(vertex2d_1)+u*(vertices_2d.at(vertex2d_2)-vertices_2d.at(vertex2d_1))+v*(vertices_2d.at(vertex2d_3)-vertices_2d.at(vertex2d_1));
 double newX = new2d.X();
 double newY = new2d.Y();
 //finally make the transformed vector
 sf::Vector2<double> transformPos(newX,newY);
 return transformPos;
}

void IcosahedralProjection::FillPMTLocations(){

 EventData& tempEvents = EventData::GetInstance();
 RAT::DS::PMTProperties *pmtProps = tempEvents.GetRun()->GetPMTProp();
 projPosVec.resize(pmtProps->GetPMTCount());
 for(int ipmt=0;ipmt<pmtProps->GetPMTCount();ipmt++){
   projPosVec[ipmt]=Projection(pmtProps->GetPos(ipmt));
 }
 projFilled = true;
}

void IcosahedralProjection::Render2d(RWWrapper& windowApp){

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
    //printf("drawing pmt %i\n",ipmt);
    fImage.DrawHollowSquare(projPosVec.at(ipmt),sf::Vector2<double>(kLocalSize,kLocalSize),ColourPalette::gPalette->GetPrimaryColour(eGrey));
  }
  //printf("finished with empty pmts\n");
  for(int ipmt=0;ipmt<rEV->GetPMTCalCount();ipmt++){
    //const sf::Vector2<double> projPos = Projection(rPMTList->GetPos(rEV->GetPMTCal(ipmt)->GetID()));
    double pmtHitTime = rEV->GetPMTCal(ipmt)->GetTime();
    fImage.DrawSquare(projPosVec.at(rEV->GetPMTCal(ipmt)->GetID()),sf::Vector2<double>(kLocalSize,kLocalSize),ColourPalette::gPalette->GetColour((500.0-pmtHitTime)/250.0));
  }
  windowApp.Draw(fImage);
  /*
  EventData& events = EventData::GetInstance();
  RAT::DS::EV* rEV = events.GetCurrentEV();
  RAT::DS::PMTProperties* rPMTList = events.GetRun()->GetPMTProp();
  for( int ipmt=0;ipmt<rPMTList->GetPMTCount();ipmt++){
    const sf::Vector2<double> projPos = Projection(rPMTList->GetPos(ipmt));
    fOpenPMT.SetPosition(projPos);
    //fOpenPMT.SetColor(ColourPalette::gPalette->GetPrimaryColour(eGrey));
    fOpenPMT.SetColor(sf::Color(220,220,220,255));
    windowApp.Draw(fOpenPMT);
  }
  for(int ipmt=0;ipmt<rEV->GetPMTCalCount();ipmt++){
    const sf::Vector2<double> projPos = Projection(rPMTList->GetPos(rEV->GetPMTCal(ipmt)->GetID()));
    fFilledPMT.SetPosition(projPos);
    double pmtHitTime = rEV->GetPMTCal(ipmt)->GetTime();
    if(pmtHitTime<250.0)
      fFilledPMT.SetColor(ColourPalette::gPalette->GetPrimaryColour(eWhite));
    else
      fFilledPMT.SetColor(ColourPalette::gPalette->GetColour((500.0-pmtHitTime)/250.0));
    windowApp.Draw(fFilledPMT);
  }
  */
}
