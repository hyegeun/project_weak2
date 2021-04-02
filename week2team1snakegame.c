#include <stdio.h>
#include <windows.h>
#include <time.h>
#include <string.h>
#include <conio.h>

void textcolor(int color_number); //�۾� ���� ���� 
void gotoxy(int x, int y); // ��ǥ�� ����� ���� 
void menu(); //�޴� �Լ� 
void print(); //���� ���� �Լ� 
void auth(); //���� ���� �� ����� ���� 
void boarder(); //������ �Լ� 
void Life(); //life�� ���� �� ���� �Լ�  
void food(); //���� ���� �Լ� 
void move(); //�� �̵� �Լ� 
void up(); //���� ���� �̵��ϴ� �Լ� 
void left(); //���� �������� �̵��ϴ� �Լ� 
void right(); //���� ���������� �̵��ϴ� �Լ� 
void down(); //���� �Ʒ��� �̵��ϴ� �Լ� 
void collision(); //���� �浹 ���� Ȯ�� �Լ� 
void game(); //���� ���� �Լ�   
void Score(); //���� ���� �Լ�  
void Bestscore(); //Bestscore ��� �Լ�  
void exitgame(); // ���� ������ �Լ�
void record(); // Rank ��� �Լ� 
void print_ascii_art();

#define MAX_USER 10

//��������  
int i; //����� Ȯ�� �뵵  
int count =0; //���ο� ����� ��ȣ ���̱�  
int a, b; 
int bestscore; //���� �ְ� ���        
int firstx[100]; //�� ���� ����  
int firsty[100]; //�� ���� ����  
int key; // Ű���� �Է¹޴� ����  
int score; //����  
int life; //��ȸ  
int speed; //���� �̵��ϴ� �ӵ�  
int body;  //���� �Ӹ�+���� ����  

struct ranker
{
	char name[20];
	int score;
};

struct ranker r[MAX_USER];

int main(void) { //���� �Լ�  
	
	system("tiTle Snake Game");
	system("mode con cols=160 lines=40"); //�ܼ�â ũ�� ����  
	
	menu();
	
	return 0;
	
}

void textcolor(int color_number) { //�۾� ���� ����  
	
 SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),color_number);

}

void gotoxy(int x, int y) { //��ǥ ����  
	
	COORD pos={x,y};

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos); 
}

void menu() { //�޴��Լ�  
	
	textcolor(10); 
	printf("\nSnake Game\n");
	textcolor(14);
	printf("\n���� ������\n2�й� 2���� 1��: ������, Ȳ��ȫ\n");
	
	textcolor(7);
	printf("--------------------------------------------------\n");

	
	textcolor(11);
	printf("\n1. ���� ����\n\n");
	printf("2. ���� ����\n\n");
	printf("3. ���� ���\n\n");
	printf("4. ���� ����\n");
	int num;    
	
	textcolor(7);
	printf("\n������ �ϴ� ��ȣ�� �Է����ּ���.\n");
	scanf("%d", &num);
	switch (num) {
		
		case 1:
			system("cls");
			print();
			break;
		
		case 2:
			system("cls");
			auth();
			break;
		
		case 3:
			system("cls");
			record();
			break; 
			
		
		case 4:
		    system("cls");
		    exitgame();
		    break;
				
		default:
			printf("\n�߸� �Է��ϼ̽��ϴ�.\n");
			Sleep(1000);
			system("cls");
			menu(); 
			break;
	}
	
	printf("\n�̿����ּż� �����մϴ�.");
	Sleep(10000);
	system("cls");
	
}

void print() { //���� ���� �Լ�  
	
	textcolor(11);
	printf("\n���� ����\n");
	
	textcolor(7);
	int k=0;
	for (k=0; k<40; k++) 
		printf("-");
	
	
	printf("\n1. Ű���� ����Ű�� �̿��� ���� �����̰� �Ͽ� ȭ�鿡 ����� ���� �Դ� �����Դϴ�.\n\n");
	printf("2. ���� ���� �ϳ� ���� ������ ������ 1�� �ö󰡸� ���� ���뵵 ������ϴ�.\n\n"); 
	printf("3. space�ٸ� ���� ��� ������ �Ͻ������Ǹ� ����Ű�� ������ �ٽ� ����˴ϴ�.\n\n");
	printf("4. ��ȸ�� �� �� ���Դϴ�.\n\n");
	printf("5. ���� ������ȯ �ϴٰ� ���̳� �ڱ� ���뿡 �ε��� �� ���� ��ȸ�� ��� ���� ���, ������ ������ �˴ϴ�.\n\n");
	
	int num;
	printf("\n�޴��� ���ư��÷��� 1, �ٷ� ������ �����Ͻ÷��� 2�� �Է����ּ���.\n");
	scanf("%d", &num);
	
	switch (num) {
		case 1:
			system("cls");
			menu();
			break;
		
		case 2:
			system("cls");
			auth();
			break;
		
		default:
			printf("\n�߸� �Է��ϼ̽��ϴ�. �޴��� ���ư��ϴ�.\n");
			
			Sleep(1000);
			system("cls");
			menu();
			break;
	}
} 

