// permutation Input: [1,2,3] Output: [[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>> res;
        vector<int> permutation;
        vector<int> visited(nums.size(), 0);
        helper(res, 0, nums, permutation, visited);
        return res;
    }
    
    void helper(vector<vector<int>>& res, int level, vector<int>& nums, vector<int>& permutation, vector<int>& visited)
    {
        if(level == nums.size())
        {
            res.push_back(permutation);
            return;
        }
        for(int i = 0; i < nums.size(); ++i)
        {
            if(!visited[i])
            {
                visited[i] = 1;
                permutation.push_back(nums[i]);
                helper(res, level + 1, nums, permutation, visited);
                visited[i] = 0;
                permutation.pop_back();
            }
        }
    }
//=============================================================================================
// unique permutation Input: [1,1,2] Output: [[1,1,2],[1,2,1],[2,1,1]]
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        vector<vector<int>> res;
        vector<int> permutation;
        vector<int> visited(nums.size(), 0);
        sort(nums.begin(), nums.end());
        helper(res, 0, nums, permutation, visited);
        return res;     
    }
    void helper(vector<vector<int>>& res, int level, vector<int>& nums, vector<int>& permutation, vector<int>& visited)
    {
        if(level == nums.size())
        {
            res.push_back(permutation);
            return;
        }
        for(int i = 0; i < nums.size(); ++i)
        {
            // if visited[i-1] ==1, it means curt i is in different level wit i-1
            // so even it is dup, we should still go to the recurssive.
            if(i > 0 && nums[i] == nums[i - 1] && visited[i-1]==0) continue;
            if(!visited[i])
            {
                visited[i] = 1;
                permutation.push_back(nums[i]);
                helper(res, level + 1, nums, permutation, visited);
                visited[i] = 0;
                permutation.pop_back();
            }
        }
    }
//==============================================================================================
// N queens, return all solution, The n-queens puzzle is the problem of placing n queens on 
// an n×n chessboard such that no two queens attack each other.
    vector<vector<string>> solveNQueens(int n) {
        vector<vector<string>> res;
        vector<string> solution(n,string(n,'.'));
        helper(res, solution, 0);
        return res;
    }
    void helper(vector<vector<string>>& res, vector<string>& solution, int row_index)
    {
        if(row_index == solution.size())
        {
            res.push_back(solution);
            return;
        }
        for(int col = 0; col < solution.size(); ++col)
        {
            if(isValid(solution, row_index, col))
            {
                solution[row_index][col] = 'Q';
                helper(res, solution, row_index + 1);
                solution[row_index][col] = '.';
            }
        }
    }
    bool isValid(vector<string>& solution, int row, int col)
    {
        for(int i = 0; i < row; ++i)  // check this column
        {
            if(solution[i][col] == 'Q') return false;
        }
        // no need to check this row because we just add Q to this row
        // we check two diagonal \/
        for(int i = row-1, j = col-1; i >=0 && j >=0; --i, --j)
        {
            if(solution[i][j] == 'Q') return false;
        }
        for(int i = row-1, j = col + 1; i >= 0 && j < solution.size(); --i, ++j )
        {
            if(solution[i][j] == 'Q') return false;
        }
        return true;
    }

// N queens II, return number of solution
    int totalNQueens(int n) {
        // we use three vector<bool> to store positions of previous queen
        // for queens in same diagonal(\), they must have same col - row + n
        // for queens in same anti_diag(/), they must have same col + row
        int res = 0;
        vector<bool> cols(n,false), diag(2*n,false), anti_diag(2*n,false);
        helper(res, cols, diag, anti_diag, 0);
        return res;
    }
    void helper(int& res, vector<bool>& cols, vector<bool>& diag,vector<bool>& anti_diag, int row_index)
    {
        int n = cols.size();
        if(row_index == n)
        {
            ++res;
            return;
        }
        for(int i = 0; i < n; ++i)
        {
            int diag_index = i - row_index + n;
            int anti_diag_index = i + row_index;
            if(cols[i] || diag[diag_index] || anti_diag[anti_diag_index]) continue;
            cols[i] = diag[diag_index] = anti_diag[anti_diag_index] = true;
            helper(res, cols, diag, anti_diag, row_index + 1);
            cols[i] = diag[diag_index] = anti_diag[anti_diag_index] = false;
        }
    }
//==========================================================================
// input n = 3, output ["((()))","(()())","(())()","()(())","()()()"]
    vector<string> generateParenthesis(int n) {
        std::vector<std::string> res;
        if (n == 0) return res;
        string solution;
        generate(res, solution, 0, 0, n);
        return res;
        
    }
    void generate(std::vector<std::string>& res, string solution, int left, int right, int n)
    {
        if (right == n)
        {
            res.push_back(solution);
        }
        if (left < n)
        {
            generate(res, solution+"(", left + 1, right, n);
        }
        if (right < left)
        {
            generate(res, solution+")", left, right+1, n);
        }
    }
