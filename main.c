#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <ctype.h>
#include <time.h>
int time_ref;
int scores[1000];
int ranknum[1000] = {0};
char names[100][100];
int rank_counter = -1;
int board[50][50] = {0};
int lines[100][10];
int boxes[50][5];
int boxes_state[30][30] = {0}; //grid*2+1
int getline[30][30] = {0};
int checker[30][30] = {0};
int board_color_info[50][50] = {0};
int undo[1000][2];
int redo [1000][2];
int undo_count = 0;
int redo_count = 0;
int game_mode = 0;
int board_row;
int board_col;
int grid_size = 0;
int lines_number;
int limit;
int turn = 2;
int boxes_number;
char entry[4];
typedef struct{
    int hours;
    int minutes;
    int seconds;
}timer;
struct player_info{
    char user_name[10];
    int score;
    int moves;
    int color; //1 for blue, 2 for red
}player1,player2;
int play_computer();
void print_time(timer x);
timer split_time(int total_seconds);
void print_logo();
void All_set();
void print_main_menu();
void print_game_mode();
void print_header();
void print_board();
void draw_line(int ,int);
int  play_game();
void undo_move();
void getrank();
void saverank(char[]);
void savename_score(char[], int);
void print_top10();
int search_rank(char[]);
int checkhighscore(char[], int playerscore);
void sort_scores();
void loadscores_from(char[]);
void lowercase(char[]);
void save(char[]);
void load(char[]);
void redo_move();
void reset();
int main(){
    system("color F0");
    char menu_choice[30];
    //------------------------------------------------------------------
    main_menu_start:
    printf("\n\n\n\n\n");
    print_logo();
    print_main_menu();
    rank_counter = -1;
    scanf("%s", &menu_choice);
    fflush(stdin);
    if(strcmp("1", menu_choice)==0){//new game
        char game_mode_choice[20];
        system("cls");
        game_mode_start:
        print_game_mode();
        scanf("%s", &game_mode_choice);
        fflush(stdin);

        if(strcmp("1", game_mode_choice)==0){//human vs human
                game_mode = 1; //human vs human code
                system("cls");
                printf("\n\n\n\n\n\n\n");
                printf("\n\t\t\t\t\t        Enter your user name\n");
                printf("\t\t\t\t\t\tplayer(1)%c%c ", 175,175);
                scanf("%s", &player1.user_name);
                fflush(stdin);
                lowercase(player1.user_name);
                player1.color = 1;//blue
                player1.score = 0;
                printf("\n\t\t\t\t\t        Enter your user name\n");
                printf("\t\t\t\t\t\tplayer(2)%c%c ", 175,175);
                scanf("%s", &player2.user_name);
                fflush(stdin);
                lowercase(player2.user_name);
                player2.color = 2;//red
                player2.score = 0;
                system("cls");
                char size_choice[3];
                grid_size_choice:
                printf("\n\n\n\n\n\n\n");
                printf("\t\t\t\t\t\t      GRID SIZE\n");
                printf("\t\t\t\t\t\t     ");
                for(int i = 0; i < 11; i++){
                    printf("%c", 205);
                }
                printf("\n\t\t\t\t\t\t 1) Beginner (2 x 2)");
                printf("\n\t\t\t\t\t\t 2) Expert   (5 x 5)");
                printf("\n\n\t\t\t\t       Enter the number associated with your choice\n");
                printf("\t\t\t\t\t\t         %c%c ", 175,175);
                scanf("%s", &size_choice);
                fflush(stdin);
                if(strcmp("1", size_choice) == 0){ // 2*2
                    lines_number = 12;
                    limit = 12;
                    grid_size = 2;
                    board_row = 8;
                    board_col = 16;
                    system("cls");
                    time_ref = clock()/CLOCKS_PER_SEC;
                    reset();
                    print_header();
                    all_set();
                    print_board();
                    int todo = play_game();
                    if (todo == 1){
                        system("cls");
                        goto main_menu_start;
                    }else if(todo == 2){
                        return 0;
                    }
                }else if(strcmp("2", size_choice) == 0){ // 5*5
                    lines_number = 60;
                    limit = 60;
                    grid_size = 5;
                    board_row = 20;
                    board_col = 40;
                    system("cls");
                    time_ref = clock()/CLOCKS_PER_SEC;
                    reset();
                    print_header();
                    all_set();
                    print_board();
                    int todo = play_game();
                    if (todo == 1){
                        system("cls");
                        goto main_menu_start;
                    }else if(todo == 2){
                        return 0;
                    }
                }else{
                    printf("\t\t\t\t\t\tINVALID INPUT!");
                    Sleep(600);
                    system("cls");
                    goto grid_size_choice;
                }
        }else if(strcmp("2", game_mode_choice)==0){ //human vs computer
                game_mode = 2; //human vs computer code
                system("cls");
                printf("\n\n\n\n\n\n\n");
                printf("\n\t\t\t\t\t        Enter your user name\n");
                printf("\t\t\t\t\t\tplayer%c%c ", 175,175);
                scanf("%s", &player1.user_name);
                fflush(stdin);
                lowercase(player1.user_name); // check////////////////////////////////
                char comp[] = "computer";
                strcpy(player2.user_name, comp);
                player1.score = 0;
                player2.score = 0;
                player1.color = 1;
                player2.color = 2;
                char size_choice[3];
                system("cls");
                grid_size_choice_comp:
                printf("\n\n\n\n\n\n\n");
                printf("\t\t\t\t\t\t      GRID SIZE\n");
                printf("\t\t\t\t\t\t     ");
                for(int i = 0; i < 11; i++){
                    printf("%c", 205);
                }
                printf("\n\t\t\t\t\t\t 1) Beginner (2 x 2)");
                printf("\n\t\t\t\t\t\t 2) Expert   (5 x 5)");
                printf("\n\n\t\t\t\t       Enter the number associated with your choice\n");
                printf("\t\t\t\t\t\t         %c%c ", 175,175);
                scanf("%s", &size_choice);
                fflush(stdin);
                if(strcmp("1", size_choice) == 0){ // 2*2
                    lines_number = 12;
                    limit = 12;
                    grid_size = 2;
                    board_row = 8;
                    board_col = 16;
                    system("cls");
                    time_ref = clock()/CLOCKS_PER_SEC;
                    reset();
                    print_header();
                    all_set();
                    print_board();
                    int todo = play_computer();
                    if (todo == 1){
                        system("cls");
                        goto main_menu_start;
                    }else if(todo == 2){
                        return 0;
                    }
                }else if(strcmp("2", size_choice) == 0){ //5*5
                    lines_number = 60;
                    limit = 60;
                    grid_size = 5;
                    board_row = 20;
                    board_col = 40;
                    system("cls");
                    time_ref = clock()/CLOCKS_PER_SEC;
                    reset();
                    print_header();
                    all_set();
                    print_board();
                    int todo = play_computer();
                    if (todo == 1){
                        system("cls");
                        goto main_menu_start;
                    }else if(todo == 2){
                        return 0;
                    }
                }else{
                    printf("\t\t\t\t\t\tINVALID INPUT!");
                    Sleep(600);
                    system("cls");
                    goto grid_size_choice_comp;
                }
        }else if(strcmp("3", game_mode_choice)==0){
            system("cls");
            goto main_menu_start;
        }else{
            printf("\t\t\t\t\t\tINVALID INPUT!");
            Sleep(600);
            system("cls");
            goto game_mode_start;
        }
    }else if(strcmp("2", menu_choice)==0){//load
            int loadchoice;
            system("cls");
            printf("\n\n");
            print_logo();
            printf("n\t\t\t\t\tchoose a load file or cancel:\n");
            printf("\n\t\t\t\t\t\t1. save1");
            printf("\n\t\t\t\t\t\t2. save2");
            printf("\n\t\t\t\t\t\t3. save3");
            printf("\n\t\t\t\t\t\t4. cancel");
            printf("\n\t\t\t\t\tEnter the number associated with your choice: ");
            do{
                fgets(entry, 4, stdin);
            }while(!(loadchoice=atoi(entry)));
            load_menu:
            switch(loadchoice){
            case 1:
                load("save1.txt");
                system("cls");
                if(game_mode == 1){
                    time_ref = clock()/CLOCKS_PER_SEC;
                    print_header();
                    print_board();
                    int todo = play_game();
                    if (todo == 1){
                        system("cls");
                        goto main_menu_start;
                    }else if(todo == 2){
                        return 0;
                    }
                }
                else if(game_mode == 2){
                    time_ref = clock()/CLOCKS_PER_SEC;
                    print_header();
                    print_board();
                    int todo = play_computer();
                    if (todo == 1){
                        system("cls");
                        goto main_menu_start;
                    }else if(todo == 2){
                        return 0;
                    }
                }
                break;
            case 2:
                load("save2.txt");
                system("cls");
                if(game_mode == 1){
                    time_ref = clock()/CLOCKS_PER_SEC;
                    print_header();
                    print_board();
                    int todo = play_game();
                    if (todo == 1){
                        system("cls");
                        goto main_menu_start;
                    }else if(todo == 2){
                        return 0;
                    }
                }
                else if(game_mode == 2){
                    time_ref = clock()/CLOCKS_PER_SEC;
                    print_header();
                    print_board();
                    int todo = play_computer();
                    if (todo == 1){
                        system("cls");
                        goto main_menu_start;
                    }else if(todo == 2){
                        return 0;
                    }
                }
                break;
            case 3:
                load("save3.txt");
                system("cls");
                if(game_mode == 1){
                    time_ref = clock()/CLOCKS_PER_SEC;
                    print_header();
                    print_board();
                    int todo = play_game();
                    if (todo == 1){
                        system("cls");
                        goto main_menu_start;
                    }else if(todo == 2){
                        return 0;
                    }
                }
                else if(game_mode == 2){
                    time_ref = clock()/CLOCKS_PER_SEC;
                    print_header();
                    print_board();
                   int todo = play_computer();
                    if (todo == 1){
                        system("cls");
                        goto main_menu_start;
                    }else if(todo == 2){
                        return 0;
                    }
                }
                break;
            case 4:
                system("cls");
                goto main_menu_start;
                break;
            default:
                printf("\n\t\t\t\t\tEnter valid savefile! ");
                scanf("%d", &loadchoice);
                goto load_menu;
            }
    }else if(strcmp("3", menu_choice)==0){
        system("cls");
        loadscores_from("users.txt");
        sort_scores();
        getrank();
        print_top10();
        rank_counter = -1;
        char exit[1];
        printf("\t\t\t\t\tPress any key to return to main menu");
        scanf("%c", &exit);
        system("cls");
        goto main_menu_start;
    }else if(strcmp("4", menu_choice)==0){
        return 0;
    }else{
        printf("\t\t\t\t\t\tINVALID INPUT!");
        Sleep(600);
        system("cls");
        goto main_menu_start;
    }
    saverank("users.txt");
    return 0;
}
void print_logo(){
    int i;
    printf("\t\t\t\t\t       %c", 201);
    for(i = 0; i < 14; i++){
        printf("%c", 205);
    }
    printf("%c", 187);
    printf("\n\t\t\t\t\t       %c", 186);
    printf("DOTS AND BOXES");
    printf("%c", 186);
    printf("\n\t\t\t\t\t       %c", 200);
    for(i = 0; i < 14; i++){
        printf("%c", 205);
    }
    printf("%c\n\n", 188);
}
void print_main_menu(){
    int i;
    printf("\t\t\t\t\t\t     %s", "MENU");
    printf("\n\t\t\t\t\t            ");
    for(i = 0; i < 6; i++){
        printf("%c", 205);
    }
    printf("\n\t\t\t\t\t\t 1) NEW GAME");
    printf("\n\t\t\t\t\t\t 2) LOAD GAME");
    printf("\n\t\t\t\t\t\t 3) TOP TEN");
    printf("\n\t\t\t\t\t\t 4) EXIT");
    printf("\n\n\t\t\t\t Enter the number associated with your choice\n");
    printf("\t\t\t\t\t\t   %c%c ", 175,175);
}
void print_game_mode(){
    int i;
    printf("\n\n\n\n\n\n\n");
    printf("\t\t\t\t\t\t      GAME MODE\n");
    printf("\t\t\t\t\t\t     ");
    for(i = 0; i < 11; i++){
        printf("%c", 205);
    }
    printf("\n\t\t\t\t\t\t 1) Human vs. Human");
    printf("\n\t\t\t\t\t\t 2) Human vs. Computer");
    printf("\n\t\t\t\t\t\t 3) Go back to Main Menu");
    printf("\n\n\t\t\t\t       Enter the number associated with your choice\n");
    printf("\t\t\t\t\t\t         %c%c ", 175,175);
}
void print_header(){
    HANDLE hConSole=GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    GetConsoleScreenBufferInfo(hConSole,&consoleInfo);
    WORD saved_attributes =consoleInfo.wAttributes;
    printf("\n");
    print_logo();
    if(game_mode == 1){//human vs human
        printf("\t\t\t\t\t PLAYER 1 \t\t\t PLAYER 2");
        printf("\n\t\t\t NAME ");
        SetConsoleTextAttribute(hConSole,244);
        printf("\t\t %s", player1.user_name);
        SetConsoleTextAttribute(hConSole,saved_attributes);
        SetConsoleTextAttribute(hConSole,241);
        printf("\t\t\t\t %s", player2.user_name);
        SetConsoleTextAttribute(hConSole,saved_attributes);
        printf("\n\t\t\t SCORE ");
        SetConsoleTextAttribute(hConSole,244);
        printf("\t\t    %d", player1.score);
        SetConsoleTextAttribute(hConSole,saved_attributes);
        SetConsoleTextAttribute(hConSole,241);
        printf("\t\t\t\t     %d", player2.score);
        SetConsoleTextAttribute(hConSole,saved_attributes);
        printf("\n\t\t\t MOVES");
        SetConsoleTextAttribute(hConSole,244);
        printf("\t\t    %d", player1.moves);
        SetConsoleTextAttribute(hConSole,saved_attributes);
        SetConsoleTextAttribute(hConSole,241);
        printf("\t\t\t\t     %d", player2.moves);
        SetConsoleTextAttribute(hConSole,saved_attributes);
        printf("\n\t\t\t\t\t\t REMAINING LINES: ");
        SetConsoleTextAttribute(hConSole, 242);
        printf("%d", lines_number);
        SetConsoleTextAttribute(hConSole, saved_attributes);
        printf("\n");
    }else if(game_mode == 2){
        printf("\t\t\t\t\t PLAYER 1 \t\t\t PLAYER 2");
        printf("\n\t\t\t NAME ");
        SetConsoleTextAttribute(hConSole,244);
        printf("\t\t %s", player1.user_name);
        SetConsoleTextAttribute(hConSole,saved_attributes);
        SetConsoleTextAttribute(hConSole,241);
        printf("\t\t\t\t %s",player2.user_name);
        SetConsoleTextAttribute(hConSole,saved_attributes);
        printf("\n\t\t\t SCORE ");
        SetConsoleTextAttribute(hConSole,244);
        printf("\t\t    %d", player1.score);
        SetConsoleTextAttribute(hConSole,saved_attributes);
        SetConsoleTextAttribute(hConSole,241);
        printf("\t\t\t\t     %d", player2.score);
        SetConsoleTextAttribute(hConSole,saved_attributes);
        printf("\n\t\t\t MOVES");
        SetConsoleTextAttribute(hConSole,244);
        printf("\t\t    %d", player1.moves);
        SetConsoleTextAttribute(hConSole,saved_attributes);
        SetConsoleTextAttribute(hConSole,241);
        printf("\t\t\t\t     %d", player2.moves);
        SetConsoleTextAttribute(hConSole,saved_attributes);
        printf("\n\t\t\t\t\t\t REMAINING LINES: ");
        SetConsoleTextAttribute(hConSole, 242);
        printf("%d", lines_number);
        SetConsoleTextAttribute(hConSole, saved_attributes);
        printf("\n");
    }

    print_time(split_time((clock()/CLOCKS_PER_SEC)-time_ref));
}
void all_set(){
    int count = 1;
    //set main points
    for(int e = 0; e <= board_row; e+=4){
        for(int f = 0; f <= board_col; f+=8){
            board[e][f] = 254;
        }
    }
    //set the lines array
    int initial_count = -4;
    int a = 0;//check////
    int rowst = 0;
    int colst = 1;
    for(int i = 0; i <= board_row; i+=4){
            colst = 1;
        for(int j = 4; j <= board_col; j+=8){
            int temp = j+1;
            if(count > 9){
                board[i][j] = count/10;
                board_color_info[i][j] = 3;
                board[i][temp] = count%10;
                board_color_info[i][temp] = 3;
            }else{
                board[i][j] = count;
                board_color_info[i][j] = 3;
            }
            lines[a][0] = count; //line number
            lines[a][1] = 0; //line status
            lines[a][2] = 1; //horizontal
            lines[a][3] = i; //starting row
            lines[a][4] = j-3; // starting column
            lines[a][5] = i; // ending row
            lines[a][6] = j+3; //ending col
            lines[a][7] = rowst; //associated cell row in the boxes state array
            lines[a][8] = colst; //associated cell col in the boxes state array
            count++;
            a++;
            colst+=2;
        }
        rowst+=2;
    }
    initial_count = -2;
    //count = 0;
    rowst = 1;
    colst = 0;
    for(int k = 2; k <= board_row; k+=4){
        colst  = 0;
        for(int g = 0; g <= board_col; g+=8){
            int temp = g+1;
            int division = count% 10;
            if(count > 9){
                board[k][g] = count/10;
                board_color_info[k][g] = 3;
                board[k][temp] = division;
                board_color_info[k][temp] = 3;
            }else{
                board[k][g] = count;
                board_color_info[k][g] = 3;
            }
            lines[a][0] = count;
            lines[a][1] = 0;
            lines[a][2] = 2; //vertical line
            lines[a][3] = k-1;
            lines[a][4] = g;
            lines[a][5] = k+1;
            lines[a][6] = g;
            lines[a][7] = rowst;
            lines[a][8] = colst;
            count ++;
            a++;
            colst+=2;
        }
        rowst+=2;
    }
    lines_number = a;
    //set the boxes array
    int boxes_count = 1;
    int b = 0;
    int col = 1, row = 1;
    for(int c = 1; c <= board_row; c+=4){
        for(int d = 1; d <= board_col; d+=8){
            boxes[b][0] = boxes_count; // box number
            boxes[b][1] = c; //start row corner
            boxes[b][2] = d; // start col corner
            boxes[b][3] = row; // row position in boxes state array
            boxes[b][4] = col; // column position in boxes state array
            boxes[b][5] = 0; // color;
            boxes_count++;
            b++;
            col+=2;
        }
        row+=2;
    }
    boxes_number = boxes_count;
    //set the boxes state array
    for(int x = 0; x < grid_size*2+1; x++){
        for(int y = 0; y < grid_size*2+1; y++){
            boxes_state[x][y] = 0;
            checker[x][y] = 0;
        }
    }
    int complinecount = 1;
    for(int x = 0; x < grid_size*2+1; x+=2){
        for(int y = 1; y < grid_size*2+1; y+=2){
            getline[x][y] = complinecount;
            complinecount++;
        }
    }
    for(int x = 1; x < grid_size*2+1; x+=2){
        for(int y = 0; y < grid_size*2+1; y+=2){
            getline[x][y] = complinecount;
            complinecount++;
        }
    }
}
void draw_line(int line_num, int color){ // 1 for blue and 2 for red
    for(int i = 0;i <limit; i++){
        if(lines[i][0] == line_num){
            lines[i][9] = color;
            lines[i][1] = 1;
            lines_number --;// check/////
            boxes_state[lines[i][7]][lines[i][8]] = 1;
            if(game_mode == 2){checker[lines[i][7]][lines[i][8]] = 1;}
            if(lines[i][2] == 1){ // horizontal line
                for(int n = lines[i][3]; n <=lines[i][5]; n++){
                    for(int m = lines[i][4]; m <= lines[i][6]; m++){
                        board[n][m] = 254;
                        board_color_info[n][m] = color;
                    }
                }
            }else if(lines[i][2] == 2){ // vertical line
                int Extra_cell;
                Extra_cell = (lines[i][3]+lines[i][5])/2;
                board_color_info[Extra_cell][lines[i][4]+1] = 0;//
                for(int k = lines[i][3]; k <=lines[i][5]; k++){
                    for(int g = lines[i][4]; g <= lines[i][6]; g++){
                        board[k][g] = 219;
                        board_color_info[k][g] = color;
                    }
                }
            }
            break;
        }
    }
}
int check_boxes(int color){// 1 for blue and 2 for red
    int to_get_point = 0;
    int box_num = 1;
    for(int i = 1; i < grid_size*2+1; i+=2){
        for(int j = 1; j < grid_size*2+1; j+=2){
            if(boxes_state[i][j] == 0){
                if(boxes_state[i][j-1] == 1 && boxes_state[i][j+1] == 1 && boxes_state[i-1][j] == 1 && boxes_state[i+1][j] == 1){
                    to_get_point++;
                    boxes_state[i][j] = 1;
                    for(int n = boxes[box_num-1][1]; n <= (boxes[box_num-1][1]+2); n++){
                        for(int m = boxes[box_num-1][2]; m <= (boxes[box_num-1][2]+6); m++){
                            board[n][m] = 219;
                            board_color_info[n][m] = color;
                        }
                    }
                    boxes[box_num-1][5] = color;
                }
            }
            box_num ++;
        }
    }
    return to_get_point;
}
void print_board(){
    HANDLE hConSole=GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    GetConsoleScreenBufferInfo(hConSole,&consoleInfo);
    WORD saved_attributes =consoleInfo.wAttributes;
    printf("\n\n\n");
    for(int a = 0; a <= board_row+1; a++){
        printf("\t\t\t\t\t\t");
        for(int b = 0; b <= board_col+1; b++){
            if(board[a][b] == 254 && board_color_info[a][b] == 1){
                SetConsoleTextAttribute(hConSole,244);
                printf("%c", board[a][b]);
                SetConsoleTextAttribute(hConSole,saved_attributes);
            }
            else if(board[a][b] == 254 && board_color_info[a][b] == 2){
                SetConsoleTextAttribute(hConSole, 241);
                printf("%c", board[a][b]);
                SetConsoleTextAttribute(hConSole,saved_attributes);
            }
            else if(board[a][b] == 254 && board_color_info[a][b] == 0){
                printf("%c", board[a][b]);
            }
            else if(board[a][b] == 219 && board_color_info[a][b] == 1){
                SetConsoleTextAttribute(hConSole,244);
                printf("%c", board[a][b]);
                SetConsoleTextAttribute(hConSole,saved_attributes);
            }
            else if(board[a][b] == 219 && board_color_info[a][b] == 2){
                SetConsoleTextAttribute(hConSole,241);
                printf("%c", board[a][b]);
                SetConsoleTextAttribute(hConSole,saved_attributes);
            }else if(board[a][b] == 0 && board_color_info[a][b] == 3){
                SetConsoleTextAttribute(hConSole,242);
                printf("%d", board[a][b]);
                SetConsoleTextAttribute(hConSole,saved_attributes);
            }else if(board[a][b] != 0 && board_color_info[a][b] == 0){
                printf("%c", 0     );
            }
            else if(board[a][b] == 0){
                printf("%c", board[a][b]);
            }
            else{
                SetConsoleTextAttribute(hConSole,242);
                printf("%d", board[a][b]);
                SetConsoleTextAttribute(hConSole,saved_attributes);
            }
        }
        printf("\n");
    }
    printf("\t\t\t\tFor Undo press(-1)\tFor Redo press(-2)\n\t\t\t\tTo Save press(-3)\tTo Go to main menu press(-4)\n\t\t\t\t\t   To Exit press(-5)\n");
}

