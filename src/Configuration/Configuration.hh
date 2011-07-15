////////////////////////////////////////////////////////////////////////
/// \class Configuration
///
/// \brief   
///
/// \author  Phil Jones <p.jones22@physics.ox.ac.uk>
///
/// REVISION HISTORY:\n
///     29/06/11 : P.Jones - First Revision, new file. \n
///     15/07/11 : Olivia Wasalski - Fixed memory leak in constructor, added destructor. \n
///
/// \detail  
///
////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////
/// \class Viewer::Configuration::NoFileError
///
/// \brief   
///
/// \author  Phil Jones <p.jones22@physics.ox.ac.uk>
///
/// REVISION HISTORY:\n
///     12/07/11 : P.Jones - First Revision, new file. \n
///
/// \detail  
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_Configuration__
#define __Viewer_Configuration__

#include <vector>
#include <string>
#include <stdexcept>

namespace xercesc_2_8
{
  class DOMDocument;
  class DOMElement;
}

namespace Viewer
{
  class ConfigurationTable;

class Configuration
{
public:
  class NoFileError : public std::runtime_error
  {
  public:
    /// Just sets up a std::runtime_error
    NoFileError( const std::string& param ) : std::runtime_error( param ) {}
  }; 

  Configuration( const std::string& fileName, bool ouput );

  ~Configuration();
  
  inline std::vector< ConfigurationTable* >::iterator GetTableBegin();
  inline std::vector< ConfigurationTable* >::iterator GetTableEnd();
  inline unsigned int GetNumTables();
  
  ConfigurationTable* NewTable( const std::string& name );

  void SaveConfiguration();

  int GetI( const std::string& name );
  double GetD( const std::string& name );
  std::string GetS( const std::string& name );

  void SetI( const std::string& name, const int value );
  void SetD( const std::string& name, const double value );
  void SetS( const std::string& name, const std::string& value );
private:
  std::string fFileName;
  std::vector< ConfigurationTable* > fConfigTables;
  xercesc_2_8::DOMDocument* fDOMDocument;
  xercesc_2_8::DOMElement* fRootElement;
  bool fOutput;

};

std::vector< ConfigurationTable* >::iterator 
Configuration::GetTableBegin()
{
  return fConfigTables.begin();
}

std::vector< ConfigurationTable* >::iterator 
Configuration::GetTableEnd()
{
  return fConfigTables.end();
}

unsigned int
Configuration::GetNumTables()
{
  return fConfigTables.size();
}

} // ::Viewer

#endif
