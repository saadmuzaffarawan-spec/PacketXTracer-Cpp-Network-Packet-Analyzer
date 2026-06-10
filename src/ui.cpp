#include "raylib.h"
#include "ui.h"
#include "networking.h"

#include <fstream>
#include <iostream>
#include <string>
#include <ctime>

enum menustate{
    StartMenu,
    Analyzer,
    About
};

menustate currentstate = StartMenu;

bool escape = false;

//Start Button for the menu
std::string Start = "Start.Analyzing";

//to check the text width we used this measuretext function
int titlewidth = MeasureText("Start.Analyzing", 40);

Rectangle Startbtn = {
    float((1280-titlewidth)/2),// this is x position
    350,// this is y axis
    340, //width
    60 // height
};

//Table Rectangle
float tableX = 0.0f;
float tableY = 100.0f;
float tableW = 850.0f;
float tableH = 600.0f;

Rectangle table = {
    tableX,
    tableY,
    tableW,
    tableH
};

//TABLE HEADER

float headerH = 40.0f;

Rectangle tableHeader = {
    tableX,
    tableY,
    tableW,
    headerH
};

//Selected Table

float selectedX = 850.0f;
float selectedY = 100.0f;
float selectedW = 430.0f;
float selectedH = 600.0f;

Rectangle selectedTable = {
    selectedX,
    selectedY,
    selectedW,
    selectedH
};

float selectedbase = 140.0f;

float RectX = 900.0f;
float RectY = selectedbase;
float RectW = 380.0f;
float RectH = 25.0f;

Rectangle selectedRect = {
    RectX,
    RectY,
    RectW,
    RectH
};

//Selected packet object to store the selected packet and display its
//details

Packetdetail selectedPacket;
bool packetSelected =false;

//Selected packet color change permananantly

int clickedpacket = -1; //-1 meaning that no packet is clicked yet

//hover boolean
bool hover =false;

//ScrollIng

int scroll = 0;
Color rowColor = Color{24, 31, 38, 255};
Color borderColor = Color{45, 55, 65, 255};
Color text = RAYWHITE;

bool darkMode = false;   // false means Wireshark light mode
bool autoScroll = true;  // true meaning keep following latest packets

Font cyberFont;

//fstream cpp librry for file handling
//Function to save the packets details in a file
// new session heading every time the app opens
void StartPacketLogSession()
{
    std::ofstream file("Examples/packetx_packets_log.txt", std::ios::app);

    if (!file.is_open())
    {
        return;
    }

    time_t now = time(0);

    file << "\n========================================\n";
    file << "NEW PACKETX TRACER SESSION STARTED\n";
    file << "Time: " << ctime(&now);
    file << "========================================\n\n";

    file.close();
}


// Saves one packet into the log file
void SavePacketToLog(Packetdetail p, int packetNumber)
{
    std::ofstream file("Examples/packetx_packets_log.txt", std::ios::app);

    if (!file.is_open())
    {
        return;
    }

    time_t now = time(0);

    file << "----------------------------------------\n";
    file << "Packet No: " << packetNumber << "\n";
    file << "Time: " << ctime(&now);
    file << "Protocol: " << p.getProtocol() << "\n";
    file << "Source IP: " << p.getSourceIp() << "\n";
    file << "Destination IP: " << p.getDestIp() << "\n";
    file << "Source Port: " << p.getSrcPort() << "\n";
    file << "Destination Port: " << p.getDestPort() << "\n";
    file << "Size: " << p.getSize() << " bytes\n";
    file << "----------------------------------------\n\n";

    file.close();
}


// Automatically saves only new packets
void SaveNewPacketsToLog()
{
    static int lastSavedPacket = 0;
    if (lastSavedPacket > int(capturedPackets.size()))
    {
        lastSavedPacket = 0;
    }
    for (int i = lastSavedPacket; i < int(int(capturedPackets.size())); i++)
    {
        SavePacketToLog(capturedPackets[i], i);
    }
    lastSavedPacket = int(capturedPackets.size());
}

template <typename T>
T limitValue(T value, T min, T max){
    if(value < min) return min;
    if(value > max) return max;
    return value;
}

