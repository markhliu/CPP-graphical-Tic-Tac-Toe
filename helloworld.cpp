
#include <iostream>
#include <stdio.h>
#include <sstream> 
#include "CTurtle.hpp"

using namespace std;

namespace ct = cturtle;




int center[9][2] = { {-200, -200}, {0, -200}, {200, -200},{-200, 0},  {0, 0},  {200, 0},{-200, 200},  {0, 200},  {200, 200} };
string turn[2] = { "x", "o"};
string cl[9] = { "1","2","3","4","5","6","7","8","9" };

ct::TurtleScreen scr(600, 600);
ct::Turtle turtle(scr);


int board(ct::Turtle& turtle) {


    for (int i = -100; i <= 100; i += 200) {

        turtle.penup();
        turtle.goTo(i, -300);
        turtle.pendown();
        turtle.goTo(i, 300);
        turtle.penup();
        turtle.goTo(-300, i);
        turtle.pendown();
        turtle.goTo(300, i);
        turtle.penup();
    };

    for (int i = 0; i < 9; i++) {

        turtle.goTo(center[i][0] - 80, center[i][1] - 80);

        turtle.write(to_string(i + 1));
    };

    return 0;
}


int mark_cell(int cell) {


    try
    {

        scr.update();
        if (turn[0] == "x") {
            turtle.pencolor({ "gray" });
            turtle.penup();
            turtle.goTo(center[cell - 1][0] - 75, center[cell - 1][1] - 75);
            turtle.pendown();
            turtle.goTo(center[cell - 1][0] + 75, center[cell - 1][1] + 75);
            turtle.penup();
            turtle.goTo(center[cell - 1][0] + 75, center[cell - 1][1] - 75);
            turtle.pendown();
            turtle.goTo(center[cell - 1][0] - 75, center[cell - 1][1] + 75);
            turtle.penup();
            turn[0] = "o";
            turn[1] = "x";
        }
        else {
            turtle.penup();
            turtle.goTo(center[cell - 1][0], center[cell - 1][1]);
            turtle.circle(80, 360, { "gray" });
            turn[0] = "x";
            turn[1] = "o";
        }


    }
    catch (exception e)
    {
        cout << e.what();
    }




    return 0;
}

bool check_win() {
    bool flag = false;
    if (cl[0] == turn[0] && cl[0] == cl[1] && cl[0] == cl[2]) flag = true;
    if (cl[3] == turn[0] && cl[3] == cl[4] && cl[3] == cl[5]) flag = true;
    if (cl[6] == turn[0] && cl[6] == cl[7] && cl[6] == cl[8]) flag = true;
    if (cl[0] == turn[0] && cl[0] == cl[3] && cl[0] == cl[6]) flag = true;
    if (cl[0] == turn[0] && cl[0] == cl[4] && cl[0] == cl[8]) flag = true;
    if (cl[2] == turn[0] && cl[2] == cl[4] && cl[2] == cl[6]) flag = true;
    if (cl[1] == turn[0] && cl[1] == cl[4] && cl[1] == cl[7]) flag = true;
    if (cl[2] == turn[0] && cl[2] == cl[5] && cl[2] == cl[8]) flag = true;
    return flag;
}

bool check_tie() {
    bool flag = false;
    if (cl[0] != "1" && cl[1] != "2" && cl[2] != "3" && cl[3] != "4" && cl[4] != "5" &&
        cl[5] != "6" && cl[6] != "7" && cl[7] != "8" && cl[8] != "9") flag = true;
    return flag;
}

int main() {


    scr.bgcolor({ "azure" });
    turtle.width(3);
    turtle.hideturtle();
    turtle.speed(ct::TS_FASTEST);



    board(turtle);
    string inp;
    do {
        cout <<"Player "<<turn[0]<< ", what's your move?\n";
        cin >> inp;
        if (inp == "1" | inp == "2" | inp == "3" | inp == "4" | inp == "5" | inp == "6" | inp == "7" | inp == "8" | inp == "9") {
            stringstream geek(inp);
            int idx;
            geek >> idx;
            if (cl[idx - 1] == inp) {
                mark_cell(idx);
                cl[idx - 1] = turn[0];
                if (check_win() == true) { cout << "Player " << turn[1] << " won" << endl; break; }
                else if (check_tie() == true) { cout << "game over, it's a tie" << endl; break; }
            }
            else { cout << "invalid move" << endl; };

        }
        else
        {
            cout << "use a number between 1 and 9 " << endl;
        }
    } while (inp != "exit");




    scr.update();



    scr.exitonclick();
    return 0;
}
