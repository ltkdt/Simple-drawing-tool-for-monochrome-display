#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <sstream>
#include <cmath>
#include <array>

// Convertion

extern std::unordered_map<int, char> ToHexLetter;

std::array<int, 4> DigitToHalfByte(int num);

extern std::unordered_map<char, int> HexLetterToInt; 

int four_bit_to_hex(int a, int b, int c, int d);

// File operations

std::string readFile();

void ReadByteToMap(std::array<int, 4> half_byte, int r_index, int c_index, int (&MatrixMap)[64][128] );

void MapCoordinateFromFile(std::string filename, int(&MatrixMap)[64][128]);

void WriteFile(int matrix_map[64][128]);
