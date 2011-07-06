////////////////////////////////////////////////////////////////////////
/// \class Viewer::StringUtils
///
/// \brief   Contains string utilities
///
/// \author  Olivia Wasalski <wasalski@triumf.ca>
///                          <oliviawasalski@gmail.com>
///
/// REVISION HISTORY:\n
///     05/07/11 : Olivia Wasalski - First Revision, New File. \n
///
/// \detail  As Brief.
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_StringUtils__
#define __Viewer_StringUtils__

#include <string>
#include <vector>
using namespace std;

namespace Viewer {

class StringUtils
{

public:

    /// Splits string using the delimiter
    static int SplitString(const string& input, 
                           const string& delimiter, 
                           vector<string>& results, 
                           bool includeEmpties = false);

}; // class StringUtils

}; // namespace Viewer

#endif // __Viewer_StringUtils__
