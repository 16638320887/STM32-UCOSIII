#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "includes.h"
#include "os_app_hooks.h"
#include "stdio.h"




//UCOSIII中以下优先级用户程序不能使用，ALIENTEK
//将这些优先级分配给了UCOSIII的5个系统内部任务
//优先级0：中断服务服务管理任务 OS_IntQTask()
//优先级1：时钟节拍任务 OS_TickTask()
//优先级2：定时任务 OS_TmrTask()
//优先级OS_CFG_PRIO_MAX-2：统计任务 OS_StatTask()
//优先级OS_CFG_PRIO_MAX-1：空闲任务 OS_IdleTask()
//技术支持：www.openedv.com
//淘宝店铺：http://eboard.taobao.com  
//广州市星翼电子科技有限公司  
//作者：正点原子 @ALIENTEK

/*
	系统内部任务
 空闲任务OS_IdleTask()、
 时钟节拍 任务 OS_TickTask()、
 统计任务 OS_StatTask()、
 定时任务 OS_TmrTask()和
 中断服务管理任务 OS_IntQTask()。


*/


//ucos系统内部任务
// OSIdleTaskTCB  
// os.h
/*
void  OS_IdleTaskInit (OS_ERR *p_err)
	{
	//创建空闲任务
	;
	}
*/
	

/*
时钟节拍任务   OS_TickTask()任务函数

OS_Init()中调用了一个 函数 OS_TickTaskInit()，

 时钟节拍任务的任务优先级为 OSCfg_TickTaskPrio，
 时钟节拍任务的优先级尽可能的高一点，
 ALIENTEk 默认设置时钟节拍任务的任务优先级为 1。


 时钟节拍任务的作用是跟踪正在延时的任务，以及在指定时间内等待某个内核对象的任务
 
  OS_TickTask()任务函数
	
	 OS_TickListInit 来初始化时钟节拍列表，函数 OS_TickListInit()代码如下
 
*/


/*  统计任务
 OS_CFG_STAT_TASK_EN 置 1，



*/
/*
  定时任务 UCOSIII 提供软件定时器功能，
	定时任务是可选的，将宏 OS_CFG_TMR_EN 设置为 1 就 会使能定时任务，
	在 OSInit()中将会调用函数 OS_TmrInit()来创建定时任务。
	定时任务的优先级 通过宏 OS_CFG_TMR_TASK_PRIO 定义，
	ALIENTEK 默认将定时器任务优先级设置为 2
*/


/*


 时间片轮转调度 前面多次提到 UCOSIII 支持多个任务同时拥有一个优先级
 要使用这个功能我们需要定义 OS_CFG_SCHED_ROUND_ROBIN_EN 为 1

*/



/*

  OSTaskDel()函数 OSTaskDel()函数用来删除任务，
	当一个任务不需要运行的话，我们就可以将其删除掉，删 除任务不是说删除任务代码
	，而是 UCOSIII 不再管理这个任务，在有些应用中我们只需要某个 任务只运行一次，
	运行完成后就将其删除掉，
	比如外设初始化任务，
	OSTaskDel()函数原型如下：
	void OSTaskDel (OS_TCB *p_tcb,  OS_ERR *p_err) 
	*p_tcb： 指向要删除的任务 TCB，也可以传递一个 NULL 指针来删除调用 OSTaskDel()函 数的任务自身。
	*p_err： 指向一个变量用来保存调用 OSTaskDel()函数后返回的错误码。

*/


/*


 任务挂起和恢复实验 6.2.1 OSTaskSuspend()函数 
 使用 OSTaskSuspend()函数挂起这个任务，
 以后再恢复运行，函数 OSTaskSuspend()的原型如下：
  void OSTaskSuspend (OS_TCB *p_tcb,OS_ERR *p_err)
  *p_tcb ： 指向需要挂起的任务的 OS_TCB，可以通过指向一个 NULL 指针将调用该函 数的任务挂起。
	*p_err： 指向一个变量，用来保存该函数的错误码。 我们可以多次调用 OSTaskSuspend ()函数来挂起一个任务，
	因此我们需要调用同样次数的 OSTaskResume()函数才可以恢复被挂起的任务，这一点非常重要。
 
*/


