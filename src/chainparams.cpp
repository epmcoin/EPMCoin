// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2019 The PIVX developers
// Copyright (c) 2019 The Extreme Private Masternode developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "libzerocoin/Params.h"
#include "chainparams.h"
#include "random.h"
#include "util.h"
#include "utilstrencodings.h"

#include <assert.h>

#include <boost/assign/list_of.hpp>

using namespace std;
using namespace boost::assign;

struct SeedSpec6 {
	uint8_t addr[16];
	uint16_t port;
};

#include "chainparamsseeds.h"

/**
 * Main network
 */

 //! Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress>& vSeedsOut, const SeedSpec6* data, unsigned int count)
{
	// It'll only connect to one or two seed nodes because once it connects,
	// it'll get a pile of addresses with newer timestamps.
	// Seed nodes are given a random 'last seen time' of between one and two
	// weeks ago.
	const int64_t nOneWeek = 7 * 24 * 60 * 60;
	for (unsigned int i = 0; i < count; i++) {
		struct in6_addr ip;
		memcpy(&ip, data[i].addr, sizeof(ip));
		CAddress addr(CService(ip, data[i].port));
		addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
		vSeedsOut.push_back(addr);
	}
}

//   What makes a good checkpoint block?
// + Is surrounded by blocks with reasonable timestamps
//   (no blocks before with a timestamp after, none after with
//    timestamp before)
// + Contains no strange transactions
static Checkpoints::MapCheckpoints mapCheckpoints =
boost::assign::map_list_of
(0, uint256("0x000009e75b044669750ce4c7fd8d497f0cac5a1100a993442be863c1c6e2bf51"))
(150, uint256("0x000000c6b9b69f9a343776e8fac39bddb322fb06ba5bc43151ebee540edf4906"))
(641, uint256("0x062fb3b07673a719053816fe47bf836af24c0b5379488c19da6126de2b133c7d"))
(953, uint256("0xc83299437470670e41674b0c58dd6b6b4728ceed54e4ee7560b1c3566beef922"))
(1672, uint256("0x8d2246dc54d915de721b534522bd8c38167774c70715287d7b067f437146dfbd"))
(2548, uint256("0x5c043afaabdfb2ccd9797b4b2e60f8e039499afa30e16c01df95078ce1a92914"))
(3250, uint256("0x1bd610cf356ee460411ccbb5c217f2f3c1dbcf738fe13fdc8a6fbbbd2122434b"))
;
static const Checkpoints::CCheckpointData data = {
	&mapCheckpoints,
	1563356682, // * UNIX timestamp of last checkpoint block
	6464,    // * total number of transactions between genesis and last checkpoint
				//   (the tx=... number in the SetBestChain debug.log lines)
	2000        // * estimated number of transactions per day after checkpoint
};

static Checkpoints::MapCheckpoints mapCheckpointsTestnet =
boost::assign::map_list_of
(0, uint256("0x001"))
;
static const Checkpoints::CCheckpointData dataTestnet = {
	&mapCheckpointsTestnet,
	1560843157,
	2501682,
	250 };

static Checkpoints::MapCheckpoints mapCheckpointsRegtest =
boost::assign::map_list_of(0, uint256("0x001"));
static const Checkpoints::CCheckpointData dataRegtest = {
	&mapCheckpointsRegtest,
	1454124731,
	0,
	100 };

libzerocoin::ZerocoinParams* CChainParams::Zerocoin_Params() const
{
	assert(this);
	static CBigNum bnDecModulus = 0;
	if (!bnDecModulus)
		bnDecModulus.SetDec(zerocoinModulus);
	static libzerocoin::ZerocoinParams ZCParamsDec = libzerocoin::ZerocoinParams(bnDecModulus);

	return &ZCParamsDec;
}

