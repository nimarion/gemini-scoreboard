#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <Adafruit_NeoPixel.h>
#include <Credentials.h>

#ifndef NUM_LEDS
#define NUM_LEDS 256
#define DATA_PIN D4
#define MATRIX_WIDTH 32 // Width of the matrix
#define MATRIX_HEIGHT 8 // Height of the matrix
#endif

const char *ssid = WIFI_SSID;
const char *password = WIFI_PW;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, DATA_PIN, NEO_GRB + NEO_KHZ800);

int openBracket[7][5] = {
    {0, 1},
    {1, 0},
    {1, 0},
    {1, 0},
    {1, 0},
    {1, 0},
    {0, 1}};
int closedBracket[7][5] = {
    {1, 0},
    {0, 1},
    {0, 1},
    {0, 1},
    {0, 1},
    {0, 1},
    {1, 0}};
int slash[7][5] = {
    {0, 0, 0, 0, 1},
    {0, 0, 0, 1, 0},
    {0, 0, 0, 1, 0},
    {0, 0, 1, 0, 0},
    {0, 1, 0, 0, 0},
    {0, 1, 0, 0, 0},
    {1, 0, 0, 0, 0}};
int slash_reverse[7][5] = {
    {1, 0, 0, 0, 0},
    {0, 1, 0, 0, 0},
    {0, 1, 0, 0, 0},
    {0, 0, 1, 0, 0},
    {0, 0, 0, 1, 0},
    {0, 0, 0, 1, 0},
    {0, 0, 0, 0, 1}};
int equal[7][5] = {
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {1, 1, 1, 1},
    {0, 0, 0, 0},
    {1, 1, 1, 1},
    {0, 0, 0, 0},
    {0, 0, 0, 0}};
int greater[7][5] = {
    {1, 0, 0, 0},
    {0, 1, 0, 0},
    {0, 0, 1, 0},
    {0, 0, 0, 1},
    {0, 0, 1, 0},
    {0, 1, 0, 0},
    {1, 0, 0, 0}};
int less[7][5] = {
    {0, 0, 0, 1},
    {0, 0, 1, 0},
    {0, 1, 0, 0},
    {1, 0, 0, 0},
    {0, 1, 0, 0},
    {0, 0, 1, 0},
    {0, 0, 0, 1}};
int plus[7][5] = {
    {0, 0, 0, 0, 0},
    {0, 0, 1, 0, 0},
    {0, 0, 1, 0, 0},
    {1, 1, 1, 1, 1},
    {0, 0, 1, 0, 0},
    {0, 0, 1, 0, 0},
    {0, 0, 0, 0, 0}};
int minus[7][5] = {
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0},
    {1, 1, 1, 1, 1},
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0}};
int colon[7][5] = {
    {0, 0},
    {1, 1},
    {1, 1},
    {0, 0},
    {1, 1},
    {1, 1},
    {0, 0}};
int dot[7][5] = {
    {0, 0},
    {0, 0},
    {0, 0},
    {0, 0},
    {0, 0},
    {1, 1},
    {1, 1}};
int zero[7][5] = {
    {0, 1, 1, 1, 0},
    {1, 0, 0, 0, 1},
    {1, 1, 0, 0, 1},
    {1, 0, 1, 0, 1},
    {1, 0, 0, 1, 1},
    {1, 0, 0, 0, 1},
    {0, 1, 1, 1, 0}};
int one[7][5] = {
    {0, 0, 1, 0, 0},
    {0, 1, 1, 0, 0},
    {0, 0, 1, 0, 0},
    {0, 0, 1, 0, 0},
    {0, 0, 1, 0, 0},
    {0, 0, 1, 0, 0},
    {0, 1, 1, 1, 0}};
int two[7][5] = {
    {0, 1, 1, 1, 0},
    {1, 0, 0, 0, 1},
    {0, 0, 0, 0, 1},
    {0, 0, 0, 1, 0},
    {0, 0, 1, 0, 0},
    {0, 1, 0, 0, 0},
    {1, 1, 1, 1, 1}};
