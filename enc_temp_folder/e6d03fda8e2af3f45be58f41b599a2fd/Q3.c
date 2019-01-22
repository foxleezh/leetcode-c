#include "include/env.h"

int lengthOfLongestSubstring(char* s) {
	int len = strlen(s);
	int max = 0;
	int first = 0;
	int temp = 0;
	char current;
	int chars[128] = {0};
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
	ALog("%d",lengthOfLongestSubstring("abcabcbb"));
	ALog("%d",lengthOfLongestSubstring("bbbbb"));
	ALog("%d",lengthOfLongestSubstring("pwwkew"));
	ALog("%d",lengthOfLongestSubstring("dvdf"));
	ALog("%d",lengthOfLongestSubstring("aab"));
	ALog("%d",lengthOfLongestSubstring("a"));
	ALog("%d",lengthOfLongestSubstring(""));
	ALog("%d",lengthOfLongestSubstring("asjrgapa"));
	ALog("%d",lengthOfLongestSubstring("abba"));
}
