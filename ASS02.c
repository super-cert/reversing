#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
typedef struct reply
{
  int reply_useless;
  int deebface;
  int board_index;
  char *reply_content;
  int check;
  void (*free)(char * );
  
  struct board *next_node;
}reply;

typedef struct board
{
  int reply_count;
  struct board *next;
  struct board *prev;
  void (*write_action)(struct board * );
  void (*delete_action)(struct board * );
  struct reply *reply_node;
  int index;
  char *Author;
  char *title;
  char * content;
  int deadbeef;
  int random;

}board;

void exit_8048D57();
int print_logo_sub_8048A15();
void read_table(struct board ** board_pointer);
int write_nextnode(struct board** board_pointer);
void writeboard(struct board** a1);
void init_node(struct board *a1);
void reply_write(struct board *board_pointer);
int selector=0;
int dword_804B090 = 0;
int rr_count;
void read_node(struct board *init_board);
void delete_board(struct board* board_pointer);
void free_node(struct reply *reply_node);
void check_count(struct reply *reply_node);
void remove_node(struct board *board_pointer);
void modify(struct board *board_pointer);
void print_reply(struct board * linked_number);
void read_content_8048C31(struct board** link_head);
//-----------------------------main----------------------------//
int main()
{
         int v0_selected_number; // eax@2

         board *checkboard; // [sp+14h] [bp-Ch]@1 //reply의 처음?
         signed int v3; // [sp+18h] [bp-8h]@1
         signed int v4;
         checkboard=NULL;
         v3 = 31337;
         v4 = 31337;
         
         int dword_804B08C = 0;

         //v1 = &byte_8049152;
         print_logo_sub_8048A15();
        while(1)
        {
          while(1)
          {
           puts("1. Write");
           puts("2. Read");
           puts("3. Exit");
           printf("=>");
           v0_selected_number = getchar();
           const int selector = v0_selected_number;
           if(v0_selected_number !='2') 
                break;
           read_table(&checkboard);
        }
        if(v0_selected_number=='3'){ //exit
                exit_8048D57();}
        if(v0_selected_number =='1') 
        {
                if ( write_nextnode(&checkboard) == 1 )
                  puts("Wrong");
                else
                  writeboard(&checkboard);
        }
        else
        {
          puts("Wrong");
        }
     }
}




int print_logo_sub_8048A15()
{
  printf(" _______________________________\n");
  printf("/==============================/\n");
  printf("|     Onetime Board Console    |\n");
  printf("/------------------------------/\n");
  printf("|          | WELCOME |         |\n");
  printf("|__________|_________|_________|\n");
  printf("|          H  A   C  K         |\n");
  printf("|     DIGITAL FORENSIC 07 DF   |\n");
  printf("|        KIM   JONG   HUN      |\n");
  printf("++++++++++++++++++++++++++++++++\n");
  return sleep(0);
}

void exit_8048D57(){

        puts("Bye Bye~");
        exit(0);
}




int write_nextnode(struct board **board_pointer)
{

  signed int v2; // [sp+8h] [bp-8h]@1
  board *board_node; // [sp+Ch] [bp-4h]@3
  int result;
  
  
  v2 = 0;
  if ( *board_pointer )
  {
    for ( board_node = *board_pointer; board_node->next; board_node = board_node->next )
      ++v2;
    result = v2 > 5;                            // 6개 이상이면 터지나?
  }
  else
  {
    result = 0;
  }
  return result;    
}



