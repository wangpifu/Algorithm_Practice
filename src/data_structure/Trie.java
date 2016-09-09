package data_structure;
//https://www.youtube.com/watch?v=AXjmTQ8LEoI
import java.util.*;
class TrieNode {
    // Initialize your data structure here.
    HashMap<Character, TrieNode> children;
    boolean isWord;
    public TrieNode() {
        children = new HashMap<>();
        isWord = false;
    }
}

public class Trie {
    private TrieNode root;

    public Trie() {
        root = new TrieNode();
    }

    // Inserts a word into the trie.
    public void insert(String word) {
        TrieNode current = root;
        for(int i = 0; i < word.length(); i++){
            char ch = word.charAt(i);
            TrieNode next = current.children.get(ch);
            if(next == null){
                next = new TrieNode();
                current.children.put(ch,next);
            }
            current = next;
        }
        // mark this as a word;
        current.isWord = true;
    }

    // Returns if the word is in the trie.
    public boolean search(String word) {
        TrieNode current = root;
        for(int i = 0; i < word.length(); i++){
            char ch = word.charAt(i);
            TrieNode next = current.children.get(ch);
            if (next == null){
                return false;
            }
            current = next;
        }
        return current.isWord;
    }

    // Returns if there is any word in the trie
    // that starts with the given prefix.
    public boolean startsWith(String prefix) {
        TrieNode current = root;
        for(int i = 0; i < prefix.length(); i++){
            char ch = prefix.charAt(i);
            TrieNode next = current.children.get(ch);
            if (next == null){
                return false;
            }
            current = next;
        }
        return true;
    }
    
     public void delete(String word) {
        delete(root, word, 0);
    }

    /**
     * Returns true if parent should delete the mapping
     */
    private boolean delete(TrieNode current, String word, int index) {
        if (index == word.length()) {
            //when end of word is reached only delete if currrent.endOfWord is true.
            if (!current.isWord) {
                return false;
            }
            current.isWord = false;
            //if current has no other mapping then return true
            return current.children.size() == 0;
        }
        char ch = word.charAt(index);
        TrieNode node = current.children.get(ch);
        if (node == null) {
            return false;
        }
        boolean shouldDeleteCurrentNode = delete(node, word, index + 1);

        //if true is returned then delete the mapping of character and trienode reference from map.
        if (shouldDeleteCurrentNode) {
            current.children.remove(ch);
            //return true if no mappings are left in the map.
            return current.children.size() == 0;
        }
        return false;
    }
}

// Your Trie object will be instantiated and called as such:
// Trie trie = new Trie();
// trie.insert("somestring");
// trie.search("key");