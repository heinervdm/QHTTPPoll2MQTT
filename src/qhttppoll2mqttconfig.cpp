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

#include "qhttppoll2mqttconfig.h"

QHTTPPoll2MQTTConfig::QHTTPPoll2MQTTConfig() : m_settings(nullptr) {}

bool QHTTPPoll2MQTTConfig::parse(const QString &configFile) {
  m_settings = new QSettings(configFile, QSettings::IniFormat);

  m_settings->beginGroup("http");
  m_pollUrl = m_settings->value("url").toUrl();
  if (!m_pollUrl.isValid()) {
    m_lastError = "Error: Invalid URL: " + m_settings->value("url").toString();
    m_settings->deleteLater();
    m_settings = nullptr;
    return false;
  }
  m_pollInterval = m_settings->value("interval", 10000).toInt();
  m_settings->endGroup();

  m_settings->beginGroup("mqtt");
  m_mqttHostname = m_settings->value("hostname").toString();
  if (m_mqttHostname.isEmpty()) {
    m_lastError = "Error: hostname is empty!";
    m_settings->deleteLater();
    m_settings = nullptr;
    return false;
  }
  m_mqttPort = m_settings->value("port", 8883).toUInt();
  m_mqttUsername = m_settings->value("username").toString();
  m_mqttPassword = m_settings->value("password").toString();
  int version = m_settings->value("version", 3).toInt();
  switch (version) {
  case 3:
    m_mqttVersion = QMqttClient::MQTT_3_1;
    break;
  case 4:
    m_mqttVersion = QMqttClient::MQTT_3_1_1;
    break;
  case 5:
    m_mqttVersion = QMqttClient::MQTT_5_0;
    break;
  default:
    m_lastError = "Error: invalid MQTT version: " +
                  m_settings->value("version").toString();
    m_settings->deleteLater();
    m_settings = nullptr;
    return false;
  }
  m_mqttUseTls = m_settings->value("usetls", false).toBool();
  m_mqttRetain = m_settings->value("retain", false).toBool();
  m_mqttTopic = m_settings->value("topic", "qhttppoll").toString();
  m_settings->endGroup();

  return true;
}
