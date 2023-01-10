#include <iostream>
#include <thread>
#include <Windows.h>
#include <random>

void click(int leftCps, int rightCps) {
    std::mt19937 rng;
    rng.seed(std::random_device()());
    std::uniform_int_distribution<std::mt19937::result_type> dist(-20, 20);
    while (true) {
        if (leftCps > 0) {
            // Perform a left mouse button click
            mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
            mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
        }
        if (rightCps > 0) {
            // Perform a right mouse button click
            mouse_event(MOUSEEVENTF_RIGHTDOWN, 0, 0, 0, 0);
            mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
        }
        // Sleep for (1 / CPS) seconds with a random variation
        int delay = 1000 / (leftCps + rightCps);
        delay += dist(rng);
        std::this_thread::sleep_for(std::chrono::milliseconds(delay));
        if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
            break;
        }
    }
}

int main() {
    int leftCps, rightCps;

    std::cout << "Enter the number of left clicks per second: ";
    std::cin >> leftCps;
    std::cout << "Enter the number of right clicks per second: ";
    std::cin >> rightCps;

    std::cout << "Autoclicker started. Press 'Esc' to quit." << std::endl;

    // Start the clicking thread
    std::thread t1(click, leftCps, rightCps);

    // Wait for the user to press 'Esc' to quit
    while (true) {
        if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
            break;
        }
    }

    // Wait for the clicking thread to finish
    t1.join();

    std::cout << "Autoclicker stopped." << std::endl;
    return 0;
}
