////////////////////////////////////////////////////////////////////////
/// \class Viewer::InputBuffer
///
/// \brief   InputBuffer, lockless buffer for TWO threads
///
/// \author  Phil Jones <p.g.jones@qmul.ac.uk>
///
/// REVISION HISTORY:\n
///     27 Oct 2012 : P.Jones - First Revision, new file. \n
///
/// \detail  InputBuffer lockless buffer for a writing and reading thread
///          not safe for more than TWO threads.
///
////////////////////////////////////////////////////////////////////////


#ifndef __Viewer_InputBuffer_hh
#define __Viewer_InputBuffer_hh

namespace Viewer
{

template<class T>
class InputBuffer
{
public:
  /// Initialise the buffer (thread 2)
  inline InputBuffer( const int size = 5000 );
  /// Destroy the buffer (thread 2)
  inline ~InputBuffer();

  /// Push data onto the buffer (thread 1 only)
  inline bool Push( T& data );
  /// Pop data from the buffer (thread 2 only)
  inline bool Pop( T& data );

  /// Return the number of elements present in the buffer
  inline int GetNumElements() const { return ( fWrite - fRead ) % fSize; }
  /// Return the buffer size
  inline int GetSize() const { return fSize; }

private:
  T* fData;
  int fRead;
  int fWrite;
  const int fSize;
};

template<class T>
inline
InputBuffer<T>::InputBuffer( int size )
  : fSize( size )
{
  fRead = fWrite = 0;
  fData = new T[fSize];
}

template<class T>
inline
InputBuffer<T>::~InputBuffer()
{
  delete[] fData;
}

template<class T>
inline bool
InputBuffer<T>::Push( T& data )
{
  int next = ( fWrite + 1 ) % fSize;
  if( next != fRead )
    {
      fData[fWrite] = data;
      fWrite = next;
      return true;
    }
  else
    return false;
}

template<class T>
inline bool
InputBuffer<T>::Pop( T& data )
{
  if( fRead == fWrite )
    return false;
  else
    {
      data = fData[fRead];
      fRead = ( fRead + 1 ) % fSize;
      return true;
    }
}

} // ::Viewer

#endif
