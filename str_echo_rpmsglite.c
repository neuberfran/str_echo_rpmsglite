
//#include "rpmsg/rpmsg_rtos.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "string.h"
#include "board.h"
#include "mu_imx.h"
#include "debug_console_imx.h"

//#include "lib/include/rpmsg_lite.h"
#include "rpmsg_lite.h"
#include "rpmsg_queue.h"
#include "rpmsg_ns.h"


////////////////////////////////////////////////////////////////////////////////
// Definitions
////////////////////////////////////////////////////////////////////////////////
#define APP_TASK_STACK_SIZE 256
#define LOCAL_EPT_ADDR (30)
#define RPMSG_MAX_SIZE 512
#define RPMSG_LITE_LINK_ID   RL_PLATFORM_IMX7D_M4_LINK_ID
#define RPMSG_LITE_SHMEM_BASE 0x9FFF0000
#define RPMSG_LITE_NS_USED 1
#define RPMSG_LITE_NS_ANNOUNCE_STRING "rpmsg-openamp-demo-channel"

/*
 * APP decided interrupt priority
 */
#define APP_MU_IRQ_PRIORITY 3

/* Globals */
static char app_buf[512]; /* Each RPMSG buffer can carry less than 512 payload */

/*!
 * @brief A basic RPMSG task
 */
static void StrEchoTask(void *pvParameters)
{
    int result;
    struct remote_device *rdev = NULL;
//    struct rpmsg_channel *app_chnl = NULL;
    void *rx_buf;
    int len;
    unsigned long src;
    void *tx_buf;
    unsigned long size;


    int recved = 0;
    char buf[RPMSG_MAX_SIZE];
    char rsp[RPMSG_MAX_SIZE];
//    int len;
    volatile unsigned long remote_addr;
    struct rpmsg_lite_endpoint *volatile rl_endpoint;
    volatile rpmsg_queue_handle rl_queue;
    struct rpmsg_lite_instance *volatile rl_instance;

    /* Initialize RPMsg Core and create virtqueues */
    rl_instance = rpmsg_lite_remote_init((void *)RPMSG_LITE_SHMEM_BASE,
                                         RPMSG_LITE_LINK_ID, RL_NO_FLAGS);

    /* Print the initial banner */
    PRINTF("\r\nRPMSG String Echo FreeRTOS RTOS API Demo...\r\n");

    /* RPMSG Init as REMOTE */
    PRINTF("RPMSG Init as Remote\r\n");


    //result = rpmsg_rtos_init(0 /*REMOTE_CPU_ID*/, &rdev, RPMSG_MASTER, &app_chnl);
    //assert(result == 0);

    printf("Waiting for Master.\r\n");
    while (!rpmsg_lite_is_link_up(rl_instance))
//    rpmsg_lite_wait_for_link_up(my_rpmsg, RL_BLOCK);

    {
        // Wait for the link to be up
    }
    printf("Exit.\r\n");

//    PRINTF("Name service handshake is done, M4 has setup a rpmsg channel [%d ---> %d]\r\n", app_chnl->src, app_chnl->dst);

    /*
     * str_echo demo loop
     */
    for (;;)
    {
        /* Get RPMsg rx buffer with message */
//        result = rpmsg_rtos_recv_nocopy(app_chnl->rp_ept, &rx_buf, &len, &src, 0xFFFFFFFF);
  //      assert(result == 0);

        /* Copy string from RPMsg rx buffer */
    //    assert(len < sizeof(app_buf));
    //    memcpy(app_buf, rx_buf, len);
     //   app_buf[len] = 0; /* End string by '\0' */

      //  if ((len == 2) && (app_buf[0] == 0xd) && (app_buf[1] == 0xa))
        //    PRINTF("Get New Line From Master Side\r\n");
        //else
          //  PRINTF("Get Message From Master Side : \"%s\" [len : %d]\r\n", app_buf, len);

        /* Get tx buffer from RPMsg */
  //      tx_buf = rpmsg_rtos_alloc_tx_buffer(app_chnl->rp_ept, &size);
    //    assert(tx_buf);
        /* Copy string to RPMsg tx buffer */
       // memcpy(tx_buf, app_buf, len);
        /* Echo back received message with nocopy send */
  //      result = rpmsg_rtos_send_nocopy(app_chnl->rp_ept, tx_buf, len, src);
    //    assert(result == 0);

        /* Release held RPMsg rx buffer */
    //    result = rpmsg_rtos_recv_nocopy_free(app_chnl->rp_ept, rx_buf);
      //  assert(result == 0);
    }
}

/*
 * MU Interrrupt ISR
 */
void BOARD_MU_HANDLER(void)
{
    /*
     * calls into rpmsg_handler provided by middleware
     */
//    rpmsg_handler();
}

int main(void)
{
    hardware_init();

    /*
     * Prepare for the MU Interrupt
     *  MU must be initialized before rpmsg init is called
     */
    MU_Init(BOARD_MU_BASE_ADDR);
    NVIC_SetPriority(BOARD_MU_IRQ_NUM, APP_MU_IRQ_PRIORITY);
    NVIC_EnableIRQ(BOARD_MU_IRQ_NUM);

    /* Create a demo task. */
    xTaskCreate(StrEchoTask, "String Echo Task", APP_TASK_STACK_SIZE,
                NULL, tskIDLE_PRIORITY+1, NULL);

    /* Start FreeRTOS scheduler. */
    vTaskStartScheduler();

    /* Should never reach this point. */
    while (true);
}
/*******************************************************************************
 * EOF
 ******************************************************************************/
