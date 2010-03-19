#include "EventModel.h"

#include <qdebug>

namespace Swift {
EventModel::EventModel() {
	
}

EventModel::~EventModel() {
	foreach (QtEvent* event, activeEvents_) {
		delete event;
	}
	foreach (QtEvent* event, inactiveEvents_) {
		delete event;
	}
}

QVariant EventModel::data(const QModelIndex& index, int role) const {
	if (!index.isValid()) {
		return QVariant();
	}
	int row = index.row();
	QtEvent* item = index.row() < activeEvents_.size() ? activeEvents_[row] : inactiveEvents_[row - activeEvents_.size()];
	QVariant result = item ? item->data(role) : QVariant();
	qDebug() << "Asked for data of " << index << ", " << role << " returning " << result;
	return result;
}

int EventModel::rowCount(const QModelIndex& parent) const {
	/* Invalid parent = root, valid parent = child, and we're a list not a tree.*/
	int count = parent.isValid() ? 0 : activeEvents_.size() + inactiveEvents_.size();
	return count;
}

void EventModel::addEvent(boost::shared_ptr<Event> event, bool active) {
	qDebug() << " Adding Event";
	if (active) {
		activeEvents_.push_front(new QtEvent(event, active));
		emit dataChanged(createIndex(0, 0), createIndex(1, 0));
	} else {
		inactiveEvents_.push_front(new QtEvent(event, active));
		emit dataChanged(createIndex(activeEvents_.size() -1, 0), createIndex(activeEvents_.size(), 0));
	}
	emit layoutChanged();
}

void EventModel::removeEvent(boost::shared_ptr<Event> event) {
	for (int i = 0; i < activeEvents_.size(); i++) {
		if (event == activeEvents_[i]->getEvent()) {
			activeEvents_.removeAt(i);
			emit dataChanged(createIndex(i - 1, 0), createIndex(i - 1, 0));
			return;
		}
	}
	for (int i = 0; i < inactiveEvents_.size(); i++) {
		if (event == inactiveEvents_[i]->getEvent()) {
			inactiveEvents_.removeAt(i);
			emit dataChanged(createIndex(activeEvents_.size() + i - 1, 0), createIndex(activeEvents_.size() + i - 1, 0));
			return;
		}
	}

}

}
