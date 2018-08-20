#pragma once

#include <Source/Developer/Common/Common.h>
#include <Source/Developer/Common/Defines.h>
#include <Source/Developer/Common/Types.h>
#include <Source/Developer/Utils/Log.h>

namespace Skel
{
    class SKEL_API Actor
    {
        private:
        
        
        public:
        virtual void BeginPlay();
        virtual void OnTick();
        virtual void OnDestroy();
    }
}


