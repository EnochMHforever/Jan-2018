/*********************************
***********************************
***     ���ݽṹ��ĩ�γ����     ***
************************************
***     ��ҵ���ƣ�����ʽ������   ***
***     ʹ�õ����ݽṹ��ջ       ***
***     UI��ʹ��easyxʵ��        ***
***********************************
***     ʵ�ֹ��ܣ�               ***
***     1.�Ӽ��˳�               ***
***     �Լӣ��˷�����           ***
***     2.ʵ������λ������       ***
***     3.ͼ�ν���ʵ��           ***
***********************************     
**********************************/


#include<iostream>
#include<stdlib.h>  
#include<stdio.h>  
#include<math.h>  
#include<string.h>  
#include<graphics.h>      // ������Ҫ�������ͼ�ο�
#include<conio.h>
#include<windows.h>


#define WINSIZEX 401	//���ڴ�С
#define WINSIZEY 471
#define WINKEYY (WINSIZEY - 1) / 8	//�м��
#define WINKEYX (WINSIZEX - 1) / 4

#define MAX 100
#define TRUE 1

#pragma warning(disable:4996) 
using namespace std;

typedef struct {
	char Str[MAX];/*�洢ԭ�������ʽ*/
	int Long;
}STR;
struct {
	int x[2];	//�������������x����������x��x[0]��ʾ����x��x[1]��ʾ����x
	int y[2];	//ͬ��
}Pos[25];

char KeyStr[][4] = { { "CE" } ,{ "<-" } ,{ "M" } ,{ "/" }
					 ,{ "(" } ,{ ")" } ,{ "^" },{ "^"}
					 ,{ "7" } ,{ "8" } ,{ "9" } ,{ "*" }
					 ,{ "4" } ,{ "5" } ,{ "6" } ,{ "+" }
					 ,{ "1" } ,{ "2" } ,{ "3" } ,{ "-" }
					 ,{ "00" } ,{ "0" } ,{ "." } ,{ "=" },{ "$" } };
//�������İ��� 

int LastStrPosT = 1;	//LastStrPos��ʾ��׺���ʽ�������
char GetStr[MAX * 5];
char TheLastStr[MAX];	//��׺���� 
float LastV = 0;  //������

void Trans(STR *InStr, char LastStr[]);//���������ʽ����׺���ʽ�����ɺ�׺���ʽ 
float Compvalue(char LastStrTemp[]);//�����׺���ʽ��ֵ 


