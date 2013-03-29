#include <limits>
using namespace std;

#include <Viewer/RIDS/Type.hh>
using namespace Viewer::RIDS;

Type::Type()
{
  fMin = numeric_limits<double>::max();
  fMax = numeric_limits<double>::min();
}

void 
Type::AddChannel( int id, double data ) 
{ 
  fData.push_back( Channel( id, data ) ); 
  if( data > fMax ) fMax = data;
  else if( data < fMin ) fMin = data;
}
