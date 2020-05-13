//
//  Config.cpp
//  vHook
//

#include "../main.h"
#include "Config.h"
#include "skins.h"

using namespace std;

Config* config = new Config();
Config* skins_cfg = new Config();
Skins skin;

const char* ConfigName;
string user     = getenv("USER");
string dsk      = "/Users/" + user + "/Desktop/";

std::string fdr      = "/Users/" + user + "/Desktop/killers";

std::string scout    = "/Users/" + user + "/Desktop/killers/scout.ini";
std::string autos    = "/Users/" + user + "/Desktop/killers/autos.ini";
std::string legit    = "/Users/" + user + "/Desktop/killers/legit.ini";
std::string smg    = "/Users/" + user + "/Desktop/killers/smg.ini";
std::string rifles    = "/Users/" + user + "/Desktop/killers/rifles.ini";
std::string skins    = "/Users/" + user + "/Desktop/killers/skins.ini";

bool GetBoolValue(bool Value)
{
    return Value;
}
int GetIntValue(int Value)
{
    return Value;
}

float GetFloatValue(float Value)
{
    return Value;
}

void Config::getConfig(int ConfigNo) {
    switch (ConfigNo) {
        case 0:
            ConfigName = scout.c_str();
            break;
        case 1:
            ConfigName = autos.c_str();
            break;
        case 2:
            ConfigName = legit.c_str();
            break;
        case 3:
            ConfigName = smg.c_str();
            break;
        case 4:
            ConfigName = rifles.c_str();
            break;
        default:
            break;
    }
}

bool fileExist(const char* path) {
    struct stat info;
    return stat(path, &info) == 0 && S_ISREG(info.st_mode);
}

