////////////////////////some famous problems on Backtacking concept///////////////////////

//1. N-Queen Problem
public class Solution 
{
	private int N;
	public IList<IList<string>> SolveNQueens(int n) 
	{
		N = n;
		var res = new List<IList<string>>();
		char[][] board = new char[N][];
		for (int i = 0; i < N; i++)
		{
			board[i] = new char[N];
			Array.Fill(board[i], '.');
		}

		Helper(res, board, 0);
		return res;
	}

	private void Helper(IList<IList<string>> res, char[][] board, int rowIndex)
	{
		if (rowIndex == N)
		{
			IList<string> list = new List<string>();
			for (int i = 0; i < N; i++)
			{
				string s = new string(board[i]);
				list.Add(s);
			}
			res.Add((list));
			return;
		}

		for (int colIndex = 0; colIndex < N; colIndex++)
		{
			if (IsValid(board, rowIndex, colIndex))
			{
				board[rowIndex][colIndex] = 'Q';
				Helper(res, board, rowIndex + 1);
				board[rowIndex][colIndex] = '.';
			}
		}
	}

	private bool IsValid(char[][] board, int rowIndex, int colIndex)
	{
		for (int i = 0; i < rowIndex; i++)
			if (board[i][colIndex] == 'Q') return false;

		for (int i = rowIndex - 1, j = colIndex - 1; i >= 0 && j >= 0; i--, j--)
			if (board[i][j] == 'Q') return false;

		for (int i = rowIndex - 1, j = colIndex + 1; i >= 0 && j < N; i--, j++)
		{
			if (board[i][j] == 'Q') return false;
		}

		return true;
	}
}

//2. Regular expression Matching
bool isMatch(string s, string p) {
        int n = s.length(),m=p.length();
        int t[n+1][m+1];
        t[0][0]=true; 
        // if both of are 0 length
        
        if(m) t[0][1]=false;
        // if string length is 0 and pattern length is 1 it will always be 0
        
        // if length of string is greater than 1 ans pattern length is 0
        for(int i=1;i<=n;i++)
        {
            t[i][0]=false;
        }
        
        // A base case where string length is 0 but pattern length is not 0
        for(int j=2;j<=m;j++)
        {
            if(p[j-1]=='*') // consider example p = "a*b*c*" but s=""
                t[0][j] = t[0][j-2];
            else t[0][j] = false;
        }
        
        for(int i=1;i<=n;i++)
        {
            for(int j=1;j<=m;j++)
            {
        
                if(p[j-1]=='.'|| p[j-1]==s[i-1]) t[i][j] = t[i-1][j-1];
                // if two character matches or one of them is "."
                
                else if(p[j-1]=='*' && j>1){ // if there is * in pattern we have to check for character behind * 
                    if(p[j-2]==s[i-1] || p[j-2]=='.'){
                        t[i][j] = t[i][j-2] || t[i-1][j];
                    }
                    else{
                        t[i][j] = t[i][j-2];
                    }
                }
                else t[i][j]=false;
            }
        }
        return t[n][m];
    }
 
 //3. Wildcard Matching
 class Solution {
public:
    bool isMatch(string s, string p) {
        int sl = s.length(), pl = p.length();
		
		// match[i][j]: p[0..j-1] matches s[0..i-1] or not
        bool match[sl+1][pl+1];
        
        // "" matches ""
        match[0][0] = true;
        
        // for empty patten, all non-empty s shall be false
        for (int i = 1; i < sl + 1; i++) {
            match[i][0] = false;
        }
        
        // for empty s, all patterns that are not like "*****" shall be false
        for (int i = 1; i < pl + 1; i++) {
            match[0][i] = match[0][i - 1] && p[i - 1] == '*';
        }


        // the code explains itself
        for (int si = 1; si < sl + 1; si++) {
            for (int pi = 1; pi < pl + 1; pi++) {
                if (p[pi - 1] == '*') {
                    match[si][pi] = match[si - 1][pi] || match[si][pi - 1];
                } else if (p[pi - 1] == '?' || p[pi-1] == s[si - 1]) {
                    match[si][pi] = match[si- 1][pi - 1];
                } else {
                    match[si][pi] = false;
                }
            }
        }

        return match[sl][pl];
    }


};

//4. Sudoku Problem

class Solution {
    unordered_map<int, unordered_set<char>> rows, cols;
    unordered_map<int, unordered_map<int, unordered_set<char>>> zones;
public:
    void solveSudoku(vector<vector<char>>& board) {
        for (int r = 0; r < board.size(); r++) {
            for (int c = 0; c < board[0].size(); c++) {
                if (board[r][c] != '.') {
                    rows[r].insert(board[r][c]);
                    cols[c].insert(board[r][c]);
                    zones[r/3][c/3].insert(board[r][c]);
                }
            }
        }
        backtracking(0,0,board);
    }
    
    bool backtracking(int r, int c, vector<vector<char>>& board) {
        if (r == 9) return true;
        if (board[r][c] != '.') {
            if (backtracking((c+1==9?r+1:r), (c+1==9?0:c+1), board)==true) return true;
        } else {
            for (char digit = '1'; digit <= '9'; digit++) {
                if (rows[r].count(digit) > 0) continue;
                else if (cols[c].count(digit) > 0) continue;
                else if (zones[r/3][c/3].count(digit) > 0) continue;
                rows[r].insert(digit);
                cols[c].insert(digit);
                zones[r/3][c/3].insert(digit);
                board[r][c] = digit;
                if (backtracking((c+1==9?r+1:r), (c+1==9?0:c+1), board)==true) return true;
                board[r][c] = '.';
                zones[r/3][c/3].erase(digit);
                cols[c].erase(digit);
                rows[r].erase(digit);
            }
        }
        return false;
    }
};