void auth() { //���� ���� �� ����� ����  

	char checkname[20];
	i=0; 
	
	printf("\n����� �̸��� 'ȫ�浿'ó�� �����ּ���.\n");
	scanf("%s", checkname);
	fflush(stdin); //�Է� ���� ����  
	
	while ( !(strcmp(checkname, r[i].name) == 0) ) { //�����ϴ� �̸� Ȯ��  
		
		if ( i == count) {
			
			count++;
			break;
    	}
		else i++;
    }
    
	strncpy( r[i].name, checkname, 20 );
	life = 1;
	
	system("cls");
	game();

}

void boarder() { //������ �Լ�  
	
	int j, k;
	
	textcolor(7);
	for (j = 5; j < 65; j+=2) {
		gotoxy(j, 5);
		printf("��");
	}
	
	for (k = 6; k < 33; k++) {
		gotoxy(5, k);
		printf("��");
	}
	
	for (k = 6; k < 33; k++) {
		gotoxy(63, k);
		printf("��");
	}
	
	for (j = 5; j < 65; j+=2) {
		gotoxy(j, 33);
		printf("��");
	}
	
}

void food() { //���� ���� �Լ�  
	    	
	textcolor(6);
	srand((unsigned)time(NULL));
 	    
    a= 7 + (rand() % 28)*2; // ����â �� �������� �������� ������ �����ǵ���  
	b= 6 + rand() % 27;
	
	int num;
    for ( num =0; num <= body; num++) {
		
		if ( (a==firstx[num]) && (b==firsty[num]) ) { //������ ��� ���ļ� �������� �ʱ� ����  
			a= 7 + (rand() % 28)*2;  
	        b= 6 + rand() % 27;
	        num= 0; 
		}
	}
	gotoxy(a, b);
	printf("��");
}

void game() { //���� ���� �Լ�  
	
	Life(); 
	
	if (life == 1) 
	    food();
	    
	else {
		gotoxy(a, b);
		printf("  ");
		food();
	}
	
	textcolor(10);
    gotoxy(5, 3);
	printf("����: %d", score);
	gotoxy(58, 3);
	printf("Life: %d", life); 

	textcolor(11);
	gotoxy(70, 5);
	printf("%s ��", r[i].name );
	gotoxy(70, 8);
	printf("���� �ְ� ���: %d", r[i].score);
	gotoxy(70, 11);
	textcolor(14);
	printf("���� �ְ� ���: %d", bestscore);
	textcolor(7);
	
	boarder();
	
	move();
	
}

void Life() {
	
	int checkbody;
	firstx[0]= 51;
    firsty[0]= 15;
	
	if (life == 1) { //life�� 1�̸�  
        firstx[1]= 49;
        firsty[1]= 15;
        firstx[2]= 47;
        firsty[2]= 15;
    
        body = 2;
	    score = 0; 
	    speed = 230;
	    
	    textcolor(11);
	    gotoxy(firstx[0], firsty[0]);
		printf("��");
			
		gotoxy(firstx[1], firsty[1]);
		printf("��");
			
		gotoxy(firstx[2], firsty[2]);
		printf("��");
		textcolor(7);
	}
	else { //life�� 0�̸�  
		
		if ( body > 20 ) { // body�� 20 �ʰ��� ��  
		
			for (checkbody =0; checkbody <= body; checkbody++) {
				gotoxy(firstx[checkbody], firsty[checkbody]);
				printf("  ");
			}
			
			textcolor(11);
			gotoxy(firstx[0], firsty[0]);
			printf("��");
			
			body= 20;
			 
			for( checkbody = 1; checkbody <= body ; checkbody++) {
	
				firstx[checkbody]= firstx[checkbody-1] -2;
				firsty[checkbody]= firsty[checkbody-1];
				gotoxy(firstx[checkbody], firsty[checkbody]);
				printf("��");
			}
			textcolor(7);
	
			
		}
		
		else { //body�� 20 ������ ��  
		
			for (checkbody =0; checkbody <= body; checkbody++) {
				gotoxy(firstx[checkbody], firsty[checkbody]);
				printf("  ");
			}
			
			textcolor(11);
			gotoxy(firstx[0], firsty[0]);
			printf("��");
			
			
			for( checkbody = 1; checkbody <=body ; checkbody++) {
	
				firstx[checkbody]= firstx[checkbody-1] -2;
				firsty[checkbody]= firsty[checkbody-1];
				gotoxy(firstx[checkbody], firsty[checkbody]);
				printf("��");
			}
			textcolor(7);
		}
		
	}
}

