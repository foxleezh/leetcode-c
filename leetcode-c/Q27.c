#include "include/env.h"
/**
 * 给定一个数组 nums 和一个值 val，你需要原地移除所有数值等于 val 的元素，返回移除后数组的新长度。
 * <p>
 * 不要使用额外的数组空间，你必须在原地修改输入数组并在使用 O(1) 额外空间的条件下完成。
 * <p>
 * 元素的顺序可以改变。你不需要考虑数组中超出新长度后面的元素。
 * <p>
 * 示例 1:
 * <p>
 * 给定 nums = [3,2,2,3], val = 3,
 * <p>
 * 函数应该返回新的长度 2, 并且 nums 中的前两个元素均为 2。
 * <p>
 * 你不需要考虑数组中超出新长度后面的元素。
 * 示例 2:
 * <p>
 * 给定 nums = [0,1,2,2,3,0,4,2], val = 2,
 * <p>
 * 函数应该返回新的长度 5, 并且 nums 中的前五个元素为 0, 1, 3, 0, 4。
 * <p>
 * 注意这五个元素可为任意顺序。
 * <p>
 * 你不需要考虑数组中超出新长度后面的元素。
 *
 * @author foxleezh
 * @date 2019-03-13.
 */

 /**
  * 解题思路：这个跟上一题解法差不多，只是把比较的数值变成定值val
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