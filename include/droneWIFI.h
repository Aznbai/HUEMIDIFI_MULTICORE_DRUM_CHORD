void tryWIFI()
{
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
}
void setupWIFI()
{
    tryWIFI();
    while (WiFi.waitForConnectResult() != WL_CONNECTED)
    {
        drawWIFIFail();
        tryWIFI();
        delay(100);
    }
    drawWifi();
}