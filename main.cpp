#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <stack>
#include <algorithm>

struct TrieNode {
    std::string str;
    std::vector<std::shared_ptr<TrieNode>> children;
    
    TrieNode(const std::string & s)
	: str(s) {}

    void add(const std::shared_ptr<TrieNode> & child) {
	children.push_back(child);
    }

    void print() {
        if (!children.empty()) {
            std::cout << str << " -> ";
            std::for_each(children.begin(), children.end(),
                          [](const std::shared_ptr<TrieNode> & p){
                              std::cout << p->str << " ";
                          });
            std::cout << std::endl;
            std::for_each(children.begin(), children.end(),
                          [](const std::shared_ptr<TrieNode> & p){
                              p->print();
                          });
        }
    }
};

using pNode = std::shared_ptr<TrieNode>;

bool compareStrsWithDot(const std::string & str, const std::string & word) {
    auto pr = std::mismatch(str.begin(), str.end(), word.begin(),
                            [](const char & ch1, const char ch2){
                                if (ch2 == '.')
                                    return true;
                                else
                                    return ch1 == ch2;
                            });
    return pr.first == str.end();
}


class Trie {
private:
    pNode root;

public:
    Trie() {
	root = std::make_shared<TrieNode>("");
    }

    void add(const std::string & word) {
        size_t len = word.size();
        while (len > 0 && !search(word.substr(0,len)))
            len--;
        
        auto curr = find(word.substr(0, len));
        len++;
        while (len <= word.size()) {
            auto next = std::make_shared<TrieNode>(word.substr(0,len));
            curr->add(next);
            curr = next;
            len++;
        }
    }

    bool search(const std::string & word) {
        // if (word.find(".") == std::string::npos) {
        //     std::stack<pNode> st;
        //     st.push(root);
        //     while (!st.empty()) {
        //         auto curr = st.top();
        //         st.pop();
        //         if (curr != nullptr) {
        //             if (!word.compare(curr->str))
        //                 return true;
        //             else if (word.find(curr->str) != std::string::npos){
        //                 std::for_each(curr->children.begin(), curr->children.end(),
        //                               [&](const pNode & p){
        //                                   st.push(p);
        //                               });
        //             }
        //         }
        //     }
        //     return false;
        // }
        // else {
            std::stack<pNode> st;
            st.push(root);
            while (!st.empty()) {
                auto curr = st.top();
                st.pop();
                if (curr != nullptr) {
                    if (curr->str.size() == word.size() && compareStrsWithDot(curr->str, word))
                        return true;
                    else if (curr->str.size() < word.size() && compareStrsWithDot(curr->str, word))
                        std::for_each(curr->children.begin(), curr->children.end(),
                                      [&](const pNode & p){
                                          st.push(p);
                                      });
                }
            }
            return false;
        // }
    }

    void print() {
        root->print();
        // std::for_each(root->children.begin(), root->children.end(),
        //               [](const pNode & p){
        //                   p->print();
        //               });
    }
        
  private:
    pNode find(const std::string & word) {
        std::stack<pNode> st;
        st.push(root);
        while (!st.empty()) {
            auto curr = st.top();
            st.pop();
            if (curr != nullptr) {
                if (!word.compare(curr->str))
                    return curr;
                else if (word.find(curr->str) != std::string::npos){
                    std::for_each(curr->children.begin(), curr->children.end(),
                                  [&](const pNode & p){
                                      st.push(p);
                                  });
                }
            }
        }
        return nullptr;
    }
};

class WordDictionary {
  public:
    WordDictionary() {
        trie = std::make_shared<Trie>();
    }
    
    void addWord(const std::string & word) {
        trie->add(word);
        trie->print();
        std::cout << std::endl;
    }

    bool searchWord(const std::string & word) {
        return trie->search(word);
    }

  private:
    std::shared_ptr<Trie> trie;
};


int main() {
    // Trie trie;
    // trie.add("A");
    // trie.print();
    // std::cout << std::endl;
    // trie.add("to");
    // trie.print();
    // std::cout << std::endl;
    // trie.add("tea");
    // trie.print();
    // std::cout << std::endl;
    // trie.add("ted");
    // trie.print();
    // std::cout << std::endl;
    // trie.add("ten");
    // trie.print();
    // std::cout << std::endl;
    // trie.add("in");
    // trie.print();
    // std::cout << std::endl;
    // trie.add("inn");
    // trie.print();
    // std::cout << std::endl;

    WordDictionary dict;
    dict.addWord("bad");
    dict.addWord("dad");
    dict.addWord("mad");

    std::cout << std::boolalpha;
    std::cout << "search(\"pad\") -> " << dict.searchWord("pad") << std::endl;
    std::cout << "search(\"bad\") -> " << dict.searchWord("bad") << std::endl;
    std::cout << "search(\".ad\") -> " << dict.searchWord(".ad") << std::endl;
    std::cout << "search(\"b..\") -> " << dict.searchWord("b..") << std::endl;
}
