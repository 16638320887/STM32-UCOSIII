#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "includes.h"
#include "os_app_hooks.h"
#include "stdio.h"




//UCOSIII���������ȼ��û�������ʹ�ã�ALIENTEK
//����Щ���ȼ��������UCOSIII��5��ϵͳ�ڲ�����
//���ȼ�0���жϷ������������� OS_IntQTask()
//���ȼ�1��ʱ�ӽ������� OS_TickTask()
//���ȼ�2����ʱ���� OS_TmrTask()
//���ȼ�OS_CFG_PRIO_MAX-2��ͳ������ OS_StatTask()
//���ȼ�OS_CFG_PRIO_MAX-1���������� OS_IdleTask()
//����֧�֣�www.openedv.com
//�Ա����̣�http://eboard.taobao.com  
//������������ӿƼ����޹�˾  
//���ߣ�����ԭ�� @ALIENTEK

/*
	ϵͳ�ڲ�����
 ��������OS_IdleTask()��
 ʱ�ӽ��� ���� OS_TickTask()��
 ͳ������ OS_StatTask()��
 ��ʱ���� OS_TmrTask()��
 �жϷ���������� OS_IntQTask()��


*/


//ucosϵͳ�ڲ�����
// OSIdleTaskTCB  
// os.h
/*
void  OS_IdleTaskInit (OS_ERR *p_err)
	{
	//������������
	;
	}
*/
	

/*
ʱ�ӽ�������   OS_TickTask()������

OS_Init()�е�����һ�� ���� OS_TickTaskInit()��

 ʱ�ӽ���������������ȼ�Ϊ OSCfg_TickTaskPrio��
 ʱ�ӽ�����������ȼ������ܵĸ�һ�㣬
 ALIENTEk Ĭ������ʱ�ӽ���������������ȼ�Ϊ 1��


 ʱ�ӽ�������������Ǹ���������ʱ�������Լ���ָ��ʱ���ڵȴ�ĳ���ں˶��������
 
  OS_TickTask()������
	
	 OS_TickListInit ����ʼ��ʱ�ӽ����б����� OS_TickListInit()��������
 
*/


/*  ͳ������
 OS_CFG_STAT_TASK_EN �� 1��



*/
/*
  ��ʱ���� UCOSIII �ṩ�����ʱ�����ܣ�
	��ʱ�����ǿ�ѡ�ģ����� OS_CFG_TMR_EN ����Ϊ 1 �� ��ʹ�ܶ�ʱ����
	�� OSInit()�н�����ú��� OS_TmrInit()��������ʱ����
	��ʱ��������ȼ� ͨ���� OS_CFG_TMR_TASK_PRIO ���壬
	ALIENTEK Ĭ�Ͻ���ʱ���������ȼ�����Ϊ 2
*/


/*


 ʱ��Ƭ��ת���� ǰ�����ᵽ UCOSIII ֧�ֶ������ͬʱӵ��һ�����ȼ�
 Ҫʹ���������������Ҫ���� OS_CFG_SCHED_ROUND_ROBIN_EN Ϊ 1

*/



/*

  OSTaskDel()���� OSTaskDel()��������ɾ������
	��һ��������Ҫ���еĻ������ǾͿ��Խ���ɾ������ɾ ��������˵ɾ���������
	������ UCOSIII ���ٹ��������������ЩӦ��������ֻ��Ҫĳ�� ����ֻ����һ�Σ�
	������ɺ�ͽ���ɾ������
	���������ʼ������
	OSTaskDel()����ԭ�����£�
	void OSTaskDel (OS_TCB *p_tcb,  OS_ERR *p_err) 
	*p_tcb�� ָ��Ҫɾ�������� TCB��Ҳ���Դ���һ�� NULL ָ����ɾ������ OSTaskDel()�� ������������
	*p_err�� ָ��һ����������������� OSTaskDel()�����󷵻صĴ����롣

*/


