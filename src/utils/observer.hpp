      
#ifndef OBSERVER_HPP
#define OBSERVER_HPP

#include <vector>

struct Observer {
  virtual void subjectChanged() = 0;
  virtual ~Observer()           = default;

 protected:
  Observer()                            = default;
  Observer(const Observer &)            = default;
  Observer(Observer &&)                 = default;
  Observer &operator=(const Observer &) = default;
  Observer &operator=(Observer &&)      = default;
};

class Subject {
  std::vector<Observer *> observers;

 protected:
  Subject()                           = default;
  Subject(const Subject &)            = default;
  Subject(Subject &&)                 = default;
  Subject &operator=(const Subject &) = default;
  Subject &operator=(Subject &&)      = default;

 public:
  void registerObserver(Observer *observer);
  void removeObserver(Observer *observer);
  void notifyObservers() const;
  virtual ~Subject() = default;
};

#endif // OBSERVER_HPP

    