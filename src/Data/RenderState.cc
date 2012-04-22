using namespace std;

#include <Viewer/RenderState.hh>
using namespace Viewer;

std::map< RenderState::EDataSource, std::string > RenderState::fsSourceNames;
std::map< RenderState::EDataType, std::string > RenderState::fsTypeNames;
std::map< RenderState::EDataSource, std::map< RenderState::EDataType, double > > RenderState::fsDefaultScalingMin;
std::map< RenderState::EDataSource, std::map< RenderState::EDataType, double > > RenderState::fsDefaultScalingMax;

void
RenderState::Initialise()
{
  fsTypeNames[eTAC] = string("TAC");
  fsTypeNames[eQHL] = string("QHL");
  fsTypeNames[eQHS] = string("QHS");
  fsTypeNames[eQLX] = string("QLX");
  fsSourceNames[eMC] = string("MC");
  fsSourceNames[eTruth] = string("Truth");
  fsSourceNames[eUnCal] = string("UnCal");
  fsSourceNames[eCal] = string("Cal");
  fsSourceNames[eScript] = string("Script");

  fsDefaultScalingMin[eUnCal][eTAC] = 0.0;
  fsDefaultScalingMin[eUnCal][eQHL] = 0.0;
  fsDefaultScalingMin[eUnCal][eQHS] = 0.0;
  fsDefaultScalingMin[eUnCal][eQLX] = 0.0;

  fsDefaultScalingMax[eUnCal][eTAC] = 4000.0;
  fsDefaultScalingMax[eUnCal][eQHL] = 4500.0;
  fsDefaultScalingMax[eUnCal][eQHS] = 4500.0;
  fsDefaultScalingMax[eUnCal][eQLX] = 1400.0;

  fsDefaultScalingMin[eCal][eTAC] = 0.0;
  fsDefaultScalingMin[eCal][eQHL] = 0.0;
  fsDefaultScalingMin[eCal][eQHS] = 0.0;
  fsDefaultScalingMin[eCal][eQLX] = 0.0;

  fsDefaultScalingMax[eCal][eTAC] = 500.0;
  fsDefaultScalingMax[eCal][eQHL] = 4000.0;
  fsDefaultScalingMax[eCal][eQHS] = 4000.0;
  fsDefaultScalingMax[eCal][eQLX] = 1000.0;

  fsDefaultScalingMin[eScript][eTAC] = 0.0;
  fsDefaultScalingMin[eScript][eQHL] = 0.0;
  fsDefaultScalingMin[eScript][eQHS] = 0.0;
  fsDefaultScalingMin[eScript][eQLX] = 0.0;

  fsDefaultScalingMax[eScript][eTAC] = 500.0;
  fsDefaultScalingMax[eScript][eQHL] = 500.0;
  fsDefaultScalingMax[eScript][eQHS] = 500.0;
  fsDefaultScalingMax[eScript][eQLX] = 500.0;
}

void
RenderState::ChangeState( EDataSource source,
			  EDataType type )
{
  fCurrentDataSource = source;
  fCurrentDataType = type;
  fCurrentScalingMin = fsDefaultScalingMin[source][type];
  fCurrentScalingMax = fsDefaultScalingMax[source][type];
}

void 
RenderState::ChangeScaling( double fractionalMin,
			    double fractionalMax )
{
  fCurrentScalingMin = fractionalMin * ( fsDefaultScalingMax[fCurrentDataSource][fCurrentDataType] - fsDefaultScalingMin[fCurrentDataSource][fCurrentDataType] );
  fCurrentScalingMax = fractionalMax * ( fsDefaultScalingMax[fCurrentDataSource][fCurrentDataType] - fsDefaultScalingMin[fCurrentDataSource][fCurrentDataType] );
}

vector<string>
RenderState::GetSourceStrings()
{
  vector<string> strings;
  for( map< EDataSource, string>::iterator iTer = fsSourceNames.begin(); iTer != fsSourceNames.end(); iTer++ )
    strings.push_back( iTer->second );
  return strings;
}

vector<string>
RenderState::GetTypeStrings()
{
  vector<string> strings;
  for( map< EDataType, string>::iterator iTer = fsTypeNames.begin(); iTer != fsTypeNames.end(); iTer++ )
    strings.push_back( iTer->second );
  return strings;
}
