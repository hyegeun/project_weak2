#include <stdio.h>
#include <windows.h>
#include <time.h>
#include <string.h>
#include <conio.h>

void textcolor(int color_number); //글씨 색깔 변경 
void gotoxy(int x, int y); // 좌표를 만들기 위해 
void menu(); //메뉴 함수 
void print(); //게임 설명 함수 
void auth(); //게임 시작 전 사용자 설정 
void boarder(); //게임판 함수 
void Life(); //life에 따른 뱀 생성 함수  
void food(); //음식 생성 함수 
void move(); //뱀 이동 함수 
void up(); //뱀이 위로 이동하는 함수 
void left(); //뱀이 왼쪽으로 이동하는 함수 
void right(); //뱀이 오른쪽으로 이동하는 함수 
void down(); //뱀이 아래로 이동하는 함수 
void collision(); //뱀의 충돌 여부 확인 함수 
void game(); //게임 시작 함수   
void Score(); //점수 증가 함수  
void Bestscore(); //Bestscore 출력 함수  
void exitgame(); // 게임 나가기 함수
void record(); // Rank 출력 함수 
void print_ascii_art();

#define MAX_USER 10

//전역변수  
int i; //사용자 확인 용도  
int count =0; //새로운 사용자 번호 붙이기  
int a, b; 
int bestscore; //게임 최고 기록        
int firstx[100]; //뱀 생성 변수  
int firsty[100]; //뱀 생성 변수  
int key; // 키보드 입력받는 변수  
int score; //점수  
int life; //기회  
int speed; //뱀이 이동하는 속도  
int body;  //뱀의 머리+몸통 개수  

struct ranker
{
	char name[20];
	int score;
};

struct ranker r[MAX_USER];

int main(void) { //메인 함수  
	
	system("tiTle Snake Game");
	system("mode con cols=160 lines=40"); //콘솔창 크기 고정  
	
	menu();
	
	return 0;
	
}

void textcolor(int color_number) { //글씨 색깔 변경  
	
 SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),color_number);

}

void gotoxy(int x, int y) { //좌표 설정  
	
	COORD pos={x,y};

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos); 
}

void menu() { //메뉴함수  
	
	textcolor(10); 
	printf("\nSnake Game\n");
	textcolor(14);
	printf("\n게임 제작자\n2분반 2주차 1팀: 김혜근, 황선홍\n");
	
	textcolor(7);
	printf("--------------------------------------------------\n");

	
	textcolor(11);
	printf("\n1. 게임 설명\n\n");
	printf("2. 게임 시작\n\n");
	printf("3. 게임 기록\n\n");
	printf("4. 게임 종료\n");
	int num;    
	
	textcolor(7);
	printf("\n들어가고자 하는 번호를 입력해주세요.\n");
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
			printf("\n잘못 입력하셨습니다.\n");
			Sleep(1000);
			system("cls");
			menu(); 
			break;
	}
	
	printf("\n이용해주셔서 감사합니다.");
	Sleep(10000);
	system("cls");
	
}

void print() { //게임 설명 함수  
	
	textcolor(11);
	printf("\n게임 설명\n");
	
	textcolor(7);
	int k=0;
	for (k=0; k<40; k++) 
		printf("-");
	
	
	printf("\n1. 키보드 방향키를 이용해 뱀을 움직이게 하여 화면에 띄어진 ★을 먹는 게임입니다.\n\n");
	printf("2. 뱀이 ★을 하나 먹을 때마다 점수가 1씩 올라가며 뱀의 몸통도 길어집니다.\n\n"); 
	printf("3. space바를 누를 경우 게임이 일시중지되며 방향키를 누르면 다시 진행됩니다.\n\n");
	printf("4. 기회는 총 두 번입니다.\n\n");
	printf("5. 뱀이 방향전환 하다가 벽이나 자기 몸통에 부딪혀 두 번의 기회를 모두 끝낸 경우, 게임은 끝나게 됩니다.\n\n");
	
	int num;
	printf("\n메뉴로 돌아가시려면 1, 바로 게임을 시작하시려면 2를 입력해주세요.\n");
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
			printf("\n잘못 입력하셨습니다. 메뉴로 돌아갑니다.\n");
			
			Sleep(1000);
			system("cls");
			menu();
			break;
	}
} 

