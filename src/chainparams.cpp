// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2012 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "assert.h"

#include "chainparams.h"
#include "main.h"
#include "util.h"

#include <boost/assign/list_of.hpp>

using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

//
// Main network
//

// Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress> &vSeedsOut, const SeedSpec6 *data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7*24*60*60;
    for (unsigned int i = 0; i < count; i++)
    {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

class CMainParams : public CChainParams {
public:
    CMainParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0xd5;
        pchMessageStart[1] = 0x7a;
        pchMessageStart[2] = 0xe4;
        pchMessageStart[3] = 0x3d;
        vAlertPubKey = ParseHex("040251669e27baf52584bfe5a757b61c8f5b0e43761250fadae6330c7ebac33835eaa89c1466547ed1f93283f68bc3bde7856a84debb0ac353e6a27430dad61c82");
        nDefaultPort = 44321;
        nRPCPort = 44122;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 15);

        // Build the genesis block. Note that the output of the genesis coinbase cannot
        // be spent as it did not originally exist in the database.
        //


        const char* pszTimestamp = "24 9 2017 Start of Kurdish Block Chain";

        std::vector<CTxIn> vin;
        vin.resize(1);
        vin[0].scriptSig = CScript() << 0 << CBigNum(42) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        std::vector<CTxOut> vout;
        vout.resize(1);
        vout[0].SetEmpty();
        CTransaction txNew(1, 1506250100, vin, vout, 0);
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime    = 1506250100;
        genesis.nBits    = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce   = 6488;
        // uncomment to log genesis block info
                //      //  start
                      //  if (true && genesis.GetHash() != hashGenesisBlock)
                      //                 {
                      //                     printf("Searching for genesis block...\n");
                      //                     uint256 hashTarget = CBigNum().SetCompact(genesis.nBits).getuint256();
                      //                     uint256 thash;
                       //
                      //                     while (true)
                      //                     {
                      //                         thash = genesis.GetHash();
                      //                         if (thash <= hashTarget)
                      //                             break;
                      //                         if ((genesis.nNonce & 0xFFF) == 0)
                      //                         {
                      //                             printf("nonce %08X: hash = %s (target = %s)\n", genesis.nNonce, thash.ToString().c_str(), hashTarget.ToString().c_str());
                      //                         }
                      //                         ++genesis.nNonce;
                      //                         if (genesis.nNonce == 0)
                      //                         {
                      //                             printf("NONCE WRAPPED, incrementing time\n");
                      //                             ++genesis.nTime;
                      //                         }
                      //                     }
                      //                     printf("genesis.nTime = %u \n", genesis.nTime);
                      //                     printf("genesis.nNonce = %u \n", genesis.nNonce);
                      //                     printf("genesis.nVersion = %u \n", genesis.nVersion);
                      //                     printf("genesis.GetHash = %s\n", genesis.GetHash().ToString().c_str()); //first this, then comment this line out and uncomment the one under.
                      //                     printf("genesis.hashMerkleRoot = %s \n", genesis.hashMerkleRoot.ToString().c_str()); //improvised. worked for me, to find merkle root
                       //
                      //                 }
                //
                //        //end
        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x0000af8611f474e997efec4294d9144bca3cc93a370d3a3fbea6cb8ef156162e"));
        assert(genesis.hashMerkleRoot == uint256("0x9a957fc4121962ed9ff30325a6c67856d1b94ef20d2fdef63d5e74d54e5a9620"));

        vSeeds.push_back(CDNSSeedData("america", "america.kurdcoin.org"));
        vSeeds.push_back(CDNSSeedData("europ", "europ.kurdcoin.org"));
        vSeeds.push_back(CDNSSeedData("asia", "asia.kurdcoin.org"));

        base58Prefixes[PUBKEY_ADDRESS] = list_of(45);
        base58Prefixes[SCRIPT_ADDRESS] = list_of(63);
        base58Prefixes[SECRET_KEY] =     list_of(75);
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x3d)(0xB2)(0x1E);
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x3d)(0xAD)(0xE4);

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));
    }

    virtual const CBlock& GenesisBlock() const { return genesis; }
    virtual Network NetworkID() const { return CChainParams::MAIN; }

    virtual const vector<CAddress>& FixedSeeds() const {
        return vFixedSeeds;
    }
protected:
    CBlock genesis;
    vector<CAddress> vFixedSeeds;
};
static CMainParams mainParams;


//
// Testnet
//

class CTestNetParams : public CMainParams {
public:
    CTestNetParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.


