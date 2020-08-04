#include <PMS.h>
#include <SoftwareSerial.h>

// http://www.taiwan921.lib.ntu.edu.tw/KKPT/KKE09.pdf

SoftwareSerial pmsSerial(2, 3);
PMS pms(pmsSerial);
PMS::DATA pmsData;


int pms_read_PM1()
{
  pms.read(pmsData);
  return pmsData.PM_AE_UG_1_0;
}

int pms_read_PM2()
{
  pms.read(pmsData);
  return pmsData.PM_AE_UG_2_5;
}

int pms_read_PM10()
{
  pms.read(pmsData);
  return pmsData.PM_AE_UG_10_0;
}

void setup()
{
  Serial.begin(9600);
  pmsSerial.begin(9600);
}

void loop()
{
  Serial.print("PM1.0:");
  Serial.println(pms_read_PM1());
  Serial.print("PM2.5:");
  Serial.println(pms_read_PM2());
  Serial.print("PM10:");
  Serial.println(pms_read_PM1());
  delay(1000);
}