/*
#��׺���ʽ����׺�Ƿ���
��׺���ʽ��һ��ͨ�õ��������߼���ʽ��ʾ����������������׺��ʽ���ڲ��������м䡣��׺���ʽ�����ǳ��õ�������ʾ������
��Ȼ�˵Ĵ��Ժ���������������׺���ʽ�����Լ������˵��׺���ʽȴ�Ǻܸ��ӵģ���˼�����ʽ��ֵʱ��ͨ����Ҫ�Ƚ���׺���ʽת��Ϊǰ׺���׺���ʽ��Ȼ���ٽ�����ֵ���Լ������˵������ǰ׺���׺���ʽ��ֵ�ǳ��򵥡�

#ǰ׺���ʽ��ǰ׺�Ƿ�������ʽ��
ǰ׺���ʽ�������λ�ڲ�����֮ǰ
ǰ׺���ʽ�ļ������ֵ��
��������ɨ����ʽ����������ʱ��������ѹ���ջ�����������ʱ������ջ�����������������������������Ӧ�ļ��㣨ջ��Ԫ�� op �ζ�Ԫ�أ������������ջ���ظ���������ֱ�����ʽ����ˣ��������ó���ֵ��Ϊ���ʽ�Ľ����
����ǰ׺���ʽ��- �� + 3 4 5 6����
(1) ��������ɨ�裬��6��5��4��3ѹ���ջ��
(2) ����+���������˵���3��4��3Ϊջ��Ԫ�أ�4Ϊ�ζ�Ԫ�أ�ע�����׺���ʽ���Ƚϣ��������3+4��ֵ����7���ٽ�7��ջ��
(3) �������ǡ����������˵���7��5�������7��5=35����35��ջ��
(4) �����-������������35-6��ֵ����29���ɴ˵ó����ս����
���Կ������ü��������ǰ׺���ʽ��ֵ�Ǻ����׵ġ�

#��׺���ʽ����׺�Ƿ����沨��ʽ��
��׺���ʽ��ǰ׺���ʽ���ƣ�ֻ�������λ�ڲ�����֮��
��׺���ʽ�ļ������ֵ��
��ǰ׺���ʽ���ƣ�ֻ��˳���Ǵ������ң�
��������ɨ����ʽ����������ʱ��������ѹ���ջ�����������ʱ������ջ�����������������������������Ӧ�ļ��㣨�ζ�Ԫ�� op?ջ��Ԫ�أ������������ջ���ظ���������ֱ�����ʽ���Ҷˣ��������ó���ֵ��Ϊ���ʽ�Ľ����
�����׺���ʽ��3 4 + 5 �� 6 -����
(1) ��������ɨ�裬��3��4ѹ���ջ��
(2) ����+���������˵���4��3��4Ϊջ��Ԫ�أ�3Ϊ�ζ�Ԫ�أ�ע����ǰ׺���ʽ���Ƚϣ��������3+4��ֵ����7���ٽ�7��ջ��
(3) ��5��ջ��
(4)?�������ǡ����������˵���5��7�������7��5=35����35��ջ��
(5) ��6��ջ��
(6) �����-������������35-6��ֵ����29���ɴ˵ó����ս����

*/
void Trans(STR *InStr , char LastStr[])
{/*���������ʽת��Ϊ��׺���ʽ*/

	int i = 1;
	char Stack[MAX];/*��Ϊջʹ��*/
	char ChStr = InStr->Str[i];	//���ڱ������������ʱԪ��
	i++;
	int LastStrPos = 1, StackTop = 0;	//StackTop���ڱ�ʾջ�������ջû�в��ÿα��ϵ����֣�����ֱ�Ӱ�ջ��ָ��Ԫ�� 

	while (ChStr != '#'){//#�����������ʽ�Ľ�����־

		cout<<"--------------------------------------------------------------------"<<endl;
		cout<<"����ջΪ:  ";
		for(int j=1;j<=StackTop;j++)
			cout<<Stack[j];
		cout<<"              ��׺���ʽΪ:  ";
		for(int k=1;k<LastStrPos;k++)
			cout<<LastStr[k];

		cout<<"       ";


	switch (ChStr){
		case'(':		/*�ж�Ϊ������*/
			StackTop++; 
			Stack[StackTop] = ChStr;

			cout<<"������ push������ջ)   ";
			break;

		case')':		//�ж�Ϊ�����ţ���ȡ������������֮ǰ�������ַ� 
			while (Stack[StackTop] != '('){
				LastStr[LastStrPos] = Stack[StackTop]; 
				StackTop--; 
				cout<<"������ pop������ջ)   ";
				LastStrPos++;
			}
			StackTop--;		//�ӵ���
			cout<<"������ pop������ջ)   ";
			break;
		case'+':		//�ж�Ϊ�Ӽ��ţ�������ջ������С������������ջ������ͽ�ջ����ջ 
		case'-':
			while (StackTop != 0 && Stack[StackTop] != '('){
				LastStr[LastStrPos] = Stack[StackTop];
				StackTop--;
				cout<<"������ pop (����ջ��    ";
				LastStrPos++;
			}
			StackTop++;			//������
			Stack[StackTop] = ChStr;
			cout<<"������ push������ջ)   ";
			break;

		case'*':		/*�ж�Ϊ�˳���*/
		case'/':
			while (Stack[StackTop] == '*' || Stack[StackTop] == '/'){
				LastStr[LastStrPos] = Stack[StackTop];		//���ջ����*����/�������ŵ���׺������
				StackTop--;
				cout<<"������ pop������ջ)   ";
				LastStrPos++;
			}
			StackTop++;
			Stack[StackTop] = ChStr;
			cout<<"������ push������ջ)   ";
			break;

		case' ':break;		//���Կո�

		default:
			while (ChStr >= '0' && ChStr <= '9' || ChStr == '.'){		//�ж�Ϊ���֣������е����ֶ�����ȥ 
				LastStr[LastStrPos] = ChStr; 
				LastStrPos++;
				ChStr = InStr->Str[i];
				i++;
			}
			i--;
			LastStr[LastStrPos] = ' ';		//�����ʱ�����Ԫ��
			LastStrPos++;
		}
		ChStr = InStr->Str[i]; i++;

		cout<<endl;
	}
	while (StackTop != 0){

		cout<<"--------------------------------------------------------------------"<<endl;
		cout<<"����ջΪ:  ";
		for(int j=1;j<=StackTop;j++)
			cout<<Stack[j];
		cout<<"              ��׺���ʽΪ:  ";
		for(int k=1;k<LastStrPos;k++)
			cout<<LastStr[k];
		cout<<"       ";


		LastStr[LastStrPos] = Stack[StackTop];
		LastStrPos++; 
		StackTop--;
		cout<<"������ pop������ջ)   ";
		cout<<endl;

	}

	cout<<"--------------------------------------------------------------------"<<endl;
	cout<<"����ջΪ:  ";
	for(int j=1;j<=StackTop;j++)
		cout<<Stack[j];
	cout<<"              ��׺���ʽΪ:  ";
	for(int k=1;k<LastStrPos;k++)
		cout<<LastStr[k];
	cout<<"       ";
	cout<<endl;

	LastStr[LastStrPos] = ' ';
	LastStrPosT = LastStrPos;
}

