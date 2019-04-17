#include <vector>

/*
 * Created by Stuart Irwin on 4/17/2019.
 * Interfaces for general logic
 */

class LogicReciever {
public:
	virtual void activate();
}

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
		for(LogicReciever *reciever : channels) {
			reciever->activate();
		}
	}

	//Destroy sender
	~LogicSender() {
		delete channels;
	}
}