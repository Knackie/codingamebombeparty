
#include <iostream>

#include <string>

#include <vector>

#include <queue>

#include <climits>

using namespace std;



struct Position {

    int x, y;



    bool operator==(const Position& other) const {

        return x == other.x && y == other.y;

    }



    Position operator+(const Position& other) const {

        return {x + other.x, y + other.y};

    }

};



bool is_valid_position(const Position& pos, int width, int height) {

    return pos.x >= 0 && pos.x < width && pos.y >= 0 && pos.y < height;

}



bool is_in_bomb_range(const Position& pos, const Position& bomb_pos, int bomb_range) {

    return (pos.x == bomb_pos.x && abs(pos.y - bomb_pos.y) <= bomb_range) ||

           (pos.y == bomb_pos.y && abs(pos.x - bomb_pos.x) <= bomb_range);

}



bool is_reachable(const vector<string>& grid, Position start, Position target, int width, int height) {

    queue<Position> q;

    vector<vector<bool>> visited(height, vector<bool>(width, false));

    q.push(start);

    visited[start.y][start.x] = true;



    while (!q.empty()) {

        Position current = q.front();

        q.pop();



        if (current == target) return true;



        for (const auto& dir : vector<Position>{{-1, 0}, {1, 0}, {0, -1}, {0, 1}}) {

            Position neighbor = current + dir;

            if (is_valid_position(neighbor, width, height) && grid[neighbor.y][neighbor.x] == '.' && !visited[neighbor.y][neighbor.x]) {

                q.push(neighbor);

                visited[neighbor.y][neighbor.x] = true;

            }

        }

    }

    return false;

}



Position find_position_A(const vector<string>& grid, Position start, int width, int height, const vector<pair<Position, int>>& bombs) {

    queue<Position> q;

    vector<vector<bool>> visited(height, vector<bool>(width, false));

    q.push(start);

    visited[start.y][start.x] = true;



    while (!q.empty()) {

        Position current = q.front();

        q.pop();



        if (grid[current.y][current.x] == '.') {

            bool safe = true;

            for (const auto& [bomb_pos, range] : bombs) {

                if (is_in_bomb_range(current, bomb_pos, range)) {

                    safe = false;

                    break;

                }

            }

            if (safe) {

                for (const auto& dir : vector<Position>{{-1, 0}, {1, 0}, {0, -1}, {0, 1}}) {

                    Position neighbor = current + dir;

                    if (is_valid_position(neighbor, width, height) &&

                        (grid[neighbor.y][neighbor.x] == '0' || (grid[neighbor.y][neighbor.x] >= '1' && grid[neighbor.y][neighbor.x] <= '9'))) {

                        cerr << "Valid position A found at: (" << current.x << ", " << current.y << ") next to crate at: ("

                             << neighbor.x << ", " << neighbor.y << ")" << endl;

                        return current;

                    }

                }

            }

        }



        for (const auto& dir : vector<Position>{{-1, 0}, {1, 0}, {0, -1}, {0, 1}}) {

            Position neighbor = current + dir;

            if (is_valid_position(neighbor, width, height) && grid[neighbor.y][neighbor.x] != 'X' && !visited[neighbor.y][neighbor.x]) {

                q.push(neighbor);

                visited[neighbor.y][neighbor.x] = true;

            }

        }

    }



    cerr << "No valid position A found after exhaustive search." << endl;

    return {-1, -1};

}



Position find_position_A_attack_mode(const vector<string>& grid, Position start, Position target, int width, int height) {

    queue<Position> q;

    vector<vector<bool>> visited(height, vector<bool>(width, false));

    q.push(start);

    visited[start.y][start.x] = true;



    while (!q.empty()) {

        Position current = q.front();

        q.pop();



        if (current == target) return current;  // Cible atteinte



        for (const auto& dir : vector<Position>{{-1, 0}, {1, 0}, {0, -1}, {0, 1}}) {

            Position neighbor = current + dir;

            if (is_valid_position(neighbor, width, height) && grid[neighbor.y][neighbor.x] == '.' && !visited[neighbor.y][neighbor.x]) {

                q.push(neighbor);

                visited[neighbor.y][neighbor.x] = true;

            }

        }

    }



    cerr << "No valid position found to approach target in attack mode." << endl;

    return {-1, -1};  // Si aucune position trouvée

}





bool is_safe_position(const Position& pos, const vector<pair<Position, int>>& bombs) {

    for (const auto& [bomb_pos, range] : bombs) {

        if (is_in_bomb_range(pos, bomb_pos, range)) {

            return false;  // Position dangereuse

        }

    }

    return true;  // Position sécurisée

}



