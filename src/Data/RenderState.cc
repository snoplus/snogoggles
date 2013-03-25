using namespace std;

#include <Viewer/RenderState.hh>
#include <Viewer/ConfigurationTable.hh>
#include <Viewer/GUIProperties.hh>
using namespace Viewer;

void
RenderState::ChangeState( int source,
                          int type )
{
  fCurrentDataSource = source;
  fCurrentDataType = type;
  fChanged = true;
}

void 
RenderState::ChangeScaling( double fractionalMin,
                            double fractionalMax )
{
  fChanged = true;
}

Colour
RenderState::GetDataColour( double data ) const
{
  return GUIProperties::GetInstance().GetColourPalette().GetColour( ( data - fCurrentScalingMin ) / ( fCurrentScalingMax - fCurrentScalingMin ) );
}
