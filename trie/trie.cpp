#include <iostream> 
using namespace std;

template <typename T>
class LinkedList {
private:
	struct Node {
		T data;
		Node* next;
		Node(T data) : data(data), next(nullptr) {}
	};

	Node* head;
	Node* tail;
public:
	LinkedList() : head(nullptr), tail(nullptr) {}

	void push(T value) {
		Node* item = new Node(value);

		if (!head)
			head = tail = item;
		else {
			tail->next = item;
			tail = item;
		}
	}

	void print() const {
		Node* temp_head = head;
		while (temp_head != nullptr) {
			cout << temp_head->data << " ";
			temp_head = temp_head->next;
		}
		cout << "\n";
	}
};




class Trie
{
private:
	static const int MaxChar = 26; 
	Trie* child[MaxChar];
	bool isLeaf{};

public:
	Trie() {
		isLeaf = false;
		for (int i = 0; i < MaxChar; ++i) {
			child[i] = nullptr;
		}
	}
	//insert
	void insert(string str, int idx = 0) {
		if (idx == (int)str.size())
			isLeaf = 1;
		else {
			int cur = str[idx] - 'a';
			if (child[cur] == 0)
				child[cur] = new Trie();
			child[cur]->insert(str, idx + 1);
		}
	}

	// 1 single word search
	bool Single_Word_Search(string str, int idx = 0)
	{
		if (idx == (int)str.size())
		{
			return isLeaf;
		}

		int cur = str[idx] - 'a';

		if (!child[cur]) // if no child found
			return false;	

		return child[cur]->Single_Word_Search(str, idx + 1);
	}

	//print
	void print(LinkedList<string>& res, string cur_str = "") {
		if (isLeaf)
			res.push(cur_str);

		for (int i = 0; i < MaxChar; ++i)
			if (child[i])
				child[i]->print(res, cur_str + (char)(i + 'a'));
	}
	//3 prefix
	void prefix_search(const string& str, LinkedList<string>& res, int idx = 0) {
		if (idx == str.size()) {
			print(res, str);
			return;  // Return after printing all words with the given prefix
		}

		int ch = str[idx] - 'a';
		if (!child[ch]) {
			cout << "No matching prefix here" << endl;
			return;  // Return if no matching prefix is found
		}

		child[ch]->prefix_search(str, res, idx + 1);
	}

	void suffix_exist(string& str, LinkedList<string>& res, int idx = 0) {
		reverse(str.begin(), str.end());
		if (idx == str.size()) {
			print(res, str);
			return;  // Return after printing all words with the given prefix
		}

		int ch = str[idx] - 'a';
		if (!child[ch]) {
			cout << "No matching prefix here" << endl;
			return;  // Return if no matching prefix is found
		}

		child[ch]->suffix_exist(str, res, idx + 1);
	}
};




int main()
{
    Trie root;

    root.insert("abcd");
    root.insert("xyz");
    root.insert("abf");
    root.insert("xn");
    root.insert("ab");
    root.insert("bcd");
	
	//LinkedList<string> results;
	//root.prefix_search("ab", results);
	//results.print();
	LinkedList<string> results1;
	root.suffix_exist("cd", results1);
	results1.print();


	return 0;
}

