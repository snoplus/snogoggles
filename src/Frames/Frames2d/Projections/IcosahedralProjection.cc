#include <cmath>
#include <map>
using namespace std;

#include <Viewer/IcosahedralProjection.hh>
using namespace Viewer;
using namespace Viewer::Frames;

//const double kLocalSize = 1.0;
const double kPSUPRadius = 8500.0;
const double kLocalSize = 137.0*0.3/kPSUPRadius;

IcosahedralProjection::IcosahedralProjection( RectPtr rect ) 
  : ProjectionBase( rect )
{
  //set up the geometry for the transformation
  //need to know the vertices
  double phi = (1.0+sqrt(5.0))/2.0;
  fVertices_3d.push_back(TVector3(pow(phi,2), 0.0,pow(phi,3)).Unit());//Vertex 2->0
  fVertices_3d.push_back(TVector3(-1.0*pow(phi,2), 0.0,pow(phi,3)).Unit());//Vertex 6->1
  fVertices_3d.push_back(TVector3(0.0,pow(phi,3),pow(phi,2)).Unit());//Vertex 12->2
  fVertices_3d.push_back(TVector3(0.0,-1.0*pow(phi,3),pow(phi,2)).Unit());//Vertex 17->3
  fVertices_3d.push_back(TVector3(pow(phi,3),pow(phi,2),0.0).Unit());//Vertex 27->4
  fVertices_3d.push_back(TVector3(-1.0*pow(phi,3),pow(phi,2),0.0).Unit());//Vertex 31->5
  fVertices_3d.push_back(TVector3(-1.0*pow(phi,3),-1.0*pow(phi,2),0.0).Unit());//Vertex 33->6
  fVertices_3d.push_back(TVector3(pow(phi,3),-1.0*pow(phi,2),0.0).Unit());//Vertex 37->7
  fVertices_3d.push_back(TVector3(0.0,pow(phi,3),-1.0*pow(phi,2)).Unit());//Vertex 46->8
  fVertices_3d.push_back(TVector3(0.0,-1.0*pow(phi,3),-1.0*pow(phi,2)).Unit());//Vertex 51->9
  fVertices_3d.push_back(TVector3(pow(phi,2),0.0,-1.0*pow(phi,3)).Unit());//Vertex 54->10
  fVertices_3d.push_back(TVector3(-1.0*pow(phi,2),0.0,-1.0*pow(phi,3)).Unit());//Vertex 58->11
  //Faces are made up of vertices as follows
  //{{2, 6,17},{2,12, 6},{2,17,37},{2,37,27},{2,27,12},{37,54,27}, {27, 54, 46}, {27, 46, 12}, {12, 46, 31}, {12, 31, 6}, { 6, 31, 33}, { 6, 33, 17}, {17, 33, 51}, {17, 51, 37}, {37, 51, 54}, {58, 54, 51}, {58, 46, 54}, {58, 31, 46}, {58, 33, 31}, {58, 51, 33}}
  //Need to know the centres of these faces
  fVertex_centres.push_back((fVertices_3d.at(0)+fVertices_3d.at(1)+fVertices_3d.at(3))*(1.0/3.0));//{2, 6,17}
  fVertex_centres.push_back((fVertices_3d.at(0)+fVertices_3d.at(2)+fVertices_3d.at(1))*(1.0/3.0));//{2,12, 6}
  fVertex_centres.push_back((fVertices_3d.at(0)+fVertices_3d.at(3)+fVertices_3d.at(7))*(1.0/3.0));//{2,17,37}
  fVertex_centres.push_back((fVertices_3d.at(0)+fVertices_3d.at(7)+fVertices_3d.at(4))*(1.0/3.0));//{2,37,27}
  fVertex_centres.push_back((fVertices_3d.at(0)+fVertices_3d.at(4)+fVertices_3d.at(2))*(1.0/3.0));//{2,27,12}
  fVertex_centres.push_back((fVertices_3d.at(7)+fVertices_3d.at(10)+fVertices_3d.at(4))*(1.0/3.0));//{37,54,27}
  fVertex_centres.push_back((fVertices_3d.at(4)+fVertices_3d.at(10)+fVertices_3d.at(8))*(1.0/3.0));//{27, 54, 46}
  fVertex_centres.push_back((fVertices_3d.at(4)+fVertices_3d.at(8)+fVertices_3d.at(2))*(1.0/3.0));//{27, 46, 12}
  fVertex_centres.push_back((fVertices_3d.at(2)+fVertices_3d.at(8)+fVertices_3d.at(5))*(1.0/3.0));//{12, 46, 31}
  fVertex_centres.push_back((fVertices_3d.at(2)+fVertices_3d.at(5)+fVertices_3d.at(1))*(1.0/3.0));//{12, 31, 6}
  fVertex_centres.push_back((fVertices_3d.at(1)+fVertices_3d.at(5)+fVertices_3d.at(6))*(1.0/3.0));//{6, 31, 33}
  fVertex_centres.push_back((fVertices_3d.at(1)+fVertices_3d.at(6)+fVertices_3d.at(3))*(1.0/3.0));//{6, 33, 17}
  fVertex_centres.push_back((fVertices_3d.at(3)+fVertices_3d.at(6)+fVertices_3d.at(9))*(1.0/3.0));//{17, 33, 51}
  fVertex_centres.push_back((fVertices_3d.at(3)+fVertices_3d.at(9)+fVertices_3d.at(7))*(1.0/3.0));//{17, 51, 37}
  fVertex_centres.push_back((fVertices_3d.at(7)+fVertices_3d.at(9)+fVertices_3d.at(10))*(1.0/3.0));//{37, 51, 54}
  fVertex_centres.push_back((fVertices_3d.at(11)+fVertices_3d.at(10)+fVertices_3d.at(9))*(1.0/3.0));//{58, 54, 51}
  fVertex_centres.push_back((fVertices_3d.at(11)+fVertices_3d.at(8)+fVertices_3d.at(10))*(1.0/3.0));//{58, 46, 54}
  fVertex_centres.push_back((fVertices_3d.at(11)+fVertices_3d.at(5)+fVertices_3d.at(8))*(1.0/3.0));//{58, 31, 46}
  fVertex_centres.push_back((fVertices_3d.at(11)+fVertices_3d.at(6)+fVertices_3d.at(5))*(1.0/3.0));//{58, 33, 31}
  fVertex_centres.push_back((fVertices_3d.at(11)+fVertices_3d.at(9)+fVertices_3d.at(6))*(1.0/3.0));//{58, 51, 33}
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
  fVertices_2d.push_back(TVector2(edge_length/total_length,0.0));//2a
  fVertices_2d.push_back(TVector2(2.0*edge_length/total_length,0.0));//2b
  fVertices_2d.push_back(TVector2(3.0*edge_length/total_length,0.0));//2c
  fVertices_2d.push_back(TVector2(4.0*edge_length/total_length,0.0));//2d
  fVertices_2d.push_back(TVector2(5.0*edge_length/total_length,0.0));//2e
  fVertices_2d.push_back(TVector2(0.5*edge_length/total_length,edge_height/total_height));//6a
  fVertices_2d.push_back(TVector2(1.5*edge_length/total_length,edge_height/total_height));//17
  fVertices_2d.push_back(TVector2(2.5*edge_length/total_length,edge_height/total_height));//37 
  fVertices_2d.push_back(TVector2(3.5*edge_length/total_length,edge_height/total_height));//27
  fVertices_2d.push_back(TVector2(4.5*edge_length/total_length,edge_height/total_height));//12
  fVertices_2d.push_back(TVector2(5.5*edge_length/total_length,edge_height/total_height));//6b
  fVertices_2d.push_back(TVector2(0.0,2.0*edge_height/total_height));//31a
  fVertices_2d.push_back(TVector2(edge_length/total_length,2.0*edge_height/total_height));//33
  fVertices_2d.push_back(TVector2(2.0*edge_length/total_length,2.0*edge_height/total_height));//51
  fVertices_2d.push_back(TVector2(3.0*edge_length/total_length,2.0*edge_height/total_height));//54
  fVertices_2d.push_back(TVector2(4.0*edge_length/total_length,2.0*edge_height/total_height));//46
  fVertices_2d.push_back(TVector2(5.0*edge_length/total_length,2.0*edge_height/total_height));//31b
  fVertices_2d.push_back(TVector2(0.5*edge_length/total_length,3.0*edge_height/total_height));//58a
  fVertices_2d.push_back(TVector2(1.5*edge_length/total_length,3.0*edge_height/total_height));//58b
  fVertices_2d.push_back(TVector2(2.5*edge_length/total_length,3.0*edge_height/total_height));//58c
  fVertices_2d.push_back(TVector2(3.5*edge_length/total_length,3.0*edge_height/total_height));//58d
  fVertices_2d.push_back(TVector2(4.5*edge_length/total_length,3.0*edge_height/total_height));//58e
}

