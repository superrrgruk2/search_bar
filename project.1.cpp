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


void give_coordinate() {
	int x , y;
    while (!kbhit()) {
        if (ismouseclick(WM_LBUTTONDOWN)) {
            getmouseclick(WM_LBUTTONDOWN, x, y);
            printf("%d \t %d \n", x, y);
        }
    }
}

void background_images()
{
	readimagefile("C:\\Users\\user\\OneDrive\\Documents\\Ball Catcher\\converted_image.bmp", 0 ,0 , 1200 , 700);
}

void drawScreen(const char input[]) {
    // Set background to white
   
  background_images();
  
    // Title
  
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 7);        
    setcolor(WHITE);
    // Font for "JOBIFY"
        setfillstyle(SOLID_FILL, LIGHTGRAY);
    bar(435     , 55 ,780  ,111);
    outtextxy(440, 50, (char*)"JOBIFY");

    // Search Box
    setcolor(WHITE);
    rectangle(320, 200, 1000, 240); 
    
    setfillstyle(SOLID_FILL, BLACK);
    bar(321, 201, 999, 239); 
    
     // User input shown here
     setcolor(WHITE);
    settextstyle(SIMPLEX_FONT, HORIZ_DIR, 2); // Only one settextstyle needed
    outtextxy(340, 210, (char*)input);
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
            outtextxy(350, y, jobs[i]); // Display the matching job
            y += 30;
            found = true;
        }
    }

    if (!found) {
    	setcolor(RED);
    	 settextstyle(SIMPLEX_FONT, HORIZ_DIR, 3); 
        outtextxy(450, y + 100, (char*)"No matching jobs found."); // Message if no jobs match
    }
}

int main() {
   initwindow(1200 , 700  , (char*)" JOBIFY ");
   background_images();

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
    return 0;
}
