////////////////////////////////////////////////////////////////////
// Last svn revision: $Id$
////////////////////////////////////////////////////////////////////
/// \class Viewer:BitManip
///
/// \brief  Class for useful bit manipulation functions
///          
/// \author Gabriel D. Orebi Gann <orebi@hep.upenn.edu>
///
/// REVISION HISTORY: P G Jones <p.g.jones@qmul.ac.uk> : Ported to snogoggles.\n
///
///  \detail  This class contains some useful functions for bit
///           manipulation, including getting PMT crate/card/channel
///           numbers from the LCN or cell number, and vice versa.
///           NB lcn = 512*iCrate + 32*iCard + iChannel
///
////////////////////////////////////////////////////////////////////
#ifndef __Viewer_BitManip__
#define __Viewer_BitManip__

#include <Rtypes.h>

namespace Viewer {

class BitManip {
public:

  BitManip();
  virtual ~BitManip();

  static int GetCCC(int lcn);
  static int GetCrate(int lcn);
  static int GetChannel(int lcn);
  static int GetCard(int lcn);

  static int GetCCCC(int lcn, int cell);
  static int GetLCN(int cccc);
  static int GetLCN(UInt_t icrate, UInt_t icard, UInt_t ichan);
  static int GetCell(int cccc);

  static int GetCCCwCell(int cccc);
  static int GetCratewCell(int cccc);
  static int GetChannelwCell(int cccc);
  static int GetCardwCell(int cccc);

  static int GetBits(int arg, int loc, int n); // returns n bits at location loc in arg
  static UInt_t GetBits(UInt_t arg, int loc, int n); // returns n bits at location loc in arg
  static ULong64_t GetBits(ULong64_t arg, int loc, int n); // returns n bits at location loc in arg
  static int ClearBit(int arg, int newbit);
  static int SetBit(int arg, int newbit);
  static int SetBits(int arg, int loc, int val);// sets bits from (least sig) location loc in arg
  static bool TestBit(unsigned int word, int bit);
  static bool TestBit(int word, int bit);
  static int AndWords(int BitManip, int mask); // Bitwise & of the arguments
  static bool TestMask(int BitManip, int mask); // Logical test of BitManip against mask
  static unsigned int FlipBit(unsigned int arg, int bit);
  static unsigned short FlipBit(unsigned short arg, int bit);
  void CopyFlipBit(int word, int bit, int &arg, int newbit); // test bit in word and set newbit in arg
  void CopyFlipSameBit(int word, int &arg, int newbit); // test bit in word and set newbit in arg
  static bool CheckLength(int arg, int length);
  static bool CheckLength(UInt_t arg, int length);
};

} // namespace Viewer

#endif

