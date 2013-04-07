////////////////////////////////////////////////////////////////////////
/// \class Viewer::Module3dFactory
///
/// \brief   Factory singleton for all 3D modules
///
/// \author  Olivia Wasalski <oliviawasalski@gmail.ca>
///          Phil Jones <p.g.jones@qmul.ac.uk>
///
/// REVISION HISTORY:\n
///     06/04/13 : P.Jones - New file, first revision \n
///
/// \detail  Combination of all the previous separate 3D module factories.
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_Module3dFactory__
#define __Viewer_Module3dFactory__

#include <vector>
#include <string>
#include <map>

#include <Viewer/Module3d.hh>
#include <Viewer/Factory.hh>

namespace Viewer
{

class Module3dAllocBase
{
public:
  virtual Module3d* New( RectPtr rect ) = 0;
};

template <class TDerived>
class Module3dAlloc : public Module3dAllocBase
{
public:
  virtual Module3d* New( RectPtr rect ) { return new TDerived( rect ); };
};

class Module3dFactory
{
public:   
  Module3dFactory();
  inline Module3d* New( const std::string &id, RectPtr rect );
  void Register( const std::string &id, Module3dAllocBase *allocator );
  inline ~Module3dFactory();
  inline std::vector<std::string> GetNames();

protected:
  std::map< std::string, Module3dAllocBase* > table;
};

inline
Module3dFactory::~Module3dFactory()
{
  for( std::map< std::string, Module3dAllocBase* >::iterator iTer = table.begin(); iTer != table.end(); iTer++ )
    delete iTer->second;
  table.clear();
}

inline Module3d*
Module3dFactory::New( const std::string& id, RectPtr rect )
{
  if( table.count(id) == 0 )
    throw FactoryUnknownID(id);
  else
    return table[id]->New( rect );
};

inline void
Module3dFactory::Register( const std::string& id, Module3dAllocBase* allocator )
{
  table[id] = allocator;
};

inline std::vector<std::string>
Module3dFactory::GetNames()
{
  std::vector<std::string> names;
  for( std::map< std::string, Module3dAllocBase* >::iterator iTer = table.begin(); iTer != table.end(); iTer++ )
    names.push_back( iTer->first );
  return names;
}

} // ::Viewer

#endif
