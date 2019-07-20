// Copyright (c) 2016-2019 The PIVX developers
// Copyright (c) 2019 The Extreme Private Masternode developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef EXTREME_PRIVATE_MASTERNODE_ACCUMULATORMAP_H
#define EXTREME_PRIVATE_MASTERNODE_ACCUMULATORMAP_H

#include "libzerocoin/Accumulator.h"
#include "libzerocoin/Coin.h"

//A map with an accumulator for each denomination
class AccumulatorMap
{
private:
    libzerocoin::ZerocoinParams* params;
    std::map<libzerocoin::CoinDenomination, std::unique_ptr<libzerocoin::Accumulator> > mapAccumulators;
public:
    explicit AccumulatorMap(libzerocoin::ZerocoinParams* params);
    bool Load(uint256 nCheckpoint);
    bool Accumulate(const libzerocoin::PublicCoin& pubCoin, bool fSkipValidation = false);
    libzerocoin::Accumulator GetAccumulator(libzerocoin::CoinDenomination denom);
    CBigNum GetValue(libzerocoin::CoinDenomination denom);
    uint256 GetCheckpoint();
    void Reset();
    void Reset(libzerocoin::ZerocoinParams* params2);
};
#endif //EXTREME_PRIVATE_MASTERNODE_ACCUMULATORMAP_H
