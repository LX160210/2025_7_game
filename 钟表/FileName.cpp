#include <graphics.h> 
#include <conio.h> 
#include <math.h> 

#define High 480  // ��Ϸ����ߴ� 
#define Width 640 
#define PI 3.14159 

void main()
{
	initgraph(Width, High);  // ��ʼ�� 640 x 480 �Ļ�ͼ���� 
	int center_x, center_y;      // ���ĵ�����꣬Ҳ�Ǳ������ 
	center_x = Width / 2;
	center_y = High / 2;
	int secondLength = Width / 5;    // ����ĳ��� 
	int secondEnd_x, secondEnd_y;    // ������յ� 
	int minuteLength = Width / 6;    //����ĳ���
	int minuteEnd_x, minuteEnd_y;    //������յ�
	int hourLength = Width / 7;      //ʱ��ĳ���
	int hourEnd_x, hourEnd_y;        //ʱ����յ�


	float secondAngle = 0;       // ���Ӷ�Ӧ�ĽǶ� 
	float minuteAngle = 0;       //�����Ӧ�ĽǶ�
	float hourAngle = 0;         //ʱ���Ӧ�ĽǶ�


	SYSTEMTIME ti;    // ����������浱ǰʱ�� 

	while (1)
	{
		BeginBatchDraw();// ����˫����

		cleardevice();// �����һ֡�������Ӱ��

		GetLocalTime(&ti);  // ��ȡ��ǰʱ�� 
		// ���ӽǶȱ仯 
		secondAngle = ti.wSecond * 2 * PI / 60;  // һȦһ��2*PI��һȦ60�룬һ���������߹��ĽǶ�Ϊ2* PI / 60
		//����Ƕȱ仯
		minuteAngle = ti.wMinute * 2 * PI / 60 + secondAngle / 60;
		//ʱ��Ƕȱ仯
		hourAngle = ti.wHour * 2 * PI / 12 + minuteAngle / 12;

		secondEnd_x = center_x + secondLength * sin(secondAngle);
		secondEnd_y = center_y - secondLength * cos(secondAngle);
		minuteEnd_x = center_x + minuteLength * sin(minuteAngle);
		minuteEnd_y = center_y - minuteLength * cos(minuteAngle);
		hourEnd_x = center_x + hourLength * sin(hourAngle);
		hourEnd_y = center_y - hourLength * cos(hourAngle);
		//��ʱ�� 
		setlinestyle(PS_SOLID, 8);//��ʵ�ߣ����8������
		setcolor(RED);
		line(center_x, center_y, hourEnd_x, hourEnd_y);
		//������
		setlinestyle(PS_SOLID, 5);//��ʵ�ߣ����5������
		setcolor(BLUE);
		line(center_x, center_y, minuteEnd_x, minuteEnd_y);
		//������
		setlinestyle(PS_SOLID, 2);//��ʵ�ߣ����2������ 
		setcolor(WHITE);
		line(center_x, center_y, secondEnd_x, secondEnd_y);

		setlinestyle(PS_SOLID, 1);
		setcolor(WHITE);
		circle(center_x, center_y, Width / 4);
		// ���̶� 
		int x, y, i;
		for (i = 0; i < 60; i++)
		{
			x = center_x + int(Width / 4.3 * sin(PI * 2 * i / 60));
			y = center_y + int(Width / 4.3 * cos(PI * 2 * i / 60));
			if (i % 15 == 0)
				bar(x - 5, y - 5, x + 5, y + 5);
			else if (i % 5 == 0)
				//�ڱ���0��15��30��45�����ƾ��� 
				circle(x, y, 3);  //�ڱ��� 5,10,15,20,��������ԲȦ 
			else
				putpixel(x, y, WHITE); //�ڱ�������λ�ô����Ƶ� 
		}
		
		FlushBatchDraw();// �ύ����
		Sleep(1000);//��ʱ1��

	}

	_getch();    // ����������� 
	closegraph();   // �ر�ͼ�ν��� 

	system("pause");
}