//==============================================================================================
    vector<string> letterCombinations(string digits) {
        if(digits.empty()) return {};
        vector<string> board = {"","","abc","def","ghi","jkl","mno","pqrs","tuv","wxyz"};
        vector<string> res;
        helper(res, digits, "", board, 0);
        return res;
    }
    
    void helper(vector<string>& res, string& digits, string output, vector<string>& board, int index)
    {
        if(index == digits.size())
        {
            res.push_back(output);
            return;
        }
        string key = board[digits[index] - '0'];
        for(auto i : key)
        {
            helper(res, digits, output + i, board, index + 1);
        }
    }
//================================================================================================
// solve sudoku
    void solveSudoku(vector<vector<char>>& board) {
        helper(board, 0, 0);
    }
    
    bool helper(vector<vector<char>>& board, int row, int col)
    {
        if(row == board.size()) return true;
        if(col == board.size()) return helper(board, row + 1, 0);
        if(board[row][col] != '.') return helper(board, row, col + 1);
        for(char c = '1'; c <= '9'; ++c)
        {
            if(!isValid(board, row, col, c)) continue;
            board[row][col] = c;
            if(helper(board, row, col + 1)) return true;
            board[row][col] = '.';
        }
        return false;
    }
    
    bool isValid(vector<vector<char>>& board, int row, int col, char c)
    {
        for(int i = 0; i < board.size(); ++i)
        {
            if (board[i][col] == c) return false;
            if (board[row][i] == c) return false;
        }
        int subbox_row_start_index = row - row % 3;
        int subbox_col_start_index = col - col % 3;
        for(int i = 0; i < 3; ++i)
        {
            for(int j = 0; j < 3; ++j)
            {
                if(board[subbox_row_start_index + i][subbox_col_start_index + j] == c) return false;
            }
        }
        return true;
    }
//===================================================================================================
//restore ip  Input: "25525511135" Output: ["255.255.11.135", "255.255.111.35"]
// non back-tracking, brute force:
    vector<string> restoreIpAddresses(string s) {
        vector<string> res;
        for (int a = 1; a < 4; ++a) 
        for (int b = 1; b < 4; ++b) 
        for (int c = 1; c < 4; ++c) 
        for (int d = 1; d < 4; ++d) 
            if (a + b + c + d == s.size()) {
                int A = stoi(s.substr(0, a));
                int B = stoi(s.substr(a, b));
                int C = stoi(s.substr(a + b, c));
                int D = stoi(s.substr(a + b + c, d));
                if (A <= 255 && B <= 255 && C <= 255 && D <= 255) {
                    string t = to_string(A) + "." + to_string(B) + "." + to_string(C) + "." + to_string(D);
                    if (t.size() == s.size() + 3) res.push_back(t);
                }
            }
        return res;
    }
//backtracking
    vector<string> restoreIpAddresses(string s) {
        vector<string> res;
        if(s.size() > 12) return res;
        helper(s, 0, "", res);
        return res;
    }
    void helper(string s, int segment, string out, vector<string>& res)
    {
        if(segment == 4 && s.empty())
        {
            res.push_back(out);
        }
        else
        {
            for(int i = 1; i < 4 && i <= s.size(); ++i)
            {
                int val = stoi(s.substr(0,i).c_str());
                // say i = 3, segment should be a 3 digit number, if it is 010, the to_string will return 10 with size 2
                if(val > 255 || i != std::to_string(val).size()) continue;
                helper(s.substr(i), segment + 1, out + s.substr(0,i)+ (segment == 3? "" : "."), res);
            }
        }
    }
//=======================================================================================================
// regular expression match '.' Matches any single character. '*' Matches zero or more of the preceding element.
    //https://www.cnblogs.com/grandyang/p/4461713.html
    bool isMatch(string s, string p) {
        if(p.empty()) return s.empty();
        if(p.size() == 1)
        {
            return (s.size() == 1) && (s[0] == p[0] || p[0] == '.');
        }
        if(p[1] != '*')
        {
            if(s.empty()) return false;
            return (s[0] == p[0] || p[0] == '.') && isMatch(s.substr(1), p.substr(1));
        }
        while(!s.empty() && (s[0] == p[0] || p[0] == '.'))
        {
            if(isMatch(s, p.substr(2))) return true;
            s = s.substr(1);
        }
        return isMatch(s, p.substr(2));
    }

//=====================================================================================================
//subsets: Input: nums = [1,2,3] Output: [[3],[1],[2],[1,2,3],[1,3],[2,3],[1,2],[]]
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> res;
        vector<int> out;
        sort(nums.begin(), nums.end());
        helper(res, out, 0, nums);
        return res;
    }
    void helper(vector<vector<int>>& res, vector<int>& out, int pos, vector<int>& nums)
    {
        res.push_back(out);
        for(int i = pos; i < nums.size(); ++i)
        {
            out.push_back(nums[i]);
            helper(res, out, i + 1, nums);
            out.pop_back();
        }
    }
