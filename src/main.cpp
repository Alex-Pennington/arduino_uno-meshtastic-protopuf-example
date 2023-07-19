#include <Arduino.h>
#include <pb.h>
#include <pb_common.h>
#include <pb_decode.h>
#include <pb_encode.h>
#include <meshardu.h>

// struct _pb_ostream_t
// {
//    bool (*callback)(pb_ostream_t *stream, const uint8_t *buf, size_t count);
//    void *state;
//    size_t max_size;
//    size_t bytes_written;
// };

#define SERIAL_RX_PIN 5
#define SERIAL_TX_PIN 6

// Request a node report every this many msec
#define NODE_REPORT_PERIOD (30 * 1000)

// When millis() is >= this, it's time to request a node report.
uint32_t next_node_report_time = 0;

// This callback function will be called repeatedly as the radio's node
// report comes in. For each node received, it will be called with
// the second parameter set to MT_NR_IN_PROGRESS. At the end of the
// report, if the IDs matched, the callback will be called with
// NULL as the first parameter and the second set to either MT_NR_DONE
// (if it was indeed the reply to our request) or MT_NR_INVALID (if it
// turned out to have been a reply to someone else's request).
//
// Everything passed to this callback could be destroyed immediately
// after it returns, so it should save it somewhere else if it needs it.
void node_report_callback(mt_node_t * nodeinfo, mt_nr_progress_t progress) {
  if (progress == MT_NR_INVALID) {
    Serial.println("Oops, ignore all that. It was a reply to someone else's query.");
    return;
  } else if (progress == MT_NR_DONE) {
    Serial.println("And that's all the nodes!");
    return;
  }
  
  Serial.print("The node at ");
  Serial.print(nodeinfo->node_num);
  if (nodeinfo->is_mine) {
    Serial.print(" (that's mine!)");
  }
  Serial.print(", last reached at time=");
  Serial.print(nodeinfo->last_heard_from);

  if (nodeinfo->long_name != NULL) {
    Serial.print(", belongs to '");
    Serial.print(nodeinfo->long_name);
    Serial.print("' (a.k.a. '");
    Serial.print(nodeinfo->short_name);
    Serial.print("' or '");
    Serial.print(nodeinfo->user_id);
    Serial.print("' at '");
    Serial.print(nodeinfo->macaddr);
    Serial.print("') ");
  } else {
    Serial.print(", prefers to remain anonymous ");
  }

  if (!isnan(nodeinfo->latitude)) {
    Serial.print("and is at ");
    Serial.print(nodeinfo->latitude);
    Serial.print(", ");
    Serial.print(nodeinfo->longitude);
    Serial.print("; ");
    Serial.print(nodeinfo->altitude);
    Serial.print(" meters above sea level moving ");
    Serial.print(nodeinfo->ground_speed);
    Serial.print(" degrees from north at ");
    Serial.print(nodeinfo->ground_speed);
    Serial.print(" m/s as of time=");
    Serial.print(nodeinfo->time_of_last_position);
    Serial.print(" and their battery is at ");
    Serial.print(nodeinfo->battery_level);
    Serial.print(" and they told our node at time=");
    Serial.println(nodeinfo->last_heard_position);
  } else {
    Serial.println(" has no position");
  }
}


void setup() {
  // Try for up to five seconds to find a serial port; if not, the show must go on
  Serial.begin(9600);
  while(true) {
    if (Serial) break;
    if (millis() > 5000) break;
  }

  Serial.print("Booted Meshtastic GPS client v1.0 in ");

  mt_serial_init(SERIAL_RX_PIN, SERIAL_TX_PIN);

  // Comment out if you want a quiet console
  mt_set_debug(true);
  
  randomSeed(micros());  
}

void loop() {
  // Record the time that this loop began (in milliseconds since the device booted)
  uint32_t now = millis();

  // Run the Meshtastic loop, and see if it's able to send requests to the device yet
  bool can_send = mt_loop(now);

  // If we can send requests, and it's time to do so, make a request and schedule
  // the next one.
  if (can_send && now >= next_node_report_time) {
    mt_request_node_report(node_report_callback);
    next_node_report_time = now + NODE_REPORT_PERIOD;
  }
}