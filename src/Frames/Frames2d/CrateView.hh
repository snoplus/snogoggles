////////////////////////////////////////////////////////////////////////
/// \class Viewer::Frames::CrateView
///
/// \brief   Displays information in crates from events
///
/// \author  Ken Clark <k.clark1@physics.ox.ac.uk>
///
/// REVISION HISTORY:\n
///     5/07/11 : K. Clark - added \n
///
/// \detail  Do my best to copy XSNOED view for better or worse.
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_CrateView__
#define __Viewer_CrateView__
#endif

#include <Viewer/Frame.hh>
#include <Viewer/Shape.hh>
#include <Viewer/ProjectionImage.hh>
#include <Viewer/Text.hh>

namespace Viewer {
namespace GUIs
{
  class MapArea;
}
  namespace Frames {

    class CrateView: public Frame {
      
    public:
      void Initialise();
      virtual void Render2d(RWWrapper& windowApp);
      virtual void Render3d();
      virtual void EventLoop();
      void SaveConfiguration(ConfigurationTable& configTable);
      virtual std::string GetName(){return CrateView::Name();}
      static std::string Name(){return std::string("CrateView");}

    private:
      
      sf::Rect<double> fProjectArea; 
      ProjectionImage fImage;

      Text fInfoText;
      GUIs::MapArea* fMapArea; 
    };



  }//Viewer namespace
}//Frames namespace
