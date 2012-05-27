#include <iostream>
using namespace std;

#include <Viewer/ConfigurationTable.hh>
using namespace Viewer;

#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/dom/DOM.hpp>
#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/util/XMLUni.hpp>
using namespace xercesc;


ConfigurationTable::ConfigurationTable( xercesc_3_1::DOMElement* element, 
                                        const string& name, 
                                        DOMDocument* domDocument )
{
  fDOMDocument = domDocument;
  fDOMElement = element;
  fConfigTables.clear();
  // Now extract config tables
  DOMNodeList* children = fDOMElement->getChildNodes();
  for( XMLSize_t ix = 0; ix < children->getLength(); ++ix ) // Pre increment to save memory
    {
      DOMNode* currentNode = children->item(ix);
      if( currentNode->getNodeType() && currentNode->getNodeType() == DOMNode::ELEMENT_NODE ) 
        {
          DOMElement* currentElement = dynamic_cast< xercesc::DOMElement* >( currentNode );
          char* xName = XMLString::transcode( currentElement->getTagName() );
          string elementName( xName );
          XMLString::release( &xName ) ;
          fConfigTables.push_back( new ConfigurationTable( currentElement, elementName, fDOMDocument ) );
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
  ConfigurationTable* newTable = new ConfigurationTable( newElement, name, fDOMDocument );
  fConfigTables.push_back( newTable );
  return newTable;
}

bool
ConfigurationTable::HasTable( const std::string& name ) const
{
  for( unsigned int iTable = 0; iTable < fConfigTables.size(); iTable++ )
    if( fConfigTables[iTable]->GetName() == name )
      return true;
  return false;
}

const ConfigurationTable*
ConfigurationTable::GetTable( const unsigned int iTable ) const
{
  return fConfigTables[iTable];
}

const ConfigurationTable*
ConfigurationTable::GetTable( const std::string& name ) const
{
  for( unsigned int iTable = 0; iTable < fConfigTables.size(); iTable++ )
    if( fConfigTables[iTable]->GetName() == name )
        return fConfigTables[iTable];
  return NULL;
}

bool
ConfigurationTable::Has( const string& name ) const
{
  XMLCh* attributeName = XMLString::transcode( name.c_str() );
  if( !fDOMElement->hasAttribute( attributeName ) )
    {
      XMLString::release( &attributeName );
      return false;
    }
  XMLString::release( &attributeName );
  return true;
}

string
ConfigurationTable::GetName() const
{
  char* name = XMLString::transcode( fDOMElement->getTagName() );
  string elementName( name );
  XMLString::release( &name );
  return elementName;
}

int 
ConfigurationTable::GetI( const string& name ) const
{
  XMLCh* attributeName = XMLString::transcode( name.c_str() );
  if( !fDOMElement->hasAttribute( attributeName ) )
    {
      XMLString::release( &attributeName );
      throw NoAttributeError( name );
    }
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
ConfigurationTable::GetD( const string& name ) const
{
  XMLCh* attributeName = XMLString::transcode( name.c_str() );
  if( !fDOMElement->hasAttribute( attributeName ) )
    {
      XMLString::release( &attributeName );
      throw NoAttributeError( name );
    }
  const XMLCh* attributeValue = fDOMElement->getAttribute( attributeName );
  char* attributeValueChar = XMLString::transcode( attributeValue );
  stringstream value;
  value.setf( ios::scientific, ios::floatfield );
  value.precision( 4 );
  value << attributeValueChar;
  double result; 
  value >> result;
  XMLString::release( &attributeName );
  XMLString::release( &attributeValueChar );
  return result;
}

string
ConfigurationTable::GetS( const string& name ) const
{
  XMLCh* attributeName = XMLString::transcode( name.c_str() );
  if( !fDOMElement->hasAttribute( attributeName ) )
    {
      XMLString::release( &attributeName );
      throw NoAttributeError( name );
    }
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
