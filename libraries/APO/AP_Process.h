/*
 * AP_Process.h
 *
 *  Created on: Feb 7, 2011
 *      Author: ashull
 */

#ifndef AP_PROCESS_H_
#define AP_PROCESS_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <cpu/irq.h>
#include <cpu/power.h>
#include <drv/timer.h>
#include <kern/proc.h>
#include <kern/monitor.h>

#ifdef __cplusplus
}
#endif

/*
void * operator new(size_t size);
void operator delete(void *ptr);

void * operator new(size_t size) {
    return malloc(size);
}

void operator delete(void * ptr) {
    free(ptr);
}
*/

/**
 * ArduPilotOne namespace to protect variables
 * from overlap with avr and libraries etc.
 * ArduPilotOne does not use any global
 * variables.
 */

namespace apo {
    
    class AP_Process {
        public:
            struct Proc {
                void (*func)();
                AP_Autopilot * apo;
            };

            /**
             * Default Constructor
             */
            AP_Process(int priority, float dt) :
                _priority(priority), _proc_dt(dt) {
                }

            /*
             * Static wrapper for the process declaration
             */
            static void processWrapper(void);

            /**
             * Accessors
             */
            int getPriority() {
                return _priority;
            }

            float proc_dt() {
                return _proc_dt;
            }

            void setupTimer();
            void waitOnTimer();

            //virtual void update();

            void createProcess(void p(), AP_Autopilot * apo) {
                proc_def.func = p;
                proc_def.apo = apo;
                _proc = proc_new(processWrapper,&proc_def, KERN_MINSTACKSIZE*2,NULL);
                proc_setPri(_proc,_priority);
            }
               
            
        protected:
            int _priority;
            float _proc_dt;
            struct Process * _proc;
            struct Proc proc_def; 
            Timer _timer;
    };

} // namespace apo

#endif /* AP_PROCESS_H_ */
// vim:ts=4:sw=4:expandtab
