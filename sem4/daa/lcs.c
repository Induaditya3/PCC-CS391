#include <stdio.h>
#include <sys/param.h>

char *str1 = "abcdefg";
char *str2 = "ebdfg";

// returns length of longest common subsequence
// i, j are indices of str1 and str2 respectively
int lcs(int i, int j){
    // base case: current character of any of the string is `null terminator`
    if (str1[i] == '\0' || str2[j] == '\0')
        return 0;
    else{
        // recursive steps:
        // both character match: increase length by 1 and look at next character of the both number
        if (str1[i] == str2[j])
            return 1 + lcs(i+1, j+1);
        else
            return MAX(lcs(i+1, j), lcs(i, j+1));
    }
}
int main(){

    int len = lcs(0, 0);
    printf("%d\n",len);
    return 0;
}
