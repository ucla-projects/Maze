#include "grid.h"
#include <iostream>
#include <cassert>
#include <cctype>
using namespace std;

void updateLocation(char dir, int &r, int &c);
int changeCharToInt(char digit);
bool parseSegment(string path, int& digit, char& direction);

bool isPathWellFormed(string path)
{
    int k = 0;
    while ( k != path.size() ) // used while-loop to check for digits
    {
        if (isdigit(path[k])) // if first character is digit
        {
            k++;
            if (isdigit(path[k])) // if second character is digit
            {
                k++;
                if (isdigit(path[k])) // if third character is digit, error
                    return false;
                if (! isdigit(path[k])) // if third character is not digit, go thru switch
                    switch (path[k]) // make sure path has one of the following letters
                    {
                    case 'N':
                    case 'n':
                    case 'E':
                    case 'e':
                    case 'W':
                    case 'w':
                    case 'S':
                    case 's':
                        break;
                    default:  // Step doesn't have  N, E, W, or S, so error
                        return false;
                    }
            }
            else // if second character is not digit, go thru switch
                switch (path[k])
                {
                    case 'N':
                    case 'n':
                    case 'E':
                    case 'e':
                    case 'W':
                    case 'w':
                    case 'S':
                    case 's':
                        break;
                    default:  // Step doesn't have N, E, W, or S, so error
                        return false;
                }
            k++;
        }
        else // if first character is not digit, error
            return false;
    }
    return true;
}

int traverseSegment(int r, int c, char dir, int maxSteps)
{
    if (isWall(r,c)) // if starting position is wall, return -1
    {
        return -1;
    }
    
    int steps = 0;
    while (steps < maxSteps)
           // continue when position is inside and steps are less than maximum steps
    {
        updateLocation(dir, r, c);
        if (r > getRows() || r < 1 || c < 1 || c > getCols() || isWall(r,c))
        {
            break;
        }
        steps++;
    }
    return steps;
    
    if (steps > maxSteps)
        return maxSteps;
    
    if (dir != 'E' && dir != 'e' && dir != 'W' && dir != 'w' && dir != 'N' && dir != 'n' && dir != 'S' && dir != 's') // if dir is not E,e,W,w,N,n,S,s, return -1
    {
        return -1;
    }
    if (maxSteps < 0) // if maxSteps is negative, return -1
    {
        return -1;
    }
}

void updateLocation(char dir, int &r, int &c)
{
    if (dir == 'E' || dir == 'e') // if E or e, add 1 to c coordinate
    {
        c++;
    }
    if (dir == 'W' || dir == 'w') // if W or w, subtract 1 from c coordinate
    {
        c--;
    }
    if (dir == 'N' || dir == 'n') // if N or n, add 1 to r coordinate
    {
        r--;
    }
    if (dir == 'S' || dir == 's') // if S or s, subtract 1 from r coordinate
    {
        r++;
    }
}


int changeCharToInt(char digit) // used to change char to int
{
    int number = digit - '0';
    return number;
}


bool parseSegment(int& j, string path, int& digit, char& direction) // parse Segment, '2n' to '2' & 'n'
{
    string newSegment;
    int digit1;
    int digit2;
    if( isdigit(path[j]) )
    {
        if ( isdigit(path[j+1]) )
        {
            char c = path[j];   // will take segments when there's 2 numbers
            digit1 = changeCharToInt(c);
            char d = path[j+1];
            digit2 = changeCharToInt(d);
            digit = (digit1 * 10) + digit2;
            j++;
        }
        else
        {
            char c = path[j];   // will take segments when there's 1 number
            digit = changeCharToInt(c);
        }
        j++;
    }
    direction = path[j]; // this path[j] has to be a direction
    j++;
    return true;
}


int traversePath(int sr, int sc, int er, int ec, string path, int& nsteps)
{
    if ( isWall(sr,sc) || isWall(er,ec) || ! isPathWellFormed(path) ) // makes sure path is valid
        return 3;
    int digit = 0;
    char dir = ' ';
    nsteps = 0;
    int j = 0;
    for (int k = 0; k != path.size(); k++)
    {
        string segment = ""; // create empty string named segment
        if (isdigit(path[k]))
        {
            segment += path[k]; // add number to string
            k++;
            
            if (isdigit(path[k]))
            {
                segment += path[k]; // add number to string
                k++;
                segment += path[k]; // add letter to string
            }
            else
            {
                segment += path[k]; // add letter to string
            }
        }
    parseSegment(j, path, digit, dir);

    if (traverseSegment(sr, sc, dir, digit) == digit)
    {
        nsteps += digit; // if path can be taken, add number of steps
    }
    else
    {
        nsteps += traverseSegment(sr, sc, dir, digit);
        return 2; // if path can't be fully taken, add number of valid steps
    }
    
    if (dir == 'E' || dir == 'e') // if E or e, add 1 to sc coordinate
    {
        sc += digit;
    }
    if (dir == 'W' || dir == 'w') // if W or w, subtract 1 from sc coordinate
    {
        sc -= digit ;
    }
    if (dir == 'N' || dir == 'n') // if N or n, add 1 to sr coordinate
    {
        sr -= digit;
    }
    if (dir == 'S' || dir == 's') // if S or s, subtract 1 from sr coordinate
    {
        sr += digit;
    }
    }
    
    if ((sr == er) && (sc == ec)) // if starting goes to ending point, return 0
        return 0;
    else return 1;
        
}