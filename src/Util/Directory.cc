#include <dirent.h>
using namespace std;

#include <Viewer/Directory.hh>

vector<string> 
Viewer::GetFilesInDirectory( const string& folderPath )
{
  vector<string> files;
  DIR *dp = opendir( folderPath.c_str() );
  struct dirent *dirp;
  if (dp != NULL) 
    {
      dirp = readdir( dp );
      while( dirp != NULL )
        {
          if( string( dirp->d_name ) != string(".") && string( dirp->d_name ) !=string("..") )
            files.push_back( string( dirp->d_name ) );
          dirp = readdir( dp );
        }    
    }
  return files;
}
