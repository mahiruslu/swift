/*
 * Copyright (c) 2010 Remko Tronçon
 * Licensed under the GNU General Public License v3.
 * See Documentation/Licenses/GPLv3.txt for more information.
 */

#pragma once

#include "Swiften/Application/ApplicationPathProvider.h"

#include <iostream>
#include <unistd.h>

#include "Swiften/Base/ByteArray.h"
#include "Swiften/Base/foreach.h"

namespace Swift {
	class UnixApplicationPathProvider : public ApplicationPathProvider {
		public:
			UnixApplicationPathProvider(const String& name);

			virtual boost::filesystem::path getHomeDir() const;
			boost::filesystem::path getDataDir() const;
			virtual boost::filesystem::path getExecutableDir() const;

			virtual std::vector<boost::filesystem::path> getResourceDirs() const {
				return resourceDirs;
			}

		private:
			std::vector<boost::filesystem::path> resourceDirs;
	};
}

