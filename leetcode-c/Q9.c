#include "include/env.h"
/**
 * �ж�һ�������Ƿ��ǻ���������������ָ���򣨴������ң��͵��򣨴������󣩶�����һ����������
 * <p>
 * ʾ�� 1:
 * <p>
 * ����: 121
 * ���: true
 * ʾ�� 2:
 * <p>
 * ����: -121
 * ���: false
 * ����: �������Ҷ�, Ϊ -121 �� ���������, Ϊ 121- �����������һ����������
 * ʾ�� 3:
 * <p>
 * ����: 10
 * ���: false
 * ����: ���������, Ϊ 01 �����������һ����������
 *
 * @author foxleezh
 * @date 2019-01-29.
 */



/**
 * ����˼·������������˼·��һ��ת��Ϊ�ַ�����Ȼ��Ƚ�ǰ���ַ��Ƿ�һ�¼��ɣ��򵥷��㣬����֮������ת�ַ�����ʱ
 *
 * �ڶ��־��ǰ����ַ�ת��Ȼ��ȽϷ�ת�������ԭ���Ƿ�һ��������������������ת��Խ�������
 *
 * �����ǿ���ֻ��תһ�룬��Ϊ������ǰ��϶�һ������ô֪����һ�����أ����ǿ��ԱȽ�ǰ�����������������ǰ����˵����һ����
 *
 */
bool isPalindrome(int x) {
	if (x < 0) {
		return false;
	}
	//        �ַ����������
	//        String s=x+"";
	//        int len=s.length();
	//        if(len==1){
	//            return true;
	//        }
	//        for (int i = 0; i < len/2; i++) {
	//            //�Ƚ�ǰ������
	//            if(s.charAt(i)!=s.charAt(len-i-1)){
	//                return false;
	//            }
	//        }
			//β��Ϊ0�Ŀ϶����ǻ���
	if (x % 10 == 0 && x != 0) {
		return false;
	}
	int last = 0;
	//��last��x��ʱ��˵����һ����
	while (last < x) {
		//ȡ���������last
		last = last * 10 + x % 10;
		x /= 10;
	}
	//last==x��ʾ������last/10==x��ʾż��
	return last == x || last / 10 == x;
}

void solution9() {
	ALog("%d",true);
	ALog("%d", isPalindrome(100));
	ALog("%d", isPalindrome(10));
	ALog("%d", isPalindrome(1));
	ALog("%d", isPalindrome(12021));
	ALog("%d", isPalindrome(1221));
	ALog("%d", isPalindrome(1211));
}