void auth() { //게임 시작 전 사용자 설정  

	char checkname[20];
	i=0; 
	
	printf("\n사용자 이름을 '홍길동'처럼 적어주세요.\n");
	scanf("%s", checkname);
	fflush(stdin); //입력 버퍼 지움  
	
	while ( !(strcmp(checkname, r[i].name) == 0) ) { //존재하는 이름 확인  
		
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

void boarder() { //게임판 함수  
	
	int j, k;
	
	textcolor(7);
	for (j = 5; j < 65; j+=2) {
		gotoxy(j, 5);
		printf("□");
	}
	
	for (k = 6; k < 33; k++) {
		gotoxy(5, k);
		printf("□");
	}
	
	for (k = 6; k < 33; k++) {
		gotoxy(63, k);
		printf("□");
	}
	
	for (j = 5; j < 65; j+=2) {
		gotoxy(j, 33);
		printf("□");
	}
	
}

void food() { //음식 생성 함수  
	    	
	textcolor(6);
	srand((unsigned)time(NULL));
 	    
    a= 7 + (rand() % 28)*2; // 게임창 안 범위에서 랜덤으로 음식이 생성되도록  
	b= 6 + rand() % 27;
	
	int num;
    for ( num =0; num <= body; num++) {
		
		if ( (a==firstx[num]) && (b==firsty[num]) ) { //음식이 뱀과 겹쳐서 생성되지 않기 위해  
			a= 7 + (rand() % 28)*2;  
	        b= 6 + rand() % 27;
	        num= 0; 
		}
	}
	gotoxy(a, b);
	printf("★");
}

void game() { //게임 시작 함수  
	
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
	printf("점수: %d", score);
	gotoxy(58, 3);
	printf("Life: %d", life); 

	textcolor(11);
	gotoxy(70, 5);
	printf("%s 님", r[i].name );
	gotoxy(70, 8);
	printf("개인 최고 기록: %d", r[i].score);
	gotoxy(70, 11);
	textcolor(14);
	printf("게임 최고 기록: %d", bestscore);
	textcolor(7);
	
	boarder();
	
	move();
	
}

void Life() {
	
	int checkbody;
	firstx[0]= 51;
    firsty[0]= 15;
	
	if (life == 1) { //life가 1이면  
        firstx[1]= 49;
        firsty[1]= 15;
        firstx[2]= 47;
        firsty[2]= 15;
    
        body = 2;
	    score = 0; 
	    speed = 230;
	    
	    textcolor(11);
	    gotoxy(firstx[0], firsty[0]);
		printf("●");
			
		gotoxy(firstx[1], firsty[1]);
		printf("ㅇ");
			
		gotoxy(firstx[2], firsty[2]);
		printf("ㅇ");
		textcolor(7);
	}
	else { //life가 0이면  
		
		if ( body > 20 ) { // body가 20 초과일 때  
		
			for (checkbody =0; checkbody <= body; checkbody++) {
				gotoxy(firstx[checkbody], firsty[checkbody]);
				printf("  ");
			}
			
			textcolor(11);
			gotoxy(firstx[0], firsty[0]);
			printf("●");
			
			body= 20;
			 
			for( checkbody = 1; checkbody <= body ; checkbody++) {
	
				firstx[checkbody]= firstx[checkbody-1] -2;
				firsty[checkbody]= firsty[checkbody-1];
				gotoxy(firstx[checkbody], firsty[checkbody]);
				printf("ㅇ");
			}
			textcolor(7);
	
			
		}
		
		else { //body가 20 이하일 때  
		
			for (checkbody =0; checkbody <= body; checkbody++) {
				gotoxy(firstx[checkbody], firsty[checkbody]);
				printf("  ");
			}
			
			textcolor(11);
			gotoxy(firstx[0], firsty[0]);
			printf("●");
			
			
			for( checkbody = 1; checkbody <=body ; checkbody++) {
	
				firstx[checkbody]= firstx[checkbody-1] -2;
				firsty[checkbody]= firsty[checkbody-1];
				gotoxy(firstx[checkbody], firsty[checkbody]);
				printf("ㅇ");
			}
			textcolor(7);
		}
		
	}
}

void move() { //뱀 이동 함수 
	
	while (1) { //무한루프  
		
		if (kbhit()) {
			
			loop:
							
			    key = getch(); //키보드 입력을 받음  
		
		        switch (key) {
		
		            case 72: // 방향키 ↑를 입력 받음  
		        	    while (1) { //무한루프  
		        	    
		        	        if (kbhit())  //키보드 입력 확인  
		        		        goto loop; //키보드 입력을 받으면 다시 loop으로 돌아감  
							
		        		
		        		    up(); //이동 함수  
		        		    
		        		    collision(); //충돌 여부 확인  
							
		        		    Score(); //점수 확인  
					    }
					    break;    
			        
			
		            case 75: //방향키 ←를 입력 받음  
			            while (1) {
			            	
			            	if (kbhit()) 
		        		        goto loop;
		        		
		        		    left();
		        		    
		        		    collision();
							
		        		    Score();
		        		}
			            break;
			
		            case 77: //방향키 →를 입력 받음  
			            while (1) {
			            	
			            	if (kbhit()) 
		        		        goto loop;
		        		
		        		    right();
		        		    
		        		    collision();
							
		        		    Score();
		        		}
			            break;
			
		            case 80: //방향키 ↓를 입력 받음  
			            while (1) {
			            	
			            	if (kbhit()) 
		        		        goto loop;
		        		
		        		    down();
		        		    
		        		    collision();
							
		        		    Score();
		        		}
			            break;
			            
			        case 27: // esc 입력시 다음 입력까지 일시정지 
						break; 
			        
			        default:
			    	    break;
		
		        }
		
	    }
	
	}
		
}

void up() { //뱀이 위로 이동하는 함수  
		
	textcolor(11);
		
	Sleep(speed);
	
	int checkbody;
	
	for( checkbody= body; checkbody >=0; checkbody--) { //뱀이 지나간 자리를 지움  
		
		gotoxy(firstx[checkbody], firsty[checkbody]);
		printf("  ");
	}
	
	for (checkbody= body; checkbody >=1; checkbody--) { //뱀의 몸통을 이동시킴  
		
		firstx[checkbody] = firstx[checkbody-1];
		firsty[checkbody] = firsty[checkbody-1];
	}
	
	firsty[0] -= 1; //뱀의 머리 이동 설정  
	
	gotoxy(firstx[0], firsty[0]); //뱀의 머리 print  
	printf("●");
	
	for (checkbody = body; checkbody >=1; checkbody--) { //뱀의 몸통 print  
		
		gotoxy(firstx[checkbody], firsty[checkbody]);
		printf("ㅇ");
	}	
		
}

void left() { //뱀이 왼쪽으로 이동하는 함수  

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
	printf("●");
	
	for (checkbody = body; checkbody >=1; checkbody--) {
		
		gotoxy(firstx[checkbody], firsty[checkbody]);
		printf("ㅇ");
	}
	
}

void right() { //뱀이 오른쪽으로 이동하는 함수  
		
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
	printf("●");
	
	for (checkbody = body; checkbody >=1; checkbody--) {
		
		gotoxy(firstx[checkbody], firsty[checkbody]);
		printf("ㅇ");
	}
	
}

void down() { //뱀이 아래쪽으로 이동하는 함수  
	
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
	printf("●");
	
	for (checkbody = body; checkbody >=1; checkbody--) {
		
		gotoxy(firstx[checkbody], firsty[checkbody]);
		printf("ㅇ");
	}
}

void collision() { //뱀의 충돌 여부 확인 함수  
	
	int check= body;
	
	if ( firstx[0] <= 5 || firstx[0] >= 63 || firsty[0] <= 5 || firsty[0] >= 33 ) { //게임보드 벽과 충돌하는지 확인 
		
		if (life ==1 ) {
			life--;
			Sleep(500);
			game();
		} 
		
		else {			
			gotoxy(23, 17); 
		    textcolor(6);
		    printf("게임이 종료되었습니다.");
		
		    if ( score > r[i].score ) { //사용자 최고 기록 확인  
			
			    r[i].score = score;
		        gotoxy(23, 19);
		        printf("개인 최고 기록: %d", r[i].score);
		    
		        if ( score > bestscore ) { //게임 최고 기록 확인  
		    	
		    	    bestscore = score;
		    	    gotoxy(23, 21);
		    	    textcolor(14);
		    	    printf("게임 최고 기록: %d", bestscore);
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
	
	while ( !(firstx[0]==firstx[check] && firsty[0]==firsty[check]) ) { //뱀의 머리가 몸통과 충돌하는지 확인  
		
		if (check == 1) {
			break;
		}
		else check--;
	}
	
	if ( (firstx[0]==firstx[check] && firsty[0]==firsty[check]) ) { //뱀의 머리가 몸통과 충돌하면 게임 종료  
		
		if (life == 1) {
			
			life--;
			Sleep(500);
			game();
		}
		
		else {
			
			gotoxy(23, 17); 
		    textcolor(6);
		    printf("게임이 종료되었습니다.");
		    
		    if ( score > r[i].score ) {
			
			    r[i].score = score;
		        gotoxy(23, 19);
		        printf("개인 최고 기록: %d", r[i].score);
		    
		        if ( r[i].score > bestscore ) {
		    	
		    	    bestscore = r[i].score;
		    	    gotoxy(23, 21);
		    	    textcolor(14);
		    	    printf("게임 최고 기록: %d", bestscore);
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

void Score() { //점수 증가 함수  
	
	if ( firstx[0]==a && firsty[0]==b ) { //뱀의 머리가 음식과 만났을 때  
		score += 1; //점수 증가  
		
		if (speed > 5) 
			speed -= 5; //속도 증가  
		 
		textcolor(10);
    	gotoxy(5, 3);
	    printf("점수: %d", score);  //점수 print  
	    body++; //뱀의 몸통 추가  
	    food(); //음식 새로 생성  
	    Bestscore();
	}
	textcolor(7);
}

void Bestscore() {

	if ( score == bestscore+1 ) {
		
		textcolor(14);
		gotoxy(70, 15);
		printf("■■■■      ■■■■■    ■■■■■    ■■■■■");
		gotoxy(70, 16);
		printf("■    ■      ■            ■                ■    ");
		gotoxy(70, 17);
		printf("■    ■      ■            ■                ■    ");
		gotoxy(70, 18);
		printf("■■■■■    ■■■■■    ■■■■■        ■    ");
		gotoxy(70, 19);
		printf("■      ■    ■                    ■        ■    ");
		gotoxy(70, 20);
		printf("■      ■    ■                    ■        ■    ");
		gotoxy(70, 21);
		printf("■■■■■    ■■■■■    ■■■■■        ■    ");
		
		gotoxy(70, 23);
		printf("■■■■■    ■■■■■    ■■■■■    ■■■■      ■■■■■");
		gotoxy(70, 24);
		printf("■            ■            ■      ■    ■    ■      ■");
		gotoxy(70, 25);
		printf("■            ■            ■      ■    ■    ■      ■");
		gotoxy(70, 26);
		printf("■■■■■    ■            ■      ■    ■■■■      ■■■■■");
		gotoxy(70, 27);
		printf("        ■    ■            ■      ■    ■    ■      ■");
		gotoxy(70, 28);
		printf("        ■    ■            ■      ■    ■     ■     ■");
		gotoxy(70, 29);
		printf("■■■■■    ■■■■■    ■■■■■    ■      ■    ■■■■■");
		textcolor(7);
	}	
}


void record() //랭킹 함수  
{	
	int i,j,tmp;
	char temp_name[20] = {0,};
	struct ranker tmp_user[MAX_USER] = {0,};	// rank 유저 정보를 담을 구조체 
	
	textcolor(10);
	printf("\n\n\t============ [HISTORY] ============\n\n");
	textcolor(7);
	
	for(i = 0; i < count; i++)
	{
		printf("\t| [%d] Score : %2d\t| Name : %s\n", (i+1), r[i].score, r[i].name);
		tmp_user[i].score = r[i].score;		// rank 유저 정보 복사 
		strncpy(tmp_user[i].name, r[i].name, 20);
	}
	
	// 높은 점수 순으로 정렬 (정렬시 바뀌는 history를 위해 tmp_user에 복사 후 정렬)
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
	printf("\t| [1st] Score : %d\t| Name : %s\n\n", tmp_user[0].score, tmp_user[0].name);	// 정렬된 rank 유저 구조체 배열 0 ~ 2번째까지 출력 
	textcolor(11);
	printf("\t| [2nd] Score : %d\t| Name : %s\n", tmp_user[1].score, tmp_user[1].name); 
	printf("\t| [3rd] Score : %d\t| Name : %s\n", tmp_user[2].score, tmp_user[2].name);
	
	int num;
	textcolor(7);
	printf("\n\n\n메뉴로 돌아가시려면 1, 바로 게임을 시작하시려면 2를 입력해주세요.\n");
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
			printf("\n\n잘못 입력하셨습니다. 메뉴로 돌아갑니다.\n");
			Sleep(1000);
			system("cls");
			menu();
			break;
	}
}

void exitgame() { //게임 나가기 함수  
	
	int num;
	printf("\n정말 게임을 종료하시겠습니까?\n");
	printf("\n종료를 원하시면 1, 다시 메뉴로 돌아가려면 2를 입력해주세요.\n");
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
			printf("\n\n잘못 입력하셨습니다. 메뉴로 돌아갑니다.\n");
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

