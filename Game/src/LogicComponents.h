#pragma once

#include <vector>

/*
 * Created by Stuart Irwin on 4/17/2019.
 * Interfaces for general logic
 */

class LogicReciever {
public:
	virtual void activate() = 0;
	virtual bool is_singleton() = 0;
	virtual ~LogicReciever() {}
};

class LogicSender {
private:
	std::vector<LogicReciever*> channels;

public:
	//Connect to receiver
	void add_channel(LogicReciever *reciever) {
		channels.push_back(reciever);
	}

	//Activate receivers
	void send() {
		for(std::vector<LogicReciever*>::iterator it = channels.begin() ; it != channels.end(); ++it) {
			(*it)->activate();

			//Delete if single use 
			if((*it)->is_singleton()) {
				channels.erase(it);
				delete *it;
			}
		}
	}

	//Destroy sender
	~LogicSender() {
		delete &channels;
	}
};