float Compvalue(char LastStrTemp[]){	/*�����׺���ʽ��ֵ*/

	float Stack[MAX];		/*��Ϊջʹ��*/
	char ChStr;			//��ʱջԪ��
	int  StackTop = 0;		/*LastStrPosΪLastStr�±꣬StackTopΪStack�±�*/
	int LastStrPos = 1;

	ChStr = LastStrTemp[LastStrPos];
	LastStrPos++;

	while (ChStr != ' '){

		cout<<"--------------------------------------------------------------------"<<endl;
		cout<<"����ջΪ:  ";
		for(int j=1;j<=StackTop;j++)
		cout<<Stack[j]<<" ";
		

		switch (ChStr){
		case'+':
			Stack[StackTop - 1] = Stack[StackTop - 1] + Stack[StackTop];
			StackTop--;
			cout<<"          ������pop������ջ)   pop������ջ)   operate('+')   push(����ջ��";
			break;
		case'-':
			Stack[StackTop - 1] = Stack[StackTop - 1] - Stack[StackTop];
			StackTop--;
			cout<<"          ������pop������ջ)   pop������ջ)   operate('-')    push(����ջ��";
			break;
		case'*':
			Stack[StackTop - 1] = Stack[StackTop - 1] * Stack[StackTop];
			StackTop--;
			cout<<"          ������pop������ջ)   pop������ջ)   operate('*')    push(����ջ��";
			break;
		case'/':
			if (Stack[StackTop] != 0)
				Stack[StackTop - 1] = Stack[StackTop - 1] / Stack[StackTop];
			else{
				exit(0);/*�쳣�˳�*/
			}
			StackTop--;
			cout<<"          ������pop������ջ)   pop������ջ)   operate('/')    push(����ջ��";
			break;
		default:
			float a=0.1;
			float NumStr = 0;	//�������ַ�ת��Ϊ����
			bool FlNum = 0;
			while (ChStr >= '0' && ChStr <= '9' || ChStr == '.'){
				if (ChStr == '.') {
					FlNum = 1;
				}
				else if (!FlNum) {
					NumStr = 10 * NumStr + ChStr - '0';/*�������ַ�ת��Ϊ��Ӧ����ֵ*/
				}
				else if (FlNum) {
					NumStr +=a * (ChStr - '0');	/*����С��*/
					a=a/10;
				}
				
				ChStr = LastStrTemp[LastStrPos];
				LastStrPos++;
			}
			StackTop++;
			cout<<"     ������ push������ջ)   ";
			Stack[StackTop] = NumStr;


		
		}
		cout<<endl;
		ChStr = LastStrTemp[LastStrPos];
		LastStrPos++;
	}


	cout<<"--------------------------------------------------------------------"<<endl;
	cout<<"����ջΪ:  ";
	for(int j=1;j<=StackTop;j++)
	cout<<Stack[j]<<" ";
	cout<<endl;

	return Stack[StackTop];
}


