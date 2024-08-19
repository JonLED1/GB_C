#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <conio.h>

#include "config.h"
#include "menu.h"
#include "field.h"
#include "drone.h"

void main(){
    int game_mode=0;
    char matrix[MAX_X][MAX_Y];
    char matrix2[MAX_X][MAX_Y];
    int score[6]={0};
    
    while(1){
        start_screen();
        game_mode=main_menu();
        clear_screen();
        fill_field(matrix);
        fill_drone(matrix2);
        drone_t drone0=init_drone(STOP,10,10,0);

        while(1){
            
            move_drone(matrix2, &drone0);
            check_pump(matrix, &drone0);
            score[0]=drone0.pumpkins;
            print_field(matrix);
            print_drone(matrix2);   
            game_menu(game_mode, score);
            ripening_pumpkis(matrix);

            if (kbhit()) {
            	char ch = getch();
				if (ch=='w' || ch=='W') drone0.direction=UP;
				if (ch=='a' || ch=='A') drone0.direction=LEFT;
				if (ch=='s' || ch=='S') drone0.direction=DOWN;
				if (ch=='d' || ch=='D') drone0.direction=RIGHT;
				if (ch=='p' || ch=='P'){
                    printf("GAME PAUSED. Press P to continue.");
                    drone0.direction=STOP;
                    while (1){
                        if (kbhit()){
                            char ch = getch();
                            if (ch=='p' || ch=='P'){
                                system("cls");
                                break;
                            }
                        }
                    }
                }
				if (ch=='q' || ch=='Q') break;;
            }
            delay(300);
        }
    }
}