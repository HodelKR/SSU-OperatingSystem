#include "types.h"
#include "stat.h"
#include "user.h"

int main(void) {
    printf(1, "start scheduler_test\n");
    // 첫 번째 자식 프로세스 생성
    int pid1 = fork();
    if(pid1 < 0) {
        printf(1, "fork failed\n");
        exit();
    }
    if(pid1 == 0) {  // 첫 번째 자식
        set_proc_info(2, 0, 0, 0, 300);
        // CPU를 계속 사용하는 무한 루프
        volatile int count = 0;
        while(1) {
            count++;
        }
        exit();
    }
    // 두 번째 자식 프로세스 생성
    int pid2 = fork();
    if(pid2 < 0) {
        printf(1, "fork failed\n");
        exit();
    }
    if(pid2 == 0) {  // 두 번째 자식
        set_proc_info(2, 0, 0, 0, 300);
        // CPU를 계속 사용하는 무한 루프
        volatile int count = 0;
        while(1) {
            count++;
        }
        exit();
    }
    // 세 번째 자식 프로세스 생성
    int pid3 = fork();
    if(pid3 < 0) {
        printf(1, "fork failed\n");
        exit();
    }
    if(pid3 == 0) {  // 세 번째 자식
        set_proc_info(2, 0, 0, 0, 300);
        // CPU를 계속 사용하는 무한 루프
        volatile int count = 0;
        while(1) {
            count++;
        }
        exit();
    }
    // 부모 프로세스는 모든 자식이 종료될 때까지 대기
    wait();
    wait();
    wait();
    printf(1, "end of scheduler_test\n");
    exit();
}