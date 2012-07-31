////////////////////////////////////////////////////////////////////
// Last svn revision: $Id$
////////////////////////////////////////////////////////////////////
#include <Viewer/BitManip.hh>

#include <cmath>
#include <algorithm>
#include <vector>
#include <iostream>
using namespace std;

namespace Viewer {


BitManip::BitManip()
{
}

BitManip::~BitManip()
{
}

// Get the n bits at location l in arg, counting the first bit as ZERO
int BitManip::GetBits(int arg, int loc, int n)
{
  int shifted = arg >> loc;
  // Select the first (least significant) n of those bits
  int mask = ((ULong64_t)1 << n) - 1;
  int value = shifted & mask;
  return value;
}
// Version for a long int
ULong64_t BitManip::GetBits(ULong64_t arg, int loc, int n)
{
  ULong64_t shifted = arg >> loc;
  // Select the first (least significant) n of those bits
  ULong64_t mask = ((ULong64_t)1 << n) - 1;
  ULong64_t value = shifted & mask;
  return value;
}
// Version for an unsigned int
UInt_t BitManip::GetBits(UInt_t arg, int loc, int n)
{
  UInt_t shifted = arg >> loc;
  // Select the first (least significant) n of those bits
  UInt_t mask = ((ULong64_t)1 << n) - 1;
  UInt_t value = shifted & mask;
  return value;
}

// Sets the bit at `newbit' in `arg' to 0
int BitManip::ClearBit(int arg, int newbit)
{
  int mask = 1 << newbit;
  int value = (~mask) & arg;
  return value;
}

// Sets the bit at `newbit' in `arg' to 1
int BitManip::SetBit(int arg, int newbit)
{
  int mask = 1 << newbit;
  int value = mask | arg;
  return value;
}

// Set the bits from (least sig) location loc in arg to val
// counting the first bit as ZERO
int BitManip::SetBits(int arg, int loc, int val)
{
  int shifted = val << loc;
  int value = shifted | arg;
  return value;
}

// Tests the value of the bit at `bit' in `word'
bool BitManip::TestBit(int word, int bit)
{
  // shift the bits in word to the right by bit
  // to put the bit-th bit at the least sig position i.e. at bit 0
  int shifted = word >> bit;
  bool value;
  if(shifted&1){value = true;}
  else{value = false;}
  return value;
}

// Tests the value of the bit at `bit' in `word'
bool BitManip::TestBit(unsigned int word, int bit)
{
  // shift the bits in word to the right by bit
  // to put the bit-th bit at the least sig position i.e. at bit 0
  unsigned int shifted = word >> bit;
  bool value;
  if(shifted&1){value = true;}
  else{value = false;}
  return value;
}

unsigned short BitManip::FlipBit(unsigned short arg, int bit)
{
  unsigned short value = 0;
  if(BitManip::TestBit(arg,bit)){
    value = ClearBit(arg,bit);
  }
  else{
    value=SetBit(arg,bit);
  }
  return value;
}

unsigned int BitManip::FlipBit(unsigned int arg, int bit)
{
  unsigned int value = 0;
  if(BitManip::TestBit(arg,bit)){
    value = ClearBit(arg,bit);
  }
  else{
    value=SetBit(arg,bit);
  }
  return value;
}

// Test whether bit `bit' in `word' is set to 1 and, if so, set bit `newbit' in `arg' to 0
void BitManip::CopyFlipBit(int word, int bit, int &arg, int newbit)
{
  // If the bit in word fails the test (i.e. = 1), set the equiv bit in arg to 0
  if (BitManip::TestBit(word, bit))
    arg = BitManip::ClearBit(arg, newbit);
}

void BitManip::CopyFlipSameBit(int word, int &arg, int newbit)
{
  if (BitManip::TestBit(word, newbit))
    arg = BitManip::ClearBit(arg, newbit);
}


// Simple bitwise &
int BitManip::AndWords(int BitManip, int mask)
{
  return BitManip & mask;
}

// Check whether word `BitManip' passes the test of `mask'
// If the bits set in `mask' (i.e. those we are testing) are 0 in `BitManip', it's bad
// Therefore to pass, all bits set in `mask' must also be set in `BitManip'
// i.e. the result of bitwise-& should equal the original mask
bool BitManip::TestMask(int BitManip, int mask)
{
  bool value = false;
  if((BitManip&mask)==mask){value = true;}
  return value;
}


bool BitManip::CheckLength(int arg, int length)
{
  int checkval = BitManip::GetBits(arg,0,length);
  bool value = true;
  if(checkval != arg)value=false;
  return value;
}

bool BitManip::CheckLength(UInt_t arg, int length)
{
  UInt_t checkval = BitManip::GetBits(arg,0,length);
  bool value = true;
  if(checkval != arg)value=false;
  return value;
}







// Routines for accessing crate/card/channel/cell number, logical channel #, CCC #
  // lcn  = 512*icrate + 32*icard + ichan;
  // ccc  = 1024*icard + 32*icrate + ichan;
  // cccc = 8192*icrate + 512*icard + 16*ichan + icell;

int BitManip::GetCCC(int lcn)
{
  int icrate = BitManip::GetBits(lcn, 9, 5);
  int icard = BitManip::GetBits(lcn, 5, 4);
  int ichan = BitManip::GetBits(lcn, 0, 5);
  int test = 512*icrate + 32*icard + ichan;
  int ccc     = 1024*icard + 32*icrate + ichan;
  return ccc;
}

int BitManip::GetCard(int lcn)
{
  int icrate = BitManip::GetBits(lcn, 9, 5);
  int icard = BitManip::GetBits(lcn, 5, 4);
  int ichan = BitManip::GetBits(lcn, 0, 5);
  int test = 512*icrate + 32*icard + ichan;
  //int ccc     = 1024*icard + 32*icrate + ichan;
  return icard;
}

int BitManip::GetCrate(int lcn)
{
  int icrate = BitManip::GetBits(lcn, 9, 5);
  int icard = BitManip::GetBits(lcn, 5, 4);
  int ichan = BitManip::GetBits(lcn, 0, 5);
  int test = 512*icrate + 32*icard + ichan;
  //int ccc     = 1024*icard + 32*icrate + ichan;
  return icrate;
}

int BitManip::GetChannel(int lcn)
{
  int icrate = BitManip::GetBits(lcn, 9, 5);
  int icard = BitManip::GetBits(lcn, 5, 4);
  int ichan = BitManip::GetBits(lcn, 0, 5);
  int test = 512*icrate + 32*icard + ichan;
  //int ccc     = 1024*icard + 32*icrate + ichan;
  return ichan;
}

int BitManip::GetCCCC(int lcn, int cell)
{
  int icrate = BitManip::GetCrate(lcn);
  int icard = BitManip::GetCard(lcn);
  int ichan = BitManip::GetChannel(lcn);
  int icell = cell;
  int test = 512*icrate + 32*icard + ichan;
  int cccc = 8192*icrate + 512*icard + 16*ichan + icell;
  return cccc;  
}

int BitManip::GetLCN(int cccc)
{
  int icrate = BitManip::GetBits(cccc, 13, 5);
  int icard = BitManip::GetBits(cccc, 9, 4);
  int ichan = BitManip::GetBits(cccc, 4, 5);
  int icell = BitManip::GetBits(cccc, 0, 4);
  int lcn = 512*icrate + 32*icard + ichan;
  int test = 8192*icrate + 512*icard + 16*ichan + icell;
  return lcn;  
}

int BitManip::GetLCN(UInt_t icrate, UInt_t icard, UInt_t ichan)
{
  int lcn = 512*icrate + 32*icard + ichan;
  return lcn;
}

int BitManip::GetCell(int cccc)
{
  int icrate = BitManip::GetBits(cccc, 13, 5);
  int icard = BitManip::GetBits(cccc, 9, 4);
  int ichan = BitManip::GetBits(cccc, 4, 5);
  int icell = BitManip::GetBits(cccc, 0, 4);
  int test = 8192*icrate + 512*icard + 16*ichan + icell;
  return icell;  
}



int BitManip::GetCCCwCell(int cccc)
{
  int icrate = BitManip::GetBits(cccc, 13, 5);
  int icard = BitManip::GetBits(cccc, 9, 4);
  int ichan = BitManip::GetBits(cccc, 4, 5);
  int icell = BitManip::GetBits(cccc, 0, 4);
  int test = 8192*icrate + 512*icard + 16*ichan + icell;
  int ccc     = 1024*icard + 32*icrate + ichan;
  return ccc;
}

int BitManip::GetCardwCell(int cccc)
{
  int icrate = BitManip::GetBits(cccc, 13, 5);
  int icard = BitManip::GetBits(cccc, 9, 4);
  int ichan = BitManip::GetBits(cccc, 4, 5);
  int icell = BitManip::GetBits(cccc, 0, 4);
  int test = 8192*icrate + 512*icard + 16*ichan + icell;
  return icard;
}

int BitManip::GetCratewCell(int cccc)
{
  int icrate = BitManip::GetBits(cccc, 13, 5);
  int icard = BitManip::GetBits(cccc, 9, 4);
  int ichan = BitManip::GetBits(cccc, 4, 5);
  int icell = BitManip::GetBits(cccc, 0, 4);
  int test = 8192*icrate + 512*icard + 16*ichan + icell;
  return icrate;
}

int BitManip::GetChannelwCell(int cccc)
{
  int icrate = BitManip::GetBits(cccc, 13, 5);
  int icard = BitManip::GetBits(cccc, 9, 4);
  int ichan = BitManip::GetBits(cccc, 4, 5);
  int icell = BitManip::GetBits(cccc, 0, 4);
  int test = 8192*icrate + 512*icard + 16*ichan + icell;
  return ichan;
}

} // namespace Viewer

