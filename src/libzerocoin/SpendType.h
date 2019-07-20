// Copyright (c) 2018 The PIVX developers
// Copyright (c) 2019 The Extreme Private Masternode developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef EXTREME_PRIVATE_MASTERNODE_SPENDTYPE_H
#define EXTREME_PRIVATE_MASTERNODE_SPENDTYPE_H

#include <cstdint>

namespace libzerocoin {
    enum SpendType : uint8_t {
        SPEND, // Used for a typical spend transaction, zEPM should be unusable after
        STAKE, // Used for a spend that occurs as a stake
        MN_COLLATERAL, // Used when proving ownership of zEPM that will be used for masternodes (future)
        SIGN_MESSAGE // Used to sign messages that do not belong above (future)
    };
}

#endif //EXTREME_PRIVATE_MASTERNODE_SPENDTYPE_H
