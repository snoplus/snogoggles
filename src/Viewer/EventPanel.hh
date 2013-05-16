////////////////////////////////////////////////////////////////////////
/// \class Viewer::EventPanel
///
/// \brief   Panel to control the currently displayed event
///
/// \author  Phil Jones <p.g.jones@qmul.ac.uk>
///
/// REVISION HISTORY:\n
///     03/06/12 : P.Jones - New file, first revision \n
///
/// \detail  This panel controls the current RenderState, i.e. the event
///          source/type and details.
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_EventPanel__
#define __Viewer_EventPanel__

#include <SFML/System/Clock.hpp>

#include <Viewer/Panel.hh>
#include <Viewer/RenderState.hh>

namespace Viewer
{

class EventPanel : public Panel
{
public:
  EventPanel( RectPtr rect,
              RenderState& renderState );
  ~EventPanel();
  /// On new event
  void NewEvent( const Event& event );
  /// The event loop
  virtual void EventLoop();
  /// Initialise without using the DataStore
  virtual void PreInitialise( const ConfigurationTable* config );
  /// Initilaise with DataStore access
  virtual void PostInitialise( const ConfigurationTable* config );
  /// Save the current configuration
  virtual void SaveConfiguration( ConfigurationTable* configTable );
  /// Return the current render state
  inline const RenderState GetRenderState();
protected:
  /// Load the GUI configuration specific to the panel
  virtual void LoadGUIConfiguration( const ConfigurationTable* config );

  void ChangeRateMode( double period, bool latest );

  RenderState& fRenderState; /// < Reference to the desktop current render state.
  sf::Clock fClock; /// < Clock to manage continuous event switching
  double fEventPeriod; /// < Time period in seconds per event, negative values indicate no continuous switching
  bool fLatest; /// < Latest event switching
private:
  enum { eMultiPrev = 0, ePrev = 1, eNext = 2, eMultiNext = 3, eDataSource = 4, eDataType = 5, eRate = 6, eGotoID = 7, eLatest = 8, eIDInput = 9 };
};

const RenderState
EventPanel::GetRenderState()
{
  return fRenderState;
}

} //::Viewer

#endif
