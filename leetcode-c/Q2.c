#include "include/env.h"

/**
 * �������� �ǿ� ������������ʾ�����Ǹ������������У����Ǹ��Ե�λ���ǰ��� ���� �ķ�ʽ�洢�ģ��������ǵ�ÿ���ڵ�ֻ�ܴ洢 һλ ���֡�
 * <p/>
 * ��������ǽ��������������������᷵��һ���µ���������ʾ���ǵĺ͡�
 * <p/>
 * �����Լ���������� 0 ֮�⣬���������������� 0 ��ͷ��
 * <p/>
 * ʾ����
 * <p/>
 * ���룺(2 -> 4 -> 3) + (5 -> 6 -> 4)
 * <p/>
 * �����7 -> 0 -> 8
 * <p/>
 * ԭ��342 + 465 = 807
 * <p/>
 */


/*
 * ����˼·�������ʵ�ʾ��Ǽӷ����ӷ��Ļ������漰����λ�����⣬�������Ǿ���һ�������������½�λ
 * 
 * �ڱ��������н�ÿһλ�����ֶ�Ӧ��ӣ������λ�Ӹ�λ��ʮλ��ʮλ��Ȼ���ټӽ�λ
 * 
 * ���жԲ���λ��ʱ�򣬱���һ����λ��+��λ�����֣���λ����ǧλ�򲻼�
 */
struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2) {
	int carry = 0;
	struct ListNode result;
	struct ListNode* cur = &result;
	while (l1 != NULL || l2 != NULL || carry != NULL) {
		if (l1 != NULL) {
			carry = carry + l1->val;
			l1 = l1->next;
		}
		if (l2 != NULL) {
			carry = carry + l2->val;
			l2 = l2->next;
		}
		struct ListNode* node = (struct ListNode*)malloc(sizeof(struct ListNode));
		node->val = carry % 10;
		node->next = NULL;
		cur->next = node;
		cur = node;
		carry /= 10;
	}
	return result.next;
}

void solution2() {
	int nums1[] = {2,4,3};
	int nums2[] = { 5, 6, 4 };
	struct ListNode* node_1 = nodeCreate(nums1,3);
	struct ListNode* node_2 = nodeCreate(nums2,3);
	char* toString = nodeToString(addTwoNumbers(node_1, node_2));
	ALog("%s", toString);
	free(toString);
	nodeFree(node_1);
	nodeFree(node_2);
}