// subsets II no duplicate Input: [1,2,2] Output:[[2],[1],[1,2,2],[2,2],[1,2],[]]
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        vector<vector<int>> res;
        vector<int> out;
        sort(nums.begin(), nums.end());
        helper(res, out, 0, nums);
        return res;
    }
    void helper(vector<vector<int>>& res, vector<int>& out, int pos, vector<int>& nums)
    {
        res.push_back(out);
        for(int i = pos; i < nums.size(); ++i)
        {
            out.push_back(nums[i]);
            helper(res, out, i + 1, nums);
            out.pop_back();
            while(i + 1 < nums.size() && nums[i] == nums[i+1])
            {
                ++i;
            }
        }
    }
//===================================================================================================
// Combination Sum, the candidates have no duplicate numbers, each value can use multiple times
//All numbers (including target) will be positive integers.
//The solution set must not contain duplicate combinations.
//Input: candidates = [2,3,5], target = 8, A solution set is:[[2,2,2,2],[2,3,3],[3,5]]
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        vector<vector<int>> res;
        vector<int> solution;
        helper(res, solution, candidates, target, 0);
        return res;
    }
    void helper(vector<vector<int>>& res, vector<int>& solution, vector<int>& candidates, int target, int pos)
    {
        if(target < 0) return;
        if(target == 0)
        {
            res.push_back(solution);
            return;
        }
        for(int i = pos; i < candidates.size(); ++i)
        {
            solution.push_back(candidates[i]);
            helper(res, solution, candidates, target - candidates[i], i);
            solution.pop_back();
        }
        
    }
// Combination Sum II, the candidates may have duplicate numbers, and each number can only be used once
//All numbers (including target) will be positive integers.
//The solution set must not contain duplicate combinations.
//Input: candidates = [10,1,2,7,6,1,5], target = 8,A solution set is:[[1, 7],[1, 2, 5],[2, 6],[1, 1, 6]]
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        vector<vector<int>> res;
        vector<int> solution;
        sort(candidates.begin(), candidates.end());
        helper(res, solution, candidates, target, 0);
        return res;
    }
    void helper(vector<vector<int>>& res, vector<int>& solution, vector<int>& candidates, int target, int pos)
    {
        if(target < 0) return;
        if(target == 0)
        {
            res.push_back(solution);
            return;
        }
        for(int i = pos; i < candidates.size(); ++i)
        {
            // use i>pos instead of i>0 because i>pos exclude same level duplicate num
            // if we use i>0, inside next level, it won't add duplcaite num, e.g, 1,1,7
            // in the second nested level, the 2nd '1' will be opt out
            if(i > pos && candidates[i] == candidates[i-1]) continue;
            solution.push_back(candidates[i]);
            helper(res, solution, candidates, target - candidates[i], i + 1);
            solution.pop_back();
        }
    }

//Combination Sum III Find all possible combinations of k numbers that add up to a 
//number n, given that only numbers from 1 to 9 can be used and each combination should be 
//a unique set of numbers. Input: k = 3, n = 9 Output: [[1,2,6], [1,3,5], [2,3,4]]
    vector<vector<int>> combinationSum3(int k, int n) {
        vector<vector<int>> res;
        vector<int> solution;
        helper(res, solution, k, n, 0, 1);
        return res;
    }
    void helper(vector<vector<int>>& res, vector<int>& solution, int k, int n, int curt_num, int pos)
    {
        if(curt_num == k)
        {
            if(n == 0)
            {
                res.push_back(solution);
            }
            return;
        }
        for(int i = pos; i <= 9; ++i)
        {
            solution.push_back(i);
            helper(res, solution, k, n - i, curt_num + 1, i + 1);
            solution.pop_back();
        }
    }
//====================================================================================================
// Palindrome Partitioning Input: "aab" Output:[["aa","b"],["a","a","b"]]
    vector<vector<string>> partition(string s) {
        vector<vector<string>> res;
        vector<string> partition;
        helper(res, partition, 0, s);
        return res;
    }
    
    void helper(vector<vector<string>>& res, vector<string> partition, int pos, string& s)
    {
        if(pos == s.size())
        {
            res.push_back(partition);
            return;
        }
        for(int i = pos; i < s.size(); ++i)
        {
            if(isPalindrome(s.substr(pos, i - pos + 1)))
            {
                partition.push_back(s.substr(pos, i - pos + 1));
                helper(res, partition, i + 1, s);
                partition.pop_back();
            }
        }
    }
    
    bool isPalindrome(string s)
    {
        auto left = s.begin();
        auto right = s.end() - 1;
        while(left < right)
        {
            if(*left != * right)
            {
                return false;
            }
            ++left;
            --right;
        }
        return true;
    }
