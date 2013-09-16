/*
 * Copyright (c) 2013 Remko Tronçon
 * Licensed under the GNU General Public License.
 * See the COPYING file for more information.
 */

#pragma once

#include <boost/shared_ptr.hpp>

#include <Swiften/Base/Override.h>
#include <Swiften/Base/API.h>
#include <Swiften/Elements/PubSubOwnerDefault.h>
#include <Swiften/Parser/GenericPayloadParser.h>

namespace Swift {
	class PayloadParserFactoryCollection;
	class PayloadParser;

	class SWIFTEN_API PubSubOwnerDefaultParser : public GenericPayloadParser<PubSubOwnerDefault> {
		public:
			PubSubOwnerDefaultParser(PayloadParserFactoryCollection* parsers);
			virtual ~PubSubOwnerDefaultParser();

			virtual void handleStartElement(const std::string& element, const std::string&, const AttributeMap& attributes) SWIFTEN_OVERRIDE;
			virtual void handleEndElement(const std::string& element, const std::string&) SWIFTEN_OVERRIDE;
			virtual void handleCharacterData(const std::string& data) SWIFTEN_OVERRIDE;

		private:
			PayloadParserFactoryCollection* parsers;
			int level;
			boost::shared_ptr<PayloadParser> currentPayloadParser;
	};
}