#include <iostream>
using namespace std;
void main() {
	//n ��С��Χ��ԲȦ
	const int numOfBoy = 7; //С������
	int boy[numOfBoy]; //С������
	int i;
	for (i = 0; i < numOfBoy; i++)//�� 1 ��ʼ��С�����
		boy[i] = i + 1;
	//������С�����
	int m; //Josephus �����еļ�� m
	cout << "please input the interval: ";
	cin >> m;
	//�����ʼʱ��С�����
	for (i = 0; i < numOfBoy; i++)
		cout << boy[i] << "��";
	cout << endl;
	//С�������뿪
	i = 0; //��ǰλ�� i ����Ϊ��һ��С��
	int n = numOfBoy; //�뿪С���ĸ���
	while (n > 1) {//ֻʣһ��С��
		//������ m ��С���뿪
		int j = m;
		do {
			//��ǰλ�� i ��������һ��С��
			i = (i + 1) % numOfBoy;
			while (boy[i] == 0)
				i = (i + 1) % numOfBoy;
			j--; //��һ��С��
		} while (j > 1); //������ m ��С��
		//�� m ��С���뿪
		cout << boy[i] << "��"; //����뿪��С��֮���
		boy[i] = 0; //��ʶ��С�����뿪
		///��ǰλ�� i ��������һ��С��
		i = (i + 1) % numOfBoy;
		while (boy[i] == 0)
			i = (i + 1) % numOfBoy;
		n--; //�뿪һ��С��
	}
	//������ʤ��
	for (int i = 0; i < numOfBoy; i++) {
		if (boy[i] != 0) {
			cout << "\nNo." << boy[i] << "��ʤ.\n"; //���ʤ����
			break;
		}
	}
	system("pause");
}