#include "include/env.h"
/**
 * 给定一个链表，删除链表的倒数第 n 个节点，并且返回链表的头结点。
 * <p>
 * 示例：
 * <p>
 * 给定一个链表: 1->2->3->4->5, 和 n = 2.
 * <p>
 * 当删除了倒数第二个节点后，链表变为 1->2->3->5.
 * 说明：
 * <p>
 * 给定的 n 保证是有效的。
 *
 * @author foxleezh
 * @date 2019-02-13.
 */


/**
 *  解题思路：这题我们可以用双指针法，先让first指针走n步，然后second指针开始走，当first走到尾部时，second指向的就是倒数第n个
 *
 *  然后再将指向的这个node删除即可
 */
struct ListNode* removeNthFromEnd(struct ListNode* head, int n) {
	struct ListNode* result = malloc(sizeof(struct ListNode));
	result->next = head;
	struct ListNode* first = result;
	struct ListNode* second = result;
	int i = 1;
	while (first->next != NULL) {
		first = first->next;
		//当first走了n步后，second开始走
		if (i > n) {
			second = second->next;
		}
		i++;
	}
	//删除倒数第n个node
	struct ListNode* temp = second->next->next;
	free(second->next);
	second->next = temp;
	struct ListNode* t = result->next;
	free(result);
	return t;
}

#define N 5
#define INDEX 2

void solution19() {
	int nums[N] = { 1, 2, 3, 4, 5 };
	char* toString = nodeToString(removeNthFromEnd(nodeCreate(nums, N), INDEX));
	ALog("%s", toString);
	free(toString);
}