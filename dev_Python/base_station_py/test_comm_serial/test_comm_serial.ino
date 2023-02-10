void setup() {
  Serial.begin(115200);
}
                                                            //debutTram  destinataire    emetteur    cnt  msg  size       données     finTram
void loop() {

  // la station AABBCC00 indique à l'objet EEEEEE04 ping
  Serial.write("BA10BBBBBB02EEEEEE0501160108DA\n");           //BA 10   BB BB BB 02   EE EE EE 05   01   16   01    08                  DA
  delay(1000);

  // l'objet EEEEEE04 indique à la station AABBCC00 pong
  Serial.write("BA10CCCCCC03EEEEEE04010600DA\n");             //BA 10   CC CC CC 03   EE EE EE 04   01   06   00                        DA
  delay(5000);

  // to object 00 00 00 02 from station EE EE EE 00, parametre ask (message n°0xA3)
  Serial.write("BA0C00000002EEEEEE000F410108DA\n");           //BA 0C   00 00 00 02   EE EE EE 00   0F   41   01    08                  DA
  delay(00);

  // to object 00 00 00 02 from station EE EE EE 00, parametre write (message n°0xA2)
  Serial.write("BA1000000002EEEEEE000B420508CAFEDECADA\n");   //BA 10   00 00 00 02   EE EE EE 00   0B   42   05     08 CA FE DE CA     DA
  delay(00);

  // à toutes stations, un objet 04, déclare I_HAVE_NO_SERVER_ID
  Serial.write("BA10FFFFFFFFEEEEEE0401FD00DA\n");             //BA 0b   FF FF FF FF   EE EE EE 04   01   FD   00                        DA
  delay(2000);

  // la station AABBCC00 indique à l'objet EEEEEE04 qu'elle est désormais son server !
  Serial.write("BA10AAAAAA01EEEEEE0601FE00DA\n");             //BA 10   AA AA AA 01   EE EE EE 06   01   FE   00                        DA
  delay(500);
}
