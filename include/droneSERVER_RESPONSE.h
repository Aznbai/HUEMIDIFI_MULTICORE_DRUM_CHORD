
String createStatePostResponseMsg()
{
    String message;
    message += '{';
    message += '"';
    message += "playOn";
    message += '"';
    message += ':';
    message += '"';
    message += String(playOn);
    message += '"';
    message += ',';
    message += '"';
    message += "bpm";
    message += '"';
    message += ':';
    message += '"';
    message += String(bpmCurr);
    message += '"';
    message += ',';
    message += '"';
    message += "drumCh";
    message += '"';
    message += ':';
    message += '"';
    message += String(drumCh);
    message += '"';
    message += ',';
    message += '"';
    message += "chordCh";
    message += '"';
    message += ':';
    message += '"';
    message += String(chordCh);
    message += '"';
    message += ',';
    message += '"';
    message += "chordGrid";
    message += '"';
    message += ':';
    message += '"';
    message += String(chordTickIndex);
    message += '"';
    message += ',';
    message += '"';
    message += "chordRoot";
    message += '"';
    message += ':';
    message += '"';
    message += String(chordRoot);
    message += '"';
    message += ',';
    message += '"';
    message += "chordStep0";
    message += '"';
    message += ':';
    message += '"';
    message += String(chordScaleStepIndex[0]);
    message += '"';
    message += ',';
    message += '"';
    message += "chordStep1";
    message += '"';
    message += ':';
    message += '"';
    message += String(chordScaleStepIndex[1]);
    message += '"';
    message += ',';
    message += '"';
    message += "chordStep2";
    message += '"';
    message += ':';
    message += '"';
    message += String(chordScaleStepIndex[2]);
    message += '"';
    message += ',';
    message += '"';
    message += "chordStep3";
    message += '"';
    message += ':';
    message += '"';
    message += String(chordScaleStepIndex[3]);
    message += '"';
    message += ',';
    message += '"';
    message += "chordStep4";
    message += '"';
    message += ':';
    message += '"';
    message += String(chordScaleStepIndex[4]);
    message += '"';
    message += ',';
    message += '"';
    message += "chordStep5";
    message += '"';
    message += ':';
    message += '"';
    message += String(chordScaleStepIndex[5]);
    message += '"';
    message += ',';
    message += '"';
    message += "chordStep6";
    message += '"';
    message += ':';
    message += '"';
    message += String(chordScaleStepIndex[6]);
    message += '"';
    message += ',';
    message += '"';
    message += "chordStep7";
    message += '"';
    message += ':';
    message += '"';
    message += String(chordScaleStepIndex[7]);
    message += '"';
    message += ',';
    message += '"';
    message += "chordStep8";
    message += '"';
    message += ':';
    message += '"';
    message += String(chordScaleStepIndex[8]);
    message += '"';
    message += ',';
    message += '"';
    message += "chordStep9";
    message += '"';
    message += ':';
    message += '"';
    message += String(chordScaleStepIndex[9]);
    message += '"';
    message += ',';
    message += '"';
    message += "chordStep10";
    message += '"';
    message += ':';
    message += '"';
    message += String(chordScaleStepIndex[10]);
    message += '"';
    message += ',';
    message += '"';
    message += "chordStep11";
    message += '"';
    message += ':';
    message += '"';
    message += String(chordScaleStepIndex[11]);
    message += '"';
    message += ',';
    message += '"';
    message += "chordStep12";
    message += '"';
    message += ':';
    message += '"';
    message += String(chordScaleStepIndex[12]);
    message += '"';
    message += ',';
    message += '"';
    message += "chordStep13";
    message += '"';
    message += ':';
    message += '"';
    message += String(chordScaleStepIndex[13]);
    message += '"';
    message += ',';
    message += '"';
    message += "chordStep14";
    message += '"';
    message += ':';
    message += '"';
    message += String(chordScaleStepIndex[14]);
    message += '"';
    message += ',';
    message += '"';
    message += "chordStep15";
    message += '"';
    message += ':';
    message += '"';
    message += String(chordScaleStepIndex[15]);
    message += '"';
    message += ',';
    message += '"';
    message += "chordStepNumber";
    message += '"';
    message += ':';
    message += '"';
    message += String(chordStepNumber);
    message += '"';
    message += ',';
    message += '"';
    message += "arpCh";
    message += '"';
    message += ':';
    message += '"';
    message += String(arpCh);
    message += '"';
    message += ',';
    message += '"';
    message += "drumMask0";
    message += '"';
    message += ':';
    message += '"';
    message += drumMask0;
    message += '"';
    message += ',';
    message += '"';
    message += "drumMask1";
    message += '"';
    message += ':';
    message += '"';
    message += drumMask1;
    message += '"';
    message += ',';
    message += '"';
    message += "drumMask2";
    message += '"';
    message += ':';
    message += '"';
    message += drumMask2;
    message += '"';
    message += ',';
    message += '"';
    message += "drumMask3";
    message += '"';
    message += ':';
    message += '"';
    message += drumMask3;
    message += '"';
    message += ',';
    message += '"';
    message += "drumMask4";
    message += '"';
    message += ':';
    message += '"';
    message += drumMask4;
    message += '"';
    message += ',';
    message += '"';
    message += "drumMask5";
    message += '"';
    message += ':';
    message += '"';
    message += drumMask5;
    message += '"';
    message += '}';
    return message;
}