/*


 �������ͻָ�ʵ�� 6.2.1 OSTaskSuspend()���� 
 ʹ�� OSTaskSuspend()���������������
 �Ժ��ٻָ����У����� OSTaskSuspend()��ԭ�����£�
  void OSTaskSuspend (OS_TCB *p_tcb,OS_ERR *p_err)
  *p_tcb �� ָ����Ҫ���������� OS_TCB������ͨ��ָ��һ�� NULL ָ�뽫���øú� �����������
	*p_err�� ָ��һ����������������ú����Ĵ����롣 ���ǿ��Զ�ε��� OSTaskSuspend ()����������һ������
	���������Ҫ����ͬ�������� OSTaskResume()�����ſ��Իָ��������������һ��ǳ���Ҫ��
 
*/


/*

 6.2.2 OSTaskResume()���� OSTaskResume()���������ָ��� OSTaskSuspend()�������������OSTaskResume()���� 
 ��Ψһ�ָܻ�����������ĺ��������������������ڵȴ�����ں˶���
 �����¼���־�顢 �ź����������ź�������Ϣ���еȣ�
 ��ʹʹ�� OSTaskResume()�����ָ��˱���������񣬸��� ��Ҳ��һ�����������У�
 ��������Ҫ����Ӧ���ں˶���ֻ�еȵ��ں˶����ſ��Լ����� �У�
 OSTaskResume()����ԭ�����£�
 void OSTaskResume (OS_TCB *p_tcb,OS_ERR *p_err) 
 *p_tcb �� ָ����Ҫ��ҵ������ OS_TCB��ָ��һ�� NULL ָ������Ч�ģ�
 ��Ϊ�������� �����У�����Ҫ��ҡ�
 *p_err�� ָ��һ����������������ú����Ĵ����롣

*/

char cpu_sage[10] ;

 u8 share_resource[30]; //������Դ��



OS_SEM MY_SEM; //����һ���ź��������ڷ��ʹ�����Դ

//�ź��������������ͬ�� 

OS_SEM TASK_MY_SEM1; //����һ���ź�������������֮�������ź��� 



//�������ȼ�  ��������  
#define usart_TASK_PRIO		2
//�����ջ��С	
#define usart_STK_SIZE 		512
//������ƿ�   ��ʼ������ƿ�
OS_TCB usartTaskTCB;
//�����ջ	
CPU_STK usart_TASK_STK[usart_STK_SIZE];
//������
void usart_task(void *p_arg);

//�������ȼ�  ��ʼ����  
#define START_TASK_PRIO		3
//�����ջ��С	
#define START_STK_SIZE 		512
//������ƿ�   ��ʼ������ƿ�
OS_TCB StartTaskTCB;
//�����ջ	
CPU_STK START_TASK_STK[START_STK_SIZE];
//������
void start_task(void *p_arg);

//�������ȼ�
#define LED0_TASK_PRIO		4
//�����ջ��С	
#define LED0_STK_SIZE 		128
//������ƿ�
OS_TCB Led0TaskTCB;
//�����ջ	
CPU_STK LED0_TASK_STK[LED0_STK_SIZE];
void led0_task(void *p_arg);

//�������ȼ�
#define LED1_TASK_PRIO		5
//�����ջ��С	
#define LED1_STK_SIZE 		128
//������ƿ�
OS_TCB Led1TaskTCB;
//�����ջ	
CPU_STK LED1_TASK_STK[LED1_STK_SIZE];
//������
void led1_task(void *p_arg);


//�ٴ�����������
//����1 

//�������ȼ�
#define TASK1_TASK_PRIO		6
//�����ջ��С	
#define TASK1_STK_SIZE 		128
//������ƿ�
OS_TCB TASK1TaskTCB;
//�����ջ	
CPU_STK   TASK1_TASK_STK[TASK1_STK_SIZE];
//������
void TASK1_task(void *p_arg);

//����2 

//�������ȼ�
#define TASK2_TASK_PRIO		7
//�����ջ��С	
#define TASK2_STK_SIZE 		128
//������ƿ�
OS_TCB TASK2TaskTCB;
//�����ջ	
CPU_STK   TASK2_TASK_STK[TASK2_STK_SIZE];
//������
void TASK2_task(void *p_arg);



//�ź���  ����    ������Ϣ  

