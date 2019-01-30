#include "include/env.h"
/**
 * ����һ���ַ��� (s) ��һ���ַ�pattern (p)��ʵ��֧�� '.' �� '*' ��������ʽƥ�䡣
 * <p>
 * '.' ƥ�����ⵥ���ַ���
 * '*' ƥ���������ǰ���Ԫ�ء�
 * ƥ��Ӧ�ø��������ַ��� (s) �������ǲ����ַ�����
 * <p>
 * ˵��:
 * <p>
 * s ����Ϊ�գ���ֻ������ a-z ��Сд��ĸ��
 * p ����Ϊ�գ���ֻ������ a-z ��Сд��ĸ���Լ��ַ� . �� *��
 * ʾ�� 1:
 * <p>
 * ����:
 * s = "aa"
 * p = "a"
 * ���: false
 * ����: "a" �޷�ƥ�� "aa" �����ַ�����
 * ʾ�� 2:
 * <p>
 * ����:
 * s = "aa"
 * p = "a*"
 * ���: true
 * ����: '*' �����ƥ���������ǰ���Ԫ��, ������ƥ�� 'a' �����, �ظ� 'a' һ��, �ַ����ɱ�Ϊ "aa"��
 * ʾ�� 3:
 * <p>
 * ����:
 * s = "ab"
 * p = ".*"
 * ���: true
 * ����: ".*" ��ʾ��ƥ���������('*')�����ַ�('.')��
 * ʾ�� 4:
 * <p>
 * ����:
 * s = "aab"
 * p = "c*a*b"
 * ���: true
 * ����: 'c' ���Բ����ظ�, 'a' ���Ա��ظ�һ�Ρ���˿���ƥ���ַ��� "aab"��
 * ʾ�� 5:
 * <p>
 * ����:
 * s = "mississippi"
 * p = "mis*is*p*."
 * ���: false
 *
 * @author foxleezh
 * @date 2019-01-29.
 */


bool matchChar(char* str, int i, char* pattern, int j, size_t m, size_t n) {

	// �ַ�����patternͬʱ����ĩβ,��ȫƥ��
	if (i == m && j == n) {
		return true;
	}
	// pattern�ȵ�ĩβ�����ﷵ��false����ʾȫƥ��
	if (i != m && j == n) {
		return false;
	}
	// ��һ���ַ���*
	if (j + 1 < n && pattern[j + 1] == '*') {
		//��ǰ�ַ�ƥ�䣬�����������
		if ((i != m && str[i] == pattern[j]) ||
			(i != m && pattern[j] == '.')) {
			return matchChar(str, i, pattern, j + 2, m, n) ||
				matchChar(str, i + 1, pattern, j + 2, m, n) ||
				matchChar(str, i + 1, pattern, j, m, n);
		}
		else {
			//��ǰ�ַ���ƥ�䣬pattern�±��ƶ�2λ
			return matchChar(str, i, pattern, j + 2, m, n);
		}
	}
	else if ((i != m && str[i] == pattern[j]) ||
		(i != m && pattern[j] == '.')) {
		// ��һ���ַ�����*����ǰ�ַ�ƥ�䣬�����±�ͬʱ�ƶ���λ
		return matchChar(str, i + 1, pattern, j + 1, m, n);
	}
	//�����������������
	return false;
}


