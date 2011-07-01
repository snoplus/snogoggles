////////////////////////////////////////////////////////////////////////
/// \file SNOGoggles
///
/// \brief   Entry point to SNOGoggles viewer
///
/// \author  Phil Jones <p.jones22@physics.ox.ac.uk>
///
/// REVISION HISTORY:\n
///     29/06/11 : P.Jones - First Revision, new file. \n
///
/// \detail  The main function is defined here
///
////////////////////////////////////////////////////////////////////////
#include <Viewer/ViewerWindow.hh>
using namespace Viewer;

int main()
{

  ViewerWindow& viewer = ViewerWindow::GetInstance();

  viewer.Initialise();
  viewer.Run();
  viewer.Destruct();
  return 0;
}