void GiveStr(char GetString[] , char *TheStr) {
	STR InStr;
	char LastStr[MAX];/*�洢��׺���ʽ*/

	InStr.Long = 0;

	for (int i = 0; i<strlen(GetString); i++) {
		if(GetString[i+1]=='+'&&GetString[i+2]=='+')
		{	
			GetString[i]++;
			InStr.Long++;
		    InStr.Str[InStr.Long] = GetString[i];
		    i+=2;
			continue;
		}
		if(GetString[i+1]=='-'&&GetString[i+2]=='-')
		{	
			GetString[i]--;
			InStr.Long++;
		    InStr.Str[InStr.Long] = GetString[i];
		    i+=2;
			continue;
		}
		if(GetString[i+1]=='^')
		{
			if(GetString[i]<='3')
			{
				GetString[i]=(GetString[i]-'0')*(GetString[i]-'0')+'0';
				InStr.Long++;
				InStr.Str[InStr.Long]=GetString[i];
				i+=2;
			}	
			else if(GetString[i]>='3')
			{
				int pp=(GetString[i]-'0')*(GetString[i]-'0');
				GetString[i]=pp/10+'0';
				GetString[i+1]=pp-10*(GetString[i]-'0')+'0';
				InStr.Long++;
				InStr.Str[InStr.Long]=GetString[i];
				InStr.Long++;
				InStr.Str[InStr.Long]=GetString[i+1];
				i+=2;
			}
			continue;
		}
		InStr.Long++;
		InStr.Str[InStr.Long] = GetString[i];
	}

	cout<<"************************************************************************"<<endl;
	cout<<"************************************************************************"<<endl;
	cout<<"***********                 ��������̨ϵͳ                  ************"<<endl;
	cout<<"************************************************************************"<<endl;
	cout<<"************************************************************************"<<endl;
	cout<<"�������ʽΪ��  ";
	for(i=1;i<=InStr.Long;i++)
		cout<<InStr.Str[i];
	
	cout<<endl;


	InStr.Long++;
	InStr.Str[InStr.Long] = '#';


	cout<<"���������ʽת��Ϊ��׺���ʽ"<<endl;
	Trans(&InStr, LastStr);
	
	cout<<endl;
	cout<<endl;
	
	cout<<"�����׺���ʽ"<<endl;
	LastV = Compvalue(LastStr);
	LastV == (int)LastV ? sprintf(TheStr , "%.0f" , LastV) : sprintf(TheStr, "%.4f", LastV);
}

void InitPos() {//��ʼ������λ�� 
	Pos[0].x[0] = 0; Pos[0].y[0] = 0; Pos[0].x[1] = WINSIZEX; Pos[0].y[1] = WINKEYY  * 2;
	
	int k = 1;
	for (int i = 2; i < 8; i++) {
		for (int j = 0; j < 4; j++) {
			Pos[k].x[0] = j * WINKEYX;	//����xy����
			Pos[k].y[0] = i * WINKEYY;

			Pos[k].x[1] = (j + 1) * WINKEYX;	//����xy����
			Pos[k].y[1] = (i + 1) * WINKEYY;
			k++;
		}
	}
}

int JudgePos(int x ,int y) {//�����ж��������λ��
	if (x > 0 && x < WINSIZEX && y > 0 && y < WINKEYY * 2)	//�ж��ı������
		return 0;
	for (int i = 1; i <= 4; i++) {
		if (x >= Pos[i].x[0] && x <= Pos[i].x[1]) {
			for (int j = i; j <= 24; j += 4) {
				if (y >= Pos[j].y[0] && y <= Pos[j].y[1]) {
					return j;
				}
			}
		}
		
	}
}

/*
nHeight 
ָ���߶ȣ��߼���λ���� 
nWidth 
�ַ���ƽ����ȣ��߼���λ�������Ϊ 0�����������Ӧ�� 
lpszFace 
�������ơ� 
*/
void PrintStr() {
	settextstyle(35, 0, _T("Prestige Elite Std"));	//�������������С����ȣ�������ʽ
	outtextxy(7,7,GetStr);
}

