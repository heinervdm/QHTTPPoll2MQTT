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

#ifndef DECONZ2MQTTCONFIG_H
#define DECONZ2MQTTCONFIG_H

#include <QMqttClient>
#include <QSettings>
#include <QUrl>

class QHTTPPoll2MQTTConfig {
public:
  explicit QHTTPPoll2MQTTConfig();

  bool parse(const QString &configFile);

  bool isValid() const { return m_settings != nullptr; }
  const QString &lastError() const { return m_lastError; }
  const QUrl &pollUrl() const { return m_pollUrl; }
  int pollInterval() const { return m_pollInterval; }
  const QString &mqttHostname() const { return m_mqttHostname; }
  quint16 mqttPort() const { return m_mqttPort; }
  const QString &mqttUsername() const { return m_mqttUsername; }
  const QString &mqttPassword() const { return m_mqttPassword; }
  QMqttClient::ProtocolVersion mqttVersion() const { return m_mqttVersion; }
  bool mqttUseTls() const { return m_mqttUseTls; }
  bool mqttRetain() const { return m_mqttRetain; }
  const QString &mqttTopic() const { return m_mqttTopic; }

private:
  QSettings *m_settings;
  QString m_lastError;
  QUrl m_pollUrl;
  int m_pollInterval;
  QString m_mqttHostname;
  quint16 m_mqttPort = 8883;
  QString m_mqttUsername;
  QString m_mqttPassword;
  QMqttClient::ProtocolVersion m_mqttVersion = QMqttClient::MQTT_3_1;
  bool m_mqttUseTls = false;
  bool m_mqttRetain = false;
  QString m_mqttTopic;
};

#endif // DECONZ2MQTTCONFIG_H
