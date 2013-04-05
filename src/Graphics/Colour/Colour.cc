#include <algorithm>

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
Colour::AddColourFraction( const Colour& newColour, const double fraction )
{
  this->r = abs( this->r + fraction * ( newColour.r - this->r ) );
  this->g = abs( this->g + fraction * ( newColour.g - this->g ) );
  this->b = abs( this->b + fraction * ( newColour.b - this->b ) );
  this->a = abs( this->a + fraction * ( newColour.a - this->a ) );
  return;
}

void
Colour::Tint( const double fraction )
{
  int r = this->r * fraction;
  int g = this->g * fraction;
  int b = this->b * fraction;
  int max = std::max( r, std::max( g, b ) );
  if( max > 255 )
    {
      // Must redistribute
      const int total = r + g + b;
      if( total > 255 * 3 )
        {
          r = 255; 
          g = 255; 
          b = 255;
        }
      else
        {
          double ratio = static_cast<double>( 3 * 255 - total ) / static_cast<double>( 3 * max - total );
          int grey = 255 - ratio * max;
          r = grey + ratio * r;
          g = grey + ratio * g;
          b = grey + ratio * b;
        }
    }
  this->r = r;
  this->g = g;
  this->b = b;
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
