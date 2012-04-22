////////////////////////////////////////////////////////////////////////
/// \class ScriptData
///
/// \brief   Produces and holds the data as produced by the current script
///
/// \author  Phil Jones <p.g.jones@qmul.ac.uk>
///
/// REVISION HISTORY:\n
///     22/05/12 : P.Jones - First Revision, new file. \n
///
/// \detail  The script is speicified to fill the TObjArray of PMTCal*
///          appropriately. This is then exposed to the frames via a
///          std::vector of PMTCal*. [This may seem perverse, but I 
///          think relying on ROOT is more perverse...] 
///
////////////////////////////////////////////////////////////////////////
#ifndef __Viewer_ScriptData__
#define __Viewer_ScriptData__

#include <vector>

#include <TObjArray.h>
#include <TPython.h>

namespace RAT
{
namespace DS
{
  class Root;
  class PMTCal;
}
}

namespace Viewer
{

class ScriptData
{
public:
  /// Constructs and initialises the data
  ScriptData();
  /// Change the python script
  void ChangeScript( const std::string& fileName );
  /// Clear the current summed data
  void Clear();
  /// Process a new event through the script
  void ProcessEvent( RAT::DS::Root* rDS );
  /// Return the Data
  inline std::vector<RAT::DS::PMTCal*>& GetData();
  
private:
  std::string fScriptFileName; /// < Name of the python script to run, assumed to be located in $VIEWERROOT/SumScripts
  TPython fPyWrapper; /// < The python wrapper
  TObjArray fPyResultArray; /// < The array filled by the python script
  std::vector<RAT::DS::PMTCal*> fScriptData; /// < The data as exposed
};

inline std::vector<RAT::DS::PMTCal*>& 
ScriptData::GetData()
{
  return fScriptData;
}

} //::Viewer

#endif
