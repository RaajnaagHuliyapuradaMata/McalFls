

//#include "Types.hpp"
//#include "target.hpp"
#include "r_fdl.hpp"
#include "fdl_descriptor.hpp"

void SampleApp_FDL_Control(void)
{

    r_fdl_status_t            fdlRet;
    r_fdl_request_t           req;

   	uint8 wBuf_au08[0x100] =    {   0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
   ,                                   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
   ,                                   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
   ,                                   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
   ,                                   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
   ,                                   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
   ,                                   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
   ,  																	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF
                                };

   uint32 rBuf_au32[0x8];
   volatile uint16 data;
    fdlRet = R_FDL_Init( &sampleApp_fdlConfig_enu );
   if( R_FDL_OK != fdlRet )
   {

        while( 1 )
            ;
   }

#ifndef R_FDL_LIB_V1_COMPATIBILITY

        req.command_enu     = R_FDL_CMD_PREPARE_ENV;
        req.idx_u32         = 0;
        req.cnt_u16         = 0;
        req.accessType_enu  = R_FDL_ACCESS_NONE;
        R_FDL_Execute( &req );

        while( R_FDL_BUSY == req.status_enu )
        {
            R_FDL_Handler();
        }
        if( R_FDL_OK != req.status_enu )
        {

            while( 1 )
                ;
        }
#endif

    req.command_enu     = R_FDL_CMD_BLANKCHECK;
    req.idx_u32         = 0x0004;
    req.cnt_u16         = 1;
    req.accessType_enu  = R_FDL_ACCESS_USER;
    R_FDL_Execute( &req );

   while( R_FDL_BUSY == req.status_enu )
   {
        R_FDL_Handler();
   }

   if( R_FDL_OK == req.status_enu )
   {

   }
   else if( R_FDL_ERR_BLANKCHECK == req.status_enu )
   {

        data = (*(uint16*)0xff200004);
     }
   else{

        while( 1 )
            ;
   }

    req.command_enu     = R_FDL_CMD_ERASE;
    req.idx_u32         = 0;
    req.cnt_u16         = 1;
    req.accessType_enu  = R_FDL_ACCESS_USER;
    R_FDL_Execute( &req );

   while( R_FDL_BUSY == req.status_enu )
   {
        R_FDL_Handler();
   }
   if( R_FDL_OK != req.status_enu )
   {

        while( 1 )
            ;
   }

    req.command_enu     = R_FDL_CMD_WRITE;
    req.idx_u32         = 0x0000;
    req.cnt_u16         = 0x10;
    req.bufAddr_u32     = (uint32)( &wBuf_au08[0] );
    req.accessType_enu  = R_FDL_ACCESS_USER;
    R_FDL_Execute( &req );
   while( R_FDL_BUSY == req.status_enu )
   {
        R_FDL_Handler();
   }
   if( R_FDL_OK != req.status_enu )
   {

        while( 1 )
            ;
   }

    req.command_enu     = R_FDL_CMD_READ;
    req.idx_u32         = 0x0000;
    req.cnt_u16         = 0x10;
    req.bufAddr_u32     = (uint32)( &rBuf_au32[0] );
    req.accessType_enu  = R_FDL_ACCESS_USER;
    R_FDL_Execute( &req );
   while( R_FDL_BUSY == req.status_enu )
   {
        R_FDL_Handler();
   }
   if( R_FDL_OK != req.status_enu )
   {

        while( 1 )
            ;
   }

    return;
}

