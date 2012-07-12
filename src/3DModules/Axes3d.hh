////////////////////////////////////////////////////////////////////////
/// \class Viewer::Frames::Axes3d
///
/// \brief   
///
/// \author Olivia Wasalski <wasalski@triumf.ca>
///			    <oliviawasalski@triumf.ca>
///
/// REVISION HISTORY:\n
/// 	12/07/11 : Olivia Wasalski - New File \n
///
/// \details 	
///
////////////////////////////////////////////////////////////////////////


#ifndef __Viewer_Frames_Axes3d__
#define __Viewer_Frames_Axes3d__

#include <cstddef>
#include <TVector3.h>
#include <Viewer/Colour.hh>
#include <Viewer/Module3d.hh>

namespace Viewer {
	namespace GUIs {
		class PersistLabel;
	}; // namespace GUIs

namespace Frames {

class Axes3d : public Module3d {

public:
    Axes3d( double length );
	virtual ~Axes3d() { }
	inline std::string GetName();
	inline std::string GetTableName();
	void CreateGUIObjects( GUIManager& g, const sf::Rect< double >& optionsArea );
	void LoadConfiguration( const ConfigurationTable* configTable );
	void SaveConfiguration( ConfigurationTable* configTable );
	void EventLoop();
    void Render( const RenderState& renderState );

private:
    void RenderAxis( const TVector3& farPoint, Colour& colour );

    Colour fXColour;
    Colour fYColour;
    Colour fZColour;

    TVector3 fXPoint;
    TVector3 fYPoint;
    TVector3 fZPoint;

	bool fDisplay;
	GUIs::PersistLabel* fDisplayGUI;

}; // class Axes3d

////////////////////////////////////////////////////////////////////////
// Inline methods
////////////////////////////////////////////////////////////////////////
std::string Axes3d::GetName()
{
	return "Axes";
}

std::string Axes3d::GetTableName()
{
	return "Axes";
}

}; // namespace Frames
}; // namespace Viewer

#endif // __Viewer_Frames_Axes3d__
