#include "pch.h"
#include "Message.h"


MediaItem::MediaItem()
    : id(""), 
    url(""), 
    fileName("")
{
}

Message::Message()
    : id(""),
    content(""),
    isSend(0),
    createdAt(""),
    messageType(0)
{
}