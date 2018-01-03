#include "Message.h"

Message::Message(char v1,char v2,char v3,int8_t prio):priority{prio}
{
    value[0]=v1;
    value[1]=v2;
    value[2]=v3;
}

Message::~Message()
{
    //dtor
}
char Message::popFirstCharacter()
{
    char pierwszyZnak=value[0];
    value[0]=value[1];
    value[1]=value[2];
    value[2]=EMPTYVALUE;
    return pierwszyZnak;
}
bool Message::isEmpty()
{
    return (value[0]==EMPTYVALUE && value[1]==EMPTYVALUE && value[2]==EMPTYVALUE);
}
void Message::setLastCharacter(char v1)
{
    if(value[0]==EMPTYVALUE)
        value[0]=v1;
    else if(value[1]==EMPTYVALUE)
        value[1]=v1;
    else if(value[2]==EMPTYVALUE)
        value[2]=v1;
}
void Message::setPriority(int8_t priority)
{
    this->priority=priority;
}
int8_t Message::getPriority()
{
    return this->priority;
}
std::string Message::toString()
{
    std::string r;
    if(value[0]!=EMPTYVALUE)
      r=r+char(value[0]+'A');
    if(value[1]!=EMPTYVALUE)
      r=r+char(value[1]+'A');
    if(value[2]!=EMPTYVALUE)
      r=r+char(value[2]+'A');
    return r;
}
