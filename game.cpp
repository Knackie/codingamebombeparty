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
    int width;
    int height;
    int my_id;
    cin >> width >> height >> my_id; cin.ignore();

    // game loop
    while (1) {
        for (int i = 0; i < height; i++) {
            string row;
            cin >> row; cin.ignore();
        }
        int entities;
        cin >> entities; cin.ignore();
        for (int i = 0; i < entities; i++) {
            int entity_type;
            int owner;
            int x;
            int y;
            int param_1;
            int param_2;
            cin >> entity_type >> owner >> x >> y >> param_1 >> param_2; cin.ignore();
        }

        // Write an action using cout. DON'T FORGET THE "<< endl"
        // To debug: cerr << "Debug messages..." << endl;

        cout << "BOMB 6 5" << endl;
    }
}