//=====================================================================================================
//Combinations Given two integers n and k, return all possible combinations of k numbers out of 1 ... n.
//Input: n = 4, k = 2 Output: [[1,2],[1,3],[1,4],[2,3],[2,4],[3,4]]
    vector<vector<int>> combine(int n, int k) {
        vector<vector<int>> res;
        vector<int> combination;
        helper(res, combination, n, k, 1);
        return res;
    }
    
    void helper(vector<vector<int>>& res, vector<int>& combination, int n, int k, int level)
    {
        if(combination.size() == k )
        {
            res.push_back(combination);
            return;
        }
        for(int i = level; i <= n; ++i)
        {
            combination.push_back(i);
            helper(res, combination,  n, k, i + 1);
            combination.pop_back();
        }
    }
//=====================================================================================================
//Given a non-negative integer n, count all numbers with unique digits, x, where 0 ≤ x < 10^n.
    int countNumbersWithUniqueDigits(int n) {
        int used = 0;// the ith bit of 'used' means that index number has been used
        int res = 1; // consider n = 1, the anwser is 0<= x < 10
        int max_value = n > 10 ? pow(10, 10) : pow(10, n);
        for(int i = 1; i <= 9; ++i)
        {
            used |= (1 << i);
            res += helper(i, max_value, used);
            used &= ~(1 << i);
        }
        return res;
    }
    
    int helper(int pre, int max, int used)
    {
        int res = 0;
        if (pre < max)  // need to be "<" not "<=", note x < pow(10, n)
        {
            ++res;
        }
        else 
        {
            return res;
        }
        for(int i = 0; i <=9; ++i)
        {
            if(not (used & (1 << i)))
            {
                int curt = pre * 10 + i;
                used |= (1 << i);
                res += helper(curt, max, used);
                used &= ~(1 << i);
                
            }
        }
        return res;
    }
//=====================================================================================================
//79. Word Search, Given a 2D board and a word, find if the word exists in the grid. The word can be 
//constructed from letters of sequentially adjacent cell, where "adjacent" cells are those horizontally 
//or vertically neighboring. The same letter cell may not be used more than once.
/*board =[
  ['A','B','C','E'],
  ['S','F','C','S'],
  ['A','D','E','E']]
Given word = "ABCCED", return true. Given word = "SEE", return true.Given word = "ABCB", return false.*/
class Solution {
public:
    bool exist(vector<vector<char>>& board, string word) {
        if (board.empty() || board[0].empty()) return false;
        int m = board.size();
        int n = board[0].size();
        vector<vector<bool>> visited(m, vector<bool>(n, false));
        for(int i = 0; i < m; ++i)
        {
            for(int j = 0; j < n; ++j)
            {
                if (helper(board, word, 0, i, j, visited))
                    return true;
            }
        }
        return false;     
    }
    
    bool helper(vector<vector<char>>& board, const string& word, int index, int x, int y, vector<vector<bool>>& visited)
    {
        if(index == word.size()) return true;
        if(x >= board.size() || y >= board[0].size()) return false;
        if(x < 0 || y < 0) return false;
        if(board[x][y] != word[index]) return false;
        if(visited[x][y]) return false;
        visited[x][y] = true;
        bool ret = helper(board, word, index + 1, x + 1, y, visited)
            || helper(board, word, index + 1, x , y + 1, visited)
            || helper(board, word, index + 1, x - 1, y, visited)
            || helper(board, word, index + 1, x , y - 1, visited);
        visited[x][y] = false;
        return ret;
    }
};
//==========================================================================================================================
/*211. Add and Search Word - Data structure design
Design a data structure that supports the following two operations:
void addWord(word)
bool search(word)*/
class WordDictionary {

struct TrieNode
{
    TrieNode* children[26];
    bool isWord;
    TrieNode() : isWord(false)
    {
        for (auto& child: children)
        {
            child = nullptr;
        }
    }
};
    
TrieNode* root;
public:
    
    /** Initialize your data structure here. */
    WordDictionary() {
        root = new TrieNode();
    }
    
    /** Adds a word into the data structure. */
    void addWord(string word) {
        auto* curt = root;
        for(auto& c : word)
        {
            int i = c - 'a';
            if(curt->children[i] == nullptr)
            {
                curt->children[i] = new TrieNode();
            }
            curt = curt->children[i];
        }
        curt->isWord = true;
    }
    
    /** Returns if the word is in the data structure. A word could contain the dot character '.' to represent any one letter. */
    bool search(string word) {
        return searchImpl(word, 0, root);
    }
    bool searchImpl(string& word, int pos, TrieNode* curt) {
        if (pos == word.size()) return curt->isWord;
        if (word[pos] == '.')
        {
            for(auto& child : curt->children)
            {
                if(child != nullptr && searchImpl(word, pos + 1, child)) return true;
            }
        }
        else
        {
            return curt->children[word[pos] - 'a'] && searchImpl(word, pos + 1, curt->children[word[pos]-'a']);
        }
        return false;
    }
};

