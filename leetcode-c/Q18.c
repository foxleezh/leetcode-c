#include "include/env.h"

/**
 * 给定一个包含 n 个整数的数组 nums 和一个目标值 target，判断 nums 中是否存在四个元素 a，b，c 和 d ，使得 a + b + c + d 的值与 target 相等？找出所有满足条件且不重复的四元组。
 * <p>
 * 注意：
 * <p>
 * 答案中不可以包含重复的四元组。
 * <p>
 * 示例：
 * <p>
 * 给定数组 nums = [1, 0, -1, 0, -2, 2]，和 target = 0。
 * <p>
 * 满足要求的四元组集合为：
 * [
 * [-1,  0, 0, 1],
 * [-2, -1, 1, 2],
 * [-2,  0, 0, 2]
 * ]
 *
 * @author foxleezh
 * @date 2019-02-11.
 */


typedef struct ArrayList_Class
{
	int **arrBase;
	int maxlen; //最大长度
	int length;    //当前有效长度
}ArrayList;


static void list_isfull(ArrayList *arr)
{
	if (arr->length >= arr->maxlen)
	{
		arr->arrBase = realloc(arr->arrBase, sizeof(int*)* (arr->maxlen * 2));
		arr->maxlen = arr->maxlen * 2;
	}
}

static ArrayList* list_create(int maxlen)
{
	ArrayList* arr = malloc(sizeof(ArrayList));
	arr->arrBase = (int **)malloc(sizeof(int*)*maxlen);
	arr->length = 0;
	arr->maxlen = maxlen;
	return arr;
}


static void list_add(ArrayList *arr, void* value)
{
	list_isfull(arr);
	arr->arrBase[arr->length] = value;
	arr->length++;
}



static void list_insert(ArrayList *arr, int pos, void* value)
{
	int i;
	if (pos<0 || pos > arr->length)
	{
		printf("插入位置不正确或者数据已满，无法插入");
		return;
	}
	list_isfull(arr);
	for (i = arr->length; i >= pos + 1; i--)
	{
		arr->arrBase[i] = arr->arrBase[i - 1];
	}
	arr->arrBase[pos] = value;
	arr->length++;
}

static void list_free(ArrayList *arr) {
	for (size_t i = 0; i < arr->length; i++)
	{
		free(arr->arrBase[i]);
	}
	free(arr->arrBase);
	free(arr);
}

static int len = 0;

ArrayList* kSum(int* nums, int numSize, int target, int k, int index) {
	ArrayList* res = list_create(numSize);
	if (index >= len) {
		return res;
	}
	if (k == 2) {
		int i = index, j = len - 1;
		while (i < j) {
			//寻找两数之和
			if (target - nums[i] == nums[j]) {
				int* temp = malloc(sizeof(int)*numSize);
				temp[numSize - 2] = nums[i];
				temp[numSize - 1] = target - nums[i];
				list_add(res, temp);
				//重复值跳过
				while (i < j && nums[i] == nums[i + 1]) {
					i++;
				}
				while (i < j && nums[j - 1] == nums[j]) {
					j--;
				}
				i++;
				j--;
			}
			else if (target - nums[i] > nums[j]) {
				i++;
			}
			else {
				j--;
			}
		}
	}
	else {
		//递归+遍历,不断进行两数之和的尝试
		for (int i = index; i < len - k + 1; i++) {
			ArrayList* temp = kSum(nums, numSize, target - nums[i], k - 1, i + 1);
			if (temp->length != 0) {
				for (size_t j = 0; j < temp->length; j++)
				{
					int* t = (int*)(temp->arrBase[j]);
					t[numSize - k] = nums[i];
				}
				for (size_t j = 0; j < temp->length; j++)
				{
					list_add(res, temp->arrBase[j]);
				}
				temp->length = 0;
			}
			list_free(temp);
			while (i < len - 1 && nums[i] == nums[i + 1]) {
				i++;
			}
		}
	}
	return res;
}

int funcmp(void* a, void* b) {
	return *((int*)a) - *((int*)b);
}

/**
 * 解题思路：之前有做过两数之和，三数之和，现在是四数之和，其实我们可以抽象出N数之和的解法
 *
 * 1.首先对数组排序，这个是必须的，保证元组不重复
 *
 * 2.我们在解三数之和的时候，将其简化为两数之和，双指针左右往中间走，那么N数之和也可以这样
 *
 * 3.在N-2次循环之前，用递归不断进行遍历，直到循环到2时用两数之和来解
 *
 */
int** fourSum1(int* nums, int numsSize, int target, int* returnSize) {
	len = numsSize;
	qsort(nums, numsSize, sizeof(int), funcmp);
	ArrayList* res = kSum(nums, 4, target, 4, 0);
	*returnSize = res->length;
	int** int_res = res->arrBase;
	free(res);
	return int_res;
}


/*
 * 与上面解法一样，只是定死4数之和，比递归效率高
 * 先排序，直接两层遍历，然后双指针左右往中间走
 */
int** fourSum(int* nums, int numsSize, int target, int* returnSize) {
	if (nums == NULL || returnSize == NULL || numsSize < 4) return NULL;

	int **ret = NULL;

	qsort(nums, numsSize, sizeof(int), funcmp);
	int sum, i, j, l, r;
	*returnSize = 0;

	for (i = 0; i < numsSize - 3; i++) {
		if (i > 0 && nums[i] == nums[i - 1]) {
			continue;
		}
		for (j = i + 1; j < numsSize - 2; j++) {
			if (j > i + 1 && nums[j] == nums[j - 1]) {
				continue;
			}
			l = j + 1, r = numsSize - 1;
			if (nums[i] + nums[j] + nums[r - 1] + nums[r] < target) {
				continue;
			}
			if (nums[i] + nums[j] + nums[l] + nums[l + 1] > target) {
				break;
			}
			while (l < r) {
				sum = nums[i] + nums[j] + nums[l] + nums[r];
				if (sum == target) {
					if (*returnSize &&
						(ret[*returnSize - 1][0] == nums[i]
							&& ret[*returnSize - 1][1] == nums[j]
							&& ret[*returnSize - 1][2] == nums[l]))
					{
						l++;
						r--;
						continue;
					}

					if ((*returnSize) % 100 == 0)
						ret = realloc(ret, sizeof(int *) * (*returnSize + 100));
					ret[*returnSize] = malloc(sizeof(int) * 4);
					ret[*returnSize][0] = nums[i];
					ret[*returnSize][1] = nums[j];
					ret[*returnSize][2] = nums[l];
					ret[*returnSize][3] = nums[r];
					*returnSize = *returnSize + 1;
					l++;
					r--;
				}
				else if (sum > target)
					r--;
				else
					l++;
			}

		}
	}
	return ret;
}

void solution18() {
	int nums[] = { -4,-3,-2,-1,0,0,1,2,3,4 };
	int* returnSize = malloc(sizeof(int));
	int** res = fourSum(nums, 10, 0, returnSize);
	for (size_t i = 0; i < *returnSize; i++)
	{
		int* list = res[i];
		ALog("[%d,%d,%d,%d]", list[0], list[1], list[2], list[3]);
		free(list);
	}
	free(res);
	free(returnSize);
}