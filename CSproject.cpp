#include <iostream>
#include <stdlib.h>
#include <conio.h> //getcharacter, clears screen
#include <windows.h> //gotoxy, sleep function
#include <chrono>
#include <thread>
using namespace std;

void gotoxy(int x, int y);//go to any column from 0 to 88 and any row  0 to 22, predefined code from internet
void choices(); //Main Screen - printed before the game starts
void cactus(int &s,int &score);//Moves cactus from right to left
void dino_print();//Prints a Dino when it is not jumping i.e at (0,0)
void dino(int &t);//Prints the jumping Dino while simultaneously removes the previously printed Dino, line by line.
void dino_jump(bool &check);//Contains the commands which control the movement of Dino

int x,t;//Global variables to run the movement functions for both Cactus and Dino
bool runner;//Bool to cycle between the Main and the game screen

int main()
{
                        //********************MAIN SCREEN FUNCTION*********************//

    choices();//Calls the Main screen function


                        //********************DINO MAIN FUNCTION**********************//

    bool once = true; // To print Dino once every time the game runs - To prevent glitches
    bool check; // To initiate the jump function
    int s=40; //Initial speed value
    int score=0; //Initializes score to 0

    while(runner)
    {

        system("Color 1F");//Changes the color theme to the actual classic chrome Dino game

        gotoxy(10,2);
        cout<<"Press X to Exit, Press Space to Jump";//Prints gaming instructions
        gotoxy(62,2);
        cout<<"TOTAL SCORE : ";//Displays the user score
        gotoxy(1,30);
        for(int i=0;i<79;i++) //Prints the grass (the base of this game)
        cout<<"^";

        std::thread t1(cactus,std::ref(s),std::ref(score)); //calling cactus using thread
        do
        {
            dino_print();

            once = false;
        }while(once); //Prints the Dino once before the game starts
        dino_print(); //Prints it again to remove the glitches

        char jump; //Variable that takes the input from user. If SpaceBar then runs the Dino thread
        do
        {
            jump = getch();//Keeps taking in input without enter being pressed
            if (jump != ' ')//Input Validation - Displays an error message for 150 milliseconds on the screen
            {
                gotoxy(50,11);
                cout<<"Error. Incorrect Character";
                Sleep(150);
                gotoxy(50,11);
                cout<<"                                    ";
            }
        }while(jump!=' ');

        if(jump == ' ')//Implements the jump action if SpaceBar is pressed
        {
            check = true;
            if (s>5) //Speed of cactus
            s=s-5;
            std::thread t2(dino_jump,std::ref(check)); //calling dino_jump using thread
            t1.join(); //Calling for end of cactus thread
            t2.join(); //Calling for end of Dino thread
            score=score+1; //Updating score
            gotoxy(70,2);
            cout<<score; //Outputs score, which keeps incrementing after 1 successful jump
        }

    }


}
                    //*****************FUNCTION CALLS*******************//
