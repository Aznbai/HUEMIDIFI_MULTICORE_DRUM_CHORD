TFT_eSPI tft = TFT_eSPI(); // Invoke library, pins defined in User_Setup.h
void drawMidi()
{
    tft.fillRect(0, 0, 240, 240, TFT_BLACK);
    tft.setTextColor(TFT_YELLOW, TFT_BLACK);
    tft.drawCentreString("MIDI", 0, 0, 2);
    tft.setTextColor(TFT_GREEN, TFT_BLACK);

    tft.drawRightString("BPM: " + String(bpmCurr), 0, 30, 1);
    tft.drawRightString("PPQN MICROS: " + String(ppqnDurr), 0, 50, 1);
    tft.drawRightString("DRUM CH: " + String(drumCh), 0, 70, 1);
    tft.drawRightString("SYNTH CH: " + String(chordCh), 0, 90, 1);
    tft.drawRightString("PLAY: " + String(playOn), 0, 110, 1);
}
void drawPlay()
{
    tft.fillRect(0, 0, 240, 240, TFT_BLACK);
    tft.setTextColor(TFT_YELLOW, TFT_BLACK);
    tft.drawCentreString("PLAY", 0, 0, 2);
    tft.setTextColor(TFT_GREEN, TFT_BLACK);
}
void drawServer()
{
    tft.fillRect(0, 0, 240, 240, TFT_BLACK);
    tft.setTextColor(TFT_GREEN, TFT_BLACK);
    tft.drawCentreString("SERVER", 0, 0, 2);
}
void drawWifi()
{
    char buffer[50];
    String(WiFi.status()).toCharArray(buffer, 50);
    tft.fillRect(0, 0, 240, 240, TFT_BLACK);
    tft.setTextColor(TFT_YELLOW, TFT_BLACK);
    tft.drawCentreString("WIFI", 0, 0, 2);
    tft.setTextColor(TFT_GREEN, TFT_BLACK);
    tft.drawRightString("CONNECTION STATUS: " + String(WiFi.status()), 0, 30, 1);
    tft.drawRightString("IPv4: " + WiFi.localIP().toString(), 0, 50, 1);
    tft.drawRightString("SSID: " + String(ssid), 0, 70, 1);
    tft.setTextSize(1); //independent multiplicator for last argument of  tft.drawCentreString();
    tft.drawRightString("PASS: " + String(password), 0, 95, 1);
    tft.drawRightString("MAC: " + String(WiFi.macAddress()), 0, 115, 1);
    tft.setTextSize(2); //independent multiplicator for last argument of  tft.drawCentreString();
    tft.drawRightString("HTTP://", 0, 130, 1);
    tft.drawRightString("HUEMIDIFI.LOCAL", 0, 146, 1);
}
void drawWIFIFail()
{
    tft.fillRect(0, 0, 240, 240, TFT_BLACK);
    tft.setTextColor(TFT_YELLOW, TFT_BLACK);
    tft.drawCentreString("WIFI ERROR:", 120, 20, 1);
    tft.drawCentreString("REATTEMPTING CONNECTION:", 120, 40, 1);
    tft.drawRightString("SSID: " + String(ssid), 120, 70, 1);
    tft.setTextSize(1); //independent multiplicator for last argument of  tft.drawCentreString();
    tft.drawRightString("PASS: " + String(password), 120, 95, 1);
    tft.setTextSize(2); //independent multiplicator for last argument of  tft.drawCentreString();
}
void drawHello()
{
    tft.fillRect(0, 0, 240, 240, TFT_BLACK);
    tft.setTextColor(TFT_YELLOW, TFT_BLACK);
    colour = random(0xFFFF);
    tft.setTextColor(colour);
    tft.drawCentreString("MEMENTO MORI", 0, 0, 2); // Next size up font 2
}
void handleTFTPageChange(int page)
{
    switch (page)
    {
    case 1:
        drawWifi();
        break;
    case 2:
        drawMidi();
        break;
    case 3:
        drawPlay();
        break;
    case 4:
        drawServer();
        break;
    default:
        drawWifi();
        break;
    }
}
void setupTFT()
{
    tft.init();
    tft.setTextSize(2); //independent multiplicator for last argument of  tft.drawCentreString();
    tft.setRotation(1);
    tft.fillScreen(TFT_BLACK);
    drawHello();
    delay(500);
}
