////////////////////////////////////////////////////////////////////////
/// \class Viewer::Factory
///
/// \brief   Allocates instances of classes
///
/// \author  Stan Seibert, 
///          Ported from RAT by Phil Jones <p.jones22@physics.ox.ac.uk>
///
/// REVISION HISTORY:\n
///     29/06/11 : P.Jones - Ported from RAT. \n
///     05/07/11 : Olivia Wasalski - Added the NullAlloc and the OptionsAlloc. \n
///		04/08/11 : Olivia Wasalski - Removed OptionsAlloc, no longer needed. \n
///
/// \detail  As Brief.
///
////////////////////////////////////////////////////////////////////////
#ifndef __Viewer_Factory__
#define __Viewer_Factory__

#include <string>
#include <map>

namespace Viewer {

template <class T>
class AllocBase {
public:
  virtual T* New( ) = 0;
};

template <class T, class TDerived>
class Alloc : public AllocBase<T> {
public:
  virtual T* New( ) {
    return new TDerived;
  };
};

template <class T>
class NullAlloc : public AllocBase<T> {
public:
  virtual T* New( ) {
    return NULL;
  };
};

class FactoryUnknownID {
public:
  FactoryUnknownID(const std::string &_id) { id = _id; };
  std::string id;
};

template <class T>
class AllocTable : public std::map< std::string, AllocBase<T>* > 
{
};


template <class T>
class Factory {
public:
  T* New(const std::string &id ) {
    if (table.count(id) == 0)
      throw FactoryUnknownID(id);
    else
      return table[id]->New( );
  };

  void Register(const std::string &id, AllocBase<T> *allocator) {
    table[id] = allocator;
  };

  ~Factory() {
    for( typename AllocTable<T>::iterator iTer = table.begin(); iTer != table.end(); iTer++ )
      delete iTer->second;
    table.clear();
  }

protected:
  AllocTable<T> table;
};


template <class T>
class GlobalFactory {
public:
  static T* New(const std::string &id) { return factory.New(id); };
  static void Register(const std::string &id, AllocBase<T> *allocator) {
    factory.Register(id, allocator);
  };


protected:
  static Factory<T> factory;
};

template<class T>
Factory<T> GlobalFactory<T>::factory;

} // namespace Viewer

#endif // __Viewer_Factory__
