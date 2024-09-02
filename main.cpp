#include "cube.h"
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>


using namespace std;

int main() {
    std::string filePath = "input2.txt";
    std::ifstream file(filePath);

    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filePath << std::endl;
        return 1;
    }

    // read in text file content, convert to string 
    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string content = buffer.str();

    file.close();

    Cube cube = Cube::parse2DCube(content);

    // test scramble 
    cube.rotateFace(0, true);
    cube.rotateFace(1, false);
    cube.rotateFace(0, false);
    // cube.rotateFace(1, true);
    // cube.rotateFace(2, true);
    // cube.rotateFace(3, false);
    // cube.rotateFace(4, true);
    // cube.rotateFace(5, false);

    std::vector<std::string> solution = cube.solve();


    // print solution
    for (const auto& move : solution) {
        std::cout << move << std::endl;
    }


    return 0;
}