#include <iostream>
#include <Windows.h>
#include <array>
#include <math.h>
using namespace std;
int nScreenWidth = 120;
int nScreenHeight = 40;
float fPlayerX=8.0f;
float fPlayerY = 8.0f;
float fPlayerA = 0.0f;
float fFOV = 3.14159/4.0; 
float fDepth = 16.0f;

int nMapWidth = 16;				// World Dimensions
int nMapHeight = 16;

int main(){
    std::cout << "Hello There! \n" ;
    // int a = 1 << 1;
    char a=0b01100011;
    wchar_t* screen = new wchar_t[nScreenWidth*nScreenHeight];
    HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
    SetConsoleActiveScreenBuffer(hConsole);
    DWORD dwBytesWritten = 0;
    wstring map;
    map += L"################";
    map += L"#..............#";    
    map += L"#..............#";    
    map += L"#..............#";    
    map += L"#..............#";    
    map += L"#..............#";    
    map += L"#..............#";    
    map += L"#..............#";    
    map += L"#..............#";    
    map += L"#..............#";    
    map += L"#..............#";    
    map += L"#..............#";    
    map += L"#..............#";    
    map += L"#..............#";    
    map += L"#..............#";    
    map += L"################";

    while(true){
        for (size_t x=0; x< nScreenWidth; x++){
            float fRayAngle = (fPlayerA - fFOV / 2.0f) + ((float)x / (float)nScreenWidth) * fFOV;
            float fDistanceToWall = 0; 
            bool bHitWall = false;

            float fEyeX = sinf(fRayAngle);
            float fEyeY = cosf(fRayAngle);



            while (!bHitWall && fDistanceToWall <  fDepth){
                fDistanceToWall += 0.1f;
                int nTestX = (int)(fPlayerX + fEyeX * fDistanceToWall);
                int nTestY = (int)(fPlayerY + fEyeY * fDistanceToWall);
                
                if (nTestX < 0 || nTestX >= nMapWidth || nTestY < 0 || nTestY >= nMapHeight){
                bHitWall = true;
                fDistanceToWall = fDepth;
                }else{
                    if (map[nTestY * nMapWidth + nTestX] == 0){
                        bHitWall = true;
                    }
                }
            }
            int nCeiling = (float)(nScreenHeight/2.0) - nScreenHeight / ((float)fDistanceToWall);
            int nFloor = nScreenHeight - nCeiling;
            for (int y=0; y< nScreenHeight; y++){
                if(y< nCeiling){
                    screen[y* nScreenWidth + x] = ' ';
                }else if(y>nCeiling && y <= nFloor){
                    std::cout << "This is a text \n" ;
                    screen[y*nScreenWidth + x] = '#';
                }else{
                    screen[y* nScreenWidth + x] = ' ';
                }
            }
        }
    screen[nScreenWidth * nScreenHeight -1] = '\0';
    WriteConsoleOutputCharacterW(hConsole, screen, nScreenWidth * nScreenHeight,  {0,0}, &dwBytesWritten);
    }

    return 0;
}