void move() { //�� �̵� �Լ� 
	
	while (1) { //���ѷ���  
		
		if (kbhit()) {
			
			loop:
							
			    key = getch(); //Ű���� �Է��� ����  
		
		        switch (key) {
		
		            case 72: // ����Ű �踦 �Է� ����  
		        	    while (1) { //���ѷ���  
		        	    
		        	        if (kbhit())  //Ű���� �Է� Ȯ��  
		        		        goto loop; //Ű���� �Է��� ������ �ٽ� loop���� ���ư�  
							
		        		
		        		    up(); //�̵� �Լ�  
		        		    
		        		    collision(); //�浹 ���� Ȯ��  
							
		        		    Score(); //���� Ȯ��  
					    }
					    break;    
			        
			
		            case 75: //����Ű �縦 �Է� ����  
			            while (1) {
			            	
			            	if (kbhit()) 
		        		        goto loop;
		        		
		        		    left();
		        		    
		        		    collision();
							
		        		    Score();
		        		}
			            break;
			
		            case 77: //����Ű �渦 �Է� ����  
			            while (1) {
			            	
			            	if (kbhit()) 
		        		        goto loop;
		        		
		        		    right();
		        		    
		        		    collision();
							
		        		    Score();
		        		}
			            break;
			
		            case 80: //����Ű �鸦 �Է� ����  
			            while (1) {
			            	
			            	if (kbhit()) 
		        		        goto loop;
		        		
		        		    down();
		        		    
		        		    collision();
							
		        		    Score();
		        		}
			            break;
			            
			        case 27: // esc �Է½� ���� �Է±��� �Ͻ����� 
						break; 
			        
			        default:
			    	    break;
		
		        }
		
	    }
	
	}
		
}

void up() { //���� ���� �̵��ϴ� �Լ�  
		
	textcolor(11);
		
	Sleep(speed);
	
	int checkbody;
	
	for( checkbody= body; checkbody >=0; checkbody--) { //���� ������ �ڸ��� ����  
		
		gotoxy(firstx[checkbody], firsty[checkbody]);
		printf("  ");
	}
	
	for (checkbody= body; checkbody >=1; checkbody--) { //���� ������ �̵���Ŵ  
		
		firstx[checkbody] = firstx[checkbody-1];
		firsty[checkbody] = firsty[checkbody-1];
	}
	
	firsty[0] -= 1; //���� �Ӹ� �̵� ����  
	
	gotoxy(firstx[0], firsty[0]); //���� �Ӹ� print  
	printf("��");
	
	for (checkbody = body; checkbody >=1; checkbody--) { //���� ���� print  
		
		gotoxy(firstx[checkbody], firsty[checkbody]);
		printf("��");
	}	
		
}

void left() { //���� �������� �̵��ϴ� �Լ�  

	textcolor(11);
		
	Sleep(speed);
	
	int checkbody;
	
	for( checkbody = body; checkbody >=0; checkbody--) {
		
		gotoxy(firstx[checkbody], firsty[checkbody]);
		printf("  ");
	}
	
	for (checkbody= body; checkbody >=1; checkbody--) {
		
		firstx[checkbody] = firstx[checkbody-1];
		firsty[checkbody] = firsty[checkbody-1];
	}
	
	firstx[0] -= 2;
	
	gotoxy(firstx[0], firsty[0]);
	printf("��");
	
	for (checkbody = body; checkbody >=1; checkbody--) {
		
		gotoxy(firstx[checkbody], firsty[checkbody]);
		printf("��");
	}
	
}

void right() { //���� ���������� �̵��ϴ� �Լ�  
		
	textcolor(11);
	
	Sleep(speed);
	
	int checkbody;
	
	for( checkbody= body; checkbody >=0; checkbody--) {
		
		gotoxy(firstx[checkbody], firsty[checkbody]);
		printf("  ");
	}
	
	for (checkbody= body; checkbody >=1; checkbody--) {
		
		firstx[checkbody] = firstx[checkbody-1];
		firsty[checkbody] = firsty[checkbody-1];
	}
	
	firstx[0] += 2;
	
	gotoxy(firstx[0], firsty[0]);
	printf("��");
	
	for (checkbody = body; checkbody >=1; checkbody--) {
		
		gotoxy(firstx[checkbody], firsty[checkbody]);
		printf("��");
	}
	
}

