#include <Viewer/DefaultTracks3d.hh>
#include <Viewer/PersistLabel.hh>
#include <Viewer/GUIEvent.hh>
#include <Viewer/ConfigurationTable.hh>
#include <Viewer/DataSelector.hh>
using namespace Viewer;

void 
DefaultTracks3d::EventLoop()
{
  while( !fEvents.empty() )
    {
      if( fEvents.front().fguiID == 0 )
        fDisplayFull = !fDisplayFull;
      else if( fEvents.front().fguiID > 0 )
        {
          GUIs::PersistLabel* button = dynamic_cast<GUIs::PersistLabel*>( fGUIManager.GetGUI( fEvents.front().fguiID ) );
          fDisplayParticle[button->GetLabel()] = button->GetState();
          fTrackBuffer.fParticleTypes[button->GetLabel()].fVisible = button->GetState();
        }
      fEvents.pop();
    }
}

void 
DefaultTracks3d::SaveConfiguration( ConfigurationTable* configTable )
{
  configTable->SetI( "DisplayFull", fDisplayFull );
  for( map<string, bool>::iterator iTer = fDisplayParticle.begin(); iTer != fDisplayParticle.end(); iTer++ )
    configTable->SetI( iTer->first, iTer->second );
}

void 
DefaultTracks3d::PreInitialise( const ConfigurationTable* configTable )
{
  // First tell the track buffer what particles are special
  fTrackBuffer.AddParticleType( "opticalphoton", 0 );
  fTrackBuffer.AddParticleType( "gamma", 1.f/6 );
  fTrackBuffer.AddParticleType( "e-", 2.f/6 );
  fTrackBuffer.AddParticleType( "neutrino", 3.f/6 );
  fTrackBuffer.AddParticleType( "neutron", 4.f/6 );
  fTrackBuffer.AddParticleType( "unknown", 5.f/6 );
  const vector<string> names = fTrackBuffer.GetNames();
  // Now the display full track button
  sf::Rect<double> size;
  size.left = 0.0; size.top = 0.0; size.width = 1.0; 
  size.height = 1.0 / static_cast<double>( names.size() + 1 );
  GUIs::PersistLabel* displayFull = dynamic_cast<GUIs::PersistLabel*>( fGUIManager.NewGUI<GUIs::PersistLabel>( size ) );
  displayFull->Initialise( 16, "Full Tracks" );
  if( configTable != NULL )
    fDisplayFull = static_cast<bool>( configTable->GetI( "DisplayFull" ) );
  displayFull->SetState( fDisplayAll );
  // Now the individual particle states
  for( vector<string>::const_iterator iTer = names.begin(); iTer != names.end(); iTer++ )
    {
      size.top += size.height;
      fDisplayParticle[*iTer] = false;
      if( configTable != NULL )
        fDisplayParticle[*iTer] = static_cast<bool>( configTable->GetI( *iTer ) );
      GUIs::PersistLabel* button = dynamic_cast<GUIs::PersistLabel*>( fGUIManager.NewGUI<GUIs::PersistLabel>( size ) );
      button->Initialise( 16, *iTer );
      button->SetState( fDisplayParticle[*iTer] );
    }
}

void
DefaultTracks3d::ProcessEvent( const RenderState& renderState )
{
  fTrackBuffer.SetAll( DataSelector::GetInstance().GetEvent() );
}

void
DefaultTracks3d::Render3d()
{
  fTrackBuffer.Render( fDisplayFull );
}
