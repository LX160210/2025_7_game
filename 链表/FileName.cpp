#include <iostream>
#include <iomanip>
using namespace std;
struct Boy//С�����
{
	int code;
	Boy* pNext;
};
//����ָ��
Boy* pFirt = 0; //��һ��С��ָ��
Boy* pCurrent = 0; //��ǰС��ָ��
Boy* pivot = 0;//ǰһ��С��ָ��
int numOfBoys, m;
void add() {
	//****************n ��С��Χ��ԲȦ****************
	//��Ϸ�ĳ�ֵ
	cout << "please input the number of boys��\n"//С����
		<< " m of counting:\n"; //��С������
	cin >> numOfBoys >> m;
	//��ԲȦ�����ӵ� 1 ��С��
	pFirt = new Boy;
	pFirt->code = 1;
	pFirt->pNext = NULL;//����û��С��,
	pCurrent = pFirt;
	//������������С��
	for (int i = 1; i < numOfBoys; i++) {
		pivot = pCurrent;//��ǰС�����ǰС��
		pCurrent = new Boy;
		pCurrent->code = i + 1; //С�����
		pivot->pNext = pCurrent; //�ӵ�ǰһ��С������
	}
	pCurrent->pNext = pFirt;//���һ��С��ָ���һ��С��
	//���ԲȦ������С��
	cout << setw(4) << pFirt->code; //�����ǰС��
	pCurrent = pFirt->pNext;
	while (pCurrent != pFirt) {
		cout << setw(4) << pCurrent->code; //�����ǰС��
		pCurrent = pCurrent->pNext;
	}
	cout << endl;
}
void count() {
	//****************С�������뿪****************
	//****��ǰλ������Ϊ��һ��С��****
	pCurrent = pFirt;
	int j;
	while (pCurrent->pNext != pCurrent) { //ֻ��һ��С��ʱ���˳�ѭ��
		//****������ m ��С���뿪****
		//��Ҫ����С���� j=m
		j = m;
		do {
			//��ǰλ�õ�������һ��С��
			pivot = pCurrent; //��ǰС�����ǰһ��С��
			pCurrent = pCurrent->pNext;//��С����ɵ�ǰС��
			j--;
		} while (j > 1);//��ǰС���� 1���������� m-1 ��
		//�� m ��С���뿪
		cout << setw(4) << pCurrent->code;
		pivot->pNext = pCurrent->pNext; //��ǰС������һ��С��������ǰһ���ĺ���
		delete pCurrent; //����ԲȦ��ɾ��
		pCurrent = pivot->pNext; //�뿪С������һ��С����Ϊ��ǰС��
	}
}
void print() {
	//****************������ʤ��****************
	cout << "\n\nthe winner is "
		<< pCurrent->code << endl; //��ʤ��
	delete pCurrent;
}
void main() {
	add();
	count();
	print();
	system("pause");
}