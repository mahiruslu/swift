/*
 * Copyright (c) 2013 Tobias Markmann
 * Licensed under the simplified BSD license.
 * See Documentation/Licenses/BSD-simplified.txt for more information.
 */

#include <Swift/QtUI/UserSearch/ContactListDelegate.h>
#include <Swift/QtUI/UserSearch/ContactListModel.h>
#include <Swift/Controllers/Contact.h>
#include <Swift/QtUI/QtSwiftUtil.h>

namespace Swift {

ContactListDelegate::ContactListDelegate(bool compact) : compact_(compact) {
}

ContactListDelegate::~ContactListDelegate() {
}

void ContactListDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const {
	if (!index.isValid()) {
		return;
	}
	const Contact* contact = static_cast<Contact*>(index.internalPointer());
	QColor nameColor = index.data(Qt::TextColorRole).value<QColor>();
	QString avatarPath = index.data(ContactListModel::AvatarRole).value<QString>();
	QIcon presenceIcon =index.data(ChatListRecentItem::PresenceIconRole).isValid() && !index.data(ChatListRecentItem::PresenceIconRole).value<QIcon>().isNull()
			? index.data(ChatListRecentItem::PresenceIconRole).value<QIcon>()
			: QIcon(":/icons/offline.png");
	QString name = P2QSTRING(contact->name);
	QString statusText = P2QSTRING(contact->jid.toString());
	common_.paintContact(painter, option, nameColor, avatarPath, presenceIcon, name, statusText, false, 0, compact_);
}

QSize ContactListDelegate::sizeHint(const QStyleOptionViewItem& /*option*/, const QModelIndex& /*index*/ ) const {
	QFontMetrics nameMetrics(common_.nameFont);
	QFontMetrics statusMetrics(common_.detailFont);
	int sizeByText = 2 * common_.verticalMargin + nameMetrics.height() + statusMetrics.height();
	return QSize(150, sizeByText);
}

void ContactListDelegate::setCompact(bool compact) {
	compact_ = compact;
}

}