/*

 6.2.2 OSTaskResume()函数 OSTaskResume()函数用来恢复被 OSTaskSuspend()函数挂起的任务，OSTaskResume()函数 
 是唯一能恢复被挂起任务的函数。如果被挂起的任务还在等待别的内核对象，
 比如事件标志组、 信号量、互斥信号量、消息队列等，
 即使使用 OSTaskResume()函数恢复了被挂起的任务，该任 务也不一定能立即运行，
 该任务还是要等相应的内核对象，只有等到内核对象后才可以继续运 行，
 OSTaskResume()函数原型如下：
 void OSTaskResume (OS_TCB *p_tcb,OS_ERR *p_err) 
 *p_tcb ： 指向需要解挂的任务的 OS_TCB，指向一个 NULL 指针是无效的，
 因为该任务正 在运行，不需要解挂。
 *p_err： 指向一个变量，用来保存该函数的错误码。

*/

char cpu_sage[10] ;

 u8 share_resource[30]; //共享资源区



OS_SEM MY_SEM; //定义一个信号量，用于访问共享资源

//信号量用来做任务的同步 

OS_SEM TASK_MY_SEM1; //定义一个信号量，用于任务之间请求信号量 



//任务优先级  串口任务  
#define usart_TASK_PRIO		2
//任务堆栈大小	
#define usart_STK_SIZE 		512
//任务控制块   开始任务控制块
OS_TCB usartTaskTCB;
//任务堆栈	
CPU_STK usart_TASK_STK[usart_STK_SIZE];
//任务函数
void usart_task(void *p_arg);

//任务优先级  开始任务  
#define START_TASK_PRIO		3
//任务堆栈大小	
#define START_STK_SIZE 		512
//任务控制块   开始任务控制块
OS_TCB StartTaskTCB;
//任务堆栈	
CPU_STK START_TASK_STK[START_STK_SIZE];
//任务函数
void start_task(void *p_arg);

//任务优先级
#define LED0_TASK_PRIO		4
//任务堆栈大小	
#define LED0_STK_SIZE 		128
//任务控制块
OS_TCB Led0TaskTCB;
//任务堆栈	
CPU_STK LED0_TASK_STK[LED0_STK_SIZE];
void led0_task(void *p_arg);

//任务优先级
#define LED1_TASK_PRIO		5
//任务堆栈大小	
#define LED1_STK_SIZE 		128
//任务控制块
OS_TCB Led1TaskTCB;
//任务堆栈	
CPU_STK LED1_TASK_STK[LED1_STK_SIZE];
//任务函数
void led1_task(void *p_arg);


//再创建两个任务
//任务1 

//任务优先级
#define TASK1_TASK_PRIO		6
//任务堆栈大小	
#define TASK1_STK_SIZE 		128
//任务控制块
OS_TCB TASK1TaskTCB;
//任务堆栈	
CPU_STK   TASK1_TASK_STK[TASK1_STK_SIZE];
//任务函数
void TASK1_task(void *p_arg);

//任务2 

//任务优先级
#define TASK2_TASK_PRIO		7
//任务堆栈大小	
#define TASK2_STK_SIZE 		128
//任务控制块
OS_TCB TASK2TaskTCB;
//任务堆栈	
CPU_STK   TASK2_TASK_STK[TASK2_STK_SIZE];
//任务函数
void TASK2_task(void *p_arg);



//信号量  邮箱    传递信息  

// 在 UCOSII 中有消息邮箱和消息队列，但是在 UCOSIII 中只有消息队列。消息队列是由用 户创建的内核对象，数量不限制
//ucos  消息传递   可以采用先进先出(FIFO)的方式，也可以采用后进先出(LIFO)的方式
//消息队列
//   OSQPend() 接收消息  等待消息队列

//  OSQPost()  向消息队列发送一条消息


