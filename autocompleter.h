
#ifndef AUTOCOMPLETER_H
#define AUTOCOMPLETER_H

#include <vector>
#include <string>

using namespace std;

class Autocompleter
{
	// For the mandatory running times below:
	// Assume that the length of every string is O(1). 

public:
	// Creates a new Autocompleter with an empty dictionary.
	//
	// Must run in O(1) time.
	Autocompleter();

	// Adds a string x to the dictionary.
	// If x is already in the dictionary, does nothing.
	//
	// Must run in O(1) time.
	void insert(string x, int freq) {
		Node* current = root;

		// Insert x into the root node
		current->top.push_back({ x, freq });
		for (int i = 0; i < min(static_cast<int>(current->top.size()), 3); ++i) {
			for (int j = 0; j < min(static_cast<int>(current->top.size()) - i - 1, 3); ++j) {
				if (current->top[j].freq < current->top[j + 1].freq) {
					swap(current->top[j], current->top[j + 1]);
				}
			}
		}
		if (current->top.size() > 3) {
			current->top.pop_back();
		}

		// Traverse the trie to insert the string into relevant nodes
		for (char c : x) {
			int index = static_cast<int>(c);
			if (current->children[index] == nullptr) {
				current->children[index] = new Node;
			}
			current = current->children[index];

			// Insert x into the current node
			current->top.push_back({ x, freq });
			for (int i = 0; i < min(static_cast<int>(current->top.size()), 3); ++i) {
				for (int j = 0; j < min(static_cast<int>(current->top.size()) - i - 1, 3); ++j) {
					if (current->top[j].freq < current->top[j + 1].freq) {
						swap(current->top[j], current->top[j + 1]);
					}
				}
			}
			if (current->top.size() > 3) {
				current->top.pop_back();
			}
		}

		// Mark the last node if necessary
		if (!current->marked) {
			current->marked = true;
			count++;
		}
	}








	// Fills the vector T with the three most-frequent completions of x.
	// If x has less than three completions, then 
	// T is filled with all completions of x.
	// The completions appear in T from most to least frequent.
	// 
	// Must run in O(1) time.
	

	void completions(string x, vector<string>& T) {
		Node* current = root;
		T.clear();

		// If the input string x is empty, directly extract completions from the root node
		if (x.empty()) {
			// Extract the completions from the top vector of the root node
			for (const Entry& entry : root->top) {
				T.push_back(entry.s);
				if (T.size() == 3) // Break if T is filled with three completions
					break;
			}
			return;
		}

		// Traverse the trie to find the node corresponding to the last character of x
		for (char c : x) {
			int index = static_cast<int>(c);
			if (current->children[index] == nullptr) {
				// No completions for x, return an empty vector
				return;
			}
			current = current->children[index];
		}

		// Extract the completions from the top vector of the last node
		for (const Entry& entry : current->top) {
			T.push_back(entry.s);
			if (T.size() == 3) // Break if T is filled with three completions
				break;
		}
	}





	

	// Returns the number of strings in the dictionary.
	// 
	// Must run in O(1) time.
	int size() {
		return count;
	}


private:
	// A helper class that stores a string and a frequency.
	class Entry
	{
	public:
		string s;
		int freq;
	};

	// A helper class that implements a trie node.
	class Node
	{
	public:
		Node()
		{
			this->marked = false;
			for (int i = 0; i < 256; ++i)
				children[i] = nullptr;
		}

		bool marked;
		vector<Entry> top;
		Node* children[256];
	};

	// Root of the trie-based data structure
	Node* root;

	// Number of marked nodes in the trie-based data structure
	int count;
};

#endif
