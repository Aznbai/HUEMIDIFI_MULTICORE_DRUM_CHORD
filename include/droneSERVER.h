AsyncWebServer server(80);
const char *PARAM_MESSAGE = "msg";
void notFound(AsyncWebServerRequest *request)
{
  request->send(404, "text/plain", "404");
}
void handlePostValChange(String paramKey, String paramVal)
{

  if (paramKey == "play")
    handleStartStop();
  if (paramKey == "bpm")
    bpmCurr = paramVal.toFloat();
  if (paramKey == "drumCh")
    drumCh = paramVal.toInt();
  if (paramKey == "chordCh")
    chordCh = paramVal.toInt();
  if (paramKey == "chordGrid")
    chordTickIndex = paramVal.toInt();
  if (paramKey == "chordStep0")
    chordScaleStepIndex[0] = paramVal.toInt();
  if (paramKey == "chordStep1")
    chordScaleStepIndex[1] = paramVal.toInt();
  if (paramKey == "chordStep2")
    chordScaleStepIndex[2] = paramVal.toInt();
  if (paramKey == "chordStep3")
    chordScaleStepIndex[3] = paramVal.toInt();

  if (paramKey == "chordStep4")
    chordScaleStepIndex[4] = paramVal.toInt();
  if (paramKey == "chordStep5")
    chordScaleStepIndex[5] = paramVal.toInt();
  if (paramKey == "chordStep6")
    chordScaleStepIndex[6] = paramVal.toInt();
  if (paramKey == "chordStep7")
    chordScaleStepIndex[7] = paramVal.toInt();
  if (paramKey == "chordStep8")
    chordScaleStepIndex[8] = paramVal.toInt();
  if (paramKey == "chordStep9")
    chordScaleStepIndex[9] = paramVal.toInt();
  if (paramKey == "chordStep10")
    chordScaleStepIndex[10] = paramVal.toInt();
  if (paramKey == "chordStep11")
    chordScaleStepIndex[11] = paramVal.toInt();
  if (paramKey == "chordStep12")
    chordScaleStepIndex[12] = paramVal.toInt();
  if (paramKey == "chordStep13")
    chordScaleStepIndex[13] = paramVal.toInt();
  if (paramKey == "chordStep14")
    chordScaleStepIndex[14] = paramVal.toInt();
  if (paramKey == "chordStep15")
    chordScaleStepIndex[15] = paramVal.toInt();
  if (paramKey == "chordStepNumber")
    chordStepNumber = paramVal.toInt();
  if (paramKey == "arpCh")
    arpCh = paramVal.toInt();
  if (paramKey == "chordRoot")
    chordRoot = paramVal.toInt();
  if (paramKey == "drumMask0")
    drumMask0 = paramVal;
  if (paramKey == "drumMask1")
    drumMask1 = paramVal;
  if (paramKey == "drumMask2")
    drumMask2 = paramVal;
  if (paramKey == "drumMask3")
    drumMask3 = paramVal;
  if (paramKey == "drumMask4")
    drumMask4 = paramVal;
  if (paramKey == "drumMask5")
    drumMask5 = paramVal;
  if (paramKey == "root")
    rootCurr = paramVal.toInt();
  if (paramKey == "velMin")
    velMin = paramVal.toInt();
  if (paramKey == "velMax")
    velMax = paramVal.toInt();
  if (paramKey == "I")
    scaleProbStep[0] = paramVal.toInt();
  if (paramKey == "II")
    scaleProbStep[1] = paramVal.toInt();
  if (paramKey == "III")
    scaleProbStep[2] = paramVal.toInt();
  if (paramKey == "IV")
    scaleProbStep[3] = paramVal.toInt();
  if (paramKey == "V")
    scaleProbStep[4] = paramVal.toInt();
  if (paramKey == "VI")
    scaleProbStep[5] = paramVal.toInt();
  if (paramKey == "VII")
    scaleProbStep[6] = paramVal.toInt();
  if (paramKey == "octShift")
    octShift = paramVal.toInt();
  if (paramKey == "fifthShift")
    fifthShift = paramVal.toInt();
}

void bindRoutes()
{
  server
      .serveStatic("/", SPIFFS, "/")
      // .setAuthentication("user", "pass");
      .setDefaultFile("index.html");
  server
      .on("/post", HTTP_POST, [](AsyncWebServerRequest *request) {
        AsyncWebParameter *p = request->getParam(0); // only first param is taken: UI sends only one parameter per request
        handlePostValChange(p->name(), p->value());
        request->send(200, "application/json", createStatePostResponseMsg());
      });
  server
      .on("/state", HTTP_POST, [](AsyncWebServerRequest *request) {
        request->send(200, "application/json", createStatePostResponseMsg());
      });

  server
      .onNotFound(notFound);
}
void setupServer()
{
  bindRoutes();
  if (!MDNS.begin("huemidifi"))
  {
    while (1)
    {
      delay(100);
    }
  }

  server.begin();
  // Start TCP (HTTP) server
  MDNS.addService("http", "tcp", 80);
}