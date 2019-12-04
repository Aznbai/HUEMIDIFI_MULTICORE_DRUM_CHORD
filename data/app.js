var stateUI = {
    play: false,
    drumCh: 1,
    chordCh: 2,
    arpCh: 3,
    drumPartsCount: 6,
    partBitMask: ["16", "16", "16", "16", "16", "16"],
    partCh: [16, 16, 16, 16, 16, 16],
    // partLength: [16, 16, 16, 16, 16, 16, 16, 16, 16, 16],
    partLength: [16, 16, 16, 16, 16, 16],
    chordRoot: 64,
    chordGrid: 1,
    chordStep: [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1],
    chordStep0: 0,
    chordStep1: 1,
    chordStep2: 3,
    chordStep3: 4,
    chordStepNumber: 4

};
var sending = false;
var remoteState;
var chordOctCurr = 6;
var chordRootNoteOct = 4;
var chordRootNoteSymbol = "C";
var chordRootNoteTmp = "3"
var chordRootNoteSymbolMapping = ["C", "G", "D", "A", "E", "B", "F#", "D&#9837;", "A&#9837;", "E&#9837;", "B&#9837;", "F"];
var chordRootNoteSymbolNormal = ["C", "D&#9837;", "D", "E&#9837;", "E", "F", "F#", "G", "A&#9837;", "A", "B&#9837;", "B"];
var chordRootNoteOrder = ["3", "10", "5", "0", "7", "2", "9", "4", "11", "6", "1", "8"];
var chordGridSymbol = ["1/32", "1/16", "1/8", "1/4", "1/2", "1/1", "2/1", "4/1", "8/1"];
var chordStepSymbol = ["I", "ii", "iii", "IV", "V", "vi", "vii°"];

var partDiv,
    chSettingsDiv,
    numberInputWrap,
    chInput,
    chInputLabel,
    drumPartChInput,
    drumPartChWrapDiv,
    drumPartLengthWrapDiv,
    drumPartLengthLabel,
    clearPartWrapDiv,
    clearPartDiv,
    randomizePartWrapDiv,
    randomizePartDiv,
    drumPartControlWrapDiv,
    drumPartSequenceWrapDiv,
    lengthMinus,
    drumPartLengthInput,
    lengthPlus,
    stepWrapDiv,
    stepCheckbox,
    chMinus,
    chPlus,
    chordStepWrapDiv,
    chordStepDiv,
    chordStepInput;

var $id = function (id) {
    return document.getElementById(id); //define id selector shorthand
};

