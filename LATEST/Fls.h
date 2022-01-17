#pragma once

#include "Std_Types.h"
#include "Compiler_Cfg_Fls.h"

class class_Fls{
   public:
      FUNC(void, FLS_CODE) InitFunction   (void);
      FUNC(void, FLS_CODE) Erase          (void);
      FUNC(void, FLS_CODE) Write          (void);
      FUNC(void, FLS_CODE) Cancel         (void);
      FUNC(void, FLS_CODE) GetStatus      (void);
      FUNC(void, FLS_CODE) GetJobResult   (void);
      FUNC(void, FLS_CODE) Read           (void);
      FUNC(void, FLS_CODE) Compare        (void);
      FUNC(void, FLS_CODE) SetMode        (void);
      FUNC(void, FLS_CODE) GetVersionInfo (void);
      FUNC(void, FLS_CODE) MainFunction   (void);
};

extern class_Fls Fls;

