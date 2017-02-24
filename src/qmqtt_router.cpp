/*
 * qmqtt_router.cpp - qmqtt router
 *
 * Copyright (c) 2013  Ery Lee <ery.lee at gmail dot com>
 * Router added by Niklas Wulf <nwulf at geenen-it-systeme dot de>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *   * Redistributions of source code must retain the above copyright notice,
 *     this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *   * Neither the name of mqttc nor the names of its contributors may be used
 *     to endorse or promote products derived from this software without
 *     specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 */
#include "qmqtt_router.h"

#include "qmqtt_client.h"
#include "qmqtt_routesubscription.h"
#include "qmqtt_logging.h"

namespace QMQTT {

Q_LOGGING_CATEGORY(router, "qmqtt.router")

Router::Router(Client *parent) : QObject(parent), _client(parent)
{
}

RouteSubscription *Router::subscribe(const QString &route)
{
    RouteSubscription *subscription = new RouteSubscription(this);
    subscription->setRoute(route);
    _client->subscribe(subscription->_topic, 0);
    connect(_client, SIGNAL(received(const Message&)), subscription, SLOT(routeMessage(const Message&)));
    return subscription;
}

} // namespace QMQTT