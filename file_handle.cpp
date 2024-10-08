#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <sstream>
#include <cmath>
#include <array>
#include "file_handle.h"

std::unordered_map<char, int> HexLetterToInt = {
    {'a', 10},
    {'b', 11},
    {'c', 12},
    {'d', 13},
    {'e', 14},
    {'f', 15}
};

std::array<int, 4> DigitToHalfByte(int num){
    std::array <int,4> byte;
    for(int j = 3; j>=0; j--){
        int base = std::pow(2,j);
        if(num >= base){
            num -= base;
            byte[3-j] = 1;
        }
        else{
            byte[3-j] = 0;
        }    
    }
    return byte;
}

void ReadByteToMap(std::array<int, 4> half_byte, int r_index, int c_index, int (&MatrixMap)[64][128] ){
    for (int i = 0; i<4; i++){
        if(half_byte[i] == 1){
            MatrixMap[r_index][c_index*4 + i] = 1;
        }
    }
}


void MapCoordinateFromFile(std::string filename, int(&MatrixMap)[64][128]){
    std::string line;
    std::ifstream FileHandle(filename);
    int i, column, row;
    column = 0;
    row = 0;
    std::array<int, 4> CurrentByte, CurrentByte2;
    while(getline(FileHandle, line)){
        /*
        std::stringstream liness(line);
        std::string value;
        while(std::getline(liness, value, '\t')) {
            std::cout << token << '\n';
        }
        */
        if(line[0] == '\t'){
            for(i=3;i <line.length(); i+= 6){
                // if the char is a number
                int digit = line[i] -'0' ;
                if(digit < 0 or digit > 9){
                    digit = HexLetterToInt[line[i]];
                }
                CurrentByte = DigitToHalfByte(digit);

                int digit2 = line[i+1] -'0' ;
                if(digit2 < 0 or digit2 > 9){
                    digit2 = HexLetterToInt[line[i+1]];
                }
                CurrentByte2 = DigitToHalfByte(digit2);

                ReadByteToMap(CurrentByte,row,column, MatrixMap);
                ReadByteToMap(CurrentByte2,row,column+1, MatrixMap);
                column += 2;
            }
            std::cout << row << " " << column << "\n";
        }

        row++;
        column = 0;
    }
    FileHandle.close();
}

std::unordered_map<int, char> ToHexLetter = {
    {10, 'a'},
    {11, 'b'},
    {12, 'c'},
    {13, 'd'},
    {14, 'e'},
    {15, 'f'}
};

int four_bit_to_hex(int a, int b, int c, int d){
    return a * 8 + b * 4 + c*2 + d*1; // a * 2^3 + b * 2^2 + c * 2^1 + d * 2^0
};


/*
The program doesn't use the readFile() function below, however I choose to include it as it can be useful if you twerk the program yourself.
It can be used for the purpose of reading a bitmap and display it on a canvas
*/
std::string readFile(){
    std::string fileContent;
    std::string appendstring(" \n");

    // Read from the text file
    std::ifstream FileHandle("object.cpp");

    // Use a while loop together with the getline() function to read the file line by line
    while (getline (FileHandle, fileContent)) {
    // Output the text from the file
        std::cout << fileContent << std::endl;
    }
    FileHandle.close();

    return fileContent;
}



/*

Translate the matrix map to matrix (16x64).

Each byte represents 8 bits corresponding 8 horizontal consecutive pixels.

Each 8 bit needs to be translated to hexadecimal first (basically binary to hexadecimal).

The function divides the byte to two parts, respresent each of them in hexadecimal from first before combine each other

Example:

11110011

==> 1111 | 0011

==> F | 3

==> F3

*/


void WriteFile(int matrix_map[64][128]){
    std::ofstream FileHandle("bitmap.cpp");

    FileHandle << "static const unsigned char myBitmap [] { " << std::endl;
     for(int i = 0; i < 64; i++){
        FileHandle << "\t";
        for(int j = 0; j < 128; j += 8){

            FileHandle << "0x";
            int first_hex = four_bit_to_hex(matrix_map[i][j], matrix_map[i][j+1], matrix_map[i][j+2], matrix_map[i][j+3]);
            if (first_hex > 9){
                FileHandle << ToHexLetter[first_hex];
            }
            else{
                FileHandle << first_hex;
            }

            // Repeat the same process
            int last_hex = four_bit_to_hex(matrix_map[i][j+4], matrix_map[i][j+5], matrix_map[i][j+6], matrix_map[i][j+7]);
            if (last_hex > 9){
                FileHandle << ToHexLetter[last_hex] << ", ";
            }
            else{
                FileHandle << last_hex << ", ";
            }
        }

        FileHandle << std::endl;
    }
    FileHandle << "};";

    FileHandle.close();
}
