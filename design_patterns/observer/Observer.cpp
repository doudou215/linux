#include <iostream>
#include <vector>

class Subject;

class Oberser {
public:
	virtual ~Oberser() {}

	virtual int getState() = 0;
	virtual void update(Subject *subject) = 0;
};


class ConcreteObserver: public Oberser {
public:
	ConcreteObserver(int state) : state_(state) {}

	int getState() {
		return state_;
	}

	void update( Subject *subject);

private:
	int state_;
};


class Subject {
public:
	virtual ~Subject() {}

	void attach(Oberser *observer) {
		observers.push_back(observer);
	}

	void detach(const int idx) {
		observers.erase(observers.begin() + idx);
	}

	void notify() {
		for (int i = 0; i < observers.size(); i++) {
			observers.at(i)->update(this);
		}
	}

	virtual int getState() = 0;
	virtual void setState(const int s) = 0;

private:
	std::vector<Oberser*> observers;
};


class ConcreteSubject: public Subject {
public:
	int getState() {
		return state_;
	}

	void setState(const int state) {
		state_ = state;
	}

private:
	int state_;
};


void ConcreteObserver::update(Subject * subject) {
	state_ = subject->getState();
	std::cout << "Observer state update" << std::endl;
}

int main() {
	ConcreteObserver obs1(1);
	ConcreteObserver obs2(2);

	std::cout << "observer 1 state " << obs1.getState() << std::endl;
	std::cout << "observer 2 state " << obs2.getState() << std::endl;

	Subject *subject = new ConcreteSubject();

	subject->attach(&obs1);
	subject->attach(&obs2);

	subject->setState(10);
	subject->notify();

	std::cout << "observer 1 state " << obs1.getState() << std::endl;
	std::cout << "observer 2 state " << obs2.getState() << std::endl;
	return 0;
}