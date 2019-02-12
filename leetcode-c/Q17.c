#include "include/env.h"
/**
 *
 *����һ������������ 2-9 ���ַ����������������ܱ�ʾ����ĸ��ϡ�
 *
 * �������ֵ���ĸ��ӳ�����£���绰������ͬ����ע�� 1 ����Ӧ�κ���ĸ��
 *
 *
 *
 * ʾ��:
 *
 * ���룺"23"
 * �����["ad", "ae", "af", "bd", "be", "bf", "cd", "ce", "cf"].
 *
 * @author foxleezh
 * @date 2019-02-01.
 */


static char* Number[] = { "","","abc","def"
		,"ghi" ,"jkl" ,"mno"
		,"pqrs" ,"tuv" ,"wxyz" };

static char** t;


/**
 * ����˼·�����������������ȿ��ܻ��뵽ֱ�ӱ������У���д�Ĺ��̻ᷢ��ÿ�α���������һ�������ֻ���õݹ���
 *
 */
static void letter(char* digits, int* returnSize,char* tt) {
	//��digitsΪ��ʱ����ʾ���εݹ����
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
		//��������ʱ����
		memcpy(ts, tt, len + 1);
		tt[len]=Number[digits[0] - '0'][i];
		tt[len+1]=0;
		letter(digits+1, returnSize,tt);
		//�ݹ���ɺ�ָ�
		memcpy(tt, ts, len + 1);
		free(ts);
	}
}

static char** letterCombinations(char* digits, int* returnSize) {
	size_t len = strlen(digits);
	size_t size = 1;
	//��������Ϊ 4^digtis
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