int three[7][5] = {
    {0, 1, 1, 1, 0},
    {1, 0, 0, 0, 1},
    {0, 0, 0, 0, 1},
    {0, 0, 1, 1, 0},
    {0, 0, 0, 0, 1},
    {1, 0, 0, 0, 1},
    {0, 1, 1, 1, 0}};
int four[7][5] = {
    {0, 0, 0, 1, 0},
    {0, 0, 1, 1, 0},
    {0, 1, 0, 1, 0},
    {1, 0, 0, 1, 0},
    {1, 1, 1, 1, 1},
    {0, 0, 0, 1, 0},
    {0, 0, 0, 1, 0}};
int five[7][5] = {
    {1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0},
    {1, 0, 0, 0, 0},
    {1, 1, 1, 1, 0},
    {0, 0, 0, 0, 1},
    {0, 0, 0, 0, 1},
    {1, 1, 1, 1, 0}};
int six[7][5] = {
    {0, 1, 1, 1, 0},
    {1, 0, 0, 0, 1},
    {1, 0, 0, 0, 0},
    {1, 1, 1, 1, 0},
    {1, 0, 0, 0, 1},
    {1, 0, 0, 0, 1},
    {0, 1, 1, 1, 0}};
int seven[7][5] = {
    {1, 1, 1, 1, 1},
    {0, 0, 0, 0, 1},
    {0, 0, 0, 1, 0},
    {0, 0, 1, 0, 0},
    {0, 0, 1, 0, 0},
    {0, 0, 1, 0, 0},
    {0, 0, 1, 0, 0}};
int eight[7][5] = {
    {0, 1, 1, 1, 0},
    {1, 0, 0, 0, 1},
    {1, 0, 0, 0, 1},
    {0, 1, 1, 1, 0},
    {1, 0, 0, 0, 1},
    {1, 0, 0, 0, 1},
    {0, 1, 1, 1, 0}};
int nine[7][5] = {
    {0, 1, 1, 1, 0},
    {1, 0, 0, 0, 1},
    {1, 0, 0, 0, 1},
    {0, 1, 1, 1, 1},
    {0, 0, 0, 0, 1},
    {1, 0, 0, 0, 1},
    {0, 1, 1, 1, 0}};
int a[7][5] = {
    {0, 1, 1, 1, 0},
    {1, 0, 0, 0, 1},
    {1, 0, 0, 0, 1},
    {1, 1, 1, 1, 1},
    {1, 0, 0, 0, 1},
    {1, 0, 0, 0, 1},
    {1, 0, 0, 0, 1}};
int b[7][5] = {
    {1, 1, 1, 1, 0},
    {1, 0, 0, 0, 1},
    {1, 0, 0, 0, 1},
    {1, 1, 1, 1, 1},
    {1, 0, 0, 0, 1},
    {1, 0, 0, 0, 1},
    {1, 1, 1, 1, 0}};
int c[7][5] = {
    {0, 1, 1, 1, 0},
    {1, 0, 0, 0, 1},
    {1, 0, 0, 0, 0},
    {1, 0, 0, 0, 0},
    {1, 0, 0, 0, 0},
    {1, 0, 0, 0, 1},
    {0, 1, 1, 1, 0}};
int d[7][5] = {
    {1, 1, 1, 1, 0},
    {1, 0, 0, 0, 1},
    {1, 0, 0, 0, 1},
    {1, 0, 0, 0, 1},
    {1, 0, 0, 0, 1},
    {1, 0, 0, 0, 1},
    {1, 1, 1, 1, 0}};
int e[7][5] = {
    {1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0},
    {1, 0, 0, 0, 0},
    {1, 1, 1, 1, 0},
    {1, 0, 0, 0, 0},
    {1, 0, 0, 0, 0},
    {1, 1, 1, 1, 1}};
