#include <bits/stdc++.h>
using namespace std;

struct Trie {

    // Nodes can use vectors but that would eat up a lot of space.
    // Now they are slow instead.
    struct Node {
        char letter;
        bool ends_here;
        map<char, Node> children;
        Node() : letter('-'), ends_here(false) {}
        Node(char c) : letter(c), ends_here(false) {}
        bool has_child(char c) {return children.find(c) != children.end();}

        void add_string(const string& s, int pos) {
            if (pos == s.size()) {
                ends_here = true;
                return;
            } else {
                const char current = s[pos];
                if (!has_child(current)) {
                    children[current] = Node(current);
                }
                children[current].add_string(s, pos + 1);
            }
        }
        
        bool prefix(const string& s, int pos) {
            //  To check if there exists a prefix to 's':
            //if (ends_here) {
            //  To check if 's' is a prefix to something in the trie:
            //if (pos == s.size())
            //  Both:
            if (ends_here or pos == s.size()) {
                return true;
            } else {
                if (!has_child(s[pos])) return false;
                else return children[s[pos]].prefix(s, pos+1);
            }
        }
    };

    Node root;

    // Returns true if this is a prefix to some word
    // or if there is a word that is a prefix to this.
    bool prefix(const string& s) {
        return root.prefix(s, 0);
    }

    void add_string(const string& s) {
        if (s.size() == 0) return;
        root.add_string(s, 0);
    }

};


void solve(const vector<string>& numbers) {
    Trie trie;
    for (const string& s : numbers) {
        if (trie.prefix(s)) {
            cout << "NO" << endl;
            return;
        }
        trie.add_string(s);
    }
    cout << "YES" << endl;
}


int main() {
    ios::sync_with_stdio(false);
    int t, n;
    cin >> t;
    while (t--) {
        cin >> n;
        vector<string> numbers(n);
        for (string& s : numbers) cin >> s;
        solve(numbers);
    }
}
