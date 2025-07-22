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

#ifndef WEBPOLLER_H
#define WEBPOLLER_H

#include "qhttppoll2mqttconfig.h"
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QObject>
#include <QTimer>

class WebPoller : public QObject {
  Q_OBJECT
public:
  explicit WebPoller(const QHTTPPoll2MQTTConfig &config,
                     QObject *parent = nullptr);

private slots:
  void poll();
  void onPollResult(QNetworkReply *reply);

signals:
  void messageReceived(const QByteArray &msg);

private:
  QHTTPPoll2MQTTConfig m_config;
  QNetworkAccessManager *m_manager;
  QTimer *m_timer;
};

#endif // WEBPOLLER_H
