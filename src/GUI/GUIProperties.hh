////////////////////////////////////////////////////////////////////////
/// \class Viewer::GUIProperties
///
/// \brief   Holds all the GUI properties.
///
/// \author  Phil Jones <p.g.jones@qmul.ac.uk>
///
/// REVISION HISTORY:\n
///      23/05/12 : P.Jones - First Revision, new file.\n
///
/// \detail  Loads the GUI properties from the appropriate xml file. 
///          These are then exposed to the viewer code.
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_GUIProperties__
#define __Viewer_GUIProperties__

#include <Viewer/GUIColourPalette.hh>
#include <Viewer/ColourPalette.hh>

namespace Viewer
{
  class ConfigurationTable;
  class ConfigurationFile;

class GUIProperties
{
public:
  /// Destruct and delete textures
  virtual ~GUIProperties();
  /// Return the singleton instance
  inline static GUIProperties& GetInstance();

  void PreInitialise( const ConfigurationTable* config );

  /// Get the list of colour scheme names
  std::vector< std::string > GetColourSchemes();
  /// Get the list of colour scheme names
  std::vector< std::string > GetGUIColourSchemes();
  /// Get the xml configuration information for object
  const ConfigurationTable* GetConfiguration( const std::string& object ) const;
  /// Get the number of desktops
  unsigned int GetNumDesktops() const;
  /// Get the current gui colour scheme
  inline const GUIColourPalette& GetGUIColourPalette() const;
  /// Get the current colour scheme
  inline const ColourPalette& GetColourPalette() const;
private:
  GUIProperties();

  GUIColourPalette fGUIColourPalette; /// < The gui colour palette
  ColourPalette fColourPalette; /// < The general colour palette
  ConfigurationFile* fGUIConfiguration; /// < The stored gui configuration xml data

  /// Stop usage of
  GUIProperties( GUIProperties const& );
  void operator=( GUIProperties const& );
};

inline GUIProperties&
GUIProperties::GetInstance()
{
  static GUIProperties instance;
  return instance;
}

inline const GUIColourPalette&
GUIProperties::GetGUIColourPalette() const
{
  return fGUIColourPalette;
}

inline const ColourPalette&
GUIProperties::GetColourPalette() const
{
  return fColourPalette;
}

} // ::Viewer

#endif
