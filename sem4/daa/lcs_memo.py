# longest common subsequence problem using memoization

def lcs_memo(str1, str2):
    cols = len(str1)
    rows = len(str2)
    dp = [[None for j in range(cols)] for i in range(rows)]

    def lcs(i, j):
        if i== rows or j == cols: # adjusting extra row and col for calculating valid indices
            return 0
        elif str2[i] == str1[j]:
            if dp[i][j] is None:
                dp[i][j] = 1 + lcs(i+1, j+1)
        else:
            if dp[i][j] is None:
                dp[i][j] = max(lcs(i+1, j), lcs(i, j+1))
        return dp[i][j]

    
    # reconstructing the string by backtracking
    def lcs_str():
        lcs_str = []
        i = rows-1
        j = cols-1
        while i > 0 and j > 0:
            # if current char match then go diagonally upward
            if str1[i] == str2[j]:
                lcs_str.append(str1[i])
                i -= 1
                j -= 1
            # if char does not match, traverse based on whichever has greater dp value
            elif dp[i][j-1] > dp[i-1][j]:
                j -= 1
            else:
                i -= 1
        return "".join(lcs_str)[::-1]
    lcs_len = lcs(0, 0)
    return lcs_len, lcs_str()

print(lcs_memo("AGGTAB", "GXTXAYB"))
        
