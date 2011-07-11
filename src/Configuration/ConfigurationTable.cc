using namespace std;

#include <Viewer/ConfigurationTable.hh>
using namespace Viewer;

#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/dom/DOM.hpp>
#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/util/XMLUni.hpp>
using namespace xercesc;


ConfigurationTable::ConfigurationTable( xercesc_2_8::DOMElement* element, bool output, DOMDocument* domDocument )
{
  fDOMDocument = domDocument;
  fDOMElement = element;
  fOutput = output;
  // Now extract config tables
  DOMNodeList* children = fDOMElement->getChildNodes();
  for( XMLSize_t ix = 0; ix < children->getLength(); ++ix ) // Pre increment to save memory
    {
      DOMNode* currentNode = children->item(ix);
      if( currentNode->getNodeType() && currentNode->getNodeType() == DOMNode::ELEMENT_NODE ) 
	{
	  DOMElement* currentElement = dynamic_cast< xercesc::DOMElement* >( currentNode );
	  char* name = XMLString::transcode( currentElement->getTagName() );
	  string elementName( name );
	  XMLString::release( &name ) ;
	  fConfigTables[ elementName ] = new ConfigurationTable( currentElement, fOutput, fDOMDocument );
	}
    }
}

ConfigurationTable*
ConfigurationTable::NewTable( const string& name )
{
  XMLCh* elementName = XMLString::transcode( name.c_str() );
  DOMElement* newElement = fDOMDocument->createElement( elementName );
  fDOMElement->appendChild( newElement );
  XMLString::release( &elementName );
  ConfigurationTable* newTable = new ConfigurationTable( newElement, fOutput, fDOMDocument );
  if( fConfigTables.count( name ) == 1 )
    throw;
  fConfigTables[ name ] = newTable;
  return newTable;
}

ConfigurationTable* 
ConfigurationTable::GetTable( const std::string& name )
{
  if( fConfigTables.count( name ) == 0 )
    throw;
  return fConfigTables[ name ];
}


int 
ConfigurationTable::GetI( const string& name )
{
  XMLCh* attributeName = XMLString::transcode( name.c_str() );
  const XMLCh* attributeValue = fDOMElement->getAttribute( attributeName );
  char* attributeValueChar = XMLString::transcode( attributeValue );
  stringstream value; 
  value << attributeValueChar;
  int result; 
  value >> result;
  XMLString::release( &attributeName );
  XMLString::release( &attributeValueChar );
  return result;
}

double 
ConfigurationTable::GetD( const string& name )
{
  XMLCh* attributeName = XMLString::transcode( name.c_str() );
  const XMLCh* attributeValue = fDOMElement->getAttribute( attributeName );
  char* attributeValueChar = XMLString::transcode( attributeValue );
  stringstream value;
  value.setf( ios::scientific, ios::floatfield );
  value.precision( 4 );
  value << attributeValueChar;
  int result; 
  value >> result;
  XMLString::release( &attributeName );
  XMLString::release( &attributeValueChar );
  return result;
}

string
ConfigurationTable::GetS( const string& name )
{
  XMLCh* attributeName = XMLString::transcode( name.c_str() );
  const XMLCh* attributeValue = fDOMElement->getAttribute( attributeName );
  char* attributeValueChar = XMLString::transcode( attributeValue );
  string result( attributeValueChar );
  XMLString::release( &attributeName );
  XMLString::release( &attributeValueChar );
  return result;
}

void 
ConfigurationTable::SetI( const std::string& name, const int value )
{
  XMLCh* attributeName = XMLString::transcode( name.c_str() );
  stringstream svalue;
  svalue << value;
  XMLCh* attributeValue = XMLString::transcode( svalue.str().c_str() );
  fDOMElement->setAttribute( attributeName, attributeValue );
  XMLString::release( &attributeName );
  XMLString::release( &attributeValue );
  return;
}

void 
ConfigurationTable::SetD( const std::string& name, const double value )
{
  XMLCh* attributeName = XMLString::transcode( name.c_str() );
  stringstream svalue;
  svalue.setf( ios::scientific, ios::floatfield );
  svalue.precision( 4 );
  svalue << value;
  XMLCh* attributeValue = XMLString::transcode( svalue.str().c_str() );
  fDOMElement->setAttribute( attributeName, attributeValue );
  XMLString::release( &attributeName );
  XMLString::release( &attributeValue );
  return;
}

void 
ConfigurationTable::SetS( const std::string& name, const std::string& value )
{
  XMLCh* attributeName = XMLString::transcode( name.c_str() );
  XMLCh* attributeValue = XMLString::transcode( value.c_str() );
  fDOMElement->setAttribute( attributeName, attributeValue );
  XMLString::release( &attributeName );
  XMLString::release( &attributeValue );
  return;
}
