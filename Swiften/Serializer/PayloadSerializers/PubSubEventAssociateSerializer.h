/*
 * Copyright (c) 2013-2017 Isode Limited.
 * All rights reserved.
 * See the COPYING file for more information.
 */

#pragma once

#include <memory>

#include <Swiften/Base/API.h>
#include <Swiften/Elements/PubSubEventAssociate.h>
#include <Swiften/Serializer/GenericPayloadSerializer.h>

namespace Swift {
    class PayloadSerializerCollection;

    class SWIFTEN_API PubSubEventAssociateSerializer : public GenericPayloadSerializer<PubSubEventAssociate> {
        public:
            PubSubEventAssociateSerializer(PayloadSerializerCollection* serializers);
            virtual ~PubSubEventAssociateSerializer() override;

            virtual std::string serializePayload(std::shared_ptr<PubSubEventAssociate>) const override;
    };
}
