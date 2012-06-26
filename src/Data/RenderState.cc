using namespace std;

#include <Viewer/RenderState.hh>
using namespace Viewer;

std::map< RIDS::EDataSource, std::string > RenderState::fsSourceNames;
std::map< RIDS::EDataType, std::string > RenderState::fsTypeNames;
std::map< RIDS::EDataSource, std::map< RIDS::EDataType, double > > RenderState::fsDefaultScalingMin;
std::map< RIDS::EDataSource, std::map< RIDS::EDataType, double > > RenderState::fsDefaultScalingMax;

void
RenderState::Initialise()
{
  fsTypeNames[RIDS::eTAC] = string("TAC");
  fsTypeNames[RIDS::eQHL] = string("QHL");
  fsTypeNames[RIDS::eQHS] = string("QHS");
  fsTypeNames[RIDS::eQLX] = string("QLX");
  fsSourceNames[RIDS::eMC] = string("MC");
  fsSourceNames[RIDS::eTruth] = string("Truth");
  fsSourceNames[RIDS::eUnCal] = string("UnCal");
  fsSourceNames[RIDS::eCal] = string("Cal");
  fsSourceNames[RIDS::eScript] = string("Script");

  fsDefaultScalingMin[RIDS::eMC][RIDS::eTAC] = 0.0;
  fsDefaultScalingMin[RIDS::eMC][RIDS::eQHL] = 0.0;

  fsDefaultScalingMax[RIDS::eMC][RIDS::eTAC] = 500.0;
  fsDefaultScalingMax[RIDS::eMC][RIDS::eQHL] = 4500.0;

  fsDefaultScalingMin[RIDS::eUnCal][RIDS::eTAC] = 0.0;
  fsDefaultScalingMin[RIDS::eUnCal][RIDS::eQHL] = 0.0;
  fsDefaultScalingMin[RIDS::eUnCal][RIDS::eQHS] = 0.0;
  fsDefaultScalingMin[RIDS::eUnCal][RIDS::eQLX] = 0.0;

  fsDefaultScalingMax[RIDS::eUnCal][RIDS::eTAC] = 4000.0;
  fsDefaultScalingMax[RIDS::eUnCal][RIDS::eQHL] = 4500.0;
  fsDefaultScalingMax[RIDS::eUnCal][RIDS::eQHS] = 4500.0;
  fsDefaultScalingMax[RIDS::eUnCal][RIDS::eQLX] = 1400.0;

  fsDefaultScalingMin[RIDS::eCal][RIDS::eTAC] = 0.0;
  fsDefaultScalingMin[RIDS::eCal][RIDS::eQHL] = 0.0;
  fsDefaultScalingMin[RIDS::eCal][RIDS::eQHS] = 0.0;
  fsDefaultScalingMin[RIDS::eCal][RIDS::eQLX] = 0.0;

  fsDefaultScalingMax[RIDS::eCal][RIDS::eTAC] = 500.0;
  fsDefaultScalingMax[RIDS::eCal][RIDS::eQHL] = 4000.0;
  fsDefaultScalingMax[RIDS::eCal][RIDS::eQHS] = 4000.0;
  fsDefaultScalingMax[RIDS::eCal][RIDS::eQLX] = 1000.0;

  fsDefaultScalingMin[RIDS::eScript][RIDS::eTAC] = 0.0;
  fsDefaultScalingMin[RIDS::eScript][RIDS::eQHL] = 0.0;
  fsDefaultScalingMin[RIDS::eScript][RIDS::eQHS] = 0.0;
  fsDefaultScalingMin[RIDS::eScript][RIDS::eQLX] = 0.0;

  fsDefaultScalingMax[RIDS::eScript][RIDS::eTAC] = 500.0;
  fsDefaultScalingMax[RIDS::eScript][RIDS::eQHL] = 500.0;
  fsDefaultScalingMax[RIDS::eScript][RIDS::eQHS] = 500.0;
  fsDefaultScalingMax[RIDS::eScript][RIDS::eQLX] = 500.0;
}

void
RenderState::ChangeState( RIDS::EDataSource source,
                          RIDS::EDataType type )
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
  for( map< RIDS::EDataSource, string>::iterator iTer = fsSourceNames.begin(); iTer != fsSourceNames.end(); iTer++ )
    strings.push_back( iTer->second );
  return strings;
}

vector<string>
RenderState::GetTypeStrings()
{
  vector<string> strings;
  for( map< RIDS::EDataType, string>::iterator iTer = fsTypeNames.begin(); iTer != fsTypeNames.end(); iTer++ )
    strings.push_back( iTer->second );
  return strings;
}