/**
 * Your WordDictionary object will be instantiated and called as such:
 * WordDictionary* obj = new WordDictionary();
 * obj->addWord(word);
 * bool param_2 = obj->search(word);
 */
//==============================================================================================================================
// 212. Word Search II, Not backtracking, but list here for reference
/*Input: board = [
  ['o','a','a','n'],
  ['e','t','a','e'],
  ['i','h','k','r'],
  ['i','f','l','v']]
words = ["oath","pea","eat","rain"] Output: ["eat","oath"]*/
class Solution {
public:
    struct TrieNode
    {
        TrieNode* children[26];
        string str;
        TrieNode() : str("")
        {
            for(auto& child : children) {child = nullptr;}
        }
    };
    struct Trie
    {
        TrieNode* root;
        Trie(){root = new TrieNode();}
        void insert(const string& s)
        {
            auto* curt = root;
            for(auto& c : s)
            {
                int i = c - 'a';
                if(!curt->children[i])
                {
                    curt->children[i] = new TrieNode();
                }
                curt = curt->children[i];
            }
            curt->str = s;
        }
    };
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
    // the brute force way is for every word, we backtracking if it is in board.
    // but consider some words may have common prefix, we use a trie to do pruning
    // when we traverse the board, we compare adjacent char to trie, if not in trie, we don't continue
        vector<string> res;
        if(words.empty() || board.empty() || board[0].empty()) return res;
        int m = board.size(); int n = board[0].size();
        vector<vector<bool>> visited = vector(m, vector<bool>(n,false));
        Trie T;
        for(auto& s : words) T.insert(s);
        auto* root = T.root;
        for(int i = 0; i < m; ++i)
        {
            for(int j = 0; j < n; ++j)
            {
                int index = board[i][j] - 'a';
                if(root->children[index])
                {
                    helper(board, res, root, visited, i, j);
                }
            }
        }
        return res;
    }
    
    void helper(vector<vector<char>>& board, vector<string>& res, TrieNode* root, vector<vector<bool>>& visited, int x, int y)
    {
        if (!root->str.empty())
        {
            res.push_back(root->str);
            root->str.clear(); // make the str to be empty in case it was added to res again
        }
        if(x >= board.size() || y >= board[0].size()) return;
        if(x < 0 || y < 0) return;
        int index = board[x][y] - 'a';
        if(!root->children[index]) return;
        if(visited[x][y]) return;
        visited[x][y] = true;
        helper(board, res, root->children[index], visited, x + 1, y);
        helper(board, res, root->children[index], visited, x - 1, y);
        helper(board, res, root->children[index], visited, x, y - 1);
        helper(board, res, root->children[index], visited, x, y + 1);
        visited[x][y] = false;
    }
};
//====================================================================================================
// Binary Watch 
/*
Given a non-negative integer n which represents the number of LEDs that are currently on, return all possible times the watch could represent.
Example: Input: n = 1 Return: ["1:00", "2:00", "4:00", "8:00", "0:01", "0:02", "0:04", "0:08", "0:16", "0:32"] */
    vector<string> readBinaryWatch(int num) {
        vector<string> res;
        vector<int> hour{8, 4, 2, 1}, minute{32, 16, 8, 4, 2, 1};
        for (int i = 0; i <= num; ++i) {
            vector<int> hours = generate(hour, i);
            vector<int> minutes = generate(minute, num - i);
            for (int h : hours) {
                if (h > 11) continue;
                for (int m : minutes) {
                    if (m > 59) continue;
                    res.push_back(to_string(h) + (m < 10 ? ":0" : ":") + to_string(m));
                }
            }
        }
        return res;
    }
    vector<int> generate(vector<int>& nums, int cnt) {
        vector<int> res;
        helper(nums, cnt, 0, 0, res);
        return res;
    }
    void helper(vector<int>& nums, int cnt, int pos, int out, vector<int>& res) {
        if (cnt == 0) {
            res.push_back(out);
            return;
        }
        for (int i = pos; i < nums.size(); ++i) {
            helper(nums, cnt - 1, i + 1, out + nums[i], res);
        }
    }
//======================================================================================================
/* 306. Additive Number Input: "199100199" Output: true Explanation: The additive 
sequence is: 1, 99, 100, 199.  1 + 99 = 100, 99 + 100 = 199 */
    bool isAdditiveNumber(string num) {
        vector<long> generated;
        bool res = false;
        helper(num, generated, 0, res);
        return res;
    }
    
    void helper(const string& num, vector<long>& generated, int pos, bool& res)
    {
        if(res) return; // we may have found a valid anwser before
        if(pos >= num.size() && generated.size() >= 3)
        {
            res = true;
            return;
        }
        for(int i = pos; i < num.size(); ++i)
        {
            string str = num.substr(pos, i - pos + 1);
            // 0 cannot be start digit and value cannot be larger than 19 digits(long )
            if((str.size() > 1 && str[0] == '0') || str.size() > 19) break; 
            long curt = stol(str);
            int n = generated.size();
            if(n >= 2 && curt != (generated[n-1] + generated[n-2])) continue;
            generated.push_back(curt);
            helper(num, generated, i + 1, res);
            generated.pop_back();
        }        
    }