function docReady(fn) {
    if (document.readyState === "complete" || document.readyState === "interactive") {
        setTimeout(fn, 1);
    } else {
        document.addEventListener("DOMContentLoaded", fn);
    }
}
docReady(function () {
    // window.setTimeout($id("preload-screen").setAttribute("class", "loaded"), 15000);
    $id("trigger-chord").click();
    // DOM is loaded and ready for manipulation
    for (let k = 0; k < stateUI.drumPartsCount; k++) { // for every part
        createPartDiv(k);
        createDrumPartControlWrapDiv(k);
        createDrumPartSequenceWrapDiv(k);
        for (let i = 0; i < stateUI.partLength[k]; i++) {
            // create step checkboxes
            createDrumSequenceStep(k, i);
        }
        $id("clrPart-" + k).addEventListener("click", function () {
            for (i = 0; i < 16; i++) { // for all 
                $id("drumPart-" + k + "-step-" + i).checked = false;
            }
            updateBitMask(k); // clrPart(k);
            // updateStepBitmask(1);
        });
        $id("lengthInputPlus-" + k).addEventListener("click", function () {
            if ($id("lengthInput-" + k).value < 16) {
                $id("lengthInput-" + k).value++;
            }
            stateUI.partLength[k] = $id("lengthInput-" + k).value;
            setDrumPartLength(k, updateBitMask(k));

        });
        $id("lengthInputMinus-" + k).addEventListener("click", function () {
            if ($id("lengthInput-" + k).value > 1) {
                $id("lengthInput-" + k).value--;
            }
            stateUI.partLength[k] = $id("lengthInput-" + k).value;
            setDrumPartLength(k, updateBitMask(k));
        });

        $id("rndPart-" + k).addEventListener("click", function () {
            randomizePart(k);
            // updateStepBitmask(1);
        });
        $id("lengthInput-" + k).addEventListener("change", function () {
            // alert();
            stateUI.partLength[k] = $id("lengthInput-" + k).value;
            setDrumPartLength(k, updateBitMask(k));
            // updateStepBitmask(1);
        });
    }
    // CREATE CHORD STEPS
    for (let i = 0; i < 16; i++) {
        createChordSteps(i);
    }
    // PLAY EVENT LISTENER
    $id("play").addEventListener("change", function () {
        togglePlay(sendUi("play", stateUI.play));
        // updateStepBitmask(1);
    });

    // BPM EVENT LISTENERS
    $id("bpm").addEventListener("change", function () {
        setBPM();
        // updateStepBitmask(1);
    });
    $id("bpmPlus").addEventListener("click", function () {
        if ($id("bpm").value < 260) {
            $id("bpm").value++;
            setBPM();
        }
        // updateStepBitmask(1);
    });
    $id("bpmMinus").addEventListener("click", function () {
        if ($id("bpm").value > 20) {
            $id("bpm").value--;
            setBPM();
        }
        // updateStepBitmask(1);
    });
    // DRUM CHANEL EVENT LISTENERS
    $id("drumCh").addEventListener("change", function () {
        setDrumCh();
        // updateStepBitmask(1);
    });
    $id("drumChPlus").addEventListener("click", function () {
        if ($id("drumCh").value < 16) {
            $id("drumCh").value++;
            setDrumCh();
        }
        // updateStepBitmask(1);
    });
    $id("drumChMinus").addEventListener("click", function () {
        if ($id("drumCh").value > 1) {
            $id("drumCh").value--;
            setDrumCh();
        }
        // updateStepBitmask(1);
    });
    // CHORD CHANEL EVENT LISTENERS
    $id("chordCh").addEventListener("change", function () {
        setChordCh();
        // updateStepBitmask(1);
    });
    $id("chordChPlus").addEventListener("click", function () {
        if ($id("chordCh").value < 16) {
            $id("chordCh").value++;
            setChordCh();
        }
        // updateStepBitmask(1);
    });
    $id("chordChMinus").addEventListener("click", function () {
        if ($id("chordCh").value > 1) {
            $id("chordCh").value--;
            setChordCh();
        }
        // updateStepBitmask(1);
    });
    // ARP CHANEL EVENT LISTENERS
    // $id("arpCh").addEventListener("change", function () {
    //     setArpCh();
    //     // updateStepBitmask(1);
    // });
    // $id("arpChPlus").addEventListener("click", function () {
    //     if ($id("arpCh").value < 16) {
    //         $id("arpCh").value++;
    //         setArpCh();
    //     }
    //     // updateStepBitmask(1);
    // });
    // $id("arpChMinus").addEventListener("click", function () {
    //     if ($id("arpCh").value > 1) {
    //         $id("arpCh").value--;
    //         setArpCh();
    //     }
    //     // updateStepBitmask(1);
    // });
    // OCTAVE NUMBER CONTROLS EVENT LISTENER
    $id("root-oct-plus").addEventListener("click", function () {
        if (chordOctCurr < 7) {
            chordOctCurr++;
            setChordRoot();
        }
    });
    $id("root-oct-minus").addEventListener("click", function () {
        if (chordOctCurr > 1) {
            chordOctCurr--;
            setChordRoot();
        }
    });
    // CIRCULAR ROOT EVENT LISTENERS
    for (let x = 0; x < 12; x++) {
        $id("pos" + x).addEventListener("click", function () {
            chordRootNoteSymbol = chordRootNoteSymbolMapping[x];
            chordRootNoteTmp = chordRootNoteOrder[x];
            setChordRoot();
        });
    }
    // CHORD GRID EVENT LISTENERS

    $id("chordGrid").addEventListener("change", function () {
        setChordGrid();
    });
    //  CHORD SCALE STEPS EVENT LISTENERS
    for (let x = 0; x < 16; x++) {
        $id("chordStep" + x).addEventListener("change", function () {
            stateUI.chordStep[x] = $id("chordStep" + x).value;
            sendUi("chordStep" + x, stateUI.chordStep[x]);
        });
    }
    // CHORD STEP NUMBER CONTROL EVENT LISTENER
    $id("chordStepNumber").addEventListener("change", function () {
        stateUI.chordStepNumber = $id("chordStepNumber").value;
        $id("chordStepNumberLabel").innerHTML = stateUI.chordStepNumber;
        setChordPartLength();
        sendUi("chordStepNumber", stateUI.chordStepNumber);
    });
    // $id("getState").addEventListener("click", function () {
    //     getRemoteState();
    // });
    getRemoteState();
    updateBitMasks();
    setInterval(getRemoteState, 6000);
    $id("preload-screen").setAttribute = ("class", "loaded")

    window.setTimeout(loadAnimation, 500);

});

