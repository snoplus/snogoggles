#include <Viewer/SerializableFactory.hh>

namespace Viewer {

SerializableFactory* SerializableFactory::fInstance = NULL;

SerializableFactory* SerializableFactory::GetInstance()
{
    if( fInstance == NULL )
        fInstance = new SerializableFactory();

    return fInstance;
}

}; // namespace Viewer
