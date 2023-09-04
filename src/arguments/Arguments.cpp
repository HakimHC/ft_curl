#include "Arguments.hpp"

#include <cxxopts.hpp>
#include <memory>
#include <stdexcept>

#include "logging.hpp"

Arguments::Arguments() {}
Arguments::~Arguments() {}

Arguments::Arguments(const int& argc, const char* argv[]) {
  std::unique_ptr<cxxopts::Options> allocated(new cxxopts::Options(
      argv[0], " - a simple HTTP client, made for educational purposes."));

  auto& options = *allocated;
  options.positional_help("URL").show_positional_help();

  options.set_width(70).set_tab_expansion().add_options()(
      "v,verbose", "Produce verbose output",
      cxxopts::value<bool>()->default_value("false"))(
      "X,request", "Specify request method to use",
      cxxopts::value<std::string>())("d,data", "Specify POST request data",
                                     cxxopts::value<std::string>())(
      "URL", "URL to request", cxxopts::value<std::vector<std::string>>())(
      "help", "Print help");

  options.parse_positional({"URL"});

  auto result = options.parse(argc, argv);

  this->_httpMethod = "GET";
  this->_verbose = false;

  if (result.count("help")) throw std::runtime_error(options.help({""}));
  if (result.count("data")) {
    this->_data = result["data"].as<std::string>();
  }
  if (result.count("request")) {
    this->_httpMethod = result["request"].as<std::string>();
  }
  if (result.count("verbose")) {
    this->_verbose = true;
  }

  if (result.count("URL") < 1) throw std::runtime_error(options.help({""}));
  auto& pos = result["URL"].as<std::vector<std::string>>();
  for (auto& i : pos) this->_urls.push_back(i);
}

const std::string& Arguments::data() const { return this->_data; }

const std::string& Arguments::httpMethod() const { return this->_httpMethod; }

const bool& Arguments::verbose() const { return this->_verbose; }
const std::vector<std::string>& Arguments::urls() const { return this->_urls; }

void Arguments::print() const {
  LOG("Verbose: " << this->_verbose);
  LOG("Method: " << this->_httpMethod);
  LOG("Data: " << this->_data);
  std::cout << "URLS: { ";
  for (size_t i = 0; i < this->_urls.size(); i++) {
    std::cout << this->_urls[i];
    if (i + 1 < this->_urls.size()) std::cout << ", ";
  }
  std::cout << " }" << std::endl;
}
