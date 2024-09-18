#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>
#include <sstream>
#include <cmath>
#include <array>
#include <vector>

std::string readFile();

typedef std::vector<std::pair<int, int>> coordinateList;

void ReadByteToMap(std::array<int, 4> half_byte, int r_index, int c_index, int (&MatrixMap)[64][128] );

void MapCoordinateFromFile(std::string filename, int(&MatrixMap)[64][128]);

extern std::unordered_map<int, char> ToHexLetter;

std::array<int, 4> DigitToHalfByte(int num);

extern std::unordered_map<char, int> HexLetterToInt; 

int four_bit_to_hex(int a, int b, int c, int d);

void WriteFile(int matrix_map[64][128]);
