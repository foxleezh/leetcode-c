#include "include/env.h"
/**
 * ����һ������ nums ��һ��ֵ val������Ҫԭ���Ƴ�������ֵ���� val ��Ԫ�أ������Ƴ���������³��ȡ�
 * <p>
 * ��Ҫʹ�ö��������ռ䣬�������ԭ���޸��������鲢��ʹ�� O(1) ����ռ����������ɡ�
 * <p>
 * Ԫ�ص�˳����Ըı䡣�㲻��Ҫ���������г����³��Ⱥ����Ԫ�ء�
 * <p>
 * ʾ�� 1:
 * <p>
 * ���� nums = [3,2,2,3], val = 3,
 * <p>
 * ����Ӧ�÷����µĳ��� 2, ���� nums �е�ǰ����Ԫ�ؾ�Ϊ 2��
 * <p>
 * �㲻��Ҫ���������г����³��Ⱥ����Ԫ�ء�
 * ʾ�� 2:
 * <p>
 * ���� nums = [0,1,2,2,3,0,4,2], val = 2,
 * <p>
 * ����Ӧ�÷����µĳ��� 5, ���� nums �е�ǰ���Ԫ��Ϊ 0, 1, 3, 0, 4��
 * <p>
 * ע�������Ԫ�ؿ�Ϊ����˳��
 * <p>
 * �㲻��Ҫ���������г����³��Ⱥ����Ԫ�ء�
 *
 * @author foxleezh
 * @date 2019-03-13.
 */

 /**
  * ����˼·���������һ��ⷨ��ֻ࣬�ǰѱȽϵ���ֵ��ɶ�ֵval
  *
  * @return
  */
int removeElement(int* nums, int numsSize, int val) {
	int index = 0;
	for (int i = 0; i < numsSize; i++) {
		if (nums[i] != val) {
			nums[index++] = nums[i];
		}
	}
	return index;
}


void solution27() {
	int nums[] = { 0,1,1,2,3,4,4,4 };
	int num = removeElement(nums, 8,1);
	char* toString = malloc(sizeof(char)*(num * 2 + 1));
	toString[0] = 0;
	char temp[3];
	for (int i = 0; i < num; i++) {
		sprintf(temp, "%d,", nums[i]);
		strcat(toString, temp);
	}
	ALog("%s", toString);
	free(toString);
}