void down() { //���� �Ʒ������� �̵��ϴ� �Լ�  
	
	textcolor(11);
	
	Sleep(speed);
	
	int checkbody;
	
	for( checkbody= body; checkbody >=0; checkbody--) {
		
		gotoxy(firstx[checkbody], firsty[checkbody]);
		printf("  ");
	}
	
	for (checkbody= body; checkbody >=1; checkbody--) {
		
		firstx[checkbody] = firstx[checkbody-1];
		firsty[checkbody] = firsty[checkbody-1];
	}
	
	firsty[0] += 1;
	
	gotoxy(firstx[0], firsty[0]);
	printf("��");
	
	for (checkbody = body; checkbody >=1; checkbody--) {
		
		gotoxy(firstx[checkbody], firsty[checkbody]);
		printf("��");
	}
}

void collision() { //���� �浹 ���� Ȯ�� �Լ�  
	
	int check= body;
	
	if ( firstx[0] <= 5 || firstx[0] >= 63 || firsty[0] <= 5 || firsty[0] >= 33 ) { //���Ӻ��� ���� �浹�ϴ��� Ȯ�� 
		
		if (life ==1 ) {
			life--;
			Sleep(500);
			game();
		} 
		
		else {			
			gotoxy(23, 17); 
		    textcolor(6);
		    printf("������ ����Ǿ����ϴ�.");
		
		    if ( score > r[i].score ) { //����� �ְ� ��� Ȯ��  
			
			    r[i].score = score;
		        gotoxy(23, 19);
		        printf("���� �ְ� ���: %d", r[i].score);
		    
		        if ( score > bestscore ) { //���� �ְ� ��� Ȯ��  
		    	
		    	    bestscore = score;
		    	    gotoxy(23, 21);
		    	    textcolor(14);
		    	    printf("���� �ְ� ���: %d", bestscore);
		    	    textcolor(7);
		    	    gotoxy(23, 23);
		    	    print_ascii_art();
			    }
		    }
			
		    Sleep(5000);
		    system("cls");
		    textcolor(7);
		    menu();
		}
		
	}
	
	while ( !(firstx[0]==firstx[check] && firsty[0]==firsty[check]) ) { //���� �Ӹ��� ����� �浹�ϴ��� Ȯ��  
		
		if (check == 1) {
			break;
		}
		else check--;
	}
	
	if ( (firstx[0]==firstx[check] && firsty[0]==firsty[check]) ) { //���� �Ӹ��� ����� �浹�ϸ� ���� ����  
		
		if (life == 1) {
			
			life--;
			Sleep(500);
			game();
		}
		
		else {
			
			gotoxy(23, 17); 
		    textcolor(6);
		    printf("������ ����Ǿ����ϴ�.");
		    
		    if ( score > r[i].score ) {
			
			    r[i].score = score;
		        gotoxy(23, 19);
		        printf("���� �ְ� ���: %d", r[i].score);
		    
		        if ( r[i].score > bestscore ) {
		    	
		    	    bestscore = r[i].score;
		    	    gotoxy(23, 21);
		    	    textcolor(14);
		    	    printf("���� �ְ� ���: %d", bestscore);
		    	    textcolor(7);
		    	    gotoxy(23, 23);
		    	    print_ascii_art();
			    }
		    }
		    Sleep(5000);
		    system("cls");
		    textcolor(7);
		    menu();
		    }
	}	
}

void Score() { //���� ���� �Լ�  
	
	if ( firstx[0]==a && firsty[0]==b ) { //���� �Ӹ��� ���İ� ������ ��  
		score += 1; //���� ����  
		
		if (speed > 5) 
			speed -= 5; //�ӵ� ����  
		 
		textcolor(10);
    	gotoxy(5, 3);
	    printf("����: %d", score);  //���� print  
	    body++; //���� ���� �߰�  
	    food(); //���� ���� ����  
	    Bestscore();
	}
	textcolor(7);
}

