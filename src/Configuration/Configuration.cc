#include <sstream>
using namespace std;

#include <Viewer/Configuration.hh>
#include <Viewer/ConfigurationTable.hh>
using namespace Viewer;

#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/dom/DOM.hpp>
#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/util/XMLUni.hpp>
#include <xercesc/framework/LocalFileFormatTarget.hpp>
using namespace xercesc;


Configuration::Configuration( bool output )
{
  stringstream configFileName;
  configFileName << getenv( "VIEWERROOT" ) << "/snogoggles.xml";

  fOutput = output;
  if( !fOutput ) // Reading
    {
      XercesDOMParser* fileParser = new XercesDOMParser;
      fileParser->setValidationScheme( XercesDOMParser::Val_Never );
      fileParser->setDoNamespaces( false );	   
      fileParser->setDoSchema( false );
      fileParser->setLoadExternalDTD( false );

      fileParser->parse( configFileName.str().c_str() );
      fDOMDocument = fileParser->getDocument();
      fRootElement = fDOMDocument->getDocumentElement();

      // Now extract config tables
      DOMNodeList* children = fRootElement->getChildNodes();
      for( XMLSize_t ix = 0; ix < children->getLength(); ++ix ) // Pre increment to save memory
	{
	  DOMNode* currentNode = children->item(ix);
	  if( currentNode->getNodeType() && currentNode->getNodeType() == DOMNode::ELEMENT_NODE ) 
	    {
	      DOMElement* currentElement = dynamic_cast< xercesc::DOMElement* >( currentNode );
	      char* name = xercesc::XMLString::transcode( currentElement->getTagName() );
	      string elementName( name );
	      xercesc::XMLString::release( &name ) ;
	      fConfigTables.push_back( new ConfigurationTable( currentElement, fOutput, fDOMDocument ) );
	    }
	}
    }
  else // Writing
    {
      XMLCh* core = XMLString::transcode( "core" );
      DOMImplementation * domImplementation =  DOMImplementationRegistry::getDOMImplementation( core );
      XMLString::release( &core );
      XMLCh* snog = XMLString::transcode( "SNOGoggles" );
      fDOMDocument = domImplementation->createDocument( NULL, snog, NULL );
      XMLString::release( &snog );
      fRootElement = fDOMDocument->getDocumentElement();
    }
}

void 
Configuration::SaveConfiguration()
{
  XMLCh* ls = XMLString::transcode( "LS" );
  DOMImplementation* domImplementation = DOMImplementationRegistry::getDOMImplementation( ls );
  XMLString::release( &ls );
  DOMWriter* serializer = reinterpret_cast<DOMImplementationLS*>( domImplementation)->createDOMWriter();
  serializer->setFeature( XMLUni::fgDOMWRTFormatPrettyPrint, true );
  stringstream configFileName;
  configFileName << getenv( "VIEWERROOT" ) << "/snogoggles.xml";
  XMLFormatTarget* target = new LocalFileFormatTarget( configFileName.str().c_str() );
  serializer->writeNode( target, *fDOMDocument );
}

ConfigurationTable*
Configuration::NewTable( const string& name )
{
  XMLCh* elementName = XMLString::transcode( name.c_str() );
  DOMElement* newElement = fDOMDocument->createElement( elementName );
  fRootElement->appendChild( newElement );
  XMLString::release( &elementName );
  if( name == string( "Frame" ) )
    {
      ConfigurationTable* newTable = new ConfigurationTable( newElement, fOutput, fDOMDocument );
      fConfigTables.push_back( newTable );
      return newTable;
    }
  else
    throw ConfigurationTable::NoTableError( name ); // TODO
}


int 
Configuration::GetI( const string& name )
{
  XMLCh* attributeName = XMLString::transcode( name.c_str() );
  const XMLCh* attributeValue = fRootElement->getAttribute( attributeName );
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
Configuration::GetD( const string& name )
{
  XMLCh* attributeName = XMLString::transcode( name.c_str() );
  const XMLCh* attributeValue = fRootElement->getAttribute( attributeName );
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
Configuration::GetS( const string& name )
{
  XMLCh* attributeName = XMLString::transcode( name.c_str() );
  const XMLCh* attributeValue = fRootElement->getAttribute( attributeName );
  char* attributeValueChar = XMLString::transcode( attributeValue );
  string result( attributeValueChar );
  XMLString::release( &attributeName );
  XMLString::release( &attributeValueChar );
  return result;
}

void 
Configuration::SetI( const std::string& name, const int value )
{
  XMLCh* attributeName = XMLString::transcode( name.c_str() );
  stringstream svalue;
  svalue << value;
  XMLCh* attributeValue = XMLString::transcode( svalue.str().c_str() );
  fRootElement->setAttribute( attributeName, attributeValue );
  XMLString::release( &attributeName );
  XMLString::release( &attributeValue );
  return;
}

void 
Configuration::SetD( const std::string& name, const double value )
{
  XMLCh* attributeName = XMLString::transcode( name.c_str() );
  stringstream svalue;
  svalue.setf( ios::scientific, ios::floatfield );
  svalue.precision( 4 );
  svalue << value;
  XMLCh* attributeValue = XMLString::transcode( svalue.str().c_str() );
  fRootElement->setAttribute( attributeName, attributeValue );
  XMLString::release( &attributeName );
  XMLString::release( &attributeValue );
  return;
}

void 
Configuration::SetS( const std::string& name, const std::string& value )
{
  XMLCh* attributeName = XMLString::transcode( name.c_str() );
  XMLCh* attributeValue = XMLString::transcode( value.c_str() );
  fRootElement->setAttribute( attributeName, attributeValue );
  XMLString::release( &attributeName );
  XMLString::release( &attributeValue );
  return;
}
