#include <iostream>
#include <vector>
#include <string>
#include <memory>

struct TrieNode {
    std::string str;
    std::vector<std::shared_ptr<TrieNode>> children;
    
    TrieNode(const std::string & s)
	: str(s) {}

    void add(const std::shared_ptr<TrieNode> & child) {
	children.push_back(child);
    }
};

using pNode = std::shared_ptr<TrieNode>;

class Trie {
private:
    pNode root;

public:
    Trie() {
	root = std::make_shared<TrieNode>("");
    }

    void add(const std::string & word) {
	
    }

    pNode find(const std::string & word) {
	
    }
};

class WordDictionary {
public:
void addWord(const std::string & word) {
}

bool searchWord(const std::string & word) {

}

private:
std::shared_ptr<Trie> trie;
};
