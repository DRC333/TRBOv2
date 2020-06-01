// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2017 The PIVX developers
// Copyright (c) 2017-2020 The Phore developers
// Copyright (c) 2017-2020 The MonetaryUnit developers
// Copyright (c) 2018-2020 The StakeCube developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chainparams.h"
#include "random.h"
#include "bignum.h"
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
static bool regenerate = false;

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
    (0,      uint256("7ba6b76c01fb05fbb814af8379861f53c336fcd0ee5baaae7516552ef90622bd")) //Genesis
	(200,      uint256("661cf7bafcb768e2cc02a398a28d5183058fd0efb360e574afff5696accc0a52")) //PoW End  
    (58000,      uint256("0b9f3ea9f8baabe69f40695c7726d4c30d4cd09962ae59a80f879f1303c9df3e")) //New Wallet Update Due 15/08/19
    (100000,      uint256("f315084d51d5baabd114e1339830e97f8530fa1d0f5479d04ddd6ac2e0f2376b")) //Block reward change
    (200000,      uint256("1c372f50f10ee7aef43aab7e86649f40671b534c675ea55673b8126f329809aa")) //Block reward change
    (300000,      uint256("9f02fc6abf2b88e1f408eecd2e445ae35f34ac78cc2d0467c2593da493e8a11a")); //Block reward change
	

static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1588354951, // * UNIX timestamp of last checkpoint block
    300000,     // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the SetBestChain debug.log lines)
    1000        // * estimated number of transactions per day after checkpoint
};

static Checkpoints::MapCheckpoints mapCheckpointsTestnet =
    boost::assign::map_list_of(0, uint256("0x001"));
static const Checkpoints::CCheckpointData dataTestnet = {
    &mapCheckpointsTestnet,
    1559471400,
    0,
    250
};

static Checkpoints::MapCheckpoints mapCheckpointsRegtest =
    boost::assign::map_list_of(0, uint256("0x001"));