void read_node(struct board *init_board)
{
  char *temp_author; // ebx@1
  char *temp_title; // ebx@1
  size_t content_size; // eax@1
  size_t real_size; // eax@1
  char *temp_content; // ebx@1
  char buf; // [sp+2Bh] [bp-271Dh]@1
  char input[10000]; // [sp+2Ch] [bp-271Ch]@1
  int v9; // [sp+273Ch] [bp-Ch]@1

  //v9 = *MK_FP(__GS__, 20);
  //scanf(&unk_8049338, &buf);
  getchar();
  printf("Author : ");
  fgets(init_board->Author, 250, stdin);
  temp_author = init_board->Author;
  temp_author[strlen(temp_author) - 1] = 0;
  
  printf("Title : ");
  fgets(init_board->title, 250, stdin);
  temp_title = init_board->title;
  temp_title[strlen(temp_title) - 1] = 0;
  
  printf("Content : ");
  fgets(input, 8000, stdin); //  allocation
  content_size = strlen(input); //size set
  init_board->content = (char*)malloc(content_size);
  real_size =strlen(input);
  memcpy(init_board->content,input,real_size);
  temp_content = init_board->content;
  temp_content[strlen(temp_content)-1]=0;
  
  //fgets(&input, 8000, stdin);
  
  //init_board->content = (char*)malloc(content_size);
  //real_size = strlen(&input);
  //memcpy(init_board->content, &input, real_size);
  //temp_content = init_board->content;
  //temp_content[strlen(temp_content) - 1] = 0;
  //return *MK_FP(__GS__, 20) ^ v9;
}

void writeboard(struct board **board_pointer)
{
  board *tmp_board_rec; // [sp+14h] [bp-14h]@3
  board *new_board_rec; // [sp+18h] [bp-10h]@1

  new_board_rec = (board*)malloc(0x30);                // v3에 먼가 할당, 48bytes?
                                                // 
  init_node(new_board_rec);     
            // 할당

  if ( *board_pointer )              
  {          // 0이 아니면
   
    (new_board_rec->write_action)(new_board_rec);// 먼가 세팅중
    printf("%d\n",new_board_rec->index);
    printf("%s\n", new_board_rec->Author);
    printf("%s\n", new_board_rec->title);
    //printf("write_ation access\n");
    for ( tmp_board_rec = *board_pointer; tmp_board_rec->next; tmp_board_rec = tmp_board_rec->next )// linked_list 형태
      ;
    
    tmp_board_rec->next = new_board_rec;
    
    new_board_rec->prev = tmp_board_rec;        // 8번째 필드 previous형태
    //printf("*board pointer success\n");
  }
  else
  {
  
    (new_board_rec->write_action)(new_board_rec);// 구조체의 write_action부분에 자기자신을 보내는 것
    *board_pointer= new_board_rec;
    //board_pointer->reply_count;
    //board_pointer->new_board_rec;
    
  }
  reply_write(new_board_rec);    // 구조체를 보내는건가?
}

void delete_board(struct board* board_pointer)
{
  
  reply* reply_node; // [sp+14h] [bp-14h]@1
  signed int i; // [sp+18h] [bp-10h]@1

  reply_node = board_pointer->reply_node;
  //reply_node = *board_pointer->reply_node;
  for ( i = 0; i <= 1; ++i )
  {
    if ( reply_node->free != free_node )     // free시도
    {	
    	//reply_node->signature != free_node()
      puts("Detected");
      exit(1);
    }
    //reply_node = reply_node->next_node;
    reply_node->next_node;
  }
  while ( reply_node->next_node )
  {
   (reply_node->free)(reply_node->reply_content);
    //reply_node = reply_node->next_node;
    reply_node=reply_node->next_node;
  }
  free(board_pointer->Author);
  free(board_pointer->title);
  free(board_pointer->content);
  free(board_pointer);
  
}
void init_node(struct board *newrec) //구조체 안에 값을 참조 //void가 맞을까?
{
  
  ++dword_804B090;                              // 값을 세팅중
  newrec->reply_count = NULL;
  newrec->next = NULL;
  newrec->prev = NULL;
  newrec->write_action = read_node;           // author, content, title 을 할당받는 곳
  newrec->delete_action = delete_board;
  newrec->reply_node = NULL;
  newrec->index = dword_804B090;                    // 인덱스네
  newrec->Author = (char*)malloc(0x100);
  newrec->title = (char*)malloc(0x100);
  newrec->random = rand();
  //result = a1;
  newrec->deadbeef = 0xDEADBEEF;

}

