#include "Koyn.h"

JsonMessage::JsonMessage()
{

}

char * JsonMessage::createJsonMessageString(int id,const  char * methodMessage, const char *  data)
{
  versionMessage = aJson.createObject();

  aJsonObject * _id = aJson.createItem(id);
  aJson.addItemToObject(versionMessage, "id", _id);
  aJsonObject * _methodMessage =    aJson.createItem(methodMessage);
  aJson.addItemToObject(versionMessage, "method", _methodMessage);
  aJsonObject * _arr =    aJson.createArray();
   aJson.addItemToArray(_arr,aJson.createItem(data));
  aJson.addItemToObject(versionMessage, "params", _arr);
  json = aJson.print(versionMessage);
  return json;
}


char * JsonMessage::createJsonMessage(int id, const char * methodMessage, int * data)
{
  versionMessage = aJson.createObject();

  aJsonObject * _id = aJson.createItem(id);
  aJson.addItemToObject(versionMessage, "id", _id);
  aJsonObject * _methodMessage =    aJson.createItem(methodMessage);
  aJson.addItemToObject(versionMessage, "method", _methodMessage);
  aJsonObject * _arr =    aJson.createArray();
  if(*data != -1)
  {
    aJson.addItemToArray(_arr,aJson.createItem(*data));
  }
  aJson.addItemToObject(versionMessage, "params", _arr);
  json = aJson.print(versionMessage);
  return json;
}

char * JsonMessage::createJsonMessage(int id, const char * methodMessage,const char * stringData,int * data)
{
  versionMessage = aJson.createObject();

  aJsonObject * _id = aJson.createItem(id);
  aJson.addItemToObject(versionMessage, "id", _id);
  aJsonObject * _methodMessage =    aJson.createItem(methodMessage);
  aJson.addItemToObject(versionMessage, "method", _methodMessage);
  aJsonObject * _arr =    aJson.createArray();
  aJson.addItemToArray(_arr,aJson.createItem(stringData));
  if(*data != -1)
  {
    aJson.addItemToArray(_arr,aJson.createItem(*data));
  }
  aJson.addItemToObject(versionMessage, "params", _arr);
  json = aJson.print(versionMessage);
  return json;
}