// �� UCOSII ������Ϣ�������Ϣ���У������� UCOSIII ��ֻ����Ϣ���С���Ϣ���������� ���������ں˶�������������
//ucos  ��Ϣ����   ���Բ����Ƚ��ȳ�(FIFO)�ķ�ʽ��Ҳ���Բ��ú���ȳ�(LIFO)�ķ�ʽ
//��Ϣ����
//   OSQPend() ������Ϣ  �ȴ���Ϣ����

//  OSQPost()  ����Ϣ���з���һ����Ϣ


/*

 OSSemCreate() ����һ���ź��� 
 OSSemDel()  ɾ��һ���ź��� 
 
 
 OSSemPend()   ����һ���ź��� 

//	OS_OPT_PEND_BLOCKING ָ���ź�����Чʱ����������Եȴ��ź�����
//	OS_OPT_PEND_NON_BLOCKING �ź�����Чʱ������ֱ�ӷ��ء�
		
 
 OSSemPendAbort() ȡ���ȴ� 
 OSSemPost() ����һ���ź��� 
 
//  opt�� ����ѡ���ź������͵ķ�ʽ��
//	OS_OPT_POST_1 ����ȴ����ź��������ȼ���ߵ��������ź�����
//	OS_OPT_POST_ALL ��ȴ����ź����������������ź�����
//	OS_OPT_POST_NO_SCHED ��ѡ���ֹ�ڱ�������ִ��������Ȳ�����
//	��ʹ �ú���ʹ�ø������ȼ��������������������״̬��
//	Ҳ����ִ��������ȣ����ǻ� �������������������������ȡ�
 
 OSSemSet() ǿ������һ���ź�����ֵ
 
*/








//�����ʱ��

////////////////////////////////////////////////////////
OS_TMR 	tmr1;		//��ʱ��1
OS_TMR	tmr2;		//��ʱ��2
void tmr1_callback(void *p_tmr, void *p_arg); 	//��ʱ��1�ص�����
void tmr2_callback(void *p_tmr, void *p_arg);	//��ʱ��2�ص�����

/*

 ��ʱ���ķֱ��������Ƕ����ϵͳ����Ƶ�� OS_CFG_TICK_RATE_HZ ������
 �������� ����Ϊ 200��ϵͳʱ�����ھ��� 5ms����ʱ������С�ֱ��ʿ϶����� 5ms��
����һ����ʱ�� �������Ҫʹ�ö�ʱ�����϶���Ҫ�ȴ���һ����ʱ����ʹ�� OSTmrCreate()����������һ�� ��ʱ����
�������Ҳ����ȷ����ʱ��������ģʽ��OSTmrCreate()����ԭ�����£�
void OSTmrCreate (OS_TMR *p_tmr,  CPU_CHAR *p_name,  OS_TICK dly,  OS_TICK period,  OS_OPT opt,  OS_TMR_CALLBACK_PTR p_callback,  void *p_callback_arg,  OS_ERR *p_err) 
p_tmr�� ָ��ʱ����ָ�룬
�� OS_TMR ��һ���ṹ�塣
p_name: ��ʱ�����ơ�
dly: ��ʼ����ʱ�����ӳ�ֵ��
period: �ظ����ڡ�
opt: ��ʱ������ѡ�
����������ģʽ����ѡ��
OS_OPT_TMR_ONE_SHOT ���ζ�ʱ�� 
OS_OPT_TMR_PERIODIC ���ڶ�ʱ��
p_callback: ָ��ص����������֡�
p_callback_arg: �ص������Ĳ����� 
p_err: ���ô˺����Ժ󷵻صĴ����롣


*/
//�����ʱ��
// opt ����Ϊ OS_OPT_TMR_ONE_SHOT���� �Ǵ����ĵ��ζ�ʱ����
/*
����һ�����ζ�ʱ���Ժ�
����һ������ OSTmrStart()������ʱ���ͻ� �Ӵ���ʱ����� dly ��ʼ��������ֱ����Ϊ 0 ���ûص�����
*/