void Config::LoadConfig() {
    
    cfg.SetUnicode(true);
    cfg.LoadFile(ConfigName);
    
    // Left Aimbot
    vars.aimbot.enabled     = cfgget_b("Aimbot", "Enabled");
    vars.aimbot.silent      = cfgget_b("Aimbot", "Silent");
    vars.aimbot.rcs         = cfgget_b("Aimbot", "RCS");
    vars.aimbot.rcsf        = cfgget_i("Aimbot", "RCSf");
    vars.aimbot.FovToPlayer = cfgget_i("Aimbot", "FOV");
    vars.aimbot.hitbox      = cfgget_i("Aimbot", "Bone");
    
    // Middle Aimbot
    vars.aimbot.autoscope      = cfgget_b("Aimbot", "Auto Scope");
    vars.aimbot.autopistol     = cfgget_b("Aimbot", "Auto Pistol");
    vars.aimbot.autocrouch     = cfgget_b("Aimbot", "Auto Crouch");
    vars.aimbot.hitscan     = cfgget_b("Aimbot", "Hitscan");
    vars.aimbot.autowall     = cfgget_b("Aimbot", "Auto Wall");
    vars.aimbot.mindmg     = cfgget_i("Aimbot", "Mindmg");
    vars.aimbot.Yawresolver     = cfgget_b("Aimbot", "Yaw Resolver");
    vars.aimbot.yresolve     = cfgget_i("Aimbot", "Yresolve");
    vars.aimbot.autoshoot     = cfgget_b("Aimbot", "Auto Shoot");
    vars.aimbot.trigger = cfgget_b("Aimbot", "Triggerbot");
    //vars.aimbot.autostop = cfgget_b("Aimbot", "Auto Stop");
    vars.misc.antiResolverFlip     = cfgget_b("Aimbot", "LBY Flip");
    
    vars.aimbot.LegitEnabled     = cfgget_b("Aimbot", "Legit Enabled");
    
    vars.aimbot.pistolFOV = cfgget_f("Aimbot", "Pistol FOV");
    vars.aimbot.pistolsmooth     = cfgget_b("Aimbot", "Pistol Smooth");
    vars.aimbot.pistolsmoothf = cfgget_f("Aimbot", "Pistol Smooth FOV");
    vars.aimbot.legitPistolHitscan     = cfgget_b("Aimbot", "Legit Pistol Hitscan");
    vars.aimbot.legitPistolHitscanType     = cfgget_i("Aimbot", "Legit Pistol Hitscan Type");
    
    vars.aimbot.rifleFOV = cfgget_f("Aimbot", "Rifle FOV");
    vars.aimbot.riflesmooth     = cfgget_b("Aimbot", "Rifle Smooth");
    vars.aimbot.riflesmoothf = cfgget_f("Aimbot", "Rifle Smooth FOV");
    vars.aimbot.legitRifleHitscan     = cfgget_b("Aimbot", "Legit Rifle Hitscan");
    vars.aimbot.legitRifleHitscanType     = cfgget_i("Aimbot", "Legit Rifle Hitscan Type");
    
    vars.aimbot.sniperFOV = cfgget_f("Aimbot", "Sniper FOV");
    vars.aimbot.snipersmooth     = cfgget_b("Aimbot", "Sniper Smooth");
    vars.aimbot.snipersmoothf = cfgget_f("Aimbot", "Sniper Smooth FOV");
    vars.aimbot.legitSniperHitscan     = cfgget_b("Aimbot", "Legit Sniper Hitscan");
    vars.aimbot.legitSniperHitscanType     = cfgget_i("Aimbot", "Legit Sniper Hitscan Type");
    
    vars.aimbot.smgFOV = cfgget_f("Aimbot", "Smg FOV");
    vars.aimbot.smgsmooth     = cfgget_b("Aimbot", "Smg Smooth");
    vars.aimbot.smgsmoothf = cfgget_f("Aimbot", "Smg Smooth FOV");
    vars.aimbot.legitSmgHitscan     = cfgget_b("Aimbot", "Legit Smg Hitscan");
    vars.aimbot.legitSmgHitscanType     = cfgget_i("Aimbot", "Legit Smg Hitscan Type");
    
    vars.aimbot.heavyFOV = cfgget_f("Aimbot", "Heavy FOV");
    vars.aimbot.heavysmooth     = cfgget_b("Aimbot", "Heavy Smooth");
    vars.aimbot.heavysmoothf = cfgget_f("Aimbot", "Heavy Smooth FOV");
    vars.aimbot.legitHeavyHitscan     = cfgget_b("Aimbot", "Legit Heavy Hitscan");
    vars.aimbot.legitHeavyHitscanType     = cfgget_i("Aimbot", "Legit Heavy Hitscan Type");
    
    //Right Aimbot
    vars.misc.antiaim  = (ButtonCode_t)cfgget_b("Aimbot", "AntiAim Enabled");
    vars.misc.thirdpersonmode     = cfgget_b("Aimbot", "Show Real Angles");
    vars.misc.thirdperson     = cfgget_b("Aimbot", "Thirdperson");
    vars.misc.fakeaa     = cfgget_b("Aimbot", "Fake aa");
    vars.misc.aaX     = cfgget_i("Misc", "aaX");
    //vars.aimbot.backtrack      = cfgget_i("Aimbot", "Backtrack");
    vars.aimbot.pointscale     = cfgget_i("Aimbot", "Pointscale");
    vars.aimbot.bodyscale     = cfgget_i("Aimbot", "Body Scale");
    
    vars.aimbot.baim_high_inaccuracy     = cfgget_b("Aimbot", "Baim high innacuracy");
    vars.aimbot.bodyaim_health     = cfgget_f("Aimbot", "Baim health");
    vars.aimbot.baim_in_air     = cfgget_b("Aimbot", "Baim in air");
    vars.aimbot.baim_slow_walk     = cfgget_b("Aimbot", "Baim slow walk");
    
    vars.misc.type     = cfgget_i("Misc", "aaY");
    vars.misc.typeFake     = cfgget_i("Misc", "FaaY");
    vars.misc.MaaY     = cfgget_i("Misc", "MaaY");
    vars.visuals.nosmoke     = cfgget_b("Misc", "No Smoke");
    vars.misc.noduckcooldown     = cfgget_b("Misc", "No Duck");
    
    vars.misc.thirdpersonkeybindez     = cfgget_b("Misc", "TPKEY");
    vars.misc.tpkeybind     = cfgget_i("Misc", "TPKEYBIND");
    
    vars.misc.fakewalkkey     = cfgget_b("Misc", "Fakewalkkey");
    vars.misc.fakewalkkeybind     = cfgget_i("Misc", "Fakewalkkeybind");
    
    vars.misc.triggerbotkey     = cfgget_b("Misc", "Triggerbotkey");
    vars.misc.triggerbotkeybind     = cfgget_i("Misc", "Triggerbotkeybind");
    
    vars.misc.autoblockkey     = cfgget_b("Misc", "Autoblockkey");
    vars.misc.autoblockkeybind     = cfgget_i("Misc", "Autoblockkeybind");
    
    vars.aimbot.fakewalk     = cfgget_b("Misc", "Fake Walk");
    vars.aimbot.fakewalktype     = cfgget_i("Misc", "FakeWalkT");
    vars.aimbot.backtrack = cfgget_b("Aimbot", "Backtrack");
    vars.aimbot.accuracyhithcance = cfgget_i("Aimbot", "ACHC");
    vars.aimbot.hitscantype = cfgget_i("Aimbot", "HT");
    vars.misc.pitchenabled = cfgget_b("Aimbot", "Pitch");
    vars.aimbot.hitchance = cfgget_b("Aimbot", "Hitchance");
    vars.aimbot.jitter = cfgget_i("Aimbot", "Jitter");
    
    // Left Visuals
    vars.visuals.enabled    = cfgget_b("Visuals", "Enabled");
    vars.visuals.enemyonly  = cfgget_b("Visuals", "Enemy Only");
    vars.visuals.visonly       = cfgget_b("Visuals", "Vis Only");
    vars.visuals.box   = cfgget_b("Visuals", "Box");
    vars.visuals.name       = cfgget_b("Visuals", "Name ESP");
    vars.visuals.health       = cfgget_b("Visuals", "Health");
    vars.visuals.armour     = cfgget_b("Visuals", "Armour");
    vars.visuals.healthtext    = cfgget_b("Visuals", "Health Text");
    vars.visuals.skeleton       = cfgget_b("Visuals", "Skeleton");
    vars.visuals.snapline       = cfgget_b("Visuals", "Snap Line");
    vars.visuals.bombtimer       = cfgget_b("Visuals", "Bomb Timer");
    vars.visuals.scoped       = cfgget_b("Visuals", "Scoped");
    vars.visuals.rcrosshair       = cfgget_b("Visuals", "RC");
    vars.visuals.scrosshair       = cfgget_b("Visuals", "SC");
    vars.visuals.active       = cfgget_b("Visuals", "Weapon");
    vars.visuals.grenade       = cfgget_b("Visuals", "Grenade");
    vars.aimbot.autostop       = cfgget_b("Aimbot", "Autostop");
     vars.aimbot.autoslow       = cfgget_b("Aimbot", "Autoslow");
    //vars.mi       = cfgget_b("Visuals", "SC");
    
    
    
    // Middle Visuals
    vars.visuals.skinc = cfgget_b("Visuals", "Skin Changer");
    vars.visuals.defusing       = cfgget_b("Visuals", "Defusing");
    vars.visuals.rescuing       = cfgget_b("Visuals", "Rescuing");
    vars.visuals.antiaim_indicator = cfgget_b("Visuals", "AA Indicator");
    vars.visuals.indicatorAA_types = cfgget_i("Visuals", "AA Indicator Type");
    vars.visuals.antiaiminfos = cfgget_b("Visuals", "AA Info");
    vars.visuals.direction = cfgget_b("Visuals", "Direction");
    //vars.visuals.grenade = cfgget_b("Visuals", "Grenade ESP");
    
    // Right Visual
    vars.visuals.chams= cfgget_b("Visuals", "Player Chams");
    
    vars.misc.flagchams= cfgget_b("Visuals", "Fake Lag Chams");
    vars.visuals.fakelagtype       = cfgget_i("Visuals", "Fake Lag Type");
    vars.visuals.fakelagchams_alpha       = cfgget_i("Visuals", "Fake Alpha");
    
    vars.visuals.localchams= cfgget_b("Visuals", "Local Chams");
    vars.visuals.localchamstype       = cfgget_i("Visuals", "Local Type");
    vars.visuals.localchams_alpha       = cfgget_i("Visuals", "Local Alpha");
    
    vars.visuals.aaline= cfgget_b("Visuals", "AA Line");
    vars.visuals.anglelinenames= cfgget_b("Visuals", "AA Line Names");
    
    vars.visuals.handchams       = cfgget_b("Visuals", "Hand Chams");
    vars.visuals.weaponchams       = cfgget_b("Visuals", "Weapon Chams");
    
    vars.misc.desynchams    = cfgget_b("Visuals", "Desync Chams");
    vars.misc.lbybreaker =  cfgget_b("Misc", "LBY Breaker");
    
    vars.misc.lbybreakermanual =  cfgget_b("Misc", "LBY Breaker Manual");
    vars.misc.lbybreakeroffset = cfgget_f("Misc", "LBY Breaker Offset");
    
    vars.misc.manualaa =  cfgget_b("Misc", "Manual AA");
    vars.misc.spectatorfirstperson =  cfgget_b("Misc", "TPSpec");
    vars.misc.fakeduck =  cfgget_b("Misc", "Fake Duck");
    
    vars.visuals.playerchams_alpha       = cfgget_i("Visuals", "PCA");
    vars.visuals.handchams_alpha       = cfgget_i("Visuals", "HCA");
    vars.visuals.weaponchams_alpha       = cfgget_i("Visuals", "WCA");
    
    vars.visuals.playersType = cfgget_i("Visuals", "Players Type");
    vars.visuals.handsType       = cfgget_i("Visuals", "Hand Type");
    vars.visuals.weaponType       = cfgget_i("Visuals", "Weapon Type");
    vars.visuals.weapons       = cfgget_b("Visuals", "Dropped Weapons");
    
    vars.visuals.hitmarker       = cfgget_b("Visuals", "Hitmarkers");
    vars.visuals.hitmarkersounds       = cfgget_b("Visuals", "Hitmarkers Sounds");
    vars.visuals.hitsize       = cfgget_i("Visuals", "Hitmarker Size");
    vars.visuals.hitduration       = cfgget_i("Visuals", "Hitmarker Duration");
    vars.visuals.hitinnergap       = cfgget_i("Visuals", "Hitmarker Inner Gap");
    vars.visuals.allieshit       = cfgget_b("Visuals", "Hitmarkers Allies");
    vars.visuals.enemyhit       = cfgget_b("Visuals", "Hitmarkers Enemies");
    
    vars.misc.showenemieslog       = cfgget_b("Visuals", "Enemy Log");
    vars.misc.showallieslog       = cfgget_b("Visuals", "Allies Log");
    vars.misc.loggerduration = cfgget_f("Visuals", "Log Duration");
     vars.misc.loggerlines = cfgget_f("Visuals", "Log Lines");
    vars.misc.showlocalplayer       = cfgget_b("Visuals", "Local Log");
    
    // Misc Left
    vars.misc.enabled = cfgget_b("Misc", "Enabled");
    vars.misc.antiuntrust = cfgget_b("Misc", "Antiunt");
    vars.misc.bhop          = cfgget_b("Misc", "Bhop");
    vars.misc.autostrafe          = cfgget_b("Misc", "Auto Strafe");
    vars.misc.cstrafe          = cfgget_b("Misc", "cStrafe");
    vars.misc.fov           = cfgget_i("Misc", "FOVf");
    vars.misc.tpoffset           = cfgget_i("Misc", "TPOff");
    vars.misc.fovt = cfgget_b("Misc", "FOV");

    vars.misc.norecoil      = cfgget_b("Misc", "No Recoil");
    vars.misc.novisual= cfgget_b("Misc", "No Visual Recoil");
    vars.misc.spammer = cfgget_b("Misc", "Chat Spam");
    vars.misc.moonwalk = cfgget_b("Misc", "Moonwalk");
    vars.misc.clantag = cfgget_b("Misc", "Clantag");
    
    vars.misc.spreadcrosshair = cfgget_b("Misc", "Spread");
    
    
    //Misc Right
    vars.misc.noflash       = cfgget_b("Misc", "No Flash Enable");
    vars.misc.flashalpha    = cfgget_i("Misc", "Flash Alpha");
    vars.misc.noscope = cfgget_b("Misc", "No Scope");
    vars.misc.fakelag = cfgget_b("Misc", "Fake Lag");
    vars.misc.fakelagfactor = cfgget_i("Misc", "FakeLagf");
    vars.misc.adaptive = cfgget_b("Misc", "Adaptive");
    // vars.misc.nightmode = cfgget_b("Misc", "Night Mode");
    vars.misc.asuswalls = cfgget_b("Misc", "Asus Walls");
    
    vars.misc.worldpaint = cfgget_b("Misc", "World Paint");
    vars.misc.antiscreenshot = cfgget_b("Misc", "Anti Screenshot");
    vars.misc.showspectators = cfgget_b("Misc", "Show Spectators");
    vars.misc.attargets = cfgget_b("Misc", "At Target");
    vars.misc.delta = cfgget_i("Aimbot", "Delta");
    vars.misc.Yoffset = cfgget_i("Aimbot", "Y Offset");
    vars.misc.turbojizzer = cfgget_b("Aimbot", "Turbo");
    vars.misc.backjizzer = cfgget_b("Aimbot", "Back");
    vars.misc.lby_spin = cfgget_b("Aimbot", "LBY Spin");
    vars.misc.tank = cfgget_b("Aimbot", "Tank");
    vars.misc.radar = cfgget_b("Aimbot", "Radar");
    //vars.aimbot.autocock = cfgget_b("Aimbot", "Auto Cock");
    vars.aimbot.baimhp = cfgget_b("Aimbot", "Baim");
    vars.aimbot.baimxhp = cfgget_i("Aimbot", "BaimxHP");
    vars.misc.asusalpha = cfgget_f("Misc", "ASUSA");
    vars.visuals.bullett = cfgget_b("Misc", "Bullet");
    vars.misc.desyncenabled = cfgget_b("Aimbot", "YawD");

    
    vars.misc.snipercrosshair = cfgget_b("Misc", "Sniper");
    vars.misc.nightmode = cfgget_b("Misc", "Nightmode");
    vars.misc.fullbright = cfgget_b("Misc", "Fullbright");
    vars.misc.nadetraj = cfgget_b("Misc", "NadeTrajectory");
    vars.misc.grenadepred = cfgget_b("Misc", "NadePred");
    
    vars.misc.hvhviewmodel = cfgget_b("Misc", "hvhviewmodel");
    vars.misc.logshots = cfgget_b("Misc", "Log Shots");
    vars.misc.viewmodelx = cfgget_i("Misc", "hvhviewmodelx");
    vars.misc.viewmodely = cfgget_i("Misc", "hvhviewmodely");
    vars.misc.viewmodelz = cfgget_i("Misc", "hvhviewmodelz");
    vars.misc.viewmodelfov = cfgget_i("Misc", "hvhviewmodelfov");
    //vars.misc.freestanding = cfgget_b("Aimbot", "Freestanding");
    
    vars.aimbot.autoaccept = cfgget_b("Misc", "Autoblock");
    vars.aimbot.autoknife = cfgget_b("Misc", "Autoknife");
    
    vars.aimbot.autodefuse = cfgget_b("Misc", "Autodefuse");
    vars.aimbot.defusesilent = cfgget_b("Misc", "Silentdefuse");
    
    vars.visuals.CTcham_red           = cfgget_f("Colors", "CT Visible Chams.R");
       vars.visuals.CTcham_green         = cfgget_f("Colors", "CT Visible Chams.G");
       vars.visuals.CTcham_blue          = cfgget_f("Colors", "CT Visible Chams.B");
       
       vars.visuals.CTchamhid_red        = cfgget_f("Colors", "CT Hidden Chams.R");
       vars.visuals.CTchamhid_green      = cfgget_f("Colors", "CT Hidden Chams.G");
       vars.visuals.CTchamhid_blue       = cfgget_f("Colors", "CT Hidden Chams.B");
       
       vars.visuals.Tcham_red           = cfgget_f("Colors", "T Visible Chams.R");
       vars.visuals.Tcham_green         = cfgget_f("Colors", "T Visible Chams.G");
       vars.visuals.Tcham_blue          = cfgget_f("Colors", "T Visible Chams.B");
       
       vars.visuals.Tchamhid_red        = cfgget_f("Colors", "T Hidden Chams.R");
       vars.visuals.Tchamhid_green      = cfgget_f("Colors", "T Hidden Chams.G");
       vars.visuals.Tchamhid_blue       = cfgget_f("Colors", "T Hidden Chams.B");
       
     
       vars.visuals.arm_red           = cfgget_f("Colors", "Arm.R");
       vars.visuals.arm_green         = cfgget_f("Colors", "Arm.G");
       vars.visuals.arm_blue          = cfgget_f("Colors", "Arm.B");
       
       vars.visuals.weapon_red        = cfgget_f("Colors", "Weapon.R");
       vars.visuals.weapon_green      = cfgget_f("Colors", "Weapon.G");
       vars.visuals.weapon_blue       = cfgget_f("Colors", "Weapon.B");
    //Colours
    /*vars.colors.pchamr      = cfgget_f("Colours", "pChamr");
     vars.colors.pchamg      = cfgget_f("Colours", "pChamg");
     vars.colors.pchamb      = cfgget_f("Colours", "pChamb");
     
     
     vars.colors.boxr        = cfgget_f("Colours", "boxr");
     vars.colors.boxg        = cfgget_f("Colours", "boxg");
     vars.colors.boxb        = cfgget_f("Colours", "boxb");
     
     vars.colors.pignr       = cfgget_f("Colours", "cignr");
     vars.colors.pigng       = cfgget_f("Colours", "cigng");
     vars.colors.pignb       = cfgget_f("Colours", "cignb");
     
     vars.colors.bignr       = cfgget_f("Colours", "bignr");
     vars.colors.bigng       = cfgget_f("Colours", "bigng");
     vars.colors.bignb       = cfgget_f("Colours", "bignb");
     */
    
}



