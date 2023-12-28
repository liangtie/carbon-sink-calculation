#ifndef CARBON_SINK_FORM_H
#define CARBON_SINK_FORM_H

struct CarbonSinkForm
{
    int _year;
    double _area;
    double polygon;
    int floorCount;
    double height;
    int buildingCount;

    [[nodiscard]] double getCarbonSink() const;
};

#endif