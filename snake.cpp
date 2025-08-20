#include <iostream>
#include <conio.h>
#include <windows.h>
#include <ctime>
using namespace std;

// Node for snake body
struct Node {
    int x, y;
    Node* next;
    Node(int x, int y) : x(x), y(y), next(NULL) {}
};

enum Direction { UP, DOWN, LEFT, RIGHT };

Node* head = NULL;   // snake tail
Node* tail = NULL;   // snake head
int width = 40, height = 20;
int food_x, food_y;
int score = 0;
Direction dir = RIGHT;
bool gameover = false;

// Move console cursor to (x, y)
void gotoXY(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// Add new node at snake head
void addNode(int x, int y) {
    Node* newNode = new Node(x, y);
    if (head == NULL) {
        head = tail = newNode;
    } else {
        tail->next = newNode;
        tail = newNode;
    }
}

// Remove tail (simulate moving forward)
void removeTail() {
    if (!head) return;
    Node* temp = head;
    head = head->next;
    delete temp;
}

// Check if snake collides with itself
bool checkCollision(int x, int y) {
    Node* curr = head;
    while (curr != NULL) {
        if (curr->x == x && curr->y == y) return true;
        curr = curr->next;
    }
    return false;
}

// Place food at random location
void placeFood() {
    do {
        food_x = rand() % width;
        food_y = rand() % height;
    } while (checkCollision(food_x, food_y));
}

// Draw game board (line boundary only)
void draw() {
    gotoXY(0, 0);

    // Top boundary
    for (int x = 0; x < width + 2; x++) cout << "-";
    cout << "\n";

    for (int y = 0; y < height; y++) {
        cout << "|"; // Left boundary
        for (int x = 0; x < width; x++) {
            if (x == food_x && y == food_y) {
                cout << "F"; // Food
            } else {
                bool printed = false;
                Node* curr = head;
                while (curr != NULL) {
                    if (curr->x == x && curr->y == y) {
                        cout << "O"; // Snake
                        printed = true;
                        break;
                    }
                    curr = curr->next;
                }
                if (!printed) cout << " ";
            }
        }
        cout << "|\n"; // Right boundary
    }

    // Bottom boundary
    for (int x = 0; x < width + 2; x++) cout << "-";
    cout << "\n";

    cout << "Score: " << score << "\n";
}

// Move snake one step
void moveSnake() {
    int newX = tail->x;
    int newY = tail->y;

    switch (dir) {
        case UP: newY--; break;
        case DOWN: newY++; break;
        case LEFT: newX--; break;
        case RIGHT: newX++; break;
    }

    // check boundary collision
    if (newX < 0 || newY < 0 || newX >= width || newY >= height || checkCollision(newX, newY)) {
        gameover = true;
        return;
    }

    // if eats food
    if (newX == food_x && newY == food_y) {
        addNode(newX, newY);
        score++;
        placeFood();
    } else {
        addNode(newX, newY);
        removeTail();
    }
}

// Handle user input (WASD)
void input() {
    if (_kbhit()) {
        char ch = _getch();
        switch (ch) {
            case 'w': if (dir != DOWN) dir = UP; break;
            case 's': if (dir != UP) dir = DOWN; break;
            case 'a': if (dir != RIGHT) dir = LEFT; break;
            case 'd': if (dir != LEFT) dir = RIGHT; break;
            case 'q': gameover = true; break;
        }
    }
}

int main() {
    srand(time(0));

    // hide console cursor
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = false;  
    SetConsoleCursorInfo(out, &cursorInfo);

    // initialize snake
    addNode(width / 2, height / 2);
    placeFood();

    // game loop
    while (!gameover) {
        draw();
        input();
        moveSnake();
        Sleep(100); // control speed
    }

    gotoXY(0, height + 2);
    cout << "\nGAME OVER! Final Score: " << score << "\n";
    system("pause");
    return 0;
}
