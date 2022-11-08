// class definitions for maze navigation assingment
// Mikhail Nesterenko
// 10/28/2022

#include <cstdlib>
#include <ctime>


#ifndef MAZE_HPP_
#define MAZE_HPP_

using std::cout;
using std::cin;
using std::endl;

// room coordinates
class Room {
//
public:
    Room():x_(-1),y_('*'){}; // void constructor, assigns -1 to X coord, and '*' to Y coord

    void pick(); // selects a random room within the maze

    // selects a random adjacent room
    // uses goodDirection() and createAdjacent()
    const Room pickAdjacent(); 

    // asks the user for the room to move adjacent to this room
    // returns {-1,*} if the user wants to quit
    // uses goodDirection() and createAdjacent()
    const Room nextMove() const; 

    void print() const;   // prints room coordinates in format "a1"

    // make this room the start room
    void makeStartRoom() {x_ = 1; y_ = 'a';};

    // make this room - the cheese room
    void makeCheeseRoom() {x_ = mazeSize_, y_ = 'a' + mazeSize_ - 1;};

    // predicate returns true if the coordinates of the two rooms match
    friend bool matchRoom(const Room&, const Room&);
// 
private:
    // checks if this direction keeps the mouse inside the maze
    bool goodDirection(const char) const;

    // returns the room adjacent to this room in the specified direction
    // assumes the direction is inside the maze
    const Room createAdjacent(const char) const;

    static const int mazeSize_ = 4; // maze is mazeSize * mazeSize
    int x_;  // 1 through mazeSize
    char y_; // 'a' through mazeSize
};


// internal wall or next move
class RoomPair {
public:
    RoomPair() {} // void constructor implicitly invokes void constructors on member variables
    // makes a roomPair out of two rooms
    RoomPair(const Room& one, const Room& two):one_(one), two_(two) {}

    void pick(); //selects a random wall, uses Room::pickAdjacent()
    void print() const; // prints the locations of the adjacent rooms

    // returns true if two pairs of adjacent rooms are the same,
    // returns false otherwise, uses matchRoom() note that r1|r2 matches r2|r1
    friend bool matchPair(const RoomPair&, const RoomPair&);

private:
    Room one_;
    Room two_;
};

// class Maze {
// public:
//     Maze() {} // places every wall between two rooms where x-coordinate is -1
//               // and y-coordinate is '*' (a star) to signify that
//               // the wall is not built yet

//     // prints the locations of all the internal walls of the maze
//     // and current mouse location
//     void print() const; 

//     // places internal walls in random locations of the maze
//     // all walls are different
//     void build(); 

//     // places current mouse location in startRoom_;
//     void start() { currentRoom_.makeStartRoom(); }

//     // takes the room to move the mouse to
//     // moves the mouse there and returns true if no walls (move is possible)
//     // does not move the mouse and returns false if wall
//     bool move(const Room&);

//     // returns current mouse location
//     const Room getCurrentRoom() { return currentRoom_; }

// private:
//     // returns the index of the element in maze_ that separates RoomPair
//     // returns -1 if none do, uses matchPair()
//     int checkMaze(const RoomPair&) const; 

//     Room currentRoom_; // current mouse Location

//     static const int numWalls_ = 8;  // number of internal walls
//     RoomPair maze_[numWalls_]; // number of internal walls
// };

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////

// ROOM CLASS FUNCTION DEFINITIONS /////////////////////////////

void Room::pick() {
    x_ = rand() % mazeSize_ + 1;
    y_ = 'a' + rand() % mazeSize_;
}

void Room::print() const {
    cout << x_ <<  y_ << endl;
}

bool Room::goodDirection(const char direction) const {
    if (direction == 'u' && y_ > 'a' ) { // Up
        return true; //
    }
    if (direction == 'd' && y_ < 'a' + mazeSize_ - 1) { // Down
        return true;
    }
    if (direction == 'l' && x_ > 1) { // Left
        return true;
    }
    if (direction == 'r' && x_ < mazeSize_ + 1) { // Right
        return true;
    }        
    return false;
}

const Room Room::createAdjacent(const char adj_room_direction) const {
    Room new_adj_room = *this;

    if (adj_room_direction == 'u') {
        new_adj_room.y_ = y_ - 1;
    }
    if (adj_room_direction == 'd') {
        new_adj_room.y_ = y_ + 1;
    }
    if (adj_room_direction == 'l') {
        new_adj_room.x_ = x_ - 1;
    }
    if (adj_room_direction == 'r') {
        new_adj_room.x_ = x_ + 1;
    }
    return new_adj_room;
}

const Room Room::pickAdjacent() {
    Room picked_room = *this;

    char rand_letters [] = {'u', 'd', 'l' , 'r'};
    char selected_rand_letter = rand_letters[rand() % 4];

    Room picked_adjacent = picked_room;
    picked_adjacent = picked_room.createAdjacent(selected_rand_letter);

    if (picked_adjacent.goodDirection(selected_rand_letter) == true) {
        return picked_adjacent;
    } else {
        cout << "Bad direction" << endl;
        return picked_room;
    }
}

const Room Room::nextMove() const {
    Room current_room = *this;
    
    cout << "Please select a room with (l = left) (r = right) (u = up) (d = down)" << endl;
    char move_selection;
    cin >> move_selection;

    Room next_room_move;
    next_room_move = current_room.createAdjacent(move_selection);
    if (next_room_move.goodDirection(move_selection) == true) {
        return next_room_move;
    } else {
        cout << "Bad direction" << endl;
        return current_room;
    }

}

bool matchRoom(const Room &current_room, const Room &new_room) {
    if (current_room.x_ == new_room.x_ && current_room.y_ == new_room.y_) {
        return true;
    }
    return false;
}

bool matchPair(const RoomPair &current_rooms, const RoomPair &new_rooms) {
    if ((matchRoom(current_rooms.one_, new_rooms.one_)) && (matchRoom(current_rooms.two_, new_rooms.two_))) {
        return true;
    }
    return false;
}

void RoomPair::pick() {
    RoomPair::one_.pickAdjacent();
    RoomPair::two_.pickAdjacent();
}

void RoomPair::print() const {
    RoomPair::one_.print();
    RoomPair::two_.print();
}

#endif // MAZE_HPP_