#include "AsyncTCP.h" //include the AsyncTCP.h library
#include "painlessMesh.h" //include the painless mesh library


//define your mesh credentials
#define   PREFIX     "meshprefix"
#define   PASSWORD   "meshpassword"
#define   PORT       5555

Scheduler userScheduler; // to control your personal task
painlessMesh  mesh; //declare the mesh connection

// User stub
void sendMessage() ; // Prototype so PlatformIO doesn't complain

Task taskSendMessage( TASK_SECOND * 1 , TASK_FOREVER, &sendMessage );

void sendMessage() { //declare the message to be sent
  String msg = "Hi from node"; //enter your message here
  msg += mesh.getNodeId();
  mesh.sendBroadcast( msg );
  taskSendMessage.setInterval( random( TASK_SECOND * 1, TASK_SECOND * 5 ));
}

// received the message, from 
void receivedCallback( uint32_t from, String &msg ) {
  Serial.printf("Received a message from: %u msg=%s\n", from, msg.c_str());
}

// print into the serial port that a new node has joined along with the node id
void newConnectionCallback(uint32_t nodeId) {
    Serial.printf("A new node has joined, nodeId = %u\n", nodeId);
}

// print in case the connections have changed
void changedConnectionCallback() {
  Serial.printf("The connections were changed! \n");
}

void nodeTimeAdjustedCallback(int32_t offset) {
    Serial.printf("Adjusted time %u. Offset = %d\n", mesh.getNodeTime(),offset);
}

void setup() {
  Serial.begin(115200); //intialize the serial baud rate to 115200 bauds

//mesh.setDebugMsgTypes( ERROR | MESH_STATUS | CONNECTION | SYNC | COMMUNICATION | GENERAL | MSG_TYPES | REMOTE ); // all types on
  mesh.setDebugMsgTypes( ERROR | STARTUP );  // set before init() so that you can see startup messages

  mesh.init( MESH_PREFIX, MESH_PASSWORD, &userScheduler, MESH_PORT );
  mesh.onReceive(&receivedCallback);
  mesh.onNewConnection(&newConnectionCallback);
  mesh.onChangedConnections(&changedConnectionCallback);
  mesh.onNodeTimeAdjusted(&nodeTimeAdjustedCallback);

  userScheduler.addTask( taskSendMessage );
  taskSendMessage.enable();
}

void loop() {
  // it will run the user scheduler as well
  mesh.update();
}
