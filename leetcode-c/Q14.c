#include "include/env.h"

/**
 * ��дһ�������������ַ��������е������ǰ׺��
 * <p>
 * ��������ڹ���ǰ׺�����ؿ��ַ��� ""��
 * <p>
 * ʾ�� 1:
 * <p>
 * ����: ["flower","flow","flight"]
 * ���: "fl"
 * ʾ�� 2:
 * <p>
 * ����: ["dog","racecar","car"]
 * ���: ""
 * ����: ���벻���ڹ���ǰ׺��
 *
 * @author foxleezh
 * @date 2019-01-31.
 */



/**
 * ����˼·�����ⷽ���кܶ࣬���Ǵ��������ʱ�临�Ӷȶ����
 *
 * �������ˮƽ�Ƚϵķ����������Աȣ�ֻҪ���ֲ�һ�����ַ������ĸ��ַ�����ĩβ�ͷ���
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