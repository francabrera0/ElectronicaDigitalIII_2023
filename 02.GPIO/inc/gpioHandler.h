#ifndef GPIOHANDLER_H_
#define GPIOHANDLER_H_

#include <stdint.h>

enum Ports {PORT0, PORT1, PORT2, PORT3, PORT4};
enum State {LOW, HIGH};
enum Dir {INPUT, OUTPUT};
enum Mode {PULLUP, REPEATER, NEITHER, PULLDOWN};

void gpioConfig(int portNumber, int pin, int pinMode, int direction);
void gpioWrite(int portNumber, int pin, int state);
int gpioRead(int portNumber, int pin);

#endif /* GPIOHANDLER_H_ */
