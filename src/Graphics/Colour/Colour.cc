#include <Viewer/ConfigurationTable.hh>
#include <Viewer/Colour.hh>
using namespace Viewer;

Colour::Colour( const ConfigurationTable* configTable )
{ 
  if( configTable->Has( "r" ) )
    r = configTable->GetI( "r" );
  else
    r = 255;
  if( configTable->Has( "g" ) )
    g = configTable->GetI( "g" );
  else
    g = 255;
  if( configTable->Has( "b" ) )
    b = configTable->GetI( "b" );
  else
    b = 255;
  if( configTable->Has( "a" ) )
    a = configTable->GetI( "a" );
  else
    a = 255;
}

void
Colour::AddColourFraction( const Colour& newColour, double fraction )
{
  this->r = this->r + fraction * ( newColour.r - this->r );
  this->g = this->g + fraction * ( newColour.g - this->g );
  this->b = this->b + fraction * ( newColour.b - this->b );
  this->a = this->a + fraction * ( newColour.a - this->a );
  return;
}

void Colour::Load( const ConfigurationTable* configTable )
{
    // define this in two steps so that if an exception is thrown 
    // in one of the colours, none of them are changed.
    int red = configTable->GetI( "r" );
    int green = configTable->GetI( "g" );
    int blue = configTable->GetI( "b" );
    int alpha = configTable->GetI( "a" );

    r = red;
    g = green;
    b = blue;
    a = alpha;
}

void Colour::Save( ConfigurationTable* configTable ) const
{
    configTable->SetI( "r", r );
    configTable->SetI( "g", g );
    configTable->SetI( "b", b );
    configTable->SetI( "a", a );
}