int main(void)
{
	OS_ERR err;
	CPU_SR_ALLOC();
	
	delay_init();  	//ʱ�ӳ�ʼ��
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�жϷ�������
	uart_init(115200);  //���ڳ�ʼ��
	LED_Init();         //LED��ʼ��

	
	OSInit(&err);		//��ʼ��UCOSIII
	OS_CRITICAL_ENTER();//�����ٽ���
	//������ʼ����
	OSTaskCreate((OS_TCB 	* )&StartTaskTCB,		//������ƿ�
				 (CPU_CHAR	* )"start task", 		//��������
                 (OS_TASK_PTR )start_task, 			//������
                 (void		* )0,					//���ݸ��������Ĳ���
                 (OS_PRIO	  )START_TASK_PRIO,     //�������ȼ�
                 (CPU_STK   * )&START_TASK_STK[0],	//�����ջ����ַ
                 (CPU_STK_SIZE)START_STK_SIZE/10,	//�����ջ�����λ
                 (CPU_STK_SIZE)START_STK_SIZE,		//�����ջ��С
                 (OS_MSG_QTY  )0,					//�����ڲ���Ϣ�����ܹ����յ������Ϣ��Ŀ,Ϊ0ʱ��ֹ������Ϣ
                 (OS_TICK	  )0,					//��ʹ��ʱ��Ƭ��תʱ��ʱ��Ƭ���ȣ�Ϊ0ʱΪĬ�ϳ��ȣ�
                 (void   	* )0,					//�û�����Ĵ洢��
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR, //����ѡ��
                 (OS_ERR 	* )&err);				//��Ÿú�������ʱ�ķ���ֵ
	OS_CRITICAL_EXIT();	//�˳��ٽ���	 
	OSStart(&err);  //����UCOSIII
	while(1);
}

