/*
 * scheduler.c
 *
 *  Created on: Nov 12, 2025
 *      Author: ASUS
 */

#ifndef SRC_SCHEDULER_C_
#define SRC_SCHEDULER_C_

#include "scheduler.h"

#define TICK 10
//SCH_Task_Head = 0;
//SCH_Due_Task_head = 0;
//SCH_Due_Task_tail = 0;



	sTask* SCH_Task_Head = NULL;



void SCH_init(void){
	SCH_Task_Head  = NULL;
//	Error_Code_G = 0;
//	timer_Init();
	//WatchDog_init();
}
void SCH_Update(void){
	if(SCH_Task_Head == 0 ){
		return;
	}
	if(SCH_Task_Head -> Delay == 0){
		SCH_Task_Head -> RunMe ++;
		sTask* temp = SCH_Task_Head;
		while(temp -> pNext != NULL && temp -> pNext -> Delay == 0){
			temp = temp -> pNext;
			temp -> RunMe ++;
		}
	}
	else
	{
		SCH_Task_Head -> Delay --;
	}



}
void SCH_Dispatch_Task(void){
	if(SCH_Task_Head == NULL){
		return;
	}


	if(SCH_Task_Head -> RunMe > 0){
		(*SCH_Task_Head -> pTask )();
		SCH_Task_Head -> RunMe --;

		sTask* SCH_Temp = SCH_Task_Head;
		SCH_Task_Head = SCH_Task_Head -> pNext;

		if(SCH_Temp -> Period != 0){
			SCH_Add_Task(SCH_Temp -> pTask,	 SCH_Temp -> Period	, SCH_Temp -> Period);
			free(SCH_Temp);
		}
		else {


			free(SCH_Temp);
		}


	}

//	SCH_Report_Status();
//	SCH_Go_To_Sleep();
}
 void SCH_Add_Task(void(* pFunction)(), uint32_t DELAY, uint32_t PERIOD){
//		sTask* newTask(pFunction, DELAY, PERIOD); // error
	// 1. Tạo task mới
		sTask* pNewTask = (sTask*)malloc(sizeof(sTask));
		pNewTask -> pTask = pFunction;
		pNewTask -> Delay = DELAY;
		pNewTask -> Period = PERIOD;
		pNewTask -> pNext = 0;
		pNewTask -> RunMe = 0;
	    // 2. TRƯỜNG HỢP 1: Danh sách rỗng
		if (SCH_Task_Head == NULL) {
			SCH_Task_Head = pNewTask;
			return; // <--- SỬA LỖI 1: Phải return ngay
		}

	    // 3. TRƯỜNG HỢP 2: Thêm vào ĐẦU danh sách
	    // (Nếu task mới có delay nhỏ hơn hoặc bằng task đầu tiên)
		if (pNewTask->Delay <= SCH_Task_Head->Delay) {
			// Cập nhật delay tương đối của task đầu tiên cũ
			SCH_Task_Head->Delay = SCH_Task_Head->Delay - pNewTask->Delay;

			// Nối task mới vào
			pNewTask->pNext = SCH_Task_Head;

	        // Cập nhật Head để trỏ đến task mới
			SCH_Task_Head = pNewTask;
			return; // <--- SỬA LỖI 2: Xử lý riêng và return
		}

	    // 4. TRƯỜNG HỢP 3: Thêm vào GIỮA hoặc CUỐI
	    // (Task mới chắc chắn không nằm ở đầu)

	    // Trừ delay của task đầu tiên
	    pNewTask->Delay -= SCH_Task_Head->Delay;

		sTask* temp = SCH_Task_Head;
		sTask* prevTemp = SCH_Task_Head;

	    temp = temp->pNext; // Bắt đầu tìm từ phần tử THỨ HAI

		while (temp != 0) {
	        // Đã tìm thấy vị trí (trước 'temp')
			if (pNewTask->Delay <= temp->Delay) {

	            // Cập nhật delay của 'temp'
				temp->Delay = temp->Delay - pNewTask->Delay;

	            // Chèn task mới vào
				pNewTask->pNext = temp;
				prevTemp->pNext = pNewTask;
				return;
			}
			else {
	            // Đi tiếp, trừ delay
				pNewTask->Delay -= temp->Delay;
				prevTemp = temp;
				temp = temp->pNext;
			}
		}

	    // Nếu vòng lặp kết thúc (temp == 0), chèn vào CUỐI
		prevTemp->pNext = pNewTask;
}
void SCH_Delete_Task(sTask* task){
		sTask* pCur = SCH_Task_Head;
		sTask* pPrev = NULL;

		while(pCur != NULL){
			if(pCur == task){
				if(pPrev == NULL){

					SCH_Task_Head = pCur -> pNext;
					if(SCH_Task_Head != NULL){
						SCH_Task_Head ->Delay += pCur ->Delay;
					}
				}
				else {
					//update waiting list
					pPrev->pNext = pCur->pNext;
					if(pCur->pNext != NULL){
						pCur->pNext->Delay += pCur->Delay; // <--- QUAN TRỌNG: Cộng dồn Delay
					}
				}


				free(pCur);
				return;

			}

			pPrev = pCur;
			pCur = pCur -> pNext;
		}


		//ERROR_G
		//return ERROR_STATUS

}
void SCH_Report_Status(void ){

}
void SCH_Go_To_Sleep(void ){
	HAL_PWR_EnterSLEEPMode(PWR_MAINREGULATOR_ON, PWR_SLEEPENTRY_WFI);
}


#endif /* SRC_SCHEDULER_C_ */
