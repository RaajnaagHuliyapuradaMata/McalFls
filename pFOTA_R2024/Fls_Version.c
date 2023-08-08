#include "Fls_Version.hpp"

#if(FLS_AR_VERSION  == FLS_AR_HIGHER_VERSION)

#define FLS_VERSION_C_AR_RELEASE_MAJOR_VERSION \
                                  FLS_AR_RELEASE_MAJOR_VERSION_VALUE
#define FLS_VERSION_C_AR_RELEASE_MINOR_VERSION \
                                  FLS_AR_RELEASE_MINOR_VERSION_VALUE
#define FLS_VERSION_C_AR_RELEASE_REVISION_VERSION \
                               FLS_AR_RELEASE_REVISION_VERSION_VALUE
#elif(FLS_AR_VERSION  == FLS_AR_LOWER_VERSION)

#define FLS_VERSION_C_AR_MAJOR_VERSION    FLS_AR_MAJOR_VERSION_VALUE
#define FLS_VERSION_C_AR_MINOR_VERSION    FLS_AR_MINOR_VERSION_VALUE
#define FLS_VERSION_C_AR_PATCH_VERSION    FLS_AR_PATCH_VERSION_VALUE
#endif

#define FLS_VERSION_C_SW_MAJOR_VERSION    FLS_SW_MAJOR_VERSION_VALUE
#define FLS_VERSION_C_SW_MINOR_VERSION    FLS_SW_MINOR_VERSION_VALUE

#if(FLS_AR_VERSION  == FLS_AR_HIGHER_VERSION)

#if(FLS_VERSION_AR_RELEASE_MAJOR_VERSION != \
                              FLS_VERSION_C_AR_RELEASE_MAJOR_VERSION)
  #error "Fls_Version.c : Mismatch in Release Major Version"
#endif
#if(FLS_VERSION_AR_RELEASE_MINOR_VERSION != \
                              FLS_VERSION_C_AR_RELEASE_MINOR_VERSION)
  #error "Fls_Version.c : Mismatch in Release Minor Version"
#endif
#if(FLS_VERSION_AR_RELEASE_REVISION_VERSION != \
                           FLS_VERSION_C_AR_RELEASE_REVISION_VERSION)
  #error "Fls_Version.c : Mismatch in Release Revision Version"
#endif
#elif(FLS_AR_VERSION  == FLS_AR_LOWER_VERSION)

#if(FLS_VERSION_AR_MAJOR_VERSION != FLS_VERSION_C_AR_MAJOR_VERSION)
  #error "Fls_Version.c : Mismatch in Specification Major Version"
#endif
#if(FLS_VERSION_AR_MINOR_VERSION != FLS_VERSION_C_AR_MINOR_VERSION)
  #error "Fls_Version.c : Mismatch in Specification Minor Version"
#endif
#if(FLS_VERSION_AR_PATCH_VERSION != FLS_VERSION_C_AR_PATCH_VERSION)
  #error "Fls_Version.c : Mismatch in Specification Patch Version"
#endif
#endif

#if(FLS_VERSION_SW_MAJOR_VERSION != FLS_VERSION_C_SW_MAJOR_VERSION)
  #error "Fls_Version.c : Mismatch in Software Major Version"
#endif
#if(FLS_VERSION_SW_MINOR_VERSION != FLS_VERSION_C_SW_MINOR_VERSION)
  #error "Fls_Version.c : Mismatch in Software Minor Version"
#endif

#if(FLS_VERSION_CHECK_EXT_MODULES == STD_ON)

#if(FLS_AR_VERSION  == FLS_AR_HIGHER_VERSION)

#if(FLS_CRITICAL_SECTION_PROTECTION == STD_ON)
#if((RTE_AR_RELEASE_MAJOR_VERSION != FLS_AR_RELEASE_MAJOR_VERSION) || \
     (RTE_AR_RELEASE_MINOR_VERSION != FLS_AR_RELEASE_MINOR_VERSION))
  #error "The AR version of Rte.h does not match the expected version"
#endif
#endif

#if(FLS_DEV_ERROR_DETECT == STD_ON)
#if((DET_AR_RELEASE_MAJOR_VERSION != FLS_AR_RELEASE_MAJOR_VERSION) || \
     (DET_AR_RELEASE_MINOR_VERSION != FLS_AR_RELEASE_MINOR_VERSION))
  #error "The AR version of Det.h does not match the expected version"
#endif
#endif

#if((DEM_AR_RELEASE_MAJOR_VERSION != FLS_AR_RELEASE_MAJOR_VERSION) || \
     (DEM_AR_RELEASE_MINOR_VERSION != FLS_AR_RELEASE_MINOR_VERSION))
  #error "The AR version of Dem.h does not match the expected version"
#endif

#if((MEMIF_AR_RELEASE_MAJOR_VERSION != FLS_AR_RELEASE_MAJOR_VERSION) || \
     (MEMIF_AR_RELEASE_MINOR_VERSION != FLS_AR_RELEASE_MINOR_VERSION))
  #error "The AR version of MemIf.h does not match the expected version"
#endif

#if((OS_AR_RELEASE_MAJOR_VERSION != FLS_AR_RELEASE_MAJOR_VERSION) || \
     (OS_AR_RELEASE_MINOR_VERSION != FLS_AR_RELEASE_MINOR_VERSION))
  #error "The AR version of Os.h does not match the expected version"
#endif
#elif(FLS_AR_VERSION  == FLS_AR_LOWER_VERSION)

#if(FLS_DEV_ERROR_DETECT == STD_ON)
#if(DET_AR_MAJOR_VERSION != FLS_DET_AR_MAJOR_VERSION)
  #error "Det.h : Mismatch in Specification Major Version"
#endif

#if(DET_AR_MINOR_VERSION != FLS_DET_AR_MINOR_VERSION)
  #error "Det.h : Mismatch in Specification Minor Version"
#endif
#endif

#endif
#endif