Position find_position_B(const vector<string>& grid, Position posA, Position player_pos, int width, int height, int bomb_range, const vector<pair<Position, int>>& bombs) {

    vector<Position> directions = {{-1, -1}, {-1, 1}, {1, -1}, {1, 1}};



    for (const auto& dir : directions) {

        for (int i = 1; i <= bomb_range; ++i) {

            Position safe_pos = {posA.x + dir.x * i, posA.y + dir.y * i};



            bool safe = is_valid_position(safe_pos, width, height) && grid[safe_pos.y][safe_pos.x] == '.';

            for (const auto& [bomb_pos, range] : bombs) {

                if (is_in_bomb_range(safe_pos, bomb_pos, range)) {

                    safe = false;

                    break;

                }

            }



            if (safe && is_reachable(grid, player_pos, safe_pos, width, height)) {

                cerr << "Valid diagonal position B found at: (" << safe_pos.x << ", " << safe_pos.y << ")" << endl;

                return safe_pos;

            }

        }

    }



    for (const auto& dir : vector<Position>{{-1, 0}, {1, 0}, {0, -1}, {0, 1}}) {

        Position safe_pos = posA + dir;



        bool safe = is_valid_position(safe_pos, width, height) && grid[safe_pos.y][safe_pos.x] == '.';

        for (const auto& [bomb_pos, range] : bombs) {

            if (is_in_bomb_range(safe_pos, bomb_pos, range)) {

                safe = false;

                break;

            }

        }



        if (safe && is_reachable(grid, player_pos, safe_pos, width, height)) {

            cerr << "Valid adjacent position B found at: (" << safe_pos.x << ", " << safe_pos.y << ")" << endl;

            return safe_pos;

        }

    }



    cerr << "No valid position B found, returning (-1, -1)." << endl;

    return {-1, -1};

}



