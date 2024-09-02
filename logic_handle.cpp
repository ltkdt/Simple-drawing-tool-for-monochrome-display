#include "logic_handle.h"
#include "raylib.h"

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

void draw_line(int x1, int y1, int x2, int y2, int (&matrix_map)[64][128] ){
    // not yet implemented
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