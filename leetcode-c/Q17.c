#include "include/env.h"
/**
 *
 *给定一个仅包含数字 2-9 的字符串，返回所有它能表示的字母组合。
 *
 * 给出数字到字母的映射如下（与电话按键相同）。注意 1 不对应任何字母。
 *
 *
 *
 * 示例:
 *
 * 输入："23"
 * 输出：["ad", "ae", "af", "bd", "be", "bf", "cd", "ce", "cf"].
 *
 * @author foxleezh
 * @date 2019-02-01.
 */


static char* Number[] = { "","","abc","def"
		,"ghi" ,"jkl" ,"mno"
		,"pqrs" ,"tuv" ,"wxyz" };

static char** t;


/**
 * 解题思路：看到这题我们首先可能会想到直接遍历就行，但写的过程会发现每次遍历次数不一样，这就只能用递归了
 *
 */
static void letter(char* digits, int* returnSize,char* tt) {
	//当digits为空时，表示单次递归结束
	if (digits[0] == 0)
	{
		if (tt[0]) {
			char* temp = malloc(strlen(tt) + 1);
			memcpy(temp,tt,strlen(tt)+1);
			t[(*returnSize)++] = temp;
		}
		return;
	}
	size_t len = strlen(Number[digits[0] - '0']);
	for (int i = 0; i < len; i++)
	{
		size_t len = strlen(tt);
		char* ts = malloc(sizeof(char)*(len + 1));
		ts[0] = 0;
		//将变量暂时保存
		memcpy(ts, tt, len + 1);
		tt[len]=Number[digits[0] - '0'][i];
		tt[len+1]=0;
		letter(digits+1, returnSize,tt);
		//递归完成后恢复
		memcpy(tt, ts, len + 1);
		free(ts);
	}
}

static char** letterCombinations(char* digits, int* returnSize) {
	size_t len = strlen(digits);
	size_t size = 1;
	//最大输出数为 4^digtis
	for (size_t i = 0; i < len; i++)
	{
		size *= 4;
	}
	t = malloc(sizeof(char*)*size);
	char* tt = malloc(sizeof(char)*len + 1);
	tt[0] = 0;
	letter(digits, returnSize,tt);
	free(tt);
	return t;
}


void solution17() {
	int* returnSize = malloc(sizeof(int));
	*returnSize = 0;
	letterCombinations("22", returnSize);
	for (size_t i = 0; i < *returnSize; i++)
	{
		ALog("%s", t[i]);
		free(t[i]);
	}
	free(t);
	free(returnSize);
}