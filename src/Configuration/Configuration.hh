////////////////////////////////////////////////////////////////////////
/// \class Configuration
///
/// \brief   
///
/// \author  Phil Jones <p.jones22@physics.ox.ac.uk>
///
/// REVISION HISTORY:\n
///     29/06/11 : P.Jones - First Revision, new file. \n
///
/// \detail  
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_Configuration__
#define __Viewer_Configuration__

#include <vector>
#include <string>

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
  Configuration( bool ouput );
  
  inline std::vector< ConfigurationTable* >::iterator GetTableBegin();
  inline std::vector< ConfigurationTable* >::iterator GetTableEnd();
  inline ConfigurationTable* GetViewerTable();
  inline unsigned int GetNumTables();
  
  ConfigurationTable* NewTable( const std::string& name );

  void SaveConfiguration();
private:
  std::vector< ConfigurationTable* > fConfigTables;
  ConfigurationTable* fViewerTable;
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


ConfigurationTable*
Configuration::GetViewerTable()
{
  return fViewerTable;
}

unsigned int
Configuration::GetNumTables()
{
  return fConfigTables.size();
}

} // ::Viewer

#endif
