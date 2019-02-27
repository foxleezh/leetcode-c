
/**
 * ���� n �����������ŵĶ���������д��һ��������ʹ���ܹ��������п��ܵĲ�����Ч��������ϡ�
 *
 * ���磬���� n = 3�����ɽ��Ϊ��
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

static void backtrack(ArrayList* ans, char* cur, size_t char_len, int open, int close, int max) {
	//��ƴ�ӵ��ַ���Ϊ���ֵ������ʱ��˵��ƴ�����
	if (char_len == max * 2) {
		char* temp = malloc(sizeof(char)*(char_len + 1));
		memcpy(temp, cur, char_len);
		temp[char_len] = 0;
		list_add(ans, temp);
		return;
	}
	//ֻҪƴ�ӡ�����������С�����ֵ���ͼ���ƴ�ӡ�����
	if (open < max) {
		cur[char_len] = '(';
		backtrack(ans, cur, char_len+1, open + 1, close, max);
	}
	//ֻҪ������������С�ڡ��������������ͼ���ƴ�ӡ�����
	if (close < open) {
		cur[char_len] = ')';
		backtrack(ans, cur, char_len+1, open, close + 1, max);
	}
}


 /**
  * ����˼·���������⣬������Ҫ�ҳ�����()��ʽ����ϣ���һ�뷨�Ǳ��������������Ȼ����һ������֤��Ҳ������2^2n�ֿ���
  *
  * ������������Ч��̫�ͣ����ǿ���������Щ���Ƿ��������ģ������һ���϶�����'('���ڶ��������ǣ�,Ҳ������'('
  *
  * ����ڶ����ǣ�,��ô������ֻ����'(',��Ϊ"())"���Դ���
  *
  * �������ǿ����ܽ������'('��')'���ִ�����ͬʱ����һ��ֻ����(,��'('����')'ʱ����һ��������'(',Ҳ������')'
  *
  * ���������д�ݹ��ʱ�򣬾Ͱ������������ӽ�ȥ�Ϳ���
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
* ����һ�ֽ��˼·���û��ݷ�����remain1��remain2��¼�������͡�����ʣ��ĸ�������index��¼���ݵ�
* 
* ��һ�ν������"(())","((()))"���֣����ݵ������ǣ��Ӻ���ǰ,�ҵ���һ�����ǡ�)������remain2��������remain1 �Ľ��з�ת
*
* ��ʵ�Ȿ���Ͻ����ݹ�˼·��һ���ģ��ݹ��ִ��Ҳ�ǰ������������̣�ֻ�ǵݹ齫��Щָ���¼����ջ��
*
* ���ǻ��ݷ��ĺô����ڲ��ᵼ��ջ�����������Ϊ����ѹջ�ͳ�ջ���߼���ִ��Ч��Ҳ������
* 
* �仵������д�����ӣ��������
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
		//�ҵ����һ�����ǡ������Ĳ���remain2����remain1
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
		//��'('��תΪ������
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