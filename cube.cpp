#include "cube.h"
#include <iostream>
#include <sstream>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <unordered_set>
#include <limits>

using namespace std;

// default constructor which creates a solved cube 
Cube::Cube() {
    for (int face = 0; face < 6; ++face) {
        state[face] = std::vector<std::vector<char>>(3, std::vector<char>(3, 'W' + face));
    }
}

Cube::Cube(const std::vector<std::vector<std::vector<char>>>& inputState) : state(inputState) {}

//     W W W
//     W W W
//     W W W
// O O O G G G R R R B B B
// O O O G G G R R R B B B
// O O O G G G R R R B B B
//     Y Y Y
//     Y Y Y
//     Y Y Y

// the parser is designed to read the 2D cube format commented above. 

Cube Cube::parse2DCube(const std::string& input) {
    std::vector<std::vector<std::vector<char>>> state(6, std::vector<std::vector<char>>(3, std::vector<char>(3)));
    stringstream ss(input);
    string line = "";
    char currColor = ' ';
    
    // read white face
    for (int i = 0; i < 3; i++) {
        std::getline(ss, line);
        for (int j = 0; j < 3; j++) {
            stringstream ss2(line);
            ss2 >> currColor;
            state[0][i][j] = currColor;
        }
    }

    // read orange, green, red, and blue faces 
    for (int i = 0; i < 3; i++) {
        std::getline(ss, line);
        std::istringstream lineStream(line);
        for (int face = 1; face <= 4; face++) {
            for (int j = 0; j < 3; j++) {
                lineStream >> currColor;
                state[face][i][j] = currColor;
            }
        }
    }

    // read yellow face
    for (int i = 0; i < 3; i++) {
        std::getline(ss, line);
        std::istringstream lineStream(line);
        for (int j = 0; j < 3; j++) {
            lineStream >> currColor;
            state[5][i][j] = currColor;
        }
    }
    return Cube(state);
}

