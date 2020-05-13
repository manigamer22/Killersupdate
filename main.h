#ifndef main_h
#define main_h

#include <stdio.h>
#include <string>
#include <cstdint>
#include <unordered_map>
#include <map>
#include <sys/mman.h>
#include <dlfcn.h>
#include <fstream>
#include <mach/mach_traps.h>
#include <mach/mach_init.h>
#include <mach/mach_error.h>
#include <mach/mach.h>
#include <mach-o/dyld_images.h>
#include <mach-o/loader.h>
#include <libproc.h>
#include <sys/stat.h>
#include <cstddef>
#include <codecvt>
#include <cstring>
#include <sstream>
#include <vector>
#include <strings.h>
#include <ios>
#include <iomanip>
#include <pwd.h>
#include <zconf.h>
#include <cstdio>

using namespace std;

#include "offsets.h"    // OFFSET 

#include "SDK/CEffects.h"
#include "SDK/AnimLayer.h"
#include "SDK/CBaseAnimating.h"
#include "SDK/Vector.h"


#include "SDK/Others.h"
#include "SDK/CPlayerResource.h"
#include "SDK/common.h"
#include "SDK/Color.h"
#include "SDK/IBaseClientDLL.h"
#include "SDK/ISurface.h"
#include "SDK/IPanel.h"
#include "SDK/recvproxyhook.h"
#include "SDK/CItemSystem.h"
#include "SDK/ICvar.h"
#include "SDK/C_BaseEntity.h"
#include "SDK/IClientEntityList.h"
#include "SDK/IVDebugOverlay.h"
#include "SDK/IEngineClient.h"
#include "SDK/IEngineTrace.h"
#include "SDK/IMaterial.h"
#include "SDK/IVModelRender.h"
#include "SDK/IGameMovement.h"
#include "SDK/IVModelInfo.h"
#include "SDK/IMaterialSystem.h"
#include "SDK/CUserCmd.h"
#include "SDK/IPrediction.h"
#include "SDK/CGlobalVarsBase.h"
#include "SDK/IInputSystem.h"
#include "SDK/IPhysicsSurfaceProps.h"
#include "SDK/CViewSetup.h"
#include "SDK/CInput.h"
#include "SDK/VMT.h"
#include "SDK/INetChannelInfo.h"
#include "SDK/GameEvent.h"
#include "SDK/IEngineVGui.h"

#include "netvarmanager.h"
#include "bvars.h"
#include "interfaces.h"
#include "drawings.h"

/* Utilities */
#include "utils.h"
#include "patternscan.h"

/* Hacks */
#include "hacks.h"
#include "hooks.h"



#endif /* main_hpp */