//===============================================================================================
/*526. Beautiful Arrangement 这道题给了我们1到N，总共N个正数，然后定义了一种优美排列方式，对于该排列中的所有数，
如果数字可以整除下标，或者下标可以整除数字，那么我们就是优美排列，让我们求出所有优美排列的个数*/
class Solution {
public:
    int countArrangement(int N) {
        int res = 0;
        vector<int> visited(N + 1, 0);
        helper(N, res, visited, 1);
        return res;
    }
    // pos is the position to put a value
    void helper(int& N, int& res, vector<int>& visited, int pos)
    {
        if(pos > N)
        {
            ++res;
            return;
        }
        //pick a number from 1 to N to see if it fits the rule
        for(int i = 1; i <= N; ++i)
        {
            if(!visited[i] && (i % pos == 0 || pos % i == 0))
            {
                visited[i] = 1;
                helper(N, res, visited, pos + 1);
                visited[i] = 0;
            }
        }
    }
};
//=================================================================================================
/*60. Permutation Sequence The set [1,2,3,...,n] contains a total of n! unique permutations.
By listing and labeling all of the permutations in order, we get the following sequence for n = 3:
"123"
"132"
"213"
"231"
"312"
"321"
Given n and k, return the kth permutation sequence. 
Given n will be between 1 and 9 inclusive.
Given k will be between 1 and n! inclusive.*/
class Solution {
public:
    /*
    a1 = k / (n - 1)!
    k1 = k % (n-1) !
    a2 = k1 / (n - 2)!
    k2 = k1 % (n - 2)!
    ...
    an-1 = kn-2 / 1!
    kn-1 = kn-2 % 1!
    an = kn-1 / 0!
    kn = kn-1 % 0! 
    https://www.cnblogs.com/grandyang/p/4358678.html
    */
    string getPermutation(int n, int k) {
        string res;
        string num = "123456789";
        vector<int> factorial(n, 1);
        for(int i = 1; i < n; i++)
        {
            factorial[i] = i * factorial[i-1];
        }
        k = k - 1; // we minus 1 because we strat from index 0
        for(int i = n; i >= 1; --i)
        {
            int j = k / factorial[i -1];
            k %= factorial[i - 1];
            res.push_back(num[j]);
            num.erase(j,1);  //string.erase(index, count)
        }
        return res;
    }
};
//================================================================================================
/* 44. Wildcard Matching '?' Matches any single character.
'*' Matches any sequence of characters (including the empty sequence).
Input:
s = "acdcb"
p = "a*c?b"
Output: false*/
class Solution {
public:
    bool isMatch(string s, string p) {
        return helper(s,p,0,0) > 1;
    }
    // helper return 0 on getting to the end of s but fialed to match
    // return 1 on not getting to the end of s and failed to macth
    // return 2 on match successfully
    int helper(string&s, string& p, int i, int j)
    {
        if(i == s.size())
        {   
            if (j == p.size()) 
            {// matched successfully
                return 2;
            }
            else if (p[j] != '*') 
            {// p is not finished, but s is finished, not match, return 0
                return 0;
            }
            else
            {
                while(j < p.size() && p[j] == '*') ++j;
                if(j == p.size())
                {// p has trailing '*', matched successfully
                    return 2;
                }
                else
                {
                    return 0;
                }
            }
        }
        if(j == p.size()) return 1;  // s is not finished and not match, return 1;
        if(s[i] == p[j] || p[j] == '?') return helper(s,p,i + 1, j +1);
        if(p[j] == '*')
        {
            if(j + 1 < p.size() && p[j+1] == '*')
            {// to jump continuous '*' because it is superfluous
                return helper(s,p,i,j+1);
            }
            for(int k = 0; k <= s.size() - i; ++k)
            {
                int res = helper(s,p,i+k,j+1);
                // prune, if s is finished, there is no need to continue back tracking it
                if (res == 0 || res == 2) return res;
            }
        }
        return 1;
    }
};
//================================================================================================
/*
691. Stickers to Spell Word
We are given N different types of stickers. Each sticker has a lowercase English word on it. 
You would like to spell out the given target string by cutting individual letters from your collection of stickers and rearranging them. 
You can use each sticker more than once if you want, and you have infinite quantities of each sticker. 
What is the minimum number of stickers that you need to spell out the target? If the task is impossible, return -1. 
Example 1: Input: ["with", "example", "science"], "thehat" Output: 3
Example 2: Input: ["notice", "possible"], "basicbasic" Output:-1 */
class Solution {
public:
    // we calculate char freq in each sticker, then for target, we traverse all
    // stickers. If first char of this target is not in this sticker, we jump.
    // Else, we format a new target with chars cannot be formed by current sticker
    // and go to next recursion. we need a map to store subtraget<->res for memo
    int minStickers(vector<string>& stickers, string target) {
        int n = stickers.size();
        vector<vector<int>> freq(n, vector<int>(26, 0));
        unordered_map<string, int> memo;  // substring <-> res
        memo[""] = 0;
        for(int i = 0 ; i < n; ++i)
        {
            for(char c : stickers[i])
            {
                ++freq[i][c - 'a'];
            }
        }
        return helper(n, target, memo, freq);
    }
    
