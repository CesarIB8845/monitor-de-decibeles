#include <UIPEthernet.h>  // Librería para manejar la comunicación Ethernet con el módulo ENC28J60

// Configuración de red
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };  // Dirección MAC del dispositivo (debe ser única en la red)
IPAddress ip(192, 168, 1, 100);  // Dirección IP estática asignada al Arduino
EthernetServer server(80);  // Crea un servidor en el puerto 80 (HTTP)

// Pines de entrada de los micrófonos conectados a entradas analógicas A0 y A1
const int mic1 = A0;  // Micrófono 1 conectado al pin A0
const int mic2 = A1;  // Micrófono 2 conectado al pin A1

void setup() {
    Serial.begin(9600);  // Inicia la comunicación serial para depuración
    Ethernet.begin(mac, ip);  // Inicia la conexión Ethernet con la MAC e IP especificadas
    server.begin();  // Inicia el servidor para escuchar solicitudes entrantes en el puerto 80
}

void loop() {
    EthernetClient client = server.available();  // Espera a que un cliente se conecte al servidor
    if (client) {  // Si hay un cliente conectado
        String request = client.readStringUntil('\r');  // Lee la solicitud HTTP hasta encontrar un retorno de carro
        client.flush();  // Limpia el búfer de entrada

        // Lee los valores analógicos de los micrófonos
        int value1 = analogRead(mic1);  // Valor del micrófono 1 (0-1023)
        int value2 = analogRead(mic2);  // Valor del micrófono 2 (0-1023)

        // Convierte los valores analógicos en una escala simulada de decibelios (0-100)
        int db1 = map(value1, 0, 1023, 0, 100);  // Mapea el valor del micrófono 1
        int db2 = map(value2, 0, 1023, 0, 100);  // Mapea el valor del micrófono 2

        // Crea una cadena JSON con los datos de ambos micrófonos
        String response = "{";  
        response += "\"mic1\":" + String(db1) + ",";  // Agrega el valor de mic1 en formato JSON
        response += "\"mic2\":" + String(db2) + "}";  // Agrega el valor de mic2 y cierra el objeto JSON

        // Envía la respuesta HTTP al cliente con encabezados apropiados
        client.println("HTTP/1.1 200 OK");  // Código de estado HTTP 200 (éxito)
        client.println("Content-Type: application/json");  // Especifica que el contenido es JSON
        client.println("Connection: close");  // Cierra la conexión después de enviar la respuesta
        client.println();  // Línea en blanco que separa encabezados del cuerpo
        client.println(response);  // Envía el cuerpo de la respuesta (el JSON)

        client.stop();  // Finaliza la conexión con el cliente
    }
}



