#include <UIPEthernet.h>

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(192, 168, 1, 100);
EthernetServer server(80);

const int mic1 = A0;
const int mic2 = A1;

const char dashboard[] PROGMEM = R"rawliteral(
<!DOCTYPE html><html><head><title>Monitor dB</title><meta name="viewport" content="width=device-width,initial-scale=1">
<style>body{font-family:sans-serif;text-align:center;background:#2d3748;color:#fff;margin:0;padding:20px}
h1{color:#f98012}.container{display:flex;flex-wrap:wrap;justify-content:center;gap:20px;margin-top:20px}
.micro-block{background:#1a237e;padding:15px;border-radius:10px;width:45%;min-width:250px}
.bar-container{width:100%;background:#e2e8f0;height:30px;border-radius:5px;margin:10px 0;overflow:hidden}
.bar{height:100%;width:0%;background:#f98012;transition:width 0.3s}
.db-value{color:#fff;font-weight:bold;margin:5px 0}
button{background:#f98012;color:#fff;border:none;padding:8px 16px;border-radius:4px;margin:5px;cursor:pointer}
button:disabled{background:#ccc}</style></head>
<body>
<h1>Monitor de Decibeles</h1>
<div><input type="text" id="arduinoIp" value="192.168.1.100">
<button id="testBtn">Probar Conexión</button></div>
<div id="status">Esperando conexión...</div>
<button id="startBtn">Iniciar</button><button id="stopBtn" disabled>Detener</button>
<div class="container">
<div class="micro-block"><h3>Micrófono 1 (A0)</h3>
<div class="bar-container"><div id="bar1" class="bar"></div></div>
<div id="value1" class="db-value">0 dB</div></div>
<div class="micro-block"><h3>Micrófono 2 (A1)</h3>
<div class="bar-container"><div id="bar2" class="bar"></div></div>
<div id="value2" class="db-value">0 dB</div></div></div>
<script>
let updateInterval;
document.getElementById('startBtn').onclick=function(){
  const ip=document.getElementById('arduinoIp').value.trim();
  this.disabled=true; document.getElementById('stopBtn').disabled=false;
  document.getElementById('status').textContent='Monitoreo activo';
  updateInterval=setInterval(async()=>{
    try{
      const response=await fetch(`http://${ip}/data`);
      if(!response.ok)throw new Error();
      const data=await response.json();
      updateDisplay(0,data.mic1); 
      updateDisplay(1,data.mic2);
    }catch(e){
      document.getElementById('status').textContent='Error de conexión';
      clearInterval(updateInterval);
    }
  },500);
};
document.getElementById('stopBtn').onclick=function(){
  clearInterval(updateInterval);
  document.getElementById('startBtn').disabled=false;
  this.disabled=true;
  document.getElementById('status').textContent='Monitoreo detenido';
};
document.getElementById('testBtn').onclick=async function(){
  const ip=document.getElementById('arduinoIp').value.trim();
  document.getElementById('status').textContent=`Probando ${ip}...`;
  try{
    await fetch(`http://${ip}`,{method:'HEAD'});
    document.getElementById('status').textContent='Conexión exitosa';
    document.getElementById('startBtn').disabled=false;
  }catch(e){
    document.getElementById('status').textContent='Conexión fallida';
  }
};
function updateDisplay(mic,value){
  const bar=document.getElementById(`bar${mic+1}`);
  const val=document.getElementById(`value${mic+1}`);
  const percent=Math.min(100,Math.max(0,value));
  bar.style.width=`${percent}%`;
  val.textContent=`${value.toFixed(1)} dB`;
  bar.style.backgroundColor=value<30?'#ff4444':'#f98012';
}
</script></body></html>
)rawliteral";

void setup() {
  Serial.begin(9600);
  Ethernet.begin(mac, ip);
  server.begin();
  
  // Verificación de pines
  pinMode(mic1, INPUT);
  pinMode(mic2, INPUT);
  
  Serial.println("Servidor iniciado");
  Serial.println("Probando lecturas...");
  Serial.print("Mic 1 (A0): "); Serial.println(analogRead(mic1));
  Serial.print("Mic 2 (A1): "); Serial.println(analogRead(mic2));
}

void loop() {
  EthernetClient client = server.available();
  
  if (client) {
    String request = client.readStringUntil('\r');
    client.flush();
    
    if (request.indexOf("GET / ") != -1 || request.indexOf("GET /index.html") != -1) {
      sendDashboard(client);
    } 
    else if (request.indexOf("GET /data") != -1) {
      sendSensorData(client);
    }
    client.stop();
  }
}

void sendDashboard(EthernetClient &client) {
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("Connection: close");
  client.println();
  client.println(reinterpret_cast<const __FlashStringHelper*>(dashboard));
}

void sendSensorData(EthernetClient &client) {
  // Lectura con verificación de errores
  int raw1 = analogRead(mic1);
  int raw2 = analogRead(mic2);
  
  // Conversión a dB con valores mínimos/máximos
  float db1 = constrain(raw1 * 0.0978, 0, 100);
  float db2 = constrain(raw2 * 0.0978, 0, 100);
  
  // Debug por serial
  Serial.print("Lecturas - Mic1: "); Serial.print(raw1);
  Serial.print(" ("); Serial.print(db1); Serial.print(" dB), ");
  Serial.print("Mic2: "); Serial.print(raw2);
  Serial.print(" ("); Serial.print(db2); Serial.println(" dB)");

  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: application/json");
  client.println("Connection: close");
  client.println();
  client.print("{\"mic1\":");
  client.print(db1);
  client.print(",\"mic2\":");
  client.print(db2);
  client.print("}");
}


