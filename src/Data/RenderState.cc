using namespace std;

#include <Viewer/RenderState.hh>
using namespace Viewer;

std::map< RenderState::EDataSource, std::string > RenderState::fsSourceNames;
std::map< RenderState::EDataType, std::string > RenderState::fsTypeNames;

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