/*

 OSSemCreate() 创建一个信号量 
 OSSemDel()  删除一个信号量 
 
 
 OSSemPend()   请求一个信号量 

//	OS_OPT_PEND_BLOCKING 指定信号量无效时，任务挂起以等待信号量。
//	OS_OPT_PEND_NON_BLOCKING 信号量无效时，任务直接返回。
		
 
 OSSemPendAbort() 取消等待 
 OSSemPost() 发送一个信号量 
 
//  opt： 用来选择信号量发送的方式。
//	OS_OPT_POST_1 仅向等待该信号量的优先级最高的任务发送信号量。
//	OS_OPT_POST_ALL 向等待该信号量的所有任务发送信号量。
//	OS_OPT_POST_NO_SCHED 该选项禁止在本函数内执行任务调度操作。
//	即使 该函数使得更高优先级的任务结束挂起进入就绪状态，
//	也不会执行任务调度，而是会 在其他后续函数中完成任务调度。
 
 OSSemSet() 强制设置一个信号量的值
 
*/








//软件定时器

////////////////////////////////////////////////////////
OS_TMR 	tmr1;		//定时器1
OS_TMR	tmr2;		//定时器2
void tmr1_callback(void *p_tmr, void *p_arg); 	//定时器1回调函数
void tmr2_callback(void *p_tmr, void *p_arg);	//定时器2回调函数

/*

 定时器的分辨率由我们定义的系统节拍频率 OS_CFG_TICK_RATE_HZ 决定，
 比如我们 定义为 200，系统时钟周期就是 5ms，定时器的最小分辨率肯定就是 5ms。
创建一个定时器 如果我们要使用定时器，肯定需要先创建一个定时器，使用 OSTmrCreate()函数来创建一个 定时器，
这个函数也用来确定定时器的运行模式，OSTmrCreate()函数原型如下：
void OSTmrCreate (OS_TMR *p_tmr,  CPU_CHAR *p_name,  OS_TICK dly,  OS_TICK period,  OS_OPT opt,  OS_TMR_CALLBACK_PTR p_callback,  void *p_callback_arg,  OS_ERR *p_err) 
p_tmr： 指向定时器的指针，
宏 OS_TMR 是一个结构体。
p_name: 定时器名称。
dly: 初始化定时器的延迟值。
period: 重复周期。
opt: 定时器运行选项，
这里有两个模式可以选择。
OS_OPT_TMR_ONE_SHOT 单次定时器 
OS_OPT_TMR_PERIODIC 周期定时器
p_callback: 指向回调函数的名字。
p_callback_arg: 回调函数的参数。 
p_err: 调用此函数以后返回的错误码。


*/
//软件定时器
// opt 设置为 OS_OPT_TMR_ONE_SHOT，就 是创建的单次定时器。
/*
创建一个单次定时器以后，
我们一旦调用 OSTmrStart()函数定时器就会 从创建时定义的 dly 开始倒计数，直到减为 0 调用回调函数
*/

int main(void)
{
	OS_ERR err;
	CPU_SR_ALLOC();
	
	delay_init();  	//时钟初始化
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//中断分组配置
	uart_init(115200);  //串口初始化
	LED_Init();         //LED初始化

	
	OSInit(&err);		//初始化UCOSIII
	OS_CRITICAL_ENTER();//进入临界区
	//创建开始任务
	OSTaskCreate((OS_TCB 	* )&StartTaskTCB,		//任务控制块
				 (CPU_CHAR	* )"start task", 		//任务名字
                 (OS_TASK_PTR )start_task, 			//任务函数
                 (void		* )0,					//传递给任务函数的参数
                 (OS_PRIO	  )START_TASK_PRIO,     //任务优先级
                 (CPU_STK   * )&START_TASK_STK[0],	//任务堆栈基地址
                 (CPU_STK_SIZE)START_STK_SIZE/10,	//任务堆栈深度限位
                 (CPU_STK_SIZE)START_STK_SIZE,		//任务堆栈大小
                 (OS_MSG_QTY  )0,					//任务内部消息队列能够接收的最大消息数目,为0时禁止接收消息
                 (OS_TICK	  )0,					//当使能时间片轮转时的时间片长度，为0时为默认长度，
                 (void   	* )0,					//用户补充的存储区
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR, //任务选项
                 (OS_ERR 	* )&err);				//存放该函数错误时的返回值
	OS_CRITICAL_EXIT();	//退出临界区	 
	OSStart(&err);  //开启UCOSIII
	while(1);
}

