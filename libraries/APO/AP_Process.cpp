
#include "AP_Process.h"

namespace apo{

    void AP_Process::processWrapper(void) {

        struct Proc * p = (struct Proc *) proc_currentUserData();
        p->func(p->apo);
    }

    void AP_Process::setupTimer() {
        timer_setDelay(&_timer,ms_to_ticks(_proc_dt));
        timer_setSignal(&_timer,_proc,SIG_USER0);
        timer_add(&_timer);
    }

    void AP_Process::waitOnTimer() {
        sig_wait(SIG_USER0);
    }
} // namespace apo
