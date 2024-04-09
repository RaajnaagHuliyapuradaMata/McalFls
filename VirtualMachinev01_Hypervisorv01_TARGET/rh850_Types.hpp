

#ifndef RH850_TYPES_H
#define RH850_TYPES_H

#define V850_TYPES_SW_MAJOR_VERSION  4
#define V850_TYPES_SW_MINOR_VERSION  0
#define V850_TYPES_SW_PATCH_VERSION  0

typedef unsigned int        uinteger;

#define RH850_SV_MODE_ICR_OR(SIZE, ADDR, VAL) \
                                    (*((volatile uint##SIZE*)(ADDR)) = \
                                    ((*((volatile uint##SIZE*)(ADDR)))|(VAL)))

#define RH850_SV_MODE_ICR_AND(SIZE, ADDR, VAL) \
                                    (*((volatile uint##SIZE*)(ADDR)) = \
                                    ((*((volatile uint##SIZE*)(ADDR)))&(VAL)))

#define RH850_SV_MODE_ICR_WRITE_ONLY(SIZE, ADDR, VAL) \
                                 (*((volatile uint##SIZE*)(ADDR)) = \
                                 (VAL))

#define RH850_SV_MODE_IMR_OR(SIZE, ADDR, VAL) \
                                    (*((volatile uint##SIZE*)(ADDR)) = \
                                    ((*((volatile uint##SIZE*)(ADDR)))|(VAL)))

#define RH850_SV_MODE_IMR_AND(SIZE, ADDR, VAL) \
                                    (*((volatile uint##SIZE*)(ADDR)) = \
                                    ((*((volatile uint##SIZE*)(ADDR)))&(VAL)))

#define RH850_SV_MODE_IMR_WRITE_ONLY(SIZE, ADDR, VAL) \
                                 (*((volatile uint##SIZE*)(ADDR)) = \
                                 (VAL))

#endif

