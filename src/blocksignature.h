// Copyright (c) 2016-2019 The PIVX developers
// Copyright (c) 2019 The Extreme Private Masternode developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef EXTREME_PRIVATE_MASTERNODE_BLOCKSIGNATURE_H
#define EXTREME_PRIVATE_MASTERNODE_BLOCKSIGNATURE_H

#include "key.h"
#include "primitives/block.h"
#include "keystore.h"

bool SignBlockWithKey(CBlock& block, const CKey& key);
bool SignBlock(CBlock& block, const CKeyStore& keystore);
bool CheckBlockSignature(const CBlock& block);

#endif //EXTREME_PRIVATE_MASTERNODE_BLOCKSIGNATURE_H
