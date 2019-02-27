#include "include/env.h"

/**
 * ����һ������ n ������������ nums ��һ��Ŀ��ֵ target���ж� nums ���Ƿ�����ĸ�Ԫ�� a��b��c �� d ��ʹ�� a + b + c + d ��ֵ�� target ��ȣ��ҳ��������������Ҳ��ظ�����Ԫ�顣
 * <p>
 * ע�⣺
 * <p>
 * ���в����԰����ظ�����Ԫ�顣
 * <p>
 * ʾ����
 * <p>
 * �������� nums = [1, 0, -1, 0, -2, 2]���� target = 0��
 * <p>
 * ����Ҫ�����Ԫ�鼯��Ϊ��
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
	int maxlen; //��󳤶�
	int length;    //��ǰ��Ч����
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
		printf("����λ�ò���ȷ���������������޷�����");
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
			//Ѱ������֮��
			if (target - nums[i] == nums[j]) {
				int* temp = malloc(sizeof(int)*numSize);
				temp[numSize - 2] = nums[i];
				temp[numSize - 1] = target - nums[i];
				list_add(res, temp);
				//�ظ�ֵ����
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
		//�ݹ�+����,���Ͻ�������֮�͵ĳ���
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
 * ����˼·��֮ǰ����������֮�ͣ�����֮�ͣ�����������֮�ͣ���ʵ���ǿ��Գ����N��֮�͵Ľⷨ
 *
 * 1.���ȶ�������������Ǳ���ģ���֤Ԫ�鲻�ظ�
 *
 * 2.�����ڽ�����֮�͵�ʱ�򣬽����Ϊ����֮�ͣ�˫ָ���������м��ߣ���ôN��֮��Ҳ��������
 *
 * 3.��N-2��ѭ��֮ǰ���õݹ鲻�Ͻ��б�����ֱ��ѭ����2ʱ������֮������
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
 * ������ⷨһ����ֻ�Ƕ���4��֮�ͣ��ȵݹ�Ч�ʸ�
 * ������ֱ�����������Ȼ��˫ָ���������м���
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