int f[7][5] = {
    {1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0},
    {1, 0, 0, 0, 0},
    {1, 1, 1, 1, 0},
    {1, 0, 0, 0, 0},
    {1, 0, 0, 0, 0},
    {1, 0, 0, 0, 0}};
int g[7][5] = {
    {0, 1, 1, 1, 0},
    {1, 0, 0, 0, 1},
    {1, 0, 0, 0, 0},
    {1, 0, 1, 1, 1},
    {1, 0, 0, 0, 1},
    {1, 0, 0, 0, 1},
    {0, 1, 1, 1, 0}};
int h[7][5] = {
    {1, 0, 0, 0, 1},
    {1, 0, 0, 0, 1},
    {1, 0, 0, 0, 1},
    {1, 1, 1, 1, 1},
    {1, 0, 0, 0, 1},
    {1, 0, 0, 0, 1},
    {1, 0, 0, 0, 1}};
int i[7][5] = {
    {1, 1, 1},
    {0, 1, 0},
    {0, 1, 0},
    {0, 1, 0},
    {0, 1, 0},
    {0, 1, 0},
    {1, 1, 1}};
int j[7][5] = {
    {0, 1, 1, 1, 1},
    {0, 0, 0, 0, 1},
    {0, 0, 0, 0, 1},
    {0, 0, 0, 0, 1},
    {0, 0, 0, 0, 1},
    {1, 0, 0, 0, 1},
    {0, 1, 1, 1, 0}};
int k[7][5] = {
    {1, 0, 0, 0, 1},
    {1, 0, 0, 0, 1},
    {1, 0, 0, 1, 0},
    {1, 1, 1, 0, 0},
    {1, 0, 0, 1, 0},
    {1, 0, 0, 0, 1},
    {1, 0, 0, 0, 1}};
int l[7][5] = {
    {1, 0, 0, 0},
    {1, 0, 0, 0},
    {1, 0, 0, 0},
    {1, 0, 0, 0},
    {1, 0, 0, 0},
    {1, 0, 0, 0},
    {1, 1, 1, 1}};
int r[7][5] = {
    {1, 1, 1, 1, 0},
    {1, 0, 0, 0, 1},
    {1, 0, 0, 0, 1},
    {1, 1, 1, 1, 0},
    {1, 0, 0, 0, 1},
    {1, 0, 0, 0, 1},
    {1, 0, 0, 0, 1}};
int s[7][5] = {
    {0, 1, 1, 1, 0},
    {1, 0, 0, 0, 1},
    {1, 0, 0, 0, 0},
    {0, 1, 1, 1, 0},
    {0, 0, 0, 0, 1},
    {1, 0, 0, 0, 1},
    {0, 1, 1, 1, 0}};
int m[7][5] = {
    {1, 0, 0, 0, 1},
    {1, 1, 0, 1, 1},
    {1, 0, 1, 0, 1},
    {1, 0, 0, 0, 1},
    {1, 0, 0, 0, 1},
    {1, 0, 0, 0, 1},
    {1, 0, 0, 0, 1}};
int n[7][5] = {
    {1, 0, 0, 0, 1},
    {1, 0, 0, 0, 1},
    {1, 1, 0, 0, 1},
    {1, 0, 1, 0, 1},
    {1, 0, 0, 1, 1},
    {1, 0, 0, 0, 1},
    {1, 0, 0, 0, 1}};
int o[7][5] = {
    {0, 1, 1, 1, 0},
    {1, 0, 0, 0, 1},
    {1, 0, 0, 0, 1},
    {1, 0, 0, 0, 1},
    {1, 0, 0, 0, 1},
    {1, 0, 0, 0, 1},
    {0, 1, 1, 1, 0}};
int p[7][5] = {
    {1, 1, 1, 1, 0},
    {1, 0, 0, 0, 1},
    {1, 0, 0, 0, 1},
    {1, 1, 1, 1, 0},
    {1, 0, 0, 0, 0},
    {1, 0, 0, 0, 0},
    {1, 0, 0, 0, 0}};