function loadAnimation() {
    $id("preload-screen").style.visibility = "hidden";
}

function createPartDiv(partID) {
    //CREATE PART DIVS
    partDiv = document.createElement("div");
    chSettingsDiv = $id("chSettings");
    partDiv.setAttribute("class", "drum-part");
    partDiv.id = "part-" + partID;
    $id("page-drum").appendChild(partDiv);
}

function createDrumPartControlWrapDiv(partID) {
    //  CREATE PART CONTROL WRAP
    drumPartControlWrapDiv = document.createElement("div");
    drumPartControlWrapDiv.setAttribute("class", "drumPartControlWrap");
    partDiv.appendChild(drumPartControlWrapDiv);
    //  CREATE RANDOMIZE PART BUTTON WRAP
    rndPartWrapDiv = document.createElement("div");
    rndPartWrapDiv.setAttribute("class", "buttonWrap");
    drumPartControlWrapDiv.appendChild(rndPartWrapDiv); //  create randomize part button wrap
    //  CREATE RANDOMIZE PART BUTTON 
    rndPartDiv = document.createElement("div");
    rndPartDiv.setAttribute("class", "button");
    rndPartDiv.id = "rndPart-" + partID;
    rndPartDiv.innerHTML = "R"
    rndPartWrapDiv.appendChild(rndPartDiv);
    //  CREATE CLEAR PART BUTTON WRAP
    clrPartWrapDiv = document.createElement("div");
    clrPartWrapDiv.setAttribute("class", "buttonWrap");
    drumPartControlWrapDiv.appendChild(clrPartWrapDiv); //  create randomize part button wrap
    //  CREATE CLEAR PART BUTTON 
    clrPartDiv = document.createElement("div");
    clrPartDiv.setAttribute("class", "button");
    clrPartDiv.id = "clrPart-" + partID;
    clrPartDiv.innerHTML = "C"
    clrPartWrapDiv.appendChild(clrPartDiv);
    // CREATE LENGTH CONTROLS
    lengthInputWrap = document.createElement("div");
    lengthInputWrap.setAttribute("class", "numberInputWrap");
    lengthInputWrap.id = "lengthInputWrap-" + partID;
    drumPartControlWrapDiv.appendChild(lengthInputWrap);
    //  CREATE DRUM PART length INPUT LABELS
    lengthInputLabel = document.createElement("div");
    lengthInputLabel.setAttribute("class", "numberInputLabel");
    lengthInputLabel.setAttribute("for", "lengthInput-" + partID);
    lengthInputLabel.innerHTML = "MIDI length ";
    // CREATE MINUS BUTTON
    lengthMinus = document.createElement("button");
    lengthMinus.innerHTML = "&#8722;";
    lengthMinus.setAttribute("class", "numberInputMinus");
    lengthMinus.id = "lengthInputMinus-" + partID;
    lengthInputWrap.appendChild(lengthMinus);
    //CREATE PART length INPUTS       
    lengthInput = document.createElement("input");
    lengthInput.setAttribute("class", "numberInput");
    lengthInput.setAttribute("type", "number");
    lengthInput.setAttribute("min", "1");
    lengthInput.setAttribute("max", "16");
    lengthInput.setAttribute("value", "16");
    lengthInput.id = "lengthInput-" + partID;
    lengthInputWrap.appendChild(lengthInput);
    // CREATE PLUS BUTTON
    lengthPlus = document.createElement("button");
    lengthPlus.innerHTML = "+";
    lengthPlus.setAttribute("class", "numberInputPlus");
    lengthPlus.id = "lengthInputPlus-" + partID;
    lengthInputWrap.appendChild(lengthPlus);
}

