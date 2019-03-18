#include "include/env.h"
/**
 * ʵ�� strStr() ������
 * <p>
 * ����һ�� haystack �ַ�����һ�� needle �ַ������� haystack �ַ������ҳ� needle �ַ������ֵĵ�һ��λ�� (��0��ʼ)����������ڣ��򷵻�  -1��
 * <p>
 * ʾ�� 1:
 * <p>
 * ����: haystack = "hello", needle = "ll"
 * ���: 2
 * ʾ�� 2:
 * <p>
 * ����: haystack = "aaaaa", needle = "bba"
 * ���: -1
 * ˵��:
 * <p>
 * �� needle �ǿ��ַ���ʱ������Ӧ������ʲôֵ�أ�����һ���������кܺõ����⡣
 * <p>
 * ���ڱ�����ԣ��� needle �ǿ��ַ���ʱ����Ӧ������ 0 ������C���Ե� strstr() �Լ� Java�� indexOf() ���������
 *
 * @author foxleezh
 * @date 2019-03-14.
 */

 /**
  * ��ȡnext����
  *
  * ���˼·����˫ָ�뷨����j��¼�ַ��������±꣬��k��¼���ַ�����ͷƥ��ĸ���
  *
  * ÿ��j��k��Ӧ���ַ�����ͬ�ˣ��ͽ�k������1�������ͬ�ˣ���ôk��ֵ��ԭ
  *
  */
static int* getNext(char* ps) {
	int p_len = strlen(ps);
	int* next = malloc(sizeof(int)*p_len);
	next[0] = -1;
	int j = 0;
	int k = -1;
	while (j < p_len - 1) {
		if (k == -1 || ps[j] == ps[k]) {//j��k��Ӧ�ַ���ͬ
			if (ps[++j] == ps[++k]) { // �������ַ����ʱҪ����
				next[j] = next[k];
			}
			else {
				next[j] = k;
			}
		}
		else {
			k = next[k];//��ԭk��ֵ�������ʱ����-1
		}
	}
	return next;
}


 /**
  * ����˼·����������ñ�����������forѭ����һ�Ƚ�ÿ���ַ���������ͬ��break��ֱ��������������
  *
  * ������˼·�򵥣���������Ч����������þ����KMP(���������ߵ����ּ��)�㷨
  *
  * KMP�㷨�Ƚϸ��ӣ��������ｲ���������ֻ���������˼
  *
  * �Ҿ���KMP�㷨�ǻ��ڱ������ģ�ֻ����ѭ����ʱ��i(���)�����ݣ�j(�ڲ�)���������ݣ��Ӷ���Ч������ÿһ�αȽϣ������ظ��Ƚϴ���
  *
  * ���������Ѿ�����ƥ�����Ч��Ϣ������iָ�벻���ݣ�ͨ���޸�jָ�룬��ģʽ���������ƶ�����Ч��λ�á�
  *
  * ��������ѵ�����ȷ��jָ���ڲ�ƥ������£�Ӧ�û��ݵ�λ�ã���Ҳ��KMP�㷨�ĺ���
  *
  * ����needle(��ҪѰ�ҵ�)�ַ�����ABCABD,������ȥƥ��ABCABCABDʱ����һ��ƥ������
  *
  *      i
  * ABCABCABD
  * ABCABD
  *      j
  * iͣ����C��λ�ã�jͣ����D��λ�ã�������Ǳ���i������jӦ���ص��ĸ�λ���أ������0
  *
  *      i
  * ABCABCABD
  *      ABCABD
  *      j
  *
  * �϶��������������Ӧ�ûص�2
  *
  *      i
  * ABCABCABD
  *    ABCABD
  *      j
  *
  * ����������ȷƥ�䣬Ҳ�������Ǹ�A��������Ĺؼ�������ôѰ��j��ȷ�Ļ��ݵ�
  *
  * ����Ĺ��ɾ��ǣ�������j��D��ʱ����ǰ��������ַ�AB�����Ǹ��ַ�����ͷ��AB��ͬ�ģ�����������j�ص�2��ʱ����Ȼ�ܹ�ƥ����i��ǰ�����ַ�
  *
  * �����ͳ�������˵�һ��ƥ��Ľ������Ϊ��һ��ƥ���Ѿ�֪��i��ǰ������AB
  *
  * �������ǵ��ص�����ҳ�j��ÿһ��λ�ò�ƥ��ʱӦ�û��ݵĵ㣬Ȼ���¼��һ��next��������
  *
  * ��ϸ����KMP�㷨�Ľ�����ο�https://www.cnblogs.com/yjiyjige/p/3263858.html
  */
static int strStr(char* haystack, char* needle) {
	int t_len = strlen(haystack);
	int p_len = strlen(needle);
	if ( p_len==0) {
		return 0;
	}
	int i = 0; // ������λ��
	int j = 0; // ģʽ����λ��
	int* next = getNext(needle);//��ȡnext����
	while (i < t_len && j < p_len) {
		if (j == -1 || haystack[i] == needle[j]) { // ��jΪ-1ʱ��Ҫ�ƶ�����i����ȻjҲҪ��0
			j++;
			i++;
		}
		else {
			j = next[j]; // j�ص�ָ��λ��
		}
	}
	if (j == p_len) {
		return i - j;
	}
	else {
		return -1;
	}
}




void solution28() {
	ALog("%d", strStr("acdbaacaaad", "aacaaad"));
}