#include "include/env.h"
/**
 * ����һ������ n ������������ nums���ж� nums ���Ƿ��������Ԫ�� a��b��c ��ʹ�� a + b + c = 0 ���ҳ��������������Ҳ��ظ�����Ԫ�顣
 * <p>
 * ע�⣺���в����԰����ظ�����Ԫ�顣
 * <p>
 * ����, �������� nums = [-1, 0, 1, 2, -1, -4]��
 * <p>
 * ����Ҫ�����Ԫ�鼯��Ϊ��
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
	//����ռ䣬ʹ���СΪ����
	int left_low = low;
	int left_high = mid;
	int right_low = mid + 1;
	int right_high = high;

	for (k = 0; left_low <= left_high && right_low <= right_high; k++) {  // �Ƚ�����ָ����ָ���Ԫ��
		if (arr[left_low] <= arr[right_low]) {
			tmp[k] = arr[left_low++];
		}
		else {
			tmp[k] = arr[right_low++];
		}
	}

	if (left_low <= left_high) {  //����һ��������ʣ�ֱ࣬�Ӹ��Ƴ���ճ���ϲ�����β
	//memcpy(tmp+k, arr+left_low, (left_high-left_low+l)*sizeof(int));
		for (i = left_low; i <= left_high; i++)
			tmp[k++] = arr[i];
	}

	if (right_low <= right_high) {
		//���ڶ���������ʣ�ֱ࣬�Ӹ��Ƴ���ճ���ϲ�����β
		//memcpy(tmp+k, arr+right_low, (right_high-right_low+1)*sizeof(int));
		for (i = right_low; i <= right_high; i++)
			tmp[k++] = arr[i];
	}

	for (i = 0; i < high - low + 1; i++)
		arr[low + i] = tmp[i];
	free(tmp);
	return;
}


//�鲢����
void merge_sort(int arr[], unsigned int first, unsigned int last) {
	int mid = 0;
	if (first < last) {
		mid = (first + last) / 2; /* ע���ֹ��� */
		merge_sort(arr, first, mid);
		merge_sort(arr, mid + 1, last);
		merge(arr, first, mid, last);
	}
	return;
}

/**
 * ����˼·��������Լ�Ϊ������֮�ͣ�����ȡһ����Ȼ���Ϊ�����෴�������������������֮�͵�������෴������ô��������֮�;�Ϊ0
 * <p>
 * �����������漰����������ͬ��Ԫ�أ�����[0,1,-1]��[0,-1,1]�ǲ��ܳ��ֵģ�����[2,2,-4]�ǿ��Եģ���������Ҫ���
 * <p>
 * Ϊ�˱�����ͬ����ϳ��֣���õİ취����������������ڱ���������������ͬ���������ܱ��������ͬ���
 *
 * �����Ź������ǿ��Բ�����ͷ���м��ߵ���ʽ�����ٶ��α���
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
		//��������0�Ŀ�ʼ����Ϊ����������Ӳ����ܵ���0
		if (nums[i] > 0) {
			break;
		}
		//������ͬ�����������ظ�
		if (i > 0 && nums[i] == nums[i - 1]) {
			continue;
		}
		//��ͷ���м��ߣ�j����k����
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
				//������ͬ����
				while (j < k && nums[j] == nums[j + 1]) {
					j++;
				}
				//������ͬ����
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