int main() {

    int width, height, my_id;

    cin >> width >> height >> my_id;

    cin.ignore();



    Position player_pos{-1, -1};

    Position posA{-1, -1};

    Position posB{-1, -1};

    bool moving_to_B = false;

    bool waiting_for_new_A = false;

    int bomb_timer = 0;

    int bomb_range = 3;

    vector<pair<Position, int>> bombs;

    bool bomb_available = false;



    // Compteur de boîtes restantes

    int remaining_boxes = 0;



    while (1) {

        vector<string> grid(height);

        bombs.clear();

        remaining_boxes = 0;



        for (int i = 0; i < height; i++) {

            cin >> grid[i];

            cin.ignore();

            // Compter les boîtes

            for (char cell : grid[i]) {

                if (cell >= '1' && cell <= '9') {

                    remaining_boxes++;

                }

            }

        }

        cerr << "Boîtes restantes : " << remaining_boxes << endl;



        int entities;

        cin >> entities;

        cin.ignore();



        bomb_available = false;



        if (remaining_boxes > 10)

        {

            bool bomb_available = false;

            for (int i = 0; i < entities; i++) {

                int entity_type, owner, x, y, param_1, param_2;

                cin >> entity_type >> owner >> x >> y >> param_1 >> param_2;

                cin.ignore();



                if (entity_type == 0 && owner == my_id) {

                    player_pos = {x, y};

                    bomb_available = (param_1 > 0);

                    bomb_range = param_2;

                    

                    cerr << "Player position: (" << player_pos.x << ", " << player_pos.y << ")" << endl;

                    cerr << "Bombs available: " << bomb_available << ", Bomb range: " << bomb_range << endl;

                } else if (entity_type == 1) {

                    bombs.push_back({{x, y}, param_2});

                }

            }



            if (bomb_timer > 0) bomb_timer--;



            bool action_taken = false;



            if (!moving_to_B && bomb_available && !waiting_for_new_A) {

                if (posA.x == -1 || posA.y == -1) {

                    posA = find_position_A(grid, player_pos, width, height, bombs);

                    if (posA.x != -1) {

                        posB = find_position_B(grid, posA, player_pos, width, height, bomb_range, bombs);

                        cerr << "Found position B at: (" << posB.x << ", " << posB.y << ")" << endl;

                    }

                }



                if (posA.x != -1 && posB.x != -1) {

                    if (player_pos == posA) {

                        cout << "BOMB " << posA.x << " " << posA.y << endl;

                        cerr << "Placed bomb at A: (" << posA.x << ", " << posA.y << "), Moving to B" << endl;

                        moving_to_B = true;

                        bomb_timer = 8;

                        action_taken = true;

                    } else {

                        cout << "MOVE " << posA.x << " " << posA.y << endl;

                        cerr << "Moving towards A at: (" << posA.x << ", " << posA.y << ")" << endl;

                        action_taken = true;

                    }

                } 

            } else if (moving_to_B) {

                if (bomb_timer > 0) {

                    bool safe = true;

                    for (const auto& [bomb_pos, range] : bombs) {

                        if (is_in_bomb_range(posB, bomb_pos, range)) {

                            safe = false;

                            break;

                        }

                    }

                    

                    if (safe) {

                        cout << "MOVE " << posB.x << " " << posB.y << endl;

                        cerr << "Waiting in position B at: (" << posB.x << ", " << posB.y << "), Bomb timer: " << bomb_timer << endl;

                    } else {

                        cerr << "Position B is unsafe due to other bombs, searching for alternative B" << endl;

                        posB = find_position_B(grid, posA, player_pos, width, height, bomb_range, bombs);

                        if (posB.x != -1 && posB.y != -1) {

                            cout << "MOVE " << posB.x << " " << posB.y << endl;

                            cerr << "New position B found at: (" << posB.x << ", " << posB.y << ")" << endl;

                        } else {

                            cout << "MOVE " << player_pos.x << " " << player_pos.y << endl;

                            cerr << "No safe alternative B found, staying in place" << endl;

                        }

                    }

                    action_taken = true;

                } else {

                    cerr << "Bomb exploded! Restarting search for new A and B." << endl;

                    moving_to_B = false;

                    waiting_for_new_A = true;

                    posA = {-1, -1};

                    posB = {-1, -1};

                }

            } else if (waiting_for_new_A) {

                cout << "MOVE " << player_pos.x << " " << player_pos.y << endl;

                cerr << "Searching for a new position A, current position: (" << player_pos.x << ", " << player_pos.y << ")" << endl;

                action_taken = true;



                if (posA.x == -1 || posA.y == -1) {

                    posA = find_position_A(grid, player_pos, width, height, bombs);

                }

                if (posA.x != -1 && posB.x == -1) {

                    posB = find_position_B(grid, posA, player_pos, width, height, bomb_range, bombs);

                }



                if (posA.x != -1 && posB.x != -1) {

                    waiting_for_new_A = false;

                    cerr << "New positions A and B found, exiting wait state. A: (" << posA.x << ", " << posA.y << "), B: (" << posB.x << ", " << posB.y << ")" << endl;

                }

            }



            if (!action_taken) {

                cout << "MOVE " << player_pos.x << " " << player_pos.y << endl;

                cerr << "Default action MOVE to stay active at: (" << player_pos.x << ", " << player_pos.y << ")" << endl;

            }

        }

        else {

            Position closest_enemy = {-1, -1};

    int min_distance = INT_MAX;



    // Recherche de l'ennemi le plus proche

    for (int i = 0; i < entities; i++) {

        int entity_type, owner, x, y, param_1, param_2;

        cin >> entity_type >> owner >> x >> y >> param_1 >> param_2;

        cin.ignore();



        if (entity_type == 0 && owner != my_id) {  // Ennemi détecté

            Position enemy_pos = {x, y};

            int distance = abs(player_pos.x - enemy_pos.x) + abs(player_pos.y - enemy_pos.y);

            if (distance < min_distance) {

                min_distance = distance;

                closest_enemy = enemy_pos;

            }

        }

    }



    // Si un ennemi a été trouvé

    if (closest_enemy.x != -1 && closest_enemy.y != -1) {

        if (min_distance <= 2 && bomb_available) {

            // Si on est à moins de 2 cases de l'ennemi, poser une bombe

            cout << "BOMB " << player_pos.x << " " << player_pos.y << endl;

            cerr << "Poser une bombe près de l'ennemi à distance " << min_distance << " cases" << endl;

            bomb_timer = 8;

        } else {

            // Sinon, continuer à se rapprocher de l'ennemi

            Position move_target = find_position_A_attack_mode(grid, player_pos, closest_enemy, width, height);

            if (move_target.x != -1 && move_target.y != -1) {

                cout << "MOVE " << move_target.x << " " << move_target.y << endl;

                cerr << "Mode attaque, déplacement vers ennemi à : (" << closest_enemy.x << ", " << closest_enemy.y << ")" << endl;

            } else {

                cout << "MOVE " << player_pos.x << " " << player_pos.y << endl;

                cerr << "Pas de position valide trouvée, reste en place" << endl;

            }

        }

    }

        }

        

    }

    return 0;

}