//开始任务函数
void start_task(void *p_arg)
{
	OS_ERR err;
	CPU_SR_ALLOC();
	p_arg = p_arg;

	CPU_Init();//初始化UCOSIII      第一步 
#if OS_CFG_STAT_TASK_EN > 0u
   OSStatTaskCPUUsageInit(&err);  	//统计任务                
#endif
	
#ifdef CPU_CFG_INT_DIS_MEAS_EN		//如果使能了测量中断关闭时间
    CPU_IntDisMeasMaxCurReset();	
#endif
	/*
	
	
	 。CPU 的总的使用率会保存在变量 OSStatTaskCPUUsage 中， 我们可以通过读取这个值来获取 CPU 的使用率
	*/
	
	
#if OS_CFG_STAT_TASK_EN > 0u 
	OSStatTaskCPUUsageInit(&err); //统计任务  #endif
#endif	
/*
	 当时使能空闲任务的钩子 函数以后每次进入空闲任务就会调用指针 OS_AppIdleTaskHookPtr 所指向的函数
	钩子函数 不能打断正在进入 
	
	*/

//
	/*
#if OS_CFG_APP_HOOKS_EN				//使用钩子函数  
	App_OS_SetAllHooks();		// 调用 App_OS_SetAllHooks()函数设置所有的钩子函数使用的 app 函数	

#endif
*/


#if	OS_CFG_SCHED_ROUND_ROBIN_EN  //当使用时间片轮转的时候
	 //使能时间片轮转调度功能,时间片长度为1个系统时钟节拍，既1*5=5ms
	OSSchedRoundRobinCfg(DEF_ENABLED,1,&err);  
#endif		

//使用定时器
/*
 要将宏 OS_CFG_TMR_DEL_EN 定义 为 1。

*/

//创建定时器1
	OSTmrCreate((OS_TMR		*)&tmr1,		//定时器1
                (CPU_CHAR	*)"tmr1",		//定时器名字
                (OS_TICK	 )20,			//20*10=200ms  初始化延时
                (OS_TICK	 )10,          //10*10=10ms  周期
                (OS_OPT		 )OS_OPT_TMR_PERIODIC, //周期模式
                (OS_TMR_CALLBACK_PTR)tmr1_callback,//定时器1回调函数
                (void	    *)0,			//参数为0
                (OS_ERR	    *)&err);		//返回的错误码
				
				
	//创建定时器2
	OSTmrCreate((OS_TMR		*)&tmr2,		
                (CPU_CHAR	*)"tmr2",		
                (OS_TICK	 )100,			//200*10=1000ms	
                (OS_TICK	 )0,   					//单周期  重复周期0
                (OS_OPT		 )OS_OPT_TMR_ONE_SHOT, 	//单次定时器
                (OS_TMR_CALLBACK_PTR)tmr2_callback,	//定时器2回调函数
                (void	    *)0,			
                (OS_ERR	    *)&err);	
/*进入临界区之前先创建了定时器任务*/
	
//	OSStatInit();						//初始化统计任务.这里会延时1秒钟左右	
	
	OS_CRITICAL_ENTER();	//进入临界区
								
								
								
		//创建一个信号量
	OSSemCreate ((OS_SEM*	)&MY_SEM,
                 (CPU_CHAR*	)"MY_SEM",
                 (OS_SEM_CTR)1,		
                 (OS_ERR*	)&err);							
								
		
			//创建一个信号量  任务间请求的信号量
	/*
								
								
								
								*/
	OSSemCreate ((OS_SEM*	)&TASK_MY_SEM1,
                 (CPU_CHAR*	)"TASK_MY_SEM1",
                 (OS_SEM_CTR)0,	//信号量的初始值为1	
                 (OS_ERR*	)&err);	//存放错误的返回值
								
	//创建其他任务
	
		//创建串口任务
	OSTaskCreate((OS_TCB 	* )&usartTaskTCB,		
				 (CPU_CHAR	* )"usart task", 		
                 (OS_TASK_PTR )usart_task, 			
                 (void		* )0,					
                 (OS_PRIO	  )usart_TASK_PRIO,     
                 (CPU_STK   * )&usart_TASK_STK[0],	
                 (CPU_STK_SIZE)usart_STK_SIZE/10,	
                 (CPU_STK_SIZE)usart_STK_SIZE,		
                 (OS_MSG_QTY  )0,					
                 (OS_TICK	  )0,					
                 (void   	* )0,					
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR,
                 (OS_ERR 	* )&err);	//存放错误的返回值
	
	
	
	//创建LED0任务
	OSTaskCreate((OS_TCB 	* )&Led0TaskTCB,		
				 (CPU_CHAR	* )"led0 task", 		
                 (OS_TASK_PTR )led0_task, 			
                 (void		* )0,					
                 (OS_PRIO	  )LED0_TASK_PRIO,     
                 (CPU_STK   * )&LED0_TASK_STK[0],	
                 (CPU_STK_SIZE)LED0_STK_SIZE/10,	
                 (CPU_STK_SIZE)LED0_STK_SIZE,		
                 (OS_MSG_QTY  )0,					
                 (OS_TICK	  )0,					
                 (void   	* )0,					
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR,
                 (OS_ERR 	* )&err);		//存放错误的返回值		
				 
	//创建LED1任务
	OSTaskCreate((OS_TCB 	* )&Led1TaskTCB,		
				 (CPU_CHAR	* )"led1 task", 		
                 (OS_TASK_PTR )led1_task, 			
                 (void		* )0,					
                 (OS_PRIO	  )LED1_TASK_PRIO,     	
                 (CPU_STK   * )&LED1_TASK_STK[0],	
                 (CPU_STK_SIZE)LED1_STK_SIZE/10,	
                 (CPU_STK_SIZE)LED1_STK_SIZE,		
                 (OS_MSG_QTY  )0,					
                 (OS_TICK	  )0,					
                 (void   	* )0,				
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR, 
                 (OS_ERR 	* )&err);	 
								 
	//创建TASK1任务
	OSTaskCreate((OS_TCB 	* )&TASK1TaskTCB,		  //任务控制块
				 (CPU_CHAR	* )"TASK1 task", 		  	  //任务名字
                 (OS_TASK_PTR )TASK1_task, 		//任务函数	
                 (void		* )0,					      //传递给任务函数的参数
                 (OS_PRIO	  )TASK1_TASK_PRIO,  //任务优先级   	 
                 (CPU_STK   * )&TASK1_TASK_STK[0],	  //任务堆栈基地址
                 (CPU_STK_SIZE)TASK1_STK_SIZE/10,	 //任务堆栈深度限位
                 (CPU_STK_SIZE)TASK1_STK_SIZE,		//任务堆栈大小
                 (OS_MSG_QTY  )0,					    //任务内部消息队列能够接收的最大消息数目,为0时禁止接收消息
                 (OS_TICK	  )0,					//当使能时间片轮转时的时间片长度，为0时为默认长度，
                 (void   	* )0,				//用户补充的存储区
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR, //任务选项
                 (OS_ERR 	* )&err);	 								//存放错误的返回值
						//创建TASK2任务
	OSTaskCreate((OS_TCB 	* )&TASK2TaskTCB,		  //任务控制块
				 (CPU_CHAR	* )"TASK2 task", 		  	  //任务名字
                 (OS_TASK_PTR )TASK2_task, 		//任务函数	
                 (void		* )0,					      //传递给任务函数的参数
                 (OS_PRIO	  )TASK2_TASK_PRIO,  //任务优先级   	 
                 (CPU_STK   * )&TASK2_TASK_STK[0],	  //任务堆栈基地址
                 (CPU_STK_SIZE)TASK2_STK_SIZE/10,	 //任务堆栈深度限位
                 (CPU_STK_SIZE)TASK2_STK_SIZE,		//任务堆栈大小
                 (OS_MSG_QTY  )0,					    //任务内部消息队列能够接收的最大消息数目,为0时禁止接收消息
                 (OS_TICK	  )0,					//当使能时间片轮转时的时间片长度，为0时为默认长度，
                 (void   	* )0,				//用户补充的存储区
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR, //任务选项
                 (OS_ERR 	* )&err);	 								//存放错误的返回值			 
								 
								 
								 
	OS_CRITICAL_EXIT();	//进入临界区
}