/**
 * ����˼·����pattern�е���һ���ַ����ǡ�*��ʱ��
 *  1�� ����ַ�����ǰ�ַ���pattern�еĵ�ǰ�ַ���ƥ�䣬����pattern�ַ��ǡ�.��,��ô�ַ���ָ���patternָ�붼����һ���ַ�
 *  2�� ����ַ�����ǰ�ַ���pattern�е�ǰ�ַ���ƥ�䣬ֱ�ӷ���false��
 *
 * ��pattern�е���һ���ǡ�*��ʱ��
 * 1������ַ�����ǰ�ַ���pattern��ǰ�ַ�ƥ�䣬������3��ƥ�䷽ʽ��
 *     a��patternָ�����2�ַ����൱��x*�����ԣ�
 *     b���ַ���ָ�����1�ַ���patternָ�����2�ַ�, �൱��x*ƥ��һλ�����
 *     c���ַ���ָ�����1�ַ���pattern���䣬������ƥ���ַ���һλ���൱��x*һֱƥ�䵽���
 * 2������ַ�����ǰ�ַ���pattern��ǰ�ַ���ƥ�䣬��patternָ�����2���ַ�������ƥ�䡣
 *
 * ��ʵ����Ĺؼ�������*�Ĵ�����Ϊ������ƥ��0��������Ǿ�Ҫ��N����ƥ��Ŀ��ܣ������õݹ鴦��ȽϺ�
 *
 * �ݹ�Ľ���������±�ͬʱ����������true������ַ��±��Ƚ���������false,���pattern�±��Ƚ���������false(ȫƥ��)������true(����ƥ��)
 */
bool isMatch0(char* s, char* p) {
	if (!strcmp(p, ".*")) {
		return true;
	}
	// ����ַ�������pattern�ǿյģ���ô�϶�û��ƥ���
	if (s == NULL || p == NULL) {
		return false;
	}
	int i = 0, j = 0;
	size_t m = strlen(s);
	size_t n = strlen(p);
	return matchChar(s, i, p, j, m, n);
}






/**
 * ����˼·����������õݹ鷨���������ö�̬�黮��˼�������
 *
 * �ο� https://leetcode.com/problems/regular-expression-matching/discuss/5684/9-lines-16ms-c-dp-solutions-with-explanations
 *
 * ���Ƕ��� dp[i][j] ��ά���飬��� s[0..i)��p[0..j) ÿһλ��ƥ����ô���������ƥ��. ����������һ�������㣬��ƥ��
 *
 * ˼·��֮ǰ�ݹ�һ��
 *
 * ��ά���� dp[i][j] �и���Ϊtrue�������ǣ�
 * 1��pattern���ַ�Ϊ��*��ʱ��
 *    a��dp[i][j] = dp[i][j - 2]   ,����*��ƥ����0�Σ�pֱ��������λ
 *    b��dp[i][j] = dp[i - 1][j] && (s[i - 1] == p[j - 2] || p[j - 2] == '.')  ������*��ƥ����1�μ����ϣ�p������s�����ƶ�һλ
 * 2��pattern���ַ���Ϊ��*��ʱ��
 *   dp[i][j] = dp[i - 1][j - 1] && (s[i - 1] == p[j - 1] || p[j - 1] == '.'); ��s��pͬʱ�����ƶ�һλ
 *
 * �����dp[m][n]��ֵΪtrueʱ(m,nΪs��p���ַ�����)��˵��������ȫƥ��
 *
 */
bool isMatch1(char* s, char* p) {
	size_t m = strlen(s);
	size_t n = strlen(p);
	bool** dp;
	dp = malloc(sizeof(bool*)*(m + 1));
	for (size_t i = 0; i < m + 1; i++)
	{
		dp[i] = calloc(sizeof(bool), (n + 1));
	}
	dp[0][0] = true;
	for (int i = 0; i <= m; i++) {
		for (int j = 1; j <= n; j++) {
			if (p[j - 1] == '*') {
				//����ǡ�*�������ж��Ƿ��ظ�0�λ����ظ���Σ�����ظ���εĻ�������֤p[0:j]��s[0:i - 1]Ҳ�ܹ�ƥ�䣩
				dp[i][j] = dp[i][j - 2] || (i > 0 && (s[i - 1] == p[j - 2] || p[j - 2] == '.') && dp[i - 1][j]);
			}
			else {
				//������ǡ�*������ֱ�ӿ���Ӧ���Ƿ�ƥ��, i = 0 �ǳ�ʼ״̬
				dp[i][j] = i > 0 && (s[i - 1] == p[j - 1] || p[j - 1] == '.')
					&& dp[i - 1][j - 1];
			}
		}
	}
	bool re = dp[m][n];
	for (size_t i = 0; i < m + 1; i++)
	{
		free(dp[i]);
	}
	free(dp);
	return re;
}


