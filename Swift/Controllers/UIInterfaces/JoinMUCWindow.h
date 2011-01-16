/*
 * Copyright (c) 2010 Remko Tronçon
 * Licensed under the GNU General Public License v3.
 * See Documentation/Licenses/GPLv3.txt for more information.
 */

#pragma once

#include <vector>

#include <Swiften/Base/String.h>
#include <Swiften/Base/boost_bsignals.h>
#include <Swiften/JID/JID.h>

namespace Swift {
	class JoinMUCWindow {
		public:
			virtual ~JoinMUCWindow() {};

			virtual void setNick(const String& nick) = 0;
			virtual void setMUC(const String& nick) = 0;
			virtual void show() = 0;

			boost::signal<void (const JID& /* muc */, const String& /* nick */, bool /* autoJoin */)> onJoinMUC;
			boost::signal<void ()> onSearchMUC;
	};
}
