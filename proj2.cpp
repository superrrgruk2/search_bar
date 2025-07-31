#include <graphics.h>
#include <conio.h>
#include <fstream>
#include <string>
#include <iostream>
#include <windows.h>
#include <cstring>
#include <vector>
#include <cctype>
#include <algorithm>

using namespace std;

int screenWidth = GetSystemMetrics(SM_CXSCREEN);
int screenHeight = GetSystemMetrics(SM_CYSCREEN);
// File to store jobs
const string JOB_FILE = "jobs.txt";

// Back button coordinates (bottom-right)
const int backBtnX1 = screenWidth - 150;
const int backBtnY1 = screenHeight - 70;
const int backBtnX2 = screenWidth - 50;
const int backBtnY2 = screenHeight - 30;


//mainMenu();

// Global role tracker
string currentRole = "";


// JOB SEARCH DATA
const int JOB_COUNT = 5;
const int MAX_LENGTH = 50;
char jobs[JOB_COUNT][MAX_LENGTH] = {
    "Software Engineer",
    "Data Analyst",
    "Web Developer",
    "Network Admin",
    "System Support"
};

void mainMenu();
// Utility: Mouse inside check
bool isMouseInside(int x, int y, int width, int height) {
    int mx = mousex();
    int my = mousey();
    return (mx >= x && mx <= x + width && my >= y && my <= y + height);
}

// Utility: Draw button
void drawButton(int x, int y, int width, int height, char label[]) {
    setcolor(WHITE);
    setfillstyle(SOLID_FILL, DARKGRAY);
    bar(x, y, x + width, y + height);
    rectangle(x, y, x + width, y + height);
    setbkcolor(DARKGRAY);
    settextstyle(BOLD_FONT, HORIZ_DIR, 2);
    outtextxy(x + (width - textwidth(label)) / 2, y + (height - textheight(label)) / 2, label);
}

// Utility: Get input
void getInput(char label[], int x, int y, char input[], int maxLen, bool isPassword = false) {
    setcolor(WHITE);
    outtextxy(x, y, label);
    rectangle(x + textwidth(label) + 10, y, x + 400, y + 30);
    int i = 0;
    char ch;
    input[0] = 0;

    while (true) {
        ch = getch();
        if (ch == 13) break;
        else if (ch == 8 && i > 0) {
            i--;
            input[i] = 0;
        } else if (isprint(ch) && i < maxLen - 1) {
            input[i++] = ch;
            input[i] = 0;
        }

        setfillstyle(SOLID_FILL, BLACK);
        bar(x + textwidth(label) + 11, y + 1, x + 399, y + 29);

        if (isPassword) {
            char temp[100];
            for (int j = 0; j < i; ++j) temp[j] = '*';
            temp[i] = 0;
            outtextxy(x + textwidth(label) + 15, y + 5, temp);
        } else {
            outtextxy(x + textwidth(label) + 15, y + 5, input);
        }
    }
}

// JOB SEARCH SCREEN
void background_images() {
    readimagefile("C:\\Users\\nisha\\OneDrive\\Desktop\\aa.png", 0, 0, 1200, 700);
}

void drawJobSearchScreen(const char input[]) {
    background_images();
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 7);
    setcolor(WHITE);
    setfillstyle(SOLID_FILL, BLACK);
    bar(435, 55, 780, 111);
    outtextxy(40, 50, (char*)"JOB VACANCY PLATFORM");

    // Search box
    setcolor(WHITE);
    rectangle(40, 160, 1200, 200);
    setfillstyle(SOLID_FILL, BLACK);
    bar(41, 161, 999, 199);
    setcolor(WHITE);
    settextstyle(SIMPLEX_FONT, HORIZ_DIR, 2); // Only one settextstyle needed 

    outtextxy(45, 173, (char*)input);
    
    
    
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
            outtextxy(350, y, jobs[i]);
            y += 30;
            found = true;
        }
    }

    if (!found) {
        setcolor(RED);
        settextstyle(SIMPLEX_FONT, HORIZ_DIR, 3);
        outtextxy(450, y + 100, (char*)"No matching jobs found.");
    }
}

void jobSearchScreen() {
    cleardevice();
    char input[MAX_LENGTH] = "";
    int index = 0;
    char ch;

    drawJobSearchScreen(input);

    while (true) {
        ch = getch();
        if (ch == 13) break;
        if (ch == 8 && index > 0) {
            index--;
            input[index] = '\0';
        } else if (ch >= 32 && ch <= 126 && index < MAX_LENGTH - 1) {
            input[index++] = ch;
            input[index] = '\0';
        }

        drawJobSearchScreen(input);
    }

    cleardevice();
    drawJobSearchScreen(input);
    showResults(input);
    getch();
}