function createDrumPartSequenceWrapDiv(partID) {
    //  CREATE DRUM PART LENGTH CONTROL GROUP 
    drumPartSequenceWrapDiv = document.createElement("div");
    drumPartSequenceWrapDiv.setAttribute("class", "drumPartSequenceWrap");
    partDiv.appendChild(drumPartSequenceWrapDiv);
}

function createDrumSequenceStep(partID, stepID) {
    //  CREATE DRUM PART STEP WRAP
    stepWrapDiv = document.createElement("div");
    stepWrapDiv.setAttribute("class", "binarySwitchWrap");
    stepWrapDiv.id = "stepWrapPart-" + partID + "-step-" + stepID;
    drumPartSequenceWrapDiv.appendChild(stepWrapDiv);
    //  CREATE STEP CHECKBOXES
    stepCheckbox = document.createElement("input");
    stepCheckbox.setAttribute("type", "checkbox");
    stepCheckbox.setAttribute("class", "binarySwitch");
    stepCheckbox.id = "drumPart-" + partID + "-step-" + stepID;
    stepWrapDiv.appendChild(stepCheckbox);
    stepCheckbox.addEventListener("change", function () {
        // propagateSliderToCheckbox(1, partLength);
        updateBitMask(partID);
    });
    stepCheckboxLabel = document.createElement("label");
    stepCheckboxLabel.setAttribute("for", "drumPart-" + partID + "-step-" + stepID);
    stepCheckboxLabel.setAttribute("class", "binarySwitchLabel");
    stepCheckboxLabel.id = "drumPart-" + partID + "-stepLabel-" + stepID;
    stepWrapDiv.appendChild(stepCheckboxLabel);
}

function createChordSteps(chordStepID) {
    chordStepWrapDiv = document.createElement("div");
    chordStepWrapDiv.setAttribute("class", "wrap");
    chordStepWrapDiv.id = "chord-step-wrap-" + chordStepID;
    $id("chordStepWrap").appendChild(chordStepWrapDiv);
    chordStepDiv = document.createElement("div");
    chordStepDiv.setAttribute("class", "vertical-range-wrap");
    chordStepWrapDiv.appendChild(chordStepDiv);
    chordStepInput = document.createElement("input");
    chordStepInput.setAttribute("class", "vertical");
    chordStepInput.setAttribute("type", "range");
    chordStepInput.setAttribute("min", "0");
    chordStepInput.setAttribute("max", "6");
    chordStepInput.setAttribute("value", "0");
    chordStepInput.id = "chordStep" + chordStepID;
    chordStepDiv.appendChild(chordStepInput);
}


function setBPM() {
    stateUI.bpm = $id("bpm").value;
    sendUi("bpm", stateUI.bpm);
}

function setDrumCh() {
    stateUI.drumCh = $id("drumCh").value;
    sendUi("drumCh", stateUI.drumCh);
}

function setChordCh() {
    stateUI.chordCh = $id("chordCh").value;
    sendUi("chordCh", stateUI.chordCh);
}

function setArpCh() {
    stateUI.arpCh = $id("arpCh").value;
    sendUi("arpCh", stateUI.arpCh);
}

function togglePlay() {
    stateUI.play = !stateUI.play;
}

function setChordRoot() {
    $id("root-note-display").innerHTML = chordRootNoteSymbol;
    $id("root-oct-display").innerHTML = chordOctCurr;
    stateUI.chordRoot = parseInt(chordRootNoteTmp) + 21 + (12 * chordOctCurr);
    // console.log(stateUI.chordRoot);
    sendUi("chordRoot", stateUI.chordRoot);
}

function setChordGrid() {
    stateUI.chordGrid = $id("chordGrid").value;
    $id("chordGridLabel").innerHTML = chordGridSymbol[$id("chordGrid").value];
    sendUi("chordGrid", stateUI.chordGrid);
}

function updateBitMask(k) {
    stateUI.partBitMask[k] = "";
    for (let i = 0; i < stateUI.partLength[k]; i++) { // write checkbox state
        var checkbox = $id("drumPart-" + k + "-step-" + i);
        checkbox.checked ?
            stateUI.partBitMask[k] += "1" :
            stateUI.partBitMask[k] += "0";
    }
    sendUi("drumMask" + k, stateUI.partBitMask[k]);
}

