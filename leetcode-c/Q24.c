#include "include/env.h"
/**
 * 给定一个链表，两两交换其中相邻的节点，并返回交换后的链表。
 * <p>
 * 你不能只是单纯的改变节点内部的值，而是需要实际的进行节点交换。
 * <p>
 * <p>
 * <p>
 * 示例:
 * <p>
 * 给定 1->2->3->4, 你应该返回 2->1->4->3.
 *
 * @author foxleezh
 * @date 2019-03-04.
 */


 /**
  * 解题思路：两两交换问题我们可以分解一下，1->2->3->4,交换后的结果是2->1->4->3
  *
  * 那么要改变的关系是，我们设head为pre，1为cur，2为post,我们两两一组开始变换
  *
  * 1.pre(head)的next原来为1，应该变了2
  *
  * 2.cur(1)的next原来为2，应该变为3
  *
  * 3.post(2)的next原来为3，应该变为1
  *
  * 只要按照这三步，两两循环即可
  *
  */
struct ListNode* swapPairs(struct ListNode* head) {
	struct ListNode dummy;
	struct ListNode* pre = &dummy;
	pre->next = head;
	struct ListNode* cur;
	struct ListNode* post;
	while (pre->next != NULL && pre->next->next != NULL) {
		cur = pre->next; //取cur
		post = pre->next->next;//取post
		pre->next = post; //将head的next变为2
		cur->next = post->next; //将1的next变为3
		post->next = cur;//将2的next变为1
		pre = pre->next->next; //两两步进
	}
	return dummy.next;
}


void solution24() {
	int nums1[] = {1,2,3,4};
	char* toString = nodeToString(swapPairs(nodeCreate(nums1, 4)));
	ALog("%s", toString);
	free(toString);
}