void Config::SaveConfig() {
    
    
    if(!fileExist(dsk.c_str()))
        mkdir(dsk.c_str(), 0775);
    
    if(!fileExist(fdr.c_str()))
        mkdir(fdr.c_str(), 0775);
    
    
    //CSimpleIniA cfg;
    cfg.SetUnicode(true);
    
    // cfg.SetLongValue("Bindings", "Aimlock Key", GetFloatValue((int)vars.aimbot.aimKey));
    //cfg.SetLongValue("Bindings", "Trigger Key", GetFloatValue((int)vars.aimbot.triggerKey));
    
    // Left Aimbot
    cfg.SetBoolValue("Aimbot", "Enabled", GetBoolValue(vars.aimbot.enabled));
    cfg.SetBoolValue("Aimbot", "RCS", GetBoolValue(vars.aimbot.rcs));
    cfg.SetLongValue("Aimbot", "RCSf", GetIntValue(vars.aimbot.rcsf));
    cfg.SetLongValue("Aimbot", "FOV", GetIntValue(vars.aimbot.FovToPlayer));
    cfg.SetLongValue("Aimbot", "Bone", GetIntValue(vars.aimbot.hitbox));
    cfg.SetBoolValue("Aimbot", "Triggerbot", GetBoolValue(vars.aimbot.trigger));
    //cfg.SetBoolValue("Aimbot", "Auto Stop", GetBoolValue(vars.aimbot.autostop));
    cfg.SetBoolValue("Aimbot", "Silent", GetBoolValue(vars.aimbot.silent));
    cfg.SetBoolValue("Aimbot", "Auto Scope", GetBoolValue(vars.aimbot.autoscope));
    cfg.SetBoolValue("Aimbot", "Auto Shoot", GetBoolValue(vars.aimbot.autoshoot));
    cfg.SetBoolValue("Aimbot", "Auto Crouch", GetBoolValue(vars.aimbot.autocrouch));
    cfg.SetBoolValue("Aimbot", "Auto Pistol", GetBoolValue(vars.aimbot.autopistol));
    cfg.SetBoolValue("Aimbot", "Yaw Resolver", GetBoolValue(vars.aimbot.Yawresolver));
    cfg.SetBoolValue("Aimbot", "Auto Wall", GetBoolValue(vars.aimbot.autowall));
    cfg.SetBoolValue("Aimbot", "Hitscan", GetBoolValue(vars.aimbot.hitscan));
    cfg.SetLongValue("Aimbot", "Mindmg", GetIntValue(vars.aimbot.mindmg));
    cfg.SetBoolValue("Aimbot", "LBY Flip", GetBoolValue(vars.misc.antiResolverFlip));
    cfg.SetBoolValue("Aimbot", "LBY Spin", GetBoolValue(vars.misc.lby_spin));
    cfg.SetBoolValue("Aimbot", "Hitchance", GetBoolValue(vars.aimbot.hitchance));
    cfg.SetBoolValue("Aimbot", "AntiAim Enabled", GetBoolValue(vars.misc.antiaim));
    cfg.SetBoolValue("Aimbot", "Autostop", GetBoolValue(vars.aimbot.autostop));
    cfg.SetBoolValue("Aimbot", "Autoslow", GetBoolValue(vars.aimbot.autoslow));
    //cfg.SetBoolValue("Aimbot", "Auto Cock", GetBoolValue(vars.aimbot.autocock));
    
    cfg.SetBoolValue("Aimbot", "Legit Enabled", GetBoolValue(vars.aimbot.LegitEnabled));
    
    cfg.SetDoubleValue("Aimbot", "Pistol FOV", GetFloatValue(vars.aimbot.pistolFOV));
    cfg.SetBoolValue("Aimbot", "Pistol Smooth", GetBoolValue(vars.aimbot.pistolsmooth));
    cfg.SetDoubleValue("Aimbot", "Pistol Smooth FOV", GetFloatValue(vars.aimbot.pistolsmoothf));
    cfg.SetBoolValue("Aimbot", "Legit Pistol Hitscan", GetBoolValue(vars.aimbot.legitPistolHitscan));
    cfg.SetLongValue("Aimbot", "Legit Pistol Hitscan Type", GetIntValue(vars.aimbot.legitPistolHitscanType));
    
    cfg.SetDoubleValue("Aimbot", "Rifle FOV", GetFloatValue(vars.aimbot.rifleFOV));
    cfg.SetBoolValue("Aimbot", "Rifle Smooth", GetBoolValue(vars.aimbot.riflesmooth));
    cfg.SetDoubleValue("Aimbot", "Rifle Smooth FOV", GetFloatValue(vars.aimbot.riflesmoothf));
    cfg.SetBoolValue("Aimbot", "Legit Rifle Hitscan", GetBoolValue(vars.aimbot.legitRifleHitscan));
    cfg.SetLongValue("Aimbot", "Legit Rifle Hitscan Type", GetIntValue(vars.aimbot.legitRifleHitscanType));
    
    cfg.SetDoubleValue("Aimbot", "Sniper FOV", GetFloatValue(vars.aimbot.sniperFOV));
    cfg.SetBoolValue("Aimbot", "Sniper Smooth", GetBoolValue(vars.aimbot.snipersmooth));
    cfg.SetDoubleValue("Aimbot", "Sniper Smooth FOV", GetFloatValue(vars.aimbot.snipersmoothf));
    cfg.SetBoolValue("Aimbot", "Legit Sniper Hitscan", GetBoolValue(vars.aimbot.legitSniperHitscan));
    cfg.SetLongValue("Aimbot", "Legit Sniper Hitscan Type", GetIntValue(vars.aimbot.legitSniperHitscanType));
    
    cfg.SetDoubleValue("Aimbot", "Smg FOV", GetFloatValue(vars.aimbot.smgFOV));
    cfg.SetBoolValue("Aimbot", "Smg Smooth", GetBoolValue(vars.aimbot.smgsmooth));
    cfg.SetDoubleValue("Aimbot", "Smg Smooth FOV", GetFloatValue(vars.aimbot.smgsmoothf));
    cfg.SetBoolValue("Aimbot", "Legit Smg Hitscan", GetBoolValue(vars.aimbot.legitSmgHitscan));
    cfg.SetLongValue("Aimbot", "Legit Smg Hitscan Type", GetIntValue(vars.aimbot.legitSmgHitscanType));
    
    cfg.SetDoubleValue("Aimbot", "Heavy FOV", GetFloatValue(vars.aimbot.heavyFOV));
    cfg.SetBoolValue("Aimbot", "Heavy Smooth", GetBoolValue(vars.aimbot.heavysmooth));
    cfg.SetDoubleValue("Aimbot", "Heavy Smooth FOV", GetFloatValue(vars.aimbot.heavysmoothf));
    cfg.SetBoolValue("Aimbot", "Legit Heavy Hitscan", GetBoolValue(vars.aimbot.legitHeavyHitscan));
    cfg.SetLongValue("Aimbot", "Legit Heavy Hitscan Type", GetIntValue(vars.aimbot.legitHeavyHitscanType));
    
    cfg.SetBoolValue("Misc", "Fake Walk", GetBoolValue(vars.aimbot.fakewalk));
    cfg.SetLongValue("Misc", "FakeWalkT", GetIntValue(vars.aimbot.fakewalktype));
    cfg.SetBoolValue("Misc", "No Smoke", GetBoolValue(vars.visuals.nosmoke));
    cfg.SetBoolValue("Misc", "No Duck", GetBoolValue(vars.misc.noduckcooldown));
    
     cfg.SetBoolValue("Misc", "Sniper", GetBoolValue(vars.misc.snipercrosshair));
     cfg.SetBoolValue("Misc", "Nightmode", GetBoolValue(vars.misc.nightmode));
     cfg.SetBoolValue("Misc", "Fullbright", GetBoolValue(vars.misc.fullbright));
    cfg.SetBoolValue("Misc", "NadeTrajectory", GetBoolValue(vars.misc.nadetraj));
    cfg.SetBoolValue("Misc", "NadePred", GetBoolValue(vars.misc.grenadepred));
    //cfg.SetBoolValue("Aimbot", "Backtrack", GetBoolValue(vars.misc.backtrack));
    cfg.SetLongValue("Aimbot", "ACHC", GetIntValue(vars.aimbot.accuracyhithcance));
    cfg.SetLongValue("Aimbot", "HT", GetIntValue(vars.aimbot.hitscantype));
     cfg.SetLongValue("Aimbot", "Yresolve", GetIntValue(vars.aimbot.yresolve));
    
    // Visuals
    cfg.SetBoolValue("Visuals", "Enabled", GetBoolValue(vars.visuals.enabled));
    cfg.SetBoolValue("Visuals", "Box", GetBoolValue(vars.visuals.box));
    cfg.SetBoolValue("Visuals", "Name ESP", GetBoolValue(vars.visuals.name));
    cfg.SetBoolValue("Visuals", "Health", GetBoolValue(vars.visuals.health));
    cfg.SetBoolValue("Visuals", "Health text", GetBoolValue(vars.visuals.healthtext));
    cfg.SetBoolValue("Visuals", "Snap Line", GetBoolValue(vars.visuals.snapline));
    cfg.SetBoolValue("Visuals", "Hand Chams", GetBoolValue(vars.visuals.handchams));
    
    cfg.SetBoolValue("Visuals", "Weapon Chams", GetBoolValue(vars.visuals.weaponchams));
    cfg.SetBoolValue("Visuals", "Weapons", GetBoolValue(vars.visuals.weapons));
    cfg.SetBoolValue("Visuals", "Skeleton", GetBoolValue(vars.visuals.skeleton));
    cfg.SetBoolValue("Visuals", "Chams", GetBoolValue(vars.visuals.chams));
    cfg.SetBoolValue("Visuals", "Enemy Only", GetBoolValue(vars.visuals.enemyonly));
    cfg.SetBoolValue("Visuals", "Bomb Timer", GetBoolValue(vars.visuals.bombtimer));
    cfg.SetBoolValue("Visuals", "Scoped", GetBoolValue(vars.visuals.scoped));
    cfg.SetBoolValue("Visuals", "RC", GetBoolValue(vars.visuals.rcrosshair));
    cfg.SetBoolValue("Visuals", "SC", GetBoolValue(vars.visuals.scrosshair));
    cfg.SetBoolValue("Visuals", "Weapon", GetBoolValue(vars.visuals.active));
    cfg.SetBoolValue("Visuals", "Grenade", GetBoolValue(vars.visuals.grenade));
    cfg.SetBoolValue("Visuals", "Vis Only", GetBoolValue(vars.visuals.visonly));
    
    
    cfg.SetLongValue("Visuals", "Hand Type", GetIntValue(vars.visuals.handsType));
    cfg.SetLongValue("Visuals", "Players Type", GetIntValue(vars.visuals.playersType));
    cfg.SetLongValue("Visuals", "Weapon Type", GetIntValue(vars.visuals.weaponType));
    
    
    cfg.SetBoolValue("Visuals", "Player Chams", GetBoolValue(vars.visuals.chams));
    cfg.SetBoolValue("Visuals", "Fake Lag Chams", GetBoolValue(vars.misc.flagchams));
    cfg.SetBoolValue("Visuals", "Local Chams", GetBoolValue(vars.visuals.localchams));
    cfg.SetBoolValue("Visuals", "Desync Chams", GetBoolValue(vars.misc.desynchams));
    cfg.SetBoolValue("Misc", "Fake Duck", GetBoolValue(vars.misc.fakeduck));
    cfg.SetBoolValue("Misc", "TPSpec", GetBoolValue(vars.misc.spectatorfirstperson));
    cfg.SetBoolValue("Misc", "Manual AA", GetBoolValue(vars.misc.spectatorfirstperson));
    cfg.SetBoolValue("Misc", "LBY Breaker", GetBoolValue(vars.misc.lbybreaker));
    cfg.SetBoolValue("Misc", "LBY Breaker Manual", GetBoolValue(vars.misc.lbybreakermanual));
    cfg.SetDoubleValue("Misc", "LBY Breaker Offset", GetFloatValue(vars.misc.lbybreakeroffset));
    cfg.SetBoolValue("Visuals", "AA Line", GetBoolValue(vars.visuals.aaline));
    cfg.SetBoolValue("Visuals", "AA Line Names", GetBoolValue(vars.visuals.anglelinenames));
    cfg.SetBoolValue("Visuals", "Hand Chams", GetBoolValue(vars.visuals.handchams));
    cfg.SetBoolValue("Visuals", "Weapon Chams", GetBoolValue(vars.visuals.weaponchams));
    cfg.SetBoolValue("Visuals", "Dropped Weapons", GetBoolValue(vars.visuals.weapons));
    cfg.SetBoolValue("Visuals", "Defusing", GetBoolValue(vars.visuals.defusing));
    
    cfg.SetLongValue("Visuals", "PCA", GetIntValue(vars.visuals.playerchams_alpha));
    cfg.SetLongValue("Visuals", "HCA", GetIntValue(vars.visuals.handchams_alpha));
    cfg.SetLongValue("Visuals", "WCA", GetIntValue(vars.visuals.weaponchams_alpha));
    cfg.SetLongValue("Visuals", "Fake Alpha", GetIntValue(vars.visuals.fakelagchams_alpha));
    cfg.SetLongValue("Visuals", "Fake Lag Type", GetIntValue(vars.visuals.fakelagtype));
    cfg.SetLongValue("Visuals", "Local Alpha", GetIntValue(vars.visuals.localchams_alpha));
    cfg.SetLongValue("Visuals", "Local Type", GetIntValue(vars.visuals.localchamstype));
    
    
    cfg.SetBoolValue("Visuals", "Enemy Log", GetBoolValue(vars.misc.showenemieslog));
    cfg.SetBoolValue("Visuals", "Allies Log", GetBoolValue(vars.misc.showallieslog));
    cfg.SetBoolValue("Visuals", "Local Log", GetBoolValue(vars.misc.showlocalplayer));
    cfg.SetDoubleValue("Visuals", "Log Lines", GetFloatValue(vars.misc.loggerlines));
    cfg.SetDoubleValue("Visuals", "Log Duration", GetFloatValue(vars.misc.loggerduration));
    
    //cfg.SetBoolValue("Visuals", "Grenade ESP", GetBoolValue(vars.visuals.grenade));
    cfg.SetBoolValue("Visuals", "Direction", GetBoolValue(vars.visuals.direction));
    cfg.SetBoolValue("Visuals", "AA Info", GetBoolValue(vars.visuals.antiaiminfos));
    cfg.SetBoolValue("Visuals", "AA Indicator", GetBoolValue(vars.visuals.antiaim_indicator));
    cfg.SetLongValue("Visuals", "AA Indicator Type", GetIntValue(vars.visuals.indicatorAA_types));
    
    cfg.SetBoolValue("Visuals", "Hitmarkers", GetBoolValue(vars.visuals.hitmarker));
    cfg.SetBoolValue("Visuals", "Hitmarkers Sounds", GetBoolValue(vars.visuals.hitmarkersounds));
    cfg.SetLongValue("Visuals", "Hitmarker Size", GetIntValue(vars.visuals.hitsize));
    cfg.SetLongValue("Visuals", "Hitmarker Duration", GetIntValue(vars.visuals.hitduration));
    cfg.SetLongValue("Visuals", "Hitmarker Inner Gap", GetIntValue(vars.visuals.hitinnergap));
    cfg.SetBoolValue("Visuals", "Hitmarkers Allies", GetBoolValue(vars.visuals.allieshit));
    cfg.SetBoolValue("Visuals", "Hitmarkers Enemies", GetBoolValue(vars.visuals.enemyhit));
    // Misc
    cfg.SetBoolValue("Misc", "Enabled", GetBoolValue(vars.misc.enabled));
    cfg.SetBoolValue("Misc", "No Recoil", GetBoolValue(vars.misc.norecoil));
    cfg.SetBoolValue("Misc", "No Visual Recoil", GetBoolValue(vars.misc.novisual));
    cfg.SetBoolValue("Misc", "Bhop", GetBoolValue(vars.misc.bhop));
    cfg.SetBoolValue("Misc", "Auto Strafe", GetBoolValue(vars.misc.autostrafe));
    cfg.SetBoolValue("Misc", "cStrafe", GetBoolValue(vars.misc.cstrafe));
    //cfg.SetBoolValue("Misc", "Airstuck", GetBoolValue(vars.misc.airstuck));
    cfg.SetBoolValue("Misc", "Show Rank", GetBoolValue(vars.misc.showrank));
    //cfg.SetBoolValue("Misc", "Asus", GetBoolValue(vars.misc.asuswalls));
    cfg.SetBoolValue("Misc", "No Flash Enable", GetBoolValue(vars.misc.noflash));
    cfg.SetLongValue("Misc", "Flash Alpha", GetIntValue(vars.misc.flashalpha));
    cfg.SetBoolValue("Misc", "Chat Spam", GetBoolValue(vars.misc.spammer));
    cfg.SetBoolValue("Misc", "Clantag", GetBoolValue(vars.misc.clantag));
    cfg.SetBoolValue("Visuals", "Skin Changer", GetBoolValue(vars.visuals.skinc));

    
    cfg.SetBoolValue("Misc", "TPKEY", GetBoolValue(vars.misc.thirdpersonkeybindez));
    cfg.SetLongValue("Misc", "TPKEYBIND", GetIntValue(vars.misc.tpkeybind));
    
    cfg.SetBoolValue("Misc", "Fakewalkkey", GetBoolValue(vars.misc.fakewalkkey));
    cfg.SetLongValue("Misc", "Fakewalkkeybind", GetIntValue(vars.misc.fakewalkkeybind));
    
    cfg.SetBoolValue("Misc", "Triggerbotkey", GetBoolValue(vars.misc.triggerbotkey));
    cfg.SetLongValue("Misc", "Triggerbotkeybind", GetIntValue(vars.misc.triggerbotkeybind));
    
    cfg.SetBoolValue("Misc", "Autoblockkey", GetBoolValue(vars.misc.autoblockkey));
    cfg.SetLongValue("Misc", "Autoblockkeybind", GetIntValue(vars.misc.autoblockkeybind));
    
    cfg.SetBoolValue("Misc", "Antiunt", GetBoolValue(vars.misc.antiuntrust));

    
    cfg.SetBoolValue("Misc", "hvhviewmodel", GetBoolValue(vars.misc.hvhviewmodel));
    cfg.SetBoolValue("Misc", "Log Shots", GetBoolValue(vars.misc.logshots));
    cfg.SetLongValue("Misc", "hvhviewmodelx", GetIntValue(vars.misc.viewmodelx));
    cfg.SetLongValue("Misc", "hvhviewmodelz", GetIntValue(vars.misc.viewmodelz));
    cfg.SetLongValue("Misc", "hvhviewmodely", GetIntValue(vars.misc.viewmodely));
    cfg.SetLongValue("Misc", "hvhviewmodelfov", GetIntValue(vars.misc.viewmodelfov));
    
    
    cfg.SetLongValue("Misc", "FOVf", GetIntValue(vars.misc.fov));
    cfg.SetLongValue("Misc", "TPOff", GetIntValue(vars.misc.tpoffset));
    cfg.SetBoolValue("Misc", "FOV", GetBoolValue(vars.misc.fovt));
    cfg.SetBoolValue("Misc", "Moonwalk", GetBoolValue(vars.misc.moonwalk));
    cfg.SetBoolValue("Misc", "Bullet", GetBoolValue(vars.visuals.bullett));
    cfg.SetBoolValue("Misc", "No Scope", GetBoolValue(vars.misc.noscope));
    cfg.SetBoolValue("Misc", "Spread", GetBoolValue(vars.misc.spreadcrosshair));
    cfg.SetBoolValue("Misc", "Fake Lag", GetBoolValue(vars.misc.fakelag));
    cfg.SetLongValue("Misc", "FakeLagf", GetIntValue(vars.misc.fakelagfactor));
    cfg.SetBoolValue("Misc", "Adaptive", GetBoolValue(vars.misc.adaptive));
    cfg.SetBoolValue("Misc", "Autoknife", GetBoolValue(vars.aimbot.autoknife));
    cfg.SetBoolValue("Misc", "Autoblock", GetBoolValue(vars.aimbot.autoaccept));
    cfg.SetBoolValue("Misc", "Autodefuse", GetBoolValue(vars.aimbot.autodefuse));
    cfg.SetBoolValue("Misc", "Silentdefuse", GetBoolValue(vars.aimbot.defusesilent));
    // cfg.SetBoolValue("Misc", "Night Mode", GetBoolValue(vars.misc.nightmode));
    cfg.SetBoolValue("Misc", "Asus Walls", GetBoolValue(vars.misc.asuswalls));
    cfg.SetBoolValue("Misc", "World Paint", GetBoolValue(vars.misc.worldpaint));
    cfg.SetBoolValue("Misc", "Anti Screenshot", GetBoolValue(vars.misc.antiscreenshot));
    cfg.SetBoolValue("Misc", "Show Spectators", GetBoolValue(vars.misc.showspectators));
    cfg.SetLongValue("Aimbot", "Delta", GetIntValue(vars.misc.delta));
    cfg.SetLongValue("Aimbot", "Jitter", GetIntValue(vars.aimbot.jitter));
    cfg.SetLongValue("Aimbot", "Y Offset", GetIntValue(vars.misc.Yoffset));
    cfg.SetBoolValue("Aimbot", "Turbo", GetBoolValue(vars.misc.turbojizzer));
    cfg.SetBoolValue("Aimbot", "Back", GetBoolValue(vars.misc.backjizzer));
    cfg.SetBoolValue("Aimbot", "LBY", GetBoolValue(vars.misc.turbojizzer));
    cfg.SetBoolValue("Aimbot", "Tank", GetBoolValue(vars.misc.tank));
     cfg.SetBoolValue("Aimbot", "YawD", GetBoolValue(vars.misc.desyncenabled));
    cfg.SetBoolValue("Aimbot", "Pitch", GetBoolValue(vars.misc.pitchenabled));
    cfg.SetBoolValue("Aimbot", "Backtrack", GetBoolValue(vars.aimbot.backtrack));
    cfg.SetBoolValue("Aimbot", "Radar", GetBoolValue(vars.misc.radar));
    cfg.SetBoolValue("Aimbot", "Baim", GetBoolValue(vars.aimbot.baimhp));
    cfg.SetLongValue("Aimbot", "Pointscale", GetIntValue(vars.aimbot.pointscale));
    cfg.SetLongValue("Aimbot", "Bodyscale", GetIntValue(vars.aimbot.bodyscale));
    cfg.SetLongValue("Aimbot", "BaimxHP", GetIntValue(vars.aimbot.baimxhp));
    cfg.SetBoolValue("Aimbot", "Baim in air", GetBoolValue(vars.aimbot.baim_in_air));
    cfg.SetBoolValue("Aimbot", "Baim slow walk", GetBoolValue(vars.aimbot.baim_slow_walk));
    cfg.SetBoolValue("Aimbot", "Baim high innaccuracy", GetBoolValue(vars.aimbot.baim_high_inaccuracy));
    cfg.SetDoubleValue("Aimbot", "Baim health", GetFloatValue(vars.aimbot.bodyaim_health));
    cfg.SetDoubleValue("Misc", "ASUSA", GetFloatValue(vars.misc.asusalpha));
    
    
    
     cfg.SetDoubleValue("Colors", "CT Visible Chams.R", GetFloatValue(vars.visuals.CTcham_red));
       cfg.SetDoubleValue("Colors", "CT Visible Chams.G", GetFloatValue(vars.visuals.CTcham_green));
       cfg.SetDoubleValue("Colors", "CT Visible Chams.B", GetFloatValue(vars.visuals.CTcham_blue));
       
       cfg.SetDoubleValue("Colors", "CT Hidden Chams.R", GetFloatValue(vars.visuals.CTchamhid_red));
       cfg.SetDoubleValue("Colors", "CT Hidden Chams.G", GetFloatValue(vars.visuals.CTchamhid_blue));
       cfg.SetDoubleValue("Colors", "CT Hidden Chams.B", GetFloatValue(vars.visuals.CTchamhid_green));
       
       cfg.SetDoubleValue("Colors", "T Visible Chams.R", GetFloatValue(vars.visuals.Tcham_red));
       cfg.SetDoubleValue("Colors", "T Visible Chams.G", GetFloatValue(vars.visuals.CTcham_green));
       cfg.SetDoubleValue("Colors", "T Visible Chams.B", GetFloatValue(vars.visuals.CTcham_blue));
       
       cfg.SetDoubleValue("Colors", "T Hidden Chams.R", GetFloatValue(vars.visuals.Tchamhid_red));
       cfg.SetDoubleValue("Colors", "T Hidden Chams.G", GetFloatValue(vars.visuals.Tchamhid_blue));
       cfg.SetDoubleValue("Colors", "T Hidden Chams.B", GetFloatValue(vars.visuals.Tchamhid_green));
       
       cfg.SetDoubleValue("Colors", "Arm.R", GetFloatValue(vars.visuals.arm_red));
       cfg.SetDoubleValue("Colors", "Arm.G", GetFloatValue(vars.visuals.arm_green));
       cfg.SetDoubleValue("Colors", "Arm.B", GetFloatValue(vars.visuals.arm_blue));
       
       cfg.SetDoubleValue("Colors", "Weapon.R", GetFloatValue(vars.visuals.weapon_red));
       cfg.SetDoubleValue("Colors", "Weapon.G", GetFloatValue(vars.visuals.weapon_green));
       cfg.SetDoubleValue("Colors", "Weapon.B", GetFloatValue(vars.visuals.weapon_blue));
    
    // AA
    cfg.SetBoolValue("Aimbot", "Show Real Angles", GetBoolValue(vars.misc.thirdpersonmode));
    cfg.SetBoolValue("Aimbot", "Thirdperson", GetBoolValue(vars.misc.thirdperson));
    cfg.SetBoolValue("Misc", "aa", GetBoolValue(vars.misc.antiaim));
    cfg.SetBoolValue("Misc", "At Target", GetBoolValue(vars.misc.attargets));
    cfg.SetBoolValue("Aimbot", "Fake aa", GetBoolValue(vars.misc.fakeaa));
    
    cfg.SetLongValue("Misc", "aaX", GetIntValue(vars.misc.aaX));
    cfg.SetLongValue("Misc", "aaY", GetIntValue(vars.misc.type));
    cfg.SetLongValue("Misc", "FaaY", GetIntValue(vars.misc.typeFake));
    cfg.SetLongValue("Misc", "MaaY", GetIntValue(vars.misc.aaY));
    
    
    
    
    
    
    cfg.SaveFile(ConfigName);
    
}

