////////////////////////////////////////////////////////////////////////
/// \class Viewer::PMTWrapper
///
/// \brief   Wraps RAT PMTs.
///
/// \author Olivia Wasalski <wasalski@triumf.ca>
///			    <oliviawasalski@triumf.ca>
///
/// REVISION HISTORY:\n
/// 	07/07/11 : Olivia Wasalski - New File \n
///
/// \details 	
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_PMTWrapper__
#define __Viewer_PMTWrapper__

#include <RAT/DS/PMTCal.hh>
#include <RAT/DS/PMTUnCal.hh>

namespace RAT {
    namespace DS {
        class PMTProperties;
    };
};

namespace Viewer {

class PMTWrapper {
public:
    virtual Int_t GetID() const = 0;
    virtual float GetsQHS() const = 0;
    virtual float GetsQHL() const = 0;
    virtual float GetsQLX() const = 0;
    virtual float GetCharge() const = 0; 
    virtual TVector3 GetPos(RAT::DS::PMTProperties * pmtlist) const = 0;
    virtual unsigned short GetCellID() const = 0;
    virtual char GetChanFlags() const = 0;
};

class PMTUnCalWrapper : public PMTWrapper {
public:
    PMTUnCalWrapper( RAT::DS::PMTUnCal* pmt ) { fPMTUnCal = pmt; }
    virtual Int_t GetID() const { return fPMTUnCal->GetID(); }
    virtual float GetsQHS() const { return fPMTUnCal->GetsQHS(); }
    virtual float GetsQHL() const { return fPMTUnCal->GetsQHL(); }
    virtual float GetsQLX() const { return fPMTUnCal->GetsQLX(); }
    virtual float GetCharge() const { return fPMTUnCal->GetCharge(); }
    virtual TVector3 GetPos(RAT::DS::PMTProperties * pmtlist) const 
        { return fPMTUnCal->GetPos( pmtlist ); }
    virtual unsigned short GetCellID() const { return fPMTUnCal->GetCellID(); }
    virtual char GetChanFlags() const { return fPMTUnCal->GetChanFlags(); }
private:
    RAT::DS::PMTUnCal* fPMTUnCal;
};

class PMTCalWrapper : public PMTWrapper {
public:
    PMTCalWrapper( RAT::DS::PMTCal* pmt ) { fPMTCal = pmt; }
    virtual Int_t GetID() const { return fPMTCal->GetID(); }
    virtual float GetsQHS() const { return fPMTCal->GetsQHS(); }
    virtual float GetsQHL() const { return fPMTCal->GetsQHL(); }
    virtual float GetsQLX() const { return fPMTCal->GetsQLX(); }
    virtual float GetCharge() const { return fPMTCal->GetCharge(); }
    virtual TVector3 GetPos(RAT::DS::PMTProperties * pmtlist) const 
        { return fPMTCal->GetPos( pmtlist ); }
    virtual unsigned short GetCellID() const { return fPMTCal->GetCellID(); }
    virtual char GetChanFlags() const { return fPMTCal->GetChanFlags(); }
private:
    RAT::DS::PMTCal* fPMTCal;
};

};

#endif // __Viewer_PMTWrapper__
