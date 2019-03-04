#include "include/env.h"
/**
 * ����һ���������������������ڵĽڵ㣬�����ؽ����������
 * <p>
 * �㲻��ֻ�ǵ����ĸı�ڵ��ڲ���ֵ��������Ҫʵ�ʵĽ��нڵ㽻����
 * <p>
 * <p>
 * <p>
 * ʾ��:
 * <p>
 * ���� 1->2->3->4, ��Ӧ�÷��� 2->1->4->3.
 *
 * @author foxleezh
 * @date 2019-03-04.
 */


 /**
  * ����˼·�����������������ǿ��Էֽ�һ�£�1->2->3->4,������Ľ����2->1->4->3
  *
  * ��ôҪ�ı�Ĺ�ϵ�ǣ�������headΪpre��1Ϊcur��2Ϊpost,��������һ�鿪ʼ�任
  *
  * 1.pre(head)��nextԭ��Ϊ1��Ӧ�ñ���2
  *
  * 2.cur(1)��nextԭ��Ϊ2��Ӧ�ñ�Ϊ3
  *
  * 3.post(2)��nextԭ��Ϊ3��Ӧ�ñ�Ϊ1
  *
  * ֻҪ����������������ѭ������
  *
  */
struct ListNode* swapPairs(struct ListNode* head) {
	struct ListNode dummy;
	struct ListNode* pre = &dummy;
	pre->next = head;
	struct ListNode* cur;
	struct ListNode* post;
	while (pre->next != NULL && pre->next->next != NULL) {
		cur = pre->next; //ȡcur
		post = pre->next->next;//ȡpost
		pre->next = post; //��head��next��Ϊ2
		cur->next = post->next; //��1��next��Ϊ3
		post->next = cur;//��2��next��Ϊ1
		pre = pre->next->next; //��������
	}
	return dummy.next;
}


void solution24() {
	int nums1[] = {1,2,3,4};
	char* toString = nodeToString(swapPairs(nodeCreate(nums1, 4)));
	ALog("%s", toString);
	free(toString);
}