int play_game(){
    HANDLE hConSole=GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    GetConsoleScreenBufferInfo(hConSole,&consoleInfo);
    WORD saved_attributes =consoleInfo.wAttributes;
    int check_score;
    int start = grid_size;
    int line_num;
    while(lines_number != 0){
        game_turn:
        if(turn % 2 == 0){// player1 turn
            SetConsoleTextAttribute(hConSole, 244);
            printf("\tEnter the line number\n\t");
            SetConsoleTextAttribute(hConSole, saved_attributes);
            do{
                fgets(entry, 4, stdin);
            }while(!(line_num=atoi(entry)));
            fflush(stdin);
            if(line_num == -1){//undo
                if(undo_count  !=0){
                    undo_move();
                    system("cls");
                    print_header();
                    print_board();
                }else{
                    printf("\t\t\t\t\tINVALID UNDO");
                    Sleep(600);
                    system("cls");
                    print_header();
                    print_board();
                    goto game_turn;
                }
            }
            else if(line_num == -2){
                if(redo_count  !=0){
                    redo_move();
                    system("cls");
                    print_header();
                    print_board();
                }else{
                    printf("\t\t\t\t\tINVALID REDO");
                    Sleep(600);
                    system("cls");
                    print_header();
                    print_board();
                    goto game_turn;
                }
            }
            else if(line_num == -3){
                int savechoice;
                system("cls");
                print_header();
                print_board();
                printf("\n\n\t\t\t\t\tchoose a save file or cancel:\n");
                printf("\n\t\t\t\t\t\t1. save1");
                printf("\n\t\t\t\t\t\t2. save2");
                printf("\n\t\t\t\t\t\t3. save3");
                printf("\n\t\t\t\t\t\t4. cancel");
                printf("\n\t\t\t\t\tEnter the number associated with your choice: ");
                do{
                    fgets(entry, 4, stdin);
                }while(!(savechoice = atoi(entry)));
                save_menu:
                switch(savechoice){
                case 1:
                    save("save1.txt");
                    return 1;
                    break;
                case 2:
                    save("save2.txt");
                    return 1;
                    break;
                case 3:
                    save("save3.txt");
                    return 1;
                    break;
                case 4:
                    goto game_turn;
                default:
                    printf("\n\t\t\t\t\tEnter valid save file! ");
                do{
                    fgets(entry, 4, stdin);
                }while(!(savechoice = atoi(entry)));
                    goto save_menu;
                }
                return 0;
            }
            else if(line_num == -4){
                return 1;
            }
            else if(line_num == -5){
                return 2;
            }
            else if(line_num <= limit && line_num >0){
                if(lines[line_num -1][1] == 0){
                    undo[undo_count][0] = line_num;
                    undo[undo_count][1] = 1;
                    undo_count++;
                    redo_count = 0;//check1

                    draw_line(line_num, player1.color);
                    player1.moves ++;
                    check_score = check_boxes(player1.color);
                    if(check_score == 1){
                        player1.score ++;
                    }else if(check_score == 2){
                        player1.score += 2;
                    }
                    else{
                        turn++;
                    }
                    system("cls");
                    print_header();
                    print_board();
                }else{
                    printf("\t\t\t\t\tINVALID LINE INPUT");
                    Sleep(600);
                    system("cls");
                    print_header();
                    print_board();
                    goto game_turn;
                }
            }else{
                    printf("\t\t\t\t\tINVALID LINE INPUT");
                    Sleep(600);
                    system("cls");
                    print_header();
                    print_board();
                    goto game_turn;
            }
        }
        else if(turn % 2 != 0){
            SetConsoleTextAttribute(hConSole, 241);
            printf("\t\t\t\t\t\t\t\tEnter the line number\n");
            SetConsoleTextAttribute(hConSole, saved_attributes);
            printf("\t\t\t\t\t\t\t\t");
            do{
                fgets(entry, 4, stdin);
            }while(!(line_num = atoi(entry)));
            fflush(stdin);
            if(line_num == -1){
                if(undo_count  !=1){
                    undo_move();
                    turn ++;
                    system("cls");
                    print_header();
                    print_board();
                }else{
                    printf("\t\t\t\t\tINVALID UNDO");
                    Sleep(600);
                    system("cls");
                    print_header();
                    print_board();
                    goto game_turn;
                }
                //previous_turn = 1;
            }
            else if(line_num == -2){
                if(redo_count  !=0){
                    redo_move();
                    turn ++;
                    system("cls");
                    print_header();
                    print_board();
                }else{
                    printf("\t\t\t\t\tINVALID REDO");
                    Sleep(600);
                    system("cls");
                    print_header();
                    print_board();
                    goto game_turn;
                }
            }
            else if(line_num == -3){
                int savechoice;
                system("cls");
                print_header();
                print_board();
                printf("\n\n\t\t\t\t\t\tcchoose a savefile or cancel:\n");
                printf("\n\t\t\t\t\t\t1. save1");
                printf("\n\t\t\t\t\t\t2. save2");
                printf("\n\t\t\t\t\t\t3. save3");
                printf("\n\t\t\t\t\t\t4. cancel");
                printf("\n\t\t\t\t\tEnter the number associateed with your choice: ");
                scanf("%d", &savechoice);
                save2_menu:
                switch(savechoice){
                case 1:
                    save("save1.txt");
                    return 1;
                    break;
                case 2:
                    save("save2.txt");
                    return 1;
                    break;
                case 3:
                    save("save3.txt");
                    return 1;
                    break;
                case 4:
                    goto game_turn;
                default:
                    printf("\n\t\t\t\t\tEnter valid savefile! ");
                    scanf("%d", &savechoice);
                    goto save2_menu;
                }
                return 0;
            }
            else if(line_num == -4){
                return 1;
            }
            else if(line_num == -5){
                return 2;
            }
            else if(line_num <= limit && line_num > 0){
                if(lines[line_num -1][1] == 0){
                    undo[undo_count][0] = line_num;
                    undo[undo_count][1] = 2;
                    undo_count++;
                    redo_count = 0;//check
                    draw_line(line_num, player2.color);
                    player2.moves ++;
                    check_score = check_boxes(player2.color);
                    if(check_score == 1){
                        player2.score ++;
                    }else if(check_score == 2){
                        player2.score +=2;
                    }else{
                        turn++;
                    }
                    system("cls");
                    print_header();
                    print_board();
                }else{
                    printf("\t\t\t\t\tINVALID LINE INPUT");
                    Sleep(600);
                    system("cls");
                    print_header();
                    print_board();
                    goto game_turn;
                }
            }else{
                    printf("\t\t\t\t\tINVALID LINE INPUT");
                    Sleep(600);
                    system("cls");
                    print_header();
                    print_board();
                    goto game_turn;
            }
        }
    }
    if(player1.score > player2.score){
        SetConsoleTextAttribute(hConSole, 244);
        printf("\n\n\t\t\t\t\t   %s won", player1.user_name);
        SetConsoleTextAttribute(hConSole, saved_attributes);
        loadscores_from("users.txt");
        sort_scores();
        int check;
        check = checkhighscore(player1.user_name, player1.score);
        if (check == 1){
            printf("\t\t\t\tCongratulations You got a new high score: %d\n", player1.score);
        }
        sort_scores();
        printf("\t\t\t\t\t\tYour rank: %d\n", search_rank(player1.user_name));
        saverank("users.txt");
        char exit[1];
        printf("\t\t\t\t\tPress any key to return to main menu");
        scanf("%c", &exit);
        return 1;
    }else if(player2.score > player1.score){
        SetConsoleTextAttribute(hConSole, 241);
        printf("\n\n\t\t\t\t\t\t   %s won\n", player2.user_name);
        SetConsoleTextAttribute(hConSole, saved_attributes);
        loadscores_from("users.txt");
        sort_scores();
        int check;
        check = checkhighscore(player2.user_name, player2.score);
        if (check == 1){
            printf("\t\t\t\tCongratulation You got a new high score: %d\n", player2.score);
        }
        sort_scores();
        printf("\t\t\t\t\t\trank: %d", search_rank(player2.user_name));
        saverank("users.txt");
        char exit[1];
        printf("\t\t\t\t\tPress any key to return to main menu");
        scanf("%c", &exit);
        return 1;
    }else{
        SetConsoleTextAttribute(hConSole, 242);
        printf("\n\n\t\t\t\t\t\t\tTIE");
        SetConsoleTextAttribute(hConSole, saved_attributes);
        char exit[1];
        printf("\t\t\t\t\tPress any key to return to main menu");
        scanf("%c", &exit);
        return 1;
    }
    printf("\n\n\n\n\n");
}
void undo_move(){
    int previous_line;
    lines_number ++;
    int i;
    previous_line = undo[undo_count - 1][0];
    i = previous_line-1;
    redo[redo_count][0] = previous_line;
    redo_count++;
    boxes_state[lines[i][7]][lines[i][8]] = 0;
    if(game_mode == 2){checker[lines[i][7]][lines[i][8]] = 0;}
    lines[i][1] = 0;
    if(lines[previous_line-1][2] == 1){ // horizontal line
        int col_place;
        col_place = (lines[previous_line-1][4] + lines[previous_line-1][6])/2;
        for(int n = lines[i][3]; n <=lines[i][5]; n++){
            for(int m = lines[i][4]; m <= lines[i][6]; m++){
                board[n][m] = 0;
                board_color_info[n][m] = 0;
            }
        }
        if(previous_line > 9){
            board[lines[previous_line-1][3]][col_place] = previous_line / 10;
            board[lines[previous_line-1][3]][col_place+1] = previous_line % 10;
            board_color_info[lines[previous_line-1][3]][col_place] = 3;
            board_color_info[lines[previous_line-1][3]][col_place+1] = 3;
        }
        else{
            board[lines[previous_line-1][3]][col_place] = previous_line;
            board_color_info[lines[previous_line-1][3]][col_place] = 3;
        }
    }
    else if(lines[previous_line-1][2] == 2){ // vertical line
        int row_place;
        row_place = (lines[i][3]+lines[i][5])/2;
        for(int k = lines[i][3]; k <=lines[i][5]; k++){
            for(int g = lines[i][4]; g <= lines[i][6]; g++){
                board[k][g] = 0;
                board_color_info[k][g] = 0;
            }
        }
        if(previous_line > 9){
            board[row_place][lines[i][4]] = previous_line /10;
            board[row_place][lines[i][4]+1] = previous_line %10;
            board_color_info[row_place][lines[i][4]] = 3;
            board_color_info[row_place][lines[i][4]+1] = 3;
        }else{
            board[row_place][lines[i][4]] = previous_line;
            board_color_info[row_place][lines[i][4]] = 3;
        }
    }
    int to_get_point = 0;
    int box_num = 1;
    for(i = 1; i < grid_size*2+1; i+=2){
        for(int j = 1; j < grid_size*2+1; j+=2){
            if(boxes_state[i][j] == 1){
                if(boxes_state[i][j-1] != 1 || boxes_state[i][j+1] != 1  || boxes_state[i-1][j] != 1 || boxes_state[i+1][j] != 1){
                    to_get_point ++;
                    boxes_state[i][j] = 0;
                    for(int n = boxes[box_num-1][1]; n <= (boxes[box_num-1][1]+2); n++){
                        for(int m = boxes[box_num-1][2]; m <= (boxes[box_num-1][2]+6); m++){
                            board[n][m] = 0;
                            board_color_info[n][m] = 0;
                        }
                    }
                    if(boxes[box_num-1][5] == 1){player1.score --;}
                    else if(boxes[box_num-1][5] == 2){player2.score --;}
                }
            }
            box_num ++;
        }
    }
    if(undo[undo_count-1][1] == 1){player1.moves --;}
    else if(undo[undo_count-1][1] == 2){player2.moves --;}
    undo_count --;
}
void redo_move(){
    int redo_line;
    lines_number --;
    redo_line = redo[redo_count-1][0];
    undo[undo_count][0] = redo_line;
    undo_count++;
    int i;
    i =redo_line -1;
    lines[i][1] = 1;
    boxes_state[lines[i][7]][lines[i][8]] = 1;
    if(game_mode == 2){checker[lines[i][7]][lines[i][8]] = 1;}
    if(lines[i][2] == 1){ // horizontal line
        for(int n = lines[i][3]; n <=lines[i][5]; n++){
            for(int m = lines[i][4]; m <= lines[i][6]; m++){
                board[n][m] = 254;
                board_color_info[n][m] = lines[i][9];
            }
        }
    }else if(lines[i][2] == 2){ // vertical line
        int Extra_cell;
        Extra_cell = (lines[i][3]+lines[i][5])/2;
        board_color_info[Extra_cell][lines[i][4]+1] = 0;//
        for(int k = lines[i][3]; k <=lines[i][5]; k++){
            for(int g = lines[i][4]; g <= lines[i][6]; g++){
                board[k][g] = 219;
                board_color_info[k][g] = lines[i][9];
            }
        }
    }
    int to_get_point = 0;
    int box_num = 1;
    for(int i = 1; i < grid_size*2+1; i+=2){
        for(int j = 1; j < grid_size*2+1; j+=2){
            if(boxes_state[i][j] == 0){
                if(boxes_state[i][j-1] == 1 && boxes_state[i][j+1] == 1 && boxes_state[i-1][j] == 1 && boxes_state[i+1][j] == 1){
                    to_get_point++;
                    boxes_state[i][j] = 1;
                    for(int n = boxes[box_num-1][1]; n <= (boxes[box_num-1][1]+2); n++){
                        for(int m = boxes[box_num-1][2]; m <= (boxes[box_num-1][2]+6); m++){
                            board[n][m] = 219;
                            board_color_info[n][m] = boxes[box_num-1][5];
                        }
                    }
                    if(boxes[box_num-1][5] == 1){player1.score ++;}
                    else if(boxes[box_num-1][5] == 2){player2.score ++;}
                }
            }
            box_num ++;
        }
    }
    if(undo[undo_count-1][1] == 1){player1.moves ++;}
    else if(undo[undo_count-1][1] == 2){player2.moves ++;}
    redo_count --;
}
//=================================== Rank Functions =============================================================
void loadscores_from(char filename[]){
    FILE *fp;
    fp = fopen(filename, "r");
    int i=0;
    while(!feof(fp)){
        fscanf(fp, "%s\n%d", &names[i], &scores[i]);
        rank_counter++;
        i++;
    }
    fclose(fp);
}
void sort_scores(){
    int x,i,temp;
    char temp_char[100];
    for(x=0; x<rank_counter-1; x++){
        for(i=0; i<rank_counter-x-1; i++){
            if(scores[i] > scores[i+1]){
                temp = scores[i];
                strcpy(temp_char, names[i]);
                scores[i] = scores[i+1];
                strcpy(names[i], names[i+1]);
                scores[i+1] = temp;
                strcpy(names[i+1], temp_char);
            }
        }
    }
}
int checkhighscore(char playername[], int playerscore){
    int i, place = 0;
    int existed;
    int status; //0 for no new high score and 1 for new high score
    for(i = rank_counter-1; i>= 0 ; i--){
        if(strcmp(names[i], playername) == 0){
            existed = 1;
            break;
        }else{
            existed = 0;
        }
        place++;
    }
    if(existed == 1){
        if(scores[i] < playerscore){
            scores[i] = playerscore;
            status = 1;
        }
        else{
            status = 0;
        }
    }else if(existed == 0){
        savename_score(playername, playerscore);
        status = 2; // new player
    }
    return status;
}
int search_rank(char playername[]){
    int i, place= 1;
    for(i = rank_counter-1; i >= 0 ; i--){
        if(strcmp(names[i], playername) == 0){
            break;
        }
        place++;
    }
    return place;
}
void print_top10(){
    int j;
    printf("\n\n\n\n\n\t\t\t\t\t\t\t  TOP 10\n");
    printf("\t\t\t\t\t\trank\tname\t\tscore\n\n");
    for(j = rank_counter-1; j >=rank_counter -10; j--){
        printf("\t\t\t\t\t\t%d\t%s\t\t  %d\n",ranknum[j],names[j] ,scores[j]);
    }
    printf("\n\n\n\n\n\n\n");
}
void savename_score(char playername[], int playerscore){
    strcpy(names[rank_counter], playername);
    scores[rank_counter] = playerscore;
    rank_counter ++;
}

