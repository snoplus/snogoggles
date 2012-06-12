////////////////////////////////////////////////////////////////////////
/// \class Viewer::GUIs::PersistLabel
///
/// \brief   Label with a check box next to it
///
/// \author  Phil Jones <p.jones22@physics.ox.ac.uk>
///
/// REVISION HISTORY:\n
///     30/06/11 : P.Jones - First Revision, new file. \n
///     07/06/12 : P.Jones - Second Revision, composite object.\n
///
/// \detail  As brief
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_GUIs_PersistLabel__
#define __Viewer_GUIs_PersistLabel__

#include <string>

#include <Viewer/GUI.hh>
#include <Viewer/Persist.hh>
#include <Viewer/RectPtr.hh>
#include <Viewer/Text.hh>

namespace Viewer
{ 
  class RWWrapper;

namespace GUIs
{

class PersistLabel : public GUI
{
public:
  PersistLabel( RectPtr rect, unsigned int guiID );
  virtual ~PersistLabel();

  void Initialise( unsigned int textureNumber, 
                   const std::string& label );
  void SetLabel( const std::string& label ); //REMOVE ME

  GUIEvent NewEvent( const Event& event );
  void Render( RWWrapper& windowApp );
  
  inline void SetState( bool state );
  inline bool GetState() const;
protected:
  Persist fPersist;
  Text fText;
};

void
PersistLabel::SetState( bool state )
{
  fPersist.SetState( state );
}

bool
PersistLabel::GetState() const
{
  return fPersist.GetState();
}

} // ::GUIs

} // ::Viewer

#endif