// MAIN INTERFACES

void showMainMenu();
void signupForm();
void showLoginSignupMenu(char role[]);

void loginForm() {
    cleardevice();
    setbkcolor(BLACK);
    setcolor(WHITE);
    settextstyle(BOLD_FONT, HORIZ_DIR, 3);
    char title[100];
    sprintf(title, "%s Portal", currentRole.c_str());
    outtextxy((screenWidth - textwidth(title)) / 2, 100, title);

    int buttonW = 400, buttonH = 70;
    int x = (screenWidth - buttonW) / 2;
    int y = 250;

    char uname[100], pass[100];
    settextstyle(BOLD_FONT, HORIZ_DIR, 2);
    outtextxy(300, 160, (char*)"* Username and password are case sensitive");
    getInput((char*)"Username:", 300, 200, uname, 100);
    getInput((char*)"Password:", 300, 250, pass, 100, true);

    const char* filename = (currentRole == "Employer") ? "employers.txt" : "jobseekers.txt";
    ifstream file(filename);
    string u, p;
    bool valid = false;

    while (file >> u >> p) {
        if (u == uname && p == pass) {
            valid = true;
            break;
        }
    }

    if (valid) {
        if (currentRole == "JobSeeker") {
            jobSearchScreen();
        } else {
            cleardevice();
            settextstyle(BOLD_FONT, HORIZ_DIR, 4);
            char msg[100];
            sprintf(msg, "Welcome, %s!", uname);
            outtextxy((screenWidth - textwidth(msg)) / 2, screenHeight / 2, msg);
            delay(2000);
            mainMenu();
        }
    } else {
        drawButton(x + 200, y, buttonW, buttonH, (char*)"Invalid credentials.");
        delay(1000);
        getch();
    }
}

void signupForm() {
    cleardevice();
    setbkcolor(BLACK);
    setcolor(WHITE);
    settextstyle(BOLD_FONT, HORIZ_DIR, 3);
    char title[100];
    sprintf(title, "%s Portal", currentRole.c_str());
    outtextxy((screenWidth - textwidth(title)) / 2, 100, title);

    int buttonW = 400, buttonH = 70;
    int x = (screenWidth - buttonW) / 2;
    int y = 550;

    char uname[100], pass[100];
    char name[100], address[100], phone[100], email[100];
    const char* filename = (currentRole == "Employer") ? "employers.txt" : "jobseekers.txt";

    getInput((char*)"Full Name:", 300, 150, name, 100);
    getInput((char*)"Address:", 300, 200, address, 100);
    getInput((char*)"Phone No:", 300, 250, phone, 100);
    getInput((char*)"Email ID:", 300, 300, email, 100);
    getInput((char*)"Username:", 300, 350, uname, 100);
    getInput((char*)"Password:", 300, 400, pass, 100, true);

    if (strlen(name) == 0 || strlen(address) == 0 || strlen(phone) == 0 || strlen(email) == 0 || strlen(uname) == 0 || strlen(pass) == 0) {
        drawButton(x, y, buttonW, buttonH, (char*)"All fields are required!");
        delay(1500);
        getch();
        return;
    }

    ofstream file(filename, ios::app);
    file << uname << " " << pass << endl;

    drawButton(x, y, buttonW, buttonH, (char*)"Sign up successful!");
    delay(1000);
    getch();
}

void showLoginSignupMenu(char role[]) {
    currentRole = role;
    setbkcolor(BLACK);
    cleardevice();
    settextstyle(BOLD_FONT, HORIZ_DIR, 3);
    setcolor(WHITE);
    char heading[100];
    sprintf(heading, "%s Portal", role);
    outtextxy((screenWidth - textwidth(heading)) / 2, 100, heading);

    int buttonW = 400, buttonH = 70;
    int x = (screenWidth - buttonW) / 2;
    int loginY = 250, signupY = 350, backY = 450;

    drawButton(x, loginY, buttonW, buttonH, (char*)"Login");
    drawButton(x, signupY, buttonW, buttonH, (char*)"Sign Up");
    drawButton(x, backY, buttonW, buttonH, (char*)"Back to Main Menu");

    delay(200);

    while (true) {
        if (ismouseclick(WM_LBUTTONDOWN)) {
            clearmouseclick(WM_LBUTTONDOWN);
            if (isMouseInside(x, loginY, buttonW, buttonH)) {
                loginForm();
                showLoginSignupMenu(role);
                return;
            } else if (isMouseInside(x, signupY, buttonW, buttonH)) {
                signupForm();
                showLoginSignupMenu(role);
                return;
            } else if (isMouseInside(x, backY, buttonW, buttonH)) {
                showMainMenu();
                return;
            }
        }
    }
}