        pchMessageStart[0] = 0x3d;
        pchMessageStart[1] = 0xa5;
        pchMessageStart[2] = 0xd3;
        pchMessageStart[3] = 0xa7;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 5);
        vAlertPubKey = ParseHex("04c5e13ee9c47c6d9c898153552d61e86be9dfe3a7c944a17b204c0491da30c888d4d8ba1a913b72f0b43496fdc998c2e41d0a1690fefbe32fb6029ed5e6cb096e");
        nDefaultPort = 55321;
        nRPCPort = 55122;
        strDataDir = "testnet";

        // Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nBits  = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce = 20;
        // uncomment to log genesis block info
                //      //  start
                      //  if (true && genesis.GetHash() != hashGenesisBlock)
                      //                 {
                      //                     printf("Searching for genesis block...\n");
                      //                     uint256 hashTarget = CBigNum().SetCompact(genesis.nBits).getuint256();
                      //                     uint256 thash;
                       //
                      //                     while (true)
                      //                     {
                      //                         thash = genesis.GetHash();
                      //                         if (thash <= hashTarget)
                      //                             break;
                      //                         if ((genesis.nNonce & 0xFFF) == 0)
                      //                         {
                      //                             printf("nonce %08X: hash = %s (target = %s)\n", genesis.nNonce, thash.ToString().c_str(), hashTarget.ToString().c_str());
                      //                         }
                      //                         ++genesis.nNonce;
                      //                         if (genesis.nNonce == 0)
                      //                         {
                      //                             printf("NONCE WRAPPED, incrementing time\n");
                      //                             ++genesis.nTime;
                      //                         }
                      //                     }
                      //                     printf("genesis.nTime = %u \n", genesis.nTime);
                      //                     printf("genesis.nNonce = %u \n", genesis.nNonce);
                      //                     printf("genesis.nVersion = %u \n", genesis.nVersion);
                      //                     printf("genesis.GetHash = %s\n", genesis.GetHash().ToString().c_str()); //first this, then comment this line out and uncomment the one under.
                      //                     printf("genesis.hashMerkleRoot = %s \n", genesis.hashMerkleRoot.ToString().c_str()); //improvised. worked for me, to find merkle root
                       //
                      //                 }
                //
                //        //end
        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x013cd814a6ca2fcf87c7d1815e025cd5d542ab8732ba4afcd305cd0c904f7496"));

        vFixedSeeds.clear();
        vSeeds.clear();

        base58Prefixes[PUBKEY_ADDRESS] = list_of(66);
        base58Prefixes[SCRIPT_ADDRESS] = list_of(196);
        base58Prefixes[SECRET_KEY]     = list_of(81);
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0xd3)(0x35)(0x87)(0xCF);
        base58Prefixes[EXT_SECRET_KEY] = list_of(0xd3)(0x35)(0x83)(0x94);

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

    }
    virtual Network NetworkID() const { return CChainParams::TESTNET; }
};
static CTestNetParams testNetParams;


//
// Regression test
//
class CRegTestParams : public CTestNetParams {
public:
    CRegTestParams() {
        pchMessageStart[0] = 0xf2;
        pchMessageStart[1] = 0xa9;
        pchMessageStart[2] = 0xb7;
        pchMessageStart[3] = 0xca;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 1);
        genesis.nTime = 1426450258;
        genesis.nBits  = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce = 0;
        //hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 18445;
        strDataDir = "regtest";

        //  if (true && genesis.GetHash() != hashGenesisBlock)
        //                 {
        //                     printf("Searching for genesis block...\n");
        //                     uint256 hashTarget = CBigNum().SetCompact(genesis.nBits).getuint256();
        //                     uint256 thash;
         //
        //                     while (true)
        //                     {
        //                         thash = genesis.GetHash();
        //                         if (thash <= hashTarget)
        //                             break;
        //                         if ((genesis.nNonce & 0xFFF) == 0)
        //                         {
        //                             printf("nonce %08X: hash = %s (target = %s)\n", genesis.nNonce, thash.ToString().c_str(), hashTarget.ToString().c_str());
        //                         }
        //                         ++genesis.nNonce;
        //                         if (genesis.nNonce == 0)
        //                         {
        //                             printf("NONCE WRAPPED, incrementing time\n");
        //                             ++genesis.nTime;
        //                         }
        //                     }
        //                     printf("genesis.nTime = %u \n", genesis.nTime);
        //                     printf("genesis.nNonce = %u \n", genesis.nNonce);
        //                     printf("genesis.nVersion = %u \n", genesis.nVersion);
        //                     printf("genesis.GetHash = %s\n", genesis.GetHash().ToString().c_str()); //first this, then comment this line out and uncomment the one under.
        //                     printf("genesis.hashMerkleRoot = %s \n", genesis.hashMerkleRoot.ToString().c_str()); //improvised. worked for me, to find merkle root
         //
        //                 }


        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x6218936b0dd6b08e608830192a5da606af1c7fe03f583f046f18a9beeea39194"));

        vSeeds.clear();  // Regtest mode doesn't have any DNS seeds.
    }

    virtual bool RequireRPCPassword() const { return false; }
    virtual Network NetworkID() const { return CChainParams::REGTEST; }
};
static CRegTestParams regTestParams;

static CChainParams *pCurrentParams = &mainParams;

const CChainParams &Params() {
    return *pCurrentParams;
}

void SelectParams(CChainParams::Network network) {
    switch (network) {
        case CChainParams::MAIN:
            pCurrentParams = &mainParams;
            break;
        case CChainParams::TESTNET:
            pCurrentParams = &testNetParams;
            break;
        case CChainParams::REGTEST:
            pCurrentParams = &regTestParams;
            break;
        default:
            assert(false && "Unimplemented network");
            return;
    }
}

bool SelectParamsFromCommandLine() {
    bool fRegTest = GetBoolArg("-regtest", false);
    bool fTestNet = GetBoolArg("-testnet", false);

    if (fTestNet && fRegTest) {
        return false;
    }

    if (fRegTest) {
        SelectParams(CChainParams::REGTEST);
    } else if (fTestNet) {
        SelectParams(CChainParams::TESTNET);
    } else {
        SelectParams(CChainParams::MAIN);
    }
    return true;
}
