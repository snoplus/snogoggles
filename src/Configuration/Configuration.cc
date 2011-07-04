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
	      if( elementName == string( "Viewer" ) )
		fViewerTable = new ConfigurationTable( currentElement, fOutput, fDOMDocument );
	      else
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
  if( name == string( "Viewer" ) )
    fViewerTable = new ConfigurationTable( newElement, fOutput, fDOMDocument );
  else if( name == string( "Frame" ) )
    fConfigTables.push_back( new ConfigurationTable( newElement, fOutput, fDOMDocument ) );
  else
    throw;
}