function updateBitMasks() {
    for (let k = 0; k < stateUI.drumPartsCount; k++) { // for every part
        stateUI.partBitMask[k] = "";
        for (let i = 0; i < stateUI.partLength[k]; i++) { // write checkbox state
            var checkbox = $id("drumPart-" + k + "-step-" + i);
            checkbox.checked ?
                stateUI.partBitMask[k] += "1" :
                stateUI.partBitMask[k] += "0";
        }
        // console.log(stateUI);
    }
}

function clrPart(partID, stepID) {
    for (var i = 0; i < 16; i++) { // for all 
        $id("drumPart-" + partID + "-step-" + i).checked = false;
    }
    updateBitMask(partID);

}

function randomizePart(partID) {
    for (let i = 0; i < stateUI.partLength[partID]; i++) { // for all checkboxes of a particular part
        var k = Math.floor(Math.random() * 3);
        k > 1 ?
            $id("drumPart-" + partID + "-step-" + i).checked = true :
            $id("drumPart-" + partID + "-step-" + i).checked = false;
    }
    updateBitMask(partID);
}

function setDrumPartLength(part) {

    for (i = stateUI.partLength[part] - 1; i < 16; i++) {
        $id("drumPart-" + part + "-step-" + i).disabled = true;
    }
    for (i = 0; i < stateUI.partLength[part]; i++) {
        $id("drumPart-" + part + "-step-" + i).disabled = false;
    }

}

function setChordPartLength(lastPart) {
    for (i = stateUI.chordStepNumber - 1; i < 16; i++) {
        $id("chord-step-wrap-" + i).classList.add("hide");
    }
    for (i = 0; i < stateUI.chordStepNumber; i++) {
        $id("chord-step-wrap-" + i).classList.remove("hide");
    }

}

function sendPartBitMask(part) {
    sendUi("drumMask" + part, stateUI.partBitMask[part]);
}

function sendUi(item, value) {
    var postString;
    postString = item + "=" + value;
    // postString+="partCh="+stateUI.par
    const xhr = new XMLHttpRequest();
    xhr.open("POST", "/post", true);
    xhr.setRequestHeader("Content-Type", "application/x-www-form-urlencoded");
    // xhr.onreadystatechange = function () {
    //     if (xhr.readyState == 4 && xhr.status == 200) {
    //         var json = JSON.parse(xhr.responseText);
    //         console.log(json.email + ", " + json.name)
    //     }
    // }
    // xhr.send(JSON.stringify(stateUI));
    xhr.send(postString);
}

function getRemoteState() {
    sending = true;
    const xhr = new XMLHttpRequest();
    xhr.open("POST", "/state", true);
    xhr.setRequestHeader("Content-Type", "application/x-www-form-urlencoded");
    xhr.onreadystatechange = function () {
        if (xhr.readyState == 4 && xhr.status == 200) {
            if (!sending) {
                setLocalState(xhr.responseText);
            }
        }
    }
    xhr.send("");
    sending = false;
}

