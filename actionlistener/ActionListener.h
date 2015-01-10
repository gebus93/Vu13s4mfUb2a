/*
 * ActionListener.h
 *
 *  Created on: 6 sty 2015
 *      Author: Łukasz
 */

#ifndef ACTIONLISTENER_ACTIONLISTENER_H_
#define ACTIONLISTENER_ACTIONLISTENER_H_

class ActionListener {
public:
	ActionListener();
	virtual ~ActionListener();

protected:
	bool running;
	bool isRunning() const;
};

#endif /* ACTIONLISTENER_ACTIONLISTENER_H_ */