void showMainMenu() {
    setbkcolor(BLACK);
    cleardevice();
    setcolor(WHITE);
    settextstyle(BOLD_FONT, HORIZ_DIR, 4);
    outtextxy((screenWidth - textwidth((char*)"JOB VACANCY PLATFORM")) / 2, 100, (char*)"JOB VACANCY PLATFORM");

    settextstyle(BOLD_FONT, HORIZ_DIR, 2);
    outtextxy((screenWidth - textwidth((char*)"Welcome to the Platform")) / 2, 160, (char*)"Welcome to the Platform");

    int buttonW = 400, buttonH = 70;
    int x = (screenWidth - buttonW) / 2;
    int employerY = 300, jobSeekerY = 400, exitY = 500;

    drawButton(x, employerY, buttonW, buttonH, (char*)"Employer");
    drawButton(x, jobSeekerY, buttonW, buttonH, (char*)"Job Seeker");
    drawButton(x, exitY, buttonW, buttonH, (char*)"Exit");

    while (true) {
        if (ismouseclick(WM_LBUTTONDOWN)) {
            clearmouseclick(WM_LBUTTONDOWN);
            if (isMouseInside(x, employerY, buttonW, buttonH)) {
                showLoginSignupMenu((char*)"Employer");
                return;
            } else if (isMouseInside(x, jobSeekerY, buttonW, buttonH)) {
                showLoginSignupMenu((char*)"JobSeeker");
                return;
            } else if (isMouseInside(x, exitY, buttonW, buttonH)) {
                exit(0);
            }
        }
    }
}


// Draw back button
void drawBackButton() {
    setfillstyle(SOLID_FILL, DARKGRAY);
    bar(backBtnX1, backBtnY1, backBtnX2, backBtnY2);
    setcolor(WHITE);
    rectangle(backBtnX1, backBtnY1, backBtnX2, backBtnY2);
    setbkcolor(BLACK);
    settextstyle(10, 0, 2);
    outtextxy(backBtnX1 + 20, backBtnY1 + 8, (char *)"Back");
}

// Check if back button was clicked
bool backButtonClicked(int mx, int my) {
    return (mx >= backBtnX1 && mx <= backBtnX2 && my >= backBtnY1 && my <= backBtnY2);
}

// Load all jobs

vector<string> loadJobs() {
    vector<string> jobs;
    ifstream infile(JOB_FILE);
    string job;
    while (getline(infile, job)) {
        if (!job.empty())
            jobs.push_back(job);
    }
    infile.close();
    return jobs;
}

