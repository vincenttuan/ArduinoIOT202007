/*
  4-Digit 7-Segment display driver.
  2x 74HC595 wired to 2x 4-digit 7-segment displays
  bits 0-7 select a digit
  bits 8-14 A-G
  顯示文字showText('A','B','C','D');
  顯示數字showText(1,2,3,4);
  若要顯示小數點：該位數字＋10
*/

char disp_c[8] ;
const int SCLK_pin = 3;
const int RCLK_pin = 4;
const int DIO_pin = 5;
int  disp[8];

unsigned long prev = 0;
unsigned long waitMS = 0;

void setup() {
  pinMode(RCLK_pin, OUTPUT);
  pinMode(DIO_pin, OUTPUT);
  pinMode(SCLK_pin, OUTPUT);
  showText('O', 'P', 'E', 'N');
}

void loop() {
  showDisplay();
  showText(random(0, 9), 2, 3, 4);
  //wait(200);
}

void showText(char a, char b , char c, char d) {
  disp_c[0] = d;
  disp_c[1] = c;
  disp_c[2] = b;
  disp_c[3] = a;
}

void showDisplay() {
  setDisp();
  for (int i = 0; i < 8; i++) {
    setDigit(i, disp[i]);
  }
}

void setDigit(int dig, int character) {
  int digits[] = {
    128, 64, 32, 16, 8, 4, 2, 1
  };

  //character set (0-9)0-9
  //            (10-19)0.-9.
  //            (20-45)A-Z
  //            (46-71)a-z
  //            (72)- (73) space
  int characters[] = {
    3, 159, 37, 13, 153, 73, 65, 31, 1, 9,
    2, 158, 36, 12, 152, 72, 64, 30, 0, 8,
    17, 1, 99, 3, 97, 113, 67, 145, 243, 135, 145, 227, 85, 19, 3, 49, 25, 115, 73, 31, 129, 129, 169, 145, 137, 37,
    5, 193, 229, 133, 33, 113, 9, 209, 247, 143, 81, 227, 85, 213, 197, 49, 25, 245, 73, 225, 199, 199, 169, 145, 137, 37,
    253, 255
  };

  digitalWrite(RCLK_pin, LOW);
  shiftOut(DIO_pin, SCLK_pin, LSBFIRST, characters[character]);
  shiftOut(DIO_pin, SCLK_pin, LSBFIRST, digits[dig]);
  digitalWrite(RCLK_pin, HIGH);
}

void setDisp() {
  for (int i = 0; i < 8; i++) {
    int val = disp_c[i];
    if ((val >= 32) && (val <= 47)) {
      switch (val) {
        case 45 :
          val = 72;
          break;
        default :
          val = 73;
          break;
      }
    } else if ((val >= 48) && (val <= 57)) { //0-9
      val -= 48;
    }
    else if ((val >= 65) && (val <= 90)) { //A-Z
      val -= 45;
    }
    else if ((val >= 97) && (val <= 122)) { //a-z
      val -= 51;
    }

    disp[i] = val;

  }
}

void wait( unsigned long milsec) {
  prev = millis();
  waitMS = milsec;
}
