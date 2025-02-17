#ifndef MOCKDATA_H
#define MOCKDATA_H
struct MockData
{
    double stw;
    double sog;
    double awa;
    double aws;
    double dpt;
    double hdg;
    double cog;
    // 
    double latdeg;
    double latmin;
    bool isNorth;
    double londeg;
    double lonmin;
    bool isWest;

    //
    double crossTrack;
    double destBearing; 
    double destRange;
    String steerDirection;
};

#endif