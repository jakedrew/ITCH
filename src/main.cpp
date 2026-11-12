#include "includes/httplib.h"

int main() {
  httplib::Server server;

  server.Get("/", [](const httplib::Request &req, httplib::Response &res) {
    res.set_content("<h1>Hello http-server</h1>", "text/html");
  });

  server.listen("0.0.0.0", 1121);
}