static const Checkpoints::CCheckpointData dataRegtest = {
    &mapCheckpointsRegtest,
    1559471400,
    0,
    100
};

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
        pchMessageStart[0] = 0x2b;
        pchMessageStart[1] = 0x4e;
        pchMessageStart[2] = 0x46;
        pchMessageStart[3] = 0xfb;
        vAlertPubKey = ParseHex("0449397babfa22d594551ee56d4ecffb95c583b8a17c887b463dc8a9b3e897126af004bdeac8cec4bc7d134069014320271bd5a8dca273a49788cfda7ea7ad02bd");
        nDefaultPort = 9533;
        bnProofOfWorkLimit = ~uint256(0) >> 1;
        nMaxReorganizationDepth = 100;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 0;
        nTargetTimespan = 1 * 60; // TRBO: 1 minute
        nTargetSpacing = 2 * 60;  // TRBO: 2 minutes
        nMaturity = 20;
        nMasternodeCountDrift = 20;
        nMaxMoneyOut = 10000000000 * COIN;

        /** Height or Time Based Activations **/
        nLastPOWBlock = 200;
        nModifierUpdateBlock = 1;

        /**
         * Build the genesis block. Note that the output of the genesis coinbase cannot
         * be spent as it did not originally exist in the database.
         *
            CBlock(hash=000005bc17744254b063fe3ee2fd568f89bd9d88c2f16fcba1c74c05625ae442, ver=1, hashPrevBlock=0000000000000000000000000000000000000000000000000000000000000000, hashMerkleRoot=81791231fefc74d7924ae1c1ff9e384f77285885f4a7a7c32570942834efd5d2, nTime=1538198000, nBits=1e0ffff0, nNonce=721427, vtx=1)
            CTransaction(hash=81791231fe, ver=1, vin.size=1, vout.size=1, nLockTime=0)
            CTxIn(COutPoint(0000000000000000000000000000000000000000000000000000000000000000, 4294967295), coinbase 04ffff001d0104147374616b65637562654d4e203239303932303138)
            CTxOut(nValue=0.00000000, scriptPubKey=0457c56ed69a1f42398804504fcab8)
         */
        const char* pszTimestamp = "TRBO Rebirth started 3rd June 2019 - Spare a Moment?";
        CMutableTransaction txNew;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].nValue = 0 * COIN;
        txNew.vout[0].scriptPubKey = CScript() << ParseHex("04a3318945c8b48e1f2fc5c1ebd68ce5935e794a97a802a24c03641e99984e5b81f8bf84604bec3dfd3abb0374bffa555d30c5ed9eb3d38cd24586b33fc95e75ef") << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime = 1559765647;
        genesis.nBits = 504365040;
        genesis.nNonce = 5594247;

        hashGenesisBlock = genesis.GetHash();
        if (regenerate) {
            hashGenesisBlock = uint256S("");
            genesis.nNonce = 0;
            if (true && (genesis.GetHash() != hashGenesisBlock)) {
                uint256 hashTarget = CBigNum().SetCompact(genesis.nBits).getuint256();
                while (genesis.GetHash() > hashTarget)
                {
                    ++genesis.nNonce;
                    if (genesis.nNonce == 0)
                    {
                        ++genesis.nTime;
                    }
                }
                std::cout << "// Mainnet ---";
                std::cout << " nonce: " << genesis.nNonce;
                std::cout << " time: " << genesis.nTime;
                std::cout << " hash: " << genesis.GetHash().ToString().c_str();
                std::cout << " merklehash: "  << genesis.hashMerkleRoot.ToString().c_str() <<  "\n";
            }
        } else {
            LogPrintf("Mainnet ---\n");
            LogPrintf(" nonce: %u\n", genesis.nNonce);
            LogPrintf(" time: %u\n", genesis.nTime);
            LogPrintf(" hash: %s\n", genesis.GetHash().ToString().c_str());
            LogPrintf(" merklehash: %s\n", genesis.hashMerkleRoot.ToString().c_str());
        assert(hashGenesisBlock == uint256("7ba6b76c01fb05fbb814af8379861f53c336fcd0ee5baaae7516552ef90622bd"));
        assert(genesis.hashMerkleRoot == uint256("679bbc54b19f91f7f5e06c5db31c3330f44fd79ca1a34da46a8224151aff7faa"));
        }
        
        vSeeds.push_back(CDNSSeedData("94.177.242.241", "94.177.242.241"));
        vSeeds.push_back(CDNSSeedData("185.35.64.141", "185.35.64.141"));
        vSeeds.push_back(CDNSSeedData("94.177.251.97", "94.177.251.97"));
        
        // TRBO addresses start with 'T'
        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 65);
        // TRBO script addresses start with '2'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 3);
        // TRBO private keys start with 'P'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 55);
        // TRBO BIP32 pubkeys start with 'xpub' (Bitcoin defaults)
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x88)(0xB2)(0x1E).convert_to_container<std::vector<unsigned char> >();
        // TRBO BIP32 prvkeys start with 'xprv' (Bitcoin defaults)
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x88)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >();
        // TRBO BIP44 coin type is '222' (0x800000de)
        nExtCoinType = 222;

        bech32_hrp = "tr";

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = false;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fSkipProofOfWorkCheck = true;
        fTestnetToBeDeprecatedFieldRPC = false;
        fHeadersFirstSyncingActive = false;

        nPoolMaxTransactions = 3;
        strSporkKey = "04db9cce4fe5919db582be63f4b4c6820546fa2028336165c8baf946bc3068a710a3ee6c9b7c214a7c1b4e6ae1cfd949dc022b0a901f68937746ef809983407adb";
        strSporkKeyTemp = "";
        strObfuscationPoolDummyAddress = "TTuXaT4YMB8exQeyk9khGy2nLLunvEgsLn";
        nBudgetFeeConfirmations = 6; // Number of confirmations for the finalization fee
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
        pchMessageStart[0] = 0x41;
        pchMessageStart[1] = 0x4d;
        pchMessageStart[2] = 0x5e;
        pchMessageStart[3] = 0x78;
        vAlertPubKey = ParseHex("");
        nDefaultPort = 9544;
        nEnforceBlockUpgradeMajority = 51;
        nRejectBlockOutdatedMajority = 75;
        nToCheckBlockUpgradeMajority = 100;
        nMinerThreads = 0;
        nTargetTimespan = 1 * 60; // TRBO: 1 day
        nTargetSpacing = 1 * 60;  // TRBO: 1 minute
        nMaturity = 5;
        nMasternodeCountDrift = 4;
        nModifierUpdateBlock = 51197; //approx Mon, 17 Apr 2017 04:00:00 GMT
        nMaxMoneyOut = 1000000000 * COIN;
        nLastPOWBlock = 200;

        //! Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nTime = 1524873600;
        genesis.nNonce = 2394236;

        hashGenesisBlock = genesis.GetHash();
        if (regenerate) {
            hashGenesisBlock = uint256S("");
            genesis.nNonce = 0;
            if (true && (genesis.GetHash() != hashGenesisBlock)) {
                uint256 hashTarget = CBigNum().SetCompact(genesis.nBits).getuint256();
                while (genesis.GetHash() > hashTarget)
                {
                    ++genesis.nNonce;
                    if (genesis.nNonce == 0)
                    {
                        ++genesis.nTime;
                    }
                }
                std::cout << "// Testnet ---";
                std::cout << " nonce: " << genesis.nNonce;
                std::cout << " time: " << genesis.nTime;
                std::cout << " hash: 0x" << genesis.GetHash().ToString().c_str();
                std::cout << " merklehash: 0x"  << genesis.hashMerkleRoot.ToString().c_str() <<  "\n";

            }
        } else {
            LogPrintf("Testnet ---\n");
            LogPrintf(" nonce: %u\n", genesis.nNonce);
            LogPrintf(" time: %u\n", genesis.nTime);
            LogPrintf(" hash: 0x%s\n", genesis.GetHash().ToString().c_str());
            LogPrintf(" merklehash: 0x%s\n", genesis.hashMerkleRoot.ToString().c_str());
            //assert(hashGenesisBlock == uint256("0x7fbf5849b7a8602fecd2d5e4465b3d4f0bfb482b02c87388b925009d14ba7e42"));
            //assert(genesis.hashMerkleRoot == uint256("0x72aeadf2484a1961e260a25d5d03ced4452e834eeed6bdc4457252f6c444914e"));
        }        

        vFixedSeeds.clear();
        vSeeds.clear();

        vSeeds.push_back(CDNSSeedData("testnetdns", "testnetdns.trbo.org"));


        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 139); // Testnet trbo addresses start with 'x' or 'y'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 19);  // Testnet trbo script addresses start with '8' or '9'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 239);     // Testnet private keys start with '9' or 'c' (Bitcoin defaults)
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x3a)(0x80)(0x61)(0xa0).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x3a)(0x80)(0x58)(0x37).convert_to_container<std::vector<unsigned char> >();
        // Testnet trbo BIP44 coin type is '1' (All coin's testnet default)
        nExtCoinType = 1;

        bech32_hrp = "ts";

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = true;

        nPoolMaxTransactions = 2;        
        strSporkKey = "";
        strSporkKeyTemp = "";
        strObfuscationPoolDummyAddress = "";
        nBudgetFeeConfirmations = 3; // Number of confirmations for the finalization fee. We have to make this very short
                                     // here because we only have a 8 block finalization window on testnet
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
        pchMessageStart[0] = 0x2d;
        pchMessageStart[1] = 0x53;
        pchMessageStart[2] = 0x6f;
        pchMessageStart[3] = 0x40;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 1;
        nTargetTimespan = 24 * 60 * 60; // TRBO: 1 day
        nTargetSpacing = 1 * 60;        // TRBO: 1 minutes
        bnProofOfWorkLimit = ~uint256(0) >> 1;
        genesis.nTime = 1524873600;
        genesis.nBits = 0x207fffff;
        genesis.nNonce = 906460;
        nMaturity = 0;
        nLastPOWBlock = 999999999; // PoS complicates Regtest because of timing issues
        nDefaultPort = 9544;

        hashGenesisBlock = genesis.GetHash();
        if (regenerate) {
            hashGenesisBlock = uint256S("");
            if (true && (genesis.GetHash() != hashGenesisBlock)) {
                uint256 hashTarget = CBigNum().SetCompact(genesis.nBits).getuint256();
                while (genesis.GetHash() > hashTarget)
                {
                    ++genesis.nNonce;
                    if (genesis.nNonce == 0)
                    {
                        ++genesis.nTime;
                    }
                }
                std::cout << "// Regtestnet ---";
                std::cout << " nonce: " << genesis.nNonce;
                std::cout << " time: " << genesis.nTime;
                std::cout << " hash: 0x" << genesis.GetHash().ToString().c_str();
                std::cout << " merklehash: 0x"  << genesis.hashMerkleRoot.ToString().c_str() <<  "\n";

            }
        } else {
            LogPrintf("Regtestnet ---\n");
            LogPrintf(" nonce: %u\n", genesis.nNonce);
            LogPrintf(" time: %u\n", genesis.nTime);
            LogPrintf(" hash: 0x%s\n", genesis.GetHash().ToString().c_str());
            LogPrintf(" merklehash: 0x%s\n", genesis.hashMerkleRoot.ToString().c_str());
            //assert(hashGenesisBlock == uint256("0x613e35c5b607586d3f5b8b109d162eac5fca0be0b0fa282277092e8dea8af138"));
            //assert(genesis.hashMerkleRoot == uint256("0x72aeadf2484a1961e260a25d5d03ced4452e834eeed6bdc4457252f6c444914e"));
        }        

        if (regenerate)
            exit(0);

        bech32_hrp = "trbot";

        vFixedSeeds.clear(); //! Testnet mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Testnet mode doesn't have any DNS seeds.

        fMiningRequiresPeers = false;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;
        fTestnetToBeDeprecatedFieldRPC = false;

        // {
        //     "PrivateKey": "923EhWh2bJHynX6d4Tqt2Q75bhTDCT1b4kff3qzDKDZHZ6pkQs7",
        //     "PublicKey": "04866dc02c998b7e1ab16fe14e0d86554595da90c36acb706a4d763b58ed0edb1f82c87e3ced065c5b299b26e12496956b9e5f9f19aa008b5c46229b15477c875a"
        // }
        strSporkKey = "";
        strSporkKeyTemp = "";
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
        nDefaultPort = 19666;
        vFixedSeeds.clear(); //! Unit test mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Unit test mode doesn't have any DNS seeds.

        nExtCoinType = 1;
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