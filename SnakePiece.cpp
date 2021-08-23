
#include "SnakePiece.h"

void SnakeData::changeDirection(short index, char newDirection) {
    std::cout << "new direction is " << newDirection << std::endl;
    if (directions[index] != newDirection) {
        if ((directions[index] == 'l' and newDirection == 'u') or
            (directions[index] == 'u' and newDirection == 'r') or
            (directions[index] == 'r' and newDirection == 'd') or
            (directions[index] == 'd' and newDirection == 'l')) {
            cv::transpose(listI[index], listI[index]);
            cv::flip(listI[index], listI[index], 1);
        }
        else {
            cv::transpose(listI[index], listI[index]);
            cv::flip(listI[index], listI[index], 1);
            cv::transpose(listI[index], listI[index]);
            cv::flip(listI[index], listI[index], 1);
            cv::transpose(listI[index], listI[index]);
            cv::flip(listI[index], listI[index], 1);
        }
        std::cout << "changed piece " << index << " from " << directions[index] << " to " << newDirection << std::endl;
        directions[index] = newDirection;
    }
}

void SnakeData::setAppleCoords() {
    bool placed = false;
    while (!placed) {
        short x = (rand()%25)*SQUAREDIMS;
        short y = (rand()%25)*SQUAREDIMS;
        std::vector<short> possible{x, y};
        if (std::find(listCoords.begin(), listCoords.end(), possible) == listCoords.end()) {
            placed = true;
            appleCoords[0] = x;
            appleCoords[1] = y;
        }
    }
}

void SnakeData::drawSnake() {
    cv::Mat background = screen.clone();
    for (int i=0; i<directions.size(); ++i) {
        cv::Rect roi = cv::Rect(listCoords[i][0], listCoords[i][1], SQUAREDIMS, SQUAREDIMS);
        cv::Mat subView = background(roi);
        listI[i].copyTo(subView);
    }
    cv::Rect roi = cv::Rect(appleCoords[0], appleCoords[1], SQUAREDIMS, SQUAREDIMS);
    cv::Mat subView = background(roi);
    apple.copyTo(subView);
    cv::imshow("Window", background);
}

bool SnakeData::gotApple(char direction) {
    bool gotit = true;
    short x, y;
    if (direction == 'l') {
        x = -1*SQUAREDIMS;
        y = 0;
    }
    else if (direction == 'u') {
        x = 0;
        y = -1*SQUAREDIMS;
    }
    else if (direction == 'r') {
        x = SQUAREDIMS;
        y = 0;
    }
    else {
        x = 0;
        y = SQUAREDIMS;
    }
    if (listCoords[0][0]+x == appleCoords[0] and listCoords[0][1]+y == appleCoords[1]) {
        directions.insert(directions.begin() + 1, directions[0]);
        changeDirection(0, direction);
        cv::Mat piece = cv::imread("./Images/snakebody.jpg");
        listI.insert(listI.begin() + 1, piece);
        std::vector<short> Coords{listCoords[0][0], listCoords[0][1]};
        listCoords.insert(listCoords.begin() + 1, Coords);
        listCoords[0][0]+=x;
        listCoords[0][1]+=y;
        setAppleCoords();
    }
    else {
        gotit = false;
    }
    return gotit;
}


bool SnakeData::moveSnake(char direction) {
    bool keepGoing = true;
    if (direction == directions[0] or ((direction == 'u' and directions[0] != 'd') or
        (direction == 'r' and directions[0] != 'l') or (direction == 'd' and directions[0] != 'u') or (direction == 'l' and directions[0] != 'r'))) {
        if(!this->gotApple(direction)) {
            for(int i=directions.size()-1; i>0; --i) {
                std::cout << "changing piece " << i << " from " << directions[i] << " to " << directions[i-1] << std::endl;
                changeDirection(i, directions[i-1]);
                listCoords[i][0] = listCoords[i-1][0];
                listCoords[i][1] = listCoords[i-1][1];
            }
            changeDirection(0, direction);
            if (direction == 'u' and listCoords[0][1]-SQUAREDIMS >=0) {
                listCoords[0][1]-=SQUAREDIMS;
            }
            else if (direction == 'l' and listCoords[0][0]-SQUAREDIMS >= 0) {
                listCoords[0][0]-=SQUAREDIMS;
            }
            else if (direction == 'd' and listCoords[0][1]+SQUAREDIMS <= 960) {
                listCoords[0][1]+=SQUAREDIMS;
            }
            else if (direction == 'r' and listCoords[0][0]+SQUAREDIMS <= 960) {
                listCoords[0][0]+=SQUAREDIMS;
            }
            if (std::find(listCoords.begin()+1, listCoords.end(), listCoords[0]) != listCoords.end()) {
                keepGoing = false;
            }
        }
    }
    return keepGoing;
}


//bool SnakeData::moveSnake(char direction) {
//    bool keepGoing = true;
//    if (direction == directions[0] or ((direction == 'u' and directions[0] != 'd') or
//        (direction == 'r' and directions[0] != 'l') or (direction == 'd' and directions[0] != 'u') or (direction == 'l' and directions[0] != 'r'))) {
//        if(!this->gotApple(direction)) {
//            for(int i=directions.size()-1; i>=0; --i) {
//                if(i>1) {
//                    changeDirection(i, directions[i-2]);
//                    listCoords[i][0] = listCoords[i-1][0];
//                    listCoords[i][1] = listCoords[i-1][1];
//                }
//                else if (i>0) {
//                    changeDirection(i, directions[i-1]);
//                    listCoords[i][0] = listCoords[i-1][0];
//                    listCoords[i][1] = listCoords[i-1][1];
//                }
//                else {
//                    changeDirection(i, direction);
//                    if (direction == 'u' and listCoords[i][1]-SQUAREDIMS >=0) {
//                        listCoords[i][1]-=SQUAREDIMS;
//                    }
//                    else if (direction == 'l' and listCoords[i][0]-SQUAREDIMS >= 0) {
//                        listCoords[i][0]-=SQUAREDIMS;
//                    }
//                    else if (direction == 'd' and listCoords[i][1]+SQUAREDIMS <= 960) {
//                        listCoords[i][1]+=SQUAREDIMS;
//                    }
//                    else if (direction == 'r' and listCoords[i][0]+SQUAREDIMS <= 960) {
//                        listCoords[i][0]+=SQUAREDIMS;
//                    }
//                    else {
//                        keepGoing = false;
//                    }
//                }
//            }
//        }
//    }
//    return keepGoing;
//}
