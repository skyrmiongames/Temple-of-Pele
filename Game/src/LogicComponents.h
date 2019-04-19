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
		std::vector<LogicReciever*>::iterator it = channels.begin();
		while (it != channels.end()) {
			(*it)->activate();

			//Delete if single use 
			if((*it)->is_singleton()) {
				it = channels.erase(it);
			}

			if (it != channels.end()) it++; 
		}
	}

	//Destroy sender
	~LogicSender() {
		delete &channels;
	}
};