//新建







//任务1 
/*
创建了共享资源区进行访问

*/
void TASK1_task(void *p_arg)
{
	
	u8 task1_str[]="First task Running!";
	uint16_t task1_count=0;
	OS_ERR err;
	p_arg = p_arg;
	

	while(1)
	{
		
		
  
		
	//	printf("任务                   1  !\r\n");
		//定义了一个信号量   访问共享空间   通过信号量发送和请求数据
		OSSemPend(&MY_SEM,0,OS_OPT_PEND_BLOCKING,0,&err); 	//请求信号量
		memcpy(share_resource,task1_str,sizeof(task1_str)); //向共享资源区拷贝数据 (1)
		delay_ms(200);
	//	printf("%s\r\n",share_resource); //串口输出共享资源区数据
		OSSemPost (&MY_SEM,OS_OPT_POST_1,&err);				//发送信号量
		LED0 = ~LED0; 
	//	OSTimeDlyHMSM(0,0,1,0,OS_OPT_TIME_PERIODIC,&err); //延时 1s
		task1_count++;
		//软件定时器
		while(task1_count==1)
		{
		OSTmrStart(&tmr1,&err);	//开启定时器1  重复运行 
		//定时器开启一次
		break;
		}
		
		
		OSTimeDlyHMSM(0,0,0,120,OS_OPT_TIME_HMSM_STRICT,&err); //延时500ms
		
		while(task1_count==10)
		{
		OSTmrStart(&tmr2,&err);	//开启定时器2   单次定时器递减计数  
			break;
		}
		/*
		OSTmrStop(&tmr1,OS_OPT_TMR_NONE,0,&err);	//关闭定时器1
		OSTmrStop(&tmr2,OS_OPT_TMR_NONE,0,&err);	//关闭定时器2
		*/
		
		
		
		printf("新建任务1任务的挂起与恢复\r\n");
		 //任务 1 执行 5 次后挂起任务 2
		while(task1_count==5)
		{
		OSTaskSuspend((OS_TCB*)&TASK2TaskTCB,&err); /*挂起任务2*/
		printf("任务 1 挂起了任务 2!\r\n");
		break;
		}

				while(task1_count==20)
		{
		OSTaskResume((OS_TCB*)&TASK2TaskTCB,&err); /*恢复任务2*/
		printf("任务 1 恢复了任务 2!\r\n");
		break;
		}
		//800ms
		OSTimeDlyHMSM(0,0,0,800,OS_OPT_TIME_HMSM_STRICT,&err); //延时500ms
	}
}

