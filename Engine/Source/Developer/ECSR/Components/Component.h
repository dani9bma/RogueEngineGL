#pragma once

namespace Skel
{
    class SKEL_API Component
    {
        public:
        virtual void BeginPlay();
        virtual void OnTick();
        virtual void OnDestroy();
        
    }
    
    
    