int q_a[7][5] = {
    {0, 1, 1, 1, 0},
    {1, 0, 0, 0, 1},
    {1, 0, 0, 0, 1},
    {1, 0, 0, 0, 1},
    {1, 0, 1, 0, 1},
    {1, 0, 0, 1, 1},
    {0, 1, 1, 1, 1}};
int t[7][5] = {
    {1, 1, 1, 1, 1},
    {0, 0, 1, 0, 0},
    {0, 0, 1, 0, 0},
    {0, 0, 1, 0, 0},
    {0, 0, 1, 0, 0},
    {0, 0, 1, 0, 0},
    {0, 0, 1, 0, 0}};
int u[7][5] = {
    {1, 0, 0, 0, 1},
    {1, 0, 0, 0, 1},
    {1, 0, 0, 0, 1},
    {1, 0, 0, 0, 1},
    {1, 0, 0, 0, 1},
    {1, 0, 0, 0, 1},
    {0, 1, 1, 1, 0}};
int v[7][5] = {
    {1, 0, 0, 0, 1},
    {1, 0, 0, 0, 1},
    {1, 0, 0, 0, 1},
    {1, 0, 0, 0, 1},
    {1, 0, 0, 0, 1},
    {0, 1, 0, 1, 0},
    {0, 0, 1, 0, 0}};
int w[7][5] = {
    {1, 0, 0, 0, 1},
    {1, 0, 0, 0, 1},
    {1, 0, 0, 0, 1},
    {1, 0, 0, 0, 1},
    {1, 0, 1, 0, 1},
    {1, 1, 0, 1, 1},
    {1, 0, 0, 0, 1}};
int x[7][5] = {
    {1, 0, 0, 0, 1},
    {1, 0, 0, 0, 1},
    {0, 1, 0, 1, 0},
    {0, 0, 1, 0, 0},
    {0, 1, 0, 1, 0},
    {1, 0, 0, 0, 1},
    {1, 0, 0, 0, 1}};
int y[7][5] = {
    {1, 0, 0, 0, 1},
    {1, 0, 0, 0, 1},
    {0, 1, 0, 1, 0},
    {0, 0, 1, 0, 0},
    {0, 0, 1, 0, 0},
    {0, 0, 1, 0, 0},
    {0, 0, 1, 0, 0}};
int z[7][5] = {
    {1, 1, 1, 1, 1},
    {0, 0, 0, 0, 1},
    {0, 0, 0, 1, 0},
    {0, 0, 1, 0, 0},
    {0, 1, 0, 0, 0},
    {1, 0, 0, 0, 0},
    {1, 1, 1, 1, 1}};
int question[7][5] = {
    {0, 1, 1, 1, 0},
    {1, 0, 0, 0, 1},
    {0, 0, 0, 0, 1},
    {0, 0, 0, 1, 0},
    {0, 0, 1, 0, 0},
    {0, 0, 0, 0, 0},
    {0, 0, 1, 0, 0}};
int empty[7][5] = {
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0}};

char packetBuffer[255];

int currentColumn = -1;
// unsigned long color = 0xFF44DD;
unsigned long color = 0xFFFFFF;

int getIndexForPosition(int x, int y)
{
  if (x < 0 || x > MATRIX_WIDTH - 1)
  {
    return -1;
  }
  if (y < 0 || y > MATRIX_HEIGHT - 1)
  {
    return -1;
  }
  boolean downToUp = x % 2 != 0;
  if (downToUp)
  {
    return x * MATRIX_HEIGHT + (MATRIX_HEIGHT - 1 - y);
  }
  else
  {
    return x * MATRIX_HEIGHT + y;
  }
}

