#include<iostream>
#include<string>
#include<vector>

std::string longestCommonPrefix(std::vector<std::string>& strs) {
        int count = strs.size();
        int len = strs[0].size();
        char c;
        for(int i = 0; i < len; ++i)
        {
            c = strs[0][i];
            for(int j = 1; j < count; ++j)
            {
                if(strs[j][i] != c)
                {
                    return strs[0].substr(0,i);
                }
            }
        }
        return strs[0];
    }

int main()
{
    std::vector<std::string> strs = {"flower","flow","flight"};
    std::string a("hello");
    std::cout<< longestCommonPrefix(strs) << std::endl;
    return 0;
}