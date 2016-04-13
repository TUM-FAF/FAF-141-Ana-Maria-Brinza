
#define ID_TIMER 100

using namespace std;

class animationB{


public:
    POINT center;
    int SpeedX,SpeedY;

    animationB(POINT center,const int &speed);
    bool accelerateB(const int& DSpeedX,const int& DSpeedY);
    bool BallColor(const COLORREF &Bcolor);
    bool BallCollision(const RECT &rect);
    bool transBall = false; //form circle to rectangle
    virtual bool moveB(const HDC &hdc,const RECT& rect,HBRUSH &hBrush)=0;

protected:
    COLORREF Bcolor;
};

class Circle : public animationB {
public:
    Circle(POINT center,const int &speed): animationB(center,speed)
    {
    }
    bool moveB(const HDC &hdc,const RECT& rect,HBRUSH &hBrush);
};
    bool Interaction(animationB &first,animationB &second);