//任务2
void TASK2_task(void *p_arg)
{
	OS_ERR err;
	p_arg = p_arg;
	while(1)
	{	
		printf("新建任务2任务的挂起与恢复\r\n");
		OSTimeDlyHMSM(0,0,0,900,OS_OPT_TIME_HMSM_STRICT,&err); //延时500ms
	}
}



//
//led0任务函数
void led0_task(void *p_arg)
{
	
	
	u8 task2_str[]="Second task Running!";
	uint16_t task_count=0;
	//main.c(258): error:  #268: declaration may not appear after executable statement in block  不能在可执行语句声明变量
	OS_ERR err;
	p_arg = p_arg;

	while(1)
	{
		LED0=0;
		printf("LED任务1\r\n");
		sprintf(cpu_sage,"ai=%d",OSStatTaskCPUUsage);
		printf("%s\r\n",cpu_sage);
		task_count++;
		/*
		printf("task_count:%d\r\n",task_count);
		OSTimeDlyHMSM(0,0,0,200,OS_OPT_TIME_HMSM_STRICT,&err); //延时200ms
		LED0=1;
		OSTimeDlyHMSM(0,0,0,500,OS_OPT_TIME_HMSM_STRICT,&err); //延时500ms
		*/
		//信号量 MY_SEM  为访问一个共享空间的信号量    
		OSSemPend(&MY_SEM,0,OS_OPT_PEND_BLOCKING,0,&err); 	//请求信号量
		memcpy(share_resource,task2_str,sizeof(task2_str));//向共享资源区拷贝数据 (2)
		delay_ms(200); 
		printf("%s\r\n",share_resource); //串口输出共享资源区数据
		OSSemPost (&MY_SEM,OS_OPT_POST_1,&err);				//发送信号量
		while(task_count==5)
		{		
		//任务间的信号量   LED0任务运行5次发送一个信号量  LED1任务运行一次 
		OSSemPost(&TASK_MY_SEM1,OS_OPT_POST_1,&err);//发送信号量 TASK_MY_SEM1  
		//如果不给TASK_MY_SEM1  发送信号量  请求这个信号量的任务将导致挂起
		task_count=0;  
		break;
		}
		
		
/*    //任务的删除与创建		
		
		//删除LED1任务
		 //任务 1 执行 5 此后删除掉LED1
		while(task_count==5)
		{
		//删除LED1任务
		OSTaskDel((OS_TCB*)&Led1TaskTCB,&err);
			break;
		}
		
	 //任务 1 执行10 此后创建 LED1
		while(task_count==10)
		{
//			
//			OS_ERR err;
//			CPU_SR_ALLOC();
//			
			OS_ERR err;
			CPU_SR_ALLOC();
			OS_CRITICAL_ENTER();	//进入临界区
			//创建LED1任务
				OSTaskCreate((OS_TCB 	* )&Led1TaskTCB,		
							 (CPU_CHAR	* )"led1 task", 		
											 (OS_TASK_PTR )led1_task, 			
											 (void		* )0,					
											 (OS_PRIO	  )LED1_TASK_PRIO,     	
											 (CPU_STK   * )&LED1_TASK_STK[0],	
											 (CPU_STK_SIZE)LED1_STK_SIZE/10,	
											 (CPU_STK_SIZE)LED1_STK_SIZE,		
											 (OS_MSG_QTY  )0,					
											 (OS_TICK	  )0,					
											 (void   	* )0,				
											 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR, 
											 (OS_ERR 	* )&err);	 
				OS_CRITICAL_EXIT();	//进入临界区
			
			
			break;
		}
*/
	}
}


