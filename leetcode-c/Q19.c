#include "include/env.h"
/**
 * ����һ������ɾ������ĵ����� n ���ڵ㣬���ҷ��������ͷ��㡣
 * <p>
 * ʾ����
 * <p>
 * ����һ������: 1->2->3->4->5, �� n = 2.
 * <p>
 * ��ɾ���˵����ڶ����ڵ�������Ϊ 1->2->3->5.
 * ˵����
 * <p>
 * ������ n ��֤����Ч�ġ�
 *
 * @author foxleezh
 * @date 2019-02-13.
 */


/**
 *  ����˼·���������ǿ�����˫ָ�뷨������firstָ����n����Ȼ��secondָ�뿪ʼ�ߣ���first�ߵ�β��ʱ��secondָ��ľ��ǵ�����n��
 *
 *  Ȼ���ٽ�ָ������nodeɾ������
 */
struct ListNode* removeNthFromEnd(struct ListNode* head, int n) {
	struct ListNode* result = malloc(sizeof(struct ListNode));
	result->next = head;
	struct ListNode* first = result;
	struct ListNode* second = result;
	int i = 1;
	while (first->next != NULL) {
		first = first->next;
		//��first����n����second��ʼ��
		if (i > n) {
			second = second->next;
		}
		i++;
	}
	//ɾ��������n��node
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