////////////////////////////////////////////////////////////////////////
/// \class ConfigurationTable
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

#ifndef __Viewer_ConfigurationTable__
#define __Viewer_ConfigurationTable__

#include <map>
#include <string>
#include <sstream>

namespace xercesc_2_8
{
  class DOMDocument;
  class DOMElement;
}

namespace Viewer
{

class ConfigurationTable
{
public:
  ConfigurationTable( xercesc_2_8::DOMElement* element, bool output, xercesc_2_8::DOMDocument* domDocument );

  ConfigurationTable* GetTable( const std::string& name );
  inline unsigned int GetNumTables();
  ConfigurationTable* NewTable( const std::string& name );

  int GetI( const std::string& name );
  double GetD( const std::string& name );
  std::string GetS( const std::string& name );

  void SetI( const std::string& name, const int value );
  void SetD( const std::string& name, const double value );
  void SetS( const std::string& name, const std::string& value );
private:
  std::map< std::string, ConfigurationTable* > fConfigTables;
  xercesc_2_8::DOMDocument* fDOMDocument;
  xercesc_2_8::DOMElement* fDOMElement;
  bool fOutput;
};

unsigned int
ConfigurationTable::GetNumTables()
{
  return fConfigTables.size();
}

} // ::Viewer

#endif
