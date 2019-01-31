#include "include/env.h"


int cmpfun(int a,int b) {
	return *(int*)a - *(int*)b;
}

/**
 *
 * 给定一个包括 n 个整数的数组 nums 和 一个目标值 target。找出 nums 中的三个整数，使得它们的和与 target 最接近。返回这三个数的和。假定每组输入只存在唯一答案。
 *
 * 例如，给定数组 nums = [-1，2，1，-4], 和 target = 1.
 *
 * 与 target 最接近的三个数的和为 2. (-1 + 2 + 1 = 2).
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
			//求和后进行比较
			if (threeSum > target) {
				right--;
			}
			else if (threeSum < target) {
				left++;
			}
			else {
				return target;
			}
			//比较sum与target的差值，将最小差值保存
			res = abs(threeSum - target) > abs(res - target) ? res : threeSum;
		}
	}
	return res;
}

void solution16() {
	int nums[5]= { 1,1,-1,-1,3};
	ALog("%d", threeSumClosest(nums,5,-1));
}
