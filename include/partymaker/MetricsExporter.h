#include <string>
#include <unordered_map>

using std::string;
using std::unordered_map;

class MetricsExporter {
 public:
  void export_measurement(const string& measurement,
      const unordered_map<string,string>& tags,
      const unordered_map<string,long>& fields);
};

