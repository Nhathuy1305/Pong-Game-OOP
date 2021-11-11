#include <iostream>
#include <time.h>
#include <conio.h>
using namespace std;

//Create list of movement of the ball
enum eDir{
    STOP = 0, 
    LEFT = 1, 
    UPLEFT = 2, 
    DOWNLEFT = 3, 
    RIGHT = 4, 
    UPRIGHT = 5, 
    DOWNRIGHT = 6
};

class CBall{
    private:
        int x,y;
        int originalX, originalY;
        eDir direction;
    public:
        CBall(int, int);
        void Reset();
        void change_Direction(eDir);
        void random_Direction();
        inline int getX();
        inline int getY();
        inline eDir get_Direction();
        void Move();
        friend ostream& operator<<(ostream &os, CBall &b){
            os << "Ball [" << b.x << "," << b.y << "][" << b.direction << "]";
            return os;
        }        
};

CBall::CBall(int posX, int posY){
    originalX = posX;
    originalY = posY;
    x = posX;
    y = posY;
    direction = STOP;
}

void CBall::Reset(){
    x = originalX;
    y = originalY;
    direction =STOP;
}

void CBall::change_Direction(eDir d){
    direction = d;
}

inline int CBall::getX(){
    return x;
}

inline int CBall::getY(){
    return y;
}

inline eDir CBall::get_Direction(){
    return direction;
}

void CBall::random_Direction(){
    direction = (eDir) ((rand()%6)+1);
}

void CBall::Move(){
    switch(direction){
        case STOP:
            break;
        case LEFT:
            x--;
            break;
        case RIGHT:
            x++;
            break;
        case UPLEFT:
            x--;
            y--;
            break;
        case DOWNLEFT:
            x--;
            y++;
            break;
        case UPRIGHT:
            x++;
            y--;
            break;
        case DOWNRIGHT:
            x++;
            y++;
            break;
        default:
            break;
    }
}

class CPaddle{
    private:
        int x,y;
        int originalX, originalY;
    public:
        CPaddle();
        CPaddle(int,int);
        inline void Reset();
        inline int getX();
        inline int getY();
        inline void moveUp();
        inline void moveDown();
        friend ostream& operator<<(ostream &os, CPaddle &b){
            os << "Paddle [" << b.x << "," << b.y << "]";
            return os;
        }
};

CPaddle::CPaddle(){
    x = y =0;
}

CPaddle::CPaddle(int posX, int posY) : CPaddle(){
    originalX = posX;
    originalY = posY;
    x = posX;
    y = posY;
}

inline void CPaddle::Reset(){
    x = originalX;
    y = originalY;
}

inline int CPaddle::getX(){
    return x;
}

inline int CPaddle::getY(){
    return y;
}

inline void CPaddle::moveUp(){
    y--;
}

inline void CPaddle::moveDown(){
    y++;
}

class CGameManager{
    private:
        int width,height;
        int score1, score2;
        char up1, down1, up2, down2;
        bool quit;
        CBall * ball;
        CPaddle *player1;
        CPaddle *player2;
    public:
    CGameManager(int, int);
    ~CGameManager();
    void Score_Up(CPaddle*);
    void Draw();
    void input();
    void logic();
    void run();
};

CGameManager::CGameManager(int w, int h){
    srand(time(NULL));
    quit = false;
    up1 = 'w';
    up2 = 'i';
    down1 = 's';
    down2 = 'k';
    score1 = score2 = 0;
    width = w;
    height = h;
    ball = new CBall(w/2, h/2);
    player1 = new CPaddle(1, h/2 - 3);
    player2 = new CPaddle(w-2, h/2 - 3);    
}

CGameManager::~CGameManager(){
    delete ball, player1, player2;
}

void CGameManager::Score_Up(CPaddle * player){
    if(player == player1) score1++;
    else if (player == player2) score2++;

    ball -> Reset();
    player1->Reset();
    player2->Reset();
}

void CGameManager::Draw(){
    system("cls");    //cls = clear
    for(int i = 0; i < width+2; i++)
        cout << "\xB2";
    cout << endl;

    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            int ballx = ball->getX();
            int bally = ball->getY();
            int player1x = player1->getX();
            int player2x = player2->getX();
            int player1y = player1->getY();
            int player2y = player2->getY();

            if(j == 0) cout << "\xB2";

            if (ballx == j && bally == i) cout << "O";
            else if (player1x == j && player1y == i) cout << "\xDB";  //player1   
            else if (player2x == j && player2y == i) cout << "\xDB";  //player2
            
            else if (player1x == j && player1y + 1 == i) cout << "\xDB";  //player1   
            else if (player1x == j && player1y + 2 == i) cout << "\xDB";  //player1   
            else if (player1x == j && player1y + 3 == i) cout << "\xDB";  //player1   

            else if (player2x == j && player2y + 1 == i) cout << "\xDB";  //player2
            else if (player2x == j && player2y + 2 == i) cout << "\xDB";  //player2
            else if (player2x == j && player2y + 3 == i) cout << "\xDB";  //player2
            else cout << " ";

            if (j == width - 1) cout << "\xB2";
        }
        cout << endl;
    }

    for(int i = 0; i < width+2; i++)
        cout << "\xB2"; 
    cout << endl;

    cout << "Score 1: " << score1 << endl << "Score 2: " << score2 << endl;  
}

void CGameManager::input(){
    ball->Move();

    int ballx = ball->getX();
    int bally = ball->getY();
    int player1x = player1->getX();
    int player2x = player2->getX();
    int player1y = player1->getY();
    int player2y = player2->getY();

    if(_kbhit()){
        char current = _getch();
        if (current == up1)
            if (player1y > 0)
                player1->moveUp();
        if (current == up2)
            if (player2y > 0)
                player2->moveUp();
        if (current == down1)
            if (player1y + 4 < height)
                player1->moveDown();
        if (current == down2)
            if (player2y + 4 < height)
                player2->moveDown();

        if(ball->get_Direction() == STOP)
            ball->random_Direction();

        if (current == 'q')
            quit = true;  
    }
}

void CGameManager::logic(){
    int ballx = ball->getX();
    int bally = ball->getY();
    int player1x = player1->getX();
    int player2x = player2->getX();
    int player1y = player1->getY();
    int player2y = player2->getY();

    //left paddle
    for(int i = 0; i < 4; i++)
        if (ballx == player1x + 1)
            if (bally == player1y + i)
                ball->change_Direction((eDir)((rand()%3)+4));

    //right paddle
    for(int i = 0; i < 4; i++)
        if (ballx == player2x - 1)
            if (bally == player2y + i)
                ball->change_Direction((eDir)((rand()%3)+1));

    //bottom wall
    if (bally == height - 1)
        ball->change_Direction(ball->get_Direction() == DOWNRIGHT ? UPRIGHT : UPLEFT);
    //top wall
    if (bally == 0)
        ball->change_Direction(ball->get_Direction() == UPRIGHT ? DOWNRIGHT : DOWNLEFT);
    //right wall
    if (ballx == width - 1)
        Score_Up(player1);
    //left wall
    if (ballx == 0)
        Score_Up(player2);
}                        

void CGameManager::run(){
    while (!quit){
        Draw();
        input();
        logic();
    }
}

int main(){
    CGameManager c(40,20);
    c.run();
    return 0;
}