void setCharacter(char character, int spacing)
{
  int maxX = 5;
  int maxY = 7;
  const int(*activeArray)[5] = nullptr;

  switch (character)
  {
  case '(':
    activeArray = openBracket;
    maxX = 2;
    break;
  case ')':
    activeArray = closedBracket;
    maxX = 2;
    break;
  case '=':
    activeArray = equal;
    maxX = 4;
    break;
  case ':':
    activeArray = colon;
    maxX = 2;
    break;
  case '.':
    activeArray = dot;
    maxX = 2;
    break;
  case '>':
    activeArray = greater;
    maxX = 4;
    break;
  case '<':
    activeArray = less;
    maxX = 4;
    break;
  case '+':
    activeArray = plus;
    break;
  case '-':
    activeArray = minus;
    break;
  case '0':
    activeArray = zero;
    break;
  case '1':
    activeArray = one;
    break;
  case '2':
    activeArray = two;
    break;
  case '3':
    activeArray = three;
    break;
  case '4':
    activeArray = four;
    break;
  case '5':
    activeArray = five;
    break;
  case '6':
    activeArray = six;
    break;
  case '7':
    activeArray = seven;
    break;
  case '8':
    activeArray = eight;
    break;
  case '9':
    activeArray = nine;
    break;
  case 'A':
  case 'a':
    activeArray = a;
    break;
  case 'B':
  case 'b':
    activeArray = b;
    break;
  case 'C':
  case 'c':
    activeArray = c;
    break;
  case 'D':
  case 'd':
    activeArray = d;
    break;
  case 'E':
  case 'e':
    activeArray = e;
    break;
  case 'F':
  case 'f':
    activeArray = f;
    break;
  case 'G':
  case 'g':
    activeArray = g;
    break;
  case 'L':
  case 'l':
    activeArray = l;
    maxX = 4;
    break;
  case 'H':
  case 'h':
    activeArray = h;
    break;
  case 'P':
  case 'p':
    activeArray = p;
    break;
  case 'Q':
  case 'q':
    activeArray = q_a;
    break;
  case 'I':
  case 'i':
    activeArray = i;
    maxX = 3;
    break;
  case 'J':
  case 'j':
    activeArray = j;
    break;
  case 'K':
  case 'k':
    activeArray = k;
    break;
  case 'M':
  case 'm':
    activeArray = m;
    break;
  case 'N':
  case 'n':
    activeArray = n;
    break;
  case 'O':
  case 'o':
    activeArray = o;
    break;
  case 'R':
  case 'r':
    activeArray = r;
    break;
  case 'S':
  case 's':
    activeArray = s;
    break;
  case 'T':
  case 't':
    activeArray = t;
    break;
  case 'U':
  case 'u':
    activeArray = u;
    break;
  case 'V':
  case 'v':
    activeArray = v;
    break;
  case 'W':
  case 'w':
    activeArray = w;
    break;
  case 'X':
  case 'x':
    activeArray = x;
    break;
  case 'Y':
  case 'y':
    activeArray = y;
    break;
  case 'Z':
  case 'z':
    activeArray = z;
    break;
  case '/':
    activeArray = slash;
    break;
  case '\\':
    activeArray = slash_reverse;
    break;
  case ' ':
  case '\n':
    activeArray = empty;
    break;
  case '?':
    activeArray = question;
    break;
  default:
    activeArray = question;
    break;
  }
  if (activeArray != nullptr)
  {
    currentColumn = currentColumn - maxX;
    for (int y = 0; y < maxY; y++)
    {
      for (int x = 0; x < maxX; x++)
      {
        if (activeArray[y][x] == 0)
        {
          continue;
        }
        int index = getIndexForPosition(x + currentColumn, y);
        if (index >= 0 && index < NUM_LEDS)
        { // Replace NUM_LEDS with the actual number of LEDs in your matrix
          strip.setPixelColor(index, color);
        }
      }
    }
    currentColumn -= spacing;
  }
}

void setMatrix(const char *displayString)
{
  strip.clear();
  if (displayString[0] == '\0')
  {
    displayString = ".:.:.:.:.:.:.";
  }
  Serial.print("Display: ");
  Serial.println(displayString);
  int strLength = strlen(displayString);
  currentColumn = MATRIX_WIDTH; // right align else 0
  int spacing = 1;
  /*for (int i = 0; i < displayString.length(); i++) {
    setCharacter(displayString.charAt(i), spacing);
    }*/
  for (int i = strLength - 1; i >= 0; i--)
  {
    setCharacter(displayString[i], spacing);
  }
  strip.show();
}