//��ʼ������
void start_task(void *p_arg)
{
	OS_ERR err;
	CPU_SR_ALLOC();
	p_arg = p_arg;

	CPU_Init();//��ʼ��UCOSIII      ��һ�� 
#if OS_CFG_STAT_TASK_EN > 0u
   OSStatTaskCPUUsageInit(&err);  	//ͳ������                
#endif
	
#ifdef CPU_CFG_INT_DIS_MEAS_EN		//���ʹ���˲����жϹر�ʱ��
    CPU_IntDisMeasMaxCurReset();	
#endif
	/*
	
	
	 ��CPU ���ܵ�ʹ���ʻᱣ���ڱ��� OSStatTaskCPUUsage �У� ���ǿ���ͨ����ȡ���ֵ����ȡ CPU ��ʹ����
	*/
	
	
#if OS_CFG_STAT_TASK_EN > 0u 
	OSStatTaskCPUUsageInit(&err); //ͳ������  #endif
#endif	
/*
	 ��ʱʹ�ܿ�������Ĺ��� �����Ժ�ÿ�ν����������ͻ����ָ�� OS_AppIdleTaskHookPtr ��ָ��ĺ���
	���Ӻ��� ���ܴ�����ڽ��� 
	
	*/

//
	/*
#if OS_CFG_APP_HOOKS_EN				//ʹ�ù��Ӻ���  
	App_OS_SetAllHooks();		// ���� App_OS_SetAllHooks()�����������еĹ��Ӻ���ʹ�õ� app ����	

#endif
*/


#if	OS_CFG_SCHED_ROUND_ROBIN_EN  //��ʹ��ʱ��Ƭ��ת��ʱ��
	 //ʹ��ʱ��Ƭ��ת���ȹ���,ʱ��Ƭ����Ϊ1��ϵͳʱ�ӽ��ģ���1*5=5ms
	OSSchedRoundRobinCfg(DEF_ENABLED,1,&err);  
#endif		

//ʹ�ö�ʱ��
/*
 Ҫ���� OS_CFG_TMR_DEL_EN ���� Ϊ 1��

*/

//������ʱ��1
	OSTmrCreate((OS_TMR		*)&tmr1,		//��ʱ��1
                (CPU_CHAR	*)"tmr1",		//��ʱ������
                (OS_TICK	 )20,			//20*10=200ms  ��ʼ����ʱ
                (OS_TICK	 )10,          //10*10=10ms  ����
                (OS_OPT		 )OS_OPT_TMR_PERIODIC, //����ģʽ
                (OS_TMR_CALLBACK_PTR)tmr1_callback,//��ʱ��1�ص�����
                (void	    *)0,			//����Ϊ0
                (OS_ERR	    *)&err);		//���صĴ�����
				
				
	//������ʱ��2
	OSTmrCreate((OS_TMR		*)&tmr2,		
                (CPU_CHAR	*)"tmr2",		
                (OS_TICK	 )100,			//200*10=1000ms	
                (OS_TICK	 )0,   					//������  �ظ�����0
                (OS_OPT		 )OS_OPT_TMR_ONE_SHOT, 	//���ζ�ʱ��
                (OS_TMR_CALLBACK_PTR)tmr2_callback,	//��ʱ��2�ص�����
                (void	    *)0,			
                (OS_ERR	    *)&err);	
/*�����ٽ���֮ǰ�ȴ����˶�ʱ������*/
	
//	OSStatInit();						//��ʼ��ͳ������.�������ʱ1��������	
	
	OS_CRITICAL_ENTER();	//�����ٽ���
								
								
								
		//����һ���ź���
	OSSemCreate ((OS_SEM*	)&MY_SEM,
                 (CPU_CHAR*	)"MY_SEM",
                 (OS_SEM_CTR)1,		
                 (OS_ERR*	)&err);							
								
		
			//����һ���ź���  �����������ź���
	/*
								
								
								
								*/
	OSSemCreate ((OS_SEM*	)&TASK_MY_SEM1,
                 (CPU_CHAR*	)"TASK_MY_SEM1",
                 (OS_SEM_CTR)0,	//�ź����ĳ�ʼֵΪ1	
                 (OS_ERR*	)&err);	//��Ŵ���ķ���ֵ
								
	//������������
	
		//������������
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
                 (OS_ERR 	* )&err);	//��Ŵ���ķ���ֵ
	
	
	
	//����LED0����
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
                 (OS_ERR 	* )&err);		//��Ŵ���ķ���ֵ		
				 
	//����LED1����
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
								 
	//����TASK1����
	OSTaskCreate((OS_TCB 	* )&TASK1TaskTCB,		  //������ƿ�
				 (CPU_CHAR	* )"TASK1 task", 		  	  //��������
                 (OS_TASK_PTR )TASK1_task, 		//������	
                 (void		* )0,					      //���ݸ��������Ĳ���
                 (OS_PRIO	  )TASK1_TASK_PRIO,  //�������ȼ�   	 
                 (CPU_STK   * )&TASK1_TASK_STK[0],	  //�����ջ����ַ
                 (CPU_STK_SIZE)TASK1_STK_SIZE/10,	 //�����ջ�����λ
                 (CPU_STK_SIZE)TASK1_STK_SIZE,		//�����ջ��С
                 (OS_MSG_QTY  )0,					    //�����ڲ���Ϣ�����ܹ����յ������Ϣ��Ŀ,Ϊ0ʱ��ֹ������Ϣ
                 (OS_TICK	  )0,					//��ʹ��ʱ��Ƭ��תʱ��ʱ��Ƭ���ȣ�Ϊ0ʱΪĬ�ϳ��ȣ�
                 (void   	* )0,				//�û�����Ĵ洢��
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR, //����ѡ��
                 (OS_ERR 	* )&err);	 								//��Ŵ���ķ���ֵ
						//����TASK2����
	OSTaskCreate((OS_TCB 	* )&TASK2TaskTCB,		  //������ƿ�
				 (CPU_CHAR	* )"TASK2 task", 		  	  //��������
                 (OS_TASK_PTR )TASK2_task, 		//������	
                 (void		* )0,					      //���ݸ��������Ĳ���
                 (OS_PRIO	  )TASK2_TASK_PRIO,  //�������ȼ�   	 
                 (CPU_STK   * )&TASK2_TASK_STK[0],	  //�����ջ����ַ
                 (CPU_STK_SIZE)TASK2_STK_SIZE/10,	 //�����ջ�����λ
                 (CPU_STK_SIZE)TASK2_STK_SIZE,		//�����ջ��С
                 (OS_MSG_QTY  )0,					    //�����ڲ���Ϣ�����ܹ����յ������Ϣ��Ŀ,Ϊ0ʱ��ֹ������Ϣ
                 (OS_TICK	  )0,					//��ʹ��ʱ��Ƭ��תʱ��ʱ��Ƭ���ȣ�Ϊ0ʱΪĬ�ϳ��ȣ�
                 (void   	* )0,				//�û�����Ĵ洢��
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR, //����ѡ��
                 (OS_ERR 	* )&err);	 								//��Ŵ���ķ���ֵ			 
								 
								 
								 
	OS_CRITICAL_EXIT();	//�����ٽ���
}


