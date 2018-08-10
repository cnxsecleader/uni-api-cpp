#ifndef UNI_API_H
#define UNI_API_H

#include "types.h"
#include "exception.h"

namespace jsonrpc { class HttpClient; class Client; }

class UniAPI
{

private:
    jsonrpc::HttpClient * httpClient;
    jsonrpc::Client * client;

public:
    /* === Constructor and Destructor === */
    UniAPI(const std::string& user, const std::string& password, const std::string& host, int port);
    ~UniAPI();

    /* === Auxiliary functions === */
    Json::Value sendcommand(const std::string& command, const Json::Value& params);

    std::string IntegerToString(int num);    
    double RoundDouble(double num);


    /* === Node functions === */
    void addnode(const std::string &node, const std::string& command);
    std::vector<nodeinfo_t> getaddednodeinfo(bool dns);
    std::vector<nodeinfo_t> getaddednodeinfo(bool dns, const std::string& node);
    std::vector<peerinfo_t> getpeerinfo();
    int getconnectioncount();


    /* === Wallet functions === */
    void backupwallet(const std::string& destination);
    std::string encryptwallet(const std::string& passphrase);
    void walletlock();
    void walletpassphrase(const std::string& passphrase, int timeout);
    void walletpassphrasechange(const std::string& oldpassphrase, const std::string& newpassphrase);

    std::string dumpprivkey(const std::string& uniaddress);
    void importprivkey(const std::string& uniprivkey);
    void importprivkey(const std::string& uniprivkey, const std::string& label, bool rescan = true);

    std::string addmultisigaddress(int nrequired, const std::vector<std::string>& keys);
    std::string addmultisigaddress(int nrequired, const std::vector<std::string>& keys, const std::string& account);
    multisig_t createmultisig(int nrequired, const std::vector<std::string>& keys);
    std::string getnewaddress(const std::string& account = "");
    validateaddress_t validateaddress(const std::string& uniaddress);

    void keypoolrefill();
    bool settxfee(double amount);
    double estimatefee(int blocks);

    std::string signmessage(const std::string& uniaddress, const std::string& message);
    bool verifymessage(const std::string& uniaddress, const std::string& signature, const std::string& message);

    getinfo_t getinfo();
    void stop();


    /* === Accounting === */
    double getbalance();
    double getbalance(const std::string& account, int minconf = 1);
    double getunconfirmedbalance();

    double getreceivedbyaccount(const std::string& account, int minconf = 1);
    double getreceivedbyaddress(const std::string& uniaddress, int minconf = 1);

    std::vector<accountinfo_t> listreceivedbyaccount(int minconf = 1, bool includeempty = false);
    std::vector<addressinfo_t> listreceivedbyaddress(int minconf = 1, bool includeempty = false);

    gettransaction_t gettransaction(const std::string& tx, bool watch);
    std::vector<transactioninfo_t> listtransactions();
    std::vector<transactioninfo_t> listtransactions(const std::string& account, int count = 10, int from = 0);

    std::string getaccount(const std::string& uniaddress);
    std::string getaccountaddress(const std::string& account);
    std::vector<std::string> getaddressesbyaccount(const std::string& account);

    std::map<std::string, double> listaccounts(int minconf = 1);
    std::vector< std::vector<addressgrouping_t> > listaddressgroupings();

    bool move(const std::string& fromaccount, const std::string& toaccount, double amount, int minconf = 1);
    bool move(const std::string& fromaccount, const std::string& toaccount, double amount,
			    const std::string& comment, int minconf = 1);

    void setaccount(const std::string& uniaddress, const std::string& account);

    std::string sendtoaddress(const std::string& uniaddress, double amount);
    std::string sendtoaddress(const std::string& uniaddress, double amount, const std::string& comment, const std::string& comment_to);

    std::string sendfrom(const std::string& fromaccount, const std::string& touniaddress, double amount);
    std::string sendfrom(const std::string& fromaccount, const std::string& touniaddress, double amount, const std::string& comment, const std::string& comment_to, int minconf = 1);

    std::string sendmany(const std::string& fromaccount, const std::map<std::string, double>& amounts);
    std::string sendmany(const std::string& fromaccount, const std::map<std::string, double>& amounts, const std::string comment, int minconf = 1);

    utxoinfo_t gettxout(const std::string& txid, int n, bool includemempool = true);
    utxosetinfo_t gettxoutsetinfo();

    std::vector<unspenttxout_t> listunspent(int minconf = 1, int maxconf = 999999);
    std::vector<txout_t> listlockunspent();
    bool lockunspent(bool unlock, const std::vector<txout_t>& outputs);



    /* === Mining functions === */
    std::string getbestblockhash();
    std::string getblockhash(int blocknumber);
    blockinfo_t getblock(const std::string& blockhash);
    int getblockcount();

    void setgenerate(bool generate, int genproclimit = -1);
    bool getgenerate();
    double getdifficulty();
    int gethashespersec();

    mininginfo_t getmininginfo();
    workdata_t getwork();
    bool getwork(const std::string& data);

    txsinceblock_t listsinceblock(const std::string& blockhash = "", int target_confirmations = 1);


    /* === Low level calls === */
    getrawtransaction_t getrawtransaction(const std::string& txid, int verbose = 0);
    decodescript_t decodescript(const std::string& hexString);
    decoderawtransaction_t decoderawtransaction(const std::string& hexString);
    std::string sendrawtransaction(const std::string& hexString, bool highFee);

    std::string createrawtransaction(const std::vector<txout_t>& inputs, const std::map<std::string, double>& amounts);
    std::string createrawtransaction(const std::vector<txout_t>& inputs, const std::map<std::string, std::string>& amounts);

    signrawtransaction_t signrawtransaction(const std::string& rawTx, const std::vector<signrawtxin_t> inputs = std::vector<signrawtxin_t>());
    signrawtransaction_t signrawtransaction(const std::string& rawTx, const std::vector<signrawtxin_t> inputs, const std::vector<std::string>& privkeys, const std::string& sighashtype = "ALL");

    std::vector<std::string> getrawmempool();
    std::string getrawchangeaddress();

};


#endif