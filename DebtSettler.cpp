#include <bits/stdc++.h>
using namespace std;

// Convert string to lowercase for consistency
string toLowerCase(const string &str) {
    string result = str;
    transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}

// Function to minimize cash flow
void minimizeCashFlow(vector<vector<int>> &graph, const vector<string> &bankNames) {
    int n = graph.size();
    vector<int> netAmount(n, 0);

    // Calculate net balance for each bank
    for (int p = 0; p < n; p++) {
        for (int i = 0; i < n; i++) {
            netAmount[p] += (graph[i][p] - graph[p][i]);
        }
    }

    // Recursive settlement function
    function<void()> settleDebts = [&]() {
        auto maxCredit = max_element(netAmount.begin(), netAmount.end()) - netAmount.begin();
        auto maxDebit = min_element(netAmount.begin(), netAmount.end()) - netAmount.begin();

        if (netAmount[maxCredit] == 0 && netAmount[maxDebit] == 0)
            return;

        int minTransfer = min(-netAmount[maxDebit], netAmount[maxCredit]);
        netAmount[maxCredit] -= minTransfer;
        netAmount[maxDebit] += minTransfer;

        cout << bankNames[maxDebit] << " pays " << minTransfer << " to " << bankNames[maxCredit] << endl;

        settleDebts();
    };

    settleDebts();
}

int main() {
    cout << "Cash Flow Minimizer with Visualization\n";

    // Input: number of banks
    int numBanks;
    cout << "Enter the number of banks: ";
    cin >> numBanks;

    // Input: bank details
    vector<string> bankNames(numBanks);
    unordered_map<string, int> bankIndex;
    cin.ignore(); // Clear input buffer

    for (int i = 0; i < numBanks; i++) {
        cout << "Enter bank name and payment modes (e.g., BankA 2 PayTM GooglePay): ";
        string line;
        getline(cin, line);

        stringstream ss(line);
        string bankName;
        ss >> bankName;
        bankName = toLowerCase(bankName);
        bankNames[i] = bankName;
        bankIndex[bankName] = i;
    }

    // Input: number of transactions
    int numTransactions;
    cout << "Enter the number of transactions: ";
    cin >> numTransactions;
    cin.ignore(); // Clear input buffer

    // Graph for transactions
    vector<vector<int>> graph(numBanks, vector<int>(numBanks, 0));

    cout << "Enter transactions (Debtor Creditor Amount):\n";
    for (int i = 0; i < numTransactions; i++) {
        string line, debtor, creditor;
        int amount;
        getline(cin, line);

        stringstream ss(line);
        ss >> debtor >> creditor >> amount;

        debtor = toLowerCase(debtor);
        creditor = toLowerCase(creditor);

        if (bankIndex.find(debtor) == bankIndex.end() || bankIndex.find(creditor) == bankIndex.end()) {
            cerr << "Error: Invalid bank names in transaction.\n";
            return 1;
        }

        graph[bankIndex[debtor]][bankIndex[creditor]] += amount;
    }

    // Display the initial graph
    cout << "\nInitial Transactions Graph:\n";
    for (int i = 0; i < numBanks; i++) {
        for (int j = 0; j < numBanks; j++) {
            if (graph[i][j] != 0) {
                cout << bankNames[i] << " owes " << graph[i][j] << " to " << bankNames[j] << endl;
            }
        }
    }

    // Minimize cash flow
    cout << "\nSettlements to minimize cash flow:\n";
    minimizeCashFlow(graph, bankNames);

    return 0;
}
