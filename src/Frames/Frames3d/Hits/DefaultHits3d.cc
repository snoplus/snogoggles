#include <Viewer/DefaultHits3d.hh>
#include <Viewer/ConfigurationTable.hh>
#include <Viewer/ConfigTableUtils.hh>
#include <Viewer/ColourPalette.hh>

#include <RAT/DS/EV.hh>
#include <RAT/DS/PMTProperties.hh>
#include <RAT/DS/PMTUnCal.hh>
#include <RAT/DS/PMTCal.hh>
#include <SFML/OpenGL.hpp>

#include <iostream>

namespace Viewer {
namespace Frames {

const std::string DefaultHits3d::fDisplayAllPMTsTag = "DisplayAllPMTs";
const std::string DefaultHits3d::fPMTTypeTag = "PMTType";
const std::string DefaultHits3d::fDisplayFrontPMTsOnlyTag = "DisplayFrontPMTsOnly";

DefaultHits3d::DefaultHits3d()
{
    fDisplayAllPMTs = false;
    fPMTType = UNCAL;
    fDisplayFrontPMTsOnly = false;
    fCurrentEV = NULL;
    fCurrentPMTList = NULL;
}

void DefaultHits3d::CreateGUIObjects( GUIManager& g, const sf::Rect<double>& optionsArea )
{
    // TODO: Needs to be completed
}

void DefaultHits3d::LoadConfiguration( ConfigurationTable* configTable )
{
    ConfigTableUtils::GetBooleanSafe( configTable, fDisplayAllPMTsTag, fDisplayAllPMTs );
    ConfigTableUtils::GetEnumSafe< PMTType >( configTable, fPMTTypeTag, fPMTType );
    ConfigTableUtils::GetBooleanSafe( configTable, fDisplayFrontPMTsOnlyTag, fDisplayFrontPMTsOnly );
}

void DefaultHits3d::SaveConfiguration( ConfigurationTable* configTable )
{
    ConfigTableUtils::SetBoolean( configTable, fDisplayAllPMTsTag, fDisplayAllPMTs );
    configTable->SetI( fPMTTypeTag, fPMTType );
    ConfigTableUtils::SetBoolean( configTable, fDisplayFrontPMTsOnlyTag, fDisplayFrontPMTsOnly );
}

void DefaultHits3d::EventLoop( )
{
    // TODO: Needs to be completed
}

void DefaultHits3d::RenderHits( RAT::DS::EV* ev, RAT::DS::PMTProperties* pmtList )
{
    if( fCurrentPMTList != pmtList )
    {
        SaveAllPMTs( pmtList );
        fCurrentPMTList = pmtList;
    }

    if( fCurrentEV != ev )
    {
        FilterHits( ev, pmtList );
        fCurrentEV = ev;
    }

    if( fDisplayAllPMTs == true )
        DisplayHits( fAllPMTs, true );

    DisplayHits( fFilteredHits, false );
}

void DefaultHits3d::SaveAllPMTs( RAT::DS::PMTProperties* pmtList )
{
    fAllPMTs.clear();
    for( int i = 0; i < pmtList->GetPMTCount(); i++ )
    {
        fAllPMTs.push_back( Hit( pmtList->GetPos( i ), ColourPalette::gPalette->GetPrimaryColour( eGrey ) ) );
    }

}

void DefaultHits3d::FilterHits( RAT::DS::EV* ev, RAT::DS::PMTProperties* pmtList )
{
    if( fPMTType == CAL )
        FilterPMTCal( ev, pmtList );
    else
        FilterPMTUnCal( ev, pmtList );
}

void DefaultHits3d::FilterPMTCal( RAT::DS::EV* ev, RAT::DS::PMTProperties* pmtList )
{
    for( int i = 0; i < ev->GetPMTCalCount(); i++ )
    {
        RAT::DS::PMTCal* pmt = ev->GetPMTCal( i );
        TVector3 pos = pmtList->GetPos( pmt->GetID() );
        if( PassesFilters( pos ) )
            fFilteredHits.push_back( Hit( pos, AssignColour( pmt ) ) );
    }
}

void DefaultHits3d::FilterPMTUnCal( RAT::DS::EV* ev, RAT::DS::PMTProperties* pmtList )
{
    for( int i = 0; i < ev->GetPMTUnCalCount(); i++ )
    {
        RAT::DS::PMTUnCal* pmt = ev->GetPMTUnCal( i );
        TVector3 pos = pmtList->GetPos( pmt->GetID() );
        if( PassesFilters( pos ) )
            fFilteredHits.push_back( Hit( pos, AssignColour( pmt ) ) );
    }
}

Colour DefaultHits3d::AssignColour( RAT::DS::PMTUnCal* pmt )
{
    return ColourPalette::gPalette->GetColour( pmt->GetsPMTt() / 4000.0 );
}

Colour DefaultHits3d::AssignColour( RAT::DS::PMTCal* pmt )
{
    return ColourPalette::gPalette->GetColour( pmt->GetsPMTt() / 500.0 );
}

bool DefaultHits3d::PassesFilters( const TVector3& pos )
{
    return FilterByFront( pos );
}

bool DefaultHits3d::FilterByFront( const TVector3& pos )
{
    if( fDisplayFrontPMTsOnly == true )
        return fFront->IsFront( pos );
    return true;
}

void DefaultHits3d::DisplayHits( const std::vector< Hit >& hits, bool forceHollow )
{
    for( int i = 0; i < hits.size(); i++ )
    {
        bool fill = fFront->IsFront( hits.at(i).GetPos() );;
        if( forceHollow ) fill = false;
        hits.at(i).Render( fill );
    }
}

}; // namespace Frames
}; // namespace Viewer