void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void choices()
{
    string choice;//Takes in User input at the Main screen
    do
    {
        //Main screen design//
        gotoxy(30,4);
        cout<<"************************************************************"<<endl;
        gotoxy(30,5);
        cout<<"************************************************************"<<endl;
        gotoxy(30,6);
        cout<<"**                                                        **"<<endl;
        gotoxy(30,7);
        cout<<"**                 Welcome To The Dino Game               **"<<endl;
        gotoxy(30,8);
        cout<<"**                                                        **"<<endl;
        gotoxy(30,9);
        cout<<"**             1) Press 1 to START the game               **"<<endl;
        gotoxy(30,10);
        cout<<"**             2) Press 2 to Exit                         **"<<endl;
        gotoxy(30,11);
        cout<<"**             3) Enter Your Choice =                     **"<<endl;
        gotoxy(30,12);
        cout<<"**                                                        **"<<endl;
        gotoxy(30,13);
        cout<<"**                                                        **"<<endl;
        gotoxy(30,14);
        cout<<"************************************************************"<<endl;
        gotoxy(30,15);
        cout<<"************************************************************"<<endl;
        gotoxy(70,11);
        cin>>choice;


if(choice != "1" && choice != "2") //Displays "INCORRECT INPUT" (for 500 milliseconds) if the value entered does not match the criteria
{
        gotoxy(30,13);
        cout<<"**                                       Incorrect Input  **"<<endl;
        Sleep(500);
}
if (choice == "1") //If value entered is 1, The game starts running
{
    runner = true;
    system("CLS");

}
else if (choice == "2") //If 2 the game ends
{
    runner = false;
    system("CLS");
    gotoxy(50,10);
    cout<<"THANK YOU!!!!";
    Sleep(500); // Displays the Thank you message for 500 Milliseconds before the program ends
    break;
}

}while(choice!="1" && choice!="2"); // Keeps the loop running until the user enters a valid input

}
void cactus(int &s,int &score)
{
    for (x=0;x<80;x++) // Moves the cactus
    {
        gotoxy(74-x,26);
        cout<<(" *| |* ");
        gotoxy(74-x,27);
        cout<<(" ||_|| ");
        gotoxy(74-x,28);
        cout<<(" ***** ");
        gotoxy(74-x,29);
        cout<<("  ||| " );
        Sleep(s); //speed of cactus
        gotoxy(76,2);
        cout<<score<<"     "; // Outputs score
    }
}
void dino_print()
{
   //***********Dino Design**********//
    gotoxy(2,17);
    cout<<("                                   ");
    gotoxy(2,18);
    cout<<("                                   ");
    gotoxy(2,19);
    cout<<("                                   ");
    gotoxy(2,20);
    cout<<("          *******                  ");
    gotoxy(2,21);
    cout<<("         *****O**                  ");
    gotoxy(2,22);
    cout<<("         *******                   ");
    gotoxy(2,23);
    cout<<(" *      ********                   ");
    gotoxy(2,24);
    cout<<(" ***  *********                    ");
    gotoxy(2,25);
    cout<<("-************                      ");
    gotoxy(2,26);
    cout<<(" --*********                       ");
    gotoxy(2,27);
    cout<<(" ---**  **                         ");
    gotoxy(2,28);
    cout<<(" ---**  **                         ");
    gotoxy(2,29);
    cout<<("    []  []                         ");
    gotoxy(2,30);
    cout<<("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^");

}
void dino(int &t)
{
    //Prints a jumping Dino while simultaneously removing the previously printed one (By printing blank lines)
    gotoxy(2,17-t);
    cout<<("                                   ");
    gotoxy(2,18-t);
    cout<<("                                   ");
    gotoxy(2,19-t);
    cout<<("                                   ");
    gotoxy(2,20-t);
    cout<<("          *******                  ");
    gotoxy(2,21-t);
    cout<<("         *****O**                  ");
    gotoxy(2,22-t);
    cout<<("         *******                   ");
    gotoxy(2,23-t);
    cout<<(" *      ********                   ");
    gotoxy(2,24-t);
    cout<<(" ***  *********                    ");
    gotoxy(2,25-t);
    cout<<("-************                      ");
    gotoxy(2,26-t);
    cout<<(" --*********                       ");
    gotoxy(2,27-t);
    cout<<(" ---**  **                         ");
    gotoxy(2,28-t);
    cout<<(" ---**  **                         ");
    gotoxy(2,29-t);
    cout<<("    []  []                         ");
    gotoxy(2,30-t);
    if(t==0)
    {
    cout<<("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^");
    }
    else
    {
    cout<<("                                   ");
    }
    if ((t>=0 && t<5) && (x>66 && x<72)) //Ends game if the cactus's position coincides with Dino's Position
    {
        string play;
        runner = false;
        system("CLS"); //Clears screen
        gotoxy(50,11);
        cout<<"Game Over"; //Displays the New Screen
        gotoxy(32,15);
        cout<<"Press 1 To play again or ANY other key to exit";
        gotoxy(50,17);
        cin>>play;
        if (play == "1")
        {
            system("CLS"); //Clears previous screen
            runner = true; //Runs the game again

        }
        else
        {
            system("CLS"); //Clears previous screen
            gotoxy(50,11);
            cout<<"Game Over"; // Still outputs the same message for 200 Milliseconds before the game ends
            Sleep(200);
            abort(); // Ends the game
        }
    }
}
void dino_jump(bool &check)
{
    int y=0;
    while(check) //This is true when SpaceBar is pressed
    {
        if (y<8) //Makes the Dino jump from ground to y = 8
            {
                for (y;y<8;y++)
                {
                    dino(y);
                    Sleep(50); //Prints the new Dino after 50 Milliseconds for smoother and visible trasition
                 }
            }
        if (y>=8) // Brings the Dino back from Max height to the ground
            {
                for (y;y>=0;y--)
                {
                    dino(y);
                    Sleep(50); //Prints the new Dino after 50 Milliseconds for smoother and visible trasition
                }
            }
        check = false; //Ends the while loop
    }
}
