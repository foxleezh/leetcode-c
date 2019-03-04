#include "include/env.h"

/**
 * 给出两个 非空 的链表用来表示两个非负的整数。其中，它们各自的位数是按照 逆序 的方式存储的，并且它们的每个节点只能存储 一位 数字。
 * <p/>
 * 如果，我们将这两个数相加起来，则会返回一个新的链表来表示它们的和。
 * <p/>
 * 您可以假设除了数字 0 之外，这两个数都不会以 0 开头。
 * <p/>
 * 示例：
 * <p/>
 * 输入：(2 -> 4 -> 3) + (5 -> 6 -> 4)
 * <p/>
 * 输出：7 -> 0 -> 8
 * <p/>
 * 原因：342 + 465 = 807
 * <p/>
 */


/*
 * 解题思路：这题的实质就是加法，加法的话就是涉及到进位的问题，所以我们就用一个变量来保存下进位
 * 
 * 在遍历过程中将每一位的数字对应相加，比如个位加个位，十位加十位，然后再加进位
 * 
 * 当有对不上位的时候，比如一个三位数+四位数这种，三位数的千位则不加
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