function setLocalState(response) {
    remoteState = JSON.parse(response);
    console.log(remoteState);
    // SET PLAY
    if (remoteState.playOn == 0) {
        stateUI.play = false;
        $id("play").checked = false;

    } else {
        stateUI.play = true;
        $id("play").checked = true;
    }
    // SET BPM
    stateUI.bpm = remoteState.bpm;
    $id("bpm").value = stateUI.bpm;
    // SET DRUM CH
    stateUI.drumCh = remoteState.drumCh;
    $id("drumCh").value = stateUI.drumCh;
    // SET CHORD CH
    stateUI.chordCh = remoteState.chordCh;
    $id("chordCh").value = stateUI.chordCh;
    // SET ARPCH
    // stateUI.arpCh = remoteState.arpCh;
    // $id("arpCh").value = stateUI.arpCh;
    // SET PART LENGTH
    stateUI.partLength[0] = remoteState.drumMask0.length;
    stateUI.partLength[1] = remoteState.drumMask1.length;
    stateUI.partLength[2] = remoteState.drumMask2.length;
    stateUI.partLength[3] = remoteState.drumMask3.length;
    stateUI.partLength[4] = remoteState.drumMask4.length;
    stateUI.partLength[5] = remoteState.drumMask5.length;
    for (let i = 0; i < stateUI.drumPartsCount; i++) {
        setDrumPartLength(i);
        $id("lengthInput-" + i).value = stateUI.partLength[i];
    }
    // SET PART BITMASK
    stateUI.partBitMask[0] = remoteState.drumMask0;
    stateUI.partBitMask[1] = remoteState.drumMask1;
    stateUI.partBitMask[2] = remoteState.drumMask2;
    stateUI.partBitMask[3] = remoteState.drumMask3;
    stateUI.partBitMask[4] = remoteState.drumMask4;
    stateUI.partBitMask[5] = remoteState.drumMask5;
    for (let i = 0; i < stateUI.drumPartsCount; i++) {
        setDrumPartBitmask(i);
    }
    //  SET CHORD ROOT
    stateUI.chordRoot = remoteState.chordRoot;
    chordRootNoteSymbol = chordRootNoteSymbolNormal[stateUI.chordRoot % 12];
    chordOctCurr = Math.floor((stateUI.chordRoot - 21) / 12);
    $id("root-note-display").innerHTML = chordRootNoteSymbol;
    $id("root-oct-display").innerHTML = chordOctCurr;
    // stateUI.chordRoot = parseInt(chordRootNoteTmp) + 21 + (12 * chordOctCurr);

    //  SET CHORD GRID
    stateUI.chordGrid = remoteState.chordGrid;
    $id("chordGrid").value = stateUI.chordGrid;
    $id("chordGridLabel").innerHTML = chordGridSymbol[$id("chordGrid").value]; // SET CHORD STEPS NUMBER
    stateUI.chordStepNumber = remoteState.chordStepNumber;
    // SET CHORD STEP COUNT
    stateUI.chordStepNumber = parseInt(remoteState.chordStepNumber);
    $id("chordStepNumberLabel").innerHTML = stateUI.chordStepNumber;
    $id("chordStepNumber").value = stateUI.chordStepNumber;
    setChordPartLength(stateUI.chordStepNumber);

    // SET CHORD STEPS
    stateUI.chordStep[0] = remoteState.chordStep0;
    stateUI.chordStep[1] = remoteState.chordStep1;
    stateUI.chordStep[2] = remoteState.chordStep2;
    stateUI.chordStep[3] = remoteState.chordStep3;
    stateUI.chordStep[4] = remoteState.chordStep4;
    stateUI.chordStep[5] = remoteState.chordStep5;
    stateUI.chordStep[6] = remoteState.chordStep6;
    stateUI.chordStep[7] = remoteState.chordStep7;
    stateUI.chordStep[8] = remoteState.chordStep8;
    stateUI.chordStep[9] = remoteState.chordStep9;
    stateUI.chordStep[10] = remoteState.chordStep10;
    stateUI.chordStep[11] = remoteState.chordStep11;
    stateUI.chordStep[12] = remoteState.chordStep12;
    stateUI.chordStep[13] = remoteState.chordStep13;
    stateUI.chordStep[14] = remoteState.chordStep14;
    stateUI.chordStep[15] = remoteState.chordStep15;
    setChordSteps();
}

function setChordSteps() {
    for (let d = 0; d < 16; d++) {
        $id("chordStep" + d).value = stateUI.chordStep[d];
    }
}

function setDrumPartBitmask(part) {
    for (let i = 0; i < 16; i++) {
        if (stateUI.partBitMask[part].charAt(i) == 0) {
            $id("drumPart-" + part + "-step-" + i).checked = false;
        } else {

            $id("drumPart-" + part + "-step-" + i).checked = true;
        }
    }
}
/*  */
/*  */
/*  */

function openTab(evt, tabName) {
    var i, tabcontent, tablinks;
    tabcontent = document.getElementsByClassName("page");
    for (i = 0; i < tabcontent.length; i++) {
        tabcontent[i].style.display = "none";
    }
    tablinks = document.getElementsByTagName("button");
    for (i = 0; i < tablinks.length; i++) {
        tablinks[i].className = tablinks[i].className.replace("active", "");
    }
    document.getElementById(tabName).style.display = "block";
    evt.currentTarget.className += "active";
}