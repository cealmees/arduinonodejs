# Arduino-Node.js

Este proyecto permite una integración entre un cliente basado en cuantificación de datos por parte de Arduino y un servidor bajo Node.js mostrando datos en tiempo real.

## Instalación

Este proyecto requiere [Node.js](https://nodejs.org/) v4+ para trabajar.

Clona el repositorio, instala los paquetes y monta el servidor.

```sh
$ git clone https://www.github.com/cealmees/arduinonodejs
$ cd arduinonodejs
$ npm install
$ npm start
```

## TODO

Si no cuentas con un arduino que permita conexión a red, puedes probar el servidor node con una petición get tan solo accediendo al siguiente link: 

```sh
http://localhost:8080/temp?value=12&value=13&value=11
```
 - El primer value en la URL corresponde a Temperatura.
 - El segundo value a Humedad.
 - El último value a Luz.

Al acceder a la página principal de servidor [http://localhost:8080](http://localhost:8080) e ingresar los datos en otra pestaña, podrás observar el cambio de valores en tiempo real. Esto funciona con base a tecnología websocket.

Arduino hace lo mismo, mandando en la URL al servidor con los valores que se recopilaron a través de múltiples sensores.
