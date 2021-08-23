
#include "main.h"

int main() {

    SnakeData info;
    
    info.directions.push_back('l');
    cv::Mat piece = cv::imread("./Images/snakehead.jpg");
    info.listI.push_back(piece);
    std::vector<short> Coords{12*SQUAREDIMS, 12*SQUAREDIMS};
    info.listCoords.push_back(Coords);
    
    info.directions.push_back('l');
    piece = cv::imread("./Images/snakebody.jpg");
    info.listI.push_back(piece);
    std::vector<short> Coords2{13*SQUAREDIMS, 12*SQUAREDIMS};
    info.listCoords.push_back(Coords2);
    
    info.directions.push_back('l');
    piece = cv::imread("./Images/snaketail.jpg");
    info.listI.push_back(piece);
    std::vector<short> Coords3{14*SQUAREDIMS, 12*SQUAREDIMS};
    info.listCoords.push_back(Coords3);

    info.screen = cv::imread("./Images/snakescreen.jpg");
    info.apple = cv::imread("./Images/apple.jpg");
    

    info.setAppleCoords();
    
    info.drawSnake();
    cv::waitKey(0);
    
    bool playing = true;
    while (playing) {
        
        int k = cv::waitKey(100);
        if (k==0 and (info.directions[0] == 'l' or info.directions[0] == 'r')) playing = info.moveSnake('u');
        else if (k==1 and (info.directions[0] == 'l' or info.directions[0] == 'r')) playing = info.moveSnake('d');
        else if (k==2 and (info.directions[0] == 'u' or info.directions[0] == 'd')) playing = info.moveSnake('l');
        else if (k==3 and (info.directions[0] == 'u' or info.directions[0] == 'd')) playing = info.moveSnake('r');
        else playing = info.moveSnake(info.directions[0]);
        
        if (playing) {
            info.drawSnake();
        }
        else {
            cv::waitKey(0);
        }
        
    }
    
    return 0;
}
