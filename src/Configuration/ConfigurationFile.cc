#include <sstream>
#include <sys/stat.h>
using namespace std;

#include <Viewer/ConfigurationFile.hh>
#include <Viewer/ConfigurationTable.hh>
using namespace Viewer;

#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/dom/DOM.hpp>
#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/util/XMLUni.hpp>
#include <xercesc/framework/LocalFileFormatTarget.hpp>
using namespace xercesc;


ConfigurationFile::ConfigurationFile( const string& filePath, bool output )
{
  fFilePath = filePath;
  fOutput = output;
  if( !fOutput ) // Reading
    {
      // Check file exists
      struct stat fileStatus;
      
      int iretStat = stat( fFilePath.c_str(), &fileStatus);
      if( iretStat != 0 )
        throw NoFileError( fFilePath );
      XercesDOMParser* fileParser = new XercesDOMParser;
      fileParser->setValidationScheme( XercesDOMParser::Val_Never );
      fileParser->setDoNamespaces( false );	   
      fileParser->setDoSchema( false );
      fileParser->setLoadExternalDTD( false );

      fileParser->parse( fFilePath.c_str() );
      fDOMDocument = fileParser->adoptDocument();
      fRootTable = new ConfigurationTable( fDOMDocument->getDocumentElement(), "root", fDOMDocument );
      delete fileParser; // no longer auses segFault, we've adopted the DOMDocument
    }
  else // Writing
    {
      XMLCh* core = XMLString::transcode( "core" );
      DOMImplementation * domImplementation =  DOMImplementationRegistry::getDOMImplementation( core );
      XMLString::release( &core );
      XMLCh* snog = XMLString::transcode( "SNOGoggles" );
      fDOMDocument = domImplementation->createDocument( NULL, snog, NULL );
      XMLString::release( &snog );
      fRootTable = new ConfigurationTable( fDOMDocument->getDocumentElement(), "root", fDOMDocument );
    }
}

ConfigurationFile::~ConfigurationFile()
{
  fDOMDocument->release(); // Apparently the correct xerces-c way
  delete fRootTable;
}

void 
ConfigurationFile::Save()
{
  XMLCh* ls = XMLString::transcode( "LS" );
  DOMImplementation* domImplementation = DOMImplementationRegistry::getDOMImplementation( ls );
  XMLString::release( &ls );
  DOMLSSerializer* serializer = reinterpret_cast<DOMImplementationLS*>( domImplementation )->createLSSerializer();
  DOMLSOutput *pOutput = reinterpret_cast<DOMImplementationLS*>( domImplementation )->createLSOutput();
  DOMConfiguration *pConfiguration = serializer->getDomConfig();
  // Have a nice output
  if( pConfiguration->canSetParameter( XMLUni::fgDOMWRTFormatPrettyPrint, true ) )
    pConfiguration->setParameter( XMLUni::fgDOMWRTFormatPrettyPrint, true );
 
  LocalFileFormatTarget* pTarget = new LocalFileFormatTarget( fFilePath.c_str() );
  pOutput->setByteStream(pTarget);
 
  serializer->write( fDOMDocument, pOutput );
  delete pTarget;
  pOutput->release();
  serializer->release();
}

const ConfigurationTable*
ConfigurationFile::GetTable() const
{
  if( fOutput == true )
    throw WrongModeError( "Configuration file is in write only mode." );
  return fRootTable;
}

ConfigurationTable*
ConfigurationFile::NewTable()
{
  if( fOutput == false )
    throw WrongModeError( "Configuration file is in read only mode." );
  return fRootTable;
}

int
ConfigurationFile::GetVersion() const
{
  return fRootTable->GetI( "version" );
}

void
ConfigurationFile::SetVersion( int version )
{
  fRootTable->SetI( "version", version );
}
