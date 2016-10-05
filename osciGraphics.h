char lineCount = 16;
char currentLine = 0;
char lines[16][4];

void setAdsrLines()
{  
  lines[2][0] = 0;
  lines[2][1] = adsr[0][2];
  lines[2][2] = lines[2][0] + 64;
  lines[2][3] = lines[2][1];

  lines[1][0] = lines[2][0];
  lines[1][1] = lines[2][1];
  lines[1][2] = lines[1][0] - (adsr[0][1] >> 1);
  lines[1][3] = 127;

  lines[0][0] = lines[1][2];
  lines[0][1] = 127;
  lines[0][2] = lines[0][0] - (adsr[0][0] >> 1);
  lines[0][3] = 0;

  lines[3][0] = lines[2][2];
  lines[3][1] = lines[2][3];
  lines[3][2] = lines[3][0] + (adsr[0][3] >> 1);
  lines[3][3] = 0;

  lines[4][0] = lines[2][2];
  lines[4][1] = lines[2][3];
  lines[4][2] = lines[4][0];
  lines[4][3] = 0;

  lines[5][0] = lines[1][0];
  lines[5][1] = lines[1][1];
  lines[5][2] = lines[5][0];
  lines[5][3] = 0;

  lines[6][0] = lines[0][0];
  lines[6][1] = lines[0][1];
  lines[6][2] = lines[6][0];
  lines[6][3] = 0;
}

void setWaveLines()
{
  lines[7][0] = 127;
  lines[7][1] = -64;
  lines[7][2] = -128;
  lines[7][3] = -64;
  for(char i = 0; i < 8; i++)
  {  
    lines[8 + i][0] = i * 32 - 128;
    lines[8 + i][1] = (wavePar[i] >> 1) - 96;
    lines[8 + i][2] = i * 32 - 128 + 31;
    lines[8 + i][3] = (wavePar[(i + 1) & 7] >> 1) - 96;
  }
}

void setupGraphics()
{
  DDRK = 255;
  DDRA = 255;
}

short lineDx;
short lineDy;
short lineSx;
short lineSy;
short lineX0;
short lineY0;
short lineX1;
short lineY1;
short lineErr;

void calcLine(char x0, char y0, char x1, char y1)
{
  lineDx = abs((short)x1 - x0);
  lineDy = abs((short)y1 - y0);
  lineSx = x0 < x1 ? 1 : -1;
  lineSy = y0 < y1 ? 1 : -1;
  lineErr = lineDx - lineDy;
  
  lineX0 = x0;
  lineY0 = y0;
  lineX1 = x1;
  lineY1 = y1;
}

boolean lineStep()
{
  if(lineX0 == lineX1 && lineY0 == lineY1)
    return false;
    if(lineX0 >= -128 && lineX0 <= 127 && lineY0 >= -128 && lineY0 <= 127)
    {
  PORTK = lineX0 - 128;
  PORTA = lineY0 - 128;  
    }
  short e2 = lineErr << 1;
  if(e2 > -lineDy)
  {
    lineErr -= lineDy;
    lineX0 += lineSx;
  }
  if(e2 < lineDx)
  {
    lineErr += lineDx;
    lineY0 += lineSy;
  }
  return true;
}

