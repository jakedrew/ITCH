#include <chrono>
#include <format>
#include <ratio>
#include <string>

#include "includes/httplib.h"

std::string getTimestamp() {
    auto tp = std::chrono::system_clock::now();
    return std::format("{:%Y/%m/%d %H:%M:%S}", tp);
}

std::string baseRequest() {
    std::string res = std::format("{}{}{}{}",
        "<h1>Stream at <a href=\"/stream\">/stream</a></h1><p>Try it with <pre>curl -N http://itch.jakedrw.com/stream</pre></p>",
        "<p>Server time: ", getTimestamp(), "</p>"
    );
    return res;
}

std::string streamRequest() {
    return std::format("{}\n", getTimestamp());
}

int main() {
  httplib::Server server;

  server.Get("/", [](const httplib::Request &req, httplib::Response &res) {
    res.set_content(baseRequest(), "text/html");
  });


  server.Get("/stream", [](const httplib::Request &req, httplib::Response &res) {
    res.set_chunked_content_provider(
      "text/event-stream",
      [](size_t offset, httplib::DataSink &sink) {

        std::string message = streamRequest();
        sink.write(message.data(), message.size());
        std::this_thread::sleep_for(std::chrono::milliseconds(100));

        return true;
      });
  });

  server.listen("0.0.0.0", 2026);
}
