#include "prometheus/wavefront_serializer.h"
#include <cmath>
#include <iostream>
#include <limits>

namespace prometheus {
    static const std::string quote = "\"";
    void WavefrontSerializer::AppendTagMap(std::ostream &out, std::vector<ClientMetric::Label> tags) const {
        if (tags.empty())
            return;

        for (ClientMetric::Label &tag : tags) {
            out << " " << quote << EscapeCharacter(tag.name) << quote << "=" << quote << EscapeCharacter(tag.value)
                << quote;
        }
    }

    void WavefrontSerializer::SerializeCounter(std::ostream &out, const MetricFamily &family,
                                               const ClientMetric &metric) const {
        out << quote << EscapeCharacter(family.name) << quote << " ";
        out << ToString(metric.counter.value) << " ";
        if (metric.timestamp_ms != 0) {
            out << (metric.timestamp_ms / 1000) << " ";
        }
        out << "source=" << quote << "prometheusMetrics" << quote;
        AppendTagMap(out, metric.label);
    }

    void WavefrontSerializer::SerializeFamily(std::ostream &out, const MetricFamily &family) const {
        switch (family.type) {
            case MetricType::Counter:
                for (auto &metric : family.metric) {
                    SerializeCounter(out, family, metric);
                }
                break;
            case MetricType::Gauge:
                for (auto &metric : family.metric) {
                    // SerializeGauge(out, family, metric);
                }
                break;
            default:
                break;
        }
    }

    void WavefrontSerializer::Serialize(std::ostream &out,
                                        const std::vector<MetricFamily> &metrics) const {
        for (auto &family : metrics) {
            SerializeFamily(out, family);
        }
    }
}