void Bestscore() {

	if ( score == bestscore+1 ) {
		
		textcolor(14);
		gotoxy(70, 15);
		printf("�����      ������    ������    ������");
		gotoxy(70, 16);
		printf("��    ��      ��            ��                ��    ");
		gotoxy(70, 17);
		printf("��    ��      ��            ��                ��    ");
		gotoxy(70, 18);
		printf("������    ������    ������        ��    ");
		gotoxy(70, 19);
		printf("��      ��    ��                    ��        ��    ");
		gotoxy(70, 20);
		printf("��      ��    ��                    ��        ��    ");
		gotoxy(70, 21);
		printf("������    ������    ������        ��    ");
		
		gotoxy(70, 23);
		printf("������    ������    ������    �����      ������");
		gotoxy(70, 24);
		printf("��            ��            ��      ��    ��    ��      ��");
		gotoxy(70, 25);
		printf("��            ��            ��      ��    ��    ��      ��");
		gotoxy(70, 26);
		printf("������    ��            ��      ��    �����      ������");
		gotoxy(70, 27);
		printf("        ��    ��            ��      ��    ��    ��      ��");
		gotoxy(70, 28);
		printf("        ��    ��            ��      ��    ��     ��     ��");
		gotoxy(70, 29);
		printf("������    ������    ������    ��      ��    ������");
		textcolor(7);
	}	
}


void record() //��ŷ �Լ�  
{	
	int i,j,tmp;
	char temp_name[20] = {0,};
	struct ranker tmp_user[MAX_USER] = {0,};	// rank ���� ������ ���� ����ü 
	
	textcolor(10);
	printf("\n\n\t============ [HISTORY] ============\n\n");
	textcolor(7);
	
	for(i = 0; i < count; i++)
	{
		printf("\t| [%d] Score : %2d\t| Name : %s\n", (i+1), r[i].score, r[i].name);
		tmp_user[i].score = r[i].score;		// rank ���� ���� ���� 
		strncpy(tmp_user[i].name, r[i].name, 20);
	}
	
	// ���� ���� ������ ���� (���Ľ� �ٲ�� history�� ���� tmp_user�� ���� �� ����)
	for(i = 0; i < count-1; i++)
	{
		for(j = i+1; j < count; j++)
		{
			if(tmp_user[i].score < tmp_user[j].score)
			{
				tmp = tmp_user[j].score;
				tmp_user[j].score = tmp_user[i].score;
				tmp_user[i].score = tmp;
				
				strncpy(temp_name, tmp_user[j].name, 20);
				strncpy(tmp_user[j].name, tmp_user[i].name, 20);
				strncpy(tmp_user[i].name, temp_name, 20);	
			}	
		}	
	}
	textcolor(14);
	printf("\n\n\n\n\t=============  [RANK]  =============\n\n");
	printf("\t| [1st] Score : %d\t| Name : %s\n\n", tmp_user[0].score, tmp_user[0].name);	// ���ĵ� rank ���� ����ü �迭 0 ~ 2��°���� ��� 
	textcolor(11);
	printf("\t| [2nd] Score : %d\t| Name : %s\n", tmp_user[1].score, tmp_user[1].name); 
	printf("\t| [3rd] Score : %d\t| Name : %s\n", tmp_user[2].score, tmp_user[2].name);
	
	int num;
	textcolor(7);
	printf("\n\n\n�޴��� ���ư��÷��� 1, �ٷ� ������ �����Ͻ÷��� 2�� �Է����ּ���.\n");
	scanf("%d", &num);
	
	switch(num)
	{
		case 1:
			system("cls");
			menu();
			break;
		
		case 2:
			system("cls");
			auth();
			break;
		
		default:
			printf("\n\n�߸� �Է��ϼ̽��ϴ�. �޴��� ���ư��ϴ�.\n");
			Sleep(1000);
			system("cls");
			menu();
			break;
	}
}

void exitgame() { //���� ������ �Լ�  
	
	int num;
	printf("\n���� ������ �����Ͻðڽ��ϱ�?\n");
	printf("\n���Ḧ ���Ͻø� 1, �ٽ� �޴��� ���ư����� 2�� �Է����ּ���.\n");
	scanf("%d", &num);
	
	switch (num) {
		
		case 1:
			system("cls");
			break;
			
		case 2:
			system("cls");
			menu();
			break;
			
		default:
			printf("\n\n�߸� �Է��ϼ̽��ϴ�. �޴��� ���ư��ϴ�.\n");
			Sleep(1000);
			system("cls");
			menu();
			break;
			
	}
}

void print_ascii_art()
{
	textcolor(10);
	printf("\n             ____\n");
	printf("            / . .\\\n");
	printf("            \\  ---<\n");
	printf("             \\  /\n");
	printf("   __________/ /\n");
	printf("-=:___________/\n");
}

