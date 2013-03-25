using namespace std;

#include <Viewer/RIDS/Event.hh>
using namespace Viewer::RIDS;

vector< pair< string, vector< string > > > Event::fsDataNames;

Event::Event()
{
  for( DataNames::const_iterator iTer = fsDataNames.begin(); iTer != fsDataNames.end(); iTer++ )
    {
      Source source( iTer->second.size() );
      fSources.push_back( source );
    }
}

const vector<Channel>& 
Event::GetData( size_t source, 
                size_t type ) const
{
  return fSources[source].GetData( type );
}

vector<string>
Event::GetSourceNames()
{
  vector<string> sourceNames;
  for( DataNames::const_iterator iTer = fsDataNames.begin(); iTer != fsDataNames.end(); iTer++ )
    sourceNames.push_back( iTer->first );
  return sourceNames;
}

vector<string>
Event::GetTypeNames( int source )
{
  return fsDataNames[source].second;
}