    int helper(int n, string target, unordered_map<string, int>& memo, vector<vector<int>>& freq)
    {
        if(memo.count(target))
        {
            return memo[target];
        }
        int res = INT_MAX;
        // calculate freq of char in current target
        vector<int> count(26, 0);
        for(char c: target)
        {
            ++count[c - 'a'];
        }
        for(int i = 0; i < n; ++i)
        {
            // if first char of target not in this sticker we jump to next loop
            if(freq[i][target[0] - 'a'] == 0) continue;
            // form new target with chars not satisfied within curent sticker
            string new_target = "";
            for(int j = 0; j < 26; ++j)
            {
                if(count[j] - freq[i][j] > 0)
                {
                    new_target += string(count[j]-freq[i][j], j + 'a');
                }
            }
            int ans = helper(n, new_target, memo, freq);
            if(ans != -1)
            {
                res = min(ans + 1, res);
            }
        }
        if (res == INT_MAX) res = -1;
        memo[target] = res;
        return res;
    }
};
//=================================================================================================
/* 72. Edit Distance
Given two words word1 and word2, find the minimum number of operations required to convert word1 to word2.
You have the following 3 operations permitted on a word:
Insert a character;Delete a character;Replace a character
Example 1: Input: word1 = "horse", word2 = "ros" Output: 3
Explanation:  horse -> rorse (replace 'h' with 'r');rorse -> rose (remove 'r');rose -> ros (remove 'e') */
class Solution {
public:
    int minDistance(string word1, string word2) {
        int n = word1.size();
        int m = word2.size();
        // have a memorized vector to cache calculated result, prune backtracking
        vector<vector<int>> memo(n, vector<int>(m));
        return helper(word1, 0, word2, 0, memo);
    }
    
