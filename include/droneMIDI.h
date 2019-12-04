void noteOn(int ch, int pitch, int vel)
{
    ch += 143;
    Serial.write(ch);    // HEX 9N NOTEON = MIDI CH: 0-F & 8N NOTEOFF = MIDI CH: 0-F
    Serial.write(pitch); // MIDI NOTE NUMBER 00-7F
    Serial.write(vel);   // VELOCITY 00-7F
}
void noteOff(int ch, int pitch, int vel)
{
    ch += 127;
    Serial.write(ch);    // HEX 9N NOTEON = MIDI CH: 0-F & 8N NOTEOFF = MIDI CH: 0-F
    Serial.write(pitch); // MIDI NOTE NUMBER 00-7F
    Serial.write(vel);   // VELOCITY 00-7F
}
void allNotesOff()
{
    for (int i = 0; i <= 127; i++)
    {
        //noteOn(144, i, 0);
        noteOff(1, i, 0);
    }
    // noteOn(123, 0, 1);
    // Serial.write(MIDI_RESET_BYTE);
}
int recalcVelocity()
{
    return random(velMin, velMax);
}
void handleStartStop()
{
    playOn = !playOn;
    if (playOn)
    {
        if (newStart)
        {
            // prevPPQNMicros = 0.0;
            // prev16Micros = 0.0;
            // reset all starting positions
            for (int i = 0; i < 6; i++)
            {
                partPosition[i] = 0;
            }
            //dont push  play immedeatly, wait for next pulse by setting the flag
            newStart = false;
            newStartPrev = true;
        }
    }
    else
    {
        noteOff(1, notePrev, recalcVelocity()); //add random release velocity
        Serial.write(MIDI_STOP_BYTE);
        newStart = true;
    }
}
void stopPrevNotes()
{
    //noteOn(144, notePrev, 0);
    noteOff(drumCh, 60, recalcVelocity());
    noteOff(drumCh, 62, recalcVelocity());
    noteOff(drumCh, 64, recalcVelocity());
    noteOff(drumCh, 65, recalcVelocity());
    noteOff(drumCh, 66, recalcVelocity());
    noteOff(drumCh, 67, recalcVelocity());
    //noteOff(drumCh, notePrev, recalcVelocity()); // with rnd  release velocity
    //   noteOff(drumCh, 60, 120); //add random release velocity
}
void startCurrNotes()
{
    char s = drumMask0[partPosition[0]];
    int i = s - '0';
    if (1 == i)
        noteOn(drumCh, drumNotes[0], recalcVelocity());
    s = drumMask1[partPosition[1]];
    i = s - '0';
    if (1 == i)
        noteOn(drumCh, drumNotes[1], recalcVelocity());
    s = drumMask2[partPosition[2]];
    i = s - '0';
    if (1 == i)
        noteOn(drumCh, drumNotes[2], recalcVelocity());
    s = drumMask3[partPosition[3]];
    i = s - '0';
    if (1 == i)
        noteOn(drumCh, drumNotes[3], recalcVelocity());
    s = drumMask4[partPosition[4]];
    i = s - '0';
    if (1 == i)
        noteOn(drumCh, drumNotes[4], recalcVelocity());
    s = drumMask5[partPosition[5]];
    i = s - '0';
    if (1 == i)
        noteOn(drumCh, drumNotes[5], recalcVelocity());

    // notePrev = noteCurr;
}
void incrementPartPosition()
{
    if (partPosition[0] < drumMask0.length() - 1)
        partPosition[0]++;
    else
        partPosition[0] = 0;
    if (partPosition[1] < drumMask1.length() - 1)
        partPosition[1]++;
    else
        partPosition[1] = 0;
    if (partPosition[2] < drumMask2.length() - 1)
        partPosition[2]++;
    else
        partPosition[2] = 0;
    if (partPosition[3] < drumMask3.length() - 1)
        partPosition[3]++;
    else
        partPosition[3] = 0;
    if (partPosition[4] < drumMask4.length() - 1)
        partPosition[4]++;
    else
        partPosition[4] = 0;
    if (partPosition[5] < drumMask5.length() - 1)
        partPosition[5]++;
    else
        partPosition[5] = 0;
}
int getIndexOfMaxVal(int *array, int size)
{
    int maxIndex = 0;
    int max = array[maxIndex];
    for (int i = 1; i < size; i++)
    {
        if (max < array[i])
        {
            max = array[i];
            maxIndex = i;
        }
    }
    return maxIndex;
}
int getWeightedStepIndex()
{ // returns index of the next scale interval based on nonuniform (weighted) random sampling
    int currRndDraw[8];
    for (int i = 0; i < 8; i++)
    {
        currRndDraw[i] = random(0, scaleProbStep[i]);
    }
    return getIndexOfMaxVal(currRndDraw, 8);
}
void recalcNotes()
{
    int i = getWeightedStepIndex();
    noteCurr = rootCurr + scaleMajorStep[i];
}
void recalcOctShift()
{
    if (octShift > 0)
    {
        if (random(0, 2) > 0)
            noteCurr += 12;
    }
}
void recalcFifthShift()
{
    if (fifthShift > 0)
    {
        if (random(0, 2) > 0)
            noteCurr += 7;
    }
}
void handleDrumTiming()
{
    if (drumTickCurr == 0)
    {
        startCurrNotes();
                incrementPartPosition();

        // stopPrevNotes();
    }
    if (drumTickCurr !=0)
    {
        noteOff(drumCh, 60, recalcVelocity());
        noteOff(drumCh, 62, recalcVelocity());
        noteOff(drumCh, 64, recalcVelocity());
        noteOff(drumCh, 65, recalcVelocity());
        noteOff(drumCh, 66, recalcVelocity());
        noteOff(drumCh, 67, recalcVelocity());
        // startCurrNotes();//
    }
}
void handleChordTiming()
{
    if (chordTickCurr == 0)
    {
        noteOn(chordCh, chordRoot + chordScaleInterval[0][chordScaleStepIndex[chordScaleStepCurr]], recalcVelocity());
        noteOn(chordCh, chordRoot + chordScaleInterval[1][chordScaleStepIndex[chordScaleStepCurr]], recalcVelocity());
        noteOn(chordCh, chordRoot + chordScaleInterval[2][chordScaleStepIndex[chordScaleStepCurr]], recalcVelocity());
        // noteOn(chordCh, chordRoot+11, recalcVelocity());
    }
    if (chordTickCurr >= chordTick[chordTickIndex] - 1)
    {
        noteOff(chordCh, chordRoot + chordScaleInterval[0][chordScaleStepIndex[chordScaleStepCurr]], recalcVelocity());
        noteOff(chordCh, chordRoot + chordScaleInterval[1][chordScaleStepIndex[chordScaleStepCurr]], recalcVelocity());
        noteOff(chordCh, chordRoot + chordScaleInterval[2][chordScaleStepIndex[chordScaleStepCurr]], recalcVelocity());
        // noteOff(chordCh, chordRoot+11, recalcVelocity());
    }
}
void resetTicks()
{
    chordTickCurr = 0;
    drumTickCurr = 0;
    chordScaleStepCurr = 0;
}
void incrementTicks()
{
    if (chordTickCurr < chordTick[chordTickIndex]) //7 11 23
    {
        chordTickCurr++;
    }
    else
    {
        chordTickCurr = 0;
        // increment counter of current chord step
        if (chordScaleStepCurr < chordStepNumber - 1)
            chordScaleStepCurr++;
        else
            chordScaleStepCurr = 0;
    }
    if (drumTickCurr < drumTick[drumTickIndex]) //7 11 23
        drumTickCurr++;
    else
        drumTickCurr = 0;
}
void handlePPQNTiming()
{ // timing check: Pulses Per Quarter Note
    ppqnDurr = 60000000 / (bpmCurr * 24);
    currPPQNMicros = micros();
    if (currPPQNMicros - prevPPQNMicros >= ppqnDurr)
    {
        if (newStartPrev)
        {
            resetTicks();
            // first pass after start command. lets start in sync!
            newStartPrev = false;
            Serial.write(MIDI_START_BYTE);
        } // send a clock pulse
        Serial.write(MIDI_CLOCK_BYTE);
        if (playOn)
        {
            handleDrumTiming();
            handleChordTiming();
            incrementTicks();
        }
        prevPPQNMicros = currPPQNMicros;
        // prevPPQNMicros = prevPPQNMicros + ppqnDurr; // next durration step is ideal not current time!!!! =>>> prevMicros=currMicros;
        //     prev16Micros = curr16Micros;
        //     tick16 = true;
        //     // recalcNotes();
        //     // recalcOctShift();
        //     // recalcFifthShift();
        //     stopPrevNotes();
        //     startCurrNotes();
        //     incrementPartPosition();
    }
}
void setupMIDI()
{
    Serial.begin(31250); //  Set MIDI baud rate:
    delay(500);          //  Wait for serial to come up
    allNotesOff();
    Serial.write(MIDI_STOP_BYTE);
}