class CMainParams : public CChainParams
{
public:
	CMainParams()
	{
		networkID = CBaseChainParams::MAIN;
		strNetworkID = "main";
		/**
		 * The message start string is designed to be unlikely to occur in normal data.
		 * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
		 * a large 4-byte int at any alignment.
		 */
		pchMessageStart[0] = 0xe2;
		pchMessageStart[1] = 0x66;
		pchMessageStart[2] = 0x2a;
		pchMessageStart[3] = 0x8d;
		vAlertPubKey = ParseHex("0000098d3ba6ba6e7423fa5cbd6a89e0a9a5348f88d472b44a5cb1a8b7ed2c1eaa665fc8dc4f012cb8241cc0b6afd6ca70c5f5448916e4e6f511bcd746ed57dc50");
		nDefaultPort = 2680;
		bnProofOfWorkLimit = ~uint256(0) >> 20; // Extreme Private Masternode starting difficulty is 1 / 2^12
		nSubsidyHalvingInterval = 210000;
		nMaxReorganizationDepth = 100;
		nEnforceBlockUpgradeMajority = 8100; // 75%
		nRejectBlockOutdatedMajority = 10260; // 95%
		nToCheckBlockUpgradeMajority = 10800; // Approximate expected amount of blocks in 7 days (1440*7.5)
		nMinerThreads = 0;
		nTargetTimespan = 1 * 60; // EXTREME_PRIVATE_MASTERNODE: 1 day
		nTargetSpacing = 1 * 60;  // EXTREME_PRIVATE_MASTERNODE: 1 minute
		nMaturity = 61;
		nMasternodeCountDrift = 20;
		nMaxMoneyOut = 80000000 * COIN;

		/** Height or Time Based Activations **/
		nLastPOWBlock = 200;
		nZerocoinStartHeight = 210;
		nZerocoinStartTime = 1563170400; // October 17, 2017 4:30:00 AM
		nBlockLastGoodCheckpoint = 210; //Last valid accumulator checkpoint
		nBlockZerocoinV2 = 210; //!> The block that zerocoin v2 becomes active - roughly Tuesday, May 8, 2018 4:00:00 AM GMT
		nBlockDoubleAccumulated = 0;

		// Public coin spend enforcement
		nPublicZCSpends = 300;

		/**
		 * Build the genesis block. Note that the output of the genesis coinbase cannot
		 * be spent as it did not originally exist in the database.
		 *
		 * CBlock(hash=00000ffd590b14, ver=1, hashPrevBlock=00000000000000, hashMerkleRoot=e0028e, nTime=1390095618, nBits=1e0ffff0, nNonce=28917698, vtx=1)
		 *   CTransaction(hash=e0028e, ver=1, vin.size=1, vout.size=1, nLockTime=0)
		 *     CTxIn(COutPoint(000000, -1), coinbase 04ffff001d01044c5957697265642030392f4a616e2f3230313420546865204772616e64204578706572696d656e7420476f6573204c6976653a204f76657273746f636b2e636f6d204973204e6f7720416363657074696e6720426974636f696e73)
		 *     CTxOut(nValue=50.00000000, scriptPubKey=0xA9037BAC7050C479B121CF)
		 *   vMerkleTree: e0028e
		 */
		const char* pszTimestamp = "Extreme Private Masternode Rise Today.";
		CMutableTransaction txNew;
		txNew.vin.resize(1);
		txNew.vout.resize(1);
		txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
		txNew.vout[0].nValue = 250 * COIN;
		txNew.vout[0].scriptPubKey = CScript() << ParseHex("04c10e83b2703ccf322f7dbd62dd5855ac7c10bd055814ce121ba32607d573b8810c02c0582aed05b4deb9c4b77b26d92428c61256cd42774babea0a073b2ed0c9") << OP_CHECKSIG;
		genesis.vtx.push_back(txNew);
		genesis.hashPrevBlock = 0;
		genesis.hashMerkleRoot = genesis.BuildMerkleTree();
		genesis.nVersion = 4;
		genesis.nAccumulatorCheckpoint = 0;
		genesis.nTime = 1563170400;
		genesis.nBits = 0x1e0ffff0;
		genesis.nNonce = 3569029;

		hashGenesisBlock = genesis.GetHash();

		assert(hashGenesisBlock == uint256("0x000009e75b044669750ce4c7fd8d497f0cac5a1100a993442be863c1c6e2bf51"));
		assert(genesis.hashMerkleRoot == uint256("0x39e25f74b38061a9abd0d00a145d48e408251510fbce88f82bb05b4c1a9ab7f7"));

		vSeeds.push_back(CDNSSeedData("1", "dnsseeder.epmcoin.io"));
		vSeeds.push_back(CDNSSeedData("2", "explorer.epmcoin.io"));
		vSeeds.push_back(CDNSSeedData("3", "node1.epmcoin.io"));
		vSeeds.push_back(CDNSSeedData("4", "node2.epmcoin.io"));
		vSeeds.push_back(CDNSSeedData("5", "node3.epmcoin.io"));
		vSeeds.push_back(CDNSSeedData("6", "node4.epmcoin.io"));
		vSeeds.push_back(CDNSSeedData("7", "node5.epmcoin.io"));
		vSeeds.push_back(CDNSSeedData("8", "node6.epmcoin.io"));
		vSeeds.push_back(CDNSSeedData("9", "node7.epmcoin.io"));
		vSeeds.push_back(CDNSSeedData("10", "node8.epmcoin.io"));
		vSeeds.push_back(CDNSSeedData("11", "node9.epmcoin.io"));
		vSeeds.push_back(CDNSSeedData("12", "node10.epmcoin.io"));
		vSeeds.push_back(CDNSSeedData("13", "node11.epmcoin.io"));
		vSeeds.push_back(CDNSSeedData("14", "node12.epmcoin.io"));
		vSeeds.push_back(CDNSSeedData("15", "node13.epmcoin.io"));
		vSeeds.push_back(CDNSSeedData("16", "node14.epmcoin.io"));
		vSeeds.push_back(CDNSSeedData("17", "node15.epmcoin.io"));
		vSeeds.push_back(CDNSSeedData("18", "node16.epmcoin.io"));
		vSeeds.push_back(CDNSSeedData("19", "node17.epmcoin.io"));
		vSeeds.push_back(CDNSSeedData("20", "node18.epmcoin.io"));
		vSeeds.push_back(CDNSSeedData("21", "node19.epmcoin.io"));
		vSeeds.push_back(CDNSSeedData("22", "node20.epmcoin.io"));
		vSeeds.push_back(CDNSSeedData("23", "node21.epmcoin.io"));
		vSeeds.push_back(CDNSSeedData("24", "node22.epmcoin.io"));
		vSeeds.push_back(CDNSSeedData("25", "node23.epmcoin.io"));
		vSeeds.push_back(CDNSSeedData("26", "node24.epmcoin.io"));
		vSeeds.push_back(CDNSSeedData("27", "node25.epmcoin.io"));
		vSeeds.push_back(CDNSSeedData("28", "node26.epmcoin.io"));
		vSeeds.push_back(CDNSSeedData("29", "node27.epmcoin.io"));
		vSeeds.push_back(CDNSSeedData("30", "node28.epmcoin.io"));
		vSeeds.push_back(CDNSSeedData("31", "node29.epmcoin.io"));
		vSeeds.push_back(CDNSSeedData("32", "node30.epmcoin.io"));
		vSeeds.push_back(CDNSSeedData("33", "node31.epmcoin.io"));
		vSeeds.push_back(CDNSSeedData("34", "node32.epmcoin.io"));
		vSeeds.push_back(CDNSSeedData("35", "node33.epmcoin.io"));
		vSeeds.push_back(CDNSSeedData("36", "node34.epmcoin.io"));
		vSeeds.push_back(CDNSSeedData("37", "node35.epmcoin.io"));
		vSeeds.push_back(CDNSSeedData("38", "node36.epmcoin.io"));
		vSeeds.push_back(CDNSSeedData("39", "node37.epmcoin.io"));
		vSeeds.push_back(CDNSSeedData("40", "node38.epmcoin.io"));
		vSeeds.push_back(CDNSSeedData("41", "node39.epmcoin.io"));
		vSeeds.push_back(CDNSSeedData("42", "node40.epmcoin.io"));
		vSeeds.push_back(CDNSSeedData("43", "node41.epmcoin.io"));
		vSeeds.push_back(CDNSSeedData("44", "node42.epmcoin.io"));
		vSeeds.push_back(CDNSSeedData("45", "node43.epmcoin.io"));
		vSeeds.push_back(CDNSSeedData("46", "node44.epmcoin.io"));
		vSeeds.push_back(CDNSSeedData("47", "node45.epmcoin.io"));
		vSeeds.push_back(CDNSSeedData("48", "node46.epmcoin.io"));
		vSeeds.push_back(CDNSSeedData("49", "node47.epmcoin.io"));
		vSeeds.push_back(CDNSSeedData("50", "node48.epmcoin.io"));
		vSeeds.push_back(CDNSSeedData("51", "node49.epmcoin.io"));
		vSeeds.push_back(CDNSSeedData("52", "node50.epmcoin.io"));
		vSeeds.push_back(CDNSSeedData("53", "node51.epmcoin.io"));
		vSeeds.push_back(CDNSSeedData("54", "node52.epmcoin.io"));
		vSeeds.push_back(CDNSSeedData("55", "node53.epmcoin.io"));
		vSeeds.push_back(CDNSSeedData("56", "node54.epmcoin.io"));
		vSeeds.push_back(CDNSSeedData("57", "node55.epmcoin.io"));
		vSeeds.push_back(CDNSSeedData("58", "node56.epmcoin.io"));
		vSeeds.push_back(CDNSSeedData("59", "node57.epmcoin.io"));
		vSeeds.push_back(CDNSSeedData("60", "node58.epmcoin.io"));
		vSeeds.push_back(CDNSSeedData("61", "node59.epmcoin.io"));
		vSeeds.push_back(CDNSSeedData("62", "node60.epmcoin.io"));
		vSeeds.push_back(CDNSSeedData("63", "node61.epmcoin.io"));
		vSeeds.push_back(CDNSSeedData("64", "node62.epmcoin.io"));
		vSeeds.push_back(CDNSSeedData("65", "node63.epmcoin.io"));
		vSeeds.push_back(CDNSSeedData("66", "node64.epmcoin.io"));
		vSeeds.push_back(CDNSSeedData("67", "node65.epmcoin.io"));
		vSeeds.push_back(CDNSSeedData("68", "node66.epmcoin.io"));
		vSeeds.push_back(CDNSSeedData("69", "node67.epmcoin.io"));
		vSeeds.push_back(CDNSSeedData("70", "node68.epmcoin.io"));
		vSeeds.push_back(CDNSSeedData("71", "node69.epmcoin.io"));
		vSeeds.push_back(CDNSSeedData("72", "node70.epmcoin.io"));
		vSeeds.push_back(CDNSSeedData("73", "node71.epmcoin.io"));
		vSeeds.push_back(CDNSSeedData("74", "node72.epmcoin.io"));
		vSeeds.push_back(CDNSSeedData("75", "node73.epmcoin.io"));
		vSeeds.push_back(CDNSSeedData("76", "node74.epmcoin.io"));
		vSeeds.push_back(CDNSSeedData("77", "node75.epmcoin.io"));
		vSeeds.push_back(CDNSSeedData("78", "node76.epmcoin.io"));
		vSeeds.push_back(CDNSSeedData("79", "node77.epmcoin.io"));
		vSeeds.push_back(CDNSSeedData("80", "node78.epmcoin.io"));
		vSeeds.push_back(CDNSSeedData("81", "node79.epmcoin.io"));
		vSeeds.push_back(CDNSSeedData("82", "node80.epmcoin.io"));
		vSeeds.push_back(CDNSSeedData("83", "node81.epmcoin.io"));
		vSeeds.push_back(CDNSSeedData("84", "node82.epmcoin.io"));
		vSeeds.push_back(CDNSSeedData("85", "node83.epmcoin.io"));
		vSeeds.push_back(CDNSSeedData("86", "node84.epmcoin.io"));
		vSeeds.push_back(CDNSSeedData("87", "node85.epmcoin.io"));
		vSeeds.push_back(CDNSSeedData("88", "node86.epmcoin.io"));
		vSeeds.push_back(CDNSSeedData("89", "node87.epmcoin.io"));
		vSeeds.push_back(CDNSSeedData("90", "node88.epmcoin.io"));
		vSeeds.push_back(CDNSSeedData("91", "node89.epmcoin.io"));
		vSeeds.push_back(CDNSSeedData("92", "node90.epmcoin.io"));
		vSeeds.push_back(CDNSSeedData("93", "node91.epmcoin.io"));
		vSeeds.push_back(CDNSSeedData("94", "node92.epmcoin.io"));
		vSeeds.push_back(CDNSSeedData("95", "node93.epmcoin.io"));
		vSeeds.push_back(CDNSSeedData("96", "node94.epmcoin.io"));
		vSeeds.push_back(CDNSSeedData("97", "node95.epmcoin.io"));
		vSeeds.push_back(CDNSSeedData("98", "node96.epmcoin.io"));
		vSeeds.push_back(CDNSSeedData("99", "node97.epmcoin.io"));
		vSeeds.push_back(CDNSSeedData("100", "node98.epmcoin.io"));
		vSeeds.push_back(CDNSSeedData("101", "node99.epmcoin.io"));
		vSeeds.push_back(CDNSSeedData("102", "node100.epmcoin.io"));


		base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 33);
		base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 65);
		base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 212);
		base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x02)(0x2D)(0x25)(0x33).convert_to_container<std::vector<unsigned char> >();
		base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x02)(0x21)(0x31)(0x2B).convert_to_container<std::vector<unsigned char> >();
		// 	BIP44 coin type is from https://github.com/satoshilabs/slips/blob/master/slip-0044.md
		base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0x77).convert_to_container<std::vector<unsigned char> >();

		convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

		fMiningRequiresPeers = true;
		fAllowMinDifficultyBlocks = false;
		fDefaultConsistencyChecks = false;
		fRequireStandard = true;
		fMineBlocksOnDemand = false;
		fSkipProofOfWorkCheck = false;
		fTestnetToBeDeprecatedFieldRPC = false;
		fHeadersFirstSyncingActive = false;

		nPoolMaxTransactions = 3;
		nBudgetCycleBlocks = 43200; //!< Amount of blocks in a months period of time (using 1 minutes per) = (60*24*30)
		strSporkKey = "04dad0bfcb1d698418530bcbe5b15486ee0a8cfaa7cac4b744fc22297b9e0ad8fe10fd9e762ffb2a9c907f541a61199850e4157135a707f15ce00e582aaa27b108";
		strObfuscationPoolDummyAddress = "Ecqoa53W9SmqJpJDnd2joFfsL8yXgCR7Tc";

		/** Zerocoin */
		zerocoinModulus = "25195908475657893494027183240048398571429282126204032027777137836043662020707595556264018525880784"
			"4069182906412495150821892985591491761845028084891200728449926873928072877767359714183472702618963750149718246911"
			"6507761337985909570009733045974880842840179742910064245869181719511874612151517265463228221686998754918242243363"
			"7259085141865462043576798423387184774447920739934236584823824281198163815010674810451660377306056201619676256133"
			"8441436038339044149526344321901146575444541784240209246165157233507787077498171257724679629263863563732899121548"
			"31438167899885040445364023527381951378636564391212010397122822120720357";
		nMaxZerocoinSpendsPerTransaction = 7; // Assume about 20kb each
		nMaxZerocoinPublicSpendsPerTransaction = 637; // Assume about 220 bytes each input
		nMinZerocoinMintFee = 1 * CENT; //high fee required for zerocoin mints
		nMintRequiredConfirmations = 20; //the maximum amount of confirmations until accumulated in 19
		nRequiredAccumulation = 1;
		nDefaultSecurityLevel = 100; //full security level for accumulators
		nZerocoinHeaderVersion = 4; //Block headers must be this version once zerocoin is active
		nZerocoinRequiredStakeDepth = 200; //The required confirmations for a zepm to be stakable

		nBudget_Fee_Confirmations = 6; // Number of confirmations for the finalization fee
		nProposalEstablishmentTime = 60 * 60 * 24; // Proposals must be at least a day old to make it into a budget
	}

	const Checkpoints::CCheckpointData& Checkpoints() const
	{
		return data;
	}
};
static CMainParams mainParams;

