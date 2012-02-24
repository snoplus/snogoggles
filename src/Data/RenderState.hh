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

  static std::vector<std::string> GetSourceStrings();
  static std::vector<std::string> GetTypeStrings();

  inline EDataSource GetDataSource() const;
  inline EDataType GetDataType() const;
private:
  EDataSource fCurrentDataSource;
  EDataType fCurrentDataType;

  static std::map< EDataSource, std::string > fsSourceNames;
  static std::map< EDataType, std::string > fsTypeNames;
};

inline 
RenderState::RenderState()
{
  fCurrentDataSource = eCal;
  fCurrentDataType = eTAC;
}

inline 
RenderState::RenderState( EDataSource source,
			  EDataType type )
{
  fCurrentDataSource = source;
  fCurrentDataType = type;
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

} //::Viewer

#endif
