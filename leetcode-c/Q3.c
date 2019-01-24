#include "include/env.h"

/**
 * 给定一个字符串，请你找出其中不含有重复字符的 最长子串 的长度。
 * <p/>
 * 示例 1:
 *<p/>
 * 输入: "abcabcbb" <br/>
 * 输出: 3 <br/>
 * 解释: 因为无重复字符的最长子串是 "abc"，所以其长度为 3。<br/>
 * 示例 2:<br/>
 *<p/>
 * 输入: "bbbbb"<br/>
 * 输出: 1<br/>
 * 解释: 因为无重复字符的最长子串是 "b"，所以其长度为 1。<br/>
 * 示例 3:
 *<p/>
 * 输入: "pwwkew"<br/>
 * 输出: 3<br/>
 * 解释: 因为无重复字符的最长子串是 "wke"，所以其长度为 3。<br/>
 *      请注意，你的答案必须是 子串 的长度，"pwke" 是一个子序列，不是子串。<br/>
 */


/*
* 解题思想：找子串可以简化为找两个相同的字符，然后把这两个相同的字符位置相减，就得到长度
* 我们可以先遍历，将字符存放在HashMap中，key是字符，value是第一次出现的位置
* 遍历过程中把得到的字符去HashMap中找，如果有就把下标相减得到长度，然后把value替换为第二次出现的位置，把初始位置置为当前位置
* 把这些长度用max变量存下，不断与max比较得出最大值
* 在结束时将重复字符最后出现的位置与字符串长度比较
* 由于字符就128个，所以可以用数组代替HashMap
*/
int lengthOfLongestSubstring(char* s) {
	int len = strlen(s);
	int max = 0;
	int first = 0;
	int temp = 0;
	char current;
	int chars[128] = { 0 };
	for (int i = 0; i < len; i++) {
		current = s[i];
		int index = chars[current];
		if (index != 0) {
			temp = i - first;
			if (index >= first) {
				first = index;
			}
			if (temp > max) {
				max = temp;
			}
		}
		chars[current] = i + 1;
	}
	temp = len - first;
	if (temp > max) {
		max = temp;
	}
	return max;
}

void solution3() {
	ALog("%d", lengthOfLongestSubstring("abcabcbb"));
	ALog("%d", lengthOfLongestSubstring("bbbbb"));
	ALog("%d", lengthOfLongestSubstring("pwwkew"));
	ALog("%d", lengthOfLongestSubstring("dvdf"));
	ALog("%d", lengthOfLongestSubstring("aab"));
	ALog("%d", lengthOfLongestSubstring("a"));
	ALog("%d", lengthOfLongestSubstring(""));
	ALog("%d", lengthOfLongestSubstring("asjrgapa"));
	ALog("%d", lengthOfLongestSubstring("abba"));
}