void Config::InitSkins() {
    
    if(fileExist(skins.c_str()))
        return;
    
    skins_cfg.SetUnicode(true);
    
    skins_cfg.SetDoubleValue("weapon_deagle", "id", GetFloatValue(skin.deagle));
    skins_cfg.SetDoubleValue("weapon_deagle", "seed", GetFloatValue(skin.deagle_Seed));
    skins_cfg.SetDoubleValue("weapon_deagle", "itemdef", GetFloatValue(1));
    
    skins_cfg.SetDoubleValue("weapon_elite", "id", GetFloatValue(skin.dual));
    skins_cfg.SetDoubleValue("weapon_elite", "seed", GetFloatValue(skin.dual_Seed));
    skins_cfg.SetDoubleValue("weapon_elite", "itemdef", GetFloatValue(2));
    
    skins_cfg.SetDoubleValue("weapon_fiveseven", "id", GetFloatValue(skin.five7));
    skins_cfg.SetDoubleValue("weapon_fiveseven", "seed", GetFloatValue(skin.five7_Seed));
    skins_cfg.SetDoubleValue("weapon_fiveseven", "itemdef", GetFloatValue(3));
    
    skins_cfg.SetDoubleValue("weapon_glock", "id", GetFloatValue(skin.glock));
    skins_cfg.SetDoubleValue("weapon_glock", "seed", GetFloatValue(skin.glock_Seed));
    skins_cfg.SetDoubleValue("weapon_glock", "itemdef", GetFloatValue(4));
    
    skins_cfg.SetDoubleValue("weapon_ak47", "id", GetFloatValue(skin.ak));
    skins_cfg.SetDoubleValue("weapon_ak47", "seed", GetFloatValue(skin.ak_Seed));
    skins_cfg.SetDoubleValue("weapon_ak47", "itemdef", GetFloatValue(7));
    
    skins_cfg.SetDoubleValue("weapon_aug", "id", GetFloatValue(skin.aug));
    skins_cfg.SetDoubleValue("weapon_aug", "seed", GetFloatValue(skin.aug_Seed));
    skins_cfg.SetDoubleValue("weapon_aug", "itemdef", GetFloatValue(8));
    
    skins_cfg.SetDoubleValue("weapon_awp", "id", GetFloatValue(skin.awp));
    skins_cfg.SetDoubleValue("weapon_awp", "seed", GetFloatValue(skin.awp_Seed));
    skins_cfg.SetDoubleValue("weapon_awp", "itemdef", GetFloatValue(9));
    
    skins_cfg.SetDoubleValue("weapon_famas", "id", GetFloatValue(skin.famas));
    skins_cfg.SetDoubleValue("weapon_famas", "seed", GetFloatValue(skin.famas_Seed));
    skins_cfg.SetDoubleValue("weapon_famas", "itemdef", GetFloatValue(10));
    
    skins_cfg.SetDoubleValue("weapon_g3sg1", "id", GetFloatValue(skin.g3));
    skins_cfg.SetDoubleValue("weapon_g3sg1", "seed", GetFloatValue(skin.g3_Seed));
    skins_cfg.SetDoubleValue("weapon_g3sg1", "itemdef", GetFloatValue(11));
    
    skins_cfg.SetDoubleValue("weapon_galilar", "id", GetFloatValue(skin.galil));
    skins_cfg.SetDoubleValue("weapon_galilar", "seed", GetFloatValue(skin.galil_Seed));
    skins_cfg.SetDoubleValue("weapon_galilar", "itemdef", GetFloatValue(13));
    
    skins_cfg.SetDoubleValue("weapon_m249", "id", GetFloatValue(skin.m249));
    skins_cfg.SetDoubleValue("weapon_m249", "seed", GetFloatValue(skin.m249_Seed));
    skins_cfg.SetDoubleValue("weapon_m249", "itemdef", GetFloatValue(14));
    
    skins_cfg.SetDoubleValue("weapon_m4a4", "id", GetFloatValue(skin.a4));
    skins_cfg.SetDoubleValue("weapon_m4a4", "seed", GetFloatValue(skin.a4_Seed));
    skins_cfg.SetDoubleValue("weapon_m4a4", "itemdef", GetFloatValue(16));
    
    skins_cfg.SetDoubleValue("weapon_mac10", "id", GetFloatValue(skin.mac10));
    skins_cfg.SetDoubleValue("weapon_mac10", "seed", GetFloatValue(skin.mac10_Seed));
    skins_cfg.SetDoubleValue("weapon_mac10", "itemdef", GetFloatValue(17));
    
    skins_cfg.SetDoubleValue("weapon_p90", "id", GetFloatValue(skin.p90));
    skins_cfg.SetDoubleValue("weapon_p90", "seed", GetFloatValue(skin.p90_Seed));
    skins_cfg.SetDoubleValue("weapon_p90", "itemdef", GetFloatValue(19));
    
    skins_cfg.SetDoubleValue("weapon_ump45", "id", GetFloatValue(skin.ump));
    skins_cfg.SetDoubleValue("weapon_ump45", "seed", GetFloatValue(skin.ump_Seed));
    skins_cfg.SetDoubleValue("weapon_ump45", "itemdef", GetFloatValue(24));
    
    skins_cfg.SetDoubleValue("weapon_xm1014", "id", GetFloatValue(skin.xm));
    skins_cfg.SetDoubleValue("weapon_xm1014", "seed", GetFloatValue(skin.xm_Seed));
    skins_cfg.SetDoubleValue("weapon_xm1014", "itemdef", GetFloatValue(25));
    
    skins_cfg.SetDoubleValue("weapon_bizon", "id", GetFloatValue(skin.bizon));
    skins_cfg.SetDoubleValue("weapon_bizon", "seed", GetFloatValue(skin.bizon_Seed));
    skins_cfg.SetDoubleValue("weapon_bizon", "itemdef", GetFloatValue(26));
    
    skins_cfg.SetDoubleValue("weapon_mag7", "id", GetFloatValue(skin.mag7));
    skins_cfg.SetDoubleValue("weapon_mag7", "seed", GetFloatValue(skin.mag7_Seed));
    skins_cfg.SetDoubleValue("weapon_mag7", "itemdef", GetFloatValue(27));
    
    skins_cfg.SetDoubleValue("weapon_negev", "id", GetFloatValue(skin.negev));
    skins_cfg.SetDoubleValue("weapon_negev", "seed", GetFloatValue(skin.negev_Seed));
    skins_cfg.SetDoubleValue("weapon_negev", "itemdef", GetFloatValue(28));
    
    skins_cfg.SetDoubleValue("weapon_sawedoff", "id", GetFloatValue(skin.sawed));
    skins_cfg.SetDoubleValue("weapon_sawedoff", "seed", GetFloatValue(skin.sawed_Seed));
    skins_cfg.SetDoubleValue("weapon_sawedoff", "itemdef", GetFloatValue(29));
    
    skins_cfg.SetDoubleValue("weapon_tec9", "id", GetFloatValue(skin.tec9));
    skins_cfg.SetDoubleValue("weapon_tec9", "seed", GetFloatValue(skin.tec9_Seed));
    skins_cfg.SetDoubleValue("weapon_tec9", "itemdef", GetFloatValue(30));
    
    skins_cfg.SetDoubleValue("weapon_hkp2000", "id", GetFloatValue(skin.p2000));
    skins_cfg.SetDoubleValue("weapon_hkp2000", "seed", GetFloatValue(skin.p2000_Seed));
    skins_cfg.SetDoubleValue("weapon_hkp2000", "itemdef", GetFloatValue(32));
    
    skins_cfg.SetDoubleValue("weapon_mp7", "id", GetFloatValue(skin.mp7));
    skins_cfg.SetDoubleValue("weapon_mp7", "seed", GetFloatValue(skin.mp7_Seed));
    skins_cfg.SetDoubleValue("weapon_mp7", "itemdef", GetFloatValue(33));
    
    skins_cfg.SetDoubleValue("weapon_mp9", "id", GetFloatValue(skin.mp9));
    skins_cfg.SetDoubleValue("weapon_mp9", "seed", GetFloatValue(skin.mp9_Seed));
    skins_cfg.SetDoubleValue("weapon_mp9", "itemdef", GetFloatValue(34));
    
    skins_cfg.SetDoubleValue("weapon_nova", "id", GetFloatValue(skin.nova));
    skins_cfg.SetDoubleValue("weapon_nova", "seed", GetFloatValue(skin.nova_Seed));
    skins_cfg.SetDoubleValue("weapon_nova", "itemdef", GetFloatValue(35));
    
    skins_cfg.SetDoubleValue("weapon_p250", "id", GetFloatValue(skin.p250));
    skins_cfg.SetDoubleValue("weapon_p250", "seed", GetFloatValue(skin.p250_Seed));
    skins_cfg.SetDoubleValue("weapon_p250", "itemdef", GetFloatValue(36));
    
    skins_cfg.SetDoubleValue("weapon_scar20", "id", GetFloatValue(skin.scar));
    skins_cfg.SetDoubleValue("weapon_scar20", "seed", GetFloatValue(skin.scar_Seed));
    skins_cfg.SetDoubleValue("weapon_scar20", "itemdef", GetFloatValue(38));
    
    skins_cfg.SetDoubleValue("weapon_sg556", "id", GetFloatValue(skin.sg));
    skins_cfg.SetDoubleValue("weapon_sg556", "seed", GetFloatValue(skin.sg_Seed));
    skins_cfg.SetDoubleValue("weapon_sg556", "itemdef", GetFloatValue(39));
    
    skins_cfg.SetDoubleValue("weapon_ssg08", "id", GetFloatValue(skin.scout));
    skins_cfg.SetDoubleValue("weapon_ssg08", "seed", GetFloatValue(skin.scout_Seed));
    skins_cfg.SetDoubleValue("weapon_ssg08", "itemdef", GetFloatValue(40));
    
    skins_cfg.SetDoubleValue("weapon_knife", "id", GetFloatValue(skin.CTknifeID));
    skins_cfg.SetDoubleValue("weapon_knife", "seed", GetFloatValue(skin.CTknfieSeed));
    skins_cfg.SetDoubleValue("weapon_knife", "itemdef", GetFloatValue(skin.knifeCT));
    
    skins_cfg.SetDoubleValue("weapon_knife_t", "id", GetFloatValue(skin.TknifeID));
    skins_cfg.SetDoubleValue("weapon_knife_t", "seed", GetFloatValue(skin.TknifeSeed));
    skins_cfg.SetDoubleValue("weapon_knife_t", "itemdef", GetFloatValue(skin.knifeT));
    
    skins_cfg.SetDoubleValue("weapon_m4a1_silencer", "id", GetFloatValue(skin.a1));
    skins_cfg.SetDoubleValue("weapon_m4a1_silencer", "seed", GetFloatValue(skin.a1_Seed));
    skins_cfg.SetDoubleValue("weapon_m4a1_silencer", "itemdef", GetFloatValue(60));
    
    skins_cfg.SetDoubleValue("weapon_usp_silencer", "id", GetFloatValue(skin.usp));
    skins_cfg.SetDoubleValue("weapon_usp_silencer", "seed", GetFloatValue(skin.usp_Seed));
    skins_cfg.SetDoubleValue("weapon_usp_silencer", "itemdef", GetFloatValue(61));
    
    skins_cfg.SetDoubleValue("weapon_cz75a", "id", GetFloatValue(skin.cz));
    skins_cfg.SetDoubleValue("weapon_cz75a", "seed", GetFloatValue(skin.cz_Seed));
    skins_cfg.SetDoubleValue("weapon_cz75a", "itemdef", GetFloatValue(63));
    
    skins_cfg.SetDoubleValue("weapon_revolver", "id", GetFloatValue(skin.r8));
    skins_cfg.SetDoubleValue("weapon_revolver", "seed", GetFloatValue(skin.r8_Seed));
    skins_cfg.SetDoubleValue("weapon_revolver", "itemdef", GetFloatValue(64));
    
    skins_cfg.SetDoubleValue("glove_t", "id", GetFloatValue(skin.TgloveID));
    skins_cfg.SetDoubleValue("glove_t", "itemdef", GetFloatValue(skin.gloveT));
    
    skins_cfg.SetDoubleValue("glove_ct", "id", GetFloatValue(skin.CTgloveID));
    skins_cfg.SetDoubleValue("glove_ct", "itemdef", GetFloatValue(skin.gloveCT));
    /*
     skins_cfg.SetDoubleValue("t glove", "id", GetFloatValue(skin.TgloveID));
     //skins_cfg.SetDoubleValue("t glove", "seed", GetFloatValue(skin.tgloveskin));
     skins_cfg.SetDoubleValue("t glove", "itemdef", GetFloatValue(skin.gloveT));
     
     skins_cfg.SetDoubleValue("ct glove", "id", GetFloatValue(skin.CTgloveID));
     //skins_cfg.SetDoubleValue("ct glove", "seed", GetFloatValue(skin.ctgloveskin));
     skins_cfg.SetDoubleValue("ct glove", "itemdef", GetFloatValue(skin.gloveCT));
     */
    
    
    skins_cfg.SaveFile(skins.c_str());
    
}

