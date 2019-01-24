#include "include/env.h"
/**
 * ��һ�������ַ������ݸ������������Դ������¡������ҽ��� Z �������С�
 * <p/>
 * ���������ַ���Ϊ "LEETCODEISHIRING" ����Ϊ 3 ʱ���������£�
 * <p/>
 * L   C   I   R   <br/>
 * E T O E S I I G <br/>
 * E   D   H   N <br/>
 * ֮����������Ҫ�����������ж�ȡ��������һ���µ��ַ��������磺"LCIRETOESIIGEDHN"��
 * <p/>
 * ����ʵ��������ַ�������ָ�������任�ĺ�����
 * <p/>
 * string convert(string s, int numRows); <br/>
 * ʾ�� 1: <br/>
 * <p/>
 * ����: s = "LEETCODEISHIRING", numRows = 3 <br/>
 * ���: "LCIRETOESIIGEDHN" <br/>
 * ʾ�� 2:
 * <p/>
 * ����: s = "LEETCODEISHIRING", numRows = 4 <br/>
 * ���: "LDREOEIIECIHNTSG" <br/>
 * ����:
 * <p/>
 * L     D     R <br/>
 * E   O E   I I <br/>
 * E C   I H   N <br/>
 * T     S     G <br/>
 */


 /**
  * ����˼·�������ȹ۲�Z �������е�һЩ�������������£��ٴ������ϣ���һ��V���ͣ������ظ����V����
  * <p/>
  * V����ÿ�����ڵĳ�����circleLen=(rows-1)*2
  * <p/>
  * ÿ���������ڵ�һ�к����һ�ж�ֻ��һ���ַ��������ж��������ַ�
  * <p/>
  * ��ȻҪ����һ��һ������������Ǿ�һ������, ��V���͵�ÿһ���ַ���ԭʼ�ַ����е�λ���ù�ʽ��ʾ����
  *  <p/>
  * i-��ǰ��,j-��ǰ����,c-���ڳ���=8
  * <p/>
  * 0============0*8+0                                    <br/>
  * 1===7========0*8+1====0*8+(8-1)                       <br/>
  * 2==6=========0*8+2===0*8+(8-2)                        <br/>
  * 3=5==========0*8+3==0*8+(8-3)                         <br/>
  * 4============0*8+4                                    <br/>
  * <p/>
  * �����ܽ����ֻҪ��V���͵ĵ�һ�У���ԭ�ַ����е�λ��Ϊj*c + i    <br/>
  * ֻҪ��V���͵ĵڶ��У���ԭ�ַ����е�λ��Ϊj*c+(c-i)
  * <p/>
  * �����������ڵ��������������������ʱ����Ӧλ�þ�û���ַ�
  *
  */
char* convert(char* s, int numRows) {
	int len = strlen(s);
	if (len <= numRows || numRows == 1) {
		return s;
	}
	char* newString = malloc(len+1);
	newString[len] = '\0';
	int circleLen = (numRows - 1) * 2;
	int start = 0;
	for (int i = 0; i < numRows; i++) {
		//V���͵�һ��Ӧ������j+i<len������ÿ��j+=circleLen,����j*c+i�����j+i
		for (int j = 0; j + i < len; j += circleLen) {
			newString[start++] = s[j + i];
			//ͬ��V���͵ڶ���Ӧ������j + (circleLen - i)< len,���ҵ�һ�к����һ��û�еڶ���
			if (i != 0 && i != numRows - 1 && j + circleLen - i < len) {
				newString[start++] = s[j + circleLen - i];
			}
		}
	}
	return newString;
}

void solution6() {
	char* re=convert("ABCDEFG", 3);
	ALog("%s",re);
	free(re);
}