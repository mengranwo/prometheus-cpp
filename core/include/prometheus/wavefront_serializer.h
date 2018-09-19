#pragma once

#include <string>
#include <vector>

#include "prometheus/metric_family.h"
#include "prometheus/serializer.h"

namespace prometheus {
    /**
     * serializer to generate wavefront proxy supported data format
     * @author Mengran Wang (mengranw@vmware.com).
     */
    class WavefrontSerializer : public Serializer {
    public:
        using Serializer::Serialize;
        void Serialize(std::ostream& out,
                       const std::vector<MetricFamily>& metrics) const override;


    private:
        void SerializeFamily(std::ostream &out, const MetricFamily &family) const;
        void SerializeCounter(std::ostream &out, const MetricFamily &family, const ClientMetric &metric) const;
        void SerializeGauge(std::ostream &out, const MetricFamily &family, const ClientMetric &metric) const;
        void AppendTagMap(std::ostream &out, std::vector<ClientMetric::Label> tags) const;
    };
}
