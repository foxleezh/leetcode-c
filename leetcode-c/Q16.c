#include "include/env.h"


int cmpfun(int a,int b) {
	return *(int*)a - *(int*)b;
}

/**
 *
 * ����һ������ n ������������ nums �� һ��Ŀ��ֵ target���ҳ� nums �е�����������ʹ�����ǵĺ��� target ��ӽ����������������ĺ͡��ٶ�ÿ������ֻ����Ψһ�𰸡�
 *
 * ���磬�������� nums = [-1��2��1��-4], �� target = 1.
 *
 * �� target ��ӽ����������ĺ�Ϊ 2. (-1 + 2 + 1 = 2).
 *
 * @author foxleezh
 * @date 2019-01-31.
 */
int threeSumClosest(int* nums, int numsSize, int target) {
	qsort(nums,numsSize,sizeof(int),cmpfun);
	int res = nums[0] + nums[1] + nums[2];
	for (int i = 0; i < numsSize - 2; i++) {
		int left = i + 1;
		int right = numsSize - 1;
		if (i > 0 && nums[i] == nums[i - 1]) {
			continue;
		}
		while (left < right) {
			int threeSum = nums[i] + nums[left] + nums[right];
			//��ͺ���бȽ�
			if (threeSum > target) {
				right--;
			}
			else if (threeSum < target) {
				left++;
			}
			else {
				return target;
			}
			//�Ƚ�sum��target�Ĳ�ֵ������С��ֵ����
			res = abs(threeSum - target) > abs(res - target) ? res : threeSum;
		}
	}
	return res;
}

void solution16() {
	int nums[5]= { 1,1,-1,-1,3};
	ALog("%d", threeSumClosest(nums,5,-1));
}