// 这里传递给 OSTaskDel()函数参数 p_tcb 的值为 0，表示删除掉任务自身


void usart_task(void *p_arg)
{
	OS_ERR err;
	p_arg = p_arg;
		while(1)
		{
		//接收串口数据  
		if(USART_RX_BUF[0]==0x01)
		{
		
		JIDIANQI=0;
			
		}
		if(USART_RX_BUF[0]==0x02)
		{
		
		JIDIANQI=1;
		}
		USART_RX_STA=0;//接收数据错误,重新开始接收	
		OSTimeDlyHMSM(0,0,0,10,OS_OPT_TIME_HMSM_STRICT,&err); //延时10ms
	}

}
//led1任务函数
void led1_task(void *p_arg)
{
	OS_ERR err;
	p_arg = p_arg;
	while(1)
	{

		
		//请求LED0任务的发送的信号量   TASK_MY_SEM1
		OSSemPend(&TASK_MY_SEM1,0,OS_OPT_PEND_BLOCKING,0,&err); //(3)
		/*		
		OS_OPT_PEND_BLOCKING 指定信号量无效时，任务挂起以等待信号量。
		OS_OPT_PEND_NON_BLOCKING 信号量无效时，任务直接返回。
		*/
		//没有信号量的发送  会导致LED1任务的阻塞
		printf("LED任务2\r\n");
		
		//JIDIANQI=~JIDIANQI;
			LED1=~LED1;
		 OSSemPost(&TASK_MY_SEM1,OS_OPT_POST_1,&err); //发送信号量(2)
		OSTimeDlyHMSM(0,0,0,500,OS_OPT_TIME_HMSM_STRICT,&err); //延时500ms
		
	}
}

//OSMboxPost(msg_key,(void*)key);//发送消息

//定时器1的回调函数
void tmr1_callback(void *p_tmr, void *p_arg)
{
	static u8 tmr1_num=0;
 printf("定时器1回调函数测试               \r\n");
//	JIDIANQI=~JIDIANQI;
//		LED1 = ~LED1;
	tmr1_num++;		//定时器1执行次数加1
}

//定时器2的回调函数
void tmr2_callback(void *p_tmr,void *p_arg)
{
	static u8 tmr2_num = 0;
	tmr2_num++;		//定时器2执行次数加1
	printf("定时器2回调函数测试               \r\n");
//	LED1 = ~LED1;
	printf("定时器2运行结束\r\n");
}


