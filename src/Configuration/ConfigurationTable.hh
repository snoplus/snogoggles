////////////////////////////////////////////////////////////////////////
/// \class Viewer::ConfigurationTable
///
/// \brief   Holds a single element entry of xml
///
/// \author  Phil Jones <p.g.jones@qmul.ac.uk>
///
/// REVISION HISTORY:\n
///     29/06/11 : P.Jones - First Revision, new file. \n
///     26/05/12 : P.Jones - Second Revision, refactor.\n
///
/// \detail  An element/node of xml.
///
////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////
/// \class Viewer::ConfigurationTable::NoTableError
///
/// \brief   Error thrown on table name not found.
///
/// \author  Phil Jones <p.jones22@physics.ox.ac.uk>
///
/// REVISION HISTORY:\n
///     11/07/11 : P.Jones - First Revision, new file. \n
///
/// \detail  As brief
///
////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////
/// \class Viewer::ConfigurationTable::NoAttributeError
///
/// \brief   Error thrown on attribute (GetI/D/S) not found.
///
/// \author  Phil Jones <p.jones22@physics.ox.ac.uk>
///
/// REVISION HISTORY:\n
///     12/07/11 : P.Jones - First Revision, new file. \n
///
/// \detail  As brief.
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_ConfigurationTable__
#define __Viewer_ConfigurationTable__

#include <vector>
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

  ConfigurationTable( xercesc_3_1::DOMElement* element, 
                      const std::string& name, 
                      xercesc_3_1::DOMDocument* domDocument );

  bool HasTable( const std::string& name ) const;
  const ConfigurationTable* GetTable( const unsigned int iTable ) const;
  const ConfigurationTable* GetTable( const std::string& name ) const;
  inline std::vector< ConfigurationTable* >::iterator GetTableBegin();
  inline std::vector< ConfigurationTable* >::iterator GetTableEnd();
  inline unsigned int GetNumTables() const;
  ConfigurationTable* NewTable( const std::string& name );

  /// Return true if property exists
  bool Has( const std::string& name ) const;
  /// Get the table name
  std::string GetName() const;

  int GetI( const std::string& name ) const;
  double GetD( const std::string& name ) const;
  std::string GetS( const std::string& name ) const;

  void SetI( const std::string& name, const int value );
  void SetD( const std::string& name, const double value );
  void SetS( const std::string& name, const std::string& value );
private:
  std::vector< ConfigurationTable* > fConfigTables; /// < Array of child tables
  std::string fName; /// < Table name 
  xercesc_3_1::DOMDocument* fDOMDocument; /// < The dom document
  xercesc_3_1::DOMElement* fDOMElement; /// < This element
};

std::vector< ConfigurationTable* >::iterator
ConfigurationTable::GetTableBegin()
{
  return fConfigTables.begin();
}
  
std::vector< ConfigurationTable* >::iterator
ConfigurationTable::GetTableEnd()
{
  return fConfigTables.end();
}
  
unsigned int
ConfigurationTable::GetNumTables() const
{
  return fConfigTables.size();
}

} // ::Viewer

#endif
