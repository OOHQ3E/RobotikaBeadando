var gateway = `ws://${window.location.hostname}/ws`;
var websocket;
window.addEventListener('load', onload);

function onload(event) {
    initWebSocket();
}

function initWebSocket() {
    console.log('Trying to open a WebSocket connection…');
    websocket = new WebSocket(gateway);
    websocket.onopen = onOpen;
    websocket.onclose = onClose;
    websocket.onmessage = onMessage;
}

function onOpen(event) {
    console.log('Connection opened');
    getValues();
}

function onClose(event) {
    console.log('Connection closed');
    setTimeout(initWebSocket, 2000);
}

function forward() {
	websocket.send("F")
}

function backward() {
	websocket.send("B")
}

function right() {
	websocket.send("R")
}

function left() {
	websocket.send("L")
}

function horn() {
	websocket.send("H")
}


function updateSpeed(element) {
    var sliderValue = document.getElementById("speedSlider").value;
    document.getElementById("speedValue").innerHTML = sliderValue;
    console.log(sliderValue);
    websocket.send(sliderValue.toString());
}