sf::Vector2<double> 
IcosahedralProjection::Project( Vector3 pmtIn )
{
  //this needs some serious additional work for the Icosahedron
  //determine to which face centre this point is closest
  TVector3 pmtPos( pmtIn.x, pmtIn.y, pmtIn.z );
  pmtPos.RotateY(3.72);
  std::map<double,int> dotProducts;
  for (UInt_t centreFaces=0;centreFaces<fVertex_centres.size();centreFaces++){
    dotProducts.insert(std::pair<double,int>(fVertex_centres.at(centreFaces).Dot(pmtPos),centreFaces));
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

sf::Vector2<double> 
IcosahedralProjection::Transform( int vertex3d_1, 
				  int vertex3d_2, 
				  int vertex3d_3, 
				  int vertex2d_1, 
				  int vertex2d_2, 
				  int vertex2d_3, 
				  TVector3 pmtPos )
{
  //now need to multiply the PMT position vector by the matrix made up of
  //the vertices to get the barycentric coordinates of the point
  Double_t origMatrix[3][3], invMatrix[3][3];
  Double_t detOrigMatrix;
  //set up the original matrix
  origMatrix[0][0]=-1.0*pmtPos.X();
  origMatrix[1][0]=-1.0*pmtPos.Y();
  origMatrix[2][0]=-1.0*pmtPos.Z();
  origMatrix[0][1]=fVertices_3d.at(vertex3d_2).X()-fVertices_3d.at(vertex3d_1).X();
  origMatrix[1][1]=fVertices_3d.at(vertex3d_2).Y()-fVertices_3d.at(vertex3d_1).Y();
  origMatrix[2][1]=fVertices_3d.at(vertex3d_2).Z()-fVertices_3d.at(vertex3d_1).Z();
  origMatrix[0][2]=fVertices_3d.at(vertex3d_3).X()-fVertices_3d.at(vertex3d_1).X();
  origMatrix[1][2]=fVertices_3d.at(vertex3d_3).Y()-fVertices_3d.at(vertex3d_1).Y();
  origMatrix[2][2]=fVertices_3d.at(vertex3d_3).Z()-fVertices_3d.at(vertex3d_1).Z();
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
 double t = (invMatrix[0][0]*(fVertices_3d.at(vertex3d_1).X()) + invMatrix[0][1]*(fVertices_3d.at(vertex3d_1).Y()) + invMatrix[0][2]*(fVertices_3d.at(vertex3d_1).Z()));
 double u = -1.0*(invMatrix[1][0]*(fVertices_3d.at(vertex3d_1).X()) + invMatrix[1][1]*(fVertices_3d.at(vertex3d_1).Y()) + invMatrix[1][2]*(fVertices_3d.at(vertex3d_1).Z()));
 double v = -1.0*(invMatrix[2][0]*(fVertices_3d.at(vertex3d_1).X()) + invMatrix[2][1]*(fVertices_3d.at(vertex3d_1).Y()) + invMatrix[2][2]*(fVertices_3d.at(vertex3d_1).Z()));
 // if (u<0 || v<0) printf("********* Calculated t: %0.2f u: %0.2f, v:%0.2f\n",t,u,v);
 //Use these to find the 2d coordinates
 TVector2 new2d = fVertices_2d.at(vertex2d_1)+u*(fVertices_2d.at(vertex2d_2)-fVertices_2d.at(vertex2d_1))+v*(fVertices_2d.at(vertex2d_3)-fVertices_2d.at(vertex2d_1));
 double newX = new2d.X();
 double newY = new2d.Y();
 //finally make the transformed vector
 sf::Vector2<double> transformPos(newX,newY);
 return transformPos;
}
