////////////////////////////////////////////////////////////////////////
/// \class Viewer::FrameFactory
///
/// \brief   Allocates Frames
///
/// \author  Phil Jones <p.jones22@physics.ox.ac.uk>
///
/// REVISION HISTORY:\n
///     25/06/11 : P.Jones - First Revision, new file. \n
///
/// \detail  
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_FrameFactory__
#define __Viewer_FrameFactory__

#include <vector>
#include <string>
#include <map>

#include <Viewer/Frame.hh>
#include <Viewer/Factory.hh>

namespace Viewer
{

class FrameAllocBase
{
public:
  virtual Frame* New( RectPtr rect ) = 0;
};

template <class TDerived>
class FrameAlloc : public FrameAllocBase
{
public:
  virtual Frame* New( RectPtr rect ) { return new TDerived( rect ); };
};

class FrameFactory
{
public:   
  FrameFactory();
  inline Frame* New( const std::string &id, RectPtr rect );
  void Register( const std::string &id, FrameAllocBase *allocator );
  inline ~FrameFactory();
  inline std::vector<std::string> GetNames();

protected:
  std::map< std::string, FrameAllocBase* > table;
};

inline
FrameFactory::~FrameFactory()
{
  for( std::map< std::string, FrameAllocBase* >::iterator iTer = table.begin(); iTer != table.end(); iTer++ )
    delete iTer->second;
  table.clear();
}

inline Frame*
FrameFactory::New( const std::string& id, RectPtr rect )
{
  if( table.count(id) == 0 )
    throw FactoryUnknownID(id);
  else
    return table[id]->New( rect );
};

inline void
FrameFactory::Register( const std::string& id, FrameAllocBase* allocator )
{
  table[id] = allocator;
};

inline std::vector<std::string>
FrameFactory::GetNames()
{
  std::vector<std::string> names;
  for( std::map< std::string, FrameAllocBase* >::iterator iTer = table.begin(); iTer != table.end(); iTer++ )
    names.push_back( iTer->first );
  return names;
}

} // ::Viewer

#endif
