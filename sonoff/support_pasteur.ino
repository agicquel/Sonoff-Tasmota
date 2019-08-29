#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_DotStarMatrix.h>
#include <Adafruit_DotStar.h>


#define APA102MATRIX_WIDTH  72
#define APA102MATRIX_HEIGHT 6

#define CLOCKPIN 12 
#define DATAPIN  14



Adafruit_DotStarMatrix *matrix;
uint16_t colors[3];
int pass = 0;
unsigned long pasteur_debounce = 10000;
char * pasteur_matrix_str = "B O N J O U R";
bool pasteur_matrix_flag = false;
int x = APA102MATRIX_WIDTH;

void PasteurNewText(char * cmnd_str){
    if(strcmp(pasteur_matrix_str,cmnd_str+19)){
        strcpy(pasteur_matrix_str,cmnd_str+19);
        x = matrix->width();
    }
}

void PasteurInit(void){
    matrix = new Adafruit_DotStarMatrix(
        APA102MATRIX_WIDTH, APA102MATRIX_HEIGHT,
        pin[GPIO_PASTEUR_DATA], pin[GPIO_PASTEUR_CLK],
        DS_MATRIX_TOP  + DS_MATRIX_RIGHT + DS_MATRIX_ROWS + DS_MATRIX_ZIGZAG,
        DOTSTAR_BRG);
    matrix->begin();
    matrix->setBrightness(10);
    matrix->setTextWrap(false);
    matrix->setTextColor(matrix->Color(0, 0, 255));

    AddLog_P(LOG_LEVEL_INFO, PSTR(D_LOG_APPLICATION "Pasteur Maxtrix init"));


}

void PasteurLoop(void){
    if (TimeReached(pasteur_debounce)) {
        SetNextTimeInterval(pasteur_debounce, 70); 

        matrix->fillScreen(0);
        matrix->setCursor(x, 0);
        matrix->print(pasteur_matrix_str);

        
        if(--x < -(APA102MATRIX_WIDTH*3)) {
            x = matrix->width();

        }
        matrix->show();
    }
}