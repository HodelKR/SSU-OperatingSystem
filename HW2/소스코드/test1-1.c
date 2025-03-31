#include "types.h"
#include "stat.h"
#include "user.h"

int main(void) {
  printf(1, "start scheduler_test\n");
  int pid = fork();
  if(pid < 0) {
    printf(1, "fork failed\n");
    exit();
  }
  else if(pid == 0) {
    // 자식 프로세스
    set_proc_info(0, 0, 0, 0, 500);  // 시스템 콜 사용
    // CPU를 계속 사용하는 무한 루프
    volatile int count = 0;  // volatile을 사용하여 최적화 방지
    while(1) {
      count++;
    }
    exit();
  }
  else {
    // 부모 프로세스
    wait();
    printf(1, "end of scheduler_test\n");
  }
  exit();
}