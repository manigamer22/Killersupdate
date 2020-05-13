#include "clantag.h"
void clan_tag()
{
    if(!vars.misc.clantag)
        return;
    
    static std::string cur_clantag = "      AIMJUNKIES.COM";
    
    static int i = 0;
    
    if (pEngine->IsInGame()) {
        if (i > 32)
        {
            marquee(cur_clantag);
            SetClanTag(cur_clantag.c_str(), cur_clantag.c_str());
            i = 0;
        }
        else
        {
            i++;
        }
    }
}
