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

/* 
   In this class, we use the pointer to establish for 3 objects: Ball, Paddle 1 and Paddle 2.
    In the private class, we declare:
        width, height, score1, score2.
        The quit in boolean data type.
    In the public:
        - Constructor to input variable.
        - When the game finish and refresh into the new chapter, we have to use the destructor to delete the 3 objects.
        - Function Score_Up to score the result (increase) whenever 1 of 2 players win.
        - Draw() function mean design the template of the play area: paddles, ball, frame columns and rows of the area.
        - Funtion input() for the user interact with the game approving keyboards (Type the keyboards then the paddle moving/game starts).
        - Logic(): change direction of the ball (interact between ball and paddle) divided into 2 part: left and right. 
        - Run() function to call 3 function: Draw(), Input(), Logic(), respectively.
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

// Constructors to create w, h in integer data types
CGameManager::CGameManager(int w, int h){
    // Set random number seed, to create a random number that do not coincide evertime the system iterative: srand(time(NULL)). 
    // (Ex: the first time is 1, the second will not meet 1 again, neither the third,...).
    srand(time(NULL));   
    quit = false;   // Set up quit when the program is false, stop.
    up1 = 'w';
    up2 = 'i';
    down1 = 's';
    down2 = 'k';
    score1 = score2 = 0;           // The initial result of 2 players.
    width = w;
    height = h;
    ball = new CBall(w/2, h/2);     // Create new ball by constructor on line 49.
    player1 = new CPaddle(1, h/2 - 3);    // Create new left paddle. 
    player2 = new CPaddle(w-2, h/2 - 3);    // Create new right paddle.
}

// Destructor clear 3 objects when 1 of 2 players let the ball get out of range.
CGameManager::~CGameManager(){
    delete ball, player1, player2;   
}

// Score points for each players:
/* 
    Rules:
        - 2 players start moving own paddle, and spike the ball.
        - If 1 of them cannot spikes it and let the ball get out of play area, the function score will chalk up
          for the other one (1 point).      
*/
void CGameManager::Score_Up(CPaddle * player){
    if(player == player1) score1++;                    // If 1 of 2 object: player1/player2 equal to pointer player -> Score point.
    else if (player == player2) score2++;

    ball -> Reset();                       // Score points then reset 3 objects: ball, player1, player2.
    player1->Reset();
    player2->Reset();
}

void CGameManager::Draw(){
    system("cls");                       //cls = clear
    for(int i = 0; i < width+2; i++)
        cout << "\xB2";                  // \xB2 is symbol: Start -> Run -> Type "charmap" -> Choose symbol then look in the left bottom.
    cout << endl;

    // Draw
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            int ballx = ball->getX();         // Set objective for ball (x,y).
            int bally = ball->getY();         
            int player1x = player1->getX();     // Set objective for paddle (x,y).
            int player2x = player2->getX();
            int player1y = player1->getY();
            int player2y = player2->getY();

            if(j == 0) cout << "\xB2";           // Draw paddle left.

            
            if (ballx == j && bally == i) cout << "O";  // Draw ball
            else if (player1x == j && player1y == i) cout << "\xDB";  //player1      // Draw 2 rows.
            else if (player2x == j && player2y == i) cout << "\xDB";  //player2
            
            else if (player1x == j && player1y + 1 == i) cout << "\xDB";  //player1     
            else if (player1x == j && player1y + 2 == i) cout << "\xDB";  //player1   
            else if (player1x == j && player1y + 3 == i) cout << "\xDB";  //player1   

            else if (player2x == j && player2y + 1 == i) cout << "\xDB";  //player2      
            else if (player2x == j && player2y + 2 == i) cout << "\xDB";  //player2
            else if (player2x == j && player2y + 3 == i) cout << "\xDB";  //player2
            else cout << " ";

            if (j == width - 1) cout << "\xB2";  // Draw paddle right.
        }
        cout << endl;
    }

    for(int i = 0; i < width+2; i++)
        cout << "\xB2";                // Draw row bottom.
    cout << endl;

    cout << "Score 1: " << score1 << endl << "Score 2: " << score2 << endl;   // Print out the result of 2 players.
}

void CGameManager::input(){
    ball->Move();

    int ballx = ball->getX();
    int bally = ball->getY();
    int player1x = player1->getX();
    int player2x = player2->getX();
    int player1y = player1->getY();
    int player2y = player2->getY();

    // The _kbhit function checks the console for a recent keystroke. 
    // If the function returns a nonzero value, a keystroke is waiting in the buffer. 
    if(_kbhit()){
        char current = _getch();       // On line 232 -> 235, the valid characters on the keyboard to move the paddle is 'w','s','i','k'.
        if (current == up1)                     
            if (player1y > 0)
                player1->moveUp();     // w
        if (current == up2)
            if (player2y > 0)
                player2->moveUp();     // i
        if (current == down1)
            if (player1y + 4 < height)
                player1->moveDown();   // s
        if (current == down2)
            if (player2y + 4 < height)
                player2->moveDown();   // k

        if(ball->get_Direction() == STOP)
            ball->random_Direction();   // The game stop when the user do not type anything from keyboard.

        if (current == 'q')
            quit = true;               // Type 'q' to stop
    }
}

void CGameManager::logic(){
    int ballx = ball->getX();
    int bally = ball->getY();
    int player1x = player1->getX();
    int player2x = player2->getX();
    int player1y = player1->getY();
    int player2y = player2->getY();

    // left paddle
    // The ball hit the paddle then it change its direction in 3 random ways.  
    for(int i = 0; i < 4; i++)
        if (ballx == player1x + 1)
            if (bally == player1y + i)
                ball->change_Direction((eDir)((rand()%3)+4));    

    // right paddle
    // The ball hit the paddle then it change its direction in 3 random ways.
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
        Score_Up(player1);            // If ball get out of play area on the right (width - 1) -> Score for 1.
    //left wall
    if (ballx == 0)
        Score_Up(player2);            // If ball get out of play area on the left (0) -> Score for 2. 
}                        

// Run the program.
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