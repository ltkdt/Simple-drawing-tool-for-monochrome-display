#include "logic_handle.h"
#include "raylib.h"
#include <cmath>

void swap_int(int &a, int&b){
    a=a+b;
    b=a-b;
    a=a-b;
}

bool same_row_or_column(int x1, int y1, int x2, int y2){
    return (x1==x2) || (y1 == y2);
}

void draw_with_pen_size(int (&matrix_map)[64][128],int y, int x, int span){
    for(int i = 0; i < span; i++){
        for(int j = 0; j < span; j++){
            if ( !(i+y > 63 || x+j > 127) ){
                matrix_map[i+y][x+j] = 1;
            }
        }
    }
}

void draw_h_line(int x1, int x2, int shared_y, int (&matrix_map)[64][128]){
    if (x1 > x2){
        swap_int(x1, x2);
    }
    for(x1; x1 < x2; x1++){
        matrix_map[shared_y][x1] = 1;
    }
}

void draw_v_line(int y1, int y2, int shared_x, int (&matrix_map)[64][128] ){
    if (y1 > y2){
        swap_int(y1, y2);
    }
    for (y1; y1 < y2; y1++){
        matrix_map[y1][shared_x] = 1;
    }
}

/*
    This is the base algorithm ,it works when delta x and delta y are both positive


void draw_line_bresenham(int x1, int y1, int x2, int y2, int (&matrix_map)[64][128] ){
    int delta_x = x2 - x1;
    int delta_y = y2 - y1;

    // No need to check if delta_x is different from 0 as I have draw_v_line to cover that case

    int y = y1;
    int dp = 2*delta_y - delta_x; // dp stands for decision parameter, or whether y will move up or down

    for(int i =0; i < delta_x +1; i++){
        matrix_map[y][x1+i] = 1;
        if(dp >= 0){
            y++;
            dp = dp + 2*delta_y - 2*delta_x;
        }
        else{
            dp = dp +2*delta_y;
        }
    }
}

*/

/*
                        \       |       /
                            \ 6 | 7 /
                        5      \|/      8
                    ------------|------------
                        4      /|\      1
                            /   |   \
                        /   3   |  2    \
*/

// The algorithm above but it can handle negative slope
void draw_line_bresenham_horizontal(int x1, int y1, int x2, int y2, int (&matrix_map)[64][128] ){
    int delta_x = x2 - x1;

    if (delta_x < 0){
        swap_int(x1, x2);
        swap_int(y1, y2);
        delta_x = -delta_x;
    }

    int delta_y = y2 - y1;
    int y_direction = (delta_y > 0) ? 1 : -1;
    delta_y = (delta_y > 0) ? delta_y  : - delta_y;

    // No need to check if delta_x is different from 0 as I have draw_v_line to cover that case

    int y = y1;
    int dp = 2*delta_y - delta_x; // dp stands for decision parameter, or whether y will move up or down

    for(int i =0; i < delta_x +1; i++){
        matrix_map[y][x1+i] = 1;
        if(dp >= 0){
            y += y_direction;
            dp = dp + 2*delta_y - 2*delta_x;
        }
        else{
            dp = dp +2*delta_y;
        }
    }
}

void draw_line_bresenham_vertical(int x1, int y1, int x2, int y2, int (&matrix_map)[64][128] ){
    int delta_y = y2 - y1;

    if (delta_y < 0){
        swap_int(x1, x2);
        swap_int(y1, y2);
        delta_y = -delta_y;
    }

    int delta_x = x2 - x1;
    int x_direction = (delta_x > 0) ? 1 : -1;
    delta_x = (delta_x > 0) ? delta_x  : - delta_x;

    // No need to check if delta_x is different from 0 as I have draw_v_line to cover that case

    int x = x1;
    int dp = 2*delta_x - delta_y; // dp stands for decision parameter, or whether y will move up or down

    for(int i =0; i < delta_y +1; i++){
        matrix_map[y1+i][x] = 1;
        if(dp >= 0){
            x += x_direction;
            dp = dp + 2*delta_x - 2*delta_y;
        }
        else{
            dp = dp + 2*delta_x;
        }
    }
}

void draw_line(int x1, int y1, int x2, int y2, int (&matrix_map)[64][128]){
    if ( std::abs(x2 -  x1) >= std::abs( y2 - y1 ) ){
        draw_line_bresenham_horizontal(x1, y1, x2, y2, matrix_map);
    }
    else{
        draw_line_bresenham_vertical(x1, y1, x2, y2, matrix_map);
    }
}

void draw_rect(int x1, int y1, int x2, int y2, int (&matrix_map)[64][128]){
    if (x1 > x2){
        swap_int(x1, x2);
    }
    if (y1 > y2){
        swap_int(y1, y2);
    }

    // Start drawing 2 lines to create rect
    // The endpoint is added 1 because the point (x1, y2) and (x2, y1) might not be colored without it

    draw_h_line(x1, x2+1, y1, matrix_map);
    draw_h_line(x1, x2+1, y2, matrix_map);
    draw_v_line(y1, y2+1, x1, matrix_map);
    draw_v_line(y1, y2+1, x2, matrix_map);
}