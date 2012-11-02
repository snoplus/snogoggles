////////////////////////////////////////////////////////////////////////
/// \class PMTSelectionScript
///
/// \brief   Controls the pmt/lcn selection scripts
///
/// \author  Phil Jones <p.g.jones@qmul.ac.uk>
///
/// REVISION HISTORY:\n
///     27/10/12 : P.Jones - First Revision, new file. \n
///
/// \detail  Holds the python api pointers to the script and the data
///          produced by the script.
///
////////////////////////////////////////////////////////////////////////
#ifndef __Viewer_PMTSelectionScript__
#define __Viewer_PMTSelectionScript__

// Special Python object forward declaration
#ifndef PyObject_HEAD
struct _object;
typedef _object PyObject;
#endif

#include <vector>
#include <string>

namespace RAT
{
namespace DS
{
  class PMTProperties;
}
}

namespace Viewer
{

class PMTSelectionScript
{
public:
  PMTSelectionScript();
  ~PMTSelectionScript();

  /// Initialise with fixed PMT data
  void Initialise( RAT::DS::PMTProperties& pmtProp );

  /// Load a script
  void Load( const std::string& scriptName );
  /// Un load the python script
  void UnLoad();

  /// Process the script
  void Process();
  /// Return a vector of selected (true) or not LCNs
  std::vector<bool> GetSelectionData() const;
private:
  void ResetData();

  std::string fCurrentScript;
  PyObject* fpScript;
  PyObject* fpSelectFunction;
  PyObject* fpData;
  PyObject* fpPMTData;
  unsigned int fChannels;
};

} //::Viewer

#endif
