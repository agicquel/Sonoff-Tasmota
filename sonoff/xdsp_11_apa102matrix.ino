// #ifdef USE_SPI
// #ifdef USE_DISPLAY
// #ifdef USE_DISPLAY_APA102MATRIX

// #define XDSP_11                11 // a ajouter dans l'interface

// #include <SPI.h>
// #include <Adafruit_GFX.h>
// #include <Adafruit_DotStarMatrix.h>
// #include <Adafruit_DotStar.h>


// #define APA102MATRIX_WIDTH  72
// #define APA102MATRIX_HEIGHT 6

// #define DATAPIN  pin[] //a changé pour pin[matrix clock] pin[matrix data]
// #define CLOCKPIN pin[]

// Adafruit_DotStarMatrix *matrix;

// const uint16_t colors[] = { matrix.Color(255, 0, 0), matrix.Color(0, 255, 0), matrix.Color(0, 0,255) };

// void APA102MatrixInitMode(void)
// {
//     //   tft->setRotation(Settings.display_rotate);  // 0
//     //   tft->invertDisplay(0);
//     //   tft->fillScreen(ILI9341_BLACK);
//     //   tft->setTextWrap(false);         // Allow text to run off edges
//     //   tft->cp437(true);
//     //   if (!Settings.display_mode) {
//     //     tft->setCursor(0, 0);
//     //     tft->setTextColor(ILI9341_WHITE, ILI9341_BLACK);
//     //     tft->setTextSize(1);
//     //   } else {
//     //     tft->setScrollMargins(TFT_TOP, TFT_BOTTOM);
//     //     tft->setCursor(0, 0);
//     //     tft->setTextColor(ILI9341_YELLOW, ILI9341_BLACK);
//     //     tft->setTextSize(2);
//     //     tft->println("HEADER");
//     //     tft_scroll = TFT_TOP;
//     //   }

    

//     //matrix->begin(); 
//     matrix->setTextWrap(false);
//     matrix->setBrightness(50);
//     matrix->setTextColor(colors[0]);
// }

// void APA102MatrixInit(uint8_t mode)
// {
//   switch(mode) {
//     case DISPLAY_INIT_MODE:
//       APA102MatrixInitMode();
//       break;
//     case DISPLAY_INIT_PARTIAL:
//     case DISPLAY_INIT_FULL:
//       break;
//   }
// }

// void APA102MatrixInitDriver(void)
// {
//   if (!Settings.display_model) {
//     Settings.display_model = XDSP_11;
//   }

//   if (XDSP_11 == Settings.display_model) {
//     if (Settings.display_width != APA102MATRIX_WIDTH) {
//       Settings.display_width = APA102MATRIX_WIDTH;
//     }
//     if (Settings.display_height != APA102MATRIX_HEIGHT) {
//       Settings.display_height = APA102MATRIX_HEIGHT;
//     }
//     //tft = new Adafruit_ILI9341(pin[GPIO_SPI_CS], pin[GPIO_SPI_DC]);
//     matrix = new Adafruit_DotStarMatrix(
//         APA102MATRIX_WIDTH, APA102MATRIX_HEIGHT,
//         DATAPIN, CLOCKPIN,
//         DS_MATRIX_TOP  + DS_MATRIX_RIGHT + DS_MATRIX_ROWS + DS_MATRIX_ZIGZAG,
//         DOTSTAR_BRG);
//     matrix->begin();

// #ifdef USE_DISPLAY_MODES1TO5
//     if (Settings.display_rotate) {
//       DisplayAllocScreenBuffer();
//     }
// #endif  // USE_DISPLAY_MODES1TO5

//     APA102MatrixInitMode();
//   }
// }

// void APA102MatrixClear(void)
// {
//   matrix->fillScreen(0x0000);
//   matrix->setCursor(0, 0);
// }

// void APA102MatrixDrawStringAt(uint16_t x, uint16_t y, char *str, uint16_t color, uint8_t flag)
// {
// //   uint16_t active_color = ILI9341_WHITE;

