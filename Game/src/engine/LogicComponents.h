#pragma once

#include <vector>

/*
 * Created by Stuart Irwin on 4/17/2019.
 * Interfaces for general logic
 */

enum RecivingAction {
	NONE,
	UNLINK,
	REMOVE
};

class LogicReciever {
  public:
	virtual void activate() {};
	virtual RecivingAction getRecivingAction() { return NONE; };
	virtual ~LogicReciever() {}
};

class LogicSender {
  private:
	std::vector<LogicReciever *> channels;

  public:
	//Connect to receiver
	void addChannel(LogicReciever *reciever) {
		channels.push_back(reciever);
	}

	//Activate receivers
	void send() {
		bool removing = false;
		for (
			std::vector<LogicReciever *>::iterator it = channels.begin(); // Get the iterator
			it != channels.end();										  // Stop if we're at the end
			(!removing && it != channels.end()) ? it++ : it							  // If we're not at the end, increment the iterator, otherwise leave it alone
		) {
			removing = false;
			(*it)->activate();

			//Delete if single use
			if((*it)->getRecivingAction() != NONE) {
				//Remove from channels
				LogicReciever *deleting = *it;
				it = channels.erase(it);
				removing = true;

				//Check for full delete
				if((deleting)->getRecivingAction() == REMOVE)
					delete deleting;
			}
		}
	}

	//Destroy sender
	~LogicSender() {
		channels.clear();
	}
};