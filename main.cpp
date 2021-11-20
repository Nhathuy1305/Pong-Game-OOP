#include <iostream>
#include <time.h>
#include <conio.h>
using namespace std;

/* Create list of the movement of the ball and define them (mean set their variable to 0,1,...6) 
 -> Meaning of "enum" function. */
enum eDir{
    STOP = 0, 
    LEFT = 1, 
    UPLEFT = 2, 
    DOWNLEFT = 3, 
    RIGHT = 4, 
    UPRIGHT = 5, 
    DOWNRIGHT = 6
};

/*  Class CBall has 9 functions, and 5 variables:
First, focus on the 9 functions:
    - First, the constructor to accept two variables input in integer data types.
    - Function "Reset" to bring the ball come back to the originial position.
    - Function "change_Dirrection" to change the ball direction when it hits the paddle.
    - Function "random_Direction": When the ball hit the paddle, it turn out, so here we set this function to make it direction more complex.
    - Function to getX(), getY() and get the direction get_Direction().
    - Function to set up the movement of the ball (in the eDir list).
    - A friend function to output the position index of the ball in Oxy.  
*/ 
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

// Set the original positon of x and y (mean its direction is stop).
CBall::CBall(int posX, int posY){
    originalX = posX;
    originalY = posY;
    x = posX;
    y = posY;
    direction = STOP;
}

// Reset position of the ball when the game is done (original position).
void CBall::Reset(){
    x = originalX;
    y = originalY;
    direction =STOP;
}

// Set direction for d.
void CBall::change_Direction(eDir d){
    direction = d;
}

// Get x from the private.
inline int CBall::getX(){
    return x;
}

// Get x from the private.
inline int CBall::getY(){
    return y;
}

// Get Direction from the private.
inline eDir CBall::get_Direction(){
    return direction;
}

// Random the dỉrection of the ball when it turns out of the paddle.
void CBall::random_Direction(){
    direction = (eDir) ((rand()%6)+1);
}

// In this function, we use switch..case conditon to set the way for the ball movement basing on the Oxy coordinate.
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
            x--;     // The system runs from left to right and up to down, so the positive direction of x coordinate is from left to right
            y--;     // and the positive direction of y coordinate is up to down.
            break;
        case DOWNLEFT:      //           O ----------------------------> x
            x--;            //            | 
            y++;            //            |       
            break;          //            |         
        case UPRIGHT:       //            |          
            x++;            //            |           
            y--;            //            |           
            break;          //            |                
        case DOWNRIGHT:     //            |  
            x++;            //            |  
            y++;            //            |  
            break;          //            v y 
        default:
            break;
    }
}


/* Class CPaddle use to create object paddle: 
    - Default constructor to set the intitial position for 2 paddles. 
    - Constructor knowing the complete information.
    - When the game finish, the paddle will return to the initial position -> inline void Reset().
    - Function to getX(), getY() in inline integer data types.
    - The paddles will have 2 way of movement:
        + Move up: moveUp().
        + Move down: moveDown().
        Both of them set in inline inline integer data types.
    - A friend function to output the position index of the paddle in Oxy.
*/
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

// Default constructor.
CPaddle::CPaddle(){
    x = y =0;
}

// Constructor to set up the initial position of 2 paddles:
//      The left: x     (posX).
//      The right: y    (posY).
CPaddle::CPaddle(int posX, int posY) : CPaddle(){
    originalX = posX;
    originalY = posY;
    x = posX;
    y = posY;
}

// Reset the paddle coming back the first positon.
inline void CPaddle::Reset(){
    x = originalX;
    y = originalY;
}

// Get x from the private.
inline int CPaddle::getX(){
    return x;
}

// Get y from the private.
inline int CPaddle::getY(){
    return y;
}

// The system run from left to right and up to down, so the positive of y coordinate is up to down.
// The paddle move up: y--.
inline void CPaddle::moveUp(){
    y--;
}

// The paddle move down: y++.
inline void CPaddle::moveDown(){
    y++;
}

/* In this class, we use the pointer to establish for 3 objects: Ball, Paddle 1 and Paddle 2.
    In the private class, we declare:
        width, height, score1, score2.
        The quit in boolean data type.
    In the public:
        - Constructor to input variable.
        - When the game finish and refresh into the new chapter, we have to use the destructor to delete the 3 objects.
        - Function Score_Up to score the result (increase) whenever 1 of 2 players win.
        - Draw() function mean design the template of the play area: paddles, ball, frame collums and rows of the area.
*/
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
    getch();
    return 0;
}