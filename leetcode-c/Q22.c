
/**
 * 给出 n 代表生成括号的对数，请你写出一个函数，使其能够生成所有可能的并且有效的括号组合。
 *
 * 例如，给出 n = 3，生成结果为：
 *
 * [
 *   "((()))",
 *   "(()())",
 *   "(())()",
 *   "()(())",
 *   "()()()"
 * ]
 *
 * @author foxleezh
 * @date 2019-02-27.
 */

#include "include/env.h"

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

static void backtrack(ArrayList* ans, char* cur, size_t char_len, int open, int close, int max) {
	//当拼接的字符串为最大值的两倍时，说明拼接完成
	if (char_len == max * 2) {
		char* temp = malloc(sizeof(char)*(char_len + 1));
		memcpy(temp, cur, char_len);
		temp[char_len] = 0;
		list_add(ans, temp);
		return;
	}
	//只要拼接‘（’的数量小于最大值，就继续拼接‘（’
	if (open < max) {
		cur[char_len] = '(';
		backtrack(ans, cur, char_len+1, open + 1, close, max);
	}
	//只要‘）’的数量小于‘（’的数量，就继续拼接‘）’
	if (close < open) {
		cur[char_len] = ')';
		backtrack(ans, cur, char_len+1, open, close + 1, max);
	}
}


 /**
  * 解题思路：根据题意，我们需要找出满足()形式的组合，第一想法是遍历出所有情况，然后再一个个验证，也就是有2^2n种可能
  *
  * 但是明显这样效率太低，我们可以想想哪些才是符合条件的，比如第一个肯定得是'('，第二个可以是）,也可以是'('
  *
  * 如果第二个是）,那么第三个只能是'(',因为"())"明显错误
  *
  * 所以我们可以总结出，当'('和')'出现次数相同时，下一个只能是(,当'('多于')'时，下一个可以是'(',也可以是')'
  *
  * 因此我们在写递归的时候，就把这两个条件加进去就可以
  */
char** generateParenthesis1(int n, int* returnSize) {
	ArrayList* ans = list_create(n*n);
	char* temp = malloc(sizeof(char)*(n*2+1));
	backtrack(ans, temp, 0, 0, 0, n);
	*returnSize = ans->length;
	char** t = ans->arrBase;
	free(ans);
	free(temp);
	return t;
}


/**
* 另外一种解决思路是用回溯法，用remain1和remain2记录‘（’和‘）’剩余的个数，用index记录回溯点
* 
* 第一次结果都是"(())","((()))"这种，回溯的条件是，从后往前,找到第一个不是‘)’并且remain2数量大于remain1 的进行反转
*
* 其实这本质上讲跟递归思路是一样的，递归的执行也是按照这样的流程，只是递归将这些指针记录到了栈里
*
* 但是回溯法的好处在于不会导致栈溢出，而且因为少了压栈和出栈的逻辑，执行效率也会提升
* 
* 其坏处就是写法复杂，不易理解
*/
char** generateParenthesis(int n, int* returnSize) {
	size_t size = n * n;
	char** result = malloc(sizeof(char*)*size);;
	char* temp = (char*)malloc((n * 2 + 1) * sizeof(char));
	temp[2 * n] = '\0';
	int index = 0, remain1 = n, remain2 = n;
	while (true) {
		while (remain1 > 0) {
			temp[index++] = '(';
			remain1--;
		}
		while (remain2 > 0) {
			temp[index++] = ')';
			remain2--;
		}
		(*returnSize)++;
		if (*returnSize > size) {
			size = size * 2;
			result = realloc(result,sizeof(char*)*size);
		}
		result[*returnSize - 1] = (char*)malloc((n * 2 + 1) * sizeof(char));
		memcpy(result[*returnSize - 1], temp, (n * 2 + 1) * sizeof(char));
		//找到最后一个不是‘）’的并且remain2大于remain1
		while (temp[index - 1] == ')' || remain1 > remain2 - 2) {
			if (temp[index - 1] == ')')
				remain2++;
			else
				remain1++;
			index--;
			if (index < 0) {
				free(temp);
				return result;
			}
		}
		//将'('反转为‘）’
		temp[index - 1] = ')';
		remain1++;
		remain2--;
	}
	free(temp);
	return result;
}


void solution22() {
	int* returnSize = malloc(sizeof(int));
	*returnSize = 0;
	char** ans=generateParenthesis(3, returnSize);
	for (size_t i = 0; i < *returnSize; i++)
	{
		ALog("%s", ans[i]);
		free(ans[i]);
	}
	free(ans);
	free(returnSize);
}