/**
 * Testnet (v3)
 */
class CTestNetParams : public CMainParams
{
public:
	CTestNetParams()
	{
		networkID = CBaseChainParams::TESTNET;
		strNetworkID = "test";
		pchMessageStart[0] = 0x45;
		pchMessageStart[1] = 0x76;
		pchMessageStart[2] = 0x65;
		pchMessageStart[3] = 0xba;
		vAlertPubKey = ParseHex("000010e83b2703ccf322f7dbd62dd5855ac7c10bd055814ce121ba32607d573b8810c02c0582aed05b4deb9c4b77b26d92428c61256cd42774babea0a073b2ed0c9");
		nDefaultPort = 51474;
		nEnforceBlockUpgradeMajority = 4320; // 75%
		nRejectBlockOutdatedMajority = 5472; // 95%
		nToCheckBlockUpgradeMajority = 5760; // 4 days
		nMinerThreads = 0;
		nTargetTimespan = 1 * 60; // EXTREME_PRIVATE_MASTERNODE: 1 day
		nTargetSpacing = 1 * 60;  // EXTREME_PRIVATE_MASTERNODE: 1 minute
		nLastPOWBlock = 200;
		nMaturity = 15;
		nMasternodeCountDrift = 4;
		nMaxMoneyOut = 43199500 * COIN;

		// Public coin spend enforcement
		nPublicZCSpends = 1106100;

		//! Modify the testnet genesis block so the timestamp is valid for a later start.
		genesis.nTime = 1454124731;
		genesis.nNonce = 2402015;

		hashGenesisBlock = genesis.GetHash();
		//assert(hashGenesisBlock == uint256("0x0000041e482b9b9691d98eefb48473405c0b8ec31b76df3797c74a78680ef818"));

		vFixedSeeds.clear();
		vSeeds.clear();
		vSeeds.push_back(CDNSSeedData("fuzzbawls.pw", "extreme_private_masternode-testnet.seed.fuzzbawls.pw"));
		vSeeds.push_back(CDNSSeedData("fuzzbawls.pw", "extreme_private_masternode-testnet.seed2.fuzzbawls.pw"));
		vSeeds.push_back(CDNSSeedData("warrows.dev", "testnet.dnsseed.extreme_private_masternode.warrows.dev"));

		base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 139); // Testnet extreme_private_masternode addresses start with 'x' or 'y'
		base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 19);  // Testnet extreme_private_masternode script addresses start with '8' or '9'
		base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 239);     // Testnet private keys start with '9' or 'c' (Bitcoin defaults)
		// Testnet extreme_private_masternode BIP32 pubkeys start with 'DRKV'
		base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x3a)(0x80)(0x61)(0xa0).convert_to_container<std::vector<unsigned char> >();
		// Testnet extreme_private_masternode BIP32 prvkeys start with 'DRKP'
		base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x3a)(0x80)(0x58)(0x37).convert_to_container<std::vector<unsigned char> >();
		// Testnet extreme_private_masternode BIP44 coin type is '1' (All coin's testnet default)
		base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0x01).convert_to_container<std::vector<unsigned char> >();

		convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

		fMiningRequiresPeers = true;
		fAllowMinDifficultyBlocks = true;
		fDefaultConsistencyChecks = false;
		fRequireStandard = true;
		fMineBlocksOnDemand = false;
		fTestnetToBeDeprecatedFieldRPC = true;

		nPoolMaxTransactions = 2;
		nBudgetCycleBlocks = 144; //!< Ten cycles per day on testnet
		strSporkKey = "04A8B319388C0F8588D238B9941DC26B26D3F9465266B368A051C5C100F79306A557780101FE2192FE170D7E6DEFDCBEE4C8D533396389C0DAFFDBC842B002243C";
		strObfuscationPoolDummyAddress = "y57cqfGRkekRyDRNeJiLtYVEbvhXrNbmox";
		nBudget_Fee_Confirmations = 3; // Number of confirmations for the finalization fee. We have to make this very short
									   // here because we only have a 8 block finalization window on testnet

		nProposalEstablishmentTime = 60 * 5; // Proposals must be at least 5 mns old to make it into a test budget
	}
	const Checkpoints::CCheckpointData& Checkpoints() const
	{
		return dataTestnet;
	}
};
static CTestNetParams testNetParams;

