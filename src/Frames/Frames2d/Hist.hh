////////////////////////////////////////////////////////////////////////
/// \class Viewer::Frames::Hist
///
/// \brief   Displays histogram of information from events
///
/// \author  Ken Clark <k.clark1@physics.ox.ac.uk>
///
/// REVISION HISTORY:\n
///     5/07/11 : K. Clark - added \n
///
/// \detail  I'll get back to you on that.
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_Hist__
#define __Viewer_Hist__
#endif

#include <Viewer/Frame.hh>
#include <Viewer/Shape.hh>
#include <Viewer/Text.hh>

namespace Viewer {
  namespace Frames {

    class Hist: public Frame {
      
    public:
      void Initialise();
      virtual void Render2d(RWWrapper& windowApp);
      virtual void Render3d();
      virtual void EventLoop();
      void SaveConfiguration(ConfigurationTable& configTable);
      void LoadConfiguration(ConfigurationTable& configTable);
      virtual std::string GetName(){return Hist::Name();}
      static std::string Name(){return std::string("Hist");}

    private:
      Shape fHistBox;
      //bool fState;
      Text fMessage;
    };



  }//Viewer namespace
}//Frames namespace
