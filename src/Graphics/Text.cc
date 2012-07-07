#include <RAT/string_utilities.hpp>

#include <sstream>
using namespace std;

#include <Viewer/Text.hh>
using namespace Viewer;

void
Text::SetString( const string& text )
{
  Clear();
  if( text.empty() )
    return;
  fTextLines = split( text );
  for( vector<string>::iterator iTer = fTextLines.begin(); iTer != fTextLines.end(); iTer++ )
    if( iTer->length() > fMaxLineLength )
      fMaxLineLength = iTer->length();
}

void
Text::AddLine( const string& text )
{
  fTextLines.push_back( text );
  if( text.length() > fMaxLineLength )
    fMaxLineLength = text.length();
}

string
Text::GetString()
{
  stringstream fullString;
  for( unsigned int iLine = 0; iLine < fTextLines.size(); iLine++ )
    {
      if( iLine == 0 )
        fullString << fTextLines[iLine];
      else
        fullString << endl << fTextLines[iLine];
    }
  return fullString.str();
}
