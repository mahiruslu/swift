#pragma once

#include <boost/shared_ptr.hpp>

#include <QAbstractListModel>
#include <QList>

#include "Swiften/Events/Event.h"

#include "Swift/QtUI/EventViewer/QtEvent.h"

namespace Swift {
class EventModel : public QAbstractListModel {
Q_OBJECT
public:
	EventModel();
	~EventModel();
	void addEvent(boost::shared_ptr<Event> event, bool active);
	void removeEvent(boost::shared_ptr<Event> event);
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;
	int rowCount(const QModelIndex& parent = QModelIndex()) const;
private:
	QList<QtEvent*> activeEvents_;
	QList<QtEvent*> inactiveEvents_;
};

}