void saverank(char filename[]){
    FILE *fnew;
    fnew = fopen(filename, "w");
    for(int a = rank_counter-1; a >=0 ; a--){
        fprintf(fnew, "%s\n%d\n", names[a], scores[a]);
    }
    fclose(fnew);
}
void getrank(){
    int rank = 1;
    for(int i = rank_counter-1; i >=0; i--){
        if(scores[i] == scores[i-1]){
            ranknum[i] = rank;
        }else{
            ranknum[i] = rank;
            rank++;
        }
    }
}
void lowercase(char playername[]){
    char result[100];
    char ch;
    int j = 0;
    while(playername[j]){
        ch = playername[j];
        playername[j] = tolower(ch);
        j++;
    }
}
void save(char savefile[]){
    FILE *fp;
    fp = fopen(savefile, "w");
    fprintf(fp, "%d\n", grid_size);
    fprintf(fp, "%d\n", turn);
    fprintf(fp, "%s\n", player1.user_name);
    fprintf(fp, "%d\n", player1.score);
    fprintf(fp, "%d\n", player1.moves);
    fprintf(fp, "%d\n", player1.color);
    fprintf(fp, "%s\n", player2.user_name);
    fprintf(fp, "%d\n", player2.score);
    fprintf(fp, "%d\n", player2.moves);
    fprintf(fp, "%d\n", player2.color);
    fprintf(fp, "%d\n", game_mode);
    fprintf(fp, "%d\n", limit);
    fprintf(fp, "%d\n", lines_number);
    fprintf(fp, "%d\n", boxes_number);
    fprintf(fp, "%d\n", board_row);
    fprintf(fp, "%d\n", board_col);
    for(int a = 0; a < limit; a++){
        for(int b = 0; b < 10;b++){
            fprintf(fp, "%d\n", lines[a][b]);//status
        }
    }
    for(int a = 0 ; a < grid_size*2+1; a++){
        for(int b = 0; b < grid_size*2+1; b++){
            fprintf(fp, "%d\n", boxes_state[a][b]);
        }
    }
    for(int i = 0; i <= board_row+1; i++){
        for(int j = 0; j <= board_col+1; j++){
            fprintf(fp, "%d\n", board[i][j]);
        }
    }
    for(int i = 0; i <= board_row+1; i++){
        for(int j = 0; j <= board_col+1; j++){
            fprintf(fp, "%d\n", board_color_info[i][j]);
        }
    }
    for(int i = 0; i <= boxes_number ; i++){
        for(int j = 0; j < 5; j++){
            fprintf(fp, "%d\n", boxes[i][j]);
        }
    }
    for(int i = 0; i < grid_size*2+1 ; i++){
        for(int j = 0; j < grid_size*2+1; j++){
            fprintf(fp, "%d\n", checker[i][j]);
        }
    }
}
void load(char loadfile[]){
    FILE *fp;
    int flag;
    fp = fopen(loadfile, "r");
    fscanf(fp, "%d", &grid_size);
    fclose(fp);
    fp = fopen(loadfile, "r");
    if(grid_size == 2){
        fscanf(fp, "%d", &grid_size);
        fscanf(fp, "%d", &turn);
        fscanf(fp, "%s", &player1.user_name);
        fscanf(fp, "%d", &player1.score);
        fscanf(fp, "%d", &player1.moves);
        fscanf(fp, "%d", &player1.color);
        fscanf(fp, "%s", &player2.user_name);
        fscanf(fp, "%d", &player2.score);
        fscanf(fp, "%d", &player2.moves);
        fscanf(fp, "%d", &player2.color);
        fscanf(fp, "%d", &game_mode);
        fscanf(fp, "%d", &limit);
        fscanf(fp, "%d", &lines_number);
        fscanf(fp, "%d", &boxes_number);
        fscanf(fp, "%d", &board_row);
        fscanf(fp, "%d", &board_col);
        for(int a = 0; a < 12; a++){
            for(int b = 0; b < 10;b++){
                fscanf(fp, "%d", &lines[a][b]);//status
            }
        }
        for(int a = 0 ; a < 2*2+1; a++){
            for(int b = 0; b < 2*2+1; b++){
                fscanf(fp, "%d", &boxes_state[a][b]);
            }
        }
        for(int i = 0; i <= 8+1; i++){
            for(int j = 0; j <= 16+1; j++){
                fscanf(fp, "%d", &board[i][j]);
            }
        }
        for(int i = 0; i <= 8+1; i++){
            for(int j = 0; j <= 16+1; j++){
                fscanf(fp, "%d", &board_color_info[i][j]);
            }
        }
        for(int i = 0; i <= 4 ; i++){
            for(int j = 0; j < 5; j++){
                fscanf(fp, "%d", &boxes[i][j]);
            }
        }
        for(int i = 0; i < grid_size*2+1 ; i++){
            for(int j = 0; j < grid_size*2+1; j++){
                fscanf(fp, "%d\n", &checker[i][j]);
            }
        }
        fclose(fp);
    }else if(grid_size == 5){
        fscanf(fp, "%d", &grid_size);
        fscanf(fp, "%d", &turn);
        fscanf(fp, "%s", &player1.user_name);
        fscanf(fp, "%d", &player1.score);
        fscanf(fp, "%d", &player1.moves);
        fscanf(fp, "%d", &player1.color);
        fscanf(fp, "%s", &player2.user_name);
        fscanf(fp, "%d", &player2.score);
        fscanf(fp, "%d", &player2.moves);
        fscanf(fp, "%d", &player2.color);
        fscanf(fp, "%d", &game_mode);
        fscanf(fp, "%d", &limit);
        fscanf(fp, "%d", &lines_number);
        fscanf(fp, "%d", &boxes_number);
        fscanf(fp, "%d", &board_row);
        fscanf(fp, "%d", &board_col);
        for(int a = 0; a < 60; a++){
            for(int b = 0; b < 10;b++){
                fscanf(fp, "%d", &lines[a][b]);//status
            }
        }
        for(int a = 0 ; a < 5*2+1; a++){
            for(int b = 0; b < 5*2+1; b++){
                fscanf(fp, "%d", &boxes_state[a][b]);
            }
        }
        for(int i = 0; i <= 20+1; i++){
            for(int j = 0; j <= 40+1; j++){
                fscanf(fp, "%d", &board[i][j]);
            }
        }
        for(int i = 0; i <= 20+1; i++){
            for(int j = 0; j <= 40+1; j++){
                fscanf(fp, "%d", &board_color_info[i][j]);
            }
        }
        for(int i = 0; i <= 25 ; i++){
            for(int j = 0; j < 5; j++){
                fscanf(fp, "%d", &boxes[i][j]);
            }
        }
        for(int i = 0; i < grid_size*2+1 ; i++){
            for(int j = 0; j < grid_size*2+1; j++){
                fscanf(fp, "%d\n", &getline[i][j]);
            }
        }
        fclose(fp);
    }
}

