const char MQTTCONFIG[] PROGMEM = R"=====(
<body>
<div id='msect'>
<div id='bo'></div>
  <div id='help'>
  <span class='close' onclick='sl();'>&times;</span><h3>MOSQUITTO HELP</h3>
  Mosquitto can be used to send short messages back and forth to an mqtt server (broker).
  With these messages you can switch or update sensors. <br><br>
  <b>enable:</b><br>Check this if you want to use mosquitto.<br><br>
  <b>address:</b><br>The (ip) address of the mqtt-broker cq domoticz<br><br>
  <b>send topic:</b><br>For outgoing communication to domoticz, the topic is '<strong>domoticz/in</strong>'.<br><br>
  <b>receive topic:</b><br>The topic where will be subscribed for incoming messages.<br><br>
  <b>mqtt_username en password</b><br>Optional, these can be left empty.
  <br><br>
  <b>json format depends on the topic:</b><br>{"inv_serial":"408000158215","temp":"19.3","p0":"0.0","p1":"5.2"}<br>
  or to domoticz: {"inv_serial":"408000158215","idx":879,"nvalue":0,"svalue":"5.2"}

  <br><br>
  </div>
</div>
<div id='msect'>
  <kop>MOSQUITTO CONFIGURATION</kop>
</div>
<div id='msect'>
  <div class='divstijl'>
  <center>
  <form id='formulier' method='get' action='MQTTconfig' oninput='showSubmit();'><table>
  
  <tr><td style='width:130px;'>enable ?<td><input type='checkbox' style='width:30px; height:30px;' name='mqtEn' #check></input></tr> 
  <tr><td >address<td><input class='inp6' name='mqtAdres' value='{mqttAdres}' size='31' placeholder='broker adres'></tr>
  <tr><td >port<td><input class='inp2' name='mqtPort' value='{mqttPort}' size='31' placeholder='mqtt port'></tr>
  <tr><td>receive topic:&nbsp<td><input class='inp6' name='mqtinTopic' value='{mqttinTopic}' placeholder='mqtt topic send' length='60'></tr>
  <tr><td>send topic:&nbsp<td><input class='inp6' name='mqtoutTopic' value='{mqttoutTopic}' placeholder='mqtt topic receive' length='60'></tr>
  <tr><td>username:&nbsp<td><input class='inp4' name='mqtUser' value='{mqtu}' size='4' length='4'></td></tr>
  <tr><td>password:&nbsp<td><input class='inp4' name='mqtPas' value='{mqtp}' size='4' length='4'></td></tr>
  </form>
  </td></table>
  </div><br>
</div>
<div id='msect'>
  <ul>
  <li id='sub'><a href='#' onclick='submitFunction("/SW=BACK")'>save</a></li>
  <li><a href='/MENU'>done</a>
  <li><a href='#' onclick='helpfunctie()'>help</a>
  <li><a href='/MQTT_TEST' >test</a></ul>
  <br></div>
</div>
</body></html>
)=====";


void zendPageMQTTconfig() {
   //DebugPrintln("we are at zendPageMQTTconfig");
//toSend = FPSTR(HTML_HEAD);
//toSend.replace("tieTel", swname );
toSend = FPSTR(HTML_HEAD);
toSend += FPSTR(MQTTCONFIG);  

  //altijd de mqtt gegevens terugzetten
 
if (Mqtt_Enabled) { toSend.replace("#check", "checked");}
toSend.replace("{mqttAdres}", Mqtt_Broker);
toSend.replace("{mqttPort}", Mqtt_Port);
toSend.replace("{mqttinTopic}", Mqtt_inTopic);
toSend.replace("{mqttoutTopic}", Mqtt_outTopic);
toSend.replace("{mqtu}", Mqtt_Username );
toSend.replace("{mqtp}", Mqtt_Password );
//toSend.replace("{idx1}", String(Mqtt_Idx));
}

void handleMQTTconfig(AsyncWebServerRequest *request) {

  //collect serverarguments
  Mqtt_Broker = request->arg("mqtAdres");
  //DebugPrint("Mqtt_Broker na strcpy = "); //DebugPrintln(Mqtt_Broker); // oke

  Mqtt_Port = request->arg("mqtPort");
  //DebugPrint("mqttPort = "); //DebugPrintln(Mqtt_Port); // ok

  Mqtt_inTopic = request->arg("mqtinTopic");
  //DebugPrint("mqtt_inTopic na strcpy = "); //DebugPrintln(String(Mqtt_inTopic)); // oke

  Mqtt_outTopic = request->arg("mqtoutTopic");
  //DebugPrint("mqtt_outTopic na strcpy = "); //DebugPrintln(String(Mqtt_outTopic)); // oke
  
  Mqtt_Username = request->arg("mqtUser");
  //DebugPrint("Mqtt_Username na strcpy = "); //DebugPrintln(Mqtt_Username); // oke

  Mqtt_Password = request->arg("mqtPas");
  //DebugPrint("Mqtt_Username na strcpy = "); //DebugPrintln(Mqtt_Password); // oke

  //Mqtt_Idx = request->arg("mqidx1").toInt(); 

// de selectbox
   char tempChar[1] = "";
   String dag = request->arg("mqtEn");  // mqselect
   if ( dag == "on") { Mqtt_Enabled = true; } else { Mqtt_Enabled = false; }

//  toSend = FPSTR(CONFIRM);
//  toSend.replace("SW=BACK", "MQTT");
//  request->send(200, "text/html", toSend); //send the html code to the client
  DebugPrintln("saved mqttconfig");
  mqttConfigsave();  // 
  actionFlag=24; // reconnect with these settings
}