/**
 * Regression test
 */
class CRegTestParams : public CTestNetParams
{
public:
	CRegTestParams()
	{
		networkID = CBaseChainParams::REGTEST;
		strNetworkID = "regtest";
		pchMessageStart[0] = 0xa1;
		pchMessageStart[1] = 0xcf;
		pchMessageStart[2] = 0x7e;
		pchMessageStart[3] = 0xac;
		nEnforceBlockUpgradeMajority = 750;
		nRejectBlockOutdatedMajority = 950;
		nToCheckBlockUpgradeMajority = 1000;
		nMinerThreads = 1;
		nTargetTimespan = 24 * 60 * 60; // EXTREME_PRIVATE_MASTERNODE: 1 day
		nTargetSpacing = 1 * 60;        // EXTREME_PRIVATE_MASTERNODE: 1 minutes
		bnProofOfWorkLimit = ~uint256(0) >> 1;
		nLastPOWBlock = 250;
		nMaturity = 100;
		nMasternodeCountDrift = 4;
		//nModifierUpdateBlock = 0; //approx Mon, 17 Apr 2017 04:00:00 GMT
		nMaxMoneyOut = 43199500 * COIN;
		nZerocoinStartHeight = 300;
		nBlockZerocoinV2 = 300;
		nZerocoinStartTime = 1501776000;
		nBlockEnforceSerialRange = 1; //Enforce serial range starting this block
		nBlockRecalculateAccumulators = 999999999; //Trigger a recalculation of accumulators
		nBlockFirstFraudulent = 999999999; //First block that bad serials emerged
		nBlockLastGoodCheckpoint = 999999999; //Last valid accumulator checkpoint

		// Public coin spend enforcement
		nPublicZCSpends = 350;

		//! Modify the regtest genesis block so the timestamp is valid for a later start.
		genesis.nTime = 1454124731;
		genesis.nNonce = 2402015;

		hashGenesisBlock = genesis.GetHash();
		//assert(hashGenesisBlock == uint256("0x0000041e482b9b9691d98eefb48473405c0b8ec31b76df3797c74a78680ef818"));
		//assert(hashGenesisBlock == uint256("0x4f023a2120d9127b21bbad01724fdb79b519f593f2a85b60d3d79160ec5f29df"));

		vFixedSeeds.clear(); //! Testnet mode doesn't have any fixed seeds.
		vSeeds.clear();      //! Testnet mode doesn't have any DNS seeds.

		fMiningRequiresPeers = false;
		fAllowMinDifficultyBlocks = true;
		fDefaultConsistencyChecks = true;
		fRequireStandard = false;
		fMineBlocksOnDemand = true;
		fTestnetToBeDeprecatedFieldRPC = false;
	}
	const Checkpoints::CCheckpointData& Checkpoints() const
	{
		return dataRegtest;
	}
};
static CRegTestParams regTestParams;

