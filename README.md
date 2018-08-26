
This application implements a simple REST API server with persistence using a SQL database.

## Dependencies
The application was implemented using the following libraries and frameworks:
  * **Qt**: This application uses the Qt's native messaging mechanism to handle, internally, the received requests asynchronously. All the data types used in this application are Qt types.
  * **CPPRestSDK (Casablanca)**: For webservice implementation. This library provides classes for creating listening webservices and also can create HTTP request (not used in this project).
  * **Google Test**: Used to implement the unit testing.
  * **QAESEncryption** class from https://github.com/bricke/Qt-AES
  
This project is meant to be linked statically so the application runs without any dependency. Although, this code can be compiled using dynamic libraries.

## Repository architecture

  * **src** folder contains the source code of the application and also the unit tests.
  * **doc** folder contains the application documentation generated using Doxygen in both HTML and Latex PDF versions. It also contains a Postman collection with examples of usage of the application's API.
