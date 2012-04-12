/*
 * Board_APM1_2560.h
 *
 *  Created on: Dec 7, 2011
 *
 */

#ifndef Board_APM1_2560_H_
#define Board_APM1_2560_H_

#include "Board_APM1.h"

namespace apo {

class Board_APM1_2560 : public Board_APM1 {
public:
    Board_APM1_2560(const parameters_t parameters) : 
        Board_APM1(parameters) {
        _eepromMaxAddr = 2048;
    }
private:
};

} // namespace apo

#endif /* AP_BOARD_APM1_2560_H_ */
// vim:ts=4:sw=4:expandtab
