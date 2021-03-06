#pragma once

#include <string>
#include <vector>

#include "prometheus/client_metric.h"
#include "prometheus/metric_family.h"

namespace prometheus {

    class Serializer {
    public:
        virtual ~Serializer() = default;

        virtual std::string Serialize(const std::vector<MetricFamily> &) const;

        virtual void Serialize(std::ostream &out,
                               const std::vector<MetricFamily> &metrics) const = 0;

        // utility functions shared by subclass
        std::string ToString(double value) const;
        const std::string EscapeCharacter(const std::string &target) const;
    };
}  // namespace prometheus
