#include "include/General/ulogger.hpp"

ULogger::ULogger(std::fstream& tfile, QDebug& deb) : file(tfile), std(deb)
{

}

template <typename T>
ULogger &operator<<(ULogger& tLog, T const& arg)
{
    tLog.std << arg << QTime::currentTime();
    tLog.file << arg << QTime::currentTime();
    return tLog;
}