timer split_time(int total_seconds){
    timer x;
    x.hours = total_seconds/3600;
    x.minutes = (total_seconds%3600)/60;
    x.seconds = ((total_seconds%3600)%60);
    return x;
}
void print_time(timer x){
    printf("\t\t\t\t\t\t %d hrs %d mins %d secs\n", x.hours, x.minutes, x.seconds);
}

int play_computer(){
    HANDLE hConSole=GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    GetConsoleScreenBufferInfo(hConSole,&consoleInfo);
    WORD saved_attributes =consoleInfo.wAttributes;
    int check_score;
    int line_num;
    int counterr=0,check=0;
    while(lines_number != 0){
        game_turn:
        if(turn % 2 == 0){// player1 turn
            SetConsoleTextAttribute(hConSole, 244);
            printf("\tEnter the line number\n\t");
            SetConsoleTextAttribute(hConSole, saved_attributes);
            do{
            fgets(entry, 4, stdin);
            }while(!(line_num=atoi(entry)));
            fflush(stdin);
            if(line_num == -1){//undo
                if(undo_count  !=0){
                    undo_move();
                    //turn ++;
                    system("cls");
                    print_header();
                    print_board();
                }else{
                    printf("INVALID UNDO");
                    Sleep(600);
                    system("cls");
                    print_header();
                    print_board();
                    goto game_turn;
                }
            }
            else if(line_num == -2){
                if(redo_count  !=0){
                    redo_move();
                    system("cls");
                    print_header();
                    print_board();
                }else{
                    printf("INVALID REDO");
                    Sleep(600);
                    system("cls");
                    print_header();
                    print_board();
                    goto game_turn;
                }
            }
            else if(line_num == -3){
                int savechoice;
                system("cls");
                print_header();
                print_board();
                printf("\n\n\t\t\t\t\tchoose a save file or cancel:\n");
                printf("\n\t\t\t\t\t\t1. save1");
                printf("\n\t\t\t\t\t\t2. save2");
                printf("\n\t\t\t\t\t\t3. save3");
                printf("\n\t\t\t\t\t\t4. cancel");
                printf("\n\t\t\t\t\tEnter the number associated with your choice: ");
                do{
                    fgets(entry, 4, stdin);
                }while(!(savechoice = atoi(entry)));
                save_menu:
                switch(savechoice){
                case 1:
                    save("save1.txt");
                    return 1;
                    break;
                case 2:
                    save("save2.txt");
                    return 1;
                    break;
                case 3:
                    save("save3.txt");
                    return 1;
                    break;
                case 4:
                    goto game_turn;
                default:
                    printf("\n\t\t\t\t\tEnter valid save file! ");
                do{
                    fgets(entry, 4, stdin);
                }while(!(savechoice = atoi(entry)));
                    goto save_menu;
                }
                return 0;
            }
            else if(line_num == -4){
                return 1;
            }
            else if(line_num == -5){
                return 2;
            }
            else if(line_num <= limit && line_num > 0){
                if(lines[line_num -1][1] == 0){
                    undo[undo_count][0] = line_num;
                    undo[undo_count][1] = 1;
                    undo_count++;
                    redo_count = 0;//check
                    draw_line(line_num, player1.color);
                    player1.moves ++;
                    check_score = check_boxes(player1.color);
                    if(check_score == 1){
                        player1.score ++;
                    }else if(check_score == 2){
                        player1.score += 2;
                    }
                    else{
                        turn++;
                    }
                    system("cls");
                    print_header();
                    print_board();
                }else{
                    printf("\t\t\t\t\tINVLID LINE INPUT");
                    Sleep(600);
                    system("cls");
                    print_header();
                    print_board();
                    goto game_turn;
                }
            }else{
                    printf("\t\t\t\t\tINVLID LINE INPUT");
                    Sleep(600);
                    system("cls");
                    print_header();
                    print_board();
                    goto game_turn;
            }
        }
        else if(turn % 2 != 0){//the computer

        for(int i=1;i<grid_size*2+1;i+=2){
            for(int j=1;j<grid_size*2+1;j+=2){
                counterr = checker[i][j-1]+checker[i][j+1]+checker[i-1][j]+checker[i+1][j];
                if (counterr==3){
                    if(checker[i][j-1]==0){
                            line_num = getline[i][j-1];
                            check = 1;
                            break;
                    }
                    else if(checker[i][j+1]==0){
                            line_num =getline[i][j+1];
                            check = 1;
                            break;
                    }
                    else if(checker[i-1][j]==0){
                            line_num =getline[i-1][j];
                            check = 1;
                            break;
                    }else {
                            line_num = getline[i+1][j];
                            check = 1;
                            break;
                            }
                    }else{check=0;}
                    if(check == 1){
                        break;
                    }
            }
                if(check == 1){
                    break;
                }
            }
            if (check==0){
                line_num = rand()%(limit-1+1)+1;
            }
            if(lines[line_num -1][1] == 0){
                undo[undo_count][0] = line_num;
                undo[undo_count][1] = 2;
                undo_count++;
                redo_count = 0;//check
                draw_line(line_num, player2.color);
                player2.moves ++;
                check_score = check_boxes(player2.color);
                if(check_score == 1){
                    player2.score ++;
                }else if(check_score == 2){
                    player2.score +=2;
                }else{
                    turn++;
                }
                Sleep(1000);
                system("cls");
                print_header();
                print_board();
            }else{
                Sleep(200);
                system("cls");
                print_header();
                print_board();
                goto game_turn;
            }
        }
    }
    if(player1.score > player2.score){
        SetConsoleTextAttribute(hConSole, 244);
        printf("\n\n\t\t\t\t\t   %s won", player1.user_name);
        SetConsoleTextAttribute(hConSole, saved_attributes);
        loadscores_from("users.txt");
        sort_scores();
        int check;
        check = checkhighscore(player1.user_name, player1.score);
        if (check == 1){
            printf("\t\t\t\tCongratulations You got a new high score: %d\n", player1.score);
        }
        sort_scores();
        printf("\t\t\t\t\tYour rank: %d\n", search_rank(player1.user_name));
        saverank("users.txt");
        char exit[1];
        printf("\t\t\t\t\tPress any key to return to main menu");
        scanf("%c", &exit);
        return 1;
    }else if(player2.score > player1.score){
        SetConsoleTextAttribute(hConSole, 241);
        printf("\n\n\t\t\t\t\t\t   computer won");
        SetConsoleTextAttribute(hConSole, saved_attributes);
        char exit[1];
        printf("\t\t\t\t\tPress any key to return to main menu");
        scanf("%c", &exit);
        return 1;
    }else{
        SetConsoleTextAttribute(hConSole, 242);
        printf("\n\n\t\t\t\t\t\t\tTIE");
        SetConsoleTextAttribute(hConSole, saved_attributes);
        char exit[1];
        printf("\t\t\t\t\tPress any key to return to main menu");
        scanf("%c", &exit);
        return 1;
    }
    printf("\n\n\n\n\n");
}
void reset(){
    for(int i = 0; i < 50; i++){
        for(int j = 0; j < 50; j++){
            board[i][j] = 0;
            board_color_info[i][j] = 0;
            turn = 2;
            player1.score = 0;
            player1.moves = 0;
            player2.score = 0;
            player2.moves = 0;
            rank_counter = -1;
        }
    }
}