//�½�







//����1 
/*
�����˹�����Դ�����з���

*/
void TASK1_task(void *p_arg)
{
	
	u8 task1_str[]="First task Running!";
	uint16_t task1_count=0;
	OS_ERR err;
	p_arg = p_arg;
	

	while(1)
	{
		
		
  
		
	//	printf("����                   1  !\r\n");
		//������һ���ź���   ���ʹ���ռ�   ͨ���ź������ͺ���������
		OSSemPend(&MY_SEM,0,OS_OPT_PEND_BLOCKING,0,&err); 	//�����ź���
		memcpy(share_resource,task1_str,sizeof(task1_str)); //������Դ���������� (1)
		delay_ms(200);
	//	printf("%s\r\n",share_resource); //�������������Դ������
		OSSemPost (&MY_SEM,OS_OPT_POST_1,&err);				//�����ź���
		LED0 = ~LED0; 
	//	OSTimeDlyHMSM(0,0,1,0,OS_OPT_TIME_PERIODIC,&err); //��ʱ 1s
		task1_count++;
		//�����ʱ��
		while(task1_count==1)
		{
		OSTmrStart(&tmr1,&err);	//������ʱ��1  �ظ����� 
		//��ʱ������һ��
		break;
		}
		
		
		OSTimeDlyHMSM(0,0,0,120,OS_OPT_TIME_HMSM_STRICT,&err); //��ʱ500ms
		
		while(task1_count==10)
		{
		OSTmrStart(&tmr2,&err);	//������ʱ��2   ���ζ�ʱ���ݼ�����  
			break;
		}
		/*
		OSTmrStop(&tmr1,OS_OPT_TMR_NONE,0,&err);	//�رն�ʱ��1
		OSTmrStop(&tmr2,OS_OPT_TMR_NONE,0,&err);	//�رն�ʱ��2
		*/
		
		
		
		printf("�½�����1����Ĺ�����ָ�\r\n");
		 //���� 1 ִ�� 5 �κ�������� 2
		while(task1_count==5)
		{
		OSTaskSuspend((OS_TCB*)&TASK2TaskTCB,&err); /*��������2*/
		printf("���� 1 ���������� 2!\r\n");
		break;
		}

				while(task1_count==20)
		{
		OSTaskResume((OS_TCB*)&TASK2TaskTCB,&err); /*�ָ�����2*/
		printf("���� 1 �ָ������� 2!\r\n");
		break;
		}
		//800ms
		OSTimeDlyHMSM(0,0,0,800,OS_OPT_TIME_HMSM_STRICT,&err); //��ʱ500ms
	}
}

//����2
void TASK2_task(void *p_arg)
{
	OS_ERR err;
	p_arg = p_arg;
	while(1)
	{	
		printf("�½�����2����Ĺ�����ָ�\r\n");
		OSTimeDlyHMSM(0,0,0,900,OS_OPT_TIME_HMSM_STRICT,&err); //��ʱ500ms
	}
}



