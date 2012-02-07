
#include "AP_Process.h"

namespace apo{

    void AP_Process::setupTimer() {
        timer_setDelay(&_timer,ms_to_ticks(_proc_dt));
        timer_set_signal(&_timer,_proc,SIG_USER0);
        timer_add(&_timer);
    }

    void AP_Process::waitOnTimer() {
        sig_wait(SIG_USER0);
    }

    void AP_Process:createProcess(void *p(void *), void * data) {
        _proc = proc_new(p, data, KERN_MINSTACKSIZE*2, NULL);
        proc_setPri(_proc, _priority);
    }



} // namespace apo
