#include <Viewer/DefaultHits3d.hh>
#include <Viewer/ConfigurationTable.hh>
#include <Viewer/ConfigTableUtils.hh>
#include <Viewer/HitRenderer3d.hh>
#include <Viewer/ColourPalette.hh>

#include <RAT/DS/EV.hh>
#include <RAT/DS/PMTProperties.hh>
#include <RAT/DS/PMTUnCal.hh>
#include <RAT/DS/PMTCal.hh>
#include <SFML/OpenGL.hpp>

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
    if( fDisplayAllPMTs == true )
        DisplayAllPMTs( pmtList );

    switch( fPMTType )
    {
        case( UNCAL ):
            RenderUnCalHits( ev, pmtList );
            break;
        case( CAL ):
            RenderCalHits( ev, pmtList );
            break;
    }
}

void DefaultHits3d::RenderUnCalHits( RAT::DS::EV* ev, RAT::DS::PMTProperties* pmtList )
{
    for(int i=0; i < ev->GetPMTUnCalCount(); i++)
    {
        glPushAttrib(GL_COLOR);
        RAT::DS::PMTUnCal* pmt = ev->GetPMTUnCal( i );
        SetColour( pmt );
        RenderHit( pmt, pmtList );
        glPopAttrib();
    }
}

void DefaultHits3d::RenderCalHits( RAT::DS::EV* ev, RAT::DS::PMTProperties* pmtList )
{
    for(int i=0; i < ev->GetPMTCalCount(); i++)
    {
        glPushAttrib(GL_COLOR);
        RAT::DS::PMTCal* pmt = ev->GetPMTCal( i );
        SetColour( pmt );
        RenderHit( pmt, pmtList );
        glPopAttrib();
    }
}

void DefaultHits3d::DisplayAllPMTs( RAT::DS::PMTProperties* pmtList )
{
    glPushAttrib( GL_COLOR );
    ColourPalette::gPalette->GetPrimaryColour( eGrey ).SetOpenGL();

    for( int i = 0; i < pmtList->GetCorrPMTsNumber(); i++ )
    {
        if( fDisplayFrontPMTsOnly == true )
            RenderFrontHollowHitOnly( pmtList->GetPos( i ) );
        else
            HitRenderer3d::RenderHollowHit( pmtList->GetPos( i ) );
    }

    glPopAttrib();
}

void DefaultHits3d::SetColour( RAT::DS::PMTUnCal* pmt )
{
    ColourPalette::gPalette->GetColour( pmt->GetsPMTt() / 4000.0 ).SetOpenGL();
}

void DefaultHits3d::SetColour( RAT::DS::PMTCal* pmt )
{
    ColourPalette::gPalette->GetColour( pmt->GetsPMTt() / 500.0 ).SetOpenGL();
}

void DefaultHits3d::RenderHit( RAT::DS::PMTUnCal* pmt, RAT::DS::PMTProperties* pmtList )
{
    if( fDisplayFrontPMTsOnly == true )
        RenderFrontSolidHitOnly( pmt->GetPos( pmtList ) );
    else if( fDisplayAllPMTs == true )
        HitRenderer3d::RenderSolidHit( pmt->GetPos( pmtList ) );
    else
        RenderSolidOrHollowHit( pmt->GetPos( pmtList ) );
}

void DefaultHits3d::RenderHit( RAT::DS::PMTCal* pmt, RAT::DS::PMTProperties* pmtList )
{
    if( fDisplayFrontPMTsOnly == true )
        RenderFrontSolidHitOnly( pmt->GetPos( pmtList ) );
    else if( fDisplayAllPMTs == true )
        HitRenderer3d::RenderSolidHit( pmt->GetPos( pmtList ) );
    else
        RenderSolidOrHollowHit( pmt->GetPos( pmtList ) );
}

void DefaultHits3d::RenderFrontSolidHitOnly( const TVector3& pos )
{
    if( fFront->IsFront( pos ) == true )
        HitRenderer3d::RenderSolidHit( pos );
}

void DefaultHits3d::RenderFrontHollowHitOnly( const TVector3& pos )
{
    if( fFront->IsFront( pos ) == true )
        HitRenderer3d::RenderHollowHit( pos );
}

void DefaultHits3d::RenderSolidOrHollowHit( const TVector3& pos )
{
    if( fFront->IsFront( pos ) == true )
        HitRenderer3d::RenderSolidHit( pos );
    else
        HitRenderer3d::RenderHollowHit( pos );
}

}; // namespace Frames
}; // namespace Viewer
