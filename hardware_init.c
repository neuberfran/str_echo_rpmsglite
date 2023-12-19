
#include "board.h"
#include "pin_mux.h"

void hardware_init(void)
{
    /* Board specific RDC settings */
    BOARD_RdcInit();

    /* Board specific clock settings */
    BOARD_ClockInit();

    /* initialize debug uart */
    dbg_uart_init();

    /* RDC MU*/
    RDC_SetPdapAccess(RDC, BOARD_MU_RDC_PDAP, 3 << (BOARD_DOMAIN_ID * 2), false, false);

    /* Enable clock gate for MU*/
    CCM_ControlGate(CCM, BOARD_MU_CCM_CCGR, ccmClockNeededRun);
}