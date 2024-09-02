#ifndef CUBE_H
#define CUBE_H

#include <vector>
#include <map>
#include <string>

class Cube {
public:
    Cube();
    Cube(const std::vector<std::vector<std::vector<char>>>& state);
    static Cube parse2DCube(const std::string& input);
    Cube applyMove(int move);
    size_t hash() const;
    bool operator==(const Cube& other) const;
    void print() const;
    void rotateFace(int face, bool clockwise);
    int getManhattanDistance(int face1, int row1, int col1, int face2, int row2, int col2) const;
    std::pair<int, int> getCornerEdgeManhattanSums() const;
    int heuristic(const Cube& other) const;
    bool isSolved() const;
    std::vector<Cube> getNeighbors() const;
    std::vector<std::string> solve();
    int search(int g, int bound, std::vector<std::string>& path, int lastFace, bool lastClockwise);

private:
    std::vector<std::vector<std::vector<char>>> state;

    enum Direction { TOP, BOTTOM, LEFT, RIGHT };

    struct AdjacentFace {
        int face;       
        Direction dir;  
    };

    const std::map<int, std::vector<AdjacentFace>> adjacentFaces = {
        {0, {{1, TOP}, {2, TOP}, {3, TOP}, {4, TOP}}}, 
        {1, {{0, LEFT}, {2, LEFT}, {5, LEFT}, {4, RIGHT}}}, 
        {2, {{0, BOTTOM}, {3, LEFT}, {5, TOP}, {1, RIGHT}}}, 
        {3, {{0, RIGHT}, {4, LEFT}, {5, RIGHT}, {2, RIGHT}}},
        {4, {{0, TOP}, {1, LEFT}, {5, BOTTOM}, {3, RIGHT}}}, 
        {5, {{2, BOTTOM}, {1, BOTTOM}, {4, BOTTOM}, {3, BOTTOM}}}  
    };

    void updateAdjacentFaces(int face, bool clockwise);
    void getFaceRowColumn(int face, Direction dir, std::vector<char>& buf) const;
    void setFaceRowColumn(int face, Direction dir, const std::vector<char>& buf);

};

#endif 
