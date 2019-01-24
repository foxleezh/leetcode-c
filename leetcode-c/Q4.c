#include "include/env.h"


/**
	 * ����˼·����������������Ϊ������������ϲ����������ҵ�(m+n)/2��������λ�� <p/>
	 * ���и�Ҫ����ʱ�临�Ӷ���log(m+n),����֪�����������㷨ʱ�临�����Ҳֻ����nlogn������������������ǲ��е� <p/>
	 * ��Ȼ��Ŀ��Ҫ������λ�������ǿ��Դ���λ���ĸ������֣���λ����ָ����������һ��������С��һ���������� <p/>
	 * �������������鶼���������飬���Ǽ���ΪA�����B���飬������Ǵ��±�Ϊi�ĵط���A�����Ϊ���룬��ߵ����϶���A[i]С���ұ߱�A[i]�� <p/>
	 * ͬ���B������±�Ϊj�ĵط���Ϊ���� <br/>
	 * left_part          |        right_part<br/>
	 * A[0], A[1], ..., A[i-1]  |  A[i], A[i+1], ..., A[m-1]<br/>
	 * B[0], B[1], ..., B[j-1]  |  B[j], B[j+1], ..., B[n-1]<br/>
	 * ��ֻҪ�����������������ǾͿ���˳���ҵ���λ�� <br/>
	 * 1.len(left_part)==len(right_part) �൱�� i+j=m-i+n-j<br/>
	 * 2.min(right_part)>=max(left_part) �൱�� B[j]>=A[i-1] && A[i]>=B[j-1] <br/>
	 * ���ڵ�һ������:<br/>
	 * ���ǿ����Ƴ�j=(m+n)/2 - i,Ҳ����i��ֵȷ���ˣ�j��ֵ��ȷ���ˣ�Ҳ����˵����ֻҪ��i��ֵȷ����������ڶ����������� <br/>
	 * ���ڵڶ��������� <br/>
	 * ������Ҫ���� B[j]>=A[i-1] && A[i]>=B[j-1]������������������֣� <br/>
	 * һ��B[j] < A[i-1],˵��i��ֵ̫���ˣ�������A[i]��ֵ�϶�����A[i-1]�����i�����Ӵ�������Զ�޷����㣬����ֻ�ܼ�Сi <br/>
	 * ����A[i] < B[j-1],˵��i��ֵ̫С�ˣ���Ҫ�Ӵ�i��ֵ <br/>
	 * ��������Щ������ֻ��Ҫ��������ȥ���ӻ���Сi��ֵ�Ϳ����ˣ��������������飬���ǿ����ö��ַ��仯i��ֵ <p/>
	 * ��������ٿ�����������B[j]>=A[i-1] && A[i]>=B[j-1]ʱ��ô�õ���λ�� <br/>
	 * max(left_part)=max(A[i-1],B[j-1]); <br/>
	 * min(right_part)=min(A[i],B[j]); <br/>
	 * �������֮����ż������λ��=(max(left_part)+min(right_part))/2 <br/>
	 * �������֮������������λ��=max(left_part)����min(right_part)����ȡ�ĸ��أ��ı߶�һ����ȡ�ı� <br/>
	 * ���ǿ��Խ�j=(m+n)/2 - i��Ϊj=(m+n+1)/2 - i����֤j��ֵ��Щ���Ӷ���֤len(left_part)>left(right_part) <br/>
	 * Ҳ���Խ�j=(m+n)/2 - i��Ϊj=(m+n-1)/2 - i����֤j��ֵСЩ, �Ӷ���֤len(right_part)>left(left_part) <br/>
	 * ������һЩ��������ˣ� <br/>
	 * ��������j����i�����ģ�j=(m+n)/2 - i, i��ȡֵ��Χ��0��m,Ҳ����˵j���ܵ�ֵ��(n-m)/2 ��(m+n)/2������j����Ϊ������ô����n>=m <br/>
	 * ���i==0����i==mʱ��A������һ����û��ֵ�ģ������⴦�� <br/>
	 * ͬ��j==0����j==mʱ��B������һ��Ҳ��û��ֵ�ģ������⴦�� <br/>
	 *
	 * @return
	 */
double findMedianSortedArrays(int* A, int nums1Size, int* B, int nums2Size) {
	int m = nums1Size;
	int n = nums2Size;
	// ��֤ m<=n
	if (m > n) {
		int* temp = A;
		A = B;
		B = temp;
		int tmp = m;
		m = n;
		n = tmp;
	}
	int iMin = 0, iMax = m;
	//��֤len(left_part)>len(right_part)
	int halfLen = (m + n + 1) / 2;
	while (iMin <= iMax) {
		int i = (iMin + iMax) / 2;
		int j = halfLen - i;
		// i ��ֵ̫������ע��i��ֵ���ϼ�С�п���i��Ϊ0,j��Ϊn,���뱣֤����0,jҲ����С��n
		if (i > iMin && B[j] < A[i - 1]) {
			iMax = i - 1;
		}// i ��ֵ̫С
		else if (i < iMax && A[i] < B[j - 1]) {
			iMin = i + 1;
		}// i��ֵ�պ�
		else {
			int maxLeft = 0;
			//�������i==0������A��left_partΪ�գ�ֻ��ȡB��left_part�����ֵ
			if (i == 0) {
				maxLeft = B[j - 1];
			}
			else if (j == 0) {
				maxLeft = A[i - 1];
			}
			else {
				maxLeft = A[i - 1]>B[j - 1]? A[i - 1]: B[j - 1];
			}
			if ((m + n) % 2 == 1) {
				return maxLeft;
			}

			int minRight = 0;
			if (i == m) {
				minRight = B[j];
			}
			else if (j == n) {
				minRight = A[i];
			}
			else {
				minRight = B[j]<A[i]? B[j]: A[i];
			}

			return (maxLeft + minRight) / 2.0;
		}
	}
	return 0.0;
}


void solution4() {
	int nums1[2] = {1,3};
	int nums2[1] = {2};
	ALog("%f",findMedianSortedArrays(nums1,2,nums2,1));
}