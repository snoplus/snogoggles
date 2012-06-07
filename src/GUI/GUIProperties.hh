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
#include <Viewer/GUITextureManager.hh>
#include <Viewer/ColourPalette.hh>

namespace Viewer
{
  class ConfigurationTable;
  class ConfigurationFile;

class GUIProperties
{
public:
  /// Destruct and delete textures
  ~GUIProperties();
  void Destruct();

  /// Return the singleton instance
  inline static GUIProperties& GetInstance();

  void PreInitialise( const ConfigurationTable* config );

  /// Get the xml configuration information for object
  const ConfigurationTable* GetConfiguration( const std::string& object ) const;
  /// Get the number of desktops
  unsigned int GetNumDesktops() const;
  /// Load new gui colour scheme
  inline void LoadGUIColourPalette( const std::string& filename );
  /// Load new colour scheme
  inline void LoadColourPalette( const std::string& filename );
  /// Get the gui texture manager
  inline const GUITextureManager& GetGUITextures() const;
  /// Get the current gui colour scheme
  inline const GUIColourPalette& GetGUIColourPalette() const;
  /// Get the current colour scheme
  inline const ColourPalette& GetColourPalette() const;

  inline void Reset();
  inline bool Changed() const;
private:
  GUIProperties();

  GUITextureManager fGUITextures; /// < Manages the gui textures
  GUIColourPalette fGUIColourPalette; /// < The gui colour palette
  ColourPalette fColourPalette; /// < The general colour palette
  ConfigurationFile* fGUIConfiguration; /// < The stored gui configuration xml data
  bool fChanged; /// < Has the gui changed in the last frame

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

inline void 
GUIProperties::LoadGUIColourPalette( const std::string& filename )
{
  fGUIColourPalette.Load( filename );
}

inline void 
GUIProperties::LoadColourPalette( const std::string& filename )
{
  fColourPalette.Load( filename );
}

inline const GUITextureManager&
GUIProperties::GetGUITextures() const
{
  return fGUITextures;
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
