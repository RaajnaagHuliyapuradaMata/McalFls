#ifndef FLS_IRQ_H
#define FLS_IRQ_H

#include "Fls_Ram.hpp"
#include "Fls_Types.hpp"

#include "SwcServiceOs.hpp"

#if(FLS_AR_VERSION  == FLS_AR_HIGHER_VERSION)
#define FLS_IRQ_AR_RELEASE_MAJOR_VERSION   FLS_AR_RELEASE_MAJOR_VERSION
#define FLS_IRQ_AR_RELEASE_MINOR_VERSION   FLS_AR_RELEASE_MINOR_VERSION
#define FLS_IRQ_AR_RELEASE_REVISION_VERSION FLS_AR_RELEASE_REVISION_VERSION
#elif(FLS_AR_VERSION  == FLS_AR_LOWER_VERSION)
#define FLS_IRQ_AR_MAJOR_VERSION  FLS_AR_MAJOR_VERSION_VALUE
#define FLS_IRQ_AR_MINOR_VERSION  FLS_AR_MINOR_VERSION_VALUE
#define FLS_IRQ_AR_PATCH_VERSION  FLS_AR_PATCH_VERSION_VALUE
#endif

#define FLS_IRQ_SW_MAJOR_VERSION  FLS_SW_MAJOR_VERSION
#define FLS_IRQ_SW_MINOR_VERSION  FLS_SW_MINOR_VERSION

#endif

