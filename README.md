# Monitor de Decibeles en Tiempo Real

## Descripción del Proyecto

Este proyecto consiste en un sistema basado en Arduino que mide los niveles de decibelios (dB) a través de dos micrófonos conectados a los pines analógicos A0 y A1. Los valores de los micrófonos se leen y se envían a través de una red Ethernet utilizando el protocolo HTTP para ser visualizados en un navegador web. El propósito de este sistema es ofrecer un monitoreo en tiempo real de los niveles de ruido en un entorno, mostrándolos gráficamente en un dashboard accesible desde cualquier dispositivo conectado a la misma red.

## Funcionamiento del Proyecto

### Hardware
- **Arduino Uno**: Microcontrolador utilizado para la lectura de datos.
- **Micrófonos electret**: Conectados a los pines analógicos A0 y A1 de Arduino para captar los niveles de ruido.
- **Módulo Ethernet ENC28J60**: Permite a Arduino conectarse a una red local y servir los datos a través de HTTP.

### Software
- El código de Arduino se encarga de:
  - Leer los valores analógicos de los micrófonos.
  - Convertir estos valores a decibelios utilizando una fórmula sencilla.
  - Servir los datos mediante un servidor web basado en el protocolo HTTP.
  - Enviar los datos en formato JSON cuando se hace una petición a la URL `/data`.
  - Servir una página HTML para visualizar los datos de los micrófonos en tiempo real.

### Interfaz Web
El dashboard se visualiza en cualquier navegador, mostrando barras de progreso que representan el nivel de decibelios de cada micrófono. La página también incluye botones para iniciar y detener la monitorización, además de un campo para probar la conexión a Arduino.

### Protocolo HTTP en el Código
El protocolo HTTP se utiliza para la comunicación entre el servidor (Arduino) y el cliente (navegador). A continuación se explica cómo se usa:

1. **Petición HTTP del Cliente**:
   Cuando un navegador realiza una solicitud HTTP, el Arduino recibe la petición en la función `loop()`. En este caso, se maneja específicamente la solicitud `GET` a las rutas `/` o `/index.html` para servir el dashboard y a `/data` para obtener los datos de los micrófonos.

2. **Respuesta HTTP del Servidor**:
   Arduino responde a las peticiones HTTP mediante la función `sendDashboard()` o `sendSensorData()`. En ambas funciones:
   - Se establece el encabezado HTTP, indicando que la respuesta es de tipo `text/html` o `application/json` según corresponda.
   - Se envía el contenido correspondiente (el HTML del dashboard o los datos JSON de los micrófonos).

### Ejemplo de Petición y Respuesta

- **Petición GET** a `/data`:
  - El navegador envía una solicitud GET a `http://192.168.1.100/data`.
  - Arduino lee los valores de los micrófonos, los convierte a dB y responde con un JSON:
    ```json
    {"mic1": 45.2, "mic2": 50.3}
    ```

- **Petición GET** a `/` o `/index.html`:
  - El navegador solicita la página principal para visualizar el dashboard.
  - Arduino responde con el HTML del dashboard que incluye las barras de progreso y los valores de los micrófonos.

## Requisitos

- **Hardware**:
  - Arduino Uno (o compatible).
  - Módulo Ethernet ENC28J60.
  - Dos micrófonos electret (MAX4466 u otros compatibles).
  - Fuente de alimentación adecuada para el Arduino y el módulo Ethernet.

- **Software**:
  - Arduino IDE con la biblioteca `UIPEthernet` instalada.
  - Navegador web para visualizar el dashboard.
  - Conexión a una red local (preferentemente una red con DHCP habilitado).

## Posibles Mejoras y Futuras Implementaciones

1. **Mejoras en la calibración**: Actualmente, los micrófonos se leen de manera simple. Implementar una calibración más avanzada para adaptar el sistema a diferentes entornos y micrófonos.
  
2. **Almacenamiento de datos históricos**: Agregar funcionalidad para almacenar los datos de los micrófonos a una base de datos (por ejemplo, SQLite) o en la memoria interna del dispositivo para análisis posterior.

3. **Interfaz más compleja**: Mejorar el diseño del dashboard, agregando gráficos de líneas para mostrar la evolución de los decibelios a lo largo del tiempo.

4. **Control de múltiples dispositivos**: Ampliar el sistema para manejar múltiples dispositivos (más de dos micrófonos), permitiendo la visualización de varios puntos de monitoreo en una sola interfaz.

5. **Notificaciones de alerta**: Configurar alertas que se activen cuando los niveles de ruido superen un umbral definido, enviando notificaciones por correo o mensaje de texto.

## Contribuciones a la Comunidad Open Source

Este proyecto tiene como objetivo ofrecer una solución sencilla y accesible para el monitoreo de ruido en tiempo real utilizando herramientas y componentes comunes de Arduino. Al compartir este código, se invita a la comunidad a mejorar, adaptar y expandir este proyecto según sus necesidades. Las contribuciones pueden incluir mejoras en la interfaz, optimización del código, o la implementación de nuevas funcionalidades.

---

**Licencia**: Este proyecto está disponible bajo la licencia MIT, lo que permite su uso, modificación y distribución libre para fines comerciales y no comerciales.