void Config::UpdateSkins() {
    
    skins_cfg.SetUnicode(true);
    
    skins_cfg.SetDoubleValue("weapon_deagle", "id", GetFloatValue(skin.deagle));
    skins_cfg.SetDoubleValue("weapon_deagle", "seed", GetFloatValue(skin.deagle_Seed));
    skins_cfg.SetDoubleValue("weapon_deagle", "itemdef", GetFloatValue(1));
    
    skins_cfg.SetDoubleValue("weapon_elite", "id", GetFloatValue(skin.dual));
    skins_cfg.SetDoubleValue("weapon_elite", "seed", GetFloatValue(skin.dual_Seed));
    skins_cfg.SetDoubleValue("weapon_elite", "itemdef", GetFloatValue(2));
    
    skins_cfg.SetDoubleValue("weapon_fiveseven", "id", GetFloatValue(skin.five7));
    skins_cfg.SetDoubleValue("weapon_fiveseven", "seed", GetFloatValue(skin.five7_Seed));
    skins_cfg.SetDoubleValue("weapon_fiveseven", "itemdef", GetFloatValue(3));
    
    skins_cfg.SetDoubleValue("weapon_glock", "id", GetFloatValue(skin.glock));
    skins_cfg.SetDoubleValue("weapon_glock", "seed", GetFloatValue(skin.glock_Seed));
    skins_cfg.SetDoubleValue("weapon_glock", "itemdef", GetFloatValue(4));
    
    skins_cfg.SetDoubleValue("weapon_ak47", "id", GetFloatValue(skin.ak));
    skins_cfg.SetDoubleValue("weapon_ak47", "seed", GetFloatValue(skin.ak_Seed));
    skins_cfg.SetDoubleValue("weapon_ak47", "itemdef", GetFloatValue(7));
    
    skins_cfg.SetDoubleValue("weapon_aug", "id", GetFloatValue(skin.aug));
    skins_cfg.SetDoubleValue("weapon_aug", "seed", GetFloatValue(skin.aug_Seed));
    skins_cfg.SetDoubleValue("weapon_aug", "itemdef", GetFloatValue(8));
    
    skins_cfg.SetDoubleValue("weapon_awp", "id", GetFloatValue(skin.awp));
    skins_cfg.SetDoubleValue("weapon_awp", "seed", GetFloatValue(skin.awp_Seed));
    skins_cfg.SetDoubleValue("weapon_awp", "itemdef", GetFloatValue(9));
    
    skins_cfg.SetDoubleValue("weapon_famas", "id", GetFloatValue(skin.famas));
    skins_cfg.SetDoubleValue("weapon_famas", "seed", GetFloatValue(skin.famas_Seed));
    skins_cfg.SetDoubleValue("weapon_famas", "itemdef", GetFloatValue(10));
    
    skins_cfg.SetDoubleValue("weapon_g3sg1", "id", GetFloatValue(skin.g3));
    skins_cfg.SetDoubleValue("weapon_g3sg1", "seed", GetFloatValue(skin.g3_Seed));
    skins_cfg.SetDoubleValue("weapon_g3sg1", "itemdef", GetFloatValue(11));
    
    skins_cfg.SetDoubleValue("weapon_galilar", "id", GetFloatValue(skin.galil));
    skins_cfg.SetDoubleValue("weapon_galilar", "seed", GetFloatValue(skin.galil_Seed));
    skins_cfg.SetDoubleValue("weapon_galilar", "itemdef", GetFloatValue(13));
    
    skins_cfg.SetDoubleValue("weapon_m249", "id", GetFloatValue(skin.m249));
    skins_cfg.SetDoubleValue("weapon_m249", "seed", GetFloatValue(skin.m249_Seed));
    skins_cfg.SetDoubleValue("weapon_m249", "itemdef", GetFloatValue(14));
    
    skins_cfg.SetDoubleValue("weapon_m4a4", "id", GetFloatValue(skin.a4));
    skins_cfg.SetDoubleValue("weapon_m4a4", "seed", GetFloatValue(skin.a4_Seed));
    skins_cfg.SetDoubleValue("weapon_m4a4", "itemdef", GetFloatValue(16));
    
    skins_cfg.SetDoubleValue("weapon_mac10", "id", GetFloatValue(skin.mac10));
    skins_cfg.SetDoubleValue("weapon_mac10", "seed", GetFloatValue(skin.mac10_Seed));
    skins_cfg.SetDoubleValue("weapon_mac10", "itemdef", GetFloatValue(17));
    
    skins_cfg.SetDoubleValue("weapon_p90", "id", GetFloatValue(skin.p90));
    skins_cfg.SetDoubleValue("weapon_p90", "seed", GetFloatValue(skin.p90_Seed));
    skins_cfg.SetDoubleValue("weapon_p90", "itemdef", GetFloatValue(19));
    
    skins_cfg.SetDoubleValue("weapon_ump45", "id", GetFloatValue(skin.ump));
    skins_cfg.SetDoubleValue("weapon_ump45", "seed", GetFloatValue(skin.ump_Seed));
    skins_cfg.SetDoubleValue("weapon_ump45", "itemdef", GetFloatValue(24));
    
    skins_cfg.SetDoubleValue("weapon_xm1014", "id", GetFloatValue(skin.xm));
    skins_cfg.SetDoubleValue("weapon_xm1014", "seed", GetFloatValue(skin.xm_Seed));
    skins_cfg.SetDoubleValue("weapon_xm1014", "itemdef", GetFloatValue(25));
    
    skins_cfg.SetDoubleValue("weapon_bizon", "id", GetFloatValue(skin.bizon));
    skins_cfg.SetDoubleValue("weapon_bizon", "seed", GetFloatValue(skin.bizon_Seed));
    skins_cfg.SetDoubleValue("weapon_bizon", "itemdef", GetFloatValue(26));
    
    skins_cfg.SetDoubleValue("weapon_mag7", "id", GetFloatValue(skin.mag7));
    skins_cfg.SetDoubleValue("weapon_mag7", "seed", GetFloatValue(skin.mag7_Seed));
    skins_cfg.SetDoubleValue("weapon_mag7", "itemdef", GetFloatValue(27));
    
    skins_cfg.SetDoubleValue("weapon_negev", "id", GetFloatValue(skin.negev));
    skins_cfg.SetDoubleValue("weapon_negev", "seed", GetFloatValue(skin.negev_Seed));
    skins_cfg.SetDoubleValue("weapon_negev", "itemdef", GetFloatValue(28));
    
    skins_cfg.SetDoubleValue("weapon_sawedoff", "id", GetFloatValue(skin.sawed));
    skins_cfg.SetDoubleValue("weapon_sawedoff", "seed", GetFloatValue(skin.sawed_Seed));
    skins_cfg.SetDoubleValue("weapon_sawedoff", "itemdef", GetFloatValue(29));
    
    skins_cfg.SetDoubleValue("weapon_tec9", "id", GetFloatValue(skin.tec9));
    skins_cfg.SetDoubleValue("weapon_tec9", "seed", GetFloatValue(skin.tec9_Seed));
    skins_cfg.SetDoubleValue("weapon_tec9", "itemdef", GetFloatValue(30));
    
    skins_cfg.SetDoubleValue("weapon_hkp2000", "id", GetFloatValue(skin.p2000));
    skins_cfg.SetDoubleValue("weapon_hkp2000", "seed", GetFloatValue(skin.p2000_Seed));
    skins_cfg.SetDoubleValue("weapon_hkp2000", "itemdef", GetFloatValue(32));
    
    skins_cfg.SetDoubleValue("weapon_mp7", "id", GetFloatValue(skin.mp7));
    skins_cfg.SetDoubleValue("weapon_mp7", "seed", GetFloatValue(skin.mp7_Seed));
    skins_cfg.SetDoubleValue("weapon_mp7", "itemdef", GetFloatValue(33));
    
    skins_cfg.SetDoubleValue("weapon_mp9", "id", GetFloatValue(skin.mp9));
    skins_cfg.SetDoubleValue("weapon_mp9", "seed", GetFloatValue(skin.mp9_Seed));
    skins_cfg.SetDoubleValue("weapon_mp9", "itemdef", GetFloatValue(34));
    
    skins_cfg.SetDoubleValue("weapon_nova", "id", GetFloatValue(skin.nova));
    skins_cfg.SetDoubleValue("weapon_nova", "seed", GetFloatValue(skin.nova_Seed));
    skins_cfg.SetDoubleValue("weapon_nova", "itemdef", GetFloatValue(35));
    
    skins_cfg.SetDoubleValue("weapon_p250", "id", GetFloatValue(skin.p250));
    skins_cfg.SetDoubleValue("weapon_p250", "seed", GetFloatValue(skin.p250_Seed));
    skins_cfg.SetDoubleValue("weapon_p250", "itemdef", GetFloatValue(36));
    
    skins_cfg.SetDoubleValue("weapon_scar20", "id", GetFloatValue(skin.scar));
    skins_cfg.SetDoubleValue("weapon_scar20", "seed", GetFloatValue(skin.scar_Seed));
    skins_cfg.SetDoubleValue("weapon_scar20", "itemdef", GetFloatValue(38));
    
    skins_cfg.SetDoubleValue("weapon_sg556", "id", GetFloatValue(skin.sg));
    skins_cfg.SetDoubleValue("weapon_sg556", "seed", GetFloatValue(skin.sg_Seed));
    skins_cfg.SetDoubleValue("weapon_sg556", "itemdef", GetFloatValue(39));
    
    skins_cfg.SetDoubleValue("weapon_ssg08", "id", GetFloatValue(skin.scout));
    skins_cfg.SetDoubleValue("weapon_ssg08", "seed", GetFloatValue(skin.scout_Seed));
    skins_cfg.SetDoubleValue("weapon_ssg08", "itemdef", GetFloatValue(40));
    
    skins_cfg.SetDoubleValue("weapon_knife", "id", GetFloatValue(skin.CTknifeID));
    skins_cfg.SetDoubleValue("weapon_knife", "seed", GetFloatValue(skin.CTknfieSeed));
    skins_cfg.SetDoubleValue("weapon_knife", "itemdef", GetFloatValue(skin.knifeCT));
    
    skins_cfg.SetDoubleValue("weapon_knife_t", "id", GetFloatValue(skin.TknifeID));
    skins_cfg.SetDoubleValue("weapon_knife_t", "seed", GetFloatValue(skin.TknifeSeed));
    skins_cfg.SetDoubleValue("weapon_knife_t", "itemdef", GetFloatValue(skin.knifeT));
    
    skins_cfg.SetDoubleValue("weapon_m4a1_silencer", "id", GetFloatValue(skin.a1));
    skins_cfg.SetDoubleValue("weapon_m4a1_silencer", "seed", GetFloatValue(skin.a1_Seed));
    skins_cfg.SetDoubleValue("weapon_m4a1_silencer", "itemdef", GetFloatValue(60));
    
    skins_cfg.SetDoubleValue("weapon_usp_silencer", "id", GetFloatValue(skin.usp));
    skins_cfg.SetDoubleValue("weapon_usp_silencer", "seed", GetFloatValue(skin.usp_Seed));
    skins_cfg.SetDoubleValue("weapon_usp_silencer", "itemdef", GetFloatValue(61));
    
    skins_cfg.SetDoubleValue("weapon_cz75a", "id", GetFloatValue(skin.cz));
    skins_cfg.SetDoubleValue("weapon_cz75a", "seed", GetFloatValue(skin.cz_Seed));
    skins_cfg.SetDoubleValue("weapon_cz75a", "itemdef", GetFloatValue(63));
    
    skins_cfg.SetDoubleValue("weapon_revolver", "id", GetFloatValue(skin.r8));
    skins_cfg.SetDoubleValue("weapon_revolver", "seed", GetFloatValue(skin.r8_Seed));
    skins_cfg.SetDoubleValue("weapon_revolver", "itemdef", GetFloatValue(64));
    
    skins_cfg.SetDoubleValue("glove_t", "id", GetFloatValue(skin.TgloveID));
       skins_cfg.SetDoubleValue("glove_t", "itemdef", GetFloatValue(skin.gloveT));
       
       skins_cfg.SetDoubleValue("glove_ct", "id", GetFloatValue(skin.CTgloveID));
       skins_cfg.SetDoubleValue("glove_ct", "itemdef", GetFloatValue(skin.gloveCT));
    
    skins_cfg.SaveFile(skins.c_str());
    
}