void GetKey() {//����������� 
	  /*FlushMouseMsgBuffer ��������Ϣ�������� 
		GetMouseMsg ��ȡһ�������Ϣ�������ǰ�����Ϣ������û�У���һֱ�ȴ��� 
		MouseHit ��⵱ǰ�Ƿ��������Ϣ�� 
		MOUSEMSG ���������Ϣ�Ľṹ�塣 */
	MOUSEMSG Msg;
	RECT r = { 0 , WINKEYY * 2 / 3 , WINSIZEX, WINKEYY * 2 };
	IMAGE ClearImgUp , ClearImgDown;

	int ProPos = 0;	//��һ������İ�ť
	int temp = 0;	//��ǰ����İ�ť
	int InCon = 0;	//������ַ���
	int TempI = 0;
	float LastStrTemp = LastV;
	char StrTemp[MAX];
	char M_Str[20] = { '/0' };

	FlushMouseMsgBuffer();
	getimage(&ClearImgUp, 1, 1, WINSIZEX , WINKEYY * 2 / 3);	//�����������Ľ�ͼ�����ڸ���ԭ�����������
	getimage(&ClearImgDown, 1, WINKEYY * 2 / 3, WINSIZEX, WINKEYY * 2);	//����������Ľ�ͼ�����ڸ���ԭ�����������

	while (TRUE) {
		
		Msg = GetMouseMsg();
	
		if (Msg.uMsg) {
			temp = JudgePos(Msg.x, Msg.y);

			switch (Msg.uMsg) {
			case WM_LBUTTONDOWN:
				setlinecolor(RGB(230, 230, 230));
				setlinestyle(PS_SOLID | PS_JOIN_BEVEL, 5);
				//setfillcolor(RGB(150, 150, 150));
				rectangle(Pos[temp].x[0], Pos[temp].y[0], Pos[temp].x[1], Pos[temp].y[1]);

				switch (temp) {
				
				case 1:
					GetStr[0] = '\0';
					putimage(1, 1, &ClearImgUp);
					putimage(1, WINKEYY * 2 / 3, &ClearImgDown);
					InCon = 0;
					PrintStr();
					break;
				case 2:
					if(InCon > 0)	//�ж��Ƿ���������ַ�
						GetStr[InCon - 1] = '\0';
					putimage(1, 1, &ClearImgUp);
					InCon--;
					PrintStr();
					break;
				case 3:
					strcat(GetStr, M_Str);
					InCon++;
					PrintStr();
					break;
				case 24:
					settextstyle(50, 0, _T("Prestige Elite Std"));	//���������С����ȣ�������ʽ
					putimage(1, WINKEYY * 2 / 3, &ClearImgDown);
					GiveStr(GetStr, TheLastStr);
					drawtext(_T(TheLastStr), &r, DT_RIGHT | DT_VCENTER | DT_SINGLELINE);
					break;
				//case 7:
				//case 8:
					break;
				default:
						strcat(GetStr, KeyStr[temp - 1]);
						InCon++;
						PrintStr();
				}
			
				Sleep(50);
				break;
			case WM_RBUTTONDOWN:
				setlinecolor(RGB(230, 230, 230));
				setlinestyle(PS_SOLID | PS_JOIN_BEVEL, 5);
				rectangle(Pos[temp].x[0], Pos[temp].y[0], Pos[temp].x[1], Pos[temp].y[1]);

				switch (temp) {
				case 3:
					strcpy(M_Str, TheLastStr);
					break;
				}
				break;
			}
		}

		setlinecolor(RGB(230, 230, 230));
		setlinestyle(PS_SOLID | PS_JOIN_BEVEL, 5);
		//setfillcolor(RGB(210,210,210));
		rectangle(Pos[ProPos].x[0], Pos[ProPos].y[0], Pos[ProPos].x[1], Pos[ProPos].y[1]);

		if (temp != 0) {
			setlinecolor(RGB(200, 200, 200));
			setlinestyle(PS_SOLID | PS_JOIN_BEVEL, 3);
			//setfillcolor(RGB(230, 230, 230));
			rectangle(Pos[temp].x[0], Pos[temp].y[0], Pos[temp].x[1], Pos[temp].y[1]);
			ProPos = temp;
		}
			
	}
}

