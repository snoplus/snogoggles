////////////////////////////////////////////////////////////////////
/// \class Channel
///
/// \brief Channel data structure
///
/// \author Phil Jones <p.g.jones@qmul.ac.uk>
///
/// REVISION HISTORY:\n
/// 20/03/13 : P.Jones - New RIDS Refactor. \n
///
/// \detail This class holds a channel's data.
///
////////////////////////////////////////////////////////////////////

#ifndef __Viewer_RIDS_Channel__
#define __Viewer_RIDS_Channel__

#include <vector>

namespace Viewer
{
namespace RIDS
{

class Channel
{
public:
  Channel() : fID( -1 ), fData( 0.0 ) { }
  Channel( int id,
           double data ) : fID( id ), fData( data ) { }

  /// Set the channel ID
  void SetID( int id ) { fID = id; }
  /// Set the data
  void SetData( double data ) { fData = data; }

  /// Return the channel ID
  int GetID() const { return fID; }
  /// Return the data
  double GetData() const { return fData; }
private:
  int fID; /// < Channel ID
  double fData; /// < Data on this channel

};

} // namespace RIDS

} // namespace Viewer

#endif