string getInputField(int x, int y, const char* label) {
    settextstyle(10, 0, 2);
    setcolor(WHITE);
    outtextxy(x, y, (char*)label);

    int boxX = x + 250, boxY = y, boxW = 400;
    rectangle(boxX, boxY, boxX + boxW, boxY + 30);

    string input = "";
    char ch;
    while (true) {
        if (ismouseclick(WM_LBUTTONDOWN)) {
            int mx, my;
            getmouseclick(WM_LBUTTONDOWN, mx, my);
            if (backButtonClicked(mx, my)) return "BACK";
        }
        ch = getch();
        if (ch == 13) break;
        else if (ch == 8 && !input.empty()) input.pop_back();
        else if (isprint(ch) && input.length() < 50) input += ch;

        setfillstyle(SOLID_FILL, BLACK);
        bar(boxX + 2, boxY + 2, boxX + boxW - 2, boxY + 28);
        setcolor(WHITE);
        outtextxy(boxX + 5, boxY + 5, (char*)input.c_str());
    }
    return input;
}
void showJobsScreen() {
    int page = 0;
    const int JOBS_PER_PAGE = 2;
    char input[MAX_LENGTH] = "";
    int index = 0;
    char ch;

    // Input search loop
    while (true) {
        cleardevice();
        setbkcolor(BLACK);
        background_images();

        // Draw header
        settextstyle(DEFAULT_FONT, HORIZ_DIR, 7);
        setcolor(WHITE);
        setfillstyle(SOLID_FILL, LIGHTGRAY);
        bar(435, 55, 780, 111);
        outtextxy(440, 50, (char*)"JOBIFY");

        // Draw search box
        setcolor(WHITE);
        rectangle(320, 200, 1000, 240);
        setfillstyle(SOLID_FILL, BLACK);
        bar(321, 201, 999, 239);
        setcolor(WHITE);
        settextstyle(SIMPLEX_FONT, HORIZ_DIR, 2);
        outtextxy(340, 210, input[0] == '\0' ? (char*)"Search..." : input);

        // Draw back button
        drawBackButton();

        // Keyboard input for search
        if (kbhit()) {
            ch = getch();
            if (ch == 13) break; // Enter
            if (ch == 8 && index > 0) {
                index--;
                input[index] = '\0';
            } else if (ch >= 32 && ch <= 126 && index < MAX_LENGTH - 1) {
                input[index++] = ch;
                input[index] = '\0';
            }
        }

        // Handle mouse for back button
        if (ismouseclick(WM_LBUTTONDOWN)) {
            int mx, my;
            getmouseclick(WM_LBUTTONDOWN, mx, my);
            if (backButtonClicked(mx, my)) return;
        }

        delay(10); // Smoother input loop
    }

    // Main job display loop
    while (true) {
        cleardevice();
        background_images();

        // Redraw header
        settextstyle(DEFAULT_FONT, HORIZ_DIR, 7);
        setcolor(WHITE);
        setfillstyle(SOLID_FILL, LIGHTGRAY);
        bar(435, 55, 780, 111);
        outtextxy(440, 50, (char*)"JOBIFY");

        // Redraw search box
        setcolor(WHITE);
        rectangle(320, 200, 1000, 240);
        setfillstyle(SOLID_FILL, BLACK);
        bar(321, 201, 999, 239);
        setcolor(WHITE);
        settextstyle(SIMPLEX_FONT, HORIZ_DIR, 2);
        outtextxy(340, 210, input);

        drawBackButton();

        // Load and filter jobs
        vector<string> jobs = loadJobs();
        vector<string> filtered;
        for (const string& job : jobs) {
            if (strstr(job.c_str(), input) != nullptr)
                filtered.push_back(job);
        }

        // Draw job boxes
        int xStart = 50, yStart = 260;
        int boxHeight = 170, boxWidth = 1000;
        int start = page * JOBS_PER_PAGE;
        int end = min(start + JOBS_PER_PAGE, (int)filtered.size());
        bool found = false;

        for (int i = start; i < end; ++i) {
            found = true;
            int y = yStart + (i - start) * (boxHeight + 10);

            setcolor(WHITE);
            rectangle(xStart, y, xStart + boxWidth, y + boxHeight);
            setfillstyle(SOLID_FILL, BLACK);
            bar(xStart + 1, y + 1, xStart + boxWidth - 1, y + boxHeight - 1);

            string job = filtered[i];
            vector<string> fields;
            size_t pos = 0;
            while ((pos = job.find(" | ")) != string::npos) {
                fields.push_back(job.substr(0, pos));
                job.erase(0, pos + 3);
            }
            fields.push_back(job);

            int fieldY = y + 15;
            for (string &f : fields) {
                outtextxy(xStart + 20, fieldY, (char*)f.c_str());
                fieldY += 25;
            }
        }

        if (!found) {
            setcolor(WHITE);
            outtextxy(340, yStart + 200, (char*)"No matching jobs found.");
        }

        // Draw "Next" button
        setcolor(WHITE);
        setfillstyle(SOLID_FILL, DARKGRAY);
        bar(950, 60, 1050, 90);
        rectangle(950, 60, 1050, 90);
        outtextxy(970, 65, (char*)"Next");

        // Wait for mouse click
        while (!ismouseclick(WM_LBUTTONDOWN)) {}

        int mx, my;
        getmouseclick(WM_LBUTTONDOWN, mx, my);

        if (backButtonClicked(mx, my)) return;

        // If "Next" clicked
        if (mx >= 950 && mx <= 1050 && my >= 60 && my <= 90) {
            if ((page + 1) * JOBS_PER_PAGE < filtered.size()) {
                page++;
            } else {
                page = 0; // Wrap back to first page
            }
        }
    }
}



