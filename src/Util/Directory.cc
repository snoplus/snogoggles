#include <dirent.h>
using namespace std;

#include <Viewer/Directory.hh>
#include <Viewer/StringUtils.hh>

vector<string> 
Viewer::GetFilesInDirectory( const string& folderPath,
                             const string& extension,
                             const string& omit )
{
  vector<string> files;
  DIR *dp = opendir( folderPath.c_str() );
  struct dirent *dirp;
  if (dp != NULL) 
    {
      dirp = readdir( dp );
      while( dirp != NULL )
        {
          string fileName = string( dirp->d_name );
          if( fileName != string(".") && fileName !=string("..") )
            {
              // Now check extension
              vector<string> parts;
              Viewer::StringUtils::SplitString( fileName, string("."), parts, false );
              if( extension == string("") || extension == parts[1] )
                files.push_back( parts[0].substr( omit.size() ) );
            }
          dirp = readdir( dp );
        }    
    }
  return files;
}
