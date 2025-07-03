//
// Created by user on 2022/8/17.
//

#include "stringdeal.h"


int qiuzuichanghuiwenshu(char *ch_){  //求字符的最长回文数
    char *ch;
    int maxLen = 1,maxLen_temp;
    strcpy(ch,ch_);
    int len = strlen(ch);
    int left,right;
        for(int i = 1;i<len-1;i++){
            left = i-1;right = i+1;
            maxLen_temp = 1;
            while(left>=0 && right<len && ch[left] == ch[right]){
                    maxLen_temp +=2;
                    --left;++right;
            }//while
            if(maxLen_temp > maxLen)
                maxLen = maxLen_temp;
        }//for
    return maxLen;
}
