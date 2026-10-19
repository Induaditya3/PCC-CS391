# dp table methd to find length and string of longest common subsequence


def lcs(str1, str2):
    rows = len(str1) + 1
    cols = len(str2) + 1

    # initialize dp table
    dp = [ [0]* cols for _ in range(rows)]

    for i in range(1,rows):
        for j in range(1,cols):
            # current letter matches
            if str1[i-1] == str2[j-1]:
                dp[i][j] = 1 + dp[i-1][j-1]
            else:
                dp[i][j] = max(dp[i-1][j], dp[i][j-1])


    # reconstructing the string by backtracking
    lcs_str = []
    i = rows-1
    j = cols-1
    while i > 0 and j > 0:
        # if current char match then go diagonally upward
        if str1[i-1] == str2[j-1]:
            lcs_str.append(str1[i-1])
            i -= 1
            j -= 1
        # if char does not match, traverse based on whichever has greater dp value
        elif dp[i][j-1] > dp[i-1][j]:
            j -= 1
        else:
            i -= 1

    return dp[rows-1][cols-1], "".join(lcs_str)[::-1]

X = "monkey"
Y = "money"
length, sequence = lcs(X, Y)
print(f"LCS Length: {length}")
print(f"LCS String: {sequence}")
