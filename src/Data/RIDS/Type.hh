////////////////////////////////////////////////////////////////////
/// \class Type
///
/// \brief Type data structure
///
/// \author Phil Jones <p.g.jones@qmul.ac.uk>
///
/// REVISION HISTORY:\n
/// 20/03/13 : P.Jones - New RIDS Refactor. \n
///
/// \detail This holds a vector of channels.
///
////////////////////////////////////////////////////////////////////

#ifndef __Viewer_RIDS_Type__
#define __Viewer_RIDS_Type__

#include <vector>

#include <Viewer/RIDS/Channel.hh>

namespace Viewer
{
namespace RIDS
{

class Type
{
public:
  Type();

  void AddChannel( int id, double data );

  size_t GetCount() const { return fData.size(); }
  
  const Channel& GetChannel( int channel ) const { return fData[channel]; } 

  double GetMin() const { return fMin; }
  double GetMax() const { return fMax; }

  /// Return a vector of channel data in this event given the source and data type
  const std::vector<Channel>& GetData() const { return fData; }
private:
  std::vector<Channel> fData; /// < The type data separated by DAQ channel
  double fMin; /// < The minimum data value
  double fMax; /// < The maximum data value
};

} // namespace RIDS

} // namespace Viewer

#endif
