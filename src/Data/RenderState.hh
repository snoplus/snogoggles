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

namespace Viewer
{

class RenderState
{
public:
  enum EDataType { eTAC, eQHL, eQHS, eQLX };
  enum EDataSource { eMC, eTruth, eUnCal, eCal };

private:
  EDataType fCurrentDataType;
  EDataSource fCurrentDataSource;

  static std::map< EDataSource, std::string> fsSourceNames;
  static std::map< EDataType, std::string> fsTypeNames;
};

} //::Viewer

#endif
