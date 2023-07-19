/* Automatically generated nanopb header */
/* Generated by nanopb-0.4.8-dev */

#ifndef PB_MESHTASTIC_MESHTASTIC_PORTNUMS_PB_H_INCLUDED
#define PB_MESHTASTIC_MESHTASTIC_PORTNUMS_PB_H_INCLUDED
#include <pb.h>

#if PB_PROTO_HEADER_VERSION != 40
#error Regenerate this file with the current version of nanopb generator.
#endif

/* Enum definitions */
/* For any new 'apps' that run on the device or via sister apps on phones/PCs they should pick and use a
 unique 'portnum' for their application.
 If you are making a new app using meshtastic, please send in a pull request to add your 'portnum' to this
 master table.
 PortNums should be assigned in the following range:
 0-63   Core Meshtastic use, do not use for third party apps
 64-127 Registered 3rd party apps, send in a pull request that adds a new entry to portnums.proto to  register your application
 256-511 Use one of these portnums for your private applications that you don't want to register publically
 All other values are reserved.
 Note: This was formerly a Type enum named 'typ' with the same id #
 We have change to this 'portnum' based scheme for specifying app handlers for particular payloads.
 This change is backwards compatible by treating the legacy OPAQUE/CLEAR_TEXT values identically. */
typedef enum _meshtastic_PortNum {
    /* Deprecated: do not use in new code (formerly called OPAQUE)
 A message sent from a device outside of the mesh, in a form the mesh does not understand
 NOTE: This must be 0, because it is documented in IMeshService.aidl to be so */
    meshtastic_PortNum_UNKNOWN_APP = 0,
    /* A simple UTF-8 text message, which even the little micros in the mesh
 can understand and show on their screen eventually in some circumstances
 even signal might send messages in this form (see below) */
    meshtastic_PortNum_TEXT_MESSAGE_APP = 1,
    /* Reserved for built-in GPIO/example app.
 See remote_hardware.proto/HardwareMessage for details on the message sent/received to this port number */
    meshtastic_PortNum_REMOTE_HARDWARE_APP = 2,
    /* The built-in position messaging app.
 Payload is a [Position](/docs/developers/protobufs/api#position) message */
    meshtastic_PortNum_POSITION_APP = 3,
    /* The built-in user info app.
 Payload is a [User](/docs/developers/protobufs/api#user) message */
    meshtastic_PortNum_NODEINFO_APP = 4,
    /* Protocol control packets for mesh protocol use.
 Payload is a [Routing](/docs/developers/protobufs/api#routing) message */
    meshtastic_PortNum_ROUTING_APP = 5,
    /* Admin control packets.
 Payload is a [AdminMessage](/docs/developers/protobufs/api#adminmessage) message */
    meshtastic_PortNum_ADMIN_APP = 6,
    /* Compressed TEXT_MESSAGE payloads. */
    meshtastic_PortNum_TEXT_MESSAGE_COMPRESSED_APP = 7,
    /* Waypoint payloads.
 Payload is a [Waypoint](/docs/developers/protobufs/api#waypoint) message */
    meshtastic_PortNum_WAYPOINT_APP = 8,
    /* Audio Payloads.
 Encapsulated codec2 packets. On 2.4 GHZ Bandwidths only for now */
    meshtastic_PortNum_AUDIO_APP = 9,
    /* Payloads for clients with a network connection proxying MQTT pub/sub to the device */
    meshtastic_PortNum_MQTT_CLIENT_PROXY_APP = 10,
    /* Provides a 'ping' service that replies to any packet it receives.
 Also serves as a small example module. */
    meshtastic_PortNum_REPLY_APP = 32,
    /* Used for the python IP tunnel feature */
    meshtastic_PortNum_IP_TUNNEL_APP = 33,
    /* Provides a hardware serial interface to send and receive from the Meshtastic network.
 Connect to the RX/TX pins of a device with 38400 8N1. Packets received from the Meshtastic
 network is forwarded to the RX pin while sending a packet to TX will go out to the Mesh network.
 Maximum packet size of 240 bytes.
 Module is disabled by default can be turned on by setting SERIAL_MODULE_ENABLED = 1 in SerialPlugh.cpp. */
    meshtastic_PortNum_SERIAL_APP = 64,
    /* STORE_FORWARD_APP (Work in Progress)
 Maintained by Jm Casler (MC Hamster) : jm@casler.org */
    meshtastic_PortNum_STORE_FORWARD_APP = 65,
    /* Optional port for messages for the range test module. */
    meshtastic_PortNum_RANGE_TEST_APP = 66,
    /* Provides a format to send and receive telemetry data from the Meshtastic network.
 Maintained by Charles Crossan (crossan007) : crossan007@gmail.com */
    meshtastic_PortNum_TELEMETRY_APP = 67,
    /* Experimental tools for estimating node position without a GPS
 Maintained by Github user a-f-G-U-C (a Meshtastic contributor)
 Project files at https://github.com/a-f-G-U-C/Meshtastic-ZPS */
    meshtastic_PortNum_ZPS_APP = 68,
    /* Used to let multiple instances of Linux native applications communicate
 as if they did using their LoRa chip.
 Maintained by GitHub user GUVWAF.
 Project files at https://github.com/GUVWAF/Meshtasticator */
    meshtastic_PortNum_SIMULATOR_APP = 69,
    /* Provides a traceroute functionality to show the route a packet towards
 a certain destination would take on the mesh. */
    meshtastic_PortNum_TRACEROUTE_APP = 70,
    /* Aggregates edge info for the network by sending out a list of each node's neighbors */
    meshtastic_PortNum_NEIGHBORINFO_APP = 71,
    /* Private applications should use portnums >= 256.
 To simplify initial development and testing you can use "PRIVATE_APP"
 in your code without needing to rebuild protobuf files (via [regen-protos.sh](https://github.com/meshtastic/firmware/blob/master/bin/regen-protos.sh)) */
    meshtastic_PortNum_PRIVATE_APP = 256,
    /* ATAK Forwarder Module https://github.com/paulmandal/atak-forwarder */
    meshtastic_PortNum_ATAK_FORWARDER = 257,
    /* Currently we limit port nums to no higher than this value */
    meshtastic_PortNum_MAX = 511
} meshtastic_PortNum;

#ifdef __cplusplus
extern "C" {
#endif

/* Helper constants for enums */
#define _meshtastic_PortNum_MIN meshtastic_PortNum_UNKNOWN_APP
#define _meshtastic_PortNum_MAX meshtastic_PortNum_MAX
#define _meshtastic_PortNum_ARRAYSIZE ((meshtastic_PortNum)(meshtastic_PortNum_MAX+1))


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif
