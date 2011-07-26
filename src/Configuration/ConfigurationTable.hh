////////////////////////////////////////////////////////////////////////
/// \class Viewer::ConfigurationTable
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

////////////////////////////////////////////////////////////////////////
/// \class Viewer::ConfigurationTable::NoTableError
///
/// \brief   
///
/// \author  Phil Jones <p.jones22@physics.ox.ac.uk>
///
/// REVISION HISTORY:\n
///     11/07/11 : P.Jones - First Revision, new file. \n
///
/// \detail  
///
////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////
/// \class Viewer::ConfigurationTable::NoAttributeError
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

#ifndef __Viewer_ConfigurationTable__
#define __Viewer_ConfigurationTable__

#include <map>
#include <string>
#include <sstream>
#include <stdexcept>

namespace xercesc_3_1
{
  class DOMDocument;
  class DOMElement;
}

namespace Viewer
{

class ConfigurationTable
{
public:
  class NoTableError : public std::runtime_error
  {
  public:
    /// Just sets up a std::runtime_error
    NoTableError( const std::string& param ) : std::runtime_error( param ) {}
  }; 

  class NoAttributeError : public std::runtime_error
  {
  public:
    /// Just sets up a std::runtime_error
    NoAttributeError( const std::string& param ) : std::runtime_error( param ) {}
  };

  ConfigurationTable( xercesc_3_1::DOMElement* element, bool output, xercesc_3_1::DOMDocument* domDocument );

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
  xercesc_3_1::DOMDocument* fDOMDocument;
  xercesc_3_1::DOMElement* fDOMElement;
  bool fOutput;
};

unsigned int
ConfigurationTable::GetNumTables()
{
  return fConfigTables.size();
}

} // ::Viewer

#endif
