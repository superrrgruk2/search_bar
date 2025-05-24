#include <graphics.h>
#include <conio.h>
#include <cstring>

const int JOB_COUNT = 5;
const int MAX_LENGTH = 50;
char jobs[JOB_COUNT][MAX_LENGTH] = {
    "Software Engineer",
    "Data Analyst",
    "Web Developer",
    "Network Admin",
    "System Support"
};

void drawScreen(const char input[]) {
    // Set background to white
    setbkcolor(WHITE);
    cleardevice();

    // Title
    setcolor(BLACK);
    settextstyle(3, 0, 6); // Font for "JOBIFY"
    outtextxy(450, 50, "JOBIFY");

    // Search Box
    setcolor(BLACK);
    rectangle(400, 150, 1000, 200); // Search bar outline

    settextstyle(0, 0, 2);
    outtextxy(410, 165, input   ); // User input shown here
}

void showResults(const char input[]) {
    int y = 230;
    bool found = false;

    for (int i = 0; i < JOB_COUNT; i++) {
        char tempJob[MAX_LENGTH], tempInput[MAX_LENGTH];
        strcpy(tempJob, jobs[i]);
        strcpy(tempInput, input);

        for (int j = 0; tempJob[j]; j++) tempJob[j] = tolower(tempJob[j]);
        for (int j = 0; tempInput[j]; j++) tempInput[j] = tolower(tempInput[j]);

        if (strstr(tempJob, tempInput)) {
            outtextxy(420, y, jobs[i]); // Display the matching job
            y += 30;
            found = true;
        }
    }

    if (!found) {
        outtextxy(420, y, "No matching jobs found."); // Message if no jobs match
    }
}

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");

    char input[MAX_LENGTH] = "";
    int index = 0;
    char ch;

    drawScreen(input);

    // Input loop
    while (true) {
        ch = getch();
        if (ch == 13) break; // Enter
        if (ch == 8 && index > 0) {
            index--;
            input[index] = '\0';
        } else if (ch >= 32 && ch <= 126 && index < MAX_LENGTH - 1) {
            input[index] = ch;
            index++;
            input[index] = '\0';
        }

        drawScreen(input); // Refresh screen with updated input
    }

    cleardevice();
    drawScreen(input);
    showResults(input);

    getch();
    closegraph();
    return 0;
}