    int helper(string& word1, int i, string& word2, int j, vector<vector<int>>& memo)
    {
        if(i == word1.size()) return word2.size() - j;
        if(j == word2.size()) return word1.size() - i;
        //means this is already calculated
        if(memo[i][j] > 0) return memo[i][j];
        if(word1[i] == word2[j])
        {
            return helper(word1, i + 1, word2, j + 1, memo);
        }
        // insert is to insert a word at this place for word1, so compare i with j + 1
        int insertInst = helper(word1, i, word2, j + 1, memo);
        // delete is to delete a word at this place for word1, so compare i + 1 with j
        int deleteInst = helper(word1, i + 1, word2, j, memo);
        int replaceInst = helper(word1, i + 1, word2, j + 1, memo);
        int res = min(insertInst, min(deleteInst, replaceInst)) + 1;
        memo[i][j] = res;
        return res;
    }
};
class Solution {
public:
    int minDistance(string word1, string word2) {
        int m = word1.size();
        int n = word2.size();
        // dp[m][n] means the edit distance of the first mth chars of word1 to first nth chars of word2
        vector<vector<int>> dp(m + 1, vector<int>(n + 1));
        // if one string is empty, the corresponding distance is length of another string
        for(int i = 0; i <= m; ++i) {dp[i][0] = i;}
        for(int i = 0; i <= n; ++i) {dp[0][i] = i;}
        for(int i = 1; i <= m; ++i)
        {
            for(int j = 1; j <= n; ++j)
            {
                if(word1[i-1] == word2[j-1])
                {
                    dp[i][j] = dp[i-1][j-1];
                }
                else
                {
                    // insert means we add a char in word1, so we compare curt i -1 with next char of word2, j
                    // delete means we delete curt char(i -1) in word1, so we compare next(i) with word2 j-1
                    dp[i][j] = min(dp[i-1][j-1], min(dp[i-1][j], dp[i][j-1])) + 1;
                }
            }
        }
        return dp[m][n];
    }
};
//===============================================================================================================================
/* 140. Word Break II
Given a non-empty string s and a dictionary wordDict containing a list of non-empty words, add spaces in s to construct 
a sentence where each word is a valid dictionary word. Return all such possible sentences.
Note:
The same word in the dictionary may be reused multiple times in the segmentation.
You may assume the dictionary does not contain duplicate words.
Example 1: Input: s = "catsanddog" wordDict = ["cat", "cats", "and", "sand", "dog"]
Output:
[
  "cats and dog",
  "cat sand dog"
] */
class Solution {
public:
    vector<string> wordBreak(string s, vector<string>& wordDict) {
        // memo used to remember a string with its possible breaks
        unordered_map<string, vector<string>> memo;
        return helper(s, wordDict, memo);
    }
    vector<string> helper(string s, vector<string>& wordDict, unordered_map<string, vector<string>>& memo)
    {
        if (memo.count(s)) return memo[s];
        if (s.empty()) return {""};
        vector<string> res;
        for (auto& word : wordDict)
        {
            if(s.substr(0, word.size()) != word) continue;
            vector<string> anw = helper(s.substr(word.size()), wordDict, memo);
            for(auto& a : anw)
            {
                res.push_back(word + (a.empty() ? "" : " ") + a);
            }
        }
        memo[s] = res;
        return res;
    }
};
//====================================================================================================================
/* 139. Word Break
Given a non-empty string s and a dictionary wordDict containing a list of non-empty words, determine if s can be 
segmented into a space-separated sequence of one or more dictionary words.
Note:
The same word in the dictionary may be reused multiple times in the segmentation.
You may assume the dictionary does not contain duplicate words.
Example 1:Input: s = "leetcode", wordDict = ["leet", "code"] Output: true
Explanation: Return true because "leetcode" can be segmented as "leet code". */
class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        // put words into a set for O(1) access
        unordered_set<string> words;
        for(auto& w : wordDict)
        {
            words.insert(w);
        }
        // a memo to remember if we could break s[i,n] at ith index
        // -1 means we didn't store it yet, 0 means no, 1 means yes
        vector<int> memo(s.size(), -1);
        return helper(memo, words, s, 0);
    }
    // we traverse the string and for each substr we check if it is in words,
    // and recurssively call helper until we got the end of this string.
    bool helper(vector<int>& memo, unordered_set<string>& words, string& s, int pos)
    {
        if(pos >= s.size()) return true;
        if(memo[pos] != -1) return memo[pos];
        for(int i = pos + 1; i <= s.size(); ++i)
        {
            // string substr (size_t pos = 0, size_t len = npos) const;
            if(words.count(s.substr(pos, i - pos)) && helper(memo, words, s, i))
            {
                memo[pos] = 1;
                return true;
            }
        }
        memo[pos] = 0;
        return false; 
    }
};
//============================================================================================================
/* 126. Word Ladder II
Given two words (beginWord and endWord), and a dictionary's word list, find all shortest transformation sequence(s) from beginWord to endWord, such that:
Only one letter can be changed at a time Each transformed word must exist in the word list. Note that beginWord is not a transformed word.
Note:
Return an empty list if there is no such transformation sequence. All words have the same length.
All words contain only lowercase alphabetic characters. You may assume no duplicates in the word list.
You may assume beginWord and endWord are non-empty and are not the same.
Example 1:
Input:
beginWord = "hit",
endWord = "cog",
wordList = ["hot","dot","dog","lot","log","cog"]
Output:
[
  ["hit","hot","dot","dog","cog"],
  ["hit","hot","lot","log","cog"]
]
*/
// Actually this was done by bfs
class Solution {
public:
    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {
        vector<vector<string>> res;
        // store all words from wordList to have a O(1) access
        unordered_set<string> dict(wordList.begin(), wordList.end());
        // store used words in this level, they will be removed from dict
        // when we get into next level for a prune purpose. one word may
        // be used multiple times by different path so we use unordered_set
        unordered_set<string> level_used_words;
        
        // we use bfs to traverse all possible path, and prune a path if it is too long
        vector<string> path{beginWord};
        queue<vector<string>> paths;
        paths.push(path);
        int level = 1, min_level = INT_MAX;
        
        while(!paths.empty())
        {
            auto p = paths.front();
            paths.pop();
            // means we get into a new level, we need to remove all
            // last level used words from dict to avoid 
            if(p.size() > level)
            {
                for(auto& w : level_used_words) dict.erase(w);
                level_used_words.clear();
                level = p.size();  // renew level to current path size
                if (level > min_level) break;
            }

            // for every char in last word, we replace to a new char and check
            // if it can form a string thats inside dict
            string last_word = p.back();
            for(int i = 0 ; i < last_word.size(); ++i)
            {
                string candidate = last_word;
                for(char ch = 'a'; ch < 'z'; ++ch)
                {
                    candidate[i] = ch;
                    if(!dict.count(candidate)) continue;
                    level_used_words.insert(candidate);
                    auto new_path = p;
                    new_path.push_back(candidate);
                    if(candidate == endWord)
                    {
                        res.push_back(new_path);
                        min_level = level;
                    }
                    else
                    {
                        paths.push(new_path);
                    }
                }
            }
        }
        return res;
    }
};
//==================================================================================================================
