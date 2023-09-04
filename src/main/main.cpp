#include <cstdlib>
#include <exception>

#include "Arguments.hpp"
#include "Client.hpp"
#include "logging.hpp"

int main(int argc, const char* argv[]) {
  Arguments* args;
  try {
    args = new Arguments(argc, argv);
  } catch (const std::exception& e) {
    LOG(e.what());
    return EXIT_FAILURE;
  }

  args->print();
  Client* client = new Client(args->urls()[0]);
  // client->print();
  delete client;
  return EXIT_SUCCESS;
}