void reply_write(struct board *board_pointer)
  {
  //board *result; // eax@7
  reply *temp_node; // [sp+10h] [bp-18h]@3
  reply *new_reply_node; // [sp+14h] [bp-14h]@1
  char *dest; // [sp+18h] [bp-10h]@1

  
  new_reply_node = (reply*)malloc(0x1C);               // 왠지 구조체느낌. dest로부터 값을 할당받음
  dest = (char*)malloc(0x78);
  new_reply_node->board_index = board_pointer->index;// index
  new_reply_node->deebface = 0xDEEBFACE;        // ? 넌뭐냐
  new_reply_node->next_node = NULL;
  if ( board_pointer->reply_node )                // reply
  {
  	//reply_node = board_pointer->reply_node;
    for ( temp_node = board_pointer->reply_node; temp_node->next_node; temp_node = temp_node->next_node )// 댓글의 인덱스가 있는지 확인
      ;
    temp_node->next_node = new_reply_node;      // 댓글넣기?
    printf("\t\tReply : ");
    getchar();
    fgets(dest, 100, stdin);                    // char값에 내가 입력한 값을 넣고
    dest[strlen(dest) - 1] = 0;                 // 값을 넣는작업 아 마지막에 \0처린가?
    new_reply_node->reply_content = dest;       // reply 값
  }
  else
  {
    
    board_pointer->reply_node = new_reply_node;
    memcpy(dest, "Welcome, It's Auto reply system", 0x64);
    new_reply_node->reply_content = dest;
  }
  //result = a1_receivvd;
  
  rr_count++;
  board_pointer->reply_count=rr_count;
  

}


void read_table(struct board ** board_pointer) //인자로 들어오는 것에 형태 : 구조체 포인터
{
  // eax@2
  board* read_node; // [sp+1Ch] [bp-Ch]@1

  read_node = *board_pointer; //구조체안에 있는ㄱ ㅜ조체
  system("/usr/bin/clear");                     // 화면을 깨끗히
  if ( read_node )                                     // 값이 있다면 출력을 하겠죠?
  {
    printf("\t| %s| %-20s | %-20s \n", "number", "author", "title");
    while ( read_node )
    {
      puts("\t-----------------------------------------------");
      printf("\t| %5d | %-20s | %-20s \n", read_node->index, read_node->Author, read_node->title);// number, author, title +4 +4 +4
      puts("\t-----------------------------------------------");
      read_node = read_node->next;                            // 4칸씩 이동한 주소에 본인이있다, while 문에서 본인을 다 출려하고 그 다음에 read_content부분에서 댓글함수로 넘어감
    }
    read_content_8048C31(board_pointer);
    
  }
  else
  {
    puts("Wrong");                     // 값이 업으니 wrong뜨고 메인으로
  }
  
}

