////////////////////////////////////////////////////////////////////////
/// \class Viewer::RenderState
///
/// \brief   Contains the current displayed data type
///
/// \author  Phil Jones <p.g.jones@qmul.ac.uk>
///
/// REVISION HISTORY:\n
///     19/02/12 : P.Jones - New file, first revision \n
///     07/05/12 : P.Jones - Update to use RIDS.\n
///     25/03/13 : P.Jones - RIDS refactor.\n
///
/// \detail  This class is used to define what data to show.
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_RenderState__
#define __Viewer_RenderState__

namespace Viewer
{
class Colour;

class RenderState
{
public:
  inline RenderState();

  inline RenderState( int source, 
                      int type );

  static void Initialise();

  void ChangeState( int source,
                    int type );
  void ChangeScaling( double fractionalMin,
                      double fractionalMax );

  inline int GetDataSource() const;
  inline int GetDataType() const;
  inline double GetScalingMin() const;
  inline double GetScalingMax() const;
  Colour GetDataColour( double data ) const;

  inline bool HasChanged() const;
  inline void Reset();

private:
  int fCurrentDataSource;
  int fCurrentDataType;

  double fCurrentScalingMin; /// < Lower numerical value to be displayed
  double fCurrentScalingMax; /// < Upper numerical value to be displayed
  bool fChanged; /// < Mark if data source/type has changed in the last frame
};

inline 
RenderState::RenderState()
{
  ChangeState( 0, 0 );
}

inline 
RenderState::RenderState( int source,
                          int type )
{
  ChangeState( source, type );
}

inline int
RenderState::GetDataSource() const
{
  return fCurrentDataSource;
}

inline int
RenderState::GetDataType() const
{
  return fCurrentDataType;
}

inline double
RenderState::GetScalingMin() const
{
  return fCurrentScalingMin;
}

inline double
RenderState::GetScalingMax() const
{
  return fCurrentScalingMax;
}

inline bool
RenderState::HasChanged() const
{
  return fChanged;
}

inline void
RenderState::Reset()
{
  fChanged = false;
}

} //::Viewer

#endif