/*

���������� ���� 
FILLSTYLE �����ʽ���� 
getbkcolor ��ȡ��ǰ��ͼ����ɫ�� 
getbkmode ��ȡͼ�������������ʱ�ı���ģʽ�� 
getfillcolor ��ȡ��ǰ�����ɫ�� 
getfillstyle ��ȡ��ǰ�����ʽ�� 
getlinecolor ��ȡ��ǰ������ɫ�� 
getlinestyle ��ȡ��ǰ������ʽ�� 
getpolyfillmode ��ȡ��ǰ��������ģʽ�� 
getrop2 ��ȡǰ���Ķ�Ԫ��դ����ģʽ�� 
LINESTYLE ������ʽ���� 
setbkcolor ���õ�ǰ��ͼ����ɫ�� 
setbkmode ����ͼ�������������ʱ�ı���ģʽ�� 
setfillcolor ���õ�ǰ�����ɫ�� 
setfillstyle ���õ�ǰ�����ʽ�� 
setlinecolor ���õ�ǰ������ɫ�� 
setlinestyle ���õ�ǰ������ʽ�� 
setpolyfillmode ���õ�ǰ��������ģʽ�� 
setrop2 ����ǰ���Ķ�Ԫ��դ����ģʽ�� 



*/
//�����������
void DrawTe() {
	
	LOGFONT f;
	settextcolor(RGB(20, 20, 20));	//����������ɫ
	settextstyle(30, 0, _T("Prestige Elite Std"));	//���������С����ȣ�������ʽ
	setbkmode(TRANSPARENT);				//�����������Ϊ͸��ɫ
	gettextstyle(&f);                     // ��ȡ��ǰ��������
										  // f.lfHeight = 48;                      // �������ָ߶�Ϊ48
	f.lfWeight=700;									  // _tcscpy(f.lfFaceName, _T("����"));    // ��������Ϊ�����塱
	f.lfQuality = ANTIALIASED_QUALITY;    // �������Ч��Ϊ�����  
	settextstyle(&f);                     // ����������ʽ


	for (int i = 0, j = 0; strcmp(KeyStr[i], "$"); i++) {	//ѭ������ַ������������
		if (i % 4 == 0 && i != 0) j++;

		outtextxy(WINKEYX / 2.5 + (i % 4) * WINKEYX, WINKEYY * (2 + j) + WINKEYY / 3, _T(KeyStr[i]));	//�����������

	}

}

//���ư�������
void DrawWindow() {
	setfillcolor(RGB(230, 230, 230));				//�����ɫ
	solidrectangle(0, 0, WINSIZEX, WINKEYY * 2);	//���Ʊ������򣬻������Σ��ޱ߿�

	setfillcolor(RGB(255, 255, 255));
	solidrectangle(0, WINKEYY * 2, WINSIZEX, WINSIZEY);	//���Ʋ�������

	setfillcolor(RGB(240, 240, 240));
	solidrectangle(WINKEYX * 3, WINKEYY * 3, WINKEYX * 4 , WINSIZEY);	//���Ʋ�������
	solidrectangle(0, WINKEYY * 2, WINSIZEX, WINKEYY * 3);	//���Ʋ�������

	setlinecolor(RGB(230, 230, 230));
	setlinestyle(PS_SOLID | PS_JOIN_BEVEL, 5);

	for (int i = 2; i <= 8; i++) {
		line(0, i * WINKEYY, WINSIZEX,  i * WINKEYY);		//������
		line((i - 2) * WINKEYX, WINKEYY * 2, (i - 2) * WINKEYX, WINSIZEY);		//������
	}
	line(0, WINKEYY * 2 / 3, WINSIZEX , WINKEYY * 2 / 3);
}

int main()
{
	
	initgraph(WINSIZEX, WINSIZEY,SHOWCONSOLE);   // ����һ��500*600�Ĵ���

	
	DrawWindow();
	DrawTe();
	InitPos();
	GetKey();

	closegraph();		   // �ر�ͼ�ο�   
	return 0;
}