void Config::LoadSkins() {
    
    if(!fileExist(skins.c_str()))
        InitSkins();
    
    skins_cfg.SetUnicode(true);
    //skins_cfg.LoadFile(skins.c_str());
    
    skin.TknifeID   = skin_cfgget_f("weapon_knife_t", "id");
    skin.CTknifeID  = skin_cfgget_f("weapon_knife", "id");
    
    skin.galil   = skin_cfgget_f("weapon_galilar", "id");
    skin.famas   = skin_cfgget_f("weapon_famas", "id");
    skin.ak      = skin_cfgget_f("weapon_ak47", "id");
    skin.a4      = skin_cfgget_f("weapon_m4a4", "id");
    skin.a1      = skin_cfgget_f("weapon_m4a1_silencer", "id");
    skin.scout   = skin_cfgget_f("weapon_ssg08", "id");
    skin.sg      = skin_cfgget_f("weapon_sg556", "id");
    skin.aug     = skin_cfgget_f("weapon_aug", "id");
    skin.awp     = skin_cfgget_f("weapon_awp", "id");
    skin.g3      = skin_cfgget_f("weapon_scar20", "id");
    skin.scar    = skin_cfgget_f("weapon_g3sg1", "id");
    
    skin.glock   = skin_cfgget_f("weapon_glock", "id");
    skin.usp     = skin_cfgget_f("weapon_usp_silencer", "id");
    skin.p2000   = skin_cfgget_f("weapon_hkp2000", "id");
    skin.dual    = skin_cfgget_f("weapon_elite", "id");
    skin.p250    = skin_cfgget_f("weapon_p250", "id");
    skin.tec9    = skin_cfgget_f("weapon_tec9", "id");
    skin.five7   = skin_cfgget_f("weapon_fiveseven", "id");
    skin.cz      = skin_cfgget_f("weapon_cz75a", "id");
    skin.deagle  = skin_cfgget_f("weapon_deagle", "id");
    skin.r8      = skin_cfgget_f("weapon_revolver", "id");
    
    skin.mac10   = skin_cfgget_f("weapon_mac10", "id");
    skin.mp9     = skin_cfgget_f("weapon_mp9", "id");
    skin.mp7     = skin_cfgget_f("weapon_mp7", "id");
    skin.ump     = skin_cfgget_f("weapon_ump45", "id");
    skin.p90     = skin_cfgget_f("weapon_p90", "id");
    skin.bizon   = skin_cfgget_f("weapon_bizon", "id");
    
    skin.nova    = skin_cfgget_f("weapon_nova", "id");
    skin.sawed   = skin_cfgget_f("weapon_sawedoff", "id");
    skin.mag7    = skin_cfgget_f("weapon_mag7", "id 7");
    skin.xm      = skin_cfgget_f("weapon_xm1014", "id");
    skin.m249    = skin_cfgget_f("weapon_m249", "id");
    skin.negev   = skin_cfgget_f("weapon_negev", "id");
    
}



bool Config::HasWeaponConfiguration(const char* section) {
    //skins_cfg.LoadFile(skins.c_str());
    CSimpleIniA::TNamesDepend sections;
    skins_cfg.GetAllSections(sections);
    sections.sort(CSimpleIniA::Entry::LoadOrder());
    
    for (auto sect : sections) {
        if(!strcmp(section, sect.pItem)) {
            return true;
        }
    }
    
    return false;
}


cSkin Config::GetWeaponConfiguration(const char *section) {
    
    //skins_cfg.LoadFile(skins.c_str());
    
    cSkin weapon_config;
    
    weapon_config.Paintkit      = (int)skin_cfgget_f(section, "id");
    weapon_config.Seed          = (int)skin_cfgget_f(section, "seed");
    weapon_config.ItemDefinition= (int)skin_cfgget_f(section, "itemdef");
    
    return weapon_config;
}

