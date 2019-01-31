#include "include/env.h"
/**
 * 给定一个包含 n 个整数的数组 nums，判断 nums 中是否存在三个元素 a，b，c ，使得 a + b + c = 0 ？找出所有满足条件且不重复的三元组。
 * <p>
 * 注意：答案中不可以包含重复的三元组。
 * <p>
 * 例如, 给定数组 nums = [-1, 0, 1, 2, -1, -4]，
 * <p>
 * 满足要求的三元组集合为：
 * [
 * [-1, 0, 1],
 * [-1, -1, 2]
 * ]
 *
 * @author foxleezh
 * @date 2019-01-31.
 */

void merge(int arr[], int low, int mid, int high) {
	int i, k;
	int *tmp = (int *)malloc((high - low + 1) * sizeof(int));
	//申请空间，使其大小为两个
	int left_low = low;
	int left_high = mid;
	int right_low = mid + 1;
	int right_high = high;

	for (k = 0; left_low <= left_high && right_low <= right_high; k++) {  // 比较两个指针所指向的元素
		if (arr[left_low] <= arr[right_low]) {
			tmp[k] = arr[left_low++];
		}
		else {
			tmp[k] = arr[right_low++];
		}
	}

	if (left_low <= left_high) {  //若第一个序列有剩余，直接复制出来粘到合并序列尾
	//memcpy(tmp+k, arr+left_low, (left_high-left_low+l)*sizeof(int));
		for (i = left_low; i <= left_high; i++)
			tmp[k++] = arr[i];
	}

	if (right_low <= right_high) {
		//若第二个序列有剩余，直接复制出来粘到合并序列尾
		//memcpy(tmp+k, arr+right_low, (right_high-right_low+1)*sizeof(int));
		for (i = right_low; i <= right_high; i++)
			tmp[k++] = arr[i];
	}

	for (i = 0; i < high - low + 1; i++)
		arr[low + i] = tmp[i];
	free(tmp);
	return;
}


//归并排序
void merge_sort(int arr[], unsigned int first, unsigned int last) {
	int mid = 0;
	if (first < last) {
		mid = (first + last) / 2; /* 注意防止溢出 */
		merge_sort(arr, first, mid);
		merge_sort(arr, mid + 1, last);
		merge(arr, first, mid, last);
	}
	return;
}

/**
 * 解题思路：这题可以简化为求两数之和，我们取一个数然后变为它的相反数，如果有另外两个数之和等于这个相反数，那么这三个数之和就为0
 * <p>
 * 但是问题中涉及到不能有相同的元素，比如[0,1,-1]和[0,-1,1]是不能出现的，但是[2,2,-4]是可以的，所以题意要清楚
 * <p>
 * 为了避免相同的组合出现，最好的办法就是先排序，排序后在遍历过程中跳过相同的数，就能避免出现相同结果
 *
 * 由于排过序，我们可以采用两头往中间走的形式，减少二次遍历
 *
 */
int** threeSum(int* nums, int numsSize, int* returnSize) {
	*returnSize = 0;
	if (numsSize < 3) {
		return malloc(sizeof(int*));
	}
	int** res = malloc(sizeof(int*)*(numsSize*(numsSize - 1)*(numsSize - 2) / 6));
	merge_sort(nums, 0, numsSize - 1);
	for (int i = 0; i < numsSize; i++) {
		//跳过大于0的开始，因为三个正数相加不可能等于0
		if (nums[i] > 0) {
			break;
		}
		//跳过相同的数，避免重复
		if (i > 0 && nums[i] == nums[i - 1]) {
			continue;
		}
		//两头往中间走，j在左，k在右
		int j = i + 1;
		int k = numsSize - 1;
		int target = 0 - nums[i];
		while (j < k) {
			if (nums[j] + nums[k] == target) {
				res[*returnSize] = malloc(sizeof(int) * 3);
				res[*returnSize][0] = nums[i];
				res[*returnSize][1] = nums[j];
				res[*returnSize][2] = nums[k];
				(*returnSize)++;
				//跳过相同的数
				while (j < k && nums[j] == nums[j + 1]) {
					j++;
				}
				//跳过相同的数
				while (j < k && nums[k] == nums[k - 1]) {
					k--;
				}
				j++;
				k--;
			}
			else if (nums[j] + nums[k] < target) {
				j++;
			}
			else {
				k--;
			}

		}
	}
	return res;
}

void solution15() {
	int* returnSize=malloc(sizeof(int));
	int nums[29] = {-7,-5,5,-6,-2,1,7,3,-4,-2,-2,-4,-8,-1,8,8,-2,-7,3,2,-7,8,-3,-10,5,2,8,7,7};
	int** re=threeSum(nums,29,returnSize);
	for (size_t i = 0; i < *returnSize; i++)
	{
		ALog("[%d,%d,%d]",re[i][0],re[i][1],re[i][2] );
		free(re[i]);
	}
	free(re);
	free(returnSize);
}