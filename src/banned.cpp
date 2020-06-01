// barrystyle 24022020
// banned inputs list
#include "main.h"

typedef std::map<uint256, int> BannedInputs;

const BannedInputs bannedFunds = 
{
    {
	    
    }
};

bool areBannedInputs(uint256 txid, int vout) {
  for (auto inputs : bannedFunds)
    if (inputs.first == txid && inputs.second == vout)
      return true;
  return false;
}
