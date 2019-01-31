#include "include/env.h"

/**
 * 编写一个函数来查找字符串数组中的最长公共前缀。
 * <p>
 * 如果不存在公共前缀，返回空字符串 ""。
 * <p>
 * 示例 1:
 * <p>
 * 输入: ["flower","flow","flight"]
 * 输出: "fl"
 * 示例 2:
 * <p>
 * 输入: ["dog","racecar","car"]
 * 输出: ""
 * 解释: 输入不存在公共前缀。
 *
 * @author foxleezh
 * @date 2019-01-31.
 */



/**
 * 解题思路：这题方法有很多，但是大多数方法时间复杂度都差不多
 *
 * 这里采用水平比较的方法，挨个对比，只要发现不一样的字符或者哪个字符到了末尾就返回
 *
 */
char* longestCommonPrefix(char** strs, int strsSize) {
	if (strs == NULL || strsSize == 0) {
		return "";
	}
	int len = strlen(strs[0]);
	for (int i = 0; i < len; i++) {
		char c = strs[0][i];
		for (int j = 1; j < strsSize; j++) {
			if (strs[j][i] != c) {
				char* re = malloc(sizeof(char)*(i+1));
				memcpy(re, strs[0], i);
				re[i] = 0;
				return re;
			}
		}
	}
	return strs[0];
}

void solution14() {
	char* strs[] = { "flower", "flow", "flight" };
	ALog("%s",longestCommonPrefix(strs,3));
}