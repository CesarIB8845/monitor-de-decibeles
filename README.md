# Monitor de Decibeles - Proyecto con Arduino y Web

Este proyecto permite medir el nivel de decibeles en tiempo real utilizando dos micrófonos MAX4466 conectados a placas **Arduino Uno** y visualizarlos en un dashboard web. El dashboard muestra barras de intensidad para cada micrófono, permitiendo monitorear los niveles de sonido de dos ubicaciones diferentes, por ejemplo, una cancha y una sala.

## Componentes utilizados

- **Arduino Uno** (ARD-010)
- **Micrófono electret MAX4466**
- **Módulo Ethernet ENC28J60**
- **Web server con HTML, CSS y JavaScript**
- **Bibliotecas necesarias para Arduino**:
  - `Ethernet.h`
  - `SPI.h`

## Descripción del Proyecto

### 1. Parte del Hardware (Arduino)

El proyecto se basa en dos placas **Arduino Uno**, cada una con un micrófono **MAX4466** y un módulo **Ethernet ENC28J60**. Las placas se encargan de medir los niveles de sonido a través de los micrófonos y enviar esos datos a un servidor web. El servidor estará hospedado en una PC local o en la nube y se puede acceder mediante un navegador web.

#### Conexiones de Hardware:
1. **Micrófono MAX4466**:
   - Conectar el pin de salida del micrófono a una entrada analógica del Arduino (por ejemplo, A0).
2. **Módulo Ethernet ENC28J60**:
   - Conectar el módulo Ethernet al Arduino siguiendo la pinout estándar del ENC28J60 y asegurarse de que la placa tiene una IP fija o esté configurada correctamente para recibir las señales.

#### Código Arduino:

El código para Arduino hace lo siguiente:
- Leer los valores de los micrófonos utilizando las entradas analógicas.
- Convertir los valores leídos en niveles de decibeles utilizando un algoritmo básico.
- Enviar los niveles de decibeles a través del módulo Ethernet a un servidor web (por ejemplo, un servidor local o en la nube).

### 2. Parte del Software (Interfaz Web)

La interfaz web es una página en HTML, CSS y JavaScript que visualiza en tiempo real los niveles de decibeles de ambos micrófonos. La página tiene dos barras que muestran la intensidad del sonido para cada micrófono. Estas barras cambian en tiempo real según el nivel de sonido medido.

#### Funcionalidad de la Interfaz:
- **Carga de dispositivos**: La página web detecta y carga automáticamente los dispositivos de entrada disponibles (micrófonos) y permite seleccionar dos micrófonos para monitoreo.
- **Monitoreo en tiempo real**: Una vez que se seleccionan los micrófonos, el botón "Iniciar Monitoreo" comienza a mostrar los niveles de decibeles en tiempo real, actualizando las barras de intensidad.
- **Calibración de micrófonos**: El botón "Calibrar Micrófonos" permite calibrar los micrófonos antes de comenzar el monitoreo, lo que ayuda a obtener lecturas más precisas.
- **Detención de monitoreo**: El botón "Detener Monitoreo" detiene el monitoreo en curso y resetea las barras.

#### Código HTML, CSS y JavaScript:

El código en el archivo `index.html` realiza lo siguiente:
- Carga dinámicamente los dispositivos de entrada de audio disponibles (micrófonos) mediante la API `navigator.mediaDevices.enumerateDevices`.
- Usa la API Web Audio (`AudioContext`) para procesar el audio de los micrófonos seleccionados y analizar los niveles de sonido.
- Muestra el nivel de sonido en decibeles en tiempo real mediante barras de progreso que se actualizan conforme cambian los niveles.

### 3. Servicio HTTP

El servicio HTTP está implementado a través de un servidor web que recibe las señales de los micrófonos desde el Arduino (mediante el módulo Ethernet ENC28J60) y las expone a la página web en tiempo real.

#### Cómo funciona el servicio HTTP:
1. **Configuración de la red**: El Arduino se conecta a la red local a través del módulo Ethernet y obtiene una dirección IP estática para poder enviar datos al servidor web.
2. **Servidor Web en la PC**: El servidor web es accesible a través de la dirección IP local del Arduino. La página web que se visualiza en el navegador se conecta al Arduino mediante HTTP, obteniendo los datos de decibeles.
3. **Comunicación**: El servidor web utiliza una API de JavaScript para enviar solicitudes HTTP y obtener los valores de los decibeles desde el Arduino. Estos valores se utilizan para actualizar las barras en la interfaz.

### 4. Cómo usar el servicio HTTP:

Para utilizar el servicio HTTP y monitorear los niveles de decibeles en tiempo real, sigue estos pasos:

1. **Configura el hardware**:
   - Conecta el micrófono MAX4466 al Arduino.
   - Conecta el módulo Ethernet ENC28J60 a la placa Arduino.
   - Asegúrate de que el Arduino esté correctamente configurado con la dirección IP de tu red.

2. **Sube el código de Arduino**:
   - Sube el código necesario a las placas Arduino. Este código se encargará de leer los valores de los micrófonos y enviarlos al servidor web a través del módulo Ethernet.

3. **Ejecuta el servidor web**:
   - Abre el archivo `index.html` en tu navegador. Esto servirá como la interfaz de monitoreo.
   - Asegúrate de que el servidor web y el Arduino estén en la misma red para que puedan comunicarse.

4. **Usa la interfaz web**:
   - **Selecciona los micrófonos**: Elige los dispositivos de entrada (micrófonos) desde el menú desplegable.
   - **Inicia el monitoreo**: Haz clic en "Iniciar Monitoreo" para comenzar a recibir datos en tiempo real.
   - **Calibra los micrófonos**: Si es necesario, calibra los micrófonos antes de iniciar el monitoreo.
   - **Detén el monitoreo**: Haz clic en "Detener Monitoreo" cuando hayas terminado.

5. **Ver los resultados**: Observa las barras de decibeles para cada micrófono y monitorea los niveles de sonido en tiempo real.

### Requisitos

1. **Arduino IDE** para subir el código a las placas Arduino.
2. **Conexión a Internet**: El módulo Ethernet ENC28J60 requiere estar conectado a la red local para poder enviar los datos.
3. **Navegador web**: Cualquier navegador moderno (como Chrome, Firefox, Edge) para visualizar la interfaz de usuario.

## Contribuciones

Las contribuciones son bienvenidas. Si deseas mejorar el proyecto, puedes crear un "pull request" con tus cambios o sugerir nuevas características.

## Licencia

Este proyecto es de código abierto bajo la Licencia MIT.

