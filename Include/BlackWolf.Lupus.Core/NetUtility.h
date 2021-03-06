/**
 * Copyright (C) 2014 David Wolf <d.wolf@live.at>
 *
 * This file is part of Lupus.
 * Lupus is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Lupus is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Lupus. If not, see <http://www.gnu.org/licenses/>.
 */
#pragma once

#include "SocketEnum.h"
#include <cstdint>
#include <memory>
#include <vector>

namespace Lupus {
    namespace Net {
        namespace Sockets {
            class Socket;
            class IPAddress;
            class IPEndPoint;

            /*!
             * Konvertiert eine 16-Bit Ganzzahl von Host zu Netzwerk Byteorder.
             *
             * \returns Die 16-Bit Ganzzahl in Netzwerk Byteorder.
             */
            LUPUSCORE_API uint16_t HostToNetworkOrder(uint16_t host) NOEXCEPT;

            /*!
             * Konvertiert eine 32-Bit Ganzzahl von Host zu Netzwerk Byteorder.
             *
             * \returns Die 32-Bit Ganzzahl in Netzwerk Byteorder.
             */
            LUPUSCORE_API uint32_t HostToNetworkOrder(uint32_t host) NOEXCEPT;

            /*!
             * Konvertiert eine 64-Bit Ganzzahl von Host zu Netzwerk Byteorder.
             *
             * \returns Die 64-Bit Ganzzahl in Netzwerk Byteorder.
             */
            LUPUSCORE_API uint64_t HostToNetworkOrder(uint64_t host) NOEXCEPT;

            /*!
             * Konvertiert eine 16-Bit Ganzzahl von Netzwerk zu Host Byteorder.
             *
             * \returns Die 16-Bit Ganzzahl in Host Byteorder.
             */
            LUPUSCORE_API uint16_t NetworkToHostOrder(uint16_t network) NOEXCEPT;

            /*!
             * Konvertiert eine 32-Bit Ganzzahl von Netzwerk zu Host Byteorder.
             *
             * \returns Die 32-Bit Ganzzahl in Host Byteorder.
             */
            LUPUSCORE_API uint32_t NetworkToHostOrder(uint32_t network) NOEXCEPT;

            /*!
             * Konvertiert eine 64-Bit Ganzzahl von Netzwerk zu Host Byteorder.
             *
             * \returns Die 64-Bit Ganzzahl in Host Byteorder.
             */
            LUPUSCORE_API uint64_t NetworkToHostOrder(uint64_t network) NOEXCEPT;

            /*!
             * Diese Funktion ruft GetAddressInformation(node, service,
             * AddressFamily::Unspecified, SocketType::Unspecified,
             * ProtocolType::Unspecified) auf.
             *
             * \sa GetAddressInformation(const String&, const String&, AddressFamily, SocketType, ProtocolType)
             */
            LUPUSCORE_API std::vector<std::shared_ptr<IPEndPoint>> GetAddressInformation(const String& node, const String& service) throw(std::runtime_error);

            /*!
             * Diese Funktion ruft GetAddressInformation(node, service,
             * family, SocketType::Unspecified, ProtocolType::Unspecified) auf.
             *
             * \sa GetAddressInformation(const String&, const String&, AddressFamily, SocketType, ProtocolType)
             */
            LUPUSCORE_API std::vector<std::shared_ptr<IPEndPoint>> GetAddressInformation(const String& node, const String& service, AddressFamily family) throw(std::runtime_error);

            /*!
             * Diese Funktion ruft GetAddressInformation(node, service,
             * AddressFamily::Unspecified, type, ProtocolType::Unspecified) auf.
             *
             * \sa GetAddressInformation(const String&, const String&, AddressFamily, SocketType, ProtocolType)
             */
            LUPUSCORE_API std::vector<std::shared_ptr<IPEndPoint>> GetAddressInformation(const String& node, const String& service, SocketType type) throw(std::runtime_error);

            /*!
             * Diese Funktion ruft GetAddressInformation(node, service,
             * AddressFamily::Unspecified, SocketType::Unspecified, protocol) auf.
             *
             * \sa GetAddressInformation(const String&, const String&, AddressFamily, SocketType, ProtocolType)
             */
            LUPUSCORE_API std::vector<std::shared_ptr<IPEndPoint>> GetAddressInformation(const String& node, const String& service, ProtocolType protocol) throw(std::runtime_error);

            /*!
             * Liest die Adressinformation des angegebenen Knotens mit dem
             * entsprechenenden Service. Falls node und service eine leere Zeichenkette
             * darstellen, dann wird ein std::runtime_error geworfen. Falls nach der
             * Lokalen-IP (Loopback) gesucht werden soll, dann muss der node eine
             * leere Zeichenkette sein. Falls ein beliebiger Service verwendet werden
             * soll, dann muss service eine leere Zeichenkette sein.
             *
             * Diese Methode führt eine DNS-Abfrage durch, dadurch sind auch Knoten der
             * Form "www.example.com" gültig.
             *
             * Als Service kann jeweils eine Portnummer oder der Service direkt
             * angegeben werden. Bsp: "http" oder "80".
             *
             * Alle gefunden Adressen werden dann schließlich in einen Vektor
             * gespeichert und retouniert.
             *
             * \param[in]   node        Der Knoten nach dem gesucht werden soll.
             * \param[in]   service     Der zu suchende Service.
             * \param[in]   family      Die zu verwendende Addressfamilie.
             * \param[in]   type        Der zu verwendende Sockettyp.
             * \param[in]   protocol    Das zu verwendende Protokoll.
             *
             * \returns Vektor mit allen gefunden Adressen.
             */
            LUPUSCORE_API std::vector<std::shared_ptr<IPEndPoint>> GetAddressInformation(
                const String& node,
                const String& service,
                AddressFamily family,
                SocketType type,
                ProtocolType protocol
                )
                throw(std::runtime_error, std::invalid_argument);
        }
    }
}
