#ifndef __ARGUMENTS_HPP__
#define __ARGUMENTS_HPP__

#include <string>
#include <vector>

class Arguments {
 public:
  Arguments(const int& argc, const char* argv[]);
  ~Arguments();

  const std::string& httpMethod() const;
  const std::string& data() const;
  const bool& verbose() const;
  const std::vector<std::string>& urls() const;

  void print() const;

 private:
  Arguments();
  Arguments(const Arguments&);
  Arguments& operator=(const Arguments&);
  bool _verbose;
  std::string _data;
  std::string _httpMethod;
  std::vector<std::string> _urls;
};

#endif  // __ARGUMENTS_HPP__
