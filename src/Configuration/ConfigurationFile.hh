////////////////////////////////////////////////////////////////////////
/// \class ConfigurationFile
///
/// \brief   Opens read/writes fto configuration xml files
///
/// \author  Phil Jones <p.g.jones@qmul.ac.uk>
///
/// REVISION HISTORY:\n
///     26/05/12 : P.Jones - First Revision, major refactor of Configuration.\n
///
/// \detail  This class opens the xml file for writing or reading. It
///          holds the root ConfigurationTable.
///
////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////
/// \class Viewer::Configuration::NoFileError
///
/// \brief   Error thrown if configuration file doesn't exist.
///
/// \author  Phil Jones <p.jones22@physics.ox.ac.uk>
///
/// REVISION HISTORY:\n
///     12/07/11 : P.Jones - First Revision, new file. \n
///
/// \detail  As brief.
///
////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////
/// \class Viewer::Configuration::WrongModeError
///
/// \brief   Error thrown if output mode is opposite to requested task
///
/// \author  Phil Jones <p.g.jones@qmul.ac.uk>
///
/// REVISION HISTORY:\n
///     26/05/12 : P.Jones - First Revision, new file. \n
///
/// \detail  As brief.
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_ConfigurationFile__
#define __Viewer_ConfigurationFile__

#include <vector>
#include <string>
#include <stdexcept>

namespace xercesc_3_1
{
  class DOMDocument;
}

namespace Viewer
{
  class ConfigurationTable;

class ConfigurationFile
{
public:
  class NoFileError : public std::runtime_error
  {
  public:
    /// Just sets up a std::runtime_error
    NoFileError( const std::string& param ) : std::runtime_error( param ) {}
  }; 
  class WrongModeError : public std::runtime_error
  {
  public:
    /// Just sets up a std::runtime_error
    WrongModeError( const std::string& param ) : std::runtime_error( param ) {}
  }; 
  /// Open a configuration file, as output?
  ConfigurationFile( const std::string& filePath, bool output );
  /// Destructor cleans up memory
  ~ConfigurationFile();
  /// Get the Root table
  const ConfigurationTable& GetTable() const;
  /// Access the writeable root table
  ConfigurationTable& NewTable();
  /// Invoke saving the configuration (loading is automatic)
  void Save();
  /// Get the file version
  int GetVersion() const;
  void SetVersion( int version );
private:
  std::string fFilePath; /// < The file path
  xercesc_3_1::DOMDocument* fDOMDocument; /// < The dom document, kept to delete on class destruction
  ConfigurationTable* fRootTable; /// < The root table
  bool fOutput; /// < Read or write mode?
  int fVersion; /// < File version code
};

} // ::Viewer

#endif
