////////////////////////////////////////////////////////////////////////
/// \class Viewer::RenderState
///
/// \brief   Contains the current displayed data type
///
/// \author  Phil Jones <p.g.jones@qmul.ac.uk>
///
/// REVISION HISTORY:\n
///     19/02/12 : P.Jones - New file, first revision \n
///
/// \detail  This class is used to define what data to show.
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_RenderState__
#define __Viewer_RenderState__

#include <string>
#include <map>
#include <vector>

namespace Viewer
{

class RenderState
{
public:
  enum EDataType { eTAC, eQHL, eQHS, eQLX };
  enum EDataSource { eMC, eTruth, eUnCal, eCal, eScript };

  inline RenderState();

  inline RenderState( EDataSource source,
		      EDataType type );

  static void Initialise();

  void ChangeState( EDataSource source,
		    EDataType type );
  void ChangeScaling( double fractionalMin,
		      double fractionalMax );

  static std::vector<std::string> GetSourceStrings();
  static std::vector<std::string> GetTypeStrings();

  inline EDataSource GetDataSource() const;
  inline EDataType GetDataType() const;
  inline double GetScalingMin() const;
  inline double GetScalingMax() const;

private:
  EDataSource fCurrentDataSource;
  EDataType fCurrentDataType;

  double fCurrentScalingMin; /// < Lower numerical value to be displayed
  double fCurrentScalingMax; /// < Upper numerical value to be displayed

  static std::map< EDataSource, std::string > fsSourceNames;
  static std::map< EDataType, std::string > fsTypeNames;
  static std::map< EDataSource, std::map< EDataType, double > > fsDefaultScalingMin;
  static std::map< EDataSource, std::map< EDataType, double > > fsDefaultScalingMax;
};

inline 
RenderState::RenderState()
{
  ChangeState( eCal, eTAC );
}

inline 
RenderState::RenderState( EDataSource source,
			  EDataType type )
{
  ChangeState( source, type );
}

inline RenderState::EDataSource 
RenderState::GetDataSource() const
{
  return fCurrentDataSource;
}

inline RenderState::EDataType 
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

} //::Viewer

#endif
