#include "include/env.h"
/**
 * ����һ�� 32 λ���з�������������Ҫ�����������ÿλ�ϵ����ֽ��з�ת��
 * <p>
 * ʾ�� 1:
 * <p>
 * ����: 123
 * ���: 321
 * ʾ�� 2:
 * <p>
 * ����: -123
 * ���: -321
 * ʾ�� 3:
 * <p>
 * ����: 120
 * ���: 21
 *
 * @author foxleezh
 * @date 2019-01-29.
 */



 /**
  * ����˼·�� ������ת�������Ϊ�Ƚ������ջ�ṹ�����ǿ�����popһλ������Ȼ��push����һ��������
  *
  * pop�Ļ�����%10��/10
  *
  * push�Ļ�����*10��+pop
  *
  * ��push��ʱ����ܻ���������λ���������������Ҫ�Ƚ�һ��int�������Сֵ
  *
  */
int reverse(int x) {
	int result = 0;
	int pop = 0;
	while (x != 0) {
		//pop����
		pop = x % 10;
		x = x / 10;
		//�������Сֵ�Ƚ�
		if (result > INT32_MAX / 10 || result < INT32_MIN / 10) {
			return 0;
		}
		//push����
		result = result * 10 + pop;
	}
	return result;
}

void solution7() {
	ALog("%d",reverse(123));
}