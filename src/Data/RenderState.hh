////////////////////////////////////////////////////////////////////////
/// \class Viewer::RenderState
///
/// \brief   Contains the current displayed data type
///
/// \author  Phil Jones <p.g.jones@qmul.ac.uk>
///
/// REVISION HISTORY:\n
///     19/02/12 : P.Jones - New file, first revision \n
///     07/05/12 : P.Jones - Update to use RIDS.\n
///
/// \detail  This class is used to define what data to show.
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_RenderState__
#define __Viewer_RenderState__

#include <string>
#include <map>
#include <vector>

#include <Viewer/RIDS/RIDS.hh>

namespace Viewer
{
class Colour;
namespace RIDS {
    class PMTHit;
}

class RenderState
{
public:
  inline RenderState();

  inline RenderState( RIDS::EDataSource source,
                      RIDS::EDataType type );

  static void Initialise();

  void ChangeState( RIDS::EDataSource source,
                    RIDS::EDataType type );
  void ChangeScaling( double fractionalMin,
                      double fractionalMax );

  static std::vector<std::string> GetSourceStrings();
  static std::vector<std::string> GetTypeStrings();

  inline RIDS::EDataSource GetDataSource() const;
  inline RIDS::EDataType GetDataType() const;
  inline double GetScalingMin() const;
  inline double GetScalingMax() const;
  Colour GetDataColour( double data ) const;
  Colour GetHitColour( const RIDS::PMTHit& pmtHit ) const;

  inline bool HasChanged() const;
  inline void Reset();

private:
  RIDS::EDataSource fCurrentDataSource;
  RIDS::EDataType fCurrentDataType;

  double fCurrentScalingMin; /// < Lower numerical value to be displayed
  double fCurrentScalingMax; /// < Upper numerical value to be displayed
  bool fChanged; /// < Mark if data source/type has changed in the last frame

  static std::map< RIDS::EDataSource, std::string > fsSourceNames;
  static std::map< RIDS::EDataType, std::string > fsTypeNames;
  static std::map< RIDS::EDataSource, std::map< RIDS::EDataType, double > > fsDefaultScalingMin;
  static std::map< RIDS::EDataSource, std::map< RIDS::EDataType, double > > fsDefaultScalingMax;
};

inline 
RenderState::RenderState()
{
  ChangeState( RIDS::eCal, RIDS::eTAC );
}

inline 
RenderState::RenderState( RIDS::EDataSource source,
                          RIDS::EDataType type )
{
  ChangeState( source, type );
}

inline RIDS::EDataSource 
RenderState::GetDataSource() const
{
  return fCurrentDataSource;
}

inline RIDS::EDataType 
RenderState::GetDataType() const
{
  return fCurrentDataType;
}

inline double
RenderState::GetScalingMin() const
{
  return fCurrentScalingMin;
}

inline double
RenderState::GetScalingMax() const
{
  return fCurrentScalingMax;
}

inline bool
RenderState::HasChanged() const
{
  return fChanged;
}

inline void
RenderState::Reset()
{
  fChanged = false;
}

} //::Viewer

#endif