// prints the cube in the 2D format
void Cube::print() const {
    for (int i = 0; i < 3; i++) {
        std::cout << "    ";
        for (int j = 0; j < 3; j++) {
            std::cout << state[0][i][j] << " ";
        }
        std::cout << std::endl;
    }

    for (int i = 0; i < 3; i++) {
        for (int face = 1; face <= 4; face++) {
            for (int j = 0; j < 3; j++) {
                std::cout << state[face][i][j] << " ";
            }
        }
        std::cout << std::endl;
    }

    for (int i = 0; i < 3; i++) {
        std::cout << "    ";
        for (int j = 0; j < 3; j++) {
            std::cout << state[5][i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void Cube::rotateFace(int face, bool clockwise) {
    std::vector<std::vector<char>> temp = state[face];
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (clockwise) {
                state[face][j][2-i] = temp[i][j];
            } else {
                state[face][2-j][i] = temp[i][j];
            }
        }
    }
    updateAdjacentFaces(face, clockwise);
}

void Cube::updateAdjacentFaces(int face, bool clockwise) {
    std::vector<AdjacentFace> adj = adjacentFaces.at(face);
    std::vector<std::vector<char>> temp(4, std::vector<char>(3));  // temp storage for rows/columns

    for (int i = 0; i < 4; i++) {
        getFaceRowColumn(adj[i].face, adj[i].dir, temp[i]);
    }

    if (clockwise) {
        for (int i = 0; i < 4; i++) {
            setFaceRowColumn(adj[(i+1)%4].face, adj[(i+1)%4].dir, temp[i]);
        }
    } else {
        for (int i = 0; i < 4; i++) {
            setFaceRowColumn(adj[i].face, adj[i].dir, temp[(i+1)%4]);
        }
    }
}

void Cube::getFaceRowColumn(int face, Direction dir, std::vector<char>& buf) const {
    switch (dir) {
        case TOP:
            buf = state[face][0];
            break;
        case BOTTOM:
            buf = state[face][2];
            break;
        case LEFT:
            for (int i = 0; i < 3; i++) buf[i] = state[face][i][0];
            break;
        case RIGHT:
            for (int i = 0; i < 3; i++) buf[i] = state[face][i][2];
            break;
    }
}

void Cube::setFaceRowColumn(int face, Direction dir, const std::vector<char>& buf) {
    switch (dir) {
        case TOP:
            state[face][0] = buf;
            break;
        case BOTTOM:
            state[face][2] = buf;
            break;
        case LEFT:
            for (int i = 0; i < 3; i++) state[face][i][0] = buf[i];
            break;
        case RIGHT:
            for (int i = 0; i < 3; i++) state[face][i][2] = buf[i];
            break;
    }
}

int Cube::getManhattanDistance(int face1, int row1, int col1, int face2, int row2, int col2) const {
    return std::abs(face1 - face2) + std::abs(row1 - row2) + std::abs(col1 - col2);
}

int Cube::heuristic(const Cube& other) const {
    int cornerSum = 0;
    int edgeSum = 0;

    for (int face = 0; face < 6; face++) {
        cornerSum += getManhattanDistance(face, 0, 0, other.state[face][0][0] - '0', 0, 0);
        cornerSum += getManhattanDistance(face, 0, 2, other.state[face][0][2] - '0', 0, 2);
        cornerSum += getManhattanDistance(face, 2, 0, other.state[face][2][0] - '0', 2, 0);
        cornerSum += getManhattanDistance(face, 2, 2, other.state[face][2][2] - '0', 2, 2);
    }

    for (int face = 0; face < 6; face++) {
        edgeSum += getManhattanDistance(face, 0, 1, other.state[face][0][1] - '0', 0, 1);
        edgeSum += getManhattanDistance(face, 1, 0, other.state[face][1][0] - '0', 1, 0);
        edgeSum += getManhattanDistance(face, 1, 2, other.state[face][1][2] - '0', 1, 2);
        edgeSum += getManhattanDistance(face, 2, 1, other.state[face][2][1] - '0', 2, 1);
    }

    int cornerHeuristic = cornerSum / 4;
    int edgeHeuristic = edgeSum / 4;

    return std::max(cornerHeuristic, edgeHeuristic);
}

bool Cube::isSolved() const {
    for (const auto& face : state) {
        char color = face[0][0];
        for (const auto& row : face) {
            for (char c : row) {
                if (c != color) return false;
            }
        }
    }
    return true;
}

std::vector<Cube> Cube::getNeighbors() const {
    std::vector<Cube> neighbors;
    for (int face = 0; face < 6; ++face) {
        for (bool clockwise : {true, false}) {
            Cube neighbor = *this;
            neighbor.rotateFace(face, clockwise);
            neighbors.push_back(neighbor);
        }
    }
    return neighbors;
}

std::vector<std::string> Cube::solve() {
    std::vector<std::string> solution;
    int bound = heuristic(*this);
    
    while (true) {
        int t = search(0, bound, solution, -1, true);
        if (t == 0) return solution; 
        if (t == std::numeric_limits<int>::max()) return {};  // no solution
        bound = t;
    }
}

int Cube::search(int g, int bound, std::vector<std::string>& path, int lastFace = -1, bool lastClockwise = true) {
    int f = g + heuristic(*this);
    if (f > bound) return f;
    if (isSolved()) return 0;

    int min = std::numeric_limits<int>::max();
    for (int face = 0; face < 6; ++face) {

        if (face == lastFace && !lastClockwise) continue;

        for (bool clockwise : {true, false}) {

            if (face == lastFace && !lastClockwise) continue;

            Cube neighbor = *this;
            neighbor.rotateFace(face, clockwise);
            string faceColor = "";
            if (face == 0) faceColor = "White";
            else if (face == 1) faceColor = "Orange";
            else if (face == 2) faceColor = "Green";
            else if (face == 3) faceColor = "Red";
            else if (face == 4) faceColor = "Blue";
            else if (face == 5) faceColor = "Yellow";

            std::string move = faceColor + (clockwise ? " CW" : " CCW");
            path.push_back(move);
            
            int t = neighbor.search(g + 1, bound, path, face, clockwise);
            
            if (t == 0) return 0; 
            if (t < min) min = t;
            
            path.pop_back();
        }
    }
    return min;
}