void read_content_8048C31(struct board** link_head)
{
   // eax@1 결과값 eax값은 보통 바깥으로 나가는용
  board *board_node; // [sp+14h] [bp-14h]@1 지역변수 i
  reply *reply_node; // [sp+18h] [bp-10h]@3 지역변수 v3
  signed int check; // [sp+1Ch] [bp-Ch]@1f

  check = 0;
  printf("\tNumber : ");
  scanf("%d", &selector);       // 값을 입력받으면 그 넘버가 인덱스가 된다
  
  for ( board_node = *link_head; board_node; board_node = board_node->next )// 첫위치어 시작해서 4바이트씩 이동해서 값이 없을때까지 반복
  {
    if ( board_node->index == selector )// 인덱스에 맞는 숫자를 입력하는 경우 최대는 0,4,8,12,16,20 6개?
    {
      reply_node = board_node->reply_node;     // index가 있는가?
      puts("\t\t===================================");
      printf("\t\t|| %d || %-20s || %-20s \n", board_node->index, board_node->Author, board_node->title);// i+ 24 : 인덱스, i+ 28 : author, i+32 : title
      puts("\t\t===================================");
      printf("\t\t|content | %s\n", board_node->content);// +36은 컨텐츠
      puts("\t\t===================================");
      check = 1;                                // 값이 있으면 1이 되나본데
      while ( reply_node )                      // 링크드 포인터 위치 + 20
      {
        printf(reply_node);
        puts("\t\t\t|");
        printf("\t\t\t|====> %s\n", reply_node->reply_content);// reply에 3번째 매체 (reply content)

        reply_node = reply_node->next_node;     // 첫 댓글 넘버인가?
        
      }
      
      print_reply(board_node);               // 각 링크에 대핸 reply 호출
    }
    
    board_node->next;
    
  }
  
  if ( !check )
    puts("Wrong");
  
}
void print_reply(struct board * linked_number)
{ // eax@14
  
  selector = 0;                 // 0으로 변환
  while ( 1 )
  {
    //result = selector;          // ?
    if ( selector == 4 )        // 4번 back 리턴
      break;
    printf("\n\t\t1. delete  2. modify  3. reply  4. back\n\t\t=> ");
    scanf("%d", &selector);

    switch(selector)
    {
      case 1:
        remove_node(linked_number);            // 삭제과정
        break;
      case 2:
        modify(linked_number);
        break;
      case 3:
        reply_write(linked_number);
        break;
      case 4:
        system("/usr/bin/clear");
      default:
        puts("wrong!\n");

    }
  }
}
void remove_node(struct board *board_pointer)
{
  //int result; // eax@2
  reply *remove_node; // [sp+18h] [bp-10h]@4

  if ( ( board_pointer->reply_count ) <=0 )
  {
    
    board_pointer->prev->next = board_pointer->next;// 링크드리스드 지우는 과정인듯?
    board_pointer->next->prev = board_pointer->prev;// a1의 값이 0보다 작은 경우
    if ( board_pointer->deadbeef == 0xDEADBEEF )// 쓰레기값으로 제대로 값이 빠졌는디 확인
    {
      for ( remove_node = board_pointer->reply_node; remove_node->next_node; remove_node = remove_node->next_node )
      {
        //check_count(remove_node->check);
        //free_node(remove_node->signature);
        remove_node->check = (int)check_count;
        remove_node->free = (char*)free_node;
      }
    }
    (board_pointer->delete_action)(board_pointer);
  }
  else
  {
    puts("Cannot Deleted. There's at least one or more replies on it");
  }
  
}

void check_count(reply *reply_node)
{
  //reply *result; // eax@1

  reply_node->reply_useless = 0;
  //result = reply_node;
  reply_node->deebface = 0xBABEFACE;
  //return result;
}

void free_node(reply *reply_node)
{
  
  free(reply_node);
}

void modify(board *board_pointer)
{
  char* v1; // ebx@1
  char* v2; // ebx@1
  // eax@1

  memset(board_pointer->Author, 0, 0xFA);      // author 변경
  memset(board_pointer->title, 0, 0xFA);       // title 변경
  //scanf("%s", &selector);// &unk_8049338은 캐스팅 선언/
  getchar();
  printf("Author : ");
  fgets(board_pointer->Author, 250, stdin);     // author 최대 길이는 250까지 변경가능, 타이핑하는곳
  v1 = board_pointer->Author;                   // 그 값을 v1 지역변수에 저장
  *(v1 + strlen(board_pointer->Author) - 1) = 0;// 값을 할당하는 건가?
  printf("Title : ");
  fgets(board_pointer->title, 250, stdin);      // 새로운 title값을 입력받는다
  v2 = board_pointer->title;
  *(v2 + strlen(board_pointer->title) - 1) = 0; // title값 변경
                       // a1이 구조체인듯 하다
  board_pointer->deadbeef = 0xC0DEACBE;         // 멀까
  
}

