#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/

int main()
{

    // game loop
    while (1) {
        int x;
        int y;
        int nextCheckpointX; // x position of the next check point
        int nextCheckpointY; // y position of the next check point
        int nextCheckpointDist; // distance to the next checkpoint
        int nextCheckpointAngle; // angle between your pod orientation and the direction of the next checkpoint
        cin >> x >> y >> nextCheckpointX >> nextCheckpointY >> nextCheckpointDist >> nextCheckpointAngle; cin.ignore();
        bool boostAvailable;

        // Write an action using cout. DON'T FORGET THE "<< endl"
        // To debug: cerr << "Debug messages..." << endl;
        cout << nextCheckpointX << " " << nextCheckpointY << " ";
        if(nextCheckpointAngle > 90 || nextCheckpointAngle < -90)
        {
            cout << "0";
        }
        else
        {
            if(nextCheckpointDist > 6000 && boostAvailable)
            {
                cout << "BOOST";
            }
            else
            {
                cout << "100";
            }
        }


        // You have to output the target position
        // followed by the power (0 <= thrust <= 100)
        // i.e.: "x y thrust"
         cout << endl;
    }
}