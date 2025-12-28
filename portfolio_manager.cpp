#include<bits/stdc++.h>
using namespace std;

// -------------------- Simple JSON read/write --------------------
map<string, double> load_json(const string &filename) {
    map<string, double> out;
    ifstream f(filename);
    if (!f.is_open()) return out;

    string line;
    while (getline(f, line)) {
        size_t key_start = line.find('"');
        if (key_start == string::npos) continue;
        size_t key_end = line.find('"', key_start + 1);
        if (key_end == string::npos) continue;
        string key = line.substr(key_start + 1, key_end - key_start - 1);

        size_t colon = line.find(':', key_end);
        if (colon == string::npos) continue;
        double val = stod(line.substr(colon + 1));
        out[key] = val;
    }
    return out;
}

void save_json(const string &filename, const map<string, double> &data) {
    ofstream f(filename);
    f << "{\n";
    size_t i = 0;
    for (auto &kv : data) {
        f << "  \"" << kv.first << "\":" << kv.second;
        if (i++ != data.size() - 1) f << ",";
        f << "\n";
    }
    f << "}\n";
}

// -------------------- Portfolio --------------------
class Portfolio {
public:
    map<string, double> holdings;
    map<string, double> targets;
    map<string, double> prices; // simulated USD prices

    Portfolio() {
        holdings = load_json("holdings.json");
        targets = load_json("targets.json");
        // Simulated prices
        prices = { {"bitcoin", 30000}, {"ethereum", 2000}, {"cardano", 0.5} };
    }

    void upsert_holding(const string &sym, double qty) {
        if (qty == 0) holdings.erase(sym);
        else holdings[sym] = qty;
        save_json("holdings.json", holdings);
    }

    void upsert_target(const string &sym, double pct) {
        targets[sym] = pct;
        save_json("targets.json", targets);
    }

    struct Valuation {
        double total_usd = 0;
        map<string, double> value_usd;
        map<string, double> allocation;
    };

    Valuation value_portfolio() {
        Valuation val;
        for (auto &kv : holdings) {
            string sym = kv.first;
            double qty = kv.second;
            double price = prices.count(sym) ? prices[sym] : 0;
            double value = qty * price;
            val.value_usd[sym] = value;
            val.total_usd += value;
        }
        for (auto &kv : val.value_usd) {
            val.allocation[kv.first] = (val.total_usd > 0) ? kv.second / val.total_usd : 0.0;
        }
        return val;
    }
};

// -------------------- Rebalancer --------------------
struct Suggestion {
    string symbol;
    double usd_to_trade; // positive=buy, negative=sell
};

vector<Suggestion> suggest_rebalance(const Portfolio::Valuation &val,
                                     const map<string, double> &targets,
                                     double threshold = 0.05) {
    vector<Suggestion> out;
    double total = val.total_usd;
    if (total <= 0) return out;
    set<string> syms;
    for (auto &kv : val.allocation) syms.insert(kv.first);
    for (auto &kv : targets) syms.insert(kv.first);
    for (auto &s : syms) {
        double cur = val.allocation.count(s) ? val.allocation.at(s) : 0.0;
        double tgt = targets.count(s) ? targets.at(s) : 0.0;
        double diff = cur - tgt;
        if (fabs(diff) > threshold) {
            double usd = -diff * total;
            usd = round(usd * 100.0) / 100.0;
            out.push_back({s, usd});
        }
    }
    return out;
}

// -------------------- CLI --------------------
void print_help() {
    cout << "Commands:\n"
         << "  add_hold SYMBOL QTY\n"
         << "  add_target SYMBOL PERCENT\n"
         << "  show\n"
         << "  suggest THRESHOLD\n"
         << "  exit\n";
}

int main() {
    Portfolio pf;
    cout << "Simple Crypto Portfolio Manager (C++ without external libs)\n";
    print_help();

    string line;
    while (true) {
        cout << "\n> ";
        if (!getline(cin, line)) break;
        if (line.empty()) continue;

        istringstream iss(line);
        string cmd;
        iss >> cmd;

        if (cmd == "add_hold") {
            string sym; double qty;
            if (!(iss >> sym >> qty)) { cout << "Usage: add_hold SYMBOL QTY\n"; continue; }
            pf.upsert_holding(sym, qty);
            cout << "Saved holding " << sym << " = " << qty << "\n";
        } 
        else if (cmd == "add_target") {
            string sym; double pct;
            if (!(iss >> sym >> pct)) { cout << "Usage: add_target SYMBOL PERCENT\n"; continue; }
            pf.upsert_target(sym, pct);
            cout << "Saved target " << sym << " = " << pct << "\n";
        } 
        else if (cmd == "show") {
            auto val = pf.value_portfolio();
            cout << fixed << setprecision(2);
            cout << "Total USD: $" << val.total_usd << "\n";
            cout << left << setw(12) << "SYMBOL" << setw(12) << "QTY"
                 << setw(12) << "PRICE" << setw(12) << "VALUE" << setw(10) << "ALLOC\n";
            for (auto &kv : pf.holdings) {
                string s = kv.first;
                double q = kv.second;
                double p = pf.prices.count(s) ? pf.prices[s] : 0;
                double v = val.value_usd.count(s) ? val.value_usd[s] : 0;
                double a = val.allocation.count(s) ? val.allocation[s]*100 : 0;
                cout << left << setw(12) << s << setw(12) << q << setw(12) << p
                     << setw(12) << v << setw(6) << a << "%\n";
            }
        } 
        else if (cmd == "suggest") {
            double thresh = 0.05; iss >> thresh;
            auto val = pf.value_portfolio();
            auto suggestions = suggest_rebalance(val, pf.targets, thresh);
            if (suggestions.empty()) cout << "No suggestions (within threshold).\n";
            else {
                cout << "Suggestions (positive=buy USD, negative=sell USD):\n";
                for (auto &s : suggestions) cout << "  " << setw(12) << s.symbol << " : " << s.usd_to_trade << " USD\n";
            }
        } 
        else if (cmd == "help") print_help();
        else if (cmd == "exit" || cmd == "quit") break;
        else cout << "Unknown command\n";
    }

    cout << "Bye\n";
    return 0;
}