/**
 * Unit test
 */
class CUnitTestParams : public CMainParams, public CModifiableParams
{
public:
	CUnitTestParams()
	{
		networkID = CBaseChainParams::UNITTEST;
		strNetworkID = "unittest";
		nDefaultPort = 51478;
		vFixedSeeds.clear(); //! Unit test mode doesn't have any fixed seeds.
		vSeeds.clear();      //! Unit test mode doesn't have any DNS seeds.

		fMiningRequiresPeers = false;
		fDefaultConsistencyChecks = true;
		fAllowMinDifficultyBlocks = false;
		fMineBlocksOnDemand = true;
	}

	const Checkpoints::CCheckpointData& Checkpoints() const
	{
		// UnitTest share the same checkpoints as MAIN
		return data;
	}

	//! Published setters to allow changing values in unit test cases
	virtual void setSubsidyHalvingInterval(int anSubsidyHalvingInterval) { nSubsidyHalvingInterval = anSubsidyHalvingInterval; }
	virtual void setEnforceBlockUpgradeMajority(int anEnforceBlockUpgradeMajority) { nEnforceBlockUpgradeMajority = anEnforceBlockUpgradeMajority; }
	virtual void setRejectBlockOutdatedMajority(int anRejectBlockOutdatedMajority) { nRejectBlockOutdatedMajority = anRejectBlockOutdatedMajority; }
	virtual void setToCheckBlockUpgradeMajority(int anToCheckBlockUpgradeMajority) { nToCheckBlockUpgradeMajority = anToCheckBlockUpgradeMajority; }
	virtual void setDefaultConsistencyChecks(bool afDefaultConsistencyChecks) { fDefaultConsistencyChecks = afDefaultConsistencyChecks; }
	virtual void setAllowMinDifficultyBlocks(bool afAllowMinDifficultyBlocks) { fAllowMinDifficultyBlocks = afAllowMinDifficultyBlocks; }
	virtual void setSkipProofOfWorkCheck(bool afSkipProofOfWorkCheck) { fSkipProofOfWorkCheck = afSkipProofOfWorkCheck; }
};
static CUnitTestParams unitTestParams;


static CChainParams* pCurrentParams = 0;

CModifiableParams* ModifiableParams()
{
	assert(pCurrentParams);
	assert(pCurrentParams == &unitTestParams);
	return (CModifiableParams*)&unitTestParams;
}

const CChainParams& Params()
{
	assert(pCurrentParams);
	return *pCurrentParams;
}

CChainParams& Params(CBaseChainParams::Network network)
{
	switch (network) {
	case CBaseChainParams::MAIN:
		return mainParams;
	case CBaseChainParams::TESTNET:
		return testNetParams;
	case CBaseChainParams::REGTEST:
		return regTestParams;
	case CBaseChainParams::UNITTEST:
		return unitTestParams;
	default:
		assert(false && "Unimplemented network");
		return mainParams;
	}
}

void SelectParams(CBaseChainParams::Network network)
{
	SelectBaseParams(network);
	pCurrentParams = &Params(network);
}

bool SelectParamsFromCommandLine()
{
	CBaseChainParams::Network network = NetworkIdFromCommandLine();
	if (network == CBaseChainParams::MAX_NETWORK_TYPES)
		return false;

	SelectParams(network);
	return true;
}
