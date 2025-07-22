/*
    QHTTPPollMQTT polls a URL and publishes the result to a MQTT broker.
    Copyright (C) 2025  Thomas Zimmermann

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */
// SPDX-License-Identifier: GPL-3.0-or-later

#include "webpoller.h"

WebPoller::WebPoller(const QHTTPPoll2MQTTConfig &config, QObject *parent)
    : QObject{parent}, m_config(config) {

  m_manager = new QNetworkAccessManager;
  connect(m_manager, &QNetworkAccessManager::finished, this,
          &WebPoller::onPollResult);
  m_timer = new QTimer;
  m_timer->setInterval(config.pollInterval());
  connect(m_timer, &QTimer::timeout, this, &WebPoller::poll);
  m_timer->start();
}

void WebPoller::poll() {
  QNetworkRequest request;
  request.setUrl(m_config.pollUrl());
  m_manager->get(request);
}

void WebPoller::onPollResult(QNetworkReply *reply) {
  if (reply->error() != QNetworkReply::NoError) {
    QTextStream(stderr) << "Error:" << reply->errorString() << Qt::endl;
    return;
  }
  emit messageReceived(reply->readAll());
  reply->deleteLater();
}