/**
 * ��̬�黮�����棬ֻ�������������ؽ��漴�ɣ�����һ��ʱ�䣬��С����ռ�
 */
bool isMatch2(char* s, char* p) {
	size_t m = strlen(s);
	size_t n = strlen(p);
	bool** dp;
	dp = malloc(sizeof(bool*) * 2);
	for (size_t i = 0; i < 2; i++)
	{
		dp[i] = calloc(sizeof(bool), (n + 1));
	}
	dp[0][0] = true;
	int cur = 0, pre = 0;
	for (int i = 0; i <= m; i++) {
		//�����������ؽ���
		cur = i % 2;
		pre = (i + 1) % 2;
		if (i > 1) {
			for (int j = 0; j <= n; j++) {
				dp[cur][j] = false;
			}
		}
		for (int j = 1; j <= n; j++) {
			if (p[j - 1] == '*') {
				dp[cur][j] = dp[cur][j - 2] || (i > 0 && (s[i - 1] == p[j - 2] || p[j - 2] == '.') && dp[pre][j]);
			}
			else {
				dp[cur][j] = i > 0 && (s[i - 1] == p[j - 1] || p[j - 1] == '.')
					&& dp[pre][j - 1];
			}
		}
	}
	cur = dp[cur][n];
	free(dp[0]);
	free(dp[1]);
	free(dp);
	return cur;
}


/**
 * ��̬�黮�����棬ֻ��һ������ǰ���漴��
 */
bool isMatch3(char* s, char* p) {
	size_t m = strlen(s);
	size_t n = strlen(p);
	bool* cur = calloc(sizeof(bool), m + 1);
	cur[m] = true;
	for (int j = n - 1; j >= 0; j--) {
		if (p[j] == '*') {
			for (int i = m - 1; i >= 0; i--) {
				cur[i] = cur[i] || cur[i + 1] && (s[i] == p[j - 1] || p[j - 1] == '.');
			}
			j--;
		}
		else {
			for (int i = 0; i < m; i++) {
				cur[i] = cur[i + 1] && (s[i] == p[j] || p[j] == '.');
			}
			cur[m] = false;
		}
	}
	bool temp = cur[0];
	free(cur);
	return temp;
}


/**
 * ��̬�黮�����棬ֻ��һ�������һЩtemp����
 */
bool isMatch(const char* s, const char* p) {
	size_t m = strlen(s);
	size_t n = strlen(p);
	bool* cur = calloc(sizeof(bool), n + 1);
	bool temp, pre;
	for (int i = 0; i <= m; i++) {
		pre = cur[0];
		cur[0] = i == 0;
		for (int j = 1; j <= n; j++) {
			temp = cur[j];
			if (p[j - 1] == '*') {
				cur[j] = cur[j - 2] || (i > 0 && cur[j] && (s[i - 1] == p[j - 2] || p[j - 2] == '.'));
			}
			else {
				cur[j] = i > 0 && pre && (s[i - 1] == p[j - 1] || p[j - 1] == '.');
			}
			pre = temp;
		}
	}
	temp = cur[n];
	free(cur);
	return temp;
}

void solution10() {
	ALog("%d", isMatch("aa", "a"));
	ALog("%d", isMatch("aa", "a.*.*"));
	ALog("%d", isMatch("aab", ".*"));
	ALog("%d", isMatch("aab", "c*a*b"));
	ALog("%d", isMatch("mississippi", "mis*is*p*."));
	ALog("%d", isMatch("bb", ".bab"));
}