void postJobStepForm() {
    cleardevice();
    drawBackButton();
    settextstyle(10, 0, 3);
    setcolor(WHITE);
    outtextxy(50, 30, (char*)"Post New Job - Step by Step");

    int yStart = 100;
    string company = getInputField(50, yStart, "Company Name:");
    if (company == "BACK") return;
    string address = getInputField(50, yStart + 60, "Address:");
    if (address == "BACK") return;
    string role = getInputField(50, yStart + 120, "Role:");
    if (role == "BACK") return;
    string salary = getInputField(50, yStart + 180, "Salary (NRs):");
    if (salary == "BACK") return;
    string age = getInputField(50, yStart + 240, "Age Requirement:");
    if (age == "BACK") return;
    string field = getInputField(50, yStart + 300, "Field:");
    if (field == "BACK") return;

    setfillstyle(SOLID_FILL, GREEN);
    bar(800, 600, 950, 650);
    setcolor(RED);
    rectangle(800, 600, 950, 650);
    outtextxy(830, 615, (char *)"Done");

    int mx, my;
    while (true) {
        if (ismouseclick(WM_LBUTTONDOWN)) {
            getmouseclick(WM_LBUTTONDOWN, mx, my);
            if (mx >= 800 && mx <= 950 && my >= 600 && my <= 650)
                break;
            if (backButtonClicked(mx, my)) return;
        }
    }

    ofstream outfile(JOB_FILE, ios::app);
    outfile << "Company : " << company << " | Address: " << address
            << " | Role: " << role << " | Salary: NRs " << salary
            << " | Age: " << age << " | Field: " << field << endl;
    outfile.close();

    cleardevice();
    settextstyle(10, 0, 3);
    outtextxy(100, 200, (char *)"? Job posted successfully!");
    outtextxy(100, 250, (char *)"Press any key to return...");
    getch();
}

