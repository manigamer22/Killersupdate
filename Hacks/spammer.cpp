#include "spammer.h"

// Thanks @pwned

vector<string> spamMessages =
{   // Add messages here
    "Afk that’s why I turned this shit on",
    "Auto shoot is on so leave me alone",
    
};


void DoSpammer()
{
    if (!pEngine->IsInGame())
        return;
    
    if (!vars.misc.spammer)
        return;
    
    
    
    static int i;
    i++;
    
    if(i % 10 == 5)
    {
        string message = "say ";
        message += spamMessages[rand() % spamMessages.size()];
        pEngine->ExecuteClientCmd(message.c_str());
    }
    
    if(i > 1000)
        i = 0;
}
