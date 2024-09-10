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

coordinateList MapCoordinateFromFile(std::string filename);

extern std::unordered_map<int, char> ToHexLetter;

std::array<int, 4> DigitToByte(int num);

extern std::unordered_map<char, int> HexLetterToInt; 

int four_bit_to_hex(int a, int b, int c, int d);

void WriteFile(int matrix_map[64][128]);