void deleteJobScreen() {
    vector<string> allJobs = loadJobs();
    vector<string> filteredJobs = allJobs;

    char input[MAX_LENGTH] = "";
    int index = 0;
    char ch;
    int page = 0;
    const int JOBS_PER_PAGE = 2;

    // --- Initial Draw (once) ---
    cleardevice(); // Only once
    background_images(); // Static BG
    drawBackButton();
    
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 7);
    setcolor(WHITE);
    setfillstyle(SOLID_FILL, LIGHTGRAY);
    bar(435, 55, 780, 111);
    outtextxy(440, 50, (char *)"JOBIFY");

    while (true) {
        // Clear dynamic region only (search box + job list)
        setfillstyle(SOLID_FILL, BLACK);
       // bar(300, 190, 1050, 700);  // <-- Adjust to job list area

        // Search box
        setcolor(WHITE);
        rectangle(320, 200, 1000, 240);
        setfillstyle(SOLID_FILL, BLACK);
        bar(321, 201, 999, 239);
        setcolor(WHITE);
        settextstyle(SIMPLEX_FONT, HORIZ_DIR, 2);
        outtextxy(340, 210, input[0] == '\0' ? (char *)"Search..." : input);

        // Pagination Button
        setcolor(WHITE);
        setfillstyle(SOLID_FILL, DARKGRAY);
        bar(950, 60, 1050, 90);
        rectangle(950, 60, 1050, 90);
        outtextxy(970, 65, (char *)"Next");

        // Filter jobs based on input
        filteredJobs.clear();
        for (string &job : allJobs) {
            string lowerJob = job, lowerInput = input;
            transform(lowerJob.begin(), lowerJob.end(), lowerJob.begin(), ::tolower);
            transform(lowerInput.begin(), lowerInput.end(), lowerInput.begin(), ::tolower);
            if (lowerJob.find(lowerInput) != string::npos)
                filteredJobs.push_back(job);
        }

        setbkcolor(BLACK);
        settextstyle(10, 0, 2);
        setcolor(WHITE);
        outtextxy(50, 260, (char *)"Delete Job - Click 'Delete' next to a job");

        // Render job cards
        int boxHeight = 170, boxWidth = 1000;
        int xStart = 50, yStart = 300;
        vector<RECT> deleteButtons;

        int start = page * JOBS_PER_PAGE;
        int end = min(start + JOBS_PER_PAGE, (int)filteredJobs.size());

        for (int i = start; i < end; ++i) {
            int y = yStart + (i - start) * (boxHeight + 10);

            setcolor(WHITE);
            rectangle(xStart, y, xStart + boxWidth, y + boxHeight);
            setfillstyle(SOLID_FILL, BLACK);
            bar(xStart + 1, y + 1, xStart + boxWidth - 1, y + boxHeight - 1);

            string job = filteredJobs[i];
            vector<string> fields;
            size_t pos = 0;
            while ((pos = job.find(" | ")) != string::npos) {
                fields.push_back(job.substr(0, pos));
                job.erase(0, pos + 3);
            }
            fields.push_back(job);

            int fieldY = y + 15;
            for (string &f : fields) {
                outtextxy(xStart + 20, fieldY, (char *)f.c_str());
                fieldY += 25;
            }

            int bx = xStart + boxWidth - 120;
            int by = y + boxHeight - 50;
            int bw = 100, bh = 30;
            setfillstyle(SOLID_FILL, RED);
            bar(bx, by, bx + bw, by + bh);
            setcolor(WHITE);
            rectangle(bx, by, bx + bw, by + bh);
            outtextxy(bx + 20, by + 5, (char *)"Delete");

            RECT btn = {bx, by, bx + bw, by + bh};
            deleteButtons.push_back(btn);
        }

        // Keyboard input
        if (kbhit()) {
            ch = getch();
            if (ch == 13) break;
            if (ch == 8 && index > 0) {
                index--;
                input[index] = '\0';
            } else if (ch >= 32 && ch <= 126 && index < MAX_LENGTH - 1) {
                input[index++] = ch;
                input[index] = '\0';
            }
        }

        // Mouse input
        if (ismouseclick(WM_LBUTTONDOWN)) {
            int mx, my;
            getmouseclick(WM_LBUTTONDOWN, mx, my);

            if (backButtonClicked(mx, my)) return;

            // Next button
            if (mx >= 950 && mx <= 1050 && my >= 60 && my <= 90) {
                if ((page + 1) * JOBS_PER_PAGE < filteredJobs.size()) {
                    page++;
                } else page = 0;
                clearmouseclick(WM_LBUTTONDOWN);
                continue;
            }

            // Delete button
            for (int i = 0; i < deleteButtons.size(); i++) {
                RECT btn = deleteButtons[i];
                if (mx >= btn.left && mx <= btn.right && my >= btn.top && my <= btn.bottom) {
                    string targetJob = filteredJobs[start + i];
                    for (int j = 0; j < allJobs.size(); j++) {
                        if (allJobs[j] == targetJob) {
                            allJobs.erase(allJobs.begin() + j);
                            break;
                        }
                    }
                    ofstream outfile(JOB_FILE);
                    for (string &job : allJobs) outfile << job << endl;
                    outfile.close();

                    input[0] = '\0';
                    index = 0;
                    page = 0;
                    break;
                }
            }

            clearmouseclick(WM_LBUTTONDOWN);
        }

        delay(10); // Optional: smooth display without using CPU too much
    }
}



void drawButton(int x, int y, int w, int h, const char *label) {
    setfillstyle(SOLID_FILL, LIGHTGRAY);
    bar(x, y, x + w, y + h);
    setcolor(WHITE);
    rectangle(x, y, x + w, y + h);
    setcolor(BLACK);
    setbkcolor(LIGHTGRAY);
    settextstyle(10, 0, 3);
    outtextxy(x + 30, y + 15, (char *)label);
}

bool isClicked(int x, int y, int w, int h, int mx, int my) {
    return (mx >= x && mx <= x + w && my >= y && my <= y + h);
}

void mainMenu() {
    int mx, my;
    bool running = true;

    while (running) {
        cleardevice();
        settextstyle(10, 0, 5);
        setcolor(WHITE);
        outtextxy(600, 40, (char *)"Employer Portal");

        drawButton(650, 150, 300, 60, "View Jobs");
        drawButton(650, 240, 300, 60, "Post Job");
        drawButton(650, 330, 300, 60, "Delete Job");
        drawButton(650, 420, 300, 60, "Exit");

        while (!ismouseclick(WM_LBUTTONDOWN)) {}
        getmouseclick(WM_LBUTTONDOWN, mx, my);

        if (isClicked(650, 150, 300, 60, mx, my))
            showJobsScreen();
        else if (isClicked(650, 240, 300, 60, mx, my))
            postJobStepForm();
        else if (isClicked(650, 330, 300, 60, mx, my))
            deleteJobScreen();
        else if (isClicked(650, 420, 300, 60, mx, my))
            running = false;
    }
}

int main() {
    initwindow(screenWidth, screenHeight, "Job Vacancy Platform");
    showMainMenu();
    closegraph();
    return 0;
}