void DrawInfoBox(float x, float y, float w, float h,
                 const char* label,
                 Color bg, Color border, Color textColor){
    DrawRectangle(x, y, w, h, bg);
    DrawRectangleLinesEx({x, y, w, h}, 1.0f, border);
    DrawText(label, x + 10, y + 7, 16, textColor);
}


void RunUI(){

    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_MSAA_4X_HINT );

    InitWindow(1280, 720, "PACKETx TRACER");
    SetTargetFPS(60);
    
    cyberFont = LoadFontEx(
        "JetBrains_Mono/static/JetBrainsMono-Regular.ttf",
        24,
        0,
        0
    );

    StartPacketLogSession();

    while (!escape)
    {
        if(IsKeyPressed(KEY_ESCAPE)){escape =true;}

        Vector2 mouse = GetMousePosition();

    int screenW = GetScreenWidth();
    int screenH = GetScreenHeight();

    if(IsKeyPressed(KEY_T)){
     darkMode = !darkMode;
    }

    if(IsKeyPressed(KEY_END)){
     autoScroll = true;
    }

    Color bg;
    Color panel;
    Color header;
    Color rowLine;
    Color mainText;

    if(darkMode){
    bg = Color{8, 12, 18, 255};
    panel = Color{15, 22, 30, 255};
    header = Color{25, 35, 45, 255};
    rowLine = Color{45, 55, 65, 255};
    mainText = RAYWHITE;
    }
    else{
    bg = Color{245, 247, 250, 255};
    panel = Color{255, 255, 255, 255};
    header = Color{230, 235, 242, 255};
    rowLine = Color{190, 200, 210, 255};
    mainText = BLACK;
    }

        BeginDrawing();
        ClearBackground(bg);

        //made these for debug but not required now
        // DrawRectangle(0, 0, 1280, 720, Fade(BLACK, 0.15f));

        // for(int i=0; i<720; i+=30){
        //     DrawLine(0,i,1280, i, GRAY);
        // }
        // for(int j=0; j<1280; j+=30){
        //     DrawLine(j,0,j, 720, GRAY);
        // }

        

        // DrawText(TextFormat("x:%d", "y:%d",(int)mouse.x, (int)mouse.y),
        // mouse.x+20, mouse.y+10, 15.0f, RED);

        if(currentstate == StartMenu){

            Color menuTitle = darkMode ? GREEN : Color{0, 80, 40, 255};
            Color menuText  = darkMode ? RAYWHITE : BLACK;
            Color buttonBg  = CheckCollisionPointRec(mouse, Startbtn) ? GREEN : Color{20, 120, 60, 255};
            Color buttonText = BLACK;

            int titleW   = MeasureText("PACKETX TRACER", 70);
            int subW     = MeasureText("Beginner Network Packet Analyzer", 24);
            int btnTextW = MeasureText(Start.c_str(), 40);

            Startbtn.x = (screenW - Startbtn.width) / 2;
            Startbtn.y = 360;

            DrawText("PACKETX TRACER", (screenW - titleW) / 2, 190, 70, menuTitle);
            DrawText("Beginner Network Packet Analyzer", (screenW - subW) / 2, 275, 24, menuText);

            DrawRectangleRec(Startbtn, buttonBg);
            DrawRectangleLinesEx(Startbtn, 2.0f, menuTitle);

            DrawText(Start.c_str(),
                     Startbtn.x + (Startbtn.width - btnTextW) / 2,
                     Startbtn.y + 10,
                     40,
                     buttonText);

            if((CheckCollisionPointRec(mouse, Startbtn) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) ||
                IsKeyPressed(KEY_ENTER)){
                currentstate = Analyzer;
            }
        }
        
        if(currentstate == Analyzer){

        SaveNewPacketsToLog();
            
        if(IsKeyPressed(KEY_BACKSPACE)) currentstate = StartMenu;

       tableX = 20;
       tableY = 100;
       tableW = screenW * 0.66f;
       tableH = screenH - 120;

       selectedX = tableX + tableW;
       selectedY = tableY;
       selectedW = screenW - selectedX - 20;
       selectedH = tableH;

       table = {tableX, tableY, tableW, tableH};
       tableHeader = {tableX, tableY, tableW, headerH};
       selectedTable = {selectedX, selectedY, selectedW, selectedH};
    
        DrawRectangleRec(table, panel);
        DrawRectangleRec(selectedTable, panel);
        DrawRectangleLinesEx(selectedTable, 2.0f, GREEN);

        DrawTextEx(
            cyberFont,
            "PACKETX LIVE ANALYZER",
            {20,25},
            28,
            1,
            mainText
        );

        DrawText(TextFormat("Packets: %d", (int)int(capturedPackets.size())),
        20, 60, 24,GREEN);

        DrawRectangleRec(table, panel);

        DrawRectangleRec(tableHeader, header);
        DrawRectangleLinesEx(tableHeader, 2.0f, GREEN);

        float noX     = tableX + 10;

        float sourceX = tableX + 50;

        float destX   = tableX + 205;
        float protoX  = tableX + 410;
        float portsX  = tableX + 515;
        float sizeX   = tableX + 690;

        DrawText("No.",         noX,     tableY + 12, 16, mainText);
        DrawText("Source",      sourceX, tableY + 12, 16, mainText);
        DrawText("Destination", destX,   tableY + 12, 16, mainText);
        DrawText("Protocol",    protoX,  tableY + 12, 16, mainText);
        DrawText("Ports",       portsX,  tableY + 12, 16, mainText);
        DrawText("Size",        sizeX,   tableY + 12, 16, mainText);

        DrawLine(sourceX - 10, tableY, sourceX - 10, tableY + tableH, rowLine);
        DrawLine(destX   - 10, tableY, destX   - 10, tableY + tableH, rowLine);
        DrawLine(protoX  - 10, tableY, protoX  - 10, tableY + tableH, rowLine);
        DrawLine(portsX  - 10, tableY, portsX  - 10, tableY + tableH, rowLine);
        DrawLine(sizeX   - 10, tableY, sizeX   - 10, tableY + tableH, rowLine);

        //Scrolling Logic

        int rowHeight = 30;
int visibleRows = (tableH - headerH) / rowHeight;

float wheel = GetMouseWheelMove();

    if(wheel > 0){
    scroll--;
    autoScroll = false;
     }

    if(wheel < 0){
    scroll++;
    autoScroll = false;
     }

     int maxScroll = int(int(capturedPackets.size())) - visibleRows;

    if(maxScroll < 0){
    maxScroll = 0;
     }

    scroll = limitValue(scroll, 0, maxScroll);

    if(autoScroll){
    scroll = maxScroll;
     }

        for(int rowIndex = 0; rowIndex < visibleRows; rowIndex++){

            int packetIndex = scroll + rowIndex;

            if(packetIndex >= int(capturedPackets.size())) break;

            Packetdetail p = capturedPackets[packetIndex];
            //Packet Display

        Rectangle Row={
            tableX,//x pos will remian 20, every packets starts from 20 pixels
            float(tableY + headerH + rowIndex*30),//y, so it starts after the header and some space
            tableW,//width,
            30,//height
          };

            rowColor = panel;
            borderColor = rowLine;
            text = mainText;

    if(p.getProtocol() == "TCP"){
        
      if(darkMode){
        rowColor = Color{18, 35, 55, 255};
        borderColor = SKYBLUE;
        text = RAYWHITE;
    }
    else{
        rowColor = RAYWHITE;
        borderColor = BLACK;
        text = BLACK;
    }
}

    else if(p.getProtocol() == "UDP"){
      if(darkMode){
        rowColor = Color{45, 32, 15, 255};
        borderColor = ORANGE;
        text = RAYWHITE;
      }

    else{
        rowColor = LIGHTGRAY;
        borderColor = GRAY;
        text = BLACK;
    }

}
    else if(p.getSourceIp() == "NULL"){
        if(darkMode){
           rowColor = Color{55, 25, 25, 255};
           borderColor = RED;
           text = RAYWHITE;
        }

    else{
           rowColor = GRAY;
           borderColor = WHITE;
           text = RAYWHITE;
    }
}
        else if(p.getProtocol() == "ARP"){
          if(darkMode){
           rowColor = Color{20, 35, 55, 255};
           borderColor = GOLD;
           text = RAYWHITE;
        }
        else{
        rowColor = BLUE;
        borderColor = DARKBLUE;
        text = RAYWHITE;
    }
}

            if(CheckCollisionPointRec(GetMousePosition(), Row)){
               rowColor    = Color{185, 220, 255, 255};
               borderColor = SKYBLUE;
               text        = BLACK;

            if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
               packetSelected = true; 
               selectedPacket = p;
               clickedpacket = packetIndex;
              }
            }


            if(packetIndex == clickedpacket){
               rowColor = Color{30, 65, 95, 255};
               borderColor = SKYBLUE;
               text = RAYWHITE;
            }

            DrawRectangleRec(Row, rowColor);
            DrawRectangleLinesEx(Row, 1.0f, borderColor);


            // row text now uses the same column positions as header
            // so every column is perfectly aligned
            Color protoText = text;

            if(p.getProtocol() == "TCP"){
                protoText = SKYBLUE;
            }
            else if(p.getProtocol() == "UDP"){
                protoText = ORANGE;
            }
            else if(p.getProtocol() == "ARP"){
                protoText = GOLD;
            }
            else if(p.getProtocol() == "ICMP"){
                protoText = RED;
            }

            DrawText(TextFormat("%d", packetIndex), noX, Row.y + 7, 14, text);
            DrawText(p.getSourceIp().c_str(), sourceX, Row.y + 7, 14, text);
            DrawText(p.getDestIp().c_str(), destX, Row.y + 7, 14, text);
            DrawText(p.getProtocol().c_str(), protoX, Row.y + 7, 14, protoText);
            DrawText(TextFormat("%d --> %d", p.getSrcPort(), p.getDestPort()), portsX, Row.y + 7, 14, text);
            DrawText(TextFormat("%d", (int)p.getSize()), sizeX, Row.y + 7, 14, text);    }

        if(packetSelected){

            float detailX = selectedX + 25;
            float detailY = selectedY + 80;
            float detailW = selectedW - 50;
            float detailH = 34;

            DrawText("Selected Packet", selectedX + 25, selectedY + 25, 28, mainText);

            DrawInfoBox(detailX, detailY, detailW, detailH,TextFormat("Protocol: %s", selectedPacket.getProtocol().c_str()),header, rowLine, mainText);

            detailY += 45;

            DrawInfoBox(detailX, detailY, detailW, detailH,TextFormat("Source IP: %s", selectedPacket.getSourceIp().c_str()),header, rowLine, mainText);

            detailY += 45;

            DrawInfoBox(detailX, detailY, detailW, detailH,TextFormat("Destination IP: %s", selectedPacket.getDestIp().c_str()),header, rowLine, mainText);

            detailY += 45;

            DrawInfoBox(detailX, detailY, detailW, detailH,TextFormat("Source Port: %d", selectedPacket.getSrcPort()),header, rowLine, mainText);

            detailY += 45;

            DrawInfoBox(detailX, detailY, detailW, detailH,TextFormat("Destination Port: %d", selectedPacket.getDestPort()),header, rowLine, mainText);
                
            detailY += 45;

            DrawInfoBox(detailX, detailY, detailW, detailH,TextFormat("Size: %d bytes", (int)selectedPacket.getSize()),header, rowLine, mainText);
        }

        else{
            DrawText("Click a packet row", selectedX + 35, selectedY + 250, 22, mainText);
        }

        DrawText("[T] Theme   [Mouse Wheel] Scroll  [END] Live Bottom   [AUTO] Packet Logging   [BACKSPACE] Menu",
              20,
             screenH - 25,
             16,
             mainText);
    }


    if(currentstate == About){
    DrawText("About PACKETX", 40, 40, 35, GREEN);
    }
    
    EndDrawing();
    
}

    UnloadFont(cyberFont);

    CloseWindow();
    
}