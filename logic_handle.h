#include "raylib.h"
#include <cmath>
#include <vector>
#include <utility>

// Utilities for drawing

void swap_int(int &a, int&b);

bool same_row_or_column(int x1, int y1, int x2, int y2);

// Drawing functions

void draw_with_pen_size(int (&matrix_map)[64][128],int y, int x, int pen_size);

void draw_h_line(int x1, int x2, int shared_y, int (&matrix_map)[64][128]);

void draw_v_line(int y1, int y2, int shared_x, int (&matrix_map)[64][128] );

void draw_line_bresenham_horizontal(int x1, int y1, int x2, int y2, int (&matrix_map)[64][128] );

void draw_line_bresenham_vertical(int x1, int y1, int x2, int y2, int (&matrix_map)[64][128] );

void draw_line(int x1, int y1, int x2, int y2, int (&matrix_map)[64][128]);

void draw_rect(int x1, int y1, int x2, int y2, int (&matrix_map)[64][128]);

void midpoint_circle(int center_x, int center_y, int r, int (&matrix_map)[64][128]);

void draw_pixel_with_check(int x, int y, int(&matrix_map)[64][128]);

// Copying - paste

std::vector<std::pair<int,int>> scan(int x1, int y1, int x2, int y2, int matrix_map[64][128]);

void paste_scan(int x, int y, std::vector<std::pair<int,int>> scan_result, int (&matrix_map)[64][128]);