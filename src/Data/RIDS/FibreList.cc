#include <RAT/DB.hh>
#include <RAT/Log.hh>

#include <string>
using namespace std;

#include <Viewer/RIDS/FibreList.hh>
using namespace Viewer::RIDS;

void 
FibreList::Initialise( int /*runID*/ ) /// < Run ID defines which pmt info table to use
{
  RAT::Log::Init("/dev/null");

  RAT::DB* db = RAT::DB::Get();
  assert(db);

  string data = getenv("GLG4DATA");
  assert(data != "");
  db->Load(data + "/SMELLIE.ratdb");
  db->Load(data + "/AMELLIE.ratdb");
  db->Load(data + "/TELLIE.ratdb");

  RAT::DBLinkPtr amellieInfo = db->GetLink("LEDARRAY", "AMELLIE");
  RAT::DBLinkPtr smellieInfo = db->GetLink("LEDARRAY", "SMELLIE");
  RAT::DBLinkPtr tellieInfo = db->GetLink("LEDARRAY", "TELLIE");
  assert(amellieInfo);
  assert(smellieInfo);
  assert(tellieInfo);

  {
    vector<double> xPos = amellieInfo->GetDArray("x");
    vector<double> yPos = amellieInfo->GetDArray("y");
    vector<double> zPos = amellieInfo->GetDArray("z");
    vector<double> uDir = amellieInfo->GetDArray("dir_x");
    vector<double> vDir = amellieInfo->GetDArray("dir_y");
    vector<double> wDir = amellieInfo->GetDArray("dir_z");
    for( size_t iPos = 0; iPos < xPos.size(); iPos++ )
      {
        fPositions.push_back( sf::Vector3<double>( xPos[iPos], yPos[iPos], zPos[iPos] ) );
        fDirections.push_back( sf::Vector3<double>( uDir[iPos], vDir[iPos], wDir[iPos] ) );
        fTypes.push_back(eAMELLIE);
      }
  }
  {
    vector<double> xPos = smellieInfo->GetDArray("x");
    vector<double> yPos = smellieInfo->GetDArray("y");
    vector<double> zPos = smellieInfo->GetDArray("z");
    vector<double> uDir = smellieInfo->GetDArray("dir_x");
    vector<double> vDir = smellieInfo->GetDArray("dir_y");
    vector<double> wDir = smellieInfo->GetDArray("dir_z");
    for( size_t iPos = 0; iPos < xPos.size(); iPos++ )
      {
        fPositions.push_back( sf::Vector3<double>( xPos[iPos], yPos[iPos], zPos[iPos] ) );
        fDirections.push_back( sf::Vector3<double>( uDir[iPos], vDir[iPos], wDir[iPos] ) );
        fTypes.push_back(eSMELLIE);
      }
  }
  {
    vector<double> xPos = tellieInfo->GetDArray("x");
    vector<double> yPos = tellieInfo->GetDArray("y");
    vector<double> zPos = tellieInfo->GetDArray("z");
    vector<double> uDir = tellieInfo->GetDArray("dir_x");
    vector<double> vDir = tellieInfo->GetDArray("dir_y");
    vector<double> wDir = tellieInfo->GetDArray("dir_z");
    for( size_t iPos = 0; iPos < xPos.size(); iPos++ )
      {
        fPositions.push_back( sf::Vector3<double>( xPos[iPos], yPos[iPos], zPos[iPos] ) );
        fDirections.push_back( sf::Vector3<double>( uDir[iPos], vDir[iPos], wDir[iPos] ) );
        fTypes.push_back(eTELLIE);
      }
  }
}
