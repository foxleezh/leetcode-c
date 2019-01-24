#include "include/env.h"
/*
 * ����һ���ַ��� s���ҵ� s ����Ļ����Ӵ�������Լ��� s ����󳤶�Ϊ 1000�� <br/>
 * <p/>
 * ʾ�� 1�� <br/>
 * <p/>
 * ����: "babad" <br/>
 * ���: "bab" <br/>
 * ע��: "aba" Ҳ��һ����Ч�𰸡� <br/>
 * ʾ�� 2�� <br/>
 * <p/>
 * ����: "cbbd" <br/>
 * ���: "bb" <br/>
 * <p/>
 */





/*
 * ����˼·�������Ӵ��������Ŷ����Ŷ���һ�����ַ�������aba,abba�������ǾͿ����ҵ�һ���±�����Ϊ���ģ��Ƚ����������ַ��Ƿ�һ�� <p/>
 *
 * ���һ���ͼ��������ң�ֱ����һ��Ϊֹ��Ȼ������Ӵ�����<p/>
 *
 * ���ڻ��ƵĶԳ��ԣ����ǿ��Ժ���һЩ�±꣬���� abba ���֣������Ƿ���b�ĺ��滹�и�b����ʱ����һ��b�Ͳ�������Ϊ���ļ�������<p/>
 *
 * ���⵱���Ƿ�����һ���㹻���Ļ����Ӵ��󣬱���40���ȣ���len-19������±�Ͳ�������<p/>
 *
 */
char* longestPalindrome(char* s) {
	int n = strlen(s);
	int maxLen = 0, start = 0;
	for (int i = 0; i < n;) {
		//����һЩ̫�̵��±�
		if (n - i <= maxLen / 2) {
			break;
		}
		int left = i, right = i;
		while (right < n - 1 && s[right + 1] == s[right]) {
			++right;
		}
		//���ظ����ַ�ֱ������
		i = right + 1;
		//Ѱ�һ��ƣ������ַ��Ա�
		while (right < n - 1 && left > 0 && s[right + 1] == s[left - 1]) {
			++right; --left;
		}
		if (maxLen < right - left + 1) {
			maxLen = right - left + 1;
			start = left;
		}
	}
	char* re = malloc(maxLen+1);
	re[maxLen] = '\0';
	memcpy(re,s+start,maxLen);
	return re;
}

void solution5() {
	char* re=longestPalindrome("abbc");
	ALog("%s",re);
	free(re);
}