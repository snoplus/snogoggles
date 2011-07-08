#include <Viewer/DefaultHits3d.hh>
#include <Viewer/PMTWrapper.hh>
#include <Viewer/ConfigurationTable.hh>
#include <Viewer/ConfigTableUtils.hh>

#include <RAT/DS/EV.hh>
#include <RAT/DS/PMTProperties.hh>

namespace RAT {
    namespace DS {
        class PMTCal;
        class PMTUnCal;
    };
};

namespace Viewer {
namespace Frames {

DefaultHits3d::DefaultHits3d()
{
    fDisplayAllPMTs = false;
    fPMTType = UNCAL;
    fDisplayFrontPMTsOnly = false;
}

void DefaultHits3d::CreateGUIObjects( GUIManager* g, const sf::Rect<double>& optionsArea )
{
    // TODO: Needs to be completed
}

void DefaultHits3d::LoadConfiguration( ConfigurationTable* configTable )
{
    fDisplayAllPMTs = ConfigTableUtils::GetBoolean( configTable, DisplayAllPMTsTag() );
    fPMTType =  (PMTType) configTable->GetI( PMTTypeTag() );
    fDisplayFrontPMTsOnly = ConfigTableUtils::GetBoolean( configTable, DisplayFrontPMTsOnlyTag() );
}

void DefaultHits3d::SaveConfiguration( ConfigurationTable* configTable )
{
    ConfigTableUtils::SetBoolean( configTable, DisplayAllPMTsTag(), fDisplayAllPMTs );
    configTable->SetI( PMTTypeTag(), fPMTType );
    ConfigTableUtils::SetBoolean( configTable, DisplayFrontPMTsOnlyTag(), fDisplayFrontPMTsOnly );
}

void DefaultHits3d::EventLoop( const GUIReturn& g )
{
    // TODO: Needs to be completed
}

void DefaultHits3d::RenderHits( RAT::DS::EV* ev, RAT::DS::PMTProperties* pmtList )
{
    if( fCurrentEV != ev || fReFilter == true )
        FilterHits( ev, pmtList );

    if( fDisplayAllPMTs == true )
        DisplayAllPMTs( pmtList );

    RenderHits( pmtList );
}

void DefaultHits3d::FilterHits( RAT::DS::EV* ev, RAT::DS::PMTProperties* pmtList )
{
    fFilteredHits.clear();
    FilterByType( ev, pmtList );
}

void DefaultHits3d::FilterByType( RAT::DS::EV* ev, RAT::DS::PMTProperties* pmtList )
{
    switch( fPMTType )
    {
        case UNCAL :
            for( int i=0; i < ev->GetPMTUnCalCount(); i++)
            {
                FilterByPosition( PMTUnCalWrapper( ev->GetPMTUnCal( i ) ), pmtList );
            }
            break;
        case CAL :
            for( int i=0; i < ev->GetPMTCalCount(); i++)
            {
                FilterByPosition( PMTCalWrapper( ev->GetPMTCal( i ) ), pmtList );
            }
            break;
    }
}

void DefaultHits3d::FilterByPosition( const PMTWrapper& pmt, RAT::DS::PMTProperties* pmtList )
{
    if( fDisplayFrontPMTsOnly == true )
    {
        if( fFront->IsFront( pmt.GetPos( pmtList ) ) )
            AddToFilteredHits( pmt, pmtList );
    }
    else AddToFilteredHits( pmt, pmtList );
}

void DefaultHits3d::AddToFilteredHits( const PMTWrapper& pmt, RAT::DS::PMTProperties* pmtList )
{
   // TODO: Needs to be completed when ColorPalette is ready
}

void DefaultHits3d::DisplayAllPMTs( RAT::DS::PMTProperties* pmtList )
{
   // TODO: Needs to be completed
}

void DefaultHits3d::RenderHits( RAT::DS::PMTProperties* pmtList )
{
    for( int i=0 ; i < fFilteredHits.size(); i++)
        RenderHit( fFilteredHits.at(i), pmtList );
}

void DefaultHits3d::RenderHit( PMTWrapper& pmt, RAT::DS::PMTProperties* pmtList )
{
   // TODO: Needs to be completed
}

}; // namespace Frames
}; // namespace Viewer