WiFiUDP Udp;

void setup()
{
  Serial.begin(115200);
  strip.begin();
  strip.setBrightness(255);
  strip.clear();
  strip.show();
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  int count = 1;
  while (WiFi.status() != WL_CONNECTED)
  {
    setMatrix(String(count).c_str());
    count++;
    Serial.print('.');
    delay(1000);
  }
  Serial.print("\nConnected! IP address: ");
  Serial.println(WiFi.localIP());
  String ip = WiFi.localIP().toString();
  setMatrix(ip.substring(ip.length() - 3).c_str());
  // Serial.println(ip.substring(ip.length() - 3).c_str());
  delay(2000);
  const char *motd = "<3";
  setMatrix(motd);
  Udp.begin(5000); // Local port to listen on
}

void loop()
{
  int packetSize = Udp.parsePacket();
  if (packetSize)
  {
    // Serial.printf("Received packet of size %d from %s:%d\n    (to %s:%d, free heap = %d B)\n", packetSize, Udp.remoteIP().toString().c_str(), Udp.remotePort(), Udp.destinationIP().toString().c_str(), Udp.localPort(), ESP.getFreeHeap());
    int n = Udp.read(packetBuffer, sizeof(packetBuffer) - 1);
    if (n < 1)
    {
      return;
    }
    packetBuffer[n] = '\0';
    // Serial.println("Contents:");
    // Serial.println(packetBuffer);
    if (strncmp(packetBuffer, "Light:", 6) == 0)
    {
      int brightness = atoi(packetBuffer + 6);
      if (brightness >= 0 && brightness <= 255)
      {
        strip.setBrightness(brightness);
      }
    }
    else if (strncmp(packetBuffer, "Color:", 6) == 0)
    {
      char *endPtr;
      color = strtoul(packetBuffer + 6, &endPtr, 16);
    }
    else
    {
      // check if starts with byte 1 20 82
      if (packetBuffer[0] == 1 && packetBuffer[1] == 20 && packetBuffer[2] == 82)
      {
        int startindex = -1;
        for (int i = strlen(packetBuffer) - 1; i >= 0; --i)
        {
          if (packetBuffer[i] == 2)
          {
            startindex = i + 1;
            break;
          }
        }
        // find first 20 after startIndex
        int lastindex = -1;
        for (int i = startindex; i < strlen(packetBuffer); ++i)
        {
          if (packetBuffer[i] == 0x20)
          {
            lastindex = i;
            break;
          }
        }
        char time[255];
        strncpy(time, packetBuffer + startindex, lastindex - startindex);
        time[lastindex - startindex] = '\0';

        int colons = 0;

        for (int i = 0; i < strlen(time); ++i)
        {
          if (time[i] == ':')
          {
            colons++;
          }
        }
        if (colons <= 2)
        {

          if (colons == 2)
          {
            int secondColonIndex = -1;
            for (int i = strlen(time) - 1; i >= 0; --i)
            {
              if (time[i] == ':')
              {
                secondColonIndex = i;
                break;
              }
            }
            char displayString[255];
            strncpy(displayString, time, secondColonIndex);
            displayString[secondColonIndex] = '\0';
            setMatrix(displayString);
          }
          else if (colons == 1)
          {
            int charTillColon = 0;
            for (int i = 0; i < strlen(time); ++i)
            {
              if (time[i] != ':')
              {
                charTillColon++;
              }
              else
              {
                break;
              }
            }
            if (charTillColon == 2)
            {
              char displayString[255];
              strncpy(displayString, time, charTillColon);
              displayString[charTillColon] = '\0';
              setMatrix(displayString);
            }
          }
          else
          {
            setMatrix(time);
          }
        }
      }
    }
  }
}