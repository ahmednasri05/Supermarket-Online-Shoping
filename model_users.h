#pragma once
using namespace std;
#include <string>
#include <iostream>
//#ifdef _WIN32
//#include <windows.h>  // Required for Windows
//#endif


struct Person {
    string ID;
    string Name;
    string PhoneNumber;
    string Password;
    string Location;
    int Age;
};

#define ANSI_RESET "\033[0m"
#define ANSI_RED "\033[31m"
#define ANSI_RESET "\033[0m"
#define ANSI_CYAN "\033[96m"
#define ANSI_YELLOW "\033[93m"
#define ANSI_BOLD "\033[1m"
#define ANSI_GREEN "\033[32m"


// Function to set text color using ANSI escape codes
void setTextColor(const char* colorCode) {
    cout << colorCode;
}
#include <thread>
void printWithDelay(const string& text, int milliseconds) {
    for (char c : text) {
        cout << c << flush;
        this_thread::sleep_for(chrono::milliseconds(milliseconds));
    }
}


//Animation functions
#include <cstdlib>
#include <vector>
#include <thread>
#include <chrono>

using namespace std;

// Function to set the cursor position using ANSI escape codes
void setCursorPosition(int x, int y) {
    cout << "\033[" << y + 1 << ";" << x + 1 << "H";
}

// Function to set text attributes using ANSI escape codes
void setTextAttributes(int color) {
    cout << "\033[38;5;" << color << "m";
}

// Function to clear the screen using ANSI escape codes
void clearScreen() {
    cout << "\033[2J\033[H";
}

// Function to introduce a dynamic and cool welcome intro
void coolWelcomeIntro() {
    clearScreen();

    setTextAttributes(14); // Yellow text
    for (int i = 1; i <= 8; ++i) {
        clearScreen();
        setCursorPosition(20, 10);
        for (int j = 0; j < i; ++j) {
            cout << " ";
        }
        cout << "Welcome to Our Online Shopping Supermarket!";
        this_thread::sleep_for(chrono::milliseconds(200));
    }

    setTextAttributes(11); // Light Blue text
    setCursorPosition(10, 12);
    cout << "Get ready for an easy and magnificent experience.";

    setTextAttributes(12); // Red text
    setCursorPosition(15, 14);
    cout << "Explore a variety of high-quality products.";

    this_thread::sleep_for(chrono::seconds(2)); // Pause for 2 seconds
}

// Function to create an enhanced sparkling firework animation
void enhancedSparklingFirework() {
    srand(static_cast<unsigned>(time(nullptr)));

    for (int i = 0; i < 100; ++i) {
        clearScreen();
        setCursorPosition(rand() % 80, rand() % 24);
        setTextAttributes(rand() % 7 + 9); // Vary the color for each spark
        cout << "*";

        setCursorPosition(rand() % 80, rand() % 24);
        setTextAttributes(rand() % 7 + 9); // Vary the color for each spark
        cout << ".";

        setCursorPosition(rand() % 80, rand() % 24);
        setTextAttributes(rand() % 7 + 9); // Vary the color for each spark
        cout << "+";

        this_thread::sleep_for(chrono::milliseconds(30)); // Adjust the sleep duration for the desired speed
    }
}

// Function to perform a colored and expanding "Enjoy" text animation
void enjoyTextAnimation() {
    clearScreen();

    vector<pair<int, int>> enjoyPositions;
    vector<int> enjoySizes;

    enjoyPositions.push_back({ rand() % 70, rand() % 20 });
    enjoySizes.push_back(1);

    int totalEnjoyCount = 1;

    for (int frame = 0; frame < 100; ++frame) {
        clearScreen();

        for (int i = 0; i < totalEnjoyCount; ++i) {
            setTextAttributes(12 + enjoySizes[i]); // Change color based on size
            setCursorPosition(enjoyPositions[i].first, enjoyPositions[i].second);
            cout << "Enjoy";
        }

        if (frame % 5 == 0) {
            enjoyPositions.push_back({ rand() % 70, rand() % 20 });
            enjoySizes.push_back(1);
            totalEnjoyCount += 1;
        }

        for (int i = 0; i < totalEnjoyCount; ++i) {
            enjoySizes[i] += 1; // Increase the size
        }

        this_thread::sleep_for(chrono::milliseconds(150));
    }
}