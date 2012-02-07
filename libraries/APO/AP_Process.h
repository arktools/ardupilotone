/*
 * AP_Process.h
 *
 *  Created on: Feb 7, 2011
 *      Author: ashull
 */

#ifndef AP_PROCESS_H_
#define AP_PROCESS_H_


/**
 * ArduPilotOne namespace to protect variables
 * from overlap with avr and libraries etc.
 * ArduPilotOne does not use any global
 * variables.
 */

namespace apo {
    
    class AP_Process {
        public:
            /**
             * Default Constructor
             */
            AP_Process(int priority, float dt) :
                _priority(priority), _proc_dt(dt) {
                }

            /**
             * Accessors
             */
            int getPriority() {
                return _priority;
            }

            float proc_dt() {
                return _proc_dt;
            }
            
        protected:
            int _priority;
            float _proc_dt;
    };

} // namespace apo

#endif /* AP_PROCESS_H_ */
// vim:ts=4:sw=4:expandtab
