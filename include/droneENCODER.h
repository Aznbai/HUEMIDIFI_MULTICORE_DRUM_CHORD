AiEsp32RotaryEncoder rotaryEncoder = AiEsp32RotaryEncoder(ROTARY_ENCODER_A_PIN, ROTARY_ENCODER_B_PIN, ROTARY_ENCODER_BUTTON_PIN, ROTARY_ENCODER_VCC_PIN);
int test_limits = 2;
void handleEncoder()
{
  if (rotaryEncoder.currentButtonState() == BUT_RELEASED)
  {
    // rotary_onButtonClick();
  }
  encoderDelta = rotaryEncoder.encoderChanged();
  if (encoderDelta == 0)
  {
    return;
  }
  else
  {
    //   if (encoderDelta > 0) //determines direction
    //   if (encoderDelta < 0) //determines direction
    pageNumber = rotaryEncoder.readEncoder() / 2;
    handleTFTPageChange(pageNumber);
  }
}
/* 
void rotary_onButtonClick()
{
  //rotaryEncoder.reset();
  //rotaryEncoder.disable();
  // rotaryEncoder.setBoundaries(-test_limits, test_limits, false);
  // test_limits *= 2;
}
 */
void setupEncoder()
{
  rotaryEncoder.begin();
  rotaryEncoder.setup([] { rotaryEncoder.readEncoder_ISR(); });
  rotaryEncoder.setBoundaries(0, 7, true); //minValue, maxValue, cycle values (when max go to min and vice versa)
  delay(1000);
  rotaryEncoder.enable();
}