// //   tft->setTextSize(Settings.display_size);
// //   if (!flag) {
// //     tft->setCursor(x, y);
// //   } else {
// //     tft->setCursor((x-1) * TFT_FONT_WIDTH * Settings.display_size, (y-1) * TFT_FONT_HEIGTH * Settings.display_size);
// //   }
// //   if (color) { active_color = color; }
// //   tft->setTextColor(active_color, ILI9341_BLACK);
// //   tft->println(str);

//   tft->setCursor(x, y);
//   matrix->print(str);
// }

// void APA102MatrixDisplayOnOff(uint8_t on)
// {
// }

// void APA102MatrixOnOff(void)
// {
// }



// //-------------------------------------------------------------------------------------------------------



// #ifdef USE_DISPLAY_MODES1TO5

// void APA102MatrixPrintLog(void)
// {
// //   disp_refresh--;
// //   if (!disp_refresh) {
// //     disp_refresh = Settings.display_refresh;
// //     if (Settings.display_rotate) {
// //       if (!disp_screen_buffer_cols) { DisplayAllocScreenBuffer(); }
// //     }

// //     char* txt = DisplayLogBuffer('\370');
// //     if (txt != nullptr) {
// //       uint8_t size = Settings.display_size;
// //       uint16_t theight = size * TFT_FONT_HEIGTH;

// //       tft->setTextSize(size);
// //       tft->setTextColor(ILI9341_CYAN, ILI9341_BLACK);  // Add background color to solve flicker
// //       if (!Settings.display_rotate) {  // Use hardware scroll
// //         tft->setCursor(0, tft_scroll);
// //         tft->fillRect(0, tft_scroll, tft->width(), theight, ILI9341_BLACK);  // Erase line
// //         tft->print(txt);
// //         tft_scroll += theight;
// //         if (tft_scroll >= (tft->height() - TFT_BOTTOM)) {
// //           tft_scroll = TFT_TOP;
// //         }
// //         tft->scrollTo(tft_scroll);
// //       } else {
// //         uint8_t last_row = Settings.display_rows -1;

// //         tft_scroll = theight;  // Start below header
// //         tft->setCursor(0, tft_scroll);
// //         for (uint32_t i = 0; i < last_row; i++) {
// //           strlcpy(disp_screen_buffer[i], disp_screen_buffer[i +1], disp_screen_buffer_cols);
// // //          tft->fillRect(0, tft_scroll, tft->width(), theight, ILI9341_BLACK);  // Erase line
// //           tft->print(disp_screen_buffer[i]);
// //           tft_scroll += theight;
// //           tft->setCursor(0, tft_scroll);
// //           delay(1);  // Fix background runs heap usage due to long runtime of this loop (up to 1 second)
// //         }
// //         strlcpy(disp_screen_buffer[last_row], txt, disp_screen_buffer_cols);
// //         DisplayFillScreen(last_row);
// //         tft->print(disp_screen_buffer[last_row]);
// //       }
// //       AddLog_P2(LOG_LEVEL_DEBUG, PSTR(D_LOG_APPLICATION "[%s]"), txt);
// //     }
// //   }
// }

// void APA102MatrixRefresh(void)  // Every second
// {
// //   if (Settings.display_mode) {  // Mode 0 is User text
// //     char tftdt[Settings.display_cols[0] +1];
// //     char date4[11];  // 24-04-2017
// //     char space[Settings.display_cols[0] - 17];
// //     char time[9];    // 13:45:43

// //     tft->setTextSize(2);
// //     tft->setTextColor(ILI9341_YELLOW, ILI9341_RED);   // Add background color to solve flicker
// //     tft->setCursor(0, 0);

// //     snprintf_P(date4, sizeof(date4), PSTR("%02d" D_MONTH_DAY_SEPARATOR "%02d" D_YEAR_MONTH_SEPARATOR "%04d"), RtcTime.day_of_month, RtcTime.month, RtcTime.year);
// //     memset(space, 0x20, sizeof(space));
// //     space[sizeof(space) -1] = '\0';
// //     snprintf_P(time, sizeof(time), PSTR("%02d" D_HOUR_MINUTE_SEPARATOR "%02d" D_MINUTE_SECOND_SEPARATOR "%02d"), RtcTime.hour, RtcTime.minute, RtcTime.second);
// //     snprintf_P(tftdt, sizeof(tftdt), PSTR("%s%s%s"), date4, space, time);

// //     tft->print(tftdt);

// //     switch (Settings.display_mode) {
// //       case 1:  // Text
// //       case 2:  // Local
// //       case 3:  // Local
// //       case 4:  // Mqtt
// //       case 5:  // Mqtt
// //         Ili9341PrintLog();
// //         break;
// //     }
// //   }
// }

// #endif  // USE_DISPLAY_MODES1TO5

// /*********************************************************************************************************************************************************************************\
//  * Interface
// \*********************************************************************************************************************************************************************************/

// bool Xdsp11(uint8_t function)
// {
//   bool result = false;

//   if (spi_flg) {
//     if (FUNC_DISPLAY_INIT_DRIVER == function) {
//       APA102MatrixInitDriver();
//     }
//     else if (XDSP_11 == Settings.display_model) {

//       if (!dsp_color) { dsp_color = 0xFFFF }
      
//       switch (function) {
//         case FUNC_DISPLAY_MODEL:
//           result = true;
//           break;
//         case FUNC_DISPLAY_INIT:
//           APA102MatrixInit(dsp_init);
//           break;
//         case FUNC_DISPLAY_POWER:
//           APA102MatrixOnOff();
//           break;
//         case FUNC_DISPLAY_CLEAR:
//           APA102MatrixClear();
//           break;
//         case FUNC_DISPLAY_DRAW_HLINE:
//           matrix->writeFastHLine(dsp_x, dsp_y, dsp_len, dsp_color);
//           break;
//         case FUNC_DISPLAY_DRAW_VLINE:
//           matrix->writeFastVLine(dsp_x, dsp_y, dsp_len, dsp_color);
//           break;
//         case FUNC_DISPLAY_DRAW_LINE:
//           matrix->writeLine(dsp_x, dsp_y, dsp_x2, dsp_y2, dsp_color);
//           break;
//         case FUNC_DISPLAY_DRAW_CIRCLE:
//           matrix->drawCircle(dsp_x, dsp_y, dsp_rad, dsp_color);
//           break;
//         case FUNC_DISPLAY_FILL_CIRCLE:
//           matrix->fillCircle(dsp_x, dsp_y, dsp_rad, dsp_color);
//           break;
//         case FUNC_DISPLAY_DRAW_RECTANGLE:
//           matrix->drawRect(dsp_x, dsp_y, dsp_x2, dsp_y2, dsp_color);
//           break;
//         case FUNC_DISPLAY_FILL_RECTANGLE:
//           matrix->fillRect(dsp_x, dsp_y, dsp_x2, dsp_y2, dsp_color);
//           break;
// //        case FUNC_DISPLAY_DRAW_FRAME:
// //          oled->display();
// //          break;
//         case FUNC_DISPLAY_TEXT_SIZE:
//           matrix->setTextSize(Settings.display_size);
//           break;
//         case FUNC_DISPLAY_FONT_SIZE:
// //          matrix->setTextSize(Settings.display_font);
//           break;
//         case FUNC_DISPLAY_DRAW_STRING:
//           APA102MatrixDrawStringAt(dsp_x, dsp_y, dsp_str, dsp_color, dsp_flag);
//           break;
//         case FUNC_DISPLAY_ONOFF:
//           APA102MatrixDisplayOnOff(dsp_on);
//           break;
//         case FUNC_DISPLAY_ROTATION:
//           matrix->setRotation(Settings.display_rotate);
//           break;
// #ifdef USE_DISPLAY_MODES1TO5
//         case FUNC_DISPLAY_EVERY_SECOND:
//           //APA102MatrixRefresh();
//           break;
// #endif  // USE_DISPLAY_MODES1TO5
//       }
//     }
//   }
//   return result;
// }

// #endif  // USE_DISPLAY_ILI9341
// #endif  // USE_DISPLAY
// #endif  // USE_SPI


