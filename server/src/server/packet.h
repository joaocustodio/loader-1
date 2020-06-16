#pragma once

namespace tcp {
constexpr size_t session_id_len = 10;

enum packet_type : int { write = 0, read };

struct packet_t {
  std::string message;
  char action;
  std::string session_id;

  packet_t() {}
  packet_t(const std::string_view msg, const packet_type &type, std::string_view session = "") {
    if (type == read) {
      if (msg.size() < session_id_len) {
        io::logger->error("packet message invalid!");
        return;
      }

      session_id = msg.substr(0, session_id_len);

      action = msg[session_id_len];
      message = msg.substr(session_id_len);
    } else {
      session_id = session;

      message = fmt::format("{}{}", session_id, msg);
    }
  }

  operator bool() const {
    return !message.empty() && !session_id.empty();
  }
};
};  // namespace tcp