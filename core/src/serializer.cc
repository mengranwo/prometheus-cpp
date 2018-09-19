#include "prometheus/serializer.h"

#include <sstream>
#include <cmath>

namespace prometheus {

    std::string Serializer::Serialize(
            const std::vector<MetricFamily> &metrics) const {
        std::ostringstream ss;
        Serialize(ss, metrics);
        return ss.str();
    }

    // Write a double as a string, with proper formatting for infinity and NaN
    std::string Serializer::ToString(double v) const {
        if (std::isnan(v)) {
            return "Nan";
        }
        if (std::isinf(v)) {
            return (v < 0 ? "-Inf" : "+Inf");
        }
        return std::to_string(v);
    }

    const std::string Serializer::EscapeCharacter(const std::string &value) const {
        bool copy = false;
        std::string temp = "";

        for (size_t i = 0; i < value.size(); ++i) {
            char c = value[i];
            if (c == '\\' || c == '"' || c == '\n') {
                if (!copy) {
                    temp.reserve(value.size() + 1);
                    temp.assign(value, 0, i);
                    copy = true;
                }
                if (c == '\\') {
                    temp.append("\\\\");
                } else if (c == '"') {
                    temp.append("\\\"");
                } else {
                    temp.append("\\\n");
                }
            } else if (copy) {
                temp.push_back(c);
            }
        }
        return copy ? temp : value;
    }
}
