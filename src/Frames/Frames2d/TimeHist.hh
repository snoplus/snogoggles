////////////////////////////////////////////////////////////////////////
/// \class Viewer::Frames::TimeHist
///
/// \brief   Displays histogram of time information from events
///
/// \author  Ken Clark <k.clark1@physics.ox.ac.uk>
///
/// REVISION HISTORY:\n
///     5/07/11 : K. Clark - added \n
///
/// \detail  I'll get back to you on that.
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_TimeHist__
#define __Viewer_TimeHist__
#endif

#include <Viewer/Frame.hh>
#include <Viewer/Shape.hh>
#include <Viewer/Text.hh>

namespace Viewer {
  namespace Frames {

    class TimeHist: public Frame {
      
    public:
      void Initialise();
      virtual void Render2d(RWWrapper& windowApp);
      virtual void Render3d();
      virtual void EventLoop();
      void SaveConfiguration(ConfigurationTable& configTable);
      virtual std::string GetName(){return TimeHist::Name();}
      static std::string Name(){return std::string("TimeHist");}

    private:
      int pmtTimes[400];
      Shape vertLine;
      Shape horizLine;
      Shape horizMarker1;
      Shape horizMarker2;
      Shape horizMarker3;
      Shape horizMarker4;
      Text horizLabel1;
      Text horizLabel2;
      Text horizLabel3;
      Text horizLabel4;
      Text vertLabel1;
      Text vertLabel2;
      Text vertLabel3;
      Text vertLabel4;
       Shape histBar;
      //Shape fHistBox;
      //bool fState;
      //Text fMessage;
    };



  }//Viewer namespace
}//Frames namespace