//
//led0������
void led0_task(void *p_arg)
{
	
	
	u8 task2_str[]="Second task Running!";
	uint16_t task_count=0;
	//main.c(258): error:  #268: declaration may not appear after executable statement in block  �����ڿ�ִ�������������
	OS_ERR err;
	p_arg = p_arg;

	while(1)
	{
		LED0=0;
		printf("LED����1\r\n");
		sprintf(cpu_sage,"ai=%d",OSStatTaskCPUUsage);
		printf("%s\r\n",cpu_sage);
		task_count++;
		/*
		printf("task_count:%d\r\n",task_count);
		OSTimeDlyHMSM(0,0,0,200,OS_OPT_TIME_HMSM_STRICT,&err); //��ʱ200ms
		LED0=1;
		OSTimeDlyHMSM(0,0,0,500,OS_OPT_TIME_HMSM_STRICT,&err); //��ʱ500ms
		*/
		//�ź��� MY_SEM  Ϊ����һ������ռ���ź���    
		OSSemPend(&MY_SEM,0,OS_OPT_PEND_BLOCKING,0,&err); 	//�����ź���
		memcpy(share_resource,task2_str,sizeof(task2_str));//������Դ���������� (2)
		delay_ms(200); 
		printf("%s\r\n",share_resource); //�������������Դ������
		OSSemPost (&MY_SEM,OS_OPT_POST_1,&err);				//�����ź���
		while(task_count==5)
		{		
		//�������ź���   LED0��������5�η���һ���ź���  LED1��������һ�� 
		OSSemPost(&TASK_MY_SEM1,OS_OPT_POST_1,&err);//�����ź��� TASK_MY_SEM1  
		//�������TASK_MY_SEM1  �����ź���  ��������ź��������񽫵��¹���
		task_count=0;  
		break;
		}
		
		
/*    //�����ɾ���봴��		
		
		//ɾ��LED1����
		 //���� 1 ִ�� 5 �˺�ɾ����LED1
		while(task_count==5)
		{
		//ɾ��LED1����
		OSTaskDel((OS_TCB*)&Led1TaskTCB,&err);
			break;
		}
		
	 //���� 1 ִ��10 �˺󴴽� LED1
		while(task_count==10)
		{
//			
//			OS_ERR err;
//			CPU_SR_ALLOC();
//			
			OS_ERR err;
			CPU_SR_ALLOC();
			OS_CRITICAL_ENTER();	//�����ٽ���
			//����LED1����
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
				OS_CRITICAL_EXIT();	//�����ٽ���
			
			
			break;
		}
*/
	}
}


// ���ﴫ�ݸ� OSTaskDel()�������� p_tcb ��ֵΪ 0����ʾɾ������������


void usart_task(void *p_arg)
{
	OS_ERR err;
	p_arg = p_arg;
		while(1)
		{
		//���մ�������  
		if(USART_RX_BUF[0]==0x01)
		{
		
		JIDIANQI=0;
			
		}
		if(USART_RX_BUF[0]==0x02)
		{
		
		JIDIANQI=1;
		}
		USART_RX_STA=0;//�������ݴ���,���¿�ʼ����	
		OSTimeDlyHMSM(0,0,0,10,OS_OPT_TIME_HMSM_STRICT,&err); //��ʱ10ms
	}

}
//led1������
void led1_task(void *p_arg)
{
	OS_ERR err;
	p_arg = p_arg;
	while(1)
	{

		
		//����LED0����ķ��͵��ź���   TASK_MY_SEM1
		OSSemPend(&TASK_MY_SEM1,0,OS_OPT_PEND_BLOCKING,0,&err); //(3)
		/*		
		OS_OPT_PEND_BLOCKING ָ���ź�����Чʱ����������Եȴ��ź�����
		OS_OPT_PEND_NON_BLOCKING �ź�����Чʱ������ֱ�ӷ��ء�
		*/
		//û���ź����ķ���  �ᵼ��LED1���������
		printf("LED����2\r\n");
		
		//JIDIANQI=~JIDIANQI;
			LED1=~LED1;
		 OSSemPost(&TASK_MY_SEM1,OS_OPT_POST_1,&err); //�����ź���(2)
		OSTimeDlyHMSM(0,0,0,500,OS_OPT_TIME_HMSM_STRICT,&err); //��ʱ500ms
		
	}
}

//OSMboxPost(msg_key,(void*)key);//������Ϣ

//��ʱ��1�Ļص�����
void tmr1_callback(void *p_tmr, void *p_arg)
{
	static u8 tmr1_num=0;
 printf("��ʱ��1�ص���������               \r\n");
//	JIDIANQI=~JIDIANQI;
//		LED1 = ~LED1;
	tmr1_num++;		//��ʱ��1ִ�д�����1
}

//��ʱ��2�Ļص�����
void tmr2_callback(void *p_tmr,void *p_arg)
{
	static u8 tmr2_num = 0;
	tmr2_num++;		//��ʱ��2ִ�д�����1
	printf("��ʱ��2�ص���������               \r\n");
//	LED1 = ~LED1;
	printf("��ʱ��2���н���\r\n");
}


