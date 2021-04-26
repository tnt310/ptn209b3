
https://linhkienthuduc.com/huong-dan-ket-noi-tcp-ip-module-sim-4g-sim7600-a7670

/*----FINAL TEST FOR MQTT WITH NO SSL/TLS------------------------------------------------------------------------------*/
1. AT+NETOPEN<CR><LF>
2. AT+IPADDR<CR><LF>
3. AT+CMQTTSTART<CR><LF>
4. AT+CMQTTACCQ=0,"mqtt"<CR><LF>  // 0: TCP, 1:TLS
6.  AT+CMQTTCONNECT=0,"tcp://m14.cloudmqtt.com:19613",3600,1,"yktdxpqb","VKCG6yboYrYd"<CR><LF>

#SUBSCRIE TOPIC AFTER CONNECTING SUCESSFULLY
7. AT+CMQTTSUB=0,9,0,1<CR><LF> // subscribed  AT+CMQTTSUB=0,9,0,1
>subscribe

#PUBLISH DATA TO SERVER
8. AT+CMQTTTOPIC=0,43<CR><LF> // Set the topic for the PUBLISH message
>606ff2e222c1752264934dbb/upstream/telemetry
9.AT+CMQTTPAYLOAD=0,105<CR><LF>// Set the payload for the PUBLISH message
>{CH1_INV1_SEN1:[{time:14:47:45 4.14.21,value:12345}],CH1_INV2_SEN2:[{time:14:47:45 4.14.21,value:12345}]}
10. AT+CMQTTPUB=0,1,148<CR><LF>  // Publish topic and message 

#DISCONNECT AND RELEASE MQTT CLIENT
11. AT+CMQTTDISC=0,120<CR><LF> // Disconnect from server
12. AT+CMQTTREL=0<CR><LF> // release a client
13. AT+CMQTTSTOP<CR><LF> //stop MQTT Service
14. AT+NETCLOSE<CR><LF>

#RESET MODULE
AT+CRESET<CR><LF> // reset module
AT+CPIN?<CR><LF> // kiểm tra SIM
AT+CREG?<CR><LF> // kiểm tra đăng ký mạng
AT+CSQ<CR><LF> // kiểm tra chất lượng mạng