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

// Convert the pnSeeds array into usable address objects.
static void convertSeeds(std::vector<CAddress> &vSeedsOut, const unsigned int *data, unsigned int count, int port)
{
	// It will only connect to one or two seed nodes because once it connects,
	// it will get a pile of addresses with newer timestamps.
	// Seed nodes are given a random "last seen time" of between one and two
	// weeks ago.
	const int64_t nOneWeek = 7 * 24 * 60 * 60;
	for (unsigned int k = 0; k < count; ++k)
	{
		struct in_addr ip;
		unsigned int i = data[k], t;

		// -- convert to big endian
		t = (i & 0x000000ff) << 24u
			| (i & 0x0000ff00) << 8u
			| (i & 0x00ff0000) >> 8u
			| (i & 0xff000000) >> 24u;

		memcpy(&ip, &t, sizeof(ip));

		CAddress addr(CService(ip, port));
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
		pchMessageStart[0] = 0xbe;
		pchMessageStart[1] = 0x9a;
		pchMessageStart[2] = 0x17;
		pchMessageStart[3] = 0x6c;
		vAlertPubKey = ParseHex("04209b60a937e4b12927986df14bdfa2c5f71d70e13ad92fd341509cc3a8967c1cb0799eee1ea9ccea28c42884486620792928fb5c9c639631f0d56d6c9e84b0d4");
		nDefaultPort = 46566;
		nRPCPort = 46738;
		bnProofOfWorkLimit = CBigNum(~uint256(0) >> 16);

		const char* pszTimestamp = "start alioth coin on Sunday 31th of March 2019";
		std::vector<CTxIn> vin;
		vin.resize(1);
		vin[0].scriptSig = CScript() << 0 << CBigNum(42) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
		std::vector<CTxOut> vout;
		vout.resize(1);
		vout[0].SetEmpty();
		CTransaction txNew(1, 1553950171, vin, vout, 0);
		genesis.vtx.push_back(txNew);
		genesis.hashPrevBlock = 0;
		genesis.hashMerkleRoot = genesis.BuildMerkleTree();
		genesis.nVersion = 1;
		genesis.nTime = 1553950171;
		genesis.nBits = 0x1e0ffff0;
		genesis.nNonce = 420507;

		hashGenesisBlock = genesis.GetHash();
  
        /*LogPrintf("Display genesis hash so we can input it below %s\n", hashGenesisBlock.ToString().c_str());
	    LogPrintf("Display merkle root so we can input it below %s\n", genesis.hashMerkleRoot.ToString().c_str());
        LogPrintf("Display nonce so we can input it below %s\n", genesis.nNonce);
        LogPrintf("Display time so we can input it below %s\n", genesis.nTime);*/

		assert(genesis.hashMerkleRoot == uint256("0x42f54c3306251c894ee8714f98b92340f85d84b00cbb1d3a8f0a4869353a951e"));
		assert(hashGenesisBlock == uint256("0xf0c23e3e7e24b38e239495f6d7dec5289664bb1e356429c92bf95f7540d80cc9"));

		base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 23);
		base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 83);
		base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 65);
		base58Prefixes[STEALTH_ADDRESS] = std::vector<unsigned char>(1, 66);
		base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x88)(0xB2)(0x1E).convert_to_container<std::vector<unsigned char> >();
		base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x88)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >();

		vSeeds.push_back(CDNSSeedData("0", "80.211.139.151"));
		vSeeds.push_back(CDNSSeedData("1", "80.211.179.252"));
//		vSeeds.push_back(CDNSSeedData("2", ""));
		convertSeeds(vFixedSeeds, pnSeed, ARRAYLEN(pnSeed), nDefaultPort);

		nPoolMaxTransactions = 3;
		strDarksendPoolDummyAddress = "tFoQDUrp63QWqFhjEr3Fmc4ubHRhyzjKUC";
		nLastPOWBlock = 3000000;
		nPOSStartBlock = 20;
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
		pchMessageStart[0] = 0x1e;
		pchMessageStart[1] = 0x7d;
		pchMessageStart[2] = 0xb6;
		pchMessageStart[3] = 0x4c;
		bnProofOfWorkLimit = CBigNum(~uint256(0) >> 16);
		vAlertPubKey = ParseHex("04209b60a937e4b12927986df14bdfa2c5f71d70e13ad92fd341509cc3a8967c1cb0799eee1ea9ccea28c42884486620792928fb5c9c639631f0d56d6c9e84b0d4");
		nDefaultPort = 20318;
		nRPCPort = 20319;
		strDataDir = "testnet";

		// Modify the testnet genesis block so the timestamp is valid for a later start.
		genesis.nBits = 0x1e0ffff0;
		genesis.nNonce = 216893;
		genesis.nTime    = 1553950172;

        hashGenesisBlock = genesis.GetHash();

        //LogPrintf("Display testNet genesis hash so we can input it below %s\n", hashGenesisBlock.ToString().c_str());

		assert(hashGenesisBlock == uint256("0x4ab388e0ba2296212d0ce2bdc61ab6741d9fbaedff89d30b1b577ceaaf093679"));

		vFixedSeeds.clear();
		vSeeds.clear();

		base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 127);
		base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 196);
		base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 239);
		base58Prefixes[STEALTH_ADDRESS] = std::vector<unsigned char>(1, 40);
		base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x35)(0x87)(0xCF).convert_to_container<std::vector<unsigned char> >();
		base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x35)(0x83)(0x94).convert_to_container<std::vector<unsigned char> >();

		convertSeeds(vFixedSeeds, pnTestnetSeed, ARRAYLEN(pnTestnetSeed), nDefaultPort);

		nLastPOWBlock = 0x7fffffff;
	}
	virtual Network NetworkID() const { return CChainParams::TESTNET; }
};
static CTestNetParams testNetParams;


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
	default:
		assert(false && "Unimplemented network");
		return;
	}
}

bool SelectParamsFromCommandLine() {

	bool fTestNet = GetBoolArg("-testnet", false);

	if (fTestNet) {
		SelectParams(CChainParams::TESTNET);
	}
	else {
		SelectParams(CChainParams::MAIN);
	}
	return true;
}