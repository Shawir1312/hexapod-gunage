void teganganBaterai() {
  for (int i = 0; i < 5; i++) {
    voltageReading += analogRead(bat2sSensPin);
    voltageReading1 += analogRead(bat1sSensPin);
    delay(1);
  }
  voltageReading = voltageReading / 5 * 0.0082;// * calibFacV;
  voltageReading1 = voltageReading1 / 5 * 0.004857;// * calibFacV;
  batVol = voltageReading;
  batVol1 = voltageReading1;
  //Serial.print("V ");
  //Serial.println(voltageReading, 2);
  //Serial.print("V1 ");
  //Serial.println(voltageReading1, 2);
  //batPct = mapFloat(batVol, 6.2, 8.4, 0, 100);
  //batPct = (153 * batVol - 540) / 10;
  batPct = (78.2 * batVol - 544) * 0.94;
  //Serial.print("pct ");
  //Serial.println(batPct, 1);

  if (batPct < 0) batPct = 0; if (batPct > 100) batPct = 100;
  if (voltageReading <= 7.2) batSt = 0;
  else if (voltageReading <= 7.5) batSt = 1;
  else batSt = 2;

  byte G = batPct;
}
