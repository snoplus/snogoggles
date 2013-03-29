////////////////////////////////////////////////////////////////////////
/// \file Directory
///
/// \brief   A Rectangle coordinate.
///
/// \author  Phil Jones <p.g.jones@qmul.ac.uk>
///
/// REVISION HISTORY:\n
///     12/06/12 : P.Jones - First Revision, new file. \n
///
/// \detail  Helper function for directory/file io.
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_Directory__
#define __Viewer_Directory__

#include <vector>
#include <string>

namespace Viewer
{

  std::vector<std::string> GetFilesInDirectory( const std::string& folderPath,
                                                const std::string& extension = std::string(""),
                                                const std::string& omit = std::string("") );

} // ::Viewer

#endif
