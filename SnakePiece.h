
#ifndef SNAKE_PIECE
#define SNAKE_PIECE

#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>

#define SQUAREDIMS 40

class SnakeData {
public:
    std::vector<char> directions;
    std::vector<cv::Mat> listI;
    std::vector< std::vector<short> > listCoords;
    
    cv::Mat screen;
    cv::Mat apple;
    short appleCoords[2];
    
    void setAppleCoords();
    void drawSnake();
    bool moveSnake(char);
    bool gotApple(char);
    void changeDirection